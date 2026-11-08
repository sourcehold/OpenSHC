#include "../EnterTitleOnGameStart.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace EnterTitleOnGameStart {

            // FUNCTION: STRONGHOLDCRUSADER 0x00491BF0
            void MenuModalRenderFunction_EnterTitleOnGameStart(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 6, x, y, width, height);
            }

        }
    }
}
}
