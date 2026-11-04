#include "../TutorialBox.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_00df5540.hpp"
#include "OpenSHC/Globals/DAT_00df5558.hpp"
#include "OpenSHC/Globals/DAT_00df555c.hpp"
#include "OpenSHC/Globals/DAT_00df5560.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BD0F0
        void TutorialBox::MenuItemRenderFunction_TutorialBox_Main(int param_1, ...)
        {
            // "Continue"
            int buttonText = 1;
            if (DAT_00df5540::instance != 0) {
                return;
            }
            if (param_1 == 2) {
                // "Exit"
                buttonText = 2;
            } else {
                if (DAT_00df5560::instance == 0) {
                    return;
                }
                if (DAT_00df5558::instance < DAT_00df555c::instance - 1
                    && DAT_SoundSystemState::instance.waveOutOpenUnk_0x8
                    && DAT_SoundSystemState::instance.soundActiveUnk_0x0) {
                    // "Skip"
                    buttonText = 5;
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            // >> 1 rather than / 2: the original shifts without the sign fix-up (sar at 0x004BD160)
            int const textX = (DAT_ButtonW::instance >> 1) + DAT_ButtonX::instance;
            int const textY = DAT_ButtonY::instance + 8;
            if (DAT_ButtonCurrentlyInteracting::instance) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TUTORIAL_BUTTONS, buttonText),
                    textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TUTORIAL_BUTTONS, buttonText),
                textX, textY, OpenSHC::Text::TTA_CENTER, 12775659, 18, FALSE, 0);
        }

    }
}
}
