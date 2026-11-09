#include "../UnusedChooseMessageBox.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AB460
        void UnusedChooseMessageBox::MenuModalRenderFunction_UnusedChooseMessageBox(int x, int y, int width, int height)
        {
            // "Select Message"
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner, DAT_PencilRenderCore::ptr)(
                199, 40, x, y, width, height);
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                x + 25, y + 100, x + 595, y + 370);
        }

    }
}
}
