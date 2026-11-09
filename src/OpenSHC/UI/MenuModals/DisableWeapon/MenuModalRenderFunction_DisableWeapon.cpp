#include "../DisableWeapon.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace DisableWeapon {

            // FUNCTION: STRONGHOLDCRUSADER 0x004ABCE0
            void MenuModalRenderFunction_DisableWeapon(int x, int y, int width, int height)
            {
                // "Weapons"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 189, x, y, width, height);
            }

        }
    }
}
}
