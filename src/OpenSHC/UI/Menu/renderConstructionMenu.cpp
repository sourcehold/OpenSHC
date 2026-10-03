#include "../Menu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/UI/Enums/TextMessageBLLookupStructTypeEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_GREYISH_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::UI::Enums::TextMessageBLLookupStructTypeEnum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F64A0
    void Menu::renderConstructionMenu()
    {
        DWORD _currentTime;
        char* text;
        int iVar1;
        uint _index;
        int _group;
        int _groupIndex;
        MenuItem* _menuItem;
        _currentTime = timeGetTime();
        _menuItem = this->hoveredItem;
        if (((_menuItem != (MenuItem*)0x0)
                && (_index = (uint)(ushort)_menuItem->textMessageLookupIndex.field0_0x0, _index != 0))
            && ((((DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU
                      || ((((DAT_GameCore::instance.activeMenuTab.tabType
                                    == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                                || (DAT_GameCore::instance.activeMenuTab.tabType
                                    == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))
                               || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_TOWER))
                          || ((DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_GATEHOUSE
                              || (DAT_GameCore::instance.activeMenuTab.tabType
                                  == OpenSHC::UI::Enums::BASMTT_ENGINEERSGUILD))))))
                     || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_TUNNELERSGUILD))
                || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_CATHEDRAL)))) {
            switch (DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].messageType) {
            case ((TextMessageBLLookupStructTypeEnum)0):
                return;
            default:
                if (((DAT_MouseState::instance.leftClickState == FALSE)
                        && (DAT_MouseState::instance.rightClickState == FALSE))
                    && ((DAT_MouseState::instance.midClickState == FALSE
                        && (DAT_GameCore::instance.settingBubbleHelp != 0)))) {
                    iVar1 = this->zero;
                    if (iVar1 == 0) {
                        this->zero = 1;
                        this->someTimestampUnk = _currentTime;
                        this->mouseXScreenSpace = DAT_MouseState::instance.screenSpaceX;
                        this->mouseYScreenSpace = DAT_MouseState::instance.screenSpaceY;
                    }
                    if (((iVar1 == 1) && (DAT_MouseState::instance.screenSpaceX == this->mouseXScreenSpace))
                        && (DAT_MouseState::instance.screenSpaceY == this->mouseYScreenSpace)) {
                        if ((int)(_currentTime - this->someTimestampUnk) < 0xc9) {}
                        this->zero = 2;
                        _group = DAT_RenderingDefinedData::instance
                                     .TextMessageLookupTable[(uint)(ushort)_menuItem->textMessageLookupIndex.field0_0x0]
                                     .textIndexInGroup;
                        this->field11_0x2c = _group;
                        _groupIndex
                            = DAT_RenderingDefinedData::instance
                                  .TextMessageLookupTable[(uint)(ushort)_menuItem->textMessageLookupIndex.field0_0x0]
                                  .textGroupIndex;
                        this->field12_0x30 = _groupIndex;
                        if (((_group == 0x12e) && (_groupIndex == 8)) && (DAT_GameCore::instance.field22_0x64 == 1)) {
                            /*
                              "Resume Game"
                             */
                            this->field12_0x30 = 0x4a;
                            this->field11_0x2c = 10;
                        }
                        this->someMenuItemPtr_0x3c = _menuItem;
                    }
                    if ((iVar1 == 2) && (this->someMenuItemPtr_0x3c == _menuItem)) {
                        text = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                            (OpenSHC::DE::SHCDE::eTextSections)(this->field12_0x30), this->field11_0x2c);
                        iVar1 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(text, 0x11);
                        if ((DAT_GameCore::instance.currentMenuViewType
                                == OpenSHC::UI::Enums::MVT_MISSION_FINISHED_TRANSITION)
                            || (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_GAME_LOSTUnk)) {
                            this->field9_0x24 = (DAT_MouseState::instance.screenSpaceX - iVar1 / 2) + 8;
                            this->field10_0x28 = DAT_MouseState::instance.screenSpaceY + 0x10;
                        } else {
                            this->field9_0x24 = (DAT_MouseState::instance.screenSpaceX - iVar1 / 2) + 8;
                            this->field10_0x28 = DAT_MouseState::instance.screenSpaceY + -0x44;
                        }
                        if (DAT_WindowAndDirectDraw::instance.resolutionY < this->field10_0x28 + 0x17) {
                            this->field10_0x28 = DAT_MouseState::instance.screenSpaceY + -0x17;
                        }
                        if (DAT_WindowAndDirectDraw::instance.resolutionX < this->field9_0x24 + 0x14 + iVar1) {
                            this->field9_0x24 = (DAT_WindowAndDirectDraw::instance.resolutionX - iVar1) + -0x14;
                        }
                        if (this->field9_0x24 < 0) {
                            this->field9_0x24 = 0;
                        }
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox,
                            DAT_PencilRenderCore::ptr)(this->field9_0x24, this->field10_0x28,
                            this->field9_0x24 + 0x12 + iVar1, this->field10_0x28 + 0x1a);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                            DAT_PencilRenderCore::ptr)(this->field9_0x24 + -1, this->field10_0x28 + -1,
                            this->field9_0x24 + 0x13 + iVar1, this->field10_0x28 + 0x1b,
                            (ushort)((int)(COL_GREYISH_YELLOW::instance.shortValue)));
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(text, this->field9_0x24 + 0xb, this->field10_0x28 + 3,
                            OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x11, FALSE, 0);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                }
                break;
            case OpenSHC::UI::Enums::TMBLLSTE_BUTTON_TEXT:
                if (DAT_GameCore::instance.settingBubbleHelp != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                        DAT_BottomLeftTextDisplayState::ptr)(1,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textGroupIndex,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textIndexInGroup,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].associatedType, 0x32, -1);
                }
                break;
            case OpenSHC::UI::Enums::TMBLLSTE_BUILDING_TEXT:
                if (DAT_GameCore::instance.settingBubbleHelp != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                        DAT_BottomLeftTextDisplayState::ptr)(2,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textGroupIndex,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textIndexInGroup,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].associatedType, 0x32, -1);
                    this->zero = 0;
                }
                break;
            case OpenSHC::UI::Enums::TMBLLSTE_POPULARITY_HELP_TEXT:
                if (DAT_GameCore::instance.settingBubbleHelp != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                        DAT_BottomLeftTextDisplayState::ptr)(3,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textGroupIndex,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textIndexInGroup,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].associatedType, 0x32, -1);
                    this->zero = 0;
                }
                break;
            case OpenSHC::UI::Enums::TMBLLSTE_WALL_TEXT:
                if (DAT_GameCore::instance.settingBubbleHelp != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                        DAT_BottomLeftTextDisplayState::ptr)(4,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textGroupIndex,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textIndexInGroup,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].associatedType, 0x32, -1);
                    this->zero = 0;
                }
                break;
            case OpenSHC::UI::Enums::TMBLLSTE_UNITS_AND_WEAPONS_TEXT:
                MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                    DAT_BottomLeftTextDisplayState::ptr)(6,
                    DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textGroupIndex,
                    DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textIndexInGroup,
                    DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].associatedType, 0x32, -1);
                this->zero = 0;
                return;
            case ((TextMessageBLLookupStructTypeEnum)7):
                MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                    DAT_BottomLeftTextDisplayState::ptr)(7,
                    DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textGroupIndex,
                    DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textIndexInGroup,
                    DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].associatedType, 0x32, -1);
                this->zero = 0;
                return;
            case ((TextMessageBLLookupStructTypeEnum)8):
                if (DAT_GameCore::instance.settingBubbleHelp != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                        DAT_BottomLeftTextDisplayState::ptr)(8,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textGroupIndex,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textIndexInGroup,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].associatedType, 0x32, -1);
                    this->zero = 0;
                }
                break;
            case ((TextMessageBLLookupStructTypeEnum)9):
                if (DAT_GameCore::instance.settingBubbleHelp != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                        DAT_BottomLeftTextDisplayState::ptr)(9,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textGroupIndex,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textIndexInGroup,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].associatedType, 0x32, -1);
                    this->zero = 0;
                }
                break;
            case ((TextMessageBLLookupStructTypeEnum)10):
                if (DAT_GameCore::instance.settingBubbleHelp != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                        DAT_BottomLeftTextDisplayState::ptr)(10,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textGroupIndex,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textIndexInGroup,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].associatedType, 0x32, -1);
                    this->zero = 0;
                }
                break;
            case ((TextMessageBLLookupStructTypeEnum)0xb):
                if (DAT_GameCore::instance.settingBubbleHelp != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                        DAT_BottomLeftTextDisplayState::ptr)(0xb,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textGroupIndex,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textIndexInGroup,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].associatedType, 0x32, -1);
                    this->zero = 0;
                }
                break;
            case ((TextMessageBLLookupStructTypeEnum)0xc):
                MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                    DAT_BottomLeftTextDisplayState::ptr)(0xc,
                    DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textGroupIndex,
                    DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textIndexInGroup,
                    DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].associatedType, 0x32, -1);
                this->zero = 0;
                return;
            case ((TextMessageBLLookupStructTypeEnum)0xd):
                if (DAT_GameCore::instance.settingBubbleHelp != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                        DAT_BottomLeftTextDisplayState::ptr)(0xd,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textGroupIndex,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].textIndexInGroup,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[_index].associatedType, 0x32, -1);
                    this->zero = 0;
                }
            }
        }
        this->zero = 0;
    }

}
}
