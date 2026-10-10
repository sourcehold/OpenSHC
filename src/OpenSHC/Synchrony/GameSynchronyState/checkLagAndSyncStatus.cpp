#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048DA60
    void GameSynchronyState::checkLagAndSyncStatus()
    {
        undefined1* puVar1;
        int* piVar2;
        DWORD DVar3;
        int iVar4;
        byte* pbVar5;
        HashContainerElement* pHVar6;
        int* piVar7;
        GUID* pGVar8;
        int _player;
        piVar7 = DAT_GameSynchronyState::instance.syncStatus10Related + 1;
        DAT_GameSynchronyState::instance.syncStatus10Related[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
        iVar4 = 1;
        piVar2 = piVar7;
        /*
          current player full id array
         */
        while (piVar2[-0x40502] == -1 || *piVar2 != 0) {
            iVar4 = iVar4 + 1;
            piVar2 = piVar2 + 1;
            if (8 < iVar4)
                goto LAB_0048da99;
        }
        if (!DAT_GameSynchronyState::instance.announcementReceivedBool) {
            DVar3 = timeGetTime();
            if (DVar3 - DAT_GameSynchronyState::instance.announcementReceiveTime < 60000) {}
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(Commands::GCT_KILL_GAME);
        }
        DVar3 = timeGetTime();
        if (DVar3 - DAT_GameSynchronyState::instance.announcementReceiveTime < 45000) {}
        _player = 1;
        do {
            if ((piVar7[-0x40502] != -1) && (*piVar7 == 0)) {
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0x3f;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _player;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(Commands::GCT_LEAVE_GAME);
                *piVar7 = 1;
            }
            _player = _player + 1;
            piVar7 = piVar7 + 1;
        } while (_player < 9);
    LAB_0048da99:
        pGVar8 = (GUID*)0x0;
        DAT_GameSynchronyState::instance.syncStatus = 1;
        DAT_GameSynchronyState::instance.field76_0xbe8 = DAT_GameSynchronyState::instance.resyncStartTime;
        DAT_GameSynchronyState::instance.announcementReceiveTime = DAT_GameSynchronyState::instance.resyncStartTime;
        DAT_GameSynchronyState::instance.announcementReceivedBool = FALSE;
        pHVar6 = &DAT_GameSynchronyState::instance.HASH_PartialHashPerPlayer.player2;
        pbVar5 = DAT_GameSynchronyState::instance.sharedDesyncFlags;
        do {
            *pbVar5 = 0;
            iVar4 = 1;
            piVar7 = DAT_GameSynchronyState::instance.currentPlayerFullIDArray;
            do {
                piVar7 = piVar7 + 1;
                if (*piVar7 != -1) {
                    pGVar8 = DAT_GameSynchronyState::instance
                                 .guids[(int)(pbVar5 + (iVar4 * 3 + 0x7a8e) * 4 + -0x1998244 + -3)];
                    break;
                }
                iVar4 = iVar4 + 1;
            } while (iVar4 < 9);
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] != -1)
                && (pGVar8 != (GUID*)pHVar6[-1].domain01)) {
                *pbVar5 = 1;
            }
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] != -1)
                && (pGVar8 != (GUID*)pHVar6->domain01)) {
                *pbVar5 = 1;
            }
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] != -1)
                && (pGVar8 != (GUID*)pHVar6[1].domain01)) {
                *pbVar5 = 1;
            }
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] != -1)
                && (pGVar8 != (GUID*)pHVar6[2].domain01)) {
                *pbVar5 = 1;
            }
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] != -1)
                && (pGVar8 != (GUID*)pHVar6[3].domain01)) {
                *pbVar5 = 1;
            }
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] != -1)
                && (pGVar8 != (GUID*)pHVar6[4].domain01)) {
                *pbVar5 = 1;
            }
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] != -1)
                && (pGVar8 != (GUID*)pHVar6[5].domain01)) {
                *pbVar5 = 1;
            }
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] != -1)
                && (pGVar8 != (GUID*)pHVar6[6].domain01)) {
                *pbVar5 = 1;
            }
            puVar1 = pbVar5 + -0x1998243;
            pHVar6 = (HashContainerElement*)&pHVar6->domain02;
            pbVar5 = pbVar5 + 1;
            if (14 < (int)puVar1) {
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                    Commands::GCT_SHARE_SYNC_STATUS);
            }
        } while (true);
    }

}
}
