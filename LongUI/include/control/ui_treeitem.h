﻿#pragma once
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

#include "ui_control.h"
//#include "../util/ui_double_click.h"
#include <cstddef>

// ui namespace
namespace LongUI {
    // tree
    class UITree;
    // treerow
    class UITreeRow;
    // cell
    class UITreeCell;
    // treechildren
    class UITreeChildren;
    // treeitem control
    class UITreeItem : public UIControl {
        // super class
        using Super = UIControl;
        // friend
        friend UITree; friend UITreeChildren;
    protected:
        // ctor
        UITreeItem(const MetaControl&) noexcept;
    public:
        // class meta
        static const  MetaControl   s_meta;
        // dtor
        ~UITreeItem() noexcept;
        // ctor
        explicit UITreeItem(UIControl* parent = nullptr) noexcept : UITreeItem(UITreeItem::s_meta) { this->final_ctor(parent); }
    public:
        // cell removed
        void CellRemoved(UITreeCell&) noexcept;
        // clear tree node
        void ClearTreeNode() noexcept { m_pTree = nullptr; };
        // get tree
        auto GetTreeNode() const noexcept { return m_pTree; };
        // is selected?
        auto IsSelected() const noexcept { return m_oStyle.state & State_Selected; }
        // is container[from xml-attribute]
        auto IsContainer()const noexcept { return m_bContainer; }
        // is opened ?
        auto IsOpened() const noexcept { return m_bOpened; }
        // get row
        auto GetRow() const noexcept { return m_pRow; }
        // get tree children
        auto GetTreeChildren() const noexcept { return m_pChildren; }
        // tree children changed
        void TreeChildrenChanged(bool has_child) noexcept;
        // tree children closed
        void TreeChildrenOpenClose(bool open) noexcept;
        // select cell
        void SelectCell(UITreeCell* cell) noexcept;
        // select cell
        void SelectCell(std::nullptr_t) noexcept;
        // get selected cell
        auto GetSelectedCell() const noexcept { return m_pSelected; }
        // calculate offset [NULL this pointer safe]
        auto CalTreeOffset() const noexcept -> float;
    public:
        // add a child item
        auto AddItem() noexcept->UITreeItem*;
        // add a cell for this
        auto AddCell() noexcept->UITreeCell*;
        // easy - add cells for this 
        void EzAddCells(const U16View labels[], uint32_t count) noexcept;
    public:
        // do normal event
        //auto DoEvent(UIControl* sender, const EventArg& e) noexcept->EventAccept override;
        // do mouse event
        //auto DoMouseEvent(const MouseEventArg& e) noexcept->EventAccept override;
        // update with some reason
        void Update(UpdateReason) noexcept override;
        // render this control only, [Global rendering and Incremental rendering]
        //void Render() const noexcept override;
        // recreate/init device(gpu) resource
        //auto Recreate() noexcept->Result override;
    protected:
        // initialize
        void initialize() noexcept override;
        // add attribute
        void add_attribute(uint32_t key, U8View value) noexcept override;
        // add child
        void add_child(UIControl& child) noexcept override;
#ifdef LUI_ACCESSIBLE
        // accessible api
        auto accessible(const AccessibleEventArg& args) noexcept->EventAccept override;
#endif
        // refresh fitting
        void refresh_fitting(UIControl* head) noexcept;
        // relayout
        void relayout(UIControl* head) noexcept;
        // is last item
        bool cal_is_last_item() const noexcept;
    protected:
        // selected cell
        UITreeCell*             m_pSelected = nullptr;
        // tree root
        UITree*                 m_pTree = nullptr;
        // tree row
        UITreeRow*              m_pRow = nullptr;
        // tree children
        UITreeChildren*         m_pChildren = nullptr;
    public:
        // level offset
        float                   level_offset = 0.f;
        // index - vaild on displayed
        uint32_t                index = 0;
    protected:
        // marked selected
        bool                    m_bMarkdSel = false;
        // opened
        bool                    m_bOpened = false;
        // container
        bool                    m_bContainer = false;
    private:
    };
    // get meta info for UITreeItem
    LUI_DECLARE_METAINFO(UITreeItem);
}
