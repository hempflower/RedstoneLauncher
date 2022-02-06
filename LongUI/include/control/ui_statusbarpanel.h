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

#include "ui_label.h"

// ui namespace
namespace LongUI {
    // status bar panel
    class UIStatusBarPanel : public UILabel {
        // super class
        using Super = UILabel;
    public:
        // class meta
        static const  MetaControl   s_meta;
        // dtor
        ~UIStatusBarPanel() noexcept = default;
        // ctor
        explicit UIStatusBarPanel(UIControl* parent = nullptr) noexcept : UIStatusBarPanel(UIStatusBarPanel::s_meta) { this->final_ctor(parent); }
    protected:
        // lui std ctor
        UIStatusBarPanel(const MetaControl&) noexcept;
        // add attribute
        void add_attribute(uint32_t key, U8View value) noexcept override;
    };
    // get meta info for UIBoxLayout
    LUI_DECLARE_METAINFO(UIStatusBarPanel);
}