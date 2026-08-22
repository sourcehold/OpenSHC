

#include "OpenSHC/UI.func.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004abd10
    void __cdecl MenuModalRenderFunction_TutorialBox_Thunk(int x, int y, int width, int height)
    {
        MACRO_CALL(UI_Func::MenuModalRenderFunction_TutorialBox)(x, y, width, height);
    }

} // namespace UI
} // namespace OpenSHC
