#include "../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/GUID_DPAID_Modem.hpp"

namespace OpenSHC {

using WindowsHelper::Enums::BOOLEnum;

// FUNCTION: STRONGHOLDCRUSADER 0x0047E160
BOOLEnum __stdcall Synchrony::DirectPlayModemRelated_MemoryAllocationCallback(
    int* param_1, undefined4 param_2, char* param_3)
{
    char cVar1;
    char* pcVar3;
    char* pcVar4;
    BOOLEnum BVar2 = MACRO_CALL(OS_Func::isEqualGUID)((GUID*)param_1, (GUID*)GUID_DPAID_Modem::ptr);
    if (BVar2) {
        pcVar3 = param_3;
        do {
            cVar1 = *pcVar3;
            pcVar3 = pcVar3 + 1;
        } while (cVar1 != '\0');
        if (pcVar3 != param_3 + 1) {
            do {
                if (30 < DAT_GameSynchronyState::instance.modemScrollbarCount) {
                    return FALSE;
                }
                pcVar3 = param_3;
                do {
                    cVar1 = *pcVar3;
                    pcVar3 = pcVar3 + 1;
                } while (cVar1 != '\0');
                pcVar3 = (char*)(MACRO_CALL(OS_Func::_malloc)((size_t)(pcVar3 + (2 - (int)(param_3 + 1)))));
                DAT_GameSynchronyState::instance
                    .stringPointerArray[DAT_GameSynchronyState::instance.modemScrollbarCount] = pcVar3;
                pcVar3 = DAT_GameSynchronyState::instance
                             .stringPointerArray[DAT_GameSynchronyState::instance.modemScrollbarCount];
                pcVar4 = param_3;
                do {
                    cVar1 = *pcVar4;
                    *pcVar3 = cVar1;
                    pcVar4 = pcVar4 + 1;
                    pcVar3 = pcVar3 + 1;
                } while (cVar1 != '\0');
                DAT_GameSynchronyState::instance.modemScrollbarCount
                    = DAT_GameSynchronyState::instance.modemScrollbarCount + 1;
                do {
                    pcVar3 = param_3;
                    param_3 = pcVar3 + 1;
                } while (*pcVar3 != '\0');
                pcVar4 = param_3;
                do {
                    cVar1 = *pcVar4;
                    pcVar4 = pcVar4 + 1;
                } while (cVar1 != '\0');
            } while (pcVar4 != pcVar3 + 2);
        }
    }
    return TRUE;
}

}
