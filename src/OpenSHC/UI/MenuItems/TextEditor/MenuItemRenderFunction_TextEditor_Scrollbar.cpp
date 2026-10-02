#include "../TextEditor.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0045EF90
        void TextEditor::MenuItemRenderFunction_TextEditor_Scrollbar(
            int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged)
        {
            int y1;
            uint x1;
            int iVar1;
            int iVar2;
            int x2;
            iVar1 = DAT_ButtonH::instance;
            iVar2 = DAT_ButtonY::instance;
            x1 = DAT_ButtonX::instance;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawScrollbar, DAT_PencilRenderCore::ptr)(
                DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)), (int)((int)(DAT_ButtonH::instance)),
                thumbYPos, isDragged, thumbHeight, 0);
            x2 = x1 + 0x13;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, iVar2 + -1, x2, iVar2 + -1, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            y1 = iVar2 + -0x16;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y1, x2, y1, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            iVar2 = iVar2 + iVar1;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, iVar2, x2, iVar2, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            iVar2 = iVar2 + 0x15;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, iVar2, x2, iVar2, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1 - 1, y1, (int)((int)(x1 - 1)), iVar2, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1 + 0x14, y1, (int)((int)(x1 + 0x14)), iVar2,
                (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
        }

    }
}
}
