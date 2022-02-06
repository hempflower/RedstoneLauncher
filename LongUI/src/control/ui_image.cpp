﻿// ui
#include <core/ui_ctrlmeta.h>
#include <core/ui_manager.h>
#include <control/ui_image.h>
#include <container/pod_hash.h>
#include <resource/ui_image_res.h>

// ui namespace
namespace LongUI {
    // UIImage类 元信息
    LUI_CONTROL_META_INFO(UIImage, "image");
}

/// <summary>
/// Initializes a new instance of the <see cref="UIImage" /> class.
/// </summary>
/// <param name="parent">The parent.</param>
/// <param name="meta">The meta.</param>
LongUI::UIImage::UIImage(const MetaControl& meta) noexcept: Super(meta) {

}


/// <summary>
/// Finalizes an instance of the <see cref="UIImage"/> class.
/// </summary>
/// <returns></returns>
LongUI::UIImage::~UIImage() noexcept {
}


/// <summary>
/// Adds the attribute.
/// </summary>
/// <param name="key">The key.</param>
/// <param name="value">The value.</param>
/// <returns></returns>
void LongUI::UIImage::add_attribute(uint32_t key, U8View value) noexcept {
    // 本控件添加属性
    constexpr auto BKDR_SRC = 0x001E57C4_ui32;
    // 计算HASH
    switch (key)
    {
    case BKDR_SRC:
        // src  : 图像源
        this->SetSource(value);
        break;
    default:
        // 其他情况, 交给超类处理
        return Super::add_attribute(key, value);
    }
}

/// <summary>
/// Sets the source.
/// </summary>
/// <param name="src">The source.</param>
void LongUI::UIImage::SetSource(U8View src) noexcept {
    constexpr auto RESTYPE = ResourceType::Type_Image;
    const auto id = UIManager.LoadResource(src, /*RESTYPE,*/ true);
#ifndef NDEBUG
    if (!id && src.end() != src.begin()) {
        LUIDebug(Error) LUI_FRAMEID
            << "Resource [not found][create failed]: "
            << src
            << endl;
    }
#endif
    // 重置数据
    if (id != m_idSrc.GetId()) {
        m_idSrc.SetId(id);
        m_idFrame = 0;
        m_uFrameCount = 1;
        Size2F fitting = { 0 };
        // 有效图片
        if (id) {
            auto& res = m_idSrc.RefResource();
            auto& img = static_cast<CUIImage&>(res);
            // 更新建议值
            fitting = img.size;
            // 计算帧动画
            m_uFrameCount = img.frame_count;
            if (m_uFrameCount > 1) this->SetTimer(img.delay, 0);
        }
        this->update_fitting_size(fitting);
        this->NeedUpdate(Reason_SizeChanged);
        this->Invalidate();
    }
}

/// <summary>
/// Does the event.
/// </summary>
/// <param name="e">The e.</param>
/// <returns></returns>
auto LongUI::UIImage::DoEvent(UIControl* sender, const EventArg& e) noexcept -> EventAccept {
    switch (e.nevent)
    {
    case LongUI::NoticeEvent::Event_Timer0:
        // TIMER#0 作为帧动画使用
        if (m_uFrameCount < 2) return Event_Ignore;
        m_idFrame = (m_idFrame + 1) % m_uFrameCount;
        this->Invalidate();
        return Event_Accept;
    }
    return Super::DoEvent(sender, e);
}

/// <summary>
/// Renders this instance.
/// </summary>
/// <returns></returns>
void LongUI::UIImage::Render() const noexcept {
    // 渲染背景
    Super::Render();
    // 图像有效
    if (m_idSrc.GetId()) {
        // 将目标画在内容区
        auto des_rect = this->RefBox().GetContentEdge();
        // 居中显示
#if 0
        if (m_bAsIcon) {
            const auto usize = m_pSharedSrc->GetSize();
            const auto src_w = static_cast<float>(usize.width);
            const auto src_h = static_cast<float>(usize.height);
            const auto des_w = des_rect.right - des_rect.left;
            const auto des_h = des_rect.bottom - des_rect.top;

            const auto target_h = des_w / src_w * src_h;
            // [target_w, des_h]
            if (target_h > des_h) {
                const auto target_w = des_h / src_h * src_w;
                const auto half = (des_w - target_w) * 0.5f;
                des_rect.left += half;
                des_rect.right -= half;
            }
            // [des_w, target_h]
            else {
                const auto half = (des_h - target_h) * 0.5f;
                des_rect.top += half;
                des_rect.bottom -= half;
            }
        }
#endif
        auto& res = m_idSrc.RefResource();
        auto& img = static_cast<const CUIImage&>(res);
        assert(res.RefData().GetType() == ResourceType::Type_Image);
        img.Render(m_idFrame, UIManager.Ref2DRenderer(), &des_rect);
    }
}

