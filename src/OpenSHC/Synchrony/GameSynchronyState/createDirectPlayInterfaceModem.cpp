#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Synchrony.func.hpp"

#include "OpenSHC/Globals/GUID_DPSPGUID_MODEM.hpp"
#include "OpenSHC/Globals/GUID_IID_IDirectPlay4A.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004874B0
    void GameSynchronyState::createDirectPlayInterfaceModem()
    {
        LPDIRECTPLAY directPlay = NULL;
        IDirectPlay4A* directPlay4A = NULL;
        DWORD addressSize = 0;
        GUID modemGuid = GUID_DPSPGUID_MODEM::instance;
        if (FAILED(DirectPlayCreate(&modemGuid, &directPlay, NULL))) {
            return;
        }
        HRESULT result = directPlay->QueryInterface(GUID_IID_IDirectPlay4A::instance, (LPVOID*)&directPlay4A);
        if (FAILED(result)) {
            directPlay->Release();
            return;
        }
        // The first call only asks for the size of the player address.
        result = directPlay4A->GetPlayerAddress(0, NULL, &addressSize);
        if (result != DPERR_BUFFERTOOSMALL) {
            directPlay->Release();
            directPlay4A->Release();
            return;
        }
        void* const address = GlobalLock(GlobalAlloc(GHND, addressSize));
        if (address == NULL) {
            directPlay->Release();
            directPlay4A->Release();
            return;
        }
        result = directPlay4A->GetPlayerAddress(0, address, &addressSize);
        if (SUCCEEDED(result)) {
            this->DPLAYX_LOBBY->EnumAddress(
                (LPDPENUMADDRESSCALLBACK)MACRO_CALL(Synchrony_Func::DirectPlayModemRelated_MemoryAllocationCallback),
                address, addressSize, NULL);
        }
        directPlay->Release();
        directPlay4A->Release();
        GlobalUnlock(GlobalHandle(address));
        GlobalFree(GlobalHandle(address));
    }

}
}
