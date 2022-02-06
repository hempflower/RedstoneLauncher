﻿#include <luiconf.h>
#include <style/ui_style.h>
#include <util/ui_unimacro.h>
#include <core/ui_color_list.h>
#include <core/ui_control_state.h>
#include <debugger/ui_debug.h>
#include <algorithm>

// longui::impl
namespace LongUI { namespace impl {
    // popuppos string table - rev
    static const uint32_t rev_popuppos_table[] = {
        0xc530a392,     // after_pointer
        0x4d659161,     // at_pointer
        0x44b850f3,     // overlap
        0xd1e17258,     // end_after
        0x4e76786f,     // end_before
        0xc51d7557,     // start_after
        0xc62c00ec,     // start_before
        0x0c26f0e8,     // after_end
        0x94f86be7,     // after_start
        0xe29e56cf,     // before_end
        0x5ed67606,     // before_start
    };
} }

/// <summary>
/// Initializes a new instance of the <see cref="Box"/> struct.
/// </summary>
void LongUI::Box::Init() noexcept {
    pos = {};
    size = {};
    visible = {};
    border = {};
    margin = {};
    padding = {};
}

#if 0
PCN_NOINLINE
/// <summary>
/// Gets the non contect.
/// </summary>
/// <param name="rect">The rect.</param>
/// <returns></returns>
void LongUI::Box::GetNonContect(RectF& rect) const noexcept {
    const auto pt = this->GetContentPos();
    rect.left = pt.x; rect.top = pt.y;
    rect.right = margin.right + border.right + padding.right;
    rect.bottom = margin.bottom + border.bottom + padding.bottom;
}
#endif

PCN_NOINLINE
/// <summary>
/// Gets the margin rect.
/// </summary>
/// <param name="rect">The rect.</param>
/// <returns></returns>
void LongUI::Box::GetMarginEdge(RectF& rect) const noexcept {
    rect.top = 0.0f;
    rect.left = 0.0f;
    rect.right = 0.0f + this->size.width;
    rect.bottom = 0.0f + this->size.height;
}


PCN_NOINLINE
/// <summary>
/// Gets the border rect.
/// </summary>
/// <param name="">The .</param>
/// <returns></returns>
void LongUI::Box::GetBorderEdge(RectF& rect) const noexcept {
    this->GetMarginEdge(rect);
    rect.top += this->margin.top;
    rect.left += this->margin.left;
    rect.right -= this->margin.right;
    rect.bottom -= this->margin.bottom;
}

/// <summary>
/// Gets the safe border edge.
/// </summary>
/// <returns></returns>
auto LongUI::Box::GetSafeBorderEdge() const noexcept -> RectF {
    RectF rect;
    this->GetMarginEdge(rect);
    rect.top += this->margin.top * 0.5f;
    rect.left += this->margin.left * 0.5f;
    rect.right -= this->margin.right * 0.5f;
    rect.bottom -= this->margin.bottom * 0.5f;
    return rect;
}

PCN_NOINLINE
/// <summary>
/// Gets the padding rect.
/// </summary>
/// <param name="rect">The rect.</param>
/// <returns></returns>
void LongUI::Box::GetPaddingEdge(RectF& rect) const noexcept {
    this->GetBorderEdge(rect);
    rect.top += this->border.top;
    rect.left += this->border.left;
    rect.right -= this->border.right;
    rect.bottom -= this->border.bottom;
}

PCN_NOINLINE
/// <summary>
/// Gets the content rect.
/// </summary>
/// <param name="rect">The rect.</param>
/// <returns></returns>
void LongUI::Box::GetContentEdge(RectF& rect) const noexcept {
    this->GetPaddingEdge(rect);
    rect.top += this->padding.top;
    rect.left += this->padding.left;
    rect.right -= this->padding.right;
    rect.bottom -= this->padding.bottom;
}

/// <summary>
/// Gets the size of the content.
/// </summary>
/// <returns></returns>
auto LongUI::Box::GetContentSize() const noexcept -> Size2F {
    const auto nonc = GetNonContentSize();
    return{ size.width - nonc.width, size.height - nonc.height };
}

