#include "../NetworkOptions.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace NetworkOptions {

            // FUNCTION: STRONGHOLDCRUSADER 0x00492A60
            void MenuModalRenderFunction_NetworkOptions(int x, int y, int width, int height)
            {
                // "Network Options"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 6, x, y, width, height);
            }

        }
    }
}
}
