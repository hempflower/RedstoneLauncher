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

#include "ui_box.h"

// ui namespace
namespace LongUI {
    // box
    class UIRichListBox;
    // tool bar
    class UIRichListItem : public UIBoxLayout {
        // super class
        using Super = UIBoxLayout;
        // friend class
        friend UIRichListBox;
    public:
        // class meta
        static const  MetaControl   s_meta;
        // dtor
        ~UIRichListItem() noexcept;
        // ctor
        explicit UIRichListItem(UIControl* parent = nullptr) noexcept : UIRichListItem(UIRichListItem::s_meta) { this->final_ctor(parent); }
        // mouse event
        auto DoMouseEvent(const MouseEventArg& e) noexcept->EventAccept override;
    protected:
        // lui std ctor
        UIRichListItem(const MetaControl&) noexcept;
    };
    // get meta info for UIBoxLayout
    LUI_DECLARE_METAINFO(UIRichListItem);
}