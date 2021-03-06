#include <control/ui_test.h>
#ifndef NDEBUG
#include <core/ui_ctrlmeta.h>
#include <debugger/ui_debug.h>


// ui namespace
namespace LongUI {
    // UITest类 元信息
    LUI_CONTROL_META_INFO(UITest, "test");
}


/// <summary>
/// Finalizes an instance of the <see cref="UITest"/> class.
/// </summary>
/// <returns></returns>
LongUI::UITest::~UITest() noexcept {
}


/// <summary>
/// Initializes a new instance of the <see cref="UITest" /> class.
/// </summary>
/// <param name="meta">The meta.</param>
LongUI::UITest::UITest(const MetaControl& meta) noexcept : Super(meta) {

}

/// <summary>
/// Does the event.
/// </summary>
/// <param name="sender">The sender.</param>
/// <param name="e">The e.</param>
/// <returns></returns>
auto LongUI::UITest::DoEvent(UIControl* sender, 
    const EventArg& e) noexcept -> EventAccept {
    return Super::DoEvent(sender, e);
}

/// <summary>
/// Does the mouse event.
/// </summary>
/// <param name="e">The e.</param>
/// <returns></returns>
auto LongUI::UITest::DoMouseEvent(const MouseEventArg & e) noexcept -> EventAccept {
    switch (e.type)
    {
    case LongUI::MouseEvent::Event_MouseWheelV:
        //LUIDebug(Hint) LUI_FRAMEID << e.type << endl;
        //return Event_Accept;
        break;
    case LongUI::MouseEvent::Event_MouseWheelH:
        LUIDebug(Hint) LUI_FRAMEID << e.type << endl;
        break;
    case LongUI::MouseEvent::Event_MouseEnter:
        break;
    case LongUI::MouseEvent::Event_MouseLeave:
        break;
    case LongUI::MouseEvent::Event_MouseMove:
        break;
    case LongUI::MouseEvent::Event_LButtonDown:
        break;
    case LongUI::MouseEvent::Event_LButtonUp:
        break;
    case LongUI::MouseEvent::Event_RButtonDown:
        break;
    case LongUI::MouseEvent::Event_RButtonUp:
        break;
    case LongUI::MouseEvent::Event_MButtonDown:
        break;
    case LongUI::MouseEvent::Event_MButtonUp:
        break;
    }
    return Super::DoMouseEvent(e);
}

/// <summary>
/// Renders this instance.
/// </summary>
/// <returns></returns>
void LongUI::UITest::Render() const noexcept {
    return Super::Render();
}

/// <summary>
/// update this instance.
/// </summary>
/// <returns></returns>
void LongUI::UITest::Update(UpdateReason reason) noexcept {
    return Super::Update(reason);
}

/// <summary>
/// Recreates this instance.
/// </summary>
/// <param name="release_only">if set to <c>true</c> [release only].</param>
/// <returns></returns>
auto LongUI::UITest::Recreate(bool release_only) noexcept -> Result {
    return Super::Recreate(release_only);
}

/// <summary>
/// add child for this
/// </summary>
/// <param name="child"></param>
/// <returns></returns>
void LongUI::UITest::add_child(UIControl& child) noexcept {
    return Super::add_child(child);
}

#endif