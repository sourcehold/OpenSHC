#include "../GameSynchronyState.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E010
    void GameSynchronyState::fetchSessionGUID(GUID* pGUID)
    {
        if ((this->scrollBarIndex != -1)
            && (this->scrollBarIndex + this->scrollBarItemOffset < this->DPLAY_SessionsCount)) {
            *pGUID = *this->DPLAY_SessionGUIDs[this->scrollBarIndex + this->scrollBarItemOffset];
        }
    }

}
}
