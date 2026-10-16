#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Synchrony {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048BF80
    void GameSynchronyState::initializeMultiplayerLobby()
    {
        int _wsaReturnCode1;
        int _wsaReturnCode2;
        hostent* _hostent;
        int _hostAddressIndex;
        IN_ADDR* p_Var1;
        WSADATA _wsaData;
        char _hostNameBuffer[80];
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)&_wsaData;
        this->providerNames[0] = (WCHAR*)0x0;
        this->guids[0] = (GUID*)0x0;
        this->providerNames[1] = (WCHAR*)0x0;
        this->guids[1] = (GUID*)0x0;
        this->providerNames[2] = (WCHAR*)0x0;
        this->guids[2] = (GUID*)0x0;
        this->providerNames[3] = (WCHAR*)0x0;
        this->guids[3] = (GUID*)0x0;
        this->providerNames[4] = (WCHAR*)0x0;
        this->guids[4] = (GUID*)0x0;
        this->providerNames[5] = (WCHAR*)0x0;
        this->guids[5] = (GUID*)0x0;
        this->providerNames[6] = (WCHAR*)0x0;
        this->guids[6] = (GUID*)0x0;
        this->providerNames[7] = (WCHAR*)0x0;
        this->guids[7] = (GUID*)0x0;
        this->providerNames[8] = (WCHAR*)0x0;
        this->guids[8] = (GUID*)0x0;
        this->providerNames[9] = (WCHAR*)0x0;
        this->guids[9] = (GUID*)0x0;
        this->DPLAYX_Connection = 0;
        this->scrollBarItemOffset = 0;
        this->selectedProviderIndex = 0;
        this->modemScrollBarOffset = 0;
        this->modemScrollbarIndex = 0;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::invokeDirectPlayEnumConnections, this)();
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::createDirectPlayInterfaceModem, this)();
        this->displayYourIP = FALSE;
        this->lanOrWan = FALSE;
        _wsaReturnCode1 = WSAStartup(257, &_wsaData);
        if (!_wsaReturnCode1) {
            _wsaReturnCode2 = gethostname(_hostNameBuffer, 0x50);
            if (((_wsaReturnCode2 != -1) && (_hostent = gethostbyname(_hostNameBuffer), _hostent != (hostent*)0x0))
                && (*_hostent->h_addr_list != (char*)0x0)) {
                _hostAddressIndex = 0;
                p_Var1 = &this->lanIP;
                do {
                    if (7 < _hostAddressIndex)
                        break;
                    p_Var1[-2].S_un.S_addr = 1;
                    *p_Var1 = **(IN_ADDR**)(_hostAddressIndex + (int)_hostent->h_addr_list);
                    _hostAddressIndex = _hostAddressIndex + 4;
                    p_Var1 = p_Var1 + 1;
                } while (*(int*)(_hostAddressIndex + (int)_hostent->h_addr_list) != 0);
            }
            WSACleanup();
        }
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::setupSkirmishLobby, this)();
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
        ;
    }

}
}
