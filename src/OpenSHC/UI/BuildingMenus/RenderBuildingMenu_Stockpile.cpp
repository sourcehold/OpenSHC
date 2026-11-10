#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_StockpileIconsPositionNudges.hpp"
#include "OpenSHC/Globals/DAT_StockpileMenuResourceIcons.hpp"
#include "OpenSHC/Globals/DAT_StockpileMenuResourceTypes.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Game::Resources::ResourceTypeInt;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    using OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043C6A0
    void BuildingMenus::RenderBuildingMenu_Stockpile()
    {
        int x = DAT_MenuHandlerState::instance.x + 30;
        int iconsY = DAT_MenuHandlerState::instance.y + 512;
        // Render stockpile title
        int titleY = DAT_MenuHandlerState::instance.y + 467;
        int titleX = DAT_MenuHandlerState::instance.x + 25;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GOODS_YARD, 0),
            titleX, titleY, OpenSHC::Text::TTA_LEFT, 0, 16, FALSE, 0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        for (int i = 0; i < 8; ++i) {
            int amount = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                             .currentResources[DAT_StockpileMenuResourceTypes::instance[i]];
            // Render resource image
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                DAT_StockpileMenuResourceIcons::instance[i], DAT_StockpileIconsPositionNudges::instance[i].x + x,
                DAT_StockpileIconsPositionNudges::instance[i].y + iconsY);
            if (DAT_MouseState::instance.leftClickStart != 0) {
                int image = DAT_StockpileMenuResourceIcons::instance[i] + GMFirstPictureIndex::instance[46] - 1;
                BOOLEnum inside = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::isMouseInsideBox,
                    DAT_MouseState::ptr)(DAT_StockpileIconsPositionNudges::instance[i].x + x,
                    DAT_StockpileIconsPositionNudges::instance[i].y + iconsY,
                    DAT_GMImageHeaders::instance.imh[image].width, DAT_GMImageHeaders::instance.imh[image].height);
                if (inside != FALSE
                    && DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .buildingEntryInfos[BEIE_MARKETPLACE]
                            .id
                        != 0
                    && MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::isResourceTypeTradeable,
                           DAT_GameState::ptr)((ResourceType)DAT_StockpileMenuResourceTypes::instance[i])
                        != FALSE) {
                    DAT_BuildingsState::instance.newSelectedBuildingID
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .buildingEntryInfos[BEIE_MARKETPLACE]
                              .id;
                    DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = 57;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .marketSelectedResourceType = DAT_StockpileMenuResourceTypes::instance[i];
                }
            }
            // Render textfields for resources
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                amount, x + 12, DAT_MenuHandlerState::instance.y + 559, OpenSHC::Text::TTA_LEFT, 0, 17, FALSE, 0);
            x += 60;
        }
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
