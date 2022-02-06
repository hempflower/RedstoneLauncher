﻿#pragma once

#include "../luiconf.h"
#ifndef LUI_DISABLE_STYLE_SUPPORT
#include "ui_renderer_decl.h"
#include "../core/ui_color.h"
#include "../core/ui_object.h"
#include "../core/ui_basic_type.h"
#include "../style/ui_attribute.h"
#include "../resource/ui_resource_id.h"
#include "../graphics/ui_graphics_decl.h"

namespace LongUI {
    // box
    struct Box;
    // background renderer
    class CUIRendererBackground : public CUISmallObject {
    public:
        // ctor
        CUIRendererBackground() noexcept;
        // dtor
        ~CUIRendererBackground() noexcept;
        // move ctor
        CUIRendererBackground(CUIRendererBackground&&) = delete;
        // copy ctor
        CUIRendererBackground(const CUIRendererBackground&) = delete;
        // befor render
        void BeforeRender() noexcept;
        // render color
        void RenderColor(const Box& box, Size2F) const noexcept;
        // render image
        void RenderImage(const Box& box, Size2F) const noexcept;
        // create device data
        auto CreateDeviceData() noexcept->Result;
        // release device data
        void ReleaseDeviceData();
        // set image id
        void SetImageId(uintptr_t id) noexcept;
        // get image id
        auto GetImageId() const noexcept { return m_idImage.GetId(); }
    private:
        // refresh image
        auto refresh_image() noexcept->Result;
        // ----------- CACHE-DATA -----------
        // image source
        RectF               m_rcImage = {};
        // image size
        Size2F              m_szImage = { 1, 1 };
        // ------------- GPU-RES ------------
    private:
        // ------------- GPU-RES ------------
        // effect
        I::Effect*          m_pBackground = nullptr;
        // iamge output
        I::EOutput*         m_pOutput = nullptr;
        // image brush
        //I::Brush*           m_pImageBrush = nullptr;
        // ------------- CPU-RES ------------
        // background-image
        CUIResourceID       m_idImage;
    public:
        // background-color
        ColorF              color;
        // background-size
        //Size2F              size;
        // background-clip
        AttributeBox        clip = Box_BorderBox;
        // background-repeat
        AttributeRepeat     repeat = Repeat_Repeat;
        // background-origin 
        AttributeBox        origin = Box_PaddingBox;
        // background-attachment
        AttributeAttachment attachment = Attachment_Scroll;
    private:
        // id change
        bool                m_bIdChanged = false;
    };
}
#endif