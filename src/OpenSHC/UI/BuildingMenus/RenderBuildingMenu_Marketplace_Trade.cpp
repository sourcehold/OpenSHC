#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
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
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Game::Resources::ResourceTypeInt;
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
    // FUNCTION: STRONGHOLDCRUSADER 0x0043D280
    void BuildingMenus::RenderBuildingMenu_Marketplace_Trade()
    {
        ResourceTypeInt RVar1
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .marketSelectedResourceType;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        ResourceType RVar4 = (OpenSHC::Game::Resources::ResourceType)(RVar1);
        if (RVar1 == OpenSHC::Game::Resources::RT_PITCH) {
            RVar4 = OpenSHC::Game::Resources::RT_PARTIALPITCH;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, (int)(RVar4 + ((ResourceType)0x62)),
            DAT_RenderingDefinedData::instance.field1048_0x55604[RVar1].x + 0x55 + DAT_MenuHandlerState::instance.x,
            DAT_RenderingDefinedData::instance.field1048_0x55604[RVar1].y + 0x20a + DAT_MenuHandlerState::instance.y);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .currentResources[DAT_GameState::instance
                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .marketSelectedResourceType],
            DAT_MenuHandlerState::instance.x + 0x98, DAT_MenuHandlerState::instance.y + 0x1fe, OpenSHC::Text::TTA_LEFT,
            0, 0x11, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x71, DAT_MenuHandlerState::instance.x + 0x1a4,
            DAT_MenuHandlerState::instance.y + 0x219);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .currentResources[0xf],
            DAT_MenuHandlerState::instance.x + 0x1b8, DAT_MenuHandlerState::instance.y + 0x1fe, OpenSHC::Text::TTA_LEFT,
            0, 0x11, FALSE, 0);
        BOOLEnum BVar2 = MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::anyGoodsAreAllowedForSale, DAT_GameState::ptr)();
        if (BVar2 != FALSE) {
            int iVar3 = MACRO_CALL_MEMBER(
                OpenSHC::Game::GameStateStructures_Func::getPreviousGoodsFilteringUnallowed, DAT_GameState::ptr)(RVar4);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar3 * 2 + 0x2a,
                DAT_MenuHandlerState::instance.x + 0x14, DAT_MenuHandlerState::instance.y + 0x1d4);
            iVar3 = MACRO_CALL_MEMBER(
                OpenSHC::Game::GameStateStructures_Func::getNextGoodFilteringUnallowed, DAT_GameState::ptr)(RVar4);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar3 * 2 + 0x2a,
                DAT_MenuHandlerState::instance.x + 0x90, DAT_MenuHandlerState::instance.y + 0x1d4);
        }
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
