﻿#include <luiconf.h>
#include <style/ui_text.h>
#include <style/ui_style_value.h>
#include <core/ui_color_list.h>
#include <event/ui_indirecttf_event.h>
#include <graphics/ui_bg_renderer.h>
#include <graphics/ui_bd_renderer.h>
#include "../private/ui_private_control.h"

#include <core/ui_manager.h>
#include <text/ui_ctl_arg.h>

//#undef PCN_NOINLINE
//#define PCN_NOINLINE

// longui::detail
namespace LongUI { namespace impl {
    // get text font
    auto get_text_font(UIControl& ctrl) noexcept->TextFont*;
    // get text font
    auto get_text_font(const UIControl& ctrl) noexcept->const TextFont*{
        return get_text_font(const_cast<UIControl&>(ctrl));
    }
    // mark tf display changed
    inline void mark_td_display_changed(UIControl& ctrl) noexcept {
        // 标记文本显示属性修改
        ctrl.NeedUpdate(Reason_TextFontDisplayChanged);
    }
    // mark tf layout changed
    inline void mark_td_layout_changed(UIControl& ctrl) noexcept {
        // 标记文本显示属性修改
        ctrl.NeedUpdate(Reason_TextFontLayoutChanged);
    }
}}

PCN_NOINLINE
/// <summary>
/// Sets the color of the fg.
/// </summary>
/// <param name="color">The color.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetFgColor(RGBA color) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
#ifndef NDEBUG
    if (color.primitive == this->GetFgColor().primitive) {
        LUIDebug(Hint) << ctrl << "set same color" << endl;
    }
#endif // !NDEBUG
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        ColorF::FromRGBA_RT(tf->text.color, color);
        impl::mark_td_display_changed(*ctrl);
    }
}

PCN_NOINLINE
/// <summary>
/// Gets the color of the fg.
/// </summary>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetFgColor() const noexcept -> RGBA {
    const auto ctrl = static_cast<const UIControl*>(this);
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        return tf->text.color.ToRGBA();
    }
    return { RGBA_Black };
}

PCN_NOINLINE
/// <summary>
/// Sets the text align.
/// </summary>
/// <param name="talign">The talign.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetTextAlign(AttributeTextAlign talign) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        tf->text.alignment = talign;
        // 标记文本布局属性修改
        impl::mark_td_layout_changed(*ctrl);
    }
}

PCN_NOINLINE
/// <summary>
/// Gets the text align.
/// </summary>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetTextAlign()const noexcept->AttributeTextAlign {
    const auto ctrl = static_cast<const UIControl*>(this);
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        return tf->text.alignment;
    }
    return TAlign_Start;
}

#ifndef LUI_DISABLE_STYLE_SUPPORT
PCN_NOINLINE
/// <summary>
/// Sets the color of the text stroke.
/// </summary>
/// <param name="color">The color.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetTextStrokeColor(RGBA color) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
#ifndef NDEBUG
    if (color.primitive == this->GetTextStrokeColor().primitive) {
        LUIDebug(Hint) << ctrl << "set same color" << endl;
    }
#endif // !NDEBUG
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        ColorF::FromRGBA_RT(tf->text.stroke_color, color);
        // 标记文本显示属性修改
        impl::mark_td_display_changed(*ctrl);
    }
}

PCN_NOINLINE
/// <summary>
/// Sets the width of the text stroke.
/// </summary>
/// <param name="width">The width.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetTextStrokeWidth(float width) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        tf->text.stroke_width = width;
        // 标记文本显示属性修改
        impl::mark_td_display_changed(*ctrl);
    }
}

PCN_NOINLINE
/// <summary>
/// Sets the color of the bg.
/// </summary>
/// <param name="color">The color.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetBgColor(RGBA color) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    if (auto r = UIControlPrivate::EnsureBgRenderer(*ctrl)) {
        ColorF::FromRGBA_RT(r->color, color);
        ctrl->Invalidate();
    }
}

PCN_NOINLINE
/// <summary>
/// Gets the color of the bg.
/// </summary>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetBgColor() const noexcept -> RGBA {
    const auto ctrl = static_cast<const UIControl*>(this);
    if (auto r = UIControlPrivate::GetBgRenderer(*ctrl)) {
        return r->color.ToRGBA();
    }
    return { RGBA_Transparent };
}

