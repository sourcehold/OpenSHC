#include "../Menu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

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

    using namespace OpenSHC::UI::Enums;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F64A0
    void Menu::renderConstructionMenu()
    {
        DWORD const now = timeGetTime();
        MenuItem* const item = this->hoveredItem;
        // the text's index is the low word of textMessageLookupIndex, read as a dword and masked
        // (the ushort field_0x0: quick_diff 0.9559 -> 0.9227)
        int const indexMask = 0xffff;
        if (item != NULL && (*(int*)&item->textMessageLookupIndex & indexMask) != 0) {
            // in the building menus, only these tabs show texts
            if (DAT_GameCore::instance.currentMenuViewType != MVT_BUILDING_AND_STATUS_MENU
                || DAT_GameCore::instance.activeMenuTab.tabType == BASMTT_BARRACKS_OR_MPMENU_MODEM
                || DAT_GameCore::instance.activeMenuTab.tabType == BASMTT_MERCENARYPOST
                || DAT_GameCore::instance.activeMenuTab.tabType == BASMTT_TOWER
                || DAT_GameCore::instance.activeMenuTab.tabType == BASMTT_GATEHOUSE
                || DAT_GameCore::instance.activeMenuTab.tabType == BASMTT_ENGINEERSGUILD
                || DAT_GameCore::instance.activeMenuTab.tabType == BASMTT_TUNNELERSGUILD
                || DAT_GameCore::instance.activeMenuTab.tabType == BASMTT_CATHEDRAL) {
                int const index = *(int*)&item->textMessageLookupIndex & indexMask;
                switch (DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].messageType) {
                case 0:
                    return;
                case TMBLLSTE_BUTTON_TEXT:
                    if (DAT_GameCore::instance.settingBubbleHelp) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(1,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textGroupIndex,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textIndexInGroup,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index]
                                .associatedType.buildingType,
                            50, -1);
                    }
                    this->zero = 0;
                    return;
                case 13:
                    if (DAT_GameCore::instance.settingBubbleHelp) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(13,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textGroupIndex,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textIndexInGroup,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index]
                                .associatedType.buildingType,
                            50, -1);
                    }
                    this->zero = 0;
                    return;
                case 7:
                    MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                        DAT_BottomLeftTextDisplayState::ptr)(7,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textGroupIndex,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textIndexInGroup,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].associatedType.buildingType,
                        50, -1);
                    this->zero = 0;
                    return;
                case TMBLLSTE_BUILDING_TEXT:
                    if (DAT_GameCore::instance.settingBubbleHelp) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(2,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textGroupIndex,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textIndexInGroup,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index]
                                .associatedType.buildingType,
                            50, -1);
                    }
                    this->zero = 0;
                    return;
                case TMBLLSTE_WALL_TEXT:
                    if (DAT_GameCore::instance.settingBubbleHelp) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(4,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textGroupIndex,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textIndexInGroup,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index]
                                .associatedType.buildingType,
                            50, -1);
                    }
                    this->zero = 0;
                    return;
                case 9:
                    if (DAT_GameCore::instance.settingBubbleHelp) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(9,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textGroupIndex,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textIndexInGroup,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index]
                                .associatedType.buildingType,
                            50, -1);
                    }
                    this->zero = 0;
                    return;
                case TMBLLSTE_POPULARITY_HELP_TEXT:
                    if (DAT_GameCore::instance.settingBubbleHelp) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(3,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textGroupIndex,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textIndexInGroup,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index]
                                .associatedType.buildingType,
                            50, -1);
                    }
                    this->zero = 0;
                    return;
                case TMBLLSTE_UNITS_AND_WEAPONS_TEXT:
                    MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                        DAT_BottomLeftTextDisplayState::ptr)(6,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textGroupIndex,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textIndexInGroup,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].associatedType.buildingType,
                        50, -1);
                    this->zero = 0;
                    return;
                case 12:
                    MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                        DAT_BottomLeftTextDisplayState::ptr)(12,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textGroupIndex,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textIndexInGroup,
                        DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].associatedType.buildingType,
                        50, -1);
                    this->zero = 0;
                    return;
                case 8:
                    if (DAT_GameCore::instance.settingBubbleHelp) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(8,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textGroupIndex,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textIndexInGroup,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index]
                                .associatedType.buildingType,
                            50, -1);
                    }
                    this->zero = 0;
                    return;
                case 10:
                    if (DAT_GameCore::instance.settingBubbleHelp) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(10,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textGroupIndex,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textIndexInGroup,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index]
                                .associatedType.buildingType,
                            50, -1);
                    }
                    this->zero = 0;
                    return;
                case 11:
                    if (DAT_GameCore::instance.settingBubbleHelp) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(11,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textGroupIndex,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index].textIndexInGroup,
                            DAT_RenderingDefinedData::instance.TextMessageLookupTable[index]
                                .associatedType.buildingType,
                            50, -1);
                    }
                    this->zero = 0;
                    return;
                default:
                    // the tooltip, once the mouse has rested on the item for 200 ms
                    if (DAT_MouseState::instance.leftClickState || DAT_MouseState::instance.rightClickState
                        || DAT_MouseState::instance.midClickState || !DAT_GameCore::instance.settingBubbleHelp) {
                        break;
                    }
                    if (this->zero == 0) {
                        this->zero = 1;
                        this->someTimestampUnk = now;
                        this->mouseXScreenSpace = DAT_MouseState::instance.screenSpaceX;
                        this->mouseYScreenSpace = DAT_MouseState::instance.screenSpaceY;
                        return;
                    }
                    if (this->zero == 1 && DAT_MouseState::instance.screenSpaceX == this->mouseXScreenSpace
                        && DAT_MouseState::instance.screenSpaceY == this->mouseYScreenSpace) {
                        if ((int)(now - this->someTimestampUnk) <= 200) {
                            return;
                        }
                        this->zero = 2;
                        this->textIndexInGroup
                            = DAT_RenderingDefinedData::instance
                                  .TextMessageLookupTable[(*(int*)&item->textMessageLookupIndex & indexMask)]
                                  .textIndexInGroup;
                        this->textGroupIndex
                            = DAT_RenderingDefinedData::instance
                                  .TextMessageLookupTable[(*(int*)&item->textMessageLookupIndex & indexMask)]
                                  .textGroupIndex;
                        // "Resume Game" while the game is paused
                        if (this->textIndexInGroup == 302 && this->textGroupIndex == 8
                            && DAT_GameCore::instance.gameSuspended == 1) {
                            this->textGroupIndex = 74;
                            this->textIndexInGroup = 10;
                        }
                        this->someMenuItemPtr_0x3c = item;
                        return;
                    }
                    if (this->zero == 2 && this->someMenuItemPtr_0x3c == item) {
                        char* const text = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                            (OpenSHC::DE::SHCDE::eTextSections)this->textGroupIndex, this->textIndexInGroup);
                        int const width = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(text, 17);
                        if (DAT_GameCore::instance.currentMenuViewType != MVT_MISSION_FINISHED_TRANSITION
                            && DAT_GameCore::instance.currentMenuViewType != MVT_GAME_LOSTUnk) {
                            this->hoverTextX = DAT_MouseState::instance.screenSpaceX - width / 2 + 8;
                            this->hoverTextY = DAT_MouseState::instance.screenSpaceY - 68;
                        } else {
                            this->hoverTextX = DAT_MouseState::instance.screenSpaceX - width / 2 + 8;
                            this->hoverTextY = DAT_MouseState::instance.screenSpaceY + 16;
                        }
                        if (this->hoverTextY + 23 > DAT_WindowAndDirectDraw::instance.resolutionY) {
                            this->hoverTextY = DAT_MouseState::instance.screenSpaceY - 23;
                        }
                        if (this->hoverTextX + width + 20 > DAT_WindowAndDirectDraw::instance.resolutionX) {
                            this->hoverTextX = DAT_WindowAndDirectDraw::instance.resolutionX - width - 20;
                        }
                        if (this->hoverTextX < 0) {
                            this->hoverTextX = 0;
                        }
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                            this->hoverTextX, this->hoverTextY, this->hoverTextX + width + 18, this->hoverTextY + 26);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                            DAT_PencilRenderCore::ptr)(this->hoverTextX - 1, this->hoverTextY - 1,
                            this->hoverTextX + width + 19, this->hoverTextY + 27,
                            COL_GREYISH_YELLOW::instance.shortValue);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(text, this->hoverTextX + 11, this->hoverTextY + 3,
                            OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 17, FALSE, 0);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                        return;
                    }
                    break;
                }
            }
        }
        this->zero = 0;
    }

}
}
