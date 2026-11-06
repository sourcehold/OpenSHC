#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EC10
    void GameSynchronyState::handleUnexpectedDPlayXResult()
    {
        // The known DirectPlay errors are left alone; any other result is formatted into a debug message.
        if (this->DPLAYX_SendAndReceiveREsult != DPERR_ALREADYINITIALIZED
            && this->DPLAYX_SendAndReceiveREsult != DPERR_ACCESSDENIED
            && this->DPLAYX_SendAndReceiveREsult != DPERR_ACTIVEPLAYERS
            && this->DPLAYX_SendAndReceiveREsult != DPERR_AUTHENTICATIONFAILED
            && this->DPLAYX_SendAndReceiveREsult != DPERR_BUFFERTOOSMALL
            && this->DPLAYX_SendAndReceiveREsult != DPERR_CANTADDPLAYER
            && this->DPLAYX_SendAndReceiveREsult != DPERR_CANTCREATEGROUP
            && this->DPLAYX_SendAndReceiveREsult != DPERR_CANTCREATEPLAYER
            && this->DPLAYX_SendAndReceiveREsult != DPERR_CANTCREATESESSION
            && this->DPLAYX_SendAndReceiveREsult != DPERR_CANTLOADCAPI
            && this->DPLAYX_SendAndReceiveREsult != DPERR_CANTLOADSECURITYPACKAGE
            && this->DPLAYX_SendAndReceiveREsult != DPERR_CANTLOADSSPI
            && this->DPLAYX_SendAndReceiveREsult != DPERR_CAPSNOTAVAILABLEYET
            && this->DPLAYX_SendAndReceiveREsult != DPERR_CONNECTING
            && this->DPLAYX_SendAndReceiveREsult != DPERR_ENCRYPTIONFAILED
            && this->DPLAYX_SendAndReceiveREsult != DPERR_EXCEPTION
            && this->DPLAYX_SendAndReceiveREsult != DPERR_GENERIC
            && this->DPLAYX_SendAndReceiveREsult != DPERR_INVALIDPASSWORD
            && this->DPLAYX_SendAndReceiveREsult != DPERR_INVALIDFLAGS
            && this->DPLAYX_SendAndReceiveREsult != DPERR_INVALIDOBJECT
            && this->DPLAYX_SendAndReceiveREsult != DPERR_INVALIDPARAM
            && this->DPLAYX_SendAndReceiveREsult != DPERR_INVALIDPLAYER
            && this->DPLAYX_SendAndReceiveREsult != DPERR_LOGONDENIED
            && this->DPLAYX_SendAndReceiveREsult != DPERR_NOCAPS
            && this->DPLAYX_SendAndReceiveREsult != DPERR_NOCONNECTION
            && this->DPLAYX_SendAndReceiveREsult != DPERR_NOMEMORY
            && this->DPLAYX_SendAndReceiveREsult != DPERR_NOMESSAGES
            && this->DPLAYX_SendAndReceiveREsult != DPERR_NONAMESERVERFOUND
            && this->DPLAYX_SendAndReceiveREsult != DPERR_NONEWPLAYERS
            && this->DPLAYX_SendAndReceiveREsult != DPERR_NOPLAYERS
            && this->DPLAYX_SendAndReceiveREsult != DPERR_NOSESSIONS
            && this->DPLAYX_SendAndReceiveREsult != DPERR_SENDTOOBIG
            && this->DPLAYX_SendAndReceiveREsult != DPERR_SIGNFAILED
            && this->DPLAYX_SendAndReceiveREsult != DPERR_TIMEOUT
            && this->DPLAYX_SendAndReceiveREsult != DPERR_UNAVAILABLE
            && this->DPLAYX_SendAndReceiveREsult != DPERR_UNSUPPORTED && this->DPLAYX_SendAndReceiveREsult != DPERR_BUSY
            && this->DPLAYX_SendAndReceiveREsult != DPERR_UNINITIALIZED
            && this->DPLAYX_SendAndReceiveREsult != DPERR_USERCANCEL
            && this->DPLAYX_SendAndReceiveREsult != DPERR_SESSIONLOST
            && this->DPLAYX_SendAndReceiveREsult != DPERR_PENDING
            && this->DPLAYX_SendAndReceiveREsult != DPERR_CONNECTIONLOST) {
            char message[100];
            // "Error:DirectPlay unknown %x"
            MACRO_CALL(OS_Func::_sprintf)(
                message, s_Error_DirectPlay_unknown__x_005a6f8c, this->DPLAYX_SendAndReceiveREsult);
        }
    }

}
}
