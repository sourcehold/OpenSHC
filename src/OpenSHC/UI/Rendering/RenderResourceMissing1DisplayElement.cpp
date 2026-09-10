#include "OpenSHC/Audio/MissingResourceState.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"

#include "OpenSHC/Globals/DAT_MissingResourceState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004AF820
    void Rendering::RenderResourceMissing1DisplayElement(int posX, int posY, DWORD elementState)
    {
        MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::renderResourceMissingText,
            DAT_MissingResourceState::ptr)(posX, posY, elementState, 1);
    }

}
}
