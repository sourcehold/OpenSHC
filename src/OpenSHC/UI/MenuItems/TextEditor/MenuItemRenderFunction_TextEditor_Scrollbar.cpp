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
            int const height = DAT_ButtonH::instance;
            int const y = DAT_ButtonY::instance;
            int const x = DAT_ButtonX::instance;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawScrollbar, DAT_PencilRenderCore::ptr)(
                x, y, height, thumbYPos, isDragged, thumbHeight, 0);
            int const right = x + 20;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x, y - 1, right - 1, y - 1, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            int const top = y - 22;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x, top, right - 1, top, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            int bottom = y + height;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x, bottom, right - 1, bottom, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            bottom = bottom + 21;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x, bottom, right - 1, bottom, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x - 1, top, x - 1, bottom, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                right, top, right, bottom, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
        }

    }
}
}
