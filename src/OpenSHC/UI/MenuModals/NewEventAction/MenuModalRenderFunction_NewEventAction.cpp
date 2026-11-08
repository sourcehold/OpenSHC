#include "../NewEventAction.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/ScenarioEvents/Enums/ScenarioEventType.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004ABAB0
        void NewEventAction::MenuModalRenderFunction_NewEventAction(int x, int y, int width, int height)
        {
            // "Event Actions"
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 103, x, y, width, height);
            // the actions that repeat label their two fields
            switch (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.scenario.ScenarioEventType) {
            case OpenSHC::Game::ScenarioEvents::Enums::SET_TRAVELING_FAIR:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_PLAGUE:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_WHEAT_DISEASE:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_HOPS_WEEVIL:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_APPLE_BLIGHT:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_TREE_FUNGUS:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_RABBIT_EXPLOSION:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_LION_ATTACK:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_BANDITS:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_MAD_COWS:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_ARCHERS:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_THEFT_FROM_GRANARY:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_FIRE:
                // "Repeat (months)"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 175),
                    x + 390, y + 461, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                // "Repeat Count"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 176),
                    x + 390, y + 496, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                break;
            }
        }

    }
}
}
