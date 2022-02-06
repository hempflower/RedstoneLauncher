﻿#pragma once

// ui
#include <control/ui_control.h>

// c++
#include <cassert>


/// <summary>
/// private function/data to UIControl
/// </summary>
struct LongUI::UIControlPrivate {
    // need relayout
    static auto IsNeedRelayout(UIControl& ctrl) noexcept { return ctrl.m_state.reason; }
#ifndef LUI_DISABLE_STYLE_SUPPORT
    // ensure bg renderer
    static auto EnsureBgRenderer(UIControl& ctrl) noexcept->CUIRendererBackground*;
    // get bg renderer
    static auto GetBgRenderer(const UIControl& ctrl) noexcept->CUIRendererBackground*;
    // ensure bd renderer
    static auto EnsureBdRenderer(UIControl& ctrl) noexcept->CUIRendererBorder*;
    // get bd renderer
    static auto GetBdRenderer(const UIControl& ctrl) noexcept->CUIRendererBorder*;
#endif
    // refresh min size
    //static void RefreshMinSize(UIControl& ctrl) noexcept;
    // update world
    static void UpdateWorld(UIControl& ctrl) noexcept;
    // update world force
    static void UpdateWorldForce(UIControl& ctrl) noexcept;
    // update world - toplevel
    static void UpdateWorldTop(UIControl& ctrl, Size2L) noexcept;
    // do mouse enter event
    static auto DoMouseEnter(UIControl& ctrl, const Point2F& pos) noexcept->EventAccept;
    // do mouse leave event
    static auto DoMouseLeave(UIControl& ctrl, const Point2F& pos) noexcept->EventAccept;
    // ----------- INLINE ZONE ----------------
    // set_contect_minsize
    //static void SetConMinsize(UIControl& ctrl, Size2F s) noexcept { ctrl.set_contect_minsize(s); }
    // ref last end time capsule
    static auto&RefLastEnd(UIControl& ctrl) noexcept { return ctrl.m_pLastEnd; }
    // set attachment - fixed
    static void SetFixed(UIControl& ctrl) noexcept { ctrl.m_state.attachment = true; }
    // set focusable - false
    static void SetFocusable0(UIControl& ctrl) noexcept { ctrl.m_state.focusable = false; }
    // set focusable - true
    static void SetFocusable1(UIControl& ctrl) noexcept { ctrl.m_state.focusable = true; }
    // set capturable - false
    static void SetCapturable0(UIControl& ctrl) noexcept { ctrl.m_state.capturable = false; }
    // set capturable - true
    static void SetCapturable1(UIControl& ctrl) noexcept { ctrl.m_state.capturable = true; }
    // set appearance
    static void SetAppearance(UIControl& ctrl, AttributeAppearance a) noexcept { 
        assert(ctrl.is_inited() == false);
        ctrl.m_oStyle.appearance = a;
    }
    // force set fixed attachment
    static void FixedAttachment(UIControl& ctrl) noexcept { ctrl.m_state.attachment = Attachment_Fixed; }
    // force set appearance
    static void ForceAppearance(UIControl& ctrl, AttributeAppearance a) noexcept { ctrl.m_oStyle.appearance = a; }
    // set flex
    static void SetFlex(UIControl& ctrl, float flex) noexcept { ctrl.m_oStyle.flex = flex; }
    // set box minwidth
    //static void SetBoxMinWidth(UIControl& ctrl, float minw) noexcept { ctrl.m_oBox.minsize.width = minw; }
    // set orient
    static void SetOrient(UIControl& ctrl, bool o) noexcept { ctrl.m_state.orient = o; }
    // is need rerelayout
    //static auto IsNeedRelayout(const UIControl& ctrl) noexcept { return ctrl.is_need_relayout(); }
    // is mouse_continue
    static auto IsMouseCon(const UIControl& ctrl) noexcept { return ctrl.m_state.mouse_continue; }
    // is dirty
    static auto IsInDirty(const UIControl& ctrl) noexcept { return ctrl.is_in_dirty_list(); }
    // dirty = true
    static auto MarkInDirty(UIControl& ctrl) noexcept { return ctrl.m_state.in_dirty_list = true; }
    // dirty = false
    static auto ClearInDirty(UIControl& ctrl) noexcept { return ctrl.m_state.in_dirty_list = false; }
    // get layout value as uint32_t
    static auto GetLayoutValueU(const UIControl& ctrl) noexcept { return ctrl.m_uLayoutValue; }
    // get layout value as float
    static auto GetLayoutValueF(const UIControl& ctrl) noexcept { return reinterpret_cast<const float&>(ctrl.m_uLayoutValue); }
    // set layout value as uint32_t
    static void SetLayoutValueU(UIControl& ctrl, uint32_t data) noexcept { ctrl.m_uLayoutValue = data; }
    // set layout value as float
    static void SetLayoutValueF(UIControl& ctrl, float data) noexcept { reinterpret_cast<float&>(ctrl.m_uLayoutValue) = data; }
    // ref layout value as float
    static auto&RefLayoutValueF(UIControl& ctrl) noexcept { return reinterpret_cast<float&>(ctrl.m_uLayoutValue); }
    // ref style state
    static auto&RefStyleState(UIControl& ctrl) noexcept { return ctrl.m_oStyle.state; }
#ifndef LUI_DISABLE_STYLE_SUPPORT
    // ref style matched value
    static auto&RefStyleMatched(UIControl& ctrl) noexcept { return ctrl.m_oStyle.matched; }
    // ref style trigger
    static auto&RefStyleTrigger(UIControl& ctrl) noexcept { return ctrl.m_oStyle.trigger; }
#endif
    // set gui event to parent
    static void SetGuiEvent2Parent(UIControl& ctrl) noexcept { ctrl.m_state.gui_event_to_parent = true; }
    // prev control
    static auto&Prev(UIControl& ctrl) noexcept { return *ctrl.prev; }
    // next control
    static auto&Next(UIControl& ctrl) noexcept  { return *ctrl.next; }
    // next control
    static auto Next(const UIControl* ctrl) noexcept -> const UIControl* { return ctrl->next; }
    // prev control
    static auto Prev(UIControl* ctrl) noexcept { return ctrl->prev; }
    // next control
    static auto Next(UIControl* ctrl) noexcept { return ctrl->next; }
    // mark window minsize changed
    //static void MarkWindowMinsizeChanged(UIControl& ctrl) noexcept { ctrl.mark_window_minsize_changed(); }
    // add child
    static void AddChild(UIControl& o, UIControl& c) noexcept { o.add_child(c); }
    // ref style
    static auto&RefStyle(UIControl& o) noexcept { return o.m_oStyle; }
    // ref box
    static auto&RefBox(UIControl& o) noexcept { return o.m_oBox; }
};
