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

#include "ui_scrollarea.h"

namespace LongUI {
    // splitter
    class UISplitter;
    // meta def
    struct UIMetaTypeDef;
    // box layout
    class UIBoxLayout : public UIScrollArea {
        // super class
        using Super = UIScrollArea;
        // friend class
        friend UIMetaTypeDef;
    public:
        // class meta
        static const  MetaControl   s_meta;
        // dtor
        ~UIBoxLayout() noexcept override;
        // ctor
        explicit UIBoxLayout(UIControl* parent = nullptr) noexcept : UIBoxLayout(UIBoxLayout::s_meta) { this->final_ctor(parent); }
        // do event
        auto DoEvent(UIControl* sender, const EventArg& e) noexcept->EventAccept override;
        // update
        void Update(UpdateReason) noexcept override;
    protected:
        // lui std ctor
        UIBoxLayout(const MetaControl& ) noexcept;
        // need relayout
        auto is_need_relayout() const noexcept { return m_state.reason & Reason_BasicRelayout; }
    private:
        // move splitter
        void move_splitter(UIControl& splitter, const EventArg& e) noexcept;
    protected:
         //add attribute
        //void add_attribute(uint32_t key, U8View value) noexcept override;
        // relayout this
        void relayout_this() noexcept;
        // relayout h
        void relayout_h() noexcept;
        // relayout v
        void relayout_v() noexcept;
        // refresh fitting
        void refresh_fitting() noexcept;
#ifdef LUI_ACCESSIBLE
        // accessible 
        auto accessible(const AccessibleEventArg&) noexcept->EventAccept override;
#endif
    public:
        // set orient
        void SetOrient(AttributeOrient o) noexcept;
        // get orient
        auto GetOrient() const noexcept { return static_cast<AttributeOrient>(m_state.orient); }
    protected:
        // real fitting size
        Size2F          m_szRealFitting = {};
    };
    // h-box layout
    using UIHBoxLayout = UIBoxLayout;
    // v-box layout
    class UIVBoxLayout final : public UIBoxLayout {
        // super class
        using Super = UIBoxLayout;
    public:
        // class meta
        static const  MetaControl   s_meta;
        // ctor
        explicit UIVBoxLayout(UIControl* parent = nullptr) noexcept : UIVBoxLayout(UIVBoxLayout::s_meta) { this->final_ctor(parent); }
        // dtor
        ~UIVBoxLayout() noexcept;
    protected:
        // ctor
        UIVBoxLayout(const MetaControl& ) noexcept;
    public:
    };
    // get meta info for UIBoxLayout
    LUI_DECLARE_METAINFO(UIBoxLayout);
    // get meta info for UIVBoxLayout
    LUI_DECLARE_METAINFO(UIVBoxLayout);
}