#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MarketStonksOrder.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043CE30
    void BuildingMenus::RenderBuildingMenu_Marketplace_Stonks()
    {
        int blendStrengthOrPriceY = 0;
        BOOLEnum keepOffsetXOrTradeable = FALSE;
        int fontSizeOrPriceX = 18;
        BGR24 color = 0;
        TextAlignment alignment = OpenSHC::Text::TTA_LEFT;
        int yOrColumnX = DAT_MenuHandlerState::instance.y + 468;
        int xOrRowY = DAT_MenuHandlerState::instance.x + 25;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        // "Here's what I sell and what they cost."
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_TRADEPOST, 1),
            xOrRowY, yOrColumnX, alignment, color, fontSizeOrPriceX, keepOffsetXOrTradeable, blendStrengthOrPriceY);
        for (int index = 0; index < 20; ++index) {
            ResourceType resourceType
                = (OpenSHC::Game::Resources::ResourceType)(DAT_MarketStonksOrder::instance[index]);
            if (resourceType != ((ResourceType)0)) {
                if (index >= 13) {
                    yOrColumnX = index - 11;
                    xOrRowY = 100;
                } else if (index >= 10) {
                    yOrColumnX = index - 10;
                    xOrRowY = 100;
                } else {
                    yOrColumnX = index;
                    xOrRowY = 40;
                }
                yOrColumnX = yOrColumnX * 47;
                keepOffsetXOrTradeable = MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::isResourceTypeTradeable, DAT_GameState::ptr)(resourceType);
                if (keepOffsetXOrTradeable != FALSE) {
                    ResourceType iconType = resourceType;
                    if (resourceType == OpenSHC::Game::Resources::RT_PITCH) {
                        iconType = OpenSHC::Game::Resources::RT_PARTIALPITCH;
                    }
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentResources[resourceType]
                        <= -100) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                            (int)(iconType * 2 + 42), DAT_MenuHandlerState::instance.x + 66 + yOrColumnX,
                            DAT_MenuHandlerState::instance.y + 447 + xOrRowY, 16);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                            (int)(iconType * 2 + 42), DAT_MenuHandlerState::instance.x + 66 + yOrColumnX,
                            DAT_MenuHandlerState::instance.y + 447 + xOrRowY);
                    }
                    if (index == 10) {
                        yOrColumnX = yOrColumnX - 10;
                    } else if (index == 11) {
                        yOrColumnX = yOrColumnX - 6;
                    } else if (index == 2) {
                        yOrColumnX = yOrColumnX + 4;
                    } else if (index == 3) {
                        yOrColumnX = yOrColumnX - 2;
                    } else if (index == 4) {
                        yOrColumnX = yOrColumnX + 2;
                    } else if (index == 12) {
                        yOrColumnX = yOrColumnX + 4;
                    } else if ((index == 13) || (index == 14)) {
                        yOrColumnX = yOrColumnX - 2;
                    }
                    blendStrengthOrPriceY = DAT_MenuHandlerState::instance.y + xOrRowY + 485;
                    fontSizeOrPriceX = DAT_MenuHandlerState::instance.x + yOrColumnX + 70;
                    int price = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getBuyPriceForOneUnit,
                        DAT_GameState::ptr)(resourceType);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(price,
                        fontSizeOrPriceX, blendStrengthOrPriceY, OpenSHC::Text::TTA_LEFT, 12775659, 0, 18, FALSE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)("/", DAT_MenuHandlerState::instance.x + 70 + yOrColumnX,
                        DAT_MenuHandlerState::instance.y + 485 + xOrRowY, OpenSHC::Text::TTA_LEFT, 12775659, 0, 18,
                        TRUE, 0);
                    blendStrengthOrPriceY = DAT_MenuHandlerState::instance.y + xOrRowY + 485;
                    fontSizeOrPriceX = DAT_MenuHandlerState::instance.x + yOrColumnX + 70;
                    price = MACRO_CALL_MEMBER(
                        OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(resourceType);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(price,
                        fontSizeOrPriceX, blendStrengthOrPriceY, OpenSHC::Text::TTA_LEFT, 12775659, 0, 18, TRUE, 0);
                }
            }
        }
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
