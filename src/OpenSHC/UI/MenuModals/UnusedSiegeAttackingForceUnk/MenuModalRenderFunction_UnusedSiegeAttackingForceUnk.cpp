#include "../UnusedSiegeAttackingForceUnk.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace UnusedSiegeAttackingForceUnk {

            // FUNCTION: STRONGHOLDCRUSADER 0x004AB510
            void MenuModalRenderFunction_UnusedSiegeAttackingForceUnk(int x, int y, int width, int height)
            {
                // "Attacking Force"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 164, x, y, width, height);
            }

        }
    }
}
}
