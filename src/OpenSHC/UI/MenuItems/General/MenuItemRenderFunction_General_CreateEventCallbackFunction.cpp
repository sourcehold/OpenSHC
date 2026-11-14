#include "../General.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BBA60
        void General::MenuItemRenderFunction_General_CreateEventCallbackFunction(int textNumInGroup, ...)
        {
            int option = -1;
            int iconOffset = 2;
            switch (textNumInGroup) {
            case 91:
            case 221:
                option = 0;
                break;
            case 92:
            case 222:
                option = 1;
                break;
            case 93:
                option = 2;
                break;
            case 94:
                option = 3;
                break;
            case 95:
                option = 4;
                break;
            case 96:
                option = 5;
                break;
            case 97:
                option = 6;
                break;
            case 98:
                option = 7;
                break;
            case 99:
                option = 8;
                break;
            case 157:
                option = 9;
                break;
            case 158:
                option = 10;
                break;
            case 159:
                option = 11;
                break;
            case 160:
                option = 12;
                break;
            case 161:
                option = 13;
                break;
            case 162:
                option = 14;
                break;
            }
            switch (textNumInGroup) {
            case 221:
            case 222:
                if (DAT_MapPropertiesState::instance.invasionEventContent.crusaderArabian == option) {
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, textNumInGroup,
                        DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                    return;
                }
                break;
            case 148:
                // drawn as the bandits button with the other icon
                textNumInGroup = 146;
                iconOffset = 0;
                // fall through
            case 146: {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                // "Bandits"; each path reads its own text position, y first, for the original's merged call
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    int const textY = DAT_ButtonY::instance + 6;
                    int const textX = DAT_ButtonW::instance / 2 - 15 + DAT_ButtonX::instance;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, textNumInGroup),
                        textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                } else {
                    int const textY = DAT_ButtonY::instance + 6;
                    int const textX = DAT_ButtonW::instance / 2 - 15 + DAT_ButtonX::instance;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, textNumInGroup),
                        textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                }
                int const nameWidth = DAT_TextManagerObject::instance.currentXOffset_0x0;
                // " - "
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    s___005a2304, nameWidth / 2 - 15 + DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                    DAT_ButtonY::instance + 6, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18,
                    FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iconOffset + 128,
                    DAT_ButtonW::instance / 2 - 9 + (DAT_TextManagerObject::instance.currentXOffset_0x0 + nameWidth) / 2
                        + DAT_ButtonX::instance,
                    DAT_ButtonY::instance + 3);
                return;
            }
            }
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(textNumInGroup);
        }

    }
}
}
