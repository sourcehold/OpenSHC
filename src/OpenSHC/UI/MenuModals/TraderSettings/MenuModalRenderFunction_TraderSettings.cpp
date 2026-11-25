#include "../TraderSettings.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace TraderSettings {

            // FUNCTION: STRONGHOLDCRUSADER 0x004AB4B0
            void MenuModalRenderFunction_TraderSettings(int x, int y, int width, int height)
            {
                // "Trader"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 38, x, y, width, height);
            }

        }
    }
}
}
