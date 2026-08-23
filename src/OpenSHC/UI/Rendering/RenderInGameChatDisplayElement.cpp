#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004AF800
    void Rendering::RenderInGameChatDisplayElement(int posX, int posY, DWORD elementState)
    {
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::renderInGameChat, DAT_GameSynchronyState::ptr)(
            posX, posY, (int)((int)(elementState)));
    }

}
}
