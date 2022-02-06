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

#include "ui_listcols.h"
//#include "../util/ui_double_click.h"

// ui namespace
namespace LongUI {
    // tree col
    class UITreeCol;
    // treecols control
    class UITreeCols : public UIBoxLayout {
        // super class
        using Super = UIBoxLayout;
        // item list
        //using ColTree = POD::Vector<UITreeCol*>;
    protected:
        // ctor
        UITreeCols(const MetaControl&) noexcept;
    public:
        // class meta
        static const  MetaControl   s_meta;
        // dtor
        ~UITreeCols() noexcept;
        // ctor
        explicit UITreeCols(UIControl* parent = nullptr) noexcept : UITreeCols(UITreeCols::s_meta) { this->final_ctor(parent); }
    protected:
        // do event
        auto DoEvent(UIControl* s, const EventArg& e) noexcept->EventAccept override;
        // update
        void Update(UpdateReason) noexcept override;
    private:
        // relayout
        void relayout_final() noexcept;
    private:
        // do update for item
        static void do_update_for_item(UIControl&) noexcept;
    };
    // get meta info for UITreeCols
    LUI_DECLARE_METAINFO(UITreeCols);
}

