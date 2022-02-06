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

// ui
#include "ui_control.h"
#include "../resource/ui_resource_id.h"


// ui namespace
namespace LongUI {
    // image resource
    class CUIImage;
    // image control
    class UIImage : public UIControl {
        // super class
        using Super = UIControl;
    public:
        // set image source
        void SetSource(U8View src) noexcept;
        // TODO: just set center contain?
        void JustSetAsIcon() noexcept { }
    protected:
        // ctor
        UIImage(const MetaControl&) noexcept;
    public:
        // class meta
        static const  MetaControl   s_meta;
        // dtor
        ~UIImage() noexcept;
        // ctor
        explicit UIImage(UIControl* parent = nullptr) noexcept : UIImage(UIImage::s_meta) { this->final_ctor(parent); }
    public:
        // do normal event
        auto DoEvent(UIControl* sender, const EventArg& e) noexcept->EventAccept override;
        // mouse event
        //auto DoMouseEvent(const MouseEventArg & e) noexcept->EventAccept override;
        // recreate_device
        //auto Recreate() noexcept->Result override;
        // render
        void Render() const noexcept override;
    protected:
        // add attribute
        void add_attribute(uint32_t key, U8View value) noexcept override;
    protected:
        // image id
        CUIResourceID       m_idSrc;
        // frame id
        uint32_t            m_idFrame = 0;
        // frame count
        uint32_t            m_uFrameCount = 1;
    };
    // get meta info for UIImage
    LUI_DECLARE_METAINFO(UIImage);
}