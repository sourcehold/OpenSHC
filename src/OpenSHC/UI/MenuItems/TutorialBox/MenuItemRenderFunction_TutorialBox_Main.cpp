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
        void TutorialBox::MenuItemRenderFunction_TutorialBox_Main(int button, ...)
        {
            // "Continue"
            int buttonText = 1;
            if (DAT_00df5540::instance != 0) {
                return;
            }
            if (button == 2) {
                // "Exit"
                buttonText = 2;
            } else {
                if (!DAT_00df5560::instance) {
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
            // the position in each path, which MSVC hoists the way the original does (above the if: 100.0% -> 97.9%)
            if (DAT_ButtonCurrentlyInteracting::instance) {
                // >> 1: the original halves without the sign fix-up (/ 2: 100.0% -> 93.9%)
                int const textX = (DAT_ButtonW::instance >> 1) + DAT_ButtonX::instance;
                int const textY = DAT_ButtonY::instance + 8;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TUTORIAL_BUTTONS, buttonText),
                    textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                return;
            }
            int const textX = (DAT_ButtonW::instance >> 1) + DAT_ButtonX::instance;
            int const textY = DAT_ButtonY::instance + 8;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TUTORIAL_BUTTONS, buttonText),
                textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
        }

    }
}
}
