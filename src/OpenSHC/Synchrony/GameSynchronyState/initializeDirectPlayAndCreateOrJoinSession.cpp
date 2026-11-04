#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/DirectPlay/OpenFlagsEnum.hpp"

#include "OpenSHC/Globals/DPLAY_CurrentSessionGUID.hpp"
#include "OpenSHC/Globals/DPLAY_InterfacePointer.hpp"
#include "OpenSHC/Globals/GUID_APP.hpp"
#include "OpenSHC/Globals/GUID_CLSID_DirectPlay.hpp"
#include "OpenSHC/Globals/GUID_IID_IDirectPlay4.hpp"
#include "OpenSHC/Globals/GUID_NULL.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047DB10
    int GameSynchronyState::initializeDirectPlayAndCreateOrJoinSession(BOOLEnum join)
    {
        IDirectPlay4A* directPlay = NULL;
        SIZE_T connectionSize = 0;
        if (this->DPLAYX_LOBBY == NULL) {
            return DPERR_INVALIDOBJECT;
        }
        HRESULT result;
        DPSESSIONDESC2 session;
        if (!join) {
            // A new connection for the selected provider, and a new DirectPlay object on it.
            if (this->DPLAYX_Connection != NULL) {
                GlobalUnlock(GlobalHandle(this->DPLAYX_Connection));
                GlobalFree(GlobalHandle(this->DPLAYX_Connection));
                this->DPLAYX_Connection = NULL;
            }
            result = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::createCompoundAddressBasedOnSelectedProvider,
                this)(&this->DPLAYX_Connection, &connectionSize);
            if (FAILED(result)) {
                return result;
            }
            if (this->DPLAYX_4A != NULL) {
                this->DPLAYX_4A->Close();
                this->DPLAYX_4A->Release();
                this->DPLAYX_4A = NULL;
            }
            result = CoCreateInstance(*GUID_CLSID_DirectPlay::ptr, NULL, CLSCTX_INPROC_SERVER,
                *GUID_IID_IDirectPlay4::ptr, (LPVOID*)&directPlay);
            if (FAILED(result)) {
                return result;
            }
            result = directPlay->InitializeConnection(this->DPLAYX_Connection, 0);
            if (FAILED(result)) {
                directPlay->Release();
                this->DPLAYX_4A = NULL;
                return result;
            }
            if (this->isHost) {
                MACRO_CALL(OS_Func::_memset)(&session, 0, sizeof(session));
                session.dwSize = sizeof(session);
                session.dwFlags = DPSESSION_OPTIMIZELATENCY | DPSESSION_DIRECTPLAYPROTOCOL | DPSESSION_KEEPALIVE
                    | DPSESSION_MIGRATEHOST;
                session.guidApplication = GUID_APP::instance;
                session.dwMaxPlayers = 8;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::setDPlaySessionNameValue, this)();
                session.lpszSessionName = this->DPLAYX_SessionName;
                result = directPlay->Open(&session, DirectPlay::OFE_CREATE);
            } else {
                // A client only opens the session once it has picked one from the enumeration.
                DPLAY_InterfacePointer::instance = directPlay;
                DPLAY_CurrentSessionGUID::instance = GUID_NULL::instance;
                this->DPLAYX_4A = directPlay;
                return DP_OK;
            }
        } else {
            // Joining reuses the DirectPlay object the session enumeration ran on.
            IDirectPlay4A* const enumerating = this->DPLAYX_4A;
            directPlay = enumerating;
            MACRO_CALL(OS_Func::_memset)(&session, 0, sizeof(session));
            session.dwSize = sizeof(session);
            session.guidApplication = GUID_APP::instance;
            session.guidInstance = DPLAY_CurrentSessionGUID::instance;
            result = enumerating->Open(&session, DirectPlay::OFE_JOIN);
        }
        if (FAILED(result)) {
            directPlay->Close();
            directPlay->Release();
            this->DPLAYX_4A = NULL;
            return result;
        }
        ZeroMemory(&this->DPLAY_PlayerNameStructure, sizeof(this->DPLAY_PlayerNameStructure));
        this->DPLAY_PlayerNameStructure.dwSize = sizeof(this->DPLAY_PlayerNameStructure);
        this->DPLAY_PlayerNameStructure.lpszShortName = this->DPLAY_PlayerShortName;
        if (directPlay->CreatePlayer(&this->DPLAYX_PlayerHandle, &this->DPLAY_PlayerNameStructure, NULL, NULL, 0, 0)
            != DP_OK) {
            return DPERR_ABORTED;
        }
        this->DPLAYX_4A = directPlay;
        return DP_OK;
    }

}
}
