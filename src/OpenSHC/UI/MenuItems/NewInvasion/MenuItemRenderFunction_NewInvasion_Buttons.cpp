#include "../NewInvasion.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BFA60
        void NewInvasion::MenuItemRenderFunction_NewInvasion_Buttons(int button, ...)
        {
            int invaderIndex = -1;
            switch (button) {
            case 9:
            case 91:
            case 221:
                invaderIndex = 0;
                break;
            case 10:
            case 92:
            case 222:
                invaderIndex = 1;
                break;
            case 11:
            case 93:
                invaderIndex = 2;
                break;
            case 12:
            case 94:
                invaderIndex = 3;
                break;
            case 87:
            case 95:
                invaderIndex = 4;
                break;
            case 96:
                invaderIndex = 5;
                break;
            case 97:
                invaderIndex = 6;
                break;
            case 98:
                invaderIndex = 7;
                break;
            case 99:
                invaderIndex = 8;
                break;
            case 157:
                invaderIndex = 9;
                break;
            case 158:
                invaderIndex = 10;
                break;
            case 159:
                invaderIndex = 11;
                break;
            case 160:
                invaderIndex = 12;
                break;
            case 161:
                invaderIndex = 13;
                break;
            case 162:
                invaderIndex = 14;
                break;
            }
            switch (button) {
            case -1:
                // the event's month, in full
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MONTHS,
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .header.month
                            + 12,
                        DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MONTHS,
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .header.month
                        + 12,
                    DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                    OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                return;
            case 9:
            case 10:
            case 11:
            case 12:
            case 87:
            case 221:
            case 222:
                // the invader: rat, snake, pig, wolf, other, crusader or arabian
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.invasion.crusaderArabian
                    == invaderIndex) {
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    // y before x: x first, or both written in the call, loses the match
                    int const textY = DAT_ButtonY::instance + 6;
                    int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, button),
                        textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                    return;
                }
                break;
            }
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(button);
        }

    }
}
}
