#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Synchrony.func.hpp"

#include "OpenSHC/Globals/GUID_DPSPGUID_MODEM.hpp"
#include "OpenSHC/Globals/GUID_IID_IDirectPlay4A.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004874B0
    void GameSynchronyState::createDirectPlayInterfaceModem()
    {
        void* _allocateMem;
        int* _allocateMemLock;
        void* pvVar4;
        int* piVar5;
        IDirectPlay4A* _interface;
        IDirectPlay4A* _refIDirectPlay;
        DWORD _playerAddress;
        GUID _guid;
        uint uVar1 = MSVC_SecurityCookie::instance ^ (uint)&_interface;
        /*
          GUID for modem service provider
         */
        _guid = GUID_DPSPGUID_MODEM::instance;
        _refIDirectPlay = (IDirectPlay4A*)0x0;
        _interface = (IDirectPlay4A*)0x0;
        _playerAddress = 0;
        int iVar2 = DirectPlayCreate(&_guid, (LPDIRECTPLAY*)&_refIDirectPlay, 0);
        if (0 <= iVar2) {
            /*
              create IDirectPlay4A
             */
            HRESULT HVar3 = _refIDirectPlay->QueryInterface(*GUID_IID_IDirectPlay4A::ptr, (LPVOID*)&_interface);
            if (HVar3 < 0) {
                _refIDirectPlay->Release();
                ;
                return;
            }
            HVar3 = _interface->GetPlayerAddress(0, (void*)0x0, &_playerAddress);
            if (HVar3 != -0x7788ffe2) {
                _refIDirectPlay->Release();
                _interface->Release();
                ;
                return;
            }
            _allocateMem = GlobalAlloc(66, _playerAddress);
            _allocateMemLock = (int*)GlobalLock(_allocateMem);
            if (_allocateMemLock == (int*)0x0) {
                _refIDirectPlay->Release();
                _interface->Release();
                ;
                return;
            }
            piVar5 = _allocateMemLock;
            HVar3 = _interface->GetPlayerAddress(0, _allocateMemLock, &_playerAddress);
            if (-1 < HVar3) {
                this->DPLAYX_LOBBY->EnumAddress((LPDPENUMADDRESSCALLBACK)MACRO_CALL(
                                                    Synchrony_Func::DirectPlayModemRelated_MemoryAllocationCallback),
                    _allocateMemLock, _playerAddress, (void*)0x0);
            }
            _refIDirectPlay->Release();
            _interface->Release();
            pvVar4 = GlobalHandle(_allocateMemLock);
            GlobalUnlock(pvVar4);
            pvVar4 = GlobalHandle(_allocateMemLock);
            GlobalFree(pvVar4);
        };
        return;
    }

}
}
