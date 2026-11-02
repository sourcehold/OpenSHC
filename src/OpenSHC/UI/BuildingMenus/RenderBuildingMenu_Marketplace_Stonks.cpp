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
        char* textAddress;
        ResourceType iconType;
        int price;
        int xOrRowY;
        TextAlignment alignment;
        BGR24 color;
        int fontSizeOrPriceX;
        BOOLEnum keepOffsetXOrTradeable;
        int blendStrengthOrPriceY;
        int index;
        ResourceType resourceType;
        blendStrengthOrPriceY = 0;
        keepOffsetXOrTradeable = FALSE;
        fontSizeOrPriceX = 0x12;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        int yOrColumnX = DAT_MenuHandlerState::instance.y + 0x1d4;
        xOrRowY = DAT_MenuHandlerState::instance.x + 0x19;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        // "Here's what I sell and what they cost."
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_TRADEPOST, 1),
            xOrRowY, yOrColumnX, alignment, color, fontSizeOrPriceX, keepOffsetXOrTradeable, blendStrengthOrPriceY);
        for (index = 0; index < 20; ++index) {
            resourceType = (OpenSHC::Game::Resources::ResourceType)(DAT_MarketStonksOrder::instance[index]);
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
                yOrColumnX = yOrColumnX * 0x2f;
                keepOffsetXOrTradeable = MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::isResourceTypeTradeable, DAT_GameState::ptr)(resourceType);
                if (keepOffsetXOrTradeable != FALSE) {
                    iconType = resourceType;
                    if (resourceType == OpenSHC::Game::Resources::RT_PITCH) {
                        iconType = OpenSHC::Game::Resources::RT_PARTIALPITCH;
                    }
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentResources[resourceType]
                        <= -100) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                            (int)(iconType * 2 + 0x2a), DAT_MenuHandlerState::instance.x + 0x42 + yOrColumnX,
                            DAT_MenuHandlerState::instance.y + 0x1bf + xOrRowY, 0x10);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                            (int)(iconType * 2 + 0x2a), DAT_MenuHandlerState::instance.x + 0x42 + yOrColumnX,
                            DAT_MenuHandlerState::instance.y + 0x1bf + xOrRowY);
                    }
                    if (index == 10) {
                        yOrColumnX = yOrColumnX - 10;
                    } else if (index == 0xb) {
                        yOrColumnX = yOrColumnX - 6;
                    } else if (index == 2) {
                        yOrColumnX = yOrColumnX + 4;
                    } else if (index == 3) {
                        yOrColumnX = yOrColumnX - 2;
                    } else if (index == 4) {
                        yOrColumnX = yOrColumnX + 2;
                    } else if (index == 0xc) {
                        yOrColumnX = yOrColumnX + 4;
                    } else if ((index == 0xd) || (index == 0xe)) {
                        yOrColumnX = yOrColumnX - 2;
                    }
                    blendStrengthOrPriceY = DAT_MenuHandlerState::instance.y + xOrRowY + 0x1e5;
                    fontSizeOrPriceX = DAT_MenuHandlerState::instance.x + yOrColumnX + 0x46;
                    price = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getBuyPriceForOneUnit,
                        DAT_GameState::ptr)(resourceType);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(price,
                        fontSizeOrPriceX, blendStrengthOrPriceY, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0, 0x12, FALSE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)("/", DAT_MenuHandlerState::instance.x + 0x46 + yOrColumnX,
                        DAT_MenuHandlerState::instance.y + 0x1e5 + xOrRowY, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0, 0x12,
                        TRUE, 0);
                    blendStrengthOrPriceY = DAT_MenuHandlerState::instance.y + xOrRowY + 0x1e5;
                    fontSizeOrPriceX = DAT_MenuHandlerState::instance.x + yOrColumnX + 0x46;
                    price = MACRO_CALL_MEMBER(
                        OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(resourceType);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(price,
                        fontSizeOrPriceX, blendStrengthOrPriceY, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0, 0x12, TRUE, 0);
                }
            }
        }
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
