#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_TextEditorState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace DisplayScenarioHelpText {

            // FUNCTION: STRONGHOLDCRUSADER 0x0045F120
            void MenuItemRenderFunction_DisplayScenarioHelpText_AnotherButtonUnk(int param_1, ...)
            {
                if (DAT_TextEditorState::instance.helpSectionHistoryStack[0] != -1) {
                    MACRO_CALL(OpenSHC::UI_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                }
            }

        }
    }
}
}
