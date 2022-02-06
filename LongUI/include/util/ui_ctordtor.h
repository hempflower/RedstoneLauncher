﻿#pragma once


#include "../luiconf.h"
#include "ui_unimacro.h"
#include <utility>
#include <cassert>
#include <type_traits>


#ifndef LUI_CANNOT_CALL_CONSTRUCTOR_DIRECTLY

// MSVC  -> can call ctor
// Clang -> call ctor via -Wmicrosoft-explicit-constructor-call
// GCC   -> cannot call ctor

#if LUI_COMPILER == LUI_COMPILER_GCC
#define LUI_CANNOT_CALL_CONSTRUCTOR_DIRECTLY
#endif

#endif

#ifdef LUI_CANNOT_CALL_CONSTRUCTOR_DIRECTLY
#include <new>
#endif

// LongUI::impl namespace
namespace LongUI { namespace impl {
    // empty dtor
    void empty_dtor(void*) noexcept;
    // dtor_t
    struct dtor_t { void(*ptr)(void*) noexcept; };
    // func-vtable helper
    struct vtable_helper {
        void(*create_obj)(void*) noexcept;
        void(*copy_t_obj)(void*, const void*) noexcept;
        void(*move_t_obj)(void*, void*) noexcept;
        void(*delete_obj)(void*) noexcept;
    };
    // release the object: real
    template<typename T, bool> struct delete_obj_helper { };
    // release the object: real
    template<typename T>
    struct delete_obj_helper<T, true> {
        // delete obj
        static inline void delete_obj_real(void*p) noexcept { }
        // get delete 
        static inline dtor_t delete_obj_ptr() noexcept { return { empty_dtor }; }
    };
    // release the object: real
    template<typename T>
    struct delete_obj_helper<T, false> {
        // delete
        static inline void delete_obj_real(void*p) noexcept { static_cast<T*>(p)->T::~T(); }
        // get delete 
        static inline dtor_t delete_obj_ptr() noexcept { return { delete_obj_real }; }
    };
    // empty0
    struct empty0 {};
    // func-vtable getter
    template<typename T> struct ctor_dtor {
        // member
        T       m;
        // ctor
        inline ctor_dtor() noexcept {};
        // dtor
        inline ~ctor_dtor() noexcept {};
        // copy ctor
        inline ctor_dtor(const ctor_dtor& a) noexcept : m(a.m) {};
        // move ctor
        inline ctor_dtor(ctor_dtor&& a) noexcept : m(std::move(a.m)) {};
        // create the object
        static void create_obj(void* ptr) noexcept {
#ifdef LUI_CANNOT_CALL_CONSTRUCTOR_DIRECTLY
            // gcc cannot call ctor directly
            new(ptr) ctor_dtor<T>();
#else
            // msc/clang extended support
            static_cast<ctor_dtor<T>*>(ptr)->ctor_dtor<T>::ctor_dtor();
#endif
        }
        // release the object
        static void delete_obj(void*p) noexcept { 
            delete_obj_helper<T, std::is_trivially_destructible<T>::value>::delete_obj_real(p);
        }
        // delete_obj pointer
        static inline dtor_t delete_obj_ptr() noexcept {
            return delete_obj_helper<T, std::is_trivially_destructible<T>::value>::delete_obj_ptr();
        }
        // ctor
        template<typename ...Args>
        ctor_dtor(empty0, Args&&... args) noexcept : m(std::forward<Args>(args)...) {};
        // create
        template<typename ...Args>
        static void create(void* ptr, Args&&... args) noexcept {
#ifdef LUI_CANNOT_CALL_CONSTRUCTOR_DIRECTLY
            // gcc cannot call ctor directly
            new(ptr) ctor_dtor<T>(empty0{}, std::forward<Args>(args)...);
#else
                // msc/clang extended support
            static_cast<ctor_dtor<T>*>(ptr)->ctor_dtor<T>::ctor_dtor(empty0{}, std::forward<Args>(args)...);
#endif
        }
#ifdef LUI_NONPOD_VECTOR
        // copy the object
        static void copy_t_obj(void* ptr, const void* x) noexcept {
            assert(ptr != x);
            const T& obj = static_cast<const T*>(x);
            create(t, obj);
        }
        // move the object
        static void move_t_obj(void* ptr, void* x) noexcept {
            assert(ptr != x);
            T& obj = static_cast<T*>(x);
            create(t, std::move(obj));
        }
        // get the vtable ptr
        static const vtable_helper* get() noexcept {
            static const vtable_helper helper{
                create_obj,  copy_t_obj, move_t_obj,  delete_obj };
            return &helper;
        }
#endif
    };
}}

