#include "../ReceiveMapFrom.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AC4C0
        void ReceiveMapFrom::MenuModalRenderFunction_ReceiveMapFrom(int x, int y, int width, int height)
        {
            /*
              added by script: "Receiving Map"
             */
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner, DAT_PencilRenderCore::ptr)(
                0x4f, 0x6b, x, y, width, height);
            int iVar1 = width / 4;
            int left = x + iVar1;
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                left + -1, y + 0x5a, (width * 3 / 4) + 1 + x, y + 0x6d, (ushort)(COL_BLACK::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(left,
                y + 0x5b,
                ((width / 2) * DAT_GameSynchronyState::instance.mapSendingByteBufferAddress[0])
                        / DAT_GameSynchronyState::instance.mapSendingFileSize
                    + iVar1 + x,
                y + 0x6c, (ushort)(COL_DARK_LIME::instance.shortValue));
            return;
        }

    }
}
}
