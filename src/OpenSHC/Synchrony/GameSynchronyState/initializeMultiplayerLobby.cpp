#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048BF80
    void GameSynchronyState::initializeMultiplayerLobby()
    {
        // the original reads some fields through the global instance rather than this, so they stay that way
        for (int provider = 0; provider < 10; ++provider) {
            DAT_GameSynchronyState::instance.providerNames[provider] = NULL;
            DAT_GameSynchronyState::instance.guids[provider] = NULL;
        }
        this->DPLAYX_Connection = NULL;
        DAT_GameSynchronyState::instance.scrollBarItemOffset = 0;
        DAT_GameSynchronyState::instance.selectedProviderIndex = 0;
        DAT_GameSynchronyState::instance.modemScrollBarOffset = 0;
        DAT_GameSynchronyState::instance.modemScrollbarIndex = 0;
        MACRO_CALL_MEMBER(
            Synchrony::GameSynchronyState_Func::invokeDirectPlayEnumConnections, DAT_GameSynchronyState::ptr)();
        MACRO_CALL_MEMBER(
            Synchrony::GameSynchronyState_Func::createDirectPlayInterfaceModem, DAT_GameSynchronyState::ptr)();
        this->hasHostAddress[0] = FALSE;
        this->hasHostAddress[1] = FALSE;
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(1, 1), &wsaData) == 0) {
            char hostName[80];
            if (gethostname(hostName, sizeof(hostName)) != SOCKET_ERROR) {
                hostent* const host = gethostbyname(hostName);
                if (host != NULL) {
                    // up to two addresses
                    for (int i = 0; host->h_addr_list[i] != NULL && i < 2; ++i) {
                        this->hasHostAddress[i] = TRUE;
                        this->hostAddress[i] = *(IN_ADDR*)host->h_addr_list[i];
                    }
                }
            }
            WSACleanup();
        }
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::setupSkirmishLobby, DAT_GameSynchronyState::ptr)();
        for (int player = 0; player < 9; ++player) {
            this->connectionLagInfoArray[player].mapTimeInTicks = 0;
            this->connectionLagInfoArray[player].subtractedMapTicks = 0;
        }
    }

}
}
