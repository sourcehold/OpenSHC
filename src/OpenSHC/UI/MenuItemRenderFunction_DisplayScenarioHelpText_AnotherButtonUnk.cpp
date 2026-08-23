#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_TextEditorState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0045F120
void UI::MenuItemRenderFunction_DisplayScenarioHelpText_AnotherButtonUnk(int param_1, va_list args)
{
    if (DAT_TextEditorState::instance.helpSectionHistoryStack[0] != -1) {
        MACRO_CALL(OpenSHC::UI_Func::
                MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
    }
}

}
