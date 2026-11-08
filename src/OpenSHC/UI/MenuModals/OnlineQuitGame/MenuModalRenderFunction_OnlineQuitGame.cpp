#include "../OnlineQuitGame.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace OnlineQuitGame {

            // FUNCTION: STRONGHOLDCRUSADER 0x004937B0
            void MenuModalRenderFunction_OnlineQuitGame(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 7, x, y, width, height);
            }

        }
    }
}
}