PCN_NOINLINE
/// <summary>
/// get non-content size
/// </summary>
/// <returns></returns>
auto LongUI::Box::GetNonContentSize() const noexcept -> Size2F {
    Size2F size;
    size.width = margin.left + border.left + padding.left;
    size.width += margin.right + border.right + padding.right;
    size.height = margin.top + border.top + padding.top;
    size.height += margin.bottom + border.bottom + padding.bottom;
    return size;
}

PCN_NOINLINE
/// <summary>
/// Gets the size of the border.
/// </summary>
/// <returns></returns>
auto LongUI::Box::GetBorderSize() const noexcept -> Size2F {
    RectF rect; this->GetBorderEdge(rect);
    return{ rect.right - rect.left, rect.bottom - rect.top };
}

/// <summary>
/// Gets the content position.
/// </summary>
/// <returns></returns>
auto LongUI::Box::GetContentPos() const noexcept -> Point2F {
    Point2F pt;
    pt.x = margin.left + border.left + padding.left;
    pt.y = margin.top + border.top + padding.top;
    return pt; 
}


/// <summary>
/// Initializes this instance.
/// </summary>
/// <returns></returns>
LongUI::Style::Style() noexcept {
    //constexpr auto a = sizeof(Style);
    state = State_Non;
    inherited = State_Disabled;
    pack = Pack_Start;
    tduration = 0;
    accesskey = 0;
    extra_abcount = 0;
    align = Align_Stretcht;
    appearance = AttributeAppearance::Appearance_None;
    offset_tf = 0;
    overflow_xex = Overflow_Visible;
    overflow_y = Overflow_Visible;
    tfunction = 0;
    flex = 0;
    limited = { };
    fitting = { };
    maxsize = { DEFAULT_CONTROL_MAX_SIZE, DEFAULT_CONTROL_MAX_SIZE };
}

/// <summary>
/// Finalizes an instance of the <see cref="Style"/> class.
/// </summary>
/// <returns></returns>
LongUI::Style::~Style() noexcept {

}



// ----------------------------------------------------------------------------


/// <summary>
/// Boxes the specified .
/// </summary>
/// <param name="view">The view.</param>
/// <returns></returns>
auto LongUI::AttrParser::Box(U8View view) noexcept -> AttributeBox {
    switch (view[0])
    {
    default: return Box_BorderBox;
    case 'p': return Box_PaddingBox;
    case 'c': return Box_ContentBox;
    case 'm': return Box_MarginBox;
    }
}

/// <summary>
/// resize
/// </summary>
/// <param name=""></param>
/// <returns></returns>
auto LongUI::AttrParser::Resize(U8View view) noexcept -> AttributeResize {
    switch (view[0])
    {
    case 'c': return Resize_Closest;
    case 'g': return Resize_Grow;
    default: return view[1] == 'a' ?
        Resize_Farthest : Resize_Flex;
    }
}

/// <summary>
/// resize
/// </summary>
/// <param name=""></param>
/// <returns></returns>
auto LongUI::AttrParser::Collapse(U8View view) noexcept -> AttributeCollapse {
    switch (view[0])
    {
    case 'a': return Resizea_After;
    case 'n': return Resizea_None;
    default: return view[1] == 'e' ?
        Resizea_Before : Resizea_Both;
    }
}

/// <summary>
/// Aligns the specified view.
/// </summary>
/// <param name="view">The view.</param>
/// <returns></returns>
auto LongUI::AttrParser::Align(U8View view) noexcept -> AttributeAlign {
    switch (view[0])
    {
    case 'c': return Align_Center;
    case 'e': return Align_End;
    case 'b': return Align_Baseline;
    default: return view[2] == 'r' ?
        Align_Stretcht : Align_Start;
    }
}

/// <summary>
/// Packs the specified .
/// </summary>
/// <param name="view">The view.</param>
/// <returns></returns>
auto LongUI::AttrParser::Pack(U8View view) noexcept -> AttributePack {
    switch (view[0])
    {
    default: return Pack_Start;
    case 'c': return Pack_Center;
    case 'e': return Pack_End;
    }
}

