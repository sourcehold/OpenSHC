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
        DAT_GameSynchronyState::instance.providerNames[0] = (WCHAR*)0x0;
        DAT_GameSynchronyState::instance.guids[0] = (GUID*)0x0;
        DAT_GameSynchronyState::instance.providerNames[1] = (WCHAR*)0x0;
        DAT_GameSynchronyState::instance.guids[1] = (GUID*)0x0;
        DAT_GameSynchronyState::instance.providerNames[2] = (WCHAR*)0x0;
        DAT_GameSynchronyState::instance.guids[2] = (GUID*)0x0;
        DAT_GameSynchronyState::instance.providerNames[3] = (WCHAR*)0x0;
        DAT_GameSynchronyState::instance.guids[3] = (GUID*)0x0;
        DAT_GameSynchronyState::instance.providerNames[4] = (WCHAR*)0x0;
        DAT_GameSynchronyState::instance.guids[4] = (GUID*)0x0;
        DAT_GameSynchronyState::instance.providerNames[5] = (WCHAR*)0x0;
        DAT_GameSynchronyState::instance.guids[5] = (GUID*)0x0;
        DAT_GameSynchronyState::instance.providerNames[6] = (WCHAR*)0x0;
        DAT_GameSynchronyState::instance.guids[6] = (GUID*)0x0;
        DAT_GameSynchronyState::instance.providerNames[7] = (WCHAR*)0x0;
        DAT_GameSynchronyState::instance.guids[7] = (GUID*)0x0;
        DAT_GameSynchronyState::instance.providerNames[8] = (WCHAR*)0x0;
        DAT_GameSynchronyState::instance.guids[8] = (GUID*)0x0;
        DAT_GameSynchronyState::instance.providerNames[9] = (WCHAR*)0x0;
        DAT_GameSynchronyState::instance.guids[9] = (GUID*)0x0;
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
        this->connectionLagInfoArray[0].mapTimeInTicks = 0;
        this->connectionLagInfoArray[0].subtractedMapTicks = 0;
        this->connectionLagInfoArray[1].mapTimeInTicks = 0;
        this->connectionLagInfoArray[1].subtractedMapTicks = 0;
        this->connectionLagInfoArray[2].mapTimeInTicks = 0;
        this->connectionLagInfoArray[2].subtractedMapTicks = 0;
        this->connectionLagInfoArray[3].mapTimeInTicks = 0;
        this->connectionLagInfoArray[3].subtractedMapTicks = 0;
        this->connectionLagInfoArray[4].mapTimeInTicks = 0;
        this->connectionLagInfoArray[4].subtractedMapTicks = 0;
        this->connectionLagInfoArray[5].mapTimeInTicks = 0;
        this->connectionLagInfoArray[5].subtractedMapTicks = 0;
        this->connectionLagInfoArray[6].mapTimeInTicks = 0;
        this->connectionLagInfoArray[6].subtractedMapTicks = 0;
        this->connectionLagInfoArray[7].mapTimeInTicks = 0;
        this->connectionLagInfoArray[7].subtractedMapTicks = 0;
        this->connectionLagInfoArray[8].mapTimeInTicks = 0;
        this->connectionLagInfoArray[8].subtractedMapTicks = 0;
    }

}
}
