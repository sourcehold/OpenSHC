#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00df5530.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/INT_00df552c.hpp"

namespace OpenSHC {
namespace UI {

    using DE::SHCDE::eGM;
    using DE::SHCDE::eTextSections;
    using Game::GameMode;
    using Game::GameMode2;
    using IO::Graphics::GmID;
    using Map::Buildings::BuildingType;
    using Map::Buildings::BuildingTypeShort;
    using Text::TextAlignment;
    using UI::Enums::BuildingsAndStatusMenuTabType;
    using UI::Enums::MenuModalType;
    using UI::Enums::MenuViewType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004B0390
    void DisplayElements::RenderPlayerInfoOnHoverDisplayElement(int posX, int posY, DWORD elementState)
    {
        int iVar5;
        BuildingTypeShort _buildingType;
        int iVar4 = 0;
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            if (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_BUILD_MENU) {}
            if (DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR) {}
        }
        int iVar3 = 0;
        if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
            if (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM) {
                posY = posY + -0x28;
            } else if (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_MERCENARYPOST) {
                posY = posY + -0x28;
            } else {
                posY = posY + -0x14;
            }
        }
        if ((!DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID)
            || (!DAT_ViewportRenderState::instance.viewportState.field0_0x0)) {
            if (DAT_ViewportRenderState::instance.viewportState.cursorWallTile
                && DAT_ViewportRenderState::instance.viewportState.field0_0x0
                && (iVar3 = (DAT_TileMapState::instance
                                    .WallOwnerLayer[DAT_ViewportRenderState::instance.viewportState.cursorWallTile]
                                & 7)
                        + 1,
                    DAT_GameCore::instance.mapU4Int0 != 0)
                && iVar3 == DAT_GameState::instance.mapAndTime.somePlayerID) {}
        } else {
            _buildingType = DAT_BuildingsState::instance
                                .buildings[DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID]
                                .buildingType;
            if (_buildingType == Map::Buildings::BT_PITCHDITCH) {}
            if (_buildingType == Map::Buildings::BT_KILLINGPIT) {}
            if (_buildingType == Map::Buildings::BT_SIGNPOST) {}
            if ((DAT_GameCore::instance.mapU4Int0)
                && (DAT_BuildingsState::instance
                        .buildings[DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID]
                        .owner
                    == DAT_GameState::instance.mapAndTime.somePlayerID)) {}
            iVar3 = (int)DAT_BuildingsState::instance
                        .buildings[DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID]
                        .owner;
        }
        if (DAT_MenuModalComposition2::instance.activeModalDialogID == UI::Enums::MMT_DISPLAY_AI_LORD_MESSAGE) {
            DAT_00df5530::instance = 0;
        }
        uint blendStrength = 0;
        if (!iVar3) {
            if (DAT_00df5530::instance) {
                DWORD DVar1 = timeGetTime();
                uint uVar2 = DVar1 - INT_00df552c::instance;
                if (uVar2 < 0x2d0) {
                    if (400 < uVar2) {
                        blendStrength = (uVar2 - 400) / 10;
                    }
                } else {
                    DAT_00df5530::instance = 0;
                }
            }
        } else {
            DAT_00df5530::instance = iVar3;
            INT_00df552c::instance = timeGetTime();
        }
        if ((DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU)
            && (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR)) {
            if (!DAT_00df5530::instance) {}
            MACRO_CALL_MEMBER(Text::TextManager_Func::computeTextWidthForTextGroup, DAT_TextManagerObject::ptr)(
                DE::SHCDE::TEXT_BUBBLE_HELP_TEXT, DAT_00df5530::instance + 0xcc, 0x10);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                DE::SHCDE::TEXT_BUBBLE_HELP_TEXT, DAT_00df5530::instance + 0xcc, posX, posY + -0x14, Text::TTA_CENTER,
                0xc2f0eb, 0, 0x10, FALSE);
        }
        if (!DAT_00df5530::instance) {}
        iVar3 = MACRO_CALL_MEMBER(Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.DAT_PlayerNames[DAT_00df5530::instance], 0x10);
        if (blendStrength) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                DAT_GameSynchronyState::instance.DAT_PlayerNames[DAT_00df5530::instance], posX + 0x28, posY,
                Text::TTA_CENTER, 0xc2f0eb, 0, 0x10, FALSE, (int)(blendStrength));
            iVar3 = posX + (-0x30 - iVar3 / 2);
            iVar4 = 0;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_00df5530::instance] == -1) {
                iVar4 = DAT_GameSynchronyState::instance.currentAIArray[DAT_00df5530::instance];
            }
            iVar5 = posY + -0x26;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_2, DAT_00df5530::instance + 0x222,
                iVar3, iVar5, (int)(blendStrength));
            if (!iVar4) {
                if (DAT_GameCore::instance.lordIcons[DAT_00df5530::instance] == 0) {
                    iVar4 = 0x21b;
                } else {
                    if (DAT_GameCore::instance.lordIcons[DAT_00df5530::instance] != 1) {
                        if (0 < DAT_TextureRenderCoreObject::instance.bitmapFaceSizes[DAT_00df5530::instance + 0x13]) {
                            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(
                                IO::Graphics::GID_INTERFACE_ICONS_2, 0x21d, iVar3, iVar5, (int)(blendStrength));
                            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::drawBitmapFaceWithBlendUnk,
                                DAT_TextureRenderCoreObject::ptr)(
                                DAT_00df5530::instance + 0x13, iVar3 + 4, posY + -0x22, (int)(blendStrength));
                        }
                        goto LAB_004b0782;
                    }
                    iVar4 = 0x21c;
                }
            } else {
                iVar4 = iVar4 + 0x20a;
            }
            MACRO_CALL_MEMBER(
                UI::Rendering::TextureRenderCore_Func::renderGMWithBlending, DAT_TextureRenderCoreObject::ptr)(
                IO::Graphics::GID_INTERFACE_ICONS_2, iVar4, iVar3, iVar5, (int)(blendStrength));
        LAB_004b0782:
            iVar4 = DAT_GameState::instance.mapAndTime.playerGroupArray[DAT_00df5530::instance];
            if (iVar4 < 1) {}
            MACRO_CALL_MEMBER(
                UI::Rendering::TextureRenderCore_Func::renderGMWithBlending, DAT_TextureRenderCoreObject::ptr)(
                IO::Graphics::GID_INTERFACE_ICONS_2, iVar4 * 2 + 0x1ed, iVar3 + 0x4c, iVar5, (int)(blendStrength));
        }
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.DAT_PlayerNames[DAT_00df5530::instance], posX + 0x28, posY,
            Text::TTA_CENTER, 0xc2f0eb, 0, 0x10, FALSE, 0);
        iVar3 = posX + (-0x30 - iVar3 / 2);
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_00df5530::instance] == -1) {
            iVar4 = DAT_GameSynchronyState::instance.currentAIArray[DAT_00df5530::instance];
        }
        iVar5 = posY + -0x26;
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            DE::SHCDE::GM_INTERFACE_ICONS2, DAT_00df5530::instance + 0x222, iVar3, iVar5);
        if (!iVar4) {
            if (DAT_GameCore::instance.lordIcons[DAT_00df5530::instance] == 0) {
                iVar4 = 0x21b;
            } else {
                if (DAT_GameCore::instance.lordIcons[DAT_00df5530::instance] != 1) {
                    if (0 < DAT_TextureRenderCoreObject::instance.bitmapFaceSizes[DAT_00df5530::instance + 0x13]) {
                        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, 0x21d, iVar3, iVar5);
                        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::drawBitmapFace,
                            DAT_TextureRenderCoreObject::ptr)(DAT_00df5530::instance + 0x13, iVar3 + 4, posY + -0x22);
                    }
                    goto LAB_004b0659;
                }
                iVar4 = 0x21c;
            }
        } else {
            iVar4 = iVar4 + 0x20a;
        }
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            DE::SHCDE::GM_INTERFACE_ICONS2, iVar4, iVar3, iVar5);
    LAB_004b0659:
        iVar4 = DAT_GameState::instance.mapAndTime.playerGroupArray[DAT_00df5530::instance];
        if (iVar4 < 1) {}
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            DE::SHCDE::GM_INTERFACE_ICONS2, iVar4 * 2 + 0x1ed, iVar3 + 0x4c, iVar5);
    }

}
}
