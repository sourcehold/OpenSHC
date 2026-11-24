#include "../SkirmishConnectionOptions.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace SkirmishConnectionOptions {

            // FUNCTION: STRONGHOLDCRUSADER 0x004ABE50
            void MenuModalRenderFunction_SkirmishConnectionOptions(int x, int y, int width, int height)
            {
                // "Connection options"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 93, x, y, width, height);
            }

        }
    }
}
}
