#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EC10
    void GameSynchronyState::handleUnexpectedDPlayXResult()
    {
        char local_68[100];
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)local_68;
        if (this->DPLAYX_SendAndReceiveREsult != -0x7788fffb && this->DPLAYX_SendAndReceiveREsult != -0x7788fff6
            && this->DPLAYX_SendAndReceiveREsult != -0x7788ffec && this->DPLAYX_SendAndReceiveREsult != -0x7788f830
            && this->DPLAYX_SendAndReceiveREsult != -0x7788ffe2 && this->DPLAYX_SendAndReceiveREsult != -0x7788ffd8
            && this->DPLAYX_SendAndReceiveREsult != -0x7788ffce && this->DPLAYX_SendAndReceiveREsult != -0x7788ffc4
            && this->DPLAYX_SendAndReceiveREsult != -0x7788ffba && this->DPLAYX_SendAndReceiveREsult != -0x7788f7f4
            && this->DPLAYX_SendAndReceiveREsult != -0x7788f808 && this->DPLAYX_SendAndReceiveREsult != -0x7788f826
            && this->DPLAYX_SendAndReceiveREsult != -0x7788ffb0 && this->DPLAYX_SendAndReceiveREsult != -0x7788fea2
            && this->DPLAYX_SendAndReceiveREsult != -0x7788f81c && this->DPLAYX_SendAndReceiveREsult != -0x7788ffa6
            && this->DPLAYX_SendAndReceiveREsult != -0x7fffbffb && this->DPLAYX_SendAndReceiveREsult != -0x7788feac
            && this->DPLAYX_SendAndReceiveREsult != -0x7788ff88 && this->DPLAYX_SendAndReceiveREsult != -0x7788ff7e
            && this->DPLAYX_SendAndReceiveREsult != -0x7ff8ffa9 && this->DPLAYX_SendAndReceiveREsult != -0x7788ff6a
            && this->DPLAYX_SendAndReceiveREsult != -0x7788f7e0 && this->DPLAYX_SendAndReceiveREsult != -0x7788ff60
            && this->DPLAYX_SendAndReceiveREsult != -0x7788ff56 && this->DPLAYX_SendAndReceiveREsult != -0x7ff8fff2
            && this->DPLAYX_SendAndReceiveREsult != -0x7788ff42 && this->DPLAYX_SendAndReceiveREsult != -0x7788ff38
            && this->DPLAYX_SendAndReceiveREsult != -0x7788feb6 && this->DPLAYX_SendAndReceiveREsult != -0x7788ff2e
            && this->DPLAYX_SendAndReceiveREsult != -0x7788ff24 && this->DPLAYX_SendAndReceiveREsult != -0x7788ff1a
            && this->DPLAYX_SendAndReceiveREsult != -0x7788f812 && this->DPLAYX_SendAndReceiveREsult != -0x7788ff10
            && this->DPLAYX_SendAndReceiveREsult != -0x7788ff06 && this->DPLAYX_SendAndReceiveREsult != -0x7fffbfff
            && this->DPLAYX_SendAndReceiveREsult != -0x7788fef2 && this->DPLAYX_SendAndReceiveREsult != -0x7788fec0
            && this->DPLAYX_SendAndReceiveREsult != -0x7788fee8 && this->DPLAYX_SendAndReceiveREsult != -0x7788feca
            && this->DPLAYX_SendAndReceiveREsult != -0x7ffffff6 && this->DPLAYX_SendAndReceiveREsult != -0x7788fe98) {
            MACRO_CALL(OS_Func::_sprintf)(local_68, "Error:DirectPlay unknown %x", this->DPLAYX_SendAndReceiveREsult);
        };
    }

}
}
