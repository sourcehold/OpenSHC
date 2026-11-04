#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/string-literals.hpp"
#include "OpenSHC/wstring-literals.hpp"

#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047DA70
    void GameSynchronyState::setDPlaySessionNameValue()
    {
        if (this->useTCPIP) {
            // L"Crusader"
            MACRO_CALL(Global_Func::PrintToDestination)(this->DPLAYX_SessionName, u_Crusader_005a6f40);
            return;
        }
        char sessionName[250];
        // "Stronghold-%s"
        MACRO_CALL(OS_Func::_sprintf)(sessionName, s_Stronghold_s_005a6f30,
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0));
        MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::multiByteToWideCharacter, DAT_WideCharMultiByteState::ptr)(
            this->DPLAYX_SessionName, sessionName);
    }

}
}
