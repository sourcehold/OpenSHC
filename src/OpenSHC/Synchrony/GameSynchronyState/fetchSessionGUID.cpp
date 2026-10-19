#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E010
    void GameSynchronyState::fetchSessionGUID(GUID* pGUID)
    {
        GUID* pGVar1;
        if ((this->scrollBarIndex != -1)
            && (this->scrollBarIndex + this->scrollBarItemOffset < this->DPLAY_SessionsCount)) {
            pGVar1 = this->DPLAY_SessionGUIDs[this->scrollBarIndex + this->scrollBarItemOffset];
            *pGUID = *pGVar1;
        }
    }

}
}
