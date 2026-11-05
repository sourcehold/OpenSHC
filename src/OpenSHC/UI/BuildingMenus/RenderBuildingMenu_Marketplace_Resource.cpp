#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_RawResourceTypes.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043D120
    void BuildingMenus::RenderBuildingMenu_Marketplace_Resource()
    {
        int titleY = DAT_MenuHandlerState::instance.y + 468;
        int titleX = DAT_MenuHandlerState::instance.x + 25;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_TRADEPOST, 3),
            titleX, titleY, OpenSHC::Text::TTA_LEFT, 0, 17, FALSE, 0);
        int offset = 0;
        for (int i = 0; i < 4; ++i) {
            ResourceType resourceType = (ResourceType)DAT_RawResourceTypes::instance[i];
            int x = DAT_MenuHandlerState::instance.x + offset + 151;
            if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::isResourceTypeTradeable, DAT_GameState::ptr)(
                    resourceType)
                != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[resourceType],
                    x, DAT_MenuHandlerState::instance.y + 562, OpenSHC::Text::TTA_CENTER, 0, 17, FALSE, 0);
            }
            offset += 104;
        }
    }

}
}
