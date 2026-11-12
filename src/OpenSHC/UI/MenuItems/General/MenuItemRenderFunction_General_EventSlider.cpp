#include "../General.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Game/ScenarioEvents/Enums/ScenarioEventType.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/COL_GREYISH_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BA3C0
        void General::MenuItemRenderFunction_General_EventSlider(
            int slider, int thumbYPos, int value, int thumbHeight, BOOL isDragged)
        {
            switch (slider) {
            case -2:
            case -1:
                // these two sliders belong to the events that have a duration
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
                    break;
                default:
                    return;
                }
                break;
            case 5:
            case 12:
            case 18:
            case 19:
            case 21:
                // the other sliders belong to the event one below their number
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType
                    != slider - 1) {
                    return;
                }
                break;
            }
            DAT_ButtonCurrentlyInteracting::instance = FALSE;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(-1, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            if (!isDragged) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + thumbYPos + 1, DAT_ButtonY::instance + 2,
                    DAT_ButtonX::instance + thumbYPos + thumbHeight - 2,
                    DAT_ButtonY::instance + DAT_ButtonH::instance - 4, COL_GREYISH_YELLOW::instance.shortValue);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + thumbYPos + 1, DAT_ButtonY::instance + 2,
                    DAT_ButtonX::instance + thumbYPos + thumbHeight - 2,
                    DAT_ButtonY::instance + DAT_ButtonH::instance - 4, COL_DARK_LIME::instance.shortValue);
            }
            if (slider == -2 && value == 10) {
                // "-"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(s___005a2280, DAT_ButtonX::instance + DAT_ButtonW::instance + 12,
                    DAT_ButtonY::instance + 6, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 18,
                    FALSE, 0);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(value,
                DAT_ButtonX::instance + DAT_ButtonW::instance + 12, DAT_ButtonY::instance + 6,
                OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 18, FALSE, 0);
        }

    }
}
}
