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

// ui header
#include "ui_box.h"
#include "ui_label.h"
#include "../style/ui_text.h"
#include "../core/ui_string.h"
#include "../text/ui_text_layout.h"
#include "../core/ui_const_sstring.h"
#include "../util/ui_named_control.h"

//#define LUI_UICAPTION_AS_UILABEL

// ui namespace
namespace LongUI {
    // UIGroupBox
    class UIGroupBox;
#ifdef LUI_UICAPTION_AS_UILABEL
    // caption
    class UICaption : public UILabel {
        // super class
        using Super = UILabel;
#else
    // caption
    class UICaption : public UIBoxLayout {
        // super class
        using Super = UIBoxLayout;
#endif
    protected:
        // ctor
        UICaption(const MetaControl&) noexcept;
    public:
        // class meta
        static const  MetaControl   s_meta;
        // dtor
        ~UICaption() noexcept;
        // ctor
        explicit UICaption(UIControl* parent = nullptr) noexcept : UICaption(UICaption::s_meta) { this->final_ctor(parent); }
        // link
        void Link(UIGroupBox& box) noexcept { m_pGroupBox = &box; }
#ifndef LUI_UICAPTION_AS_UILABEL
        // ref defualt label text
        auto&RefText() const noexcept { return m_oLabel.RefText(); }
    public:
        // update
        void Update(UpdateReason) noexcept override;
    protected:
        // initialize
        void initialize() noexcept override;
    protected:
        // defualt label
        UILabel                 m_oLabel;
#endif
    protected:
        // add attribute
        void add_attribute(uint32_t key, U8View value) noexcept override;
    protected:
        // group box
        UIGroupBox*             m_pGroupBox = nullptr;
    };
    // get meta info for UICaption
    LUI_DECLARE_METAINFO(UICaption);
}
