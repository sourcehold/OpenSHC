#include "../ReceiveMapFrom.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

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
            // "Receiving Map"
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 107, x, y, width, height);
            y += 10;
            int const left = x + width / 4;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                left - 1, y + 80, width * 3 / 4 + 1 + x, y + 99, COL_BLACK::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                left, y + 81,
                ((width / 2) * DAT_GameSynchronyState::instance.mapSendingByteBufferAddress[0])
                        / DAT_GameSynchronyState::instance.mapSendingFileSize
                    + width / 4 + x,
                y + 98, COL_DARK_LIME::instance.shortValue);
        }

    }
}
}
