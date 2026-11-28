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

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Buildings::BuildingTypeShort;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004B0390
    void DisplayElements::RenderPlayerInfoOnHoverDisplayElement(int posX, int posY, DWORD elementState)
    {
        int aiIndex = 0;
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            if (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_BUILD_MENU)
                return;
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                return;
        }
        int hoveredOwner = 0;
        if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
            if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM) {
                posY = posY + -0x28;
            } else if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                posY = posY + -0x28;
            } else {
                posY = posY + -0x14;
            }
        }
        if ((DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID == 0)
            || (DAT_ViewportRenderState::instance.viewportState.field0_0x0 == 0)) {
            if (DAT_ViewportRenderState::instance.viewportState.cursorWallTile != 0
                && DAT_ViewportRenderState::instance.viewportState.field0_0x0 != 0
                && (hoveredOwner
                    = (DAT_TileMapState::instance
                              .WallOwnerLayer[DAT_ViewportRenderState::instance.viewportState.cursorWallTile]
                          & 7)
                        + 1,
                    DAT_GameCore::instance.mapU4Int0 != 0)
                && hoveredOwner == DAT_GameState::instance.mapAndTime.somePlayerID)
                return;
        } else {
            BuildingTypeShort _buildingType
                = DAT_BuildingsState::instance
                      .buildings[DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID]
                      .buildingType;
            if (_buildingType == OpenSHC::Map::Buildings::BT_PITCHDITCH)
                return;
            if (_buildingType == OpenSHC::Map::Buildings::BT_KILLINGPIT)
                return;
            if (_buildingType == OpenSHC::Map::Buildings::BT_SIGNPOST)
                return;
            if ((DAT_GameCore::instance.mapU4Int0 != 0)
                && (DAT_BuildingsState::instance
                        .buildings[DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID]
                        .owner
                    == DAT_GameState::instance.mapAndTime.somePlayerID))
                return;
            hoveredOwner = (int)DAT_BuildingsState::instance
                               .buildings[DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID]
                               .owner;
        }
        if (DAT_MenuModalComposition2::instance.activeModalDialogID
            == OpenSHC::UI::Enums::MMT_DISPLAY_AI_LORD_MESSAGE) {
            DAT_00df5530::instance = 0;
            return;
        }
        uint blendStrength = 0;
        if (hoveredOwner != 0) {
            DAT_00df5530::instance = hoveredOwner;
            INT_00df552c::instance = timeGetTime();
        } else if (DAT_00df5530::instance != 0) {
            uint elapsed = timeGetTime() - INT_00df552c::instance;
            if (0x2d0 <= elapsed) {
                DAT_00df5530::instance = 0;
            } else if (400 < elapsed) {
                blendStrength = (elapsed - 400) / 10;
            }
        }
        if ((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU)
            && (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)) {
            if (DAT_00df5530::instance == 0)
                return;
            MACRO_CALL_MEMBER(
                OpenSHC::Text::TextManager_Func::computeTextWidthForTextGroup, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_BUBBLE_HELP_TEXT, DAT_00df5530::instance + 0xcc, 0x10);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_BUBBLE_HELP_TEXT, DAT_00df5530::instance + 0xcc, posX, posY + -0x14,
                OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0, 0x10, FALSE);
            return;
        }
        if (DAT_00df5530::instance == 0)
            return;
        int textWidth = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth,
            DAT_TextManagerObject::ptr)(DAT_GameSynchronyState::instance.DAT_PlayerNames[DAT_00df5530::instance], 0x10);
        int halfWidth = textWidth / 2;
        if (blendStrength == 0) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                DAT_GameSynchronyState::instance.DAT_PlayerNames[DAT_00df5530::instance], posX + 0x28, posY,
                OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0, 0x10, FALSE, 0);
            int iconX = posX + (-0x30 - halfWidth);
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_00df5530::instance] == -1) {
                aiIndex = DAT_GameSynchronyState::instance.currentAIArray[DAT_00df5530::instance];
            }
            int iconY = posY + -0x26;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, DAT_00df5530::instance + 0x222, iconX, iconY);
            if (aiIndex == 0) {
                if (DAT_GameCore::instance.lordIcons[DAT_00df5530::instance] == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x21b, iconX, iconY);
                } else if (DAT_GameCore::instance.lordIcons[DAT_00df5530::instance] == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x21c, iconX, iconY);
                } else if (0 < DAT_TextureRenderCoreObject::instance.bitmapFaceSizes[DAT_00df5530::instance + 0x13]) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x21d, iconX, iconY);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFace,
                        DAT_TextureRenderCoreObject::ptr)(DAT_00df5530::instance + 0x13, iconX + 4, posY + -0x22);
                }
            } else {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, aiIndex + 0x20a, iconX, iconY);
            }
            int playerGroup = DAT_GameState::instance.mapAndTime.playerGroupArray[DAT_00df5530::instance];
            if (playerGroup <= 0)
                return;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, playerGroup * 2 + 0x1ed, iconX + 0x4c, iconY);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                DAT_GameSynchronyState::instance.DAT_PlayerNames[DAT_00df5530::instance], posX + 0x28, posY,
                OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0, 0x10, FALSE, (int)(blendStrength));
            int iconX = posX + (-0x30 - halfWidth);
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_00df5530::instance] == -1) {
                aiIndex = DAT_GameSynchronyState::instance.currentAIArray[DAT_00df5530::instance];
            }
            int iconY = posY + -0x26;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                DAT_00df5530::instance + 0x222, iconX, iconY, (int)(blendStrength));
            if (aiIndex == 0) {
                if (DAT_GameCore::instance.lordIcons[DAT_00df5530::instance] == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x21b, iconX, iconY, (int)(blendStrength));
                } else if (DAT_GameCore::instance.lordIcons[DAT_00df5530::instance] == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x21c, iconX, iconY, (int)(blendStrength));
                } else if (0 < DAT_TextureRenderCoreObject::instance.bitmapFaceSizes[DAT_00df5530::instance + 0x13]) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x21d, iconX, iconY, (int)(blendStrength));
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFaceWithBlendUnk,
                        DAT_TextureRenderCoreObject::ptr)(
                        DAT_00df5530::instance + 0x13, iconX + 4, posY + -0x22, (int)(blendStrength));
                }
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, aiIndex + 0x20a, iconX, iconY, (int)(blendStrength));
            }
            int playerGroup = DAT_GameState::instance.mapAndTime.playerGroupArray[DAT_00df5530::instance];
            if (playerGroup <= 0)
                return;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, playerGroup * 2 + 0x1ed,
                iconX + 0x4c, iconY, (int)(blendStrength));
        }
    }
}
}
