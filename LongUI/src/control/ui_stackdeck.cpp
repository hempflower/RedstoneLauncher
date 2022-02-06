﻿#include <control/ui_deck.h>
#include <control/ui_stack.h>
#include <core/ui_ctrlmeta.h>
#include <debugger/ui_debug.h>

#include <algorithm>
#include <cassert>

// ui namespace
namespace LongUI {
    // UIDeck类 元信息
    LUI_CONTROL_META_INFO(UIDeck, "deck");
    // UIStack类 元信息
    LUI_CONTROL_META_INFO(UIStack, "stack");
    // impl namespace
    namespace impl {
        // find greatest child-minsize/ right-buttom
        auto greatest_fitting_rb(UIControl& ctrl) noexcept {
            Size2F size = { 0.f, 0.f };
            for (auto& child : ctrl) {
                const auto pos = child.GetPos();
                const auto thism = child.GetBoxFittingSize();
                const Size2F rb{ pos.x + thism.width, pos.y + thism.height };
                size.width = std::max(size.width, rb.width);
                size.height = std::max(size.height, rb.height);
            }
            return size;
        }
    }
}

// ----------------------------------------------------------------------------
// --------------------              Deck             -------------------------
// ----------------------------------------------------------------------------


/// <summary>
/// Finalizes an instance of the <see cref="UIDeck"/> class.
/// </summary>
/// <returns></returns>
LongUI::UIDeck::~UIDeck() noexcept {
}


/// <summary>
/// Initializes a new instance of the <see cref="UIDeck"/> class.
/// </summary>
/// <param name="meta">The meta.</param>
LongUI::UIDeck::UIDeck(const MetaControl& meta) noexcept : Super(meta) {
}

/// <summary>
/// Updates this instance.
/// </summary>
/// <returns></returns>
void LongUI::UIDeck::Update(UpdateReason reason) noexcept {
    // 有变数
    if (reason & Reason_ChildIndexChanged) {
        uint32_t index = 0;
        for (auto& child : (*this)) {
            child.SetVisible(index == m_index);
            ++index;
        }
    }
    // 超类处理
    return Super::Update(reason);
}

/// <summary>
/// add attribute to UIDeck
/// </summary>
/// <param name="key"></param>
/// <param name="value"></param>
/// <returns></returns>
void LongUI::UIDeck::add_attribute(uint32_t key, U8View value) noexcept {
    constexpr auto SELINDEX             = 0x0a92fd4b_ui32;
    switch (key)
    {
    case SELINDEX:
        // selectedIndex  初始值
        m_index = value.ToInt32();
        return;
    }
    // 超类处理
    Super::add_attribute(key, value);
}

/// <summary>
/// Sets the index of the selected.
/// </summary>
/// <param name="index">The index.</param>
/// <returns></returns>
void LongUI::UIDeck::SetSelectedIndex(uint32_t index) noexcept {
    if (index >= this->GetChildrenCount()) return;
    if (m_index != index) {
        this->Invalidate();
        const auto newitem = this->cal_index_child<UIControl>(index);
        const auto olditem = this->cal_index_child<UIControl>(m_index);
        assert(newitem && "404");
        if (olditem) olditem->SetVisible(false);
        newitem->SetVisible(true);
        m_index = index;
    }
}

/// <summary>
/// Ons the index changed.
/// </summary>
/// <returns></returns>
void LongUI::UIDeck::on_index_changed() noexcept {
    // TODO: index changed event;
    //this->FireEvent(_selectedChanged());
}

// ----------------------------------------------------------------------------
// --------------------             Stack             -------------------------
// ----------------------------------------------------------------------------


/// <summary>
/// Finalizes an instance of the <see cref="UIStack"/> class.
/// </summary>
/// <returns></returns>
LongUI::UIStack::~UIStack() noexcept {

}


/// <summary>
/// Initializes a new instance of the <see cref="UIStack"/> class.
/// </summary>
/// <param name="meta">The meta.</param>
LongUI::UIStack::UIStack(const MetaControl& meta) noexcept : Super(meta) {

}

/// <summary>
/// Updates this instance.
/// </summary>
/// <returns></returns>
void LongUI::UIStack::Update(UpdateReason reason) noexcept {
    // 要求重新计算
    if (reason & Reason_BasicUpdateFitting)
        this->refresh_fitting();
    // 要求重新布局
    if (reason & (Reason_BasicRelayout & ~Reason_ChildLayoutChanged))
        this->relayout_stack();
    // 其他的交给超类处理
    Super::Update(reason);
}


/// <summary>
/// refresh fitting size
/// </summary>
/// <returns></returns>
void LongUI::UIStack::refresh_fitting() noexcept {
    const auto fitting = impl::greatest_fitting_rb(*this);
    this->set_limited_width_lp(fitting.width);
    this->set_limited_width_lp(fitting.height);
    this->update_fitting_size(fitting);
}

/// <summary>
/// Relayouts the stack.
/// </summary>
/// <returns></returns>
void LongUI::UIStack::relayout_stack() noexcept {
    for (auto& child : (*this)) 
        this->resize_child(child, child.GetBoxFittingSize());
}

