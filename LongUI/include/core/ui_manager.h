﻿#pragma once
/**
* Copyright (c) 2014-2020 dustpg   mailto:dustpg@gmail.com
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following
* conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*/

// debug
#include "../debugger/ui_debug.h"
// locker
#include "../thread/ui_locker.h"
// config
#include "../interface/ui_iconfig.h"
// cc
#include "ui_control_control.h"
// window manager
#include "ui_window_manager.h"
// resource manager
#include "ui_resource_manager.h"
// string view
#include "ui_string_view.h"
// ostype
#include "../util/ui_ostype.h"
// type
#include <type_traits>
// waiter
#include <thread/ui_waiter.h>
// info list
#include "../interface/ui_ctrlinfolist.h"

// longui manager
#define UIManager (LongUI::RefUIInstance())

// ui namespace
namespace LongUI {
    // detail namespace
    namespace impl { 
        // ctor_dtor
        template<typename T> struct ctor_dtor;
        // private data for manager
        template<size_t> struct private_manager;
        // 32bit
        template<> struct private_manager<4> { enum { size = 40, align = 4 }; };
        // 64bit
        template<> struct private_manager<8> { enum { size = 64, align = 8 }; };
    }
    // input
    class CUIInputKM;
    // config keeper, make sure config inited first
    struct ConfigKeeper { IUIConfigure* config; };
    // longui ui-manager
    class CUIManager final : 
        protected ConfigKeeper,
        public CUIDebug,
        public CUIResMgr, 
        public CUIWndMgr,
        public CUIControlControl {
        // refresh system info
        void refresh_system_info() noexcept;
    public:
        // input
        friend CUIInputKM;
        // ctor_dtor
        friend impl::ctor_dtor<CUIManager>;
        // interface for memory management
        struct IMM;
        // private
        struct Private;
    public:
        // delete later for control
        void DeleteLater(UIControl&) noexcept;
        // initialize
        auto Initialize(
            IUIConfigure* config = nullptr,
            ConfigureFlag cfgflag = ConfigureFlag::Flag_Default
        ) noexcept ->Result;
        // uninitialize
        void Uninitialize() noexcept;
        // do one frame
        void OneFrame() noexcept;
        // wait vblank
        void WaitForVBlank() noexcept;
        // need recreate_device
        void NeedRecreate() noexcept;
    public:
        // add [unique]/[release-free] text
        ULID GetUniqueText(U8View pair) noexcept;
        // create control within element name
        auto CreateControl(U8View element, UIControl* parent) noexcept->UIControl*;
    public:
        // call this on kill focus to manage input
        //void OnKillFocus() noexcept;
        // get wheel scroll lines
        auto GetWheelScrollLines() const noexcept { return m_uWheelScrollLines; }
        // get wheel scroll chars
        auto GetWheelScrollChars() const noexcept { return m_uWheelScrollChars; }
        // get delta time in ms
        auto GetDeltaTimeMs() const noexcept { return m_dwDeltaTime; }
        // get delta time in sec.
        auto GetDeltaTime() const noexcept { return m_fDeltaTime; }
        // get app run time in ms
        //auto GetAppTimeTick() const noexcept { return m_dwTimeTick - m_cStartTick; }
#ifdef NDEBUG
        // lock data
        void DataLock() noexcept { m_uiDataLocker.Lock(); }
#else
        // in rendering debug data
        size_t          dbg_rendering = 0;
        // lock data
        void DataLock() noexcept;
#endif
        // unlock data
        void DataUnlock() noexcept { m_uiDataLocker.Unlock(); }
        // lock rendering
        void RenderLock() noexcept { m_uiRenderLocker.Lock(); }
        // try lock rendering
        auto TryRenderLock() noexcept { return m_uiRenderLocker.TryLock(); }
        // unlock rendering
        void RenderUnlock() noexcept { m_uiRenderLocker.Unlock(); }
        // get data locker recursion count
        auto DataRecursion() const noexcept { return m_uiDataLocker.GetRecursionCount(); }
        // get gui thread id
        auto GetGuiThreadId() const noexcept { return m_uGuiThreadId; }
        // ref later locker
        auto&RefLaterLocker() noexcept { return m_uiLaterLocker; }
    public:
        // ref control infos
        auto&RefControlInfos() const noexcept { return m_oCtrlInfo; }
        // exit
        void Exit(uintptr_t code = 0) noexcept;
        // break loop
        void BreakMsgLoop(uintptr_t code) noexcept { this->config->BreakMsgLoop(code); }
        // msg-loop(could be in recursion)
        void RecursionMsgLoop() noexcept { this->config->RecursionMsgLoop(); }
        // On OOM
        auto HandleOOM(size_t retry_count, size_t try_alloc) noexcept->CodeOOM;
        // on error info lost
        void OnErrorInfoLost(Result, ErrorOccasion occ) noexcept;
        // load data from url
        void LoadDataFromUrl(U8View url_utf8, POD::Vector<uint8_t>& buffer) noexcept;
    public:
        // run a section script for event
        bool Evaluation(ScriptUI s, const GuiEventArg& c) noexcept { return this->config->Evaluation(s, c); }
        // alloc the script memory and copy into
        auto AllocScript(U8View view) noexcept { return this->config->AllocScript(view); }
        // free the script memory
        void FreeScript(ScriptUI script) noexcept { this->config->FreeScript(script); }
        // eval script for window init
        void Evaluation(U8View v, CUIWindow& w) noexcept { this->config->Evaluation(v, w); }
        // finalize window script if has script
        void FinalizeScript(CUIWindow& w) noexcept { this->config->FinalizeScript(w); };
    public:
        // set timer [0~7]
        void SetTimer(UIControl&, uint32_t elapse, uint32_t id0_7) noexcept;
        // kill timer [0~7]
        void KillTimer(UIControl&, uint32_t id0_7) noexcept;
    private:
        // ctor
        CUIManager(IUIConfigure*, ConfigureFlag, Result& ) noexcept;
        // ctor
        CUIManager(const CUIManager&) noexcept = delete;
        // ctor
        CUIManager(CUIManager&&) noexcept = delete;
        // dtor
        ~CUIManager() noexcept;
        // this manager
        inline auto this_() noexcept->CUIManager*;
    public:
#ifndef  NDEBUG
        // alloc counter: normal  [CUIManager::RefInstance().alloc_counter_n_dbg]
        size_t                  alloc_counter_n_dbg = 0;
        // alloc counter: small   [CUIManager::RefInstance().alloc_counter_s_dbg]
        size_t                  alloc_counter_s_dbg = 0;
#endif // ! NDEBUG
        // flag for configure
        ConfigureFlag const     flag;
    private:
        // delta time in sec.
        float                   m_fDeltaTime = 0.f;
        // app start tick
        //uint32_t                m_cStartTick = 0;
        // wheel scroll lines 
        uint32_t                m_uWheelScrollLines = 3;
        // wheel scroll chars
        uint32_t                m_uWheelScrollChars = 3;
        // gui thread id
        uint32_t                m_uGuiThreadId = 0;
        // unused u32
        uint32_t                m_uUnused = 0;
        // tool window
        HWND                    m_hToolWnd = nullptr;
#ifndef NDEBUG
        // debug window
        CUIWindow*              m_pDebugWindow = nullptr;
#endif
        // data locker
        CUILocker               m_uiDataLocker;
        // rendering locker
        CUILocker               m_uiRenderLocker;
        // ctor locker
        CUILocker               m_uiLaterLocker;
        // time capsule waiter
        CUIWaiter               m_uiTimeCapsuleWaiter;
    protected:
        // try recreate_device all device resource
        void try_recreate() noexcept;
        // call time capsule#1
        void call_time_capsule_s1() noexcept;
        // call time capsule#2
        void call_time_capsule_s2() noexcept;
        // private manager
        auto&pm() noexcept { return reinterpret_cast<Private&>(m_private); }
        // private data
        std::aligned_storage<
            impl::private_manager<sizeof(void*)>::size,
            impl::private_manager<sizeof(void*)>::align
        >::type                 m_private;
    private:
        // recreate_device flag
        bool                    m_flagRecreate = false;
    private:
        // control infos
        ControlInfoList         m_oCtrlInfo;
    public:
        // common buffer[single ime once]
        std::aligned_storage<IME_COMMON_BUF_LENGTH, sizeof(uint32_t)>::type
                                ime_common_buf;
    };
    // int code
    inline auto IntCode(uintptr_t code) noexcept -> int {
        return static_cast<int32_t>(static_cast<uint32_t>(code));
    }
    // int code
    inline auto IntCode(int code) noexcept -> uintptr_t {
        return static_cast<uint32_t>(static_cast<int32_t>(code));   
    }
    /// <summary>
    /// single instance buffer for longui manager
    /// </summary>
    extern std::aligned_storage<sizeof(CUIManager), alignof(CUIManager)>::type s_bufManager;
    PCN_FOINLINE
    /// <summary>
    /// Gets the ui manager instance.
    /// 获取UI管理器实例
    /// </summary>
    /// <returns></returns>
    static auto RefUIInstance() noexcept -> CUIManager & {
        return reinterpret_cast<CUIManager&>(s_bufManager);
    }
    // auto data locker
    class CUIDataAutoLocker {
    public:
        // ctor
        CUIDataAutoLocker() noexcept { LongUI::RefUIInstance().DataLock(); }
        // dtor
        ~CUIDataAutoLocker() noexcept { LongUI::RefUIInstance().DataUnlock(); }
    };
    // auto dxgi(rendering) locker
    class CUIRenderAutoLocker {
    public:
        // ctor
        CUIRenderAutoLocker() noexcept { LongUI::RefUIInstance().RenderLock(); }
        // dtor
        ~CUIRenderAutoLocker() noexcept { LongUI::RefUIInstance().RenderUnlock(); }
    };
    // blocking gui operation auto unlocker
    class CUIBlockingGuiOpAutoUnlocker {
        // counter
        const uint32_t  m_counter;
        // init
        static auto init() noexcept->uint32_t;
        // uninit
        static void uninit(uint32_t) noexcept;
    public:
        // ctor
        CUIBlockingGuiOpAutoUnlocker() noexcept : m_counter(init()) {};
        // dtor
        ~CUIBlockingGuiOpAutoUnlocker() noexcept { uninit(m_counter); }
    };
}

