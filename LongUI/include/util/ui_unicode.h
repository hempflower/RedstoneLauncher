﻿#pragma once
#include <cstdint>

namespace LongUI {
    /// <summary>
    /// unicode namespace
    /// </summary>
    namespace Unicode {
        // utf-8
        struct UTF8 { using type = char; };
        // utf-16
        struct UTF16 { using type = char16_t; };
        // utf-16
        struct UTF32 { using type = char32_t; };
        // wchar helper
        template<size_t> struct wchar_helper;
        // 2?char16_t
        template<> struct wchar_helper<sizeof(char16_t)> { using type = UTF16; using untype = UTF32; };
        // 4?char32_t
        template<> struct wchar_helper<sizeof(char32_t)> { using type = UTF32; using untype = UTF16; };
        // wide char
        struct WChar {
            using type = wchar_t;
            using same = typename wchar_helper<sizeof(wchar_t)>::type;
            using same_t = typename same::type;
            using unsame = typename wchar_helper<sizeof(wchar_t)>::untype;
            using unsame_t = typename unsame::type;
        };
        // is_surrogate
        inline auto IsSurrogate(uint16_t ch) noexcept { return ((ch) & 0xF800) == 0xD800; }
        // is_high_surrogate
        inline auto IsHighSurrogate(uint16_t ch) noexcept { return ((ch) & 0xFC00) == 0xD800; }
        // is_low_surrogate
        inline auto IsLowSurrogate(uint16_t ch) noexcept { return ((ch) & 0xFC00) == 0xDC00; }
    }
    // wchar_t
    using wcharxx_t = typename Unicode::WChar::same_t;
    // not wchar_t
    using unwchar_t = typename Unicode::WChar::unsame_t;
    // detail namespace
    namespace impl {
        // utf16 to system char type
        inline auto sys(const wcharxx_t* str) noexcept {
            return reinterpret_cast<const wchar_t*>(str);
        }
        // utf16 to system char type
        inline auto sys(const wchar_t* str) noexcept {
            return reinterpret_cast<const wcharxx_t*>(str);
        }
    }
}
