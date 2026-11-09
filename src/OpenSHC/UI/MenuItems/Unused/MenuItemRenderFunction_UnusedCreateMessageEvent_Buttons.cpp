#include "../Unused.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BA980
        void Unused::MenuItemRenderFunction_UnusedCreateMessageEvent_Buttons(int button, ...)
        {
            DAT_ButtonUnknownZero::instance = FALSE;
            // The message library: buttons 4 to 8 open its pages, "Tutor" to "Characters".
            // On "Characters" the faces 1009 to 1012 stand in for buttons 9 to 12; on the other pages they are off.
            if (DAT_MapPropertiesState::instance.field_0x13590 == 4) {
                if (button == 9 || button == 10 || button == 11 || button == 12) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
            } else if (button == 1009 || button == 1010 || button == 1011 || button == 1012) {
                DAT_ButtonUnknownZero::instance = TRUE;
                return;
            }
            // the open page's button and the entries chosen on pages 3 and 4 are drawn highlighted
            if ((button <= 8 && button - 4 == DAT_MapPropertiesState::instance.field_0x13590)
                || (DAT_MapPropertiesState::instance.field_0x13590 == 4
                    && (((button <= 12 || button > 1000)
                            && button - 1009 == DAT_MapPropertiesState::instance.field_0x13594)
                        || button - 13 == DAT_MapPropertiesState::instance.field_0x13598))
                || (DAT_MapPropertiesState::instance.field_0x13590 == 3 && button <= 12
                    && button - 8 == DAT_MapPropertiesState::instance.field_0x13594)) {
                // on "Adviser Prompts" buttons 9 and 10 are "Civil" and "Military", 11 and 12 are off
                if (DAT_MapPropertiesState::instance.field_0x13590 == 3 && button >= 9) {
                    if (button == 9) {
                        button = 24;
                    } else if (button == 10) {
                        button = 25;
                    } else {
                        DAT_ButtonUnknownZero::instance = TRUE;
                        return;
                    }
                }
                DAT_ButtonCurrentlyInteracting::instance = TRUE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                if (DAT_MapPropertiesState::instance.field_0x13590 == 4
                    && (button == 1009 || button == 1010 || button == 1011 || button == 1012)) {
                    // a character's face above its name
                    button -= 1000;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ENEMY_FACES, button - 8,
                        DAT_ButtonW::instance / 2 - 32 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7);
                    DAT_ButtonY::instance += 72;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SCENARIO, button, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                    DAT_ButtonY::instance + 6, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18,
                    FALSE);
                return;
            }
            // pages 0 to 2 have no buttons past 8, page 3 none past 12
            if (DAT_MapPropertiesState::instance.field_0x13590 < 3 && button >= 9) {
                return;
            }
            if (DAT_MapPropertiesState::instance.field_0x13590 < 4 && button >= 13) {
                return;
            }
            if (DAT_MapPropertiesState::instance.field_0x13590 == 3 && button >= 9) {
                if (button == 9) {
                    button = 24;
                } else if (button == 10) {
                    button = 25;
                } else {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            if (DAT_MapPropertiesState::instance.field_0x13590 == 4
                && (button == 1009 || button == 1010 || button == 1011 || button == 1012)) {
                button -= 1000;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ENEMY_FACES, button - 8,
                    DAT_ButtonW::instance / 2 - 32 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7);
                DAT_ButtonY::instance += 72;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (!DAT_ButtonCurrentlyInteracting::instance) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SCENARIO, button, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                    DAT_ButtonY::instance + 6, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18,
                    FALSE);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SCENARIO, button, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                    DAT_ButtonY::instance + 6, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18,
                    FALSE);
            }
        }

    }
}
}