PCN_NOINLINE
/// <summary>
/// Gets the color of the text stroke.
/// </summary>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetTextStrokeColor() const noexcept->RGBA {
    const auto ctrl = static_cast<const UIControl*>(this);
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        return tf->text.stroke_color.ToRGBA();
    }
    return { RGBA_Transparent };
}

PCN_NOINLINE
/// <summary>
/// Gets the width of the text stroke.
/// </summary>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetTextStrokeWidth() const noexcept -> float {
    const auto ctrl = static_cast<const UIControl*>(this);
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        return tf->text.stroke_width;
    }
    return 0.0f;
}




PCN_NOINLINE
/// <summary>
/// Sets the bg image.
/// </summary>
/// <param name="id">The identifier.</param>
/// <remarks>
/// won't change ref-count inside, you should do it out side
/// </remarks>
/// <returns></returns>
void LongUI::CUIStyleValue::SetBgImageID(uintptr_t id) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    if (auto r = UIControlPrivate::EnsureBgRenderer(*ctrl)) {
        r->SetImageId(id);
        ctrl->Invalidate();
    }
}


PCN_NOINLINE
/// <summary>
/// Gets the bg image.
/// </summary>
/// <remarks>
/// won't change ref-count inside, you should do it out side
/// </remarks>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetBgImageID() const noexcept -> uintptr_t {
    const auto ctrl = static_cast<const UIControl*>(this);
    if (auto r = UIControlPrivate::GetBgRenderer(*ctrl)) {
        return r->GetImageId();
    }
    return 0;
}

PCN_NOINLINE
/// <summary>
/// Gets the bg repeat.
/// </summary>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetBgRepeat() const noexcept -> AttributeRepeat {
    const auto ctrl = static_cast<const UIControl*>(this);
    if (auto r = UIControlPrivate::GetBgRenderer(*ctrl)) {
        return r->repeat;
    }
    return Repeat_Repeat;
}

PCN_NOINLINE
/// <summary>
/// Sets the bg clip.
/// </summary>
/// <param name="clip">The clip.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetBgClip(AttributeBox clip) noexcept {
    assert(clip < AttributeBox::BOX_COUNT && "out of range");
    const auto ctrl = static_cast<UIControl*>(this);
    if (auto r = UIControlPrivate::EnsureBgRenderer(*ctrl)) {
        r->clip = clip;
        ctrl->Invalidate();
    }
}

PCN_NOINLINE
/// <summary>
/// Gets the bg clip.
/// </summary>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetBgClip() const noexcept->AttributeBox {
    const auto ctrl = static_cast<const UIControl*>(this);
    if (auto r = UIControlPrivate::GetBgRenderer(*ctrl)) {
        return r->clip;
    }
    return Box_BorderBox;
}


PCN_NOINLINE
/// <summary>
/// Sets the bg origin.
/// </summary>
/// <param name="ar">The ar.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetBgOrigin(AttributeBox ab) noexcept {
    assert(ab < AttributeBox::BOX_COUNT && "out of range");
    const auto ctrl = static_cast<UIControl*>(this);
    if (auto r = UIControlPrivate::EnsureBgRenderer(*ctrl)) {
        r->origin = ab;
        ctrl->Invalidate();
    }
}

PCN_NOINLINE
/// <summary>
/// Gets the bg origin.
/// </summary>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetBgOrigin() const noexcept->AttributeBox {
    const auto ctrl = static_cast<const UIControl*>(this);
    if (auto r = UIControlPrivate::GetBgRenderer(*ctrl)) {
        return r->origin;
    }
    return Box_BorderBox;
}


PCN_NOINLINE
/// <summary>
/// Sets the bd radius.
/// </summary>
/// <param name="radius">The radius.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetBdRadius(Size2F radius) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    if (auto r = UIControlPrivate::EnsureBdRenderer(*ctrl)) {
        r->radius_x = radius.width;
        r->radius_y = radius.height;
        ctrl->Invalidate();
    }
}

PCN_NOINLINE
/// <summary>
/// Sets the color of the bd.
/// </summary>
/// <param name="radius">The radius.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetBdColor(RGBA color) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    if (auto r = UIControlPrivate::EnsureBdRenderer(*ctrl)) {
        ColorF::FromRGBA_RT(r->color, color);
        ctrl->Invalidate();
    }
}

