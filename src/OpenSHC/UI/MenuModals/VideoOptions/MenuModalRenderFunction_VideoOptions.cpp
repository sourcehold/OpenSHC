#include "../VideoOptions.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x00492120
        void VideoOptions::MenuModalRenderFunction_VideoOptions(int x, int y, int width, int height)
        {
            // "Video Options"
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner, DAT_PencilRenderCore::ptr)(
                OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 4, x, y, width, height);
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                x + 102, y + 213, x + 178, y + 252, 16);
        }

    }
}
}