/// <summary>
/// string view to crop enum
/// </summary>
/// <param name="view">the string view.</param>
/// <returns></returns>
auto LongUI::AttrParser::Crop(U8View view) noexcept -> AttributeCrop {
    switch (view[0])
    {
    default: return Crop_None;
    case 's': return Crop_Start;
    case 'c': return Crop_Center;
    case 'e': return Crop_End;
    }
}

/// <summary>
/// Seltypes the specified .
/// </summary>
/// <param name="">The .</param>
/// <returns></returns>
auto LongUI::AttrParser::Seltype(U8View view) noexcept -> AttributeSeltype {
    switch (view[0])
    {
    default: return Seltype_Single;
    case 'm': return Seltype_Multiple;
    case 'c': return Seltype_Cell;
    case 't': return Seltype_Text;
    }
}

/// <summary>
/// Overflows the specified .
/// </summary>
/// <param name="view">The view.</param>
/// <returns></returns>
auto LongUI::AttrParser::Overflow(U8View view) noexcept -> AttributeOverflow {
    switch (view[0])
    {
    default: return Overflow_Visible;
    case 'a': return Overflow_Auto;
    case 'h': return Overflow_Hidden;
    case 's': return Overflow_Scroll;
    }
}

/// <summary>
/// Appearances the specified view.
/// </summary>
/// <param name="view">The view.</param>
/// <returns></returns>
auto LongUI::AttrParser::Appearance(U8View view) noexcept -> AttributeAppearance {
    view[0];
    // TODO: NOTIMPL
    return Appearance_None;
}


/// <summary>
/// get <seealso cref="PopupPosition"/> from string
/// </summary>
/// <param name="view"></param>
/// <returns></returns>
auto LongUI::AttrParser::PopupPosition(U8View view) noexcept -> AttributePopupPosition {
    const auto code = LongUI::BKDRHash(view.first, view.second);
    const auto bgein = std::begin(impl::rev_popuppos_table);
    const auto end = std::end(impl::rev_popuppos_table);
    const auto itr = std::find(bgein, end, code);
#ifndef NDEBUG
    if (itr == end) LUIDebug(Warning) << view << " not found" << end;
#endif 
    return static_cast<AttributePopupPosition>(end - itr);
}



// longui
namespace LongUI {
    // repeat data
    const uint32_t REPEAT_DATA[] = {
        0xfcef1f9f_ui32,    // repeat
        0xf1c473aa_ui32,    // space
        0xe019b212_ui32,    // round
        0x4adeb4b7_ui32,    // no-repeat
        0x79aed116_ui32,    // repeat-x
        0x79aed117_ui32,    // repeat-y
    };
    // stretch data
    const uint32_t STRETCH_DATA[] = {
        0xddf0e19a_ui32,    // ultra-condensed
        0xa41e35ee_ui32,    // extra-condensed
        0x56fd39df_ui32,    // condensed
        0xed2dab54_ui32,    // semi-condensed
        0xbeadc473_ui32,    // normal
        0x50e559e8_ui32,    // semi-expanded
        0x8e48a541_ui32,    // expanded
        0x3ad78dc6_ui32,    // extra-expanded
        0x75e8cbaa_ui32,    // ultra-expanded
    };
    PCN_NOINLINE
    /// <summary>
    /// Uint32s the index of the find.
    /// </summary>
    /// <param name="list">The list.</param>
    /// <param name="len">The length.</param>
    /// <param name="code">The code.</param>
    /// <returns></returns>
    auto Uint32FindIndex(const uint32_t list[], uint32_t len, uint32_t code) noexcept -> uint32_t {
        uint32_t index = 0;
        for (; index != len; ++index) {
            if (list[index] == code) break;
        }
        return index;
    }
}

