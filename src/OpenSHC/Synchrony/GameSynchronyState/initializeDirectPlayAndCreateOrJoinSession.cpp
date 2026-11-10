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
        // The original zeroes the size on entry; declared at its first use, the code changes.
        SIZE_T connectionSize = 0;
        if (this->DPLAYX_LOBBY == NULL) {
            return DPERR_INVALIDOBJECT;
        }
        HRESULT result;
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
            result = CoCreateInstance(GUID_CLSID_DirectPlay::instance, NULL, CLSCTX_INPROC_SERVER,
                GUID_IID_IDirectPlay4::instance, (LPVOID*)&directPlay);
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
                DPSESSIONDESC2 description;
                MACRO_CALL(OS_Func::_memset)(&description, 0, sizeof(description));
                description.dwSize = sizeof(description);
                description.dwFlags = DPSESSION_OPTIMIZELATENCY | DPSESSION_DIRECTPLAYPROTOCOL | DPSESSION_KEEPALIVE
                    | DPSESSION_MIGRATEHOST;
                description.guidApplication = GUID_APP::instance;
                description.dwMaxPlayers = 8;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::setDPlaySessionNameValue, this)();
                description.lpszSessionName = this->DPLAYX_SessionName;
                result = directPlay->Open(&description, DirectPlay::OFE_CREATE);
            } else {
                // A client only opens the session once it has picked one from the enumeration.
                DPLAY_InterfacePointer::instance = directPlay;
                DPLAY_CurrentSessionGUID::instance = GUID_NULL::instance;
                this->DPLAYX_4A = directPlay;
                return DP_OK;
            }
        } else {
            // Joining reuses the DirectPlay object the session enumeration ran on. Open goes through a copy of the
            // pointer of its own: through directPlay, MSVC merges the two Open calls into one.
            IDirectPlay4A* const enumerationDirectPlay = this->DPLAYX_4A;
            directPlay = enumerationDirectPlay;
            DPSESSIONDESC2 description;
            MACRO_CALL(OS_Func::_memset)(&description, 0, sizeof(description));
            description.dwSize = sizeof(description);
            description.guidApplication = GUID_APP::instance;
            description.guidInstance = DPLAY_CurrentSessionGUID::instance;
            result = enumerationDirectPlay->Open(&description, DirectPlay::OFE_JOIN);
        }
        if (FAILED(result)) {
            directPlay->Close();
            directPlay->Release();
            this->DPLAYX_4A = NULL;
            return result;
        }
        // The original zeroes this one inline, and the session descriptions above through its memset.
        memset(&this->DPLAY_PlayerNameStructure, 0, sizeof(this->DPLAY_PlayerNameStructure));
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
