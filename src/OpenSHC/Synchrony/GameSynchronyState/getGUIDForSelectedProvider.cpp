#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/GUID_DPSPGUID_TCPIP.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047D4A0
    void GameSynchronyState::getGUIDForSelectedProvider(GUID* guid)
    {
        if (this->useTCPIP) {
            *guid = GUID_DPSPGUID_TCPIP::instance;
            return;
        }
        *guid = *this->guids[this->selectedProviderIndex + this->scrollBarItemOffset];
    }

}
}
