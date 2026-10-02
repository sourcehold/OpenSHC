#include "../OverlaySlider.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/COL_GREYISH_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x004AA800
        void OverlaySlider::MenuItemRenderFunction_OverlaySlider_Slider(
            int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged)
        {
            int iVar1;
            char* pcVar2;
            int iVar3;
            TextAlignment TVar4;
            BGR24 BVar5;
            int iVar6;
            BOOLEnum BVar7;
            undefined2 color;
            int iVar8;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)),
                (int)((int)(DAT_ButtonW::instance + DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonH::instance + DAT_ButtonY::instance)), 0xc);
            if (-1 < DAT_MenuModalComposition2::instance.textGroup) {
                iVar8 = 0;
                BVar7 = FALSE;
                iVar6 = 0x13;
                BVar5 = 0xc2f0eb;
                TVar4 = OpenSHC::Text::TTA_CENTER;
                iVar1 = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                iVar3 = DAT_ButtonY::instance + 4;
                pcVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    (OpenSHC::DE::SHCDE::eTextSections)DAT_MenuModalComposition2::instance.textGroup,
                    DAT_MenuModalComposition2::instance.textIndex);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar2, iVar1, iVar3, TVar4, BVar5, iVar6, BVar7, iVar8);
            }
            color = COL_DARK_LIME::instance.shortValue;
            if (isDragged == 0) {
                color = COL_GREYISH_YELLOW::instance.shortValue;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                DAT_ButtonX::instance + thumbYPos, (int)((int)(DAT_ButtonY::instance)),
                DAT_ButtonX::instance + thumbYPos + thumbHeight,
                (int)((int)(DAT_ButtonH::instance + DAT_ButtonY::instance)), (ushort)((int)(color)));
            if ((thumbHeight == DAT_ButtonW::instance) && (-1 < DAT_MenuModalComposition2::instance.textGroup)) {
                iVar8 = 0;
                BVar7 = FALSE;
                iVar6 = 0x13;
                BVar5 = 0xccfaff;
                TVar4 = OpenSHC::Text::TTA_CENTER;
                iVar1 = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                iVar3 = DAT_ButtonY::instance + 4;
                pcVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    (OpenSHC::DE::SHCDE::eTextSections)DAT_MenuModalComposition2::instance.textGroup,
                    DAT_MenuModalComposition2::instance.textIndex);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar2, iVar1, iVar3, TVar4, BVar5, iVar6, BVar7, iVar8);
            }
        }

    }
}
}
