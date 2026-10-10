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
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawScrollbar, DAT_PencilRenderCore::ptr)(
                DAT_ButtonX::instance, (int)(DAT_ButtonY::instance), (int)(DAT_ButtonH::instance), thumbYPos, isDragged,
                thumbHeight, 0);
            x2 = x1 + 0x13;
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, iVar2 + -1, x2, iVar2 + -1, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            y1 = iVar2 + -0x16;
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y1, x2, y1, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            iVar2 = iVar2 + iVar1;
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, iVar2, x2, iVar2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            iVar2 = iVar2 + 0x15;
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, iVar2, x2, iVar2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1 - 1, y1, (int)(x1 - 1), iVar2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1 + 0x14, y1, (int)(x1 + 0x14), iVar2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
        }

    }
}
}
