#include "../TutorialBox.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004BD0F0
        void TutorialBox::MenuItemRenderFunction_TutorialBox_Main(int param_1, ...)
        {
            int xParam;
            char* textAddress;
            int yParam;
            int numInGroup;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            numInGroup = 1;
            if (DAT_00df5540::instance == 0) {
                if (param_1 == 2) {
                    numInGroup = 2;
                } else {
                    if (DAT_00df5560::instance == 0) {}
                    if (((DAT_00df5558::instance < DAT_00df555c::instance + -1)
                            && (DAT_SoundSystemState::instance.waveOutOpenUnk_0x8 != FALSE))
                        && (DAT_SoundSystemState::instance.soundActiveUnk_0x0 != 0)) {
                        numInGroup = 5;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                blendStrength = 0;
                xParam = (DAT_ButtonW::instance >> 1) + DAT_ButtonX::instance;
                yParam = DAT_ButtonY::instance + 8;
                keepOffsetX = FALSE;
                fontSize = 0x12;
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    color = 0xc2f0eb;
                } else {
                    color = 0xccfaff;
                }
                alignment = OpenSHC::Text::TTA_CENTER;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TUTORIAL_BUTTONS, numInGroup), xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
            }
        }

    }
}
}
