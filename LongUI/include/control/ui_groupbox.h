#pragma once
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
// tmp->hbox
#include "ui_box.h"

// ui namespace
namespace LongUI {
    // caption
    class UICaption;
    // groupbox
    class UIGroupBox : public UIBoxLayout {
        // super class
        using Super = UIBoxLayout;
    protected:
        // ctor
        UIGroupBox(const MetaControl&) noexcept;
    public:
        // class meta
        static const  MetaControl   s_meta;
        // dtor
        ~UIGroupBox() noexcept;
        // ctor
        explicit UIGroupBox(UIControl* parent = nullptr) noexcept : UIGroupBox(UIGroupBox::s_meta) { this->final_ctor(parent); }
        // caption removed
        void CaptionRemoved(UICaption& c) noexcept;
    public:
         //update this
        //void Update() noexcept override;
    protected:
        // add attribute
        void add_attribute(uint32_t key, U8View value) noexcept override;
        // add child
        void add_child(UIControl& child) noexcept override;
#ifdef LUI_ACCESSIBLE
        // accessible api
        auto accessible(const AccessibleEventArg& args) noexcept->EventAccept;
#endif
    private: // private impl
        // private head
        UIHBoxLayout            m_oHeadLayout;
        // private body
        UIVBoxLayout            m_oBodyLayout;
    private:
        // caption
        UICaption*              m_pCaption = nullptr;
    };
    // get meta info for UIGroupBox
    LUI_DECLARE_METAINFO(UIGroupBox);
}