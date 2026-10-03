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
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
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

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0043CE30
    void BuildingMenus::RenderBuildingMenu_Marketplace_Stonks()
    {
        char* textAddress;
        ResourceType RVar2;
        int iVar3;
        int iVar4;
        TextAlignment alignment;
        BGR24 color;
        int iVar5;
        BOOLEnum BVar6;
        int iVar7;
        int _index;
        ResourceType _resourceType;
        iVar7 = 0;
        BVar6 = FALSE;
        iVar5 = 0x12;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        int iVar1 = DAT_MenuHandlerState::instance.y + 0x1d4;
        iVar4 = DAT_MenuHandlerState::instance.x + 0x19;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        /*
          added by script: "Here's what I sell and what they cost."
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_TRADEPOST, 1), iVar4, iVar1, alignment, color, iVar5, BVar6, iVar7);
        _index = 0;
        do {
            _resourceType = (OpenSHC::Game::Resources::ResourceType)(DAT_RenderingDefinedData::instance
                    .MarketStonksOrder[_index]);
            if (_resourceType != ((ResourceType)0)) {
                if (_index < 13) {
                    if (_index < 10) {
                        iVar4 = 40;
                        iVar1 = _index;
                    } else {
                        iVar4 = 100;
                        iVar1 = _index + -10;
                    }
                } else {
                    iVar4 = 100;
                    iVar1 = _index + -0xb;
                }
                iVar1 = iVar1 * 0x2f;
                BVar6 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::isResourceTypeTradeable,
                    DAT_GameState::ptr)(_resourceType);
                if (BVar6 != FALSE) {
                    RVar2 = _resourceType;
                    if (_resourceType == OpenSHC::Game::Resources::RT_PITCH) {
                        RVar2 = OpenSHC::Game::Resources::RT_PARTIALPITCH;
                    }
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentResources[_resourceType]
                        < -99) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                            (int)(RVar2 * 2 + 0x2a), DAT_MenuHandlerState::instance.x + 0x42 + iVar1,
                            DAT_MenuHandlerState::instance.y + 0x1bf + iVar4, 0x10);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                            (int)(RVar2 * 2 + 0x2a), DAT_MenuHandlerState::instance.x + 0x42 + iVar1,
                            DAT_MenuHandlerState::instance.y + 0x1bf + iVar4);
                    }
                    if (_index == 10) {
                        iVar1 = iVar1 + -10;
                    } else if (_index == 0xb) {
                        iVar1 = iVar1 + -6;
                    } else if (_index == 2) {
                        iVar1 = iVar1 + 4;
                    } else if (_index == 3) {
                        iVar1 = iVar1 + -2;
                    } else if (_index == 4) {
                        iVar1 = iVar1 + 2;
                    } else if (_index == 0xc) {
                        iVar1 = iVar1 + 4;
                    } else if ((_index == 0xd) || (_index == 0xe)) {
                        iVar1 = iVar1 + -2;
                    }
                    iVar7 = DAT_MenuHandlerState::instance.y + 0x1e5;
                    iVar5 = DAT_MenuHandlerState::instance.x + 0x46;
                    iVar3 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getBuyPriceForOneUnit,
                        DAT_GameState::ptr)(_resourceType);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                        iVar3, iVar5 + iVar1, iVar7 + iVar4, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0, 0x12, FALSE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)("/", DAT_MenuHandlerState::instance.x + 0x46 + iVar1,
                        DAT_MenuHandlerState::instance.y + 0x1e5 + iVar4, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0, 0x12,
                        TRUE, 0);
                    iVar7 = DAT_MenuHandlerState::instance.y + 0x1e5;
                    iVar5 = DAT_MenuHandlerState::instance.x + 0x46;
                    iVar3 = MACRO_CALL_MEMBER(
                        OpenSHC::Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(_resourceType);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                        iVar3, iVar5 + iVar1, iVar7 + iVar4, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0, 0x12, TRUE, 0);
                }
            }
            _index = _index + 1;
            if (0x13 < _index) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
        } while (true);
    }

}
}