/// <summary>
/// Repeats the specified v1.
/// </summary>
/// <param name="v1">The v1.</param>
/// <param name="v2">The v2.</param>
/// <returns></returns>
auto LongUI::AttrParser::Repeat2(U8View v1, U8View v2) noexcept -> AttributeRepeat {
    assert(v1.end() > v1.begin());
    /*
        repeat-x    :repeat     no-repeat
        repeat-y    :no-repeat  repeat
        repeat      :repeat     repeat
        space       :space      space
        round       :round      round
        no-repeat   :no-repeat  no-repeat

        stretch
    */
    const auto hash1 = LongUI::BKDRHash(v1.begin(), v1.end());
    // stretch
    const auto index = hash1 == 0x02f093f5 ? Repeat_Stretch 
        : LongUI::Uint32FindIndex(
        LongUI::REPEAT_DATA, 
        sizeof(REPEAT_DATA) / sizeof(REPEAT_DATA[0]),
        hash1
    );
    // 1 for 2
    if (index > Repeat_NoRepeat) {
        // repeat-x
        if (index == Repeat_NoRepeat + 1) return Repeat_RepeatXOnly;
        // repeat-y
        else return Repeat_RepeatYOnly;
    }
    // y-repeat
    const auto hash2 = LongUI::BKDRHash(v2.begin(), v2.end());
    // stretch->no-repeat
    const auto index2 = hash2 == 0x02f093f5 ? Repeat_Stretch
        : LongUI::Uint32FindIndex(
            LongUI::REPEAT_DATA,
            sizeof(REPEAT_DATA) / sizeof(REPEAT_DATA[0]),
            hash2
        );
    return static_cast<AttributeRepeat>(index | (index2 << 4));
}




#include <text/ui_attribute.h>

/// <summary>
/// Fonts the style.
/// </summary>
/// <param name="view">The view.</param>
/// <returns></returns>
auto LongUI::TFAttrParser::Style(U8View view) noexcept->AttributeFontStyle {
    switch (view[0])
    {
    default: return Style_Normal;
    case 'o': return Style_Oblique;
    case 'i': return Style_Italic;
    }
}

/// <summary>
/// Weights the specified view.
/// </summary>
/// <param name="view">The view.</param>
/// <returns></returns>
auto LongUI::TFAttrParser::Weight(U8View view)noexcept->AttributeFontWeight {
    switch (const auto ch = view[0])
    {
    default: 
        if (ch >= '0' && ch <= '9') {
            const auto v = view.ToInt32();
            return static_cast<AttributeFontWeight>(v);
        }
        [[fallthrough]];
    case 'n': return Weight_Normal;
    case 'l': return Weight_Light;
    case 'b': return Weight_Bold;
    }
    return Weight_Normal;
}

/// <summary>
/// Texts the align.
/// </summary>
/// <param name="view">The view.</param>
/// <returns></returns>
auto LongUI::TFAttrParser::TextAlign(U8View view) noexcept -> AttributeTextAlign {
    switch (view[0])
    {
    default: return TAlign_Start;
    case 'r': return TAlign_Right;
    case 'e': return TAlign_End;
    case 'c': return TAlign_Center;
    case 'j': return TAlign_Justified;
    }
}

/// <summary>
/// Stretches the specified view.
/// </summary>
/// <param name="view">The view.</param>
/// <returns></returns>
auto LongUI::TFAttrParser::Stretch(U8View view)noexcept->AttributeFontStretch {
    /*
        ultra-condensed 50%
        extra-condensed 62.5%
        condensed       75%
        semi-condensed  87.5%
        normal          100%
        semi-expanded   112.5%
        expanded        125%
        extra-expanded  150%
        ultra-expanded  200%
    */
    const auto hash = LongUI::BKDRHash(view.begin(), view.end());
    const auto index = LongUI::Uint32FindIndex(
        LongUI::STRETCH_DATA,
        sizeof(STRETCH_DATA) / sizeof(STRETCH_DATA[0]),
        hash
    );
    // 没有找到
    if (index == sizeof(STRETCH_DATA) / sizeof(STRETCH_DATA[0])) {
        --view.second;
        // 百分比
        if (*view.second == '%') {
            // FIXME: 和映射表一致{50~150->50~200}
            constexpr float step = 12.5f;
            const auto persent = view.ToFloat();
            auto rv = int8_t(int(persent / step) - 3);
            if (rv < 0) rv = 0;
            else if (rv > Stretch_UltraExpanded) rv = Stretch_UltraExpanded;
            return static_cast<AttributeFontStretch>(rv);
        }
        return Stretch_Normal;
    }
    return static_cast<AttributeFontStretch>(index + 1);
}

