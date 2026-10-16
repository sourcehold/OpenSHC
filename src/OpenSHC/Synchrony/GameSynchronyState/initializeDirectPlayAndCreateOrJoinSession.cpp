#include "../../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/DirectPlay/OpenFlagsEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DPLAY_CurrentSessionGUID.hpp"
#include "OpenSHC/Globals/DPLAY_InterfacePointer.hpp"
#include "OpenSHC/Globals/GUID_CLSID_DirectPlay.hpp"
#include "OpenSHC/Globals/GUID_IID_IDirectPlay4.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

#include "OpenSHC/Globals/GUID_UNKNOWN.hpp"

namespace OpenSHC {
namespace Synchrony {

    using DirectPlay::OpenFlagsEnum;
    using WindowsHelper::Enums::BOOLEnum;

    /*
      Note that join == TRUE expects the direct play interface to already live      decompilerscript: committed:
      2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0047DB10
    int GameSynchronyState::initializeDirectPlayAndCreateOrJoinSession(BOOLEnum join)
    {
        IDirectPlay4A* ppIVar1;
        uint uVar2;
        HRESULT _lobbyStatus;
        void* pvVar3;
        int _status;
        HRESULT _dpStatus;
        HRESULT _cpStatus;
        HRESULT _setStatus;
        IDirectPlay4A* unaff_EDI;
        IDirectPlay4A* _dplay4;
        SIZE_T local_58;
        DPSESSIONDESC2 _session;
        ppIVar1 = this->DPLAYX_4A;
        uVar2 = MSVC_SecurityCookie::instance ^ (uint)&_dplay4;
        _dplay4 = (IDirectPlay4A*)0x0;
        local_58 = 0;
        if (this->DPLAYX_LOBBY == (IDirectPlayLobby3*)0x0) {
            _lobbyStatus = DPERR_INVALIDOBJECT;
            ;
            return (int)(_lobbyStatus);
        }
        if (!join) {
            if (this->DPLAYX_Connection != (void*)0x0) {
                pvVar3 = GlobalHandle(this->DPLAYX_Connection);
                GlobalUnlock(pvVar3);
                pvVar3 = GlobalHandle(this->DPLAYX_Connection);
                GlobalFree(pvVar3);
                this->DPLAYX_Connection = (void*)0x0;
            }
            _status = MACRO_CALL_MEMBER(
                Synchrony::GameSynchronyState_Func::createCompoundAddressBasedOnSelectedProvider, this)((LPVOID*)&this->DPLAYX_Connection, &local_58);
            if (_status < 0)
                goto LAB_return;
            if (this->DPLAYX_4A != (IDirectPlay4A*)0x0) {
                this->DPLAYX_4A->Close();
                this->DPLAYX_4A->Release();
                this->DPLAYX_4A = (IDirectPlay4A*)0x0;
            }
            _status = CoCreateInstance(*GUID_CLSID_DirectPlay::ptr, (IUnknown*)0x0, 1,
                *GUID_IID_IDirectPlay4::ptr, (LPVOID*)&_dplay4);
            if (_status < 0)
                goto LAB_return;
            _dpStatus = _dplay4->InitializeConnection(this->DPLAYX_Connection, 0);
            if (_dpStatus < DP_OK)
                goto LAB_release;
            if (this->isHost) {
                MACRO_CALL(OS_Func::_memset)(&_session, 0, (size_t)((int)(80)));
                _session.guidApplication = GUID_UNKNOWN::instance;
                _session.dwSize = 80;
                _session.dwFlags = DPSESSION_OPTIMIZELATENCY
                    | DPSESSION_DIRECTPLAYPROTOCOL | DPSESSION_KEEPALIVE
                    | DPSESSION_MIGRATEHOST;
                _session.dwMaxPlayers = 8;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::setDPlaySessionNameValue, this)();
                _session.lpszSessionName = this->DPLAYX_SessionName;
                _dpStatus = _dplay4->Open(&_session, DirectPlay::OFE_CREATE);
                goto LAB_close_and_release_if_err;
            }
            DPLAY_CurrentSessionGUID::instance.Data1 = 0;
            DPLAY_CurrentSessionGUID::instance.Data2 = 0;
            DPLAY_CurrentSessionGUID::instance.Data3 = 0;
            DPLAY_InterfacePointer::instance = _dplay4;
            DPLAY_CurrentSessionGUID::instance.Data4[0] = '\0';
            DPLAY_CurrentSessionGUID::instance.Data4[1] = '\0';
            DPLAY_CurrentSessionGUID::instance.Data4[2] = '\0';
            DPLAY_CurrentSessionGUID::instance.Data4[3] = '\0';
            DPLAY_CurrentSessionGUID::instance.Data4[4] = '\0';
            DPLAY_CurrentSessionGUID::instance.Data4[5] = '\0';
            DPLAY_CurrentSessionGUID::instance.Data4[6] = '\0';
            DPLAY_CurrentSessionGUID::instance.Data4[7] = '\0';
        } else {
            _dplay4 = this->DPLAYX_4A;
            MACRO_CALL(OS_Func::_memset)(&_session, 0, (size_t)((int)(80)));
            _session.guidApplication = GUID_UNKNOWN::instance;
            _session.guidInstance.Data1 = DPLAY_CurrentSessionGUID::instance.Data1;
            _session.guidInstance.Data4[0] = DPLAY_CurrentSessionGUID::instance.Data4[0];
            _session.guidInstance.Data4[1] = DPLAY_CurrentSessionGUID::instance.Data4[1];
            _session.guidInstance.Data4[2] = DPLAY_CurrentSessionGUID::instance.Data4[2];
            _session.guidInstance.Data4[3] = DPLAY_CurrentSessionGUID::instance.Data4[3];
            _session.guidInstance.Data4[4] = DPLAY_CurrentSessionGUID::instance.Data4[4];
            _session.guidInstance.Data4[5] = DPLAY_CurrentSessionGUID::instance.Data4[5];
            _session.guidInstance.Data4[6] = DPLAY_CurrentSessionGUID::instance.Data4[6];
            _session.guidInstance.Data4[7] = DPLAY_CurrentSessionGUID::instance.Data4[7];
            _session.dwSize = 80;
            _session.guidInstance.Data2 = DPLAY_CurrentSessionGUID::instance.Data2;
            _session.guidInstance.Data3 = DPLAY_CurrentSessionGUID::instance.Data3;
            _dpStatus = ppIVar1->Open(&_session, DirectPlay::OFE_JOIN);
        LAB_close_and_release_if_err:
            if (_dpStatus < DP_OK) {
                /*
                  Close?
                 */
                unaff_EDI->Close();
            LAB_release:
                _dplay4->Release();
                this->DPLAYX_4A = (IDirectPlay4A*)0x0;
                ;
                return (int)(_dpStatus);
            }
            this->DPLAY_PlayerNameStructure.dwFlags = 0;
            this->DPLAY_PlayerNameStructure.lpszLongName = (WCHAR*)0x0;
            this->DPLAY_PlayerNameStructure.dwSize = 0x10;
            this->DPLAY_PlayerNameStructure.lpszShortName = this->DPLAY_PlayerShortName;
            _cpStatus = _dplay4->CreatePlayer((LPDPID)&this->DPLAYX_PlayerHandle,
                &this->DPLAY_PlayerNameStructure, (void*)0x0, (void*)0x0, 0, 0);
            if (_cpStatus != DP_OK) {
                _setStatus = DPERR_ABORTED;
                ;
                return (int)(_setStatus);
            }
        }
        _status = 0;
        this->DPLAYX_4A = _dplay4;
    LAB_return:;
        return _status;
    }

}
}
