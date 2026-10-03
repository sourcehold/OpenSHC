#include "../Menu.func.hpp"

#include "OpenSHC/Rendering/Enums/GmDataIndex.hpp"
#include "OpenSHC/UI/Callbacks/SimpleActionHandler.hpp"
#include "OpenSHC/UI/Callbacks/SimpleRenderFunction.hpp"
#include "OpenSHC/UI/Enums/MenuItemType.hpp"
#include "OpenSHC/UI/Enums/MenuItemUCMarker.hpp"
#include "OpenSHC/UI/Enums/UserControlID.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Rendering::Enums::GmDataIndex;
    using OpenSHC::UI::Enums::MenuItemType;
    using OpenSHC::UI::Enums::MenuItemUCMarker;
    using OpenSHC::UI::Enums::UserControlID;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F4100
    Menu* Menu::Constructor_Menu(MenuItem* menuItemArrayAddress)
    {
        MenuItem* _shiftedCurrentMenuItemPtr;
        MenuItem* _nextMenuItem2;
        MenuItem* _nextMenuItem3;
        MenuItem* _currentMenuItemPtr;
        MenuItem* _nextMenuItem1;
        GmDataIndexInt GVar1;
        int _itemsToSkip;
        uint _nextMenuItemType2;
        MenuItemTypeInt* _nextMenuItemType4Ptr;
        MenuItemTypeInt _currentMenuItemType;
        MenuItemActionHandlerUnion _previousClickHandler;
        MenuItemRenderFunctionUnion _previousRenderFunction;
        MenuItemUCMarkerInt _ucMarker;
        this->menuItemArray = menuItemArrayAddress;
        this->xPosition = 0;
        this->yPosition = 0;
        this->thousand = 1000;
        this->zero = 0;
        this->someTimestampUnk = 0;
        this->mouseXScreenSpace = -1000;
        /*
          0x66 is the final element sentinel
         */
        if (menuItemArrayAddress->menuItemType != OpenSHC::UI::Enums::MIT_LAST_ENTRY) {
            _shiftedCurrentMenuItemPtr = (OpenSHC::UI::MenuItem*)(&menuItemArrayAddress->position);
            do {
                _ucMarker = (_shiftedCurrentMenuItemPtr->position).ucInfo.ucMarker_0x0;
                _shiftedCurrentMenuItemPtr->menuPointer = this;
                if (_ucMarker == OpenSHC::UI::Enums::USE_UC_COORDS) {
                    _shiftedCurrentMenuItemPtr->ucID
                        = *(UserControlIDShort*)((int)&_shiftedCurrentMenuItemPtr->position + 4);
                } else {
                    _shiftedCurrentMenuItemPtr->ucID = ((MenuItemType)0xffff);
                }
                _currentMenuItemType = _shiftedCurrentMenuItemPtr->menuItemType;
                _currentMenuItemPtr = _shiftedCurrentMenuItemPtr;
                _shiftedCurrentMenuItemPtr->unknownZero = 0;
                if (_currentMenuItemType == OpenSHC::UI::Enums::MIT_TAB_CONSIDER_ITEM_SKIP_BECAUSE_OTHER_MENU_TAB) {
                    _nextMenuItem1 = (MenuItem*)((int)_shiftedCurrentMenuItemPtr + 0x4c);
                    _itemsToSkip = 0;
                    _currentMenuItemType = *(MenuItemTypeInt*)((int)_shiftedCurrentMenuItemPtr + 0x4c);
                    while ((_currentMenuItemType != OpenSHC::UI::Enums::MIT_LAST_ENTRY
                        && (_currentMenuItemType
                            != OpenSHC::UI::Enums::MIT_TAB_CONSIDER_ITEM_SKIP_BECAUSE_OTHER_MENU_TAB))) {
                        if (_currentMenuItemType == OpenSHC::UI::Enums::MIT_STOP_HANDLING)
                            goto LAB_004f419d;
                        _currentMenuItemPtr = _nextMenuItem1 + 1;
                        _nextMenuItem1 = _nextMenuItem1 + 1;
                        _itemsToSkip = _itemsToSkip + 1;
                        _currentMenuItemType = _currentMenuItemPtr->menuItemType;
                    }
                    if (_nextMenuItem1->menuItemType == OpenSHC::UI::Enums::MIT_STOP_HANDLING) {
                    LAB_004f419d:
                        _itemsToSkip = _itemsToSkip + 1;
                    }
                    /*
                      The whole structure here just seems to set this value. Why? --TheRedDaemon
                     */
                    (_shiftedCurrentMenuItemPtr->firstItemTypeData).itemsToSkip = _itemsToSkip;
                } else if (_currentMenuItemType == OpenSHC::UI::Enums::MIT_START_OF_INTERACTION_GROUPUnk) {
                    _previousClickHandler = _shiftedCurrentMenuItemPtr->menuItemActionHandler;
                    _previousRenderFunction = _shiftedCurrentMenuItemPtr->menuItemRenderFunction;
                    _nextMenuItem2 = (MenuItem*)((int)_shiftedCurrentMenuItemPtr + 0x4c);
                    GVar1 = OpenSHC::Rendering::Enums::GDI_NONE_0;
                    _nextMenuItemType2 = _nextMenuItem2->menuItemType;
                    while ((_nextMenuItemType2 & OpenSHC::UI::Enums::MIT_PART_OF_INTERACTION_GROUPUnk)
                        != ((MenuItemType)0)) {
                        if ((_nextMenuItem2->menuItemActionHandler).simple
                            == (OpenSHC::UI::Callbacks::SimpleActionHandler*)0x0) {
                            _nextMenuItem2->menuItemActionHandler = _previousClickHandler;
                        }
                        if ((_nextMenuItem2->menuItemRenderFunction).simple
                            == (OpenSHC::UI::Callbacks::SimpleRenderFunction*)0x0) {
                            _nextMenuItem2->menuItemRenderFunction = _previousRenderFunction;
                        }
                        _nextMenuItem2 = _nextMenuItem2 + 1;
                        GVar1 = GVar1 + OpenSHC::Rendering::Enums::GDI_ICONS_PLACEHOLDERS_1_PIC_61;
                        _nextMenuItemType2 = _nextMenuItem2->menuItemType;
                    }
                    (_shiftedCurrentMenuItemPtr->firstItemTypeData).gmDataIndex = GVar1;
                    _currentMenuItemType = _nextMenuItem2->menuItemType;
                    while (_currentMenuItemType == ((MenuItemType)0x11000000)) {
                        _currentMenuItemPtr->menuItemType
                            = _currentMenuItemPtr->menuItemType | ((MenuItemType)0x20000000);
                        _previousClickHandler = _nextMenuItem2->menuItemActionHandler;
                        _previousRenderFunction = _nextMenuItem2->menuItemRenderFunction;
                        _nextMenuItem3 = _nextMenuItem2 + 1;
                        GVar1 = OpenSHC::Rendering::Enums::GDI_NONE_0;
                        _currentMenuItemType = _nextMenuItem3->menuItemType;
                        while ((_currentMenuItemType & OpenSHC::UI::Enums::MIT_PART_OF_INTERACTION_GROUPUnk)
                            != ((MenuItemType)0)) {
                            if ((_nextMenuItem3->menuItemActionHandler).simple
                                == (OpenSHC::UI::Callbacks::SimpleActionHandler*)0x0) {
                                _nextMenuItem3->menuItemActionHandler = _previousClickHandler;
                            }
                            if ((_nextMenuItem3->menuItemRenderFunction).simple
                                == (OpenSHC::UI::Callbacks::SimpleRenderFunction*)0x0) {
                                _nextMenuItem3->menuItemRenderFunction = _previousRenderFunction;
                            }
                            _nextMenuItem3 = _nextMenuItem3 + 1;
                            GVar1 = GVar1 + OpenSHC::Rendering::Enums::GDI_ICONS_PLACEHOLDERS_1_PIC_61;
                            _currentMenuItemType = _nextMenuItem3->menuItemType;
                        }
                        (_nextMenuItem2->firstItemTypeData).gmDataIndex = GVar1;
                        _nextMenuItem2 = _nextMenuItem3;
                        _currentMenuItemType = _nextMenuItem3->menuItemType;
                    }
                } else if ((_currentMenuItemType & 0x4000000) != ((MenuItemType)0)) {
                    _currentMenuItemType = _currentMenuItemPtr->menuItemType;
                    while (((_currentMenuItemType & 0x4000000) != ((MenuItemType)0)
                        && (_currentMenuItemPtr != menuItemArrayAddress))) {
                        _currentMenuItemPtr = _currentMenuItemPtr + -1;
                        _currentMenuItemType = _currentMenuItemPtr->menuItemType;
                    }
                    _currentMenuItemPtr->menuItemType = _currentMenuItemPtr->menuItemType | ((MenuItemType)0x8000000);
                }
                _nextMenuItemType4Ptr = (MenuItemTypeInt*)((int)_shiftedCurrentMenuItemPtr + 0x4c);
                _shiftedCurrentMenuItemPtr = _shiftedCurrentMenuItemPtr + 10;
            } while (*_nextMenuItemType4Ptr != OpenSHC::UI::Enums::MIT_LAST_ENTRY);
        }
        return this;
    }

}
}
