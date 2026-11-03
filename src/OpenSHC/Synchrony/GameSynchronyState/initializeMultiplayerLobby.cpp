#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048BF80
    void GameSynchronyState::initializeMultiplayerLobby()
    {
        for (int provider = 0; provider < 10; provider++) {
            DAT_GameSynchronyState::instance.providerNames[provider] = NULL;
            DAT_GameSynchronyState::instance.guids[provider] = NULL;
        }
        this->DPLAYX_Connection = 0;
        DAT_GameSynchronyState::instance.scrollBarItemOffset = 0;
        DAT_GameSynchronyState::instance.selectedProviderIndex = 0;
        DAT_GameSynchronyState::instance.modemScrollBarOffset = 0;
        DAT_GameSynchronyState::instance.modemScrollbarIndex = 0;
        MACRO_CALL_MEMBER(
            Synchrony::GameSynchronyState_Func::invokeDirectPlayEnumConnections, DAT_GameSynchronyState::ptr)();
        MACRO_CALL_MEMBER(
            Synchrony::GameSynchronyState_Func::createDirectPlayInterfaceModem, DAT_GameSynchronyState::ptr)();
        this->displayYourIP = FALSE;
        this->lanOrWan = FALSE;
        WSADATA wsaData;
        if (WSAStartup(257, &wsaData) == 0) {
            char hostName[80];
            if (gethostname(hostName, 80) != -1) {
                hostent* const host = gethostbyname(hostName);
                if (host != NULL && host->h_addr_list[0] != NULL) {
                    // Up to two addresses: the first goes to lanIP and sets displayYourIP, the second to wanIP and
                    // lanOrWan.
                    for (int i = 0; host->h_addr_list[i] != NULL; i++) {
                        if (i >= 2) {
                            break;
                        }
                        (&this->displayYourIP)[i] = TRUE;
                        (&this->lanIP)[i] = *(IN_ADDR*)host->h_addr_list[i];
                    }
                }
            }
            WSACleanup();
        }
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::setupSkirmishLobby, DAT_GameSynchronyState::ptr)();
        for (int player = 0; player < 9; player++) {
            this->connectionLagInfoArray[player].mapTimeInTicks = 0;
            this->connectionLagInfoArray[player].subtractedMapTicks = 0;
        }
    }

}
}
