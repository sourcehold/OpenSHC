#include "../MouseState.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x00472A90
    void MouseState::drawMouseBasedBox()
    {
        if (!DAT_MouseState::instance.field31_0x94) {
            return;
        }
        if (!DAT_MouseState::instance.leftClickState && !DAT_MouseState::instance.draggingStopped) {
            MACRO_CALL_MEMBER(MouseState_Func::resetMouseCursorState, this)();
            return;
        }
        int left = this->previousSelectionBox.left;
        int right = this->previousSelectionBox.right;
        int top = this->previousSelectionBox.top;
        int bottom = this->previousSelectionBox.bottom;

        DAT_PencilRenderCore::instance.surfaceTarget = Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
            left, top, right, bottom, COL_BLACK::instance.shortValue);

        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
            left + 1, top + 1, right + -1, bottom + -1, COL_WHITE::instance.shortValue);

        DAT_PencilRenderCore::instance.surfaceTarget = Rendering::Enums::RT_SCREEN_MENU;
    }

}
}
