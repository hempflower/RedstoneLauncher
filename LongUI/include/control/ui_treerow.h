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

// super
#include "ui_control.h"
//#include "../util/ui_double_click.h"
// base
#include "ui_image.h"

// ui namespace
namespace LongUI {
    // tree row
    class UITreeRow : public UIControl {
        // super class
        using Super = UIControl;
    protected:
        // ctor
        UITreeRow(const MetaControl&) noexcept;
    public:
        // class meta
        static const  MetaControl   s_meta;
        // dtor
        ~UITreeRow() noexcept;
        // ctor
        explicit UITreeRow(UIControl* parent = nullptr) noexcept : UITreeRow(UITreeRow::s_meta) { this->final_ctor(parent); }
    public:
        // is selected?
        //auto IsSelected() const noexcept { return m_oStyle.state.selected; }
        // get row string
        void GetRowString(CUIString&) const noexcept;
        // set has child
        void SetHasChild(bool has) noexcept;
        // open node
        bool OpenNode() noexcept;
        // close node
        bool CloseNode() noexcept;
        // toggle node
        bool ToggleNode() noexcept;
        // Init open close[ call this from parent]
        void InitOpen_Parent(bool) noexcept;
    public:
        // do normal event
        auto DoEvent(UIControl* sender, const EventArg& e) noexcept->EventAccept override;
        // do mouse event
        auto DoMouseEvent(const MouseEventArg& e) noexcept->EventAccept override;
        // update
        void Update(UpdateReason) noexcept override;
        // render this control only, [Global rendering and Incremental rendering]
        //void Render() const noexcept override;
        // recreate/init device(gpu) resource
        //auto Recreate() noexcept->Result override;
    protected:
        // initialize
        void initialize() noexcept override;
        // open/close node
        void open_close(bool open) noexcept;
        // relayout
        void relayout() noexcept;
        // refresh fitting
        void refresh_fitting() noexcept;
    private: // private impl
        // private twisty[+]
        UIImage                 m_oTwisty;
        // private image
        UIImage                 m_oImage;
    protected:
        // node closed
        bool                    m_bOpened = true;
        // node keep child
        bool                    m_bHasChild = false;
    public:
        // skip relayout
        //bool                    skip_relayout = false;
    };
    // get meta info for UITreeRow
    LUI_DECLARE_METAINFO(UITreeRow);
}
