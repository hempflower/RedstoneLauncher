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
#include "ui_box.h"
// base
#include "ui_image.h"
#include "ui_label.h"

// ui namespace
namespace LongUI {
    // image control
    class UIImage;
    // redio group
    class UIRadioGroup;
    // radio
    class UIRadio : public UIBoxLayout {
        // super class
        using Super = UIBoxLayout;
    public:
        // on commnad event
        static constexpr auto _onCommand() noexcept { return GuiEvent::Event_OnCommand; }
    public:
        // is checked
        auto IsChecked() const noexcept { return m_oStyle.state & State_Checked; }
        // set checked
        void SetChecked(bool) noexcept;
        // set selected(sameas checked)
        void SetSelected(bool sel) noexcept { this->SetChecked(sel); }
        // set image source
        void SetImageSource(U8View src) noexcept;
        // get text [RECOMMENDED] 
        auto GetTextView() const noexcept { return m_oLabel.GetTextView(); }
        // get text [UNRECOMMENDED] 
        auto GetText() const noexcept { return m_oLabel.GetText(); }
        // ref text - string object
        auto&RefText() const noexcept { return m_oLabel.RefText(); }
        // set text
        void SetText(const CUIString& text) noexcept;
        // set text
        void SetText(CUIString&& text) noexcept;
        // set text
        void SetText(U16View text) noexcept;
    protected:
        // ctor
        UIRadio(const MetaControl&) noexcept;
    public:
        // class meta
        static const  MetaControl   s_meta;
        // dtor
        ~UIRadio() noexcept;
        // ctor
        explicit UIRadio(UIControl* parent = nullptr) noexcept : UIRadio(UIRadio::s_meta) { this->final_ctor(parent); }
        // update this
        void Update(UpdateReason) noexcept override;
        // do normal event
        auto DoEvent(UIControl* sender, const EventArg& arg) noexcept->EventAccept override;
        // do mouse event
        auto DoMouseEvent(const MouseEventArg& e) noexcept->EventAccept override;
        // do input event
        auto DoInputEvent(InputEventArg e) noexcept->EventAccept;
#ifdef LUI_DRAW_FOCUS_RECT
        // Update Focus Rect
        void UpdateFocusRect() const noexcept;
        // trigger
        auto FireEvent(const GuiEventArg& event) noexcept->EventAccept override;
#endif
    protected:
        // after text changed
        void after_text_changed() noexcept;
        // initialize
        void initialize() noexcept override;
        // add attribute
        void add_attribute(uint32_t key, U8View value) noexcept override;
        // private image
        UIImage             m_oImage;
        // private label
        UILabel             m_oLabel;
    private:
        // radio group
        UIRadioGroup*       m_pRadioGroup = nullptr;
        // image child
        UIImage*            m_pImageChild = nullptr;
        // a new image added
        bool                m_bNewImage = false;
    };
    // get meta info for UIRadio
    LUI_DECLARE_METAINFO(UIRadio);
}