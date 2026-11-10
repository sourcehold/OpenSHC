#include "../EditScenario.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
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
        namespace EditScenario {

            // FUNCTION: STRONGHOLDCRUSADER 0x004BAC20
            void MenuItemRenderFunction_EditScenario_StartDateMonth(int param_1, ...)
            {
                MACRO_CALL_MEMBER(Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                // One call per colour (one call with a colour local: quick_diff 0.9062 -> 0.5373)
                // y, x, then the month, in each branch (once, before the test: quick_diff 0.9062 -> 0.8438)
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    int const textY = DAT_ButtonY::instance + 6;
                    int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    // The month's full name, read last (first: quick_diff 0.9062 -> 0.6970; in the call: 0.6857)
                    int const monthTextIndex = DAT_MapPropertiesState::instance.SEC_StartingMonth + 12;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MONTHS, monthTextIndex),
                        textX, textY, Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                    return;
                }
                int const textY = DAT_ButtonY::instance + 6;
                int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                int const monthTextIndex = DAT_MapPropertiesState::instance.SEC_StartingMonth + 12;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_MONTHS, monthTextIndex),
                    textX, textY, Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
            }

        }
    }
}
}
