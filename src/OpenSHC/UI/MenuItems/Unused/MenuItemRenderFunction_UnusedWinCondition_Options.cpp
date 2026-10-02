#include "../Unused.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_GREYISH_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004AA970
        void Unused::MenuItemRenderFunction_UnusedWinCondition_Options(int param_1, ...)
        {
            int xParam;
            char* textAddress;
            int yParam;
            BGR24 color;
            TextAlignment alignment;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            if (param_1 < (int)DAT_MenuModalComposition1::instance.mbr_0x64) {
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    color = 0xc2f0eb;
                } else {
                    color = 0xccfaff;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)),
                        (int)((int)(DAT_ButtonW::instance + DAT_ButtonX::instance)),
                        (int)((int)(DAT_ButtonH::instance + DAT_ButtonY::instance)),
                        (ushort)((int)(COL_GREYISH_YELLOW::instance.shortValue)));
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)),
                    (int)((int)(DAT_ButtonW::instance + DAT_ButtonX::instance)),
                    (int)((int)((OpenSHC::DE::SHCDE::eTextSections)(DAT_ButtonH::instance + DAT_ButtonY::instance))),
                    0xc);
                blendStrength = 0;
                keepOffsetX = FALSE;
                fontSize = 0x13;
                alignment = OpenSHC::Text::TTA_CENTER;
                xParam = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                yParam = DAT_ButtonY::instance + 8;
                textAddress = MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    (OpenSHC::DE::SHCDE::eTextSections)DAT_MenuModalComposition1::instance.textGroup,
                    DAT_MenuModalComposition1::instance.textIndex + param_1);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    textAddress, xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
            }
        }

    }
}
}
