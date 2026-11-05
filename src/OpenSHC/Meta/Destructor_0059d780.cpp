#include "../Meta.func.hpp"

#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"

#include "OpenSHC/Globals/DAT_TextEditorState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D780
void Meta::Destructor_0059d780()
{
    MACRO_CALL_MEMBER(UI::Rendering::AlphaAndButtonSurface_Func::freeMemory,
        (UI::Rendering::AlphaAndButtonSurface*)DAT_TextEditorState::ptr)();
}

}
