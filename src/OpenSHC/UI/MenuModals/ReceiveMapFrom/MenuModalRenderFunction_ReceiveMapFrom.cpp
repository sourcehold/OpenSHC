#include "../ReceiveMapFrom.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004AC4C0
        void ReceiveMapFrom::MenuModalRenderFunction_ReceiveMapFrom(int x, int y, int width, int height)
        {
            int left;
            int iVar1;
            /*
              added by script: "Receiving Map"
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(0x4f, 0x6b, x, y, width, height);
            iVar1 = (int)(width + (width >> 0x1f & 3U)) >> 2;
            left = x + iVar1;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                left + -1, y + 0x5a, ((int)(width * 3 + (width * 3 >> 0x1f & 3U)) >> 2) + 1 + x, y + 0x6d,
                (ushort)((int)(COL_BLACK::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                left, y + 0x5b,
                ((width / 2) * DAT_GameSynchronyState::instance.mapSendingByteBufferAddress[0])
                        / DAT_GameSynchronyState::instance.mapSendingFileSize
                    + iVar1 + x,
                y + 0x6c, (ushort)((int)(COL_DARK_LIME::instance.shortValue)));
            return;
        }

    }
}
}
