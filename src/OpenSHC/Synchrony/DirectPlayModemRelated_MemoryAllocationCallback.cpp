// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/GUID_DPAID_Modem.hpp"

namespace OpenSHC {

using WindowsHelper::Enums::BOOLEnum;

// FUNCTION: STRONGHOLDCRUSADER 0x0047E160
BOOLEnum __stdcall Synchrony::DirectPlayModemRelated_MemoryAllocationCallback(
    int* param_1, undefined4 param_2, char* param_3, undefined4 param_4)
{
    char* entry = param_3;
    if (MACRO_CALL(OS_Func::isEqualGUID)((GUID*)param_1, &GUID_DPAID_Modem::instance)) {
        while (strlen(entry) != 0) {
            if (DAT_GameSynchronyState::instance.modemScrollbarCount >= 30) {
                return FALSE;
            }
            DAT_GameSynchronyState::instance.stringPointerArray[DAT_GameSynchronyState::instance.modemScrollbarCount]
                = (char*)MACRO_CALL(OS_Func::_malloc)(strlen(entry) + 2);
            strcpy(DAT_GameSynchronyState::instance
                       .stringPointerArray[DAT_GameSynchronyState::instance.modemScrollbarCount],
                entry);
            DAT_GameSynchronyState::instance.modemScrollbarCount += 1;
            entry += strlen(entry) + 1;
        }
    }
    return TRUE;
}

}
