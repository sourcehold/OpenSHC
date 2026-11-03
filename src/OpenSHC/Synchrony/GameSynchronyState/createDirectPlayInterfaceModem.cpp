#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Synchrony.func.hpp"

#include "OpenSHC/Globals/GUID_DPSPGUID_MODEM.hpp"
#include "OpenSHC/Globals/GUID_IID_IDirectPlay4A.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004874B0
    void GameSynchronyState::createDirectPlayInterfaceModem()
    {
        IDirectPlay4A* directPlay = NULL;
        IDirectPlay4A* directPlay4A = NULL;
        DWORD addressSize = 0;
        // GUID for the modem service provider
        GUID modemGuid = GUID_DPSPGUID_MODEM::instance;
        if (DirectPlayCreate(&modemGuid, (LPDIRECTPLAY*)&directPlay, 0) < 0) {
            return;
        }
        HRESULT result = directPlay->QueryInterface(GUID_IID_IDirectPlay4A::instance, (LPVOID*)&directPlay4A);
        if (result < 0) {
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
        HGLOBAL const addressMemory = GlobalAlloc(GHND, addressSize);
        void* const address = GlobalLock(addressMemory);
        if (address == NULL) {
            directPlay->Release();
            directPlay4A->Release();
            return;
        }
        result = directPlay4A->GetPlayerAddress(0, address, &addressSize);
        if (0 <= result) {
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
