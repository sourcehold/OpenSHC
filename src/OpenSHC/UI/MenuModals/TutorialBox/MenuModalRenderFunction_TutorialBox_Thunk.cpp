#include "OpenSHC/UI/MenuModals/TutorialBox.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace TutorialBox {

            // FUNCTION: STRONGHOLDCRUSADER 0x004abd10
            void MenuModalRenderFunction_TutorialBox_Thunk(int x, int y, int width, int height)
            {
                MACRO_CALL(OpenSHC::UI::MenuModals::TutorialBox_Func::MenuModalRenderFunction_TutorialBox)(
                    x, y, width, height);
            }

        }
    }
}
}
