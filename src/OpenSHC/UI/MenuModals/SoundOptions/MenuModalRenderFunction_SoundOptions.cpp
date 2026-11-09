#include "../SoundOptions.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace SoundOptions {

            // FUNCTION: STRONGHOLDCRUSADER 0x00492660
            void MenuModalRenderFunction_SoundOptions(int x, int y, int width, int height)
            {
                // "Sound Options"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 5, x, y, width, height);
            }

        }
    }
}
}
