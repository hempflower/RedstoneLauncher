﻿// Gui Core
#include <core/ui_window.h>
#include <core/ui_manager.h>
#include <core/ui_ctrlmeta.h>
#include <core/ui_popup_window.h>
//#include <debugger/ui_debug.h>
// Control
#include <control/ui_menu.h>
#include <control/ui_menubar.h>
#include <control/ui_menuitem.h>
#include <control/ui_menupopup.h>
// Private
#include "../private/ui_private_control.h"


// ui namespace
namespace LongUI {
    // UIMenuBar类 元信息
    LUI_CONTROL_META_INFO(UIMenuBar, "menubar");
    // UIMenu类 元信息
    LUI_CONTROL_META_INFO(UIMenu, "menu");
}


// ----------------------------- UIMenuBar


/// <summary>
/// Finalizes an instance of the <see cref="UIMenuBar"/> class.
/// </summary>
/// <returns></returns>
LongUI::UIMenuBar::~UIMenuBar() noexcept {

}

/// <summary>
/// Initializes a new instance of the <see cref="UIMenuBar"/> class.
/// </summary>
/// <param name="meta">The meta.</param>
LongUI::UIMenuBar::UIMenuBar(const MetaControl& meta) noexcept :Super(meta) {
    // 居中对齐
    m_oStyle.align = Align_Center;
}





// ----------------------------- UIMenu




/// <summary>
/// Finalizes an instance of the <see cref="UIMenu"/> class.
/// </summary>
/// <returns></returns>
LongUI::UIMenu::~UIMenu() noexcept {
}

/// <summary>
/// Initializes a new instance of the <see cref="UIMenu"/> class.
/// </summary>
/// <param name="meta">The meta.</param>
LongUI::UIMenu::UIMenu(const MetaControl& meta) noexcept : Super(meta) {
    m_bMenuBar = true;
    m_type = BehaviorType::Type_Menu;
    m_oStyle.appearance = Appearance_ToolBarButton;
}

/// <summary>
/// initialize UIMenu
/// </summary>
/// <returns></returns>
void LongUI::UIMenu::initialize() noexcept {
    // 父节点是MenuPopup?
    if (uisafe_cast<UIMenuPopup>(m_pParent)) {
        UIControlPrivate::SetAppearance(*this, Appearance_Menu);
        // !!! 初始化超类
        Super::initialize();
        if (const auto pMenuArrow = new(std::nothrow) UIControl{ this }) {
            UIControlPrivate::SetAppearance(*pMenuArrow, Appearance_MenuArrow);
        }
        this->set_label_flex(1);
        return;
    }
    // 初始化超类
    Super::initialize();
}

/// <summary>
/// Does the event.
/// </summary>
/// <param name="sender">The sender.</param>
/// <param name="e">The e.</param>
/// <returns></returns>
auto LongUI::UIMenu::DoEvent(UIControl* sender, const EventArg& e) noexcept -> EventAccept {
    // 初始化
    switch (e.nevent)
    {
    case NoticeEvent::Event_PopupBegin:
        // 弹出的是内建的菜单
        if (sender == m_pMenuPopup) {
            assert(m_pParent && "parent must be valid");
            // 父节点是UIMenuBar?
            if (const auto bar = uisafe_cast<UIMenuBar>(m_pParent)) {
                bar->SetNowMenu(*this);
            }
        }
        break;
    case NoticeEvent::Event_PopupEnd:
        // 关闭的是内建的菜单
        if (sender == m_pMenuPopup) {
            assert(m_pParent && "parent must be valid");
            // 父节点是UIMenuBar?
            if (const auto bar = uisafe_cast<UIMenuBar>(m_pParent)) {
                bar->ClearNowMenu();
            }
        }
        break;
    }
    // 超类处理
    return Super::DoEvent(sender, e);
}

/// <summary>
/// Does the mouse event.
/// </summary>
/// <param name="e">The e.</param>
/// <returns></returns>
auto LongUI::UIMenu::DoMouseEvent(const MouseEventArg& e) noexcept->EventAccept {
    switch (e.type)
    {
    case MouseEvent::Event_MouseEnter:
        // 鼠标移入而且菜单条处于激活模式
        assert(m_pParent && "parent must be vaild");
        // 父节点是UIMenuBar
        if (const auto bar = uisafe_cast<UIMenuBar>(m_pParent)) {
            if (bar->HasNowMenu(*this)) this->Click();
        }
        // 父节点是MenuPopup
        else if (const auto menu = longui_cast<UIMenuPopup*>(m_pParent)) {

        }
        break;
    case MouseEvent::Event_MouseLeave:
        if (m_bPopupShown && m_pMenuPopup) {
            if (const auto ptr = uisafe_cast<UIMenuPopup>(m_pParent)) {
                ptr->SetDelayClosedPopup();
            }
        }
        break;
    case MouseEvent::Event_MouseIdleHover:
        // 显示下一级
        if (m_pMenuPopup && uisafe_cast<UIMenuPopup>(m_pParent)) {
            this->try_show_next_level_menu();
            return Event_Accept;
        }
        break;
    case MouseEvent::Event_LButtonUp:
        // 父节点是MenuPopup?
        if (m_pMenuPopup && uisafe_cast<UIMenuPopup>(m_pParent)) {
            // 显示下一级菜单
            this->try_show_next_level_menu();
            // XXX: 截断上流消息, 直达UIControl
            return UIControl::DoMouseEvent(e);
        }
        break;
    }
    return Super::DoMouseEvent(e);
}

/// <summary>
/// Tries the show next level menu.
/// </summary>
/// <returns></returns>
void LongUI::UIMenu::try_show_next_level_menu() noexcept {
    // 没有头发
    assert(m_pMenuPopup && "must be valid");
    // 显示了就不算
    if (m_pMenuPopup->RefWindow().IsVisible()) return;
    // CHECK状态
    this->StartAnimation({ State_Closed, State_Closed });
    // XXX: 出现在右侧
    const auto edge = this->RefBox().GetBorderEdge();
    const auto pos = this->MapToWindowEx({ edge.right, -1 });
    LongUI::PopupWindowFromViewport(
        *this,
        *m_pMenuPopup,
        pos,
        PopupType::Type_PopupH,
        m_pMenuPopup->GetPopupPosition()
    );
}

/// <summary>
/// Adds the child.
/// </summary>
/// <param name="child">The child.</param>
/// <returns></returns>
void LongUI::UIMenu::add_child(UIControl& child) noexcept {
    // UIMenuPopup
    if (const auto ptr = uisafe_cast<UIMenuPopup>(&child)) {
        assert(m_pMenuPopup == nullptr);
        m_pMenuPopup = ptr;
        return;
    }
    // 其他的
    return Super::add_child(child);
}

/// <summary>
/// Adds the attribute.
/// </summary>
/// <param name="key">The key.</param>
/// <param name="value">The value.</param>
/// <returns></returns>
void LongUI::UIMenu::add_attribute(uint32_t key, U8View value) noexcept {
    constexpr auto BKDR_TYPE = 0x0fab1332_ui32;
    switch (key)
    {
    case BKDR_TYPE:
        // 无视TYPE
        break;
    default:
        // 其他情况, 交给超类处理
        return Super::add_attribute(key, value);
    }
}
