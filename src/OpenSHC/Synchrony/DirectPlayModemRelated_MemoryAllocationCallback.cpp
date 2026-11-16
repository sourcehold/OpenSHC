#include "../Synchrony.func.hpp"

// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/GUID_DPAID_Modem.hpp"

namespace OpenSHC {

using WindowsHelper::Enums::BOOLEnum;

// FUNCTION: STRONGHOLDCRUSADER 0x0047E160
BOOLEnum __stdcall Synchrony::DirectPlayModemRelated_MemoryAllocationCallback(
    GUID* guidDataType, DWORD dataSize, char* data, void* context)
{
    char* entry = data;
    if (MACRO_CALL(OS_Func::isEqualGUID)(guidDataType, &GUID_DPAID_Modem::instance)) {
        // A for loop with the step in its header compiles differently (95.6%).
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
