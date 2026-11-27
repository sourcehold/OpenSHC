#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_FoodTypes.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Game::Resources::ResourceTypeInt;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043D070
    void BuildingMenus::RenderBuildingMenu_Marketplace_Food()
    {
        int titleY = DAT_MenuHandlerState::instance.y + 468;
        int titleX = DAT_MenuHandlerState::instance.x + 25;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_TRADEPOST, 2),
            titleX, titleY, OpenSHC::Text::TTA_LEFT, 0, 17, FALSE, 0);
        int offset = 0;
        for (int i = 0; i < 8; ++i) {
            ResourceType resourceType = (ResourceType)DAT_FoodTypes::instance[i];
            int x = DAT_MenuHandlerState::instance.x + offset + 120;
            if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::isResourceTypeTradeable, DAT_GameState::ptr)(
                    resourceType)
                != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[resourceType],
                    x, DAT_MenuHandlerState::instance.y + 562, OpenSHC::Text::TTA_CENTER, 0, 17, FALSE, 0);
            }
            offset += 52;
        }
    }

}
}
