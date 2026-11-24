#include "../OptionsMenu.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace OptionsMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x00491810
            void MenuModalRenderFunction_OptionsMenu(int x, int y, int width, int height)
            {
                // "Game Options"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 1, x, y, width, height);
            }

        }
    }
}
}
