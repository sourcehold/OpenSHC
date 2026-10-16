#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/GUID_DPSPGUID_TCPIP.hpp"

namespace OpenSHC {
namespace Synchrony {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047D4A0
    void GameSynchronyState::getGUIDForSelectedProvider(GUID* param_1)
    {
        GUID* pGVar1;
        if (this->useTCPIP) {
            /*
              fixme: include check for steam provider
             */
            /* DirectPlay TCP/IP service provider {36E95EE0-8577-11CF-960C-0080C7534E82} */
            *param_1 = GUID_DPSPGUID_TCPIP::instance;
            return;
        }
        pGVar1 = this->guids[this->selectedProviderIndex + this->scrollBarItemOffset];
        *param_1 = *pGVar1;
    }

}
}