PCN_NOINLINE
/// <summary>
/// Gets the bd style.
/// </summary>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetBdStyle() const noexcept->AttributeBStyle {
    const auto ctrl = static_cast<const UIControl*>(this);
    if (auto r = UIControlPrivate::GetBdRenderer(*ctrl)) {
        return r->style;
    }
    return Style_None;
}


PCN_NOINLINE
/// <summary>
/// Gets the color of the bd.
/// </summary>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetBdColor() const noexcept -> RGBA{
    const auto ctrl = static_cast<const UIControl*>(this);
    if (auto r = UIControlPrivate::GetBdRenderer(*ctrl)) {
        return r->color.ToRGBA();
    }
    return { RGBA_Transparent };
}


PCN_NOINLINE
/// <summary>
/// Gets the bd radius.
/// </summary>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetBdRadius() const noexcept -> Size2F{
    const auto ctrl = static_cast<const UIControl*>(this);
    if (auto r = UIControlPrivate::GetBdRenderer(*ctrl)) {
        return { r->radius_x, r->radius_y };
    }
    return {};
}


PCN_NOINLINE
/// <summary>
/// Sets the bd style.
/// </summary>
/// <param name="style">The style.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetBdStyle(AttributeBStyle style) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    if (auto r = UIControlPrivate::EnsureBdRenderer(*ctrl)) {
        r->style = style;
        ctrl->Invalidate();
    }
}


PCN_NOINLINE
/// <summary>
/// Sets the bd image source.
/// </summary>
/// <param name="id">The identifier.</param>
/// <remarks>
/// won't change ref-count inside, you should do it out side
/// </remarks>
/// <returns></returns>
void LongUI::CUIStyleValue::SetBdImageSourceID(uintptr_t id) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    if (auto r = UIControlPrivate::EnsureBdRenderer(*ctrl)) {
        r->SetImageId(id);
        ctrl->Invalidate();
    }
}

PCN_NOINLINE
/// <summary>
/// Sets the bd image slice.
/// </summary>
/// <param name="slice">The slice.</param>
/// <param name="fill">if set to <c>true</c> [fill].</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetBdImageSlice(const RectF& slice, bool fill) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    if (auto r = UIControlPrivate::EnsureBdRenderer(*ctrl)) {
        r->SetImageSlice(slice, fill);
        ctrl->Invalidate();
    }
}

PCN_NOINLINE
/// <summary>
/// Sets the bd image repeat.
/// </summary>
/// <param name="repeat">The repeat.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetBdImageRepeat(AttributeRepeat repeat) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    if (auto r = UIControlPrivate::EnsureBdRenderer(*ctrl)) {
        r->SetImageRepeat(repeat);
        ctrl->Invalidate();
    }
}

PCN_NOINLINE
/// <summary>
/// Gets the bd image source.
/// </summary>
/// <remarks>
/// won't change ref-count inside, you should do it out side
/// </remarks>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetBdImageSourceID() const noexcept -> uintptr_t {
    const auto ctrl = static_cast<const UIControl*>(this);
    if (auto r = UIControlPrivate::GetBdRenderer(*ctrl)) {
        return r->GetImageId();
    }
    return 0;
}

PCN_NOINLINE
/// <summary>
/// Gets the bd image slice.
/// </summary>
/// <param name="output">The output.</param>
/// <returns></returns>
bool LongUI::CUIStyleValue::GetBdImageSlice(RectF& output) const noexcept {
    const auto ctrl = static_cast<const UIControl*>(this);
    if (auto r = UIControlPrivate::GetBdRenderer(*ctrl)) {
        return r->GetImageSlice(output);
    }
    output = { };
    return false;
}

/// <summary>
/// Gets the bd image repeat.
/// </summary>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetBdImageRepeat() const noexcept -> AttributeRepeat {
    const auto ctrl = static_cast<const UIControl*>(this);
    if (auto r = UIControlPrivate::GetBdRenderer(*ctrl)) {
        return r->GetImageRepeat();
    }
    return Repeat_Repeat;
}

