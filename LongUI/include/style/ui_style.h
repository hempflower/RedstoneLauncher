﻿#pragma once

// ui
#include "../luiconf.h"
#include "ui_ssvalue.h"
#include "ui_attribute.h"
#include "ui_style_state.h"
#include "../core/ui_basic_type.h"
// c++
#include <cassert>

namespace LongUI {
    // Box Model
    struct Box {
        // visible rect[world border edge]
        RectF       visible;
        // box position
        Point2F     pos;
        // box size(margin-box size)
        Size2F      size;
        // margin
        RectF       margin;
        // border
        RectF       border;
        // padding
        RectF       padding;
        // ctor
        void Init() noexcept;
        // get margin edge
        auto GetMarginEdge() const noexcept { RectF rc; GetMarginEdge(rc); return rc; }
        // get border edge
        auto GetBorderEdge() const noexcept { RectF rc; GetBorderEdge(rc); return rc; }
        // get padding edge
        auto GetPaddingEdge() const noexcept { RectF rc; GetPaddingEdge(rc); return rc; }
        // get content edge
        auto GetContentEdge() const noexcept { RectF rc; GetContentEdge(rc); return rc; }
        // get safe-border edge
        auto GetSafeBorderEdge() const noexcept->RectF;
        // get contect size
        auto GetContentSize() const noexcept->Size2F;
        // get border size
        auto GetBorderSize() const noexcept->Size2F;
        // get contect pos
        auto GetContentPos() const noexcept->Point2F;
        // get non contect size
        auto GetNonContentSize() const noexcept->Size2F;
        //// get Non-content size
        //void GetNonContect(RectF&) const noexcept;
        //// get Non-content rect
        //auto GetNonContect() const noexcept { RectF rc; GetNonContect(rc); return rc; }
        // get margin edge
        void GetMarginEdge(RectF&) const noexcept;
        // get border edge
        void GetBorderEdge(RectF&) const noexcept;
        // get padding edge
        void GetPaddingEdge(RectF&) const noexcept;
        // get content edge
        void GetContentEdge(RectF&) const noexcept;
    };
    // text/font
    struct TextFont;
    // Style model
    struct /*alignas(double)*/ Style {
        // get TextFont
        auto GetTextFont() noexcept {
            assert(offset_tf && "bad offset");
            const auto ptr = reinterpret_cast<char*>(this) + offset_tf;
            return reinterpret_cast<TextFont*>(ptr);
        }
        // ctor
        Style() noexcept;
        // dtor
        ~Style() noexcept;
        // no copy
        Style(const Style&) noexcept = delete;
        // state            [4]
        StyleState          state;
        // state inherited  [4]
        StyleState          inherited;
        // flex             [4]
        float               flex;
        // t-duration       [2]
        uint16_t            tduration;
        // offset in byte for text font, set this if support text [2]
        uint16_t            offset_tf;
        // pack             [1]
        AttributePack       pack;
        // align            [1]
        AttributeAlign      align;
        // appearance tpye  [1]
        AttributeAppearance appearance;
        // t-timing funtion [1]
        uint8_t             tfunction;

        // overflow-x       [1] high 6bit for min-* * max-*
        AttributeOverflow   overflow_xex;
        // overflow-y
        AttributeOverflow   overflow_y;
        // accesskey char   [1]
        char                accesskey;
        // extri-anima-buck [1]
        uint8_t             extra_abcount;

        // fitting size / size if overflow_sizestyled.xxx
        Size2F              fitting;
        // limited size / min-size if sizestyled
        Size2F              limited;
        // style used max size
        Size2F              maxsize;
#ifndef LUI_DISABLE_STYLE_SUPPORT
        // value list matched
        SSValues            matched;
        // trigger
        SSTrigger           trigger;
#endif
    };
}
