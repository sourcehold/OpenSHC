#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Synchrony.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/GUID_CLSID_DirectPlay.hpp"
#include "OpenSHC/Globals/GUID_CLSID_DirectPlayLobby.hpp"
#include "OpenSHC/Globals/GUID_IID_IDirectPlay4.hpp"
#include "OpenSHC/Globals/GUID_IID_IDirectPlayLobby3.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00487250
    void GameSynchronyState::invokeDirectPlayEnumConnections()
    {
        this->DPLAYX_4A = NULL;
        this->DPLAYX_LOBBY = NULL;
        IDirectPlay4A* directPlay = NULL;
        IDirectPlayLobby3* lobby = NULL;
        // TCP/IP, IPX and modem have the first three slots reserved.
        DAT_GameSynchronyState::instance.scrollBarItemCount = 3;
        if (SUCCEEDED(CoCreateInstance(*GUID_CLSID_DirectPlay::ptr, NULL, CLSCTX_INPROC_SERVER,
                *GUID_IID_IDirectPlay4::ptr, (LPVOID*)&directPlay))) {
            if (FAILED(CoCreateInstance(*GUID_CLSID_DirectPlayLobby::ptr, NULL, CLSCTX_INPROC_SERVER,
                    *GUID_IID_IDirectPlayLobby3::ptr, (LPVOID*)&lobby))) {
                directPlay->Release();
                return;
            }
            directPlay->EnumConnections(NULL, MACRO_CALL(Synchrony_Func::EnumConnectionsCallback), NULL, 0);
            // A reserved provider that is not installed leaves its slot; one block per slot, as the original has no
            // loop.
            if (this->guids[2] == NULL) {
                for (int provider = 2; provider < this->scrollBarItemCount; ++provider) {
                    this->guids[provider] = this->guids[provider + 1];
                    this->providerNames[provider] = this->providerNames[provider + 1];
                }
                --this->scrollBarItemCount;
            }
            if (this->guids[1] == NULL) {
                for (int provider = 1; provider < this->scrollBarItemCount; ++provider) {
                    this->guids[provider] = this->guids[provider + 1];
                    this->providerNames[provider] = this->providerNames[provider + 1];
                }
                --this->scrollBarItemCount;
            }
            if (this->guids[0] == NULL) {
                for (int provider = 0; provider < this->scrollBarItemCount; ++provider) {
                    this->guids[provider] = this->guids[provider + 1];
                    this->providerNames[provider] = this->providerNames[provider + 1];
                }
                --this->scrollBarItemCount;
            }
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::setMenuTypeBasedOnDirectPlayGUID, this)();
            this->DPLAYX_LOBBY = lobby;
            directPlay->Release();
        }
    }

}
}
