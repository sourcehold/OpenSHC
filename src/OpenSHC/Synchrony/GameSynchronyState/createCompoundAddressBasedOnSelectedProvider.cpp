// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"

#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/GUID_DPAID_INet.hpp"
#include "OpenSHC/Globals/GUID_DPAID_Modem.hpp"
#include "OpenSHC/Globals/GUID_DPAID_Phone.hpp"
#include "OpenSHC/Globals/GUID_DPAID_ServiceProvider.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_IPX.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_MODEM.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_TCPIP.hpp"

#include <stdlib.h>
#include <string.h>

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047D6A0
    int GameSynchronyState::createCompoundAddressBasedOnSelectedProvider(
        LPVOID* pCompoundAddress, SIZE_T* compoundAddressSize)
    {
        DWORD size = 0;
        GUID provider;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::getGUIDForSelectedProvider, this)(&provider);
        DPCOMPOUNDADDRESSELEMENT elements[3];
        char texts[3][200];
        DWORD port;
        DWORD elementCount;
        if (MACRO_CALL(OS_Func::isEqualGUID)(&provider, GUID_DPSPGUID_MODEM::ptr)) {
            // Modem: the selected modem, if any, and the phone number.
            elements[0].guidDataType = GUID_DPAID_ServiceProvider::instance;
            elements[0].dwDataSize = sizeof(GUID);
            elements[0].lpData = GUID_DPSPGUID_MODEM::ptr;
            elementCount = 1;
            strcpy(texts[0], this->stringPointerArray[this->modemScrollbarIndex + this->modemScrollBarOffset]);
            // The original measures the name again for the element's size.
            size_t const modemNameLength = strlen(texts[0]);
            if (modemNameLength != 0) {
                elements[1].guidDataType = GUID_DPAID_Modem::instance;
                elements[1].dwDataSize = strlen(texts[0]) + 1;
                elements[1].lpData = texts[0];
                elementCount = 2;
            }
            strcpy(texts[1],
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(7));
            elements[elementCount].guidDataType = GUID_DPAID_Phone::instance;
            elements[elementCount].dwDataSize = strlen(texts[1]) + 1;
            elements[elementCount].lpData = texts[1];
            ++elementCount;
        } else if (MACRO_CALL(OS_Func::isEqualGUID)(&provider, GUID_DPSPGUID_TCPIP::ptr)) {
            // TCP/IP: the address and, when one is given, the port.
            elements[0].guidDataType = GUID_DPAID_ServiceProvider::instance;
            elements[0].dwDataSize = sizeof(GUID);
            elements[0].lpData = GUID_DPSPGUID_TCPIP::ptr;
            strcpy(texts[2],
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(5));
            elements[1].guidDataType = GUID_DPAID_INet::instance;
            elements[1].dwDataSize = strlen(texts[2]) + 1;
            elements[1].lpData = texts[2];
            elementCount = 2;
            port = (WORD)atol(
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(6));
            if ((WORD)port > 0) {
                // fixme: the original never sets the port element's GUID (DPAID_INetPort).
                elements[2].dwDataSize = sizeof(WORD);
                elements[2].lpData = &port;
                elementCount = 3;
            }
        } else if (MACRO_CALL(OS_Func::isEqualGUID)(&provider, GUID_DPSPGUID_IPX::ptr)) {
            elements[0].guidDataType = GUID_DPAID_ServiceProvider::instance;
            elements[0].dwDataSize = sizeof(GUID);
            elements[0].lpData = GUID_DPSPGUID_IPX::ptr;
            elementCount = 1;
        } else {
            elements[0].guidDataType = GUID_DPAID_ServiceProvider::instance;
            elements[0].dwDataSize = sizeof(GUID);
            elements[0].lpData = &provider;
            elementCount = 1;
        }
        HRESULT result = this->DPLAYX_LOBBY->CreateCompoundAddress(elements, elementCount, NULL, &size);
        if (result != DPERR_BUFFERTOOSMALL) {
            return result;
        }
        void* const address = GlobalLock(GlobalAlloc(GHND, size));
        if (address == NULL) {
            return DPERR_NOMEMORY;
        }
        result = this->DPLAYX_LOBBY->CreateCompoundAddress(elements, elementCount, address, &size);
        if (FAILED(result)) {
            GlobalUnlock(GlobalHandle(address));
            GlobalFree(GlobalHandle(address));
            return result;
        }
        *pCompoundAddress = address;
        *compoundAddressSize = size;
        return DP_OK;
    }

}
}