PCN_NOINLINE
/// <summary>
/// Sets the bg attachment.
/// </summary>
/// <param name="aa">The aa.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetBgAttachment(AttributeAttachment aa) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    if (auto r = UIControlPrivate::EnsureBgRenderer(*ctrl)) {
        r->attachment = aa;
        ctrl->Invalidate();
    }
}

PCN_NOINLINE
/// <summary>
/// Sets the bg repeat.
/// </summary>
/// <param name="ar">The ar.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetBgRepeat(AttributeRepeat ar) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    if (auto r = UIControlPrivate::EnsureBgRenderer(*ctrl)) {
        r->repeat = ar;
        ctrl->Invalidate();
    }
}


PCN_NOINLINE
/// <summary>
/// Sets the size of the font.
/// </summary>
/// <param name="size">The size.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetFontSize(float size) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        tf->font.size = size;
        // 标记文本布局属性修改
        impl::mark_td_layout_changed(*ctrl);
    }
}

PCN_NOINLINE
/// <summary>
/// Gets the size of the font.
/// </summary>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetFontSize() const noexcept->float {
    const auto ctrl = static_cast<const UIControl*>(this);
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        return tf->font.size;
    }
    return UIManager.RefDefaultFont().size;
}


PCN_NOINLINE
/// <summary>
/// Sets the font style.
/// </summary>
/// <param name="style">The style.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetFontStyle(AttributeFontStyle style) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        tf->font.style = style;
        // 标记文本布局属性修改
        impl::mark_td_layout_changed(*ctrl);
    }
}



PCN_NOINLINE
/// <summary>
/// Gets the font style.
/// </summary>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetFontStyle()const noexcept->AttributeFontStyle {
    const auto ctrl = static_cast<const UIControl*>(this);
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        return tf->font.style;
    }
    return UIManager.RefDefaultFont().style;
}

PCN_NOINLINE
/// <summary>
/// Sets the font family.
/// </summary>
/// <param name="family">The family.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetFontFamily(const char* family) noexcept {
    // 默认字体
    if (family == nullptr) 
        family = UIManager.RefDefaultFont().family;
    const auto ctrl = static_cast<UIControl*>(this);
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        tf->font.family = family;
        // 标记文本布局属性修改
        impl::mark_td_layout_changed(*ctrl);
    }
}

PCN_NOINLINE
/// <summary>
/// Gets the font style.
/// </summary>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetFontFamily()const noexcept->const char* {
    const auto ctrl = static_cast<const UIControl*>(this);
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        return tf->font.family;
    }
    return UIManager.RefDefaultFont().family;
}

PCN_NOINLINE
/// <summary>
/// Sets the font weight.
/// </summary>
/// <param name="style">The weight.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetFontWeight(AttributeFontWeight weight) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        tf->font.weight = weight;
        // 标记文本布局属性修改
        impl::mark_td_layout_changed(*ctrl);
    }
}

PCN_NOINLINE
/// <summary>
/// Gets the font weight.
/// </summary>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetFontWeight()const noexcept->AttributeFontWeight {
    const auto ctrl = static_cast<const UIControl*>(this);
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        return tf->font.weight;
    }
    return UIManager.RefDefaultFont().weight;
}

PCN_NOINLINE
/// <summary>
/// Sets the font stretch.
/// </summary>
/// <param name="style">The stretch.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetFontStretch(AttributeFontStretch stretch) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        tf->font.stretch = stretch;
        // 标记文本布局属性修改
        impl::mark_td_layout_changed(*ctrl);
    }
}

PCN_NOINLINE
/// <summary>
/// Gets the font stretch.
/// </summary>
/// <returns></returns>
auto LongUI::CUIStyleValue::GetFontStretch()const noexcept->AttributeFontStretch {
    const auto ctrl = static_cast<const UIControl*>(this);
    // 存在TF对象
    if (const auto tf = impl::get_text_font(*ctrl)) {
        return tf->font.stretch;
    }
    return UIManager.RefDefaultFont().stretch;
}

PCN_NOINLINE
/// <summary>
/// Afters the box changed.
/// </summary>
void LongUI::CUIStyleValue::after_box_changed() {
    const auto ctrl = static_cast<UIControl*>(this);
    //UIControlPrivate::MarkWindowMinsizeChanged(*ctrl);
    // XXX: 单独修改Box可能性很低, 内部重新布局
    ctrl->NeedUpdate(Reason_BoxChanged);
    if (const auto p = ctrl->GetParent()) 
        p->NeedUpdate(Reason_ChildLayoutChanged);
}

