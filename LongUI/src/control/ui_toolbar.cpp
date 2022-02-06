﻿// Gui
#include <core/ui_ctrlmeta.h>
#include <control/ui_toolbar.h>
#include <control/ui_toolbarbutton.h>
// Private
#include "../private/ui_private_control.h"


// ui namespace
namespace LongUI {
    // UIToolBar类 元信息
    LUI_CONTROL_META_INFO(UIToolBar, "toolbar");
    // UIToolBarButton类 元信息
    LUI_CONTROL_META_INFO(UIToolBarButton, "toolbarbutton");
}


// ----------------------------- UIToolBar





/// <summary>
/// Finalizes an instance of the <see cref="UIToolBar"/> class.
/// </summary>
/// <returns></returns>
LongUI::UIToolBar::~UIToolBar() noexcept {
}

/// <summary>
/// Initializes a new instance of the <see cref="UIToolBar"/> class.
/// </summary>
/// <param name="meta">The meta.</param>
LongUI::UIToolBar::UIToolBar(const MetaControl& meta) noexcept :Super(meta) {
    // 居中对齐
    m_oStyle.align = Align_Center;
}





// ----------------------------- UIToolBarButton




/// <summary>
/// Finalizes an instance of the <see cref="UIToolBarButton"/> class.
/// </summary>
/// <returns></returns>
LongUI::UIToolBarButton::~UIToolBarButton() noexcept {

}

/// <summary>
/// Initializes a new instance of the <see cref="UIToolBarButton"/> class.
/// </summary>
/// <param name="meta">The meta.</param>
LongUI::UIToolBarButton::UIToolBarButton(const MetaControl& meta) noexcept : Super(meta) {
    m_bToolBar = true;
    // 弱外貌
    m_oStyle.appearance = Appearance_ToolBarButton;
}