/// <summary>
/// Sets the margin top.
/// </summary>
/// <param name="value">The value.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetMarginTop(float value) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    auto& box = const_cast<Box&>(ctrl->RefBox());
    box.margin.top = value;
    this->after_box_changed();
}


/// <summary>
/// Sets the margin left.
/// </summary>
/// <param name="value">The value.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetMarginLeft(float value) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    auto& box = const_cast<Box&>(ctrl->RefBox());
    box.margin.left = value;
    this->after_box_changed();
}

/// <summary>
/// Sets the margin right.
/// </summary>
/// <param name="value">The value.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetMarginRight(float value) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    auto& box = const_cast<Box&>(ctrl->RefBox());
    box.margin.right = value;
    this->after_box_changed();
}

/// <summary>
/// Sets the margin bottom.
/// </summary>
/// <param name="value">The value.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetMarginBottom(float value) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    auto& box = const_cast<Box&>(ctrl->RefBox());
    box.margin.bottom = value;
    this->after_box_changed();
}

/// <summary>
/// Sets the padding top.
/// </summary>
/// <param name="value">The value.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetPaddingTop(float value) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    auto& box = const_cast<Box&>(ctrl->RefBox());
    box.padding.top = value;
    this->after_box_changed();
}

/// <summary>
/// Sets the padding left.
/// </summary>
/// <param name="value">The value.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetPaddingLeft(float value) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    auto& box = const_cast<Box&>(ctrl->RefBox());
    box.padding.left = value;
    this->after_box_changed();
}

/// <summary>
/// Sets the padding right.
/// </summary>
/// <param name="value">The value.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetPaddingRight(float value) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    auto& box = const_cast<Box&>(ctrl->RefBox());
    box.padding.right = value;
    this->after_box_changed();
}

/// <summary>
/// Sets the padding bottom.
/// </summary>
/// <param name="value">The value.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetPaddingBottom(float value) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    auto& box = const_cast<Box&>(ctrl->RefBox());
    box.padding.bottom = value;
    this->after_box_changed();
}

/// <summary>
/// Sets the border top.
/// </summary>
/// <param name="value">The value.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetBorderTop(float value) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    auto& box = const_cast<Box&>(ctrl->RefBox());
    box.border.top = value; 
    this->after_box_changed();
}

/// <summary>
/// Sets the border left.
/// </summary>
/// <param name="value">The value.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetBorderLeft(float value) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    auto& box = const_cast<Box&>(ctrl->RefBox());
    box.border.left = value;
    this->after_box_changed();
}

/// <summary>
/// Sets the border right.
/// </summary>
/// <param name="value">The value.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetBorderRight(float value) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    auto& box = const_cast<Box&>(ctrl->RefBox());
    box.border.right = value;
    this->after_box_changed();
}

/// <summary>
/// Sets the border bottom.
/// </summary>
/// <param name="value">The value.</param>
/// <returns></returns>
void LongUI::CUIStyleValue::SetBorderBottom(float value) noexcept {
    const auto ctrl = static_cast<UIControl*>(this);
    auto& box = const_cast<Box&>(ctrl->RefBox());
    box.border.bottom = value;
    this->after_box_changed();
}

#endif

// longui::detail
namespace LongUI { namespace impl {
    /// <summary>
    /// Gets the text font.
    /// </summary>
    /// <param name="ctrl">The control.</param>
    /// <returns></returns>
    auto get_text_font(UIControl& ctrl) noexcept->TextFont* {
        auto& style = ctrl.RefStyle();
        // 存在直接Text对象
        if (style.offset_tf) {
            // 没对齐
            if (style.offset_tf & 1) {
                // 查找间接Text对象
                IndirectTextFontGuiArg arg;
                ctrl.DoEvent(nullptr, arg);
#ifndef NDEBUG
                if (arg.text_font == nullptr) {
                    LUIDebug(Warning)
                        << "try to set" << ctrl
                        << "with text-font, but not found"
                        << endl;
                }
#endif // !NDEBUG
                return arg.text_font;
            }
            return const_cast<Style&>(style).GetTextFont();
        }
        return nullptr;
    }
}}
