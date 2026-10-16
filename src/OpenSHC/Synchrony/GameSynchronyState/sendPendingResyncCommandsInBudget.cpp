#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using WindowsHelper::Enums::BOOLEnum;

    /*
      Resumable chunked resync sender. Picks up from somePacketSubTypeUnk (cases 0-15) and resumes   sending resync
      commands for the category at that index, starting from resyncResumeOuterIndex/resyncResumeInnerIndex   offsets.
      Sends until the packet budget (resyncPacketBudget) is exhausted, then suspends by saving   position and queuing
      GCT_QUIT_MULTIPLAYERGAME as a continuation signal. When all categories are   complete, queues
      GCT_CHECK_GAME_SYNCUnk and advances syncStatus to 3.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0048E680
    void GameSynchronyState::sendPendingResyncCommandsInBudget()
    {
        int (*paiVar1)[160];
        int iVar2;
        DWORD DVar3;
        int iVar4;
        int* piVar5;
        int* piVar6;
        int* piVar7;
        int iVar8;
        int local_14;
        int* local_10;
        int* local_c;
        int* local_8;
        iVar4 = this->resyncResumeInnerIndex;
        iVar8 = this->resyncResumeOuterIndex;
        local_14 = 0;
        iVar2 = 1;
        piVar7 = this->syncRelatedStatusArray;
        while (piVar7 = piVar7 + 1, *piVar7 != 0) {
            iVar2 = iVar2 + 1;
            if (8 < iVar2)
                goto LAB_0048e72e;
        }
        if (!this->announcementReceivedBool) {}
        DVar3 = timeGetTime();
        if (DVar3 - this->announcementReceiveTime < 0xafc9) {}
        iVar2 = 1;
        local_10 = this->syncRelatedStatusArray;
        do {
            local_10 = local_10 + 1;
            if (*local_10 == 0) {
                this->DAT_GameCommandParam1 = 0x3f;
                this->DAT_GameCommandParam0 = iVar2;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                    Commands::GCT_LEAVE_GAME);
                *local_10 = 1;
            }
            iVar2 = iVar2 + 1;
        } while (iVar2 < 9);
    LAB_0048e72e:
        switch (this->somePacketSubTypeUnk) {
        case 0xc:
            goto switchD_0048e739_caseD_c;
        case 0xd:
        switchD_0048e739_caseD_d:
            if (iVar8 < 0x1e) {
                local_c = (int*)(iVar8 << 7);
                do {
                    if (iVar4 < 0x20) {
                        local_8 = this->HASH_LogicalTileMap[1].hashDataArray[0].componentArray + (int)local_c + iVar4;
                        do {
                            iVar2 = 1;
                            piVar7 = this->currentPlayerFullIDArray;
                            piVar5 = local_8;
                            do {
                                piVar7 = piVar7 + 1;
                                if ((*piVar7 != -1)
                                    && (this->HASH_LogicalTileMap[this->currentPlayerSlotID]
                                            .hashDataArray[iVar8]
                                            .componentArray[iVar4]
                                        != *piVar5)) {
                                    this->DAT_GameCommandParam0 = iVar8;
                                    this->DAT_GameCommandParam1 = iVar4;
                                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                        Commands::GCT_SEND_RESYNC_TILEMAPDATA1);
                                    this->currentPacketTotalSize
                                        = this->currentPacketTotalSize + this->DAT_CurrentTransmitCommandPacketSize;
                                    local_14 = local_14 + this->DAT_CurrentTransmitCommandPacketSize;
                                    if (local_14 > (int)this->resyncPacketBudget) {
                                        this->resyncResumeInnerIndex = iVar4 + 1;
                                        this->somePacketSubTypeUnk = 0xd;
                                        this->resyncResumeOuterIndex = iVar8;
                                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                            this)(Commands::GCT_QUIT_MULTIPLAYERGAME);
                                    }
                                    break;
                                }
                                iVar2 = iVar2 + 1;
                                piVar5 = piVar5 + 0xf00;
                            } while (iVar2 < 9);
                            local_8 = local_8 + 1;
                            iVar4 = iVar4 + 1;
                        } while (iVar4 < 0x20);
                    }
                    local_c = (int*)((int)local_c + 0x80);
                    iVar8 = iVar8 + 1;
                    iVar4 = 0;
                } while ((int)local_c < 0xf00);
            }
            break;
        case 0xe:
            goto switchD_0048e739_caseD_e;
        case 0xf:
        switchD_0048e739_caseD_f:
            if ((this->sharedDesyncFlags[0xd] != 0) && (iVar8 < 0x50)) {
                piVar7 = this->HASH_HeatMaps[1] + iVar8;
                do {
                    iVar4 = 1;
                    piVar5 = this->currentPlayerFullIDArray;
                    piVar6 = piVar7;
                    do {
                        piVar5 = piVar5 + 1;
                        if ((*piVar5 != -1) && (this->HASH_HeatMaps[this->currentPlayerSlotID][iVar8] != *piVar6)) {
                            this->DAT_GameCommandParam0 = iVar8;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_HOST_SHARE_HEATMAP);
                            this->currentPacketTotalSize
                                = this->currentPacketTotalSize + this->DAT_CurrentTransmitCommandPacketSize;
                            local_14 = local_14 + this->DAT_CurrentTransmitCommandPacketSize;
                            if (local_14 > (int)this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 0xf;
                            LAB_0048e84b:
                                this->resyncResumeOuterIndex = iVar8 + 1;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_QUIT_MULTIPLAYERGAME);
                            }
                            break;
                        }
                        iVar4 = iVar4 + 1;
                        piVar6 = piVar6 + 0x50;
                    } while (iVar4 < 9);
                    iVar8 = iVar8 + 1;
                    piVar7 = piVar7 + 1;
                } while (iVar8 < 0x50);
            }
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                Commands::GCT_CHECK_GAME_SYNCUnk);
            this->syncStatus = 3;
            return;
        default:
            iVar8 = 0;
        case 0:
            if ((this->sharedDesyncFlags[0] != 0) && (iVar8 < 0x9c4)) {
                piVar7 = this->HASH_Units[1] + iVar8;
                do {
                    iVar4 = 1;
                    piVar5 = this->currentPlayerFullIDArray;
                    piVar6 = piVar7;
                    do {
                        piVar5 = piVar5 + 1;
                        if ((*piVar5 != -1) && (this->HASH_Units[this->currentPlayerSlotID][iVar8] != *piVar6)) {
                            this->DAT_GameCommandParam0 = iVar8;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_UNIT);
                            this->currentPacketTotalSize
                                = this->currentPacketTotalSize + this->DAT_CurrentTransmitCommandPacketSize;
                            local_14 = local_14 + this->DAT_CurrentTransmitCommandPacketSize;
                            if (local_14 > (int)this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 0;
                                goto LAB_0048e84b;
                            }
                            break;
                        }
                        iVar4 = iVar4 + 1;
                        piVar6 = piVar6 + 0x9c4;
                    } while (iVar4 < 9);
                    iVar8 = iVar8 + 1;
                    piVar7 = piVar7 + 1;
                } while (iVar8 < 0x9c4);
            }
            iVar8 = 0;
        case 1:
            if ((this->sharedDesyncFlags[1] != 0) && (iVar8 < 2000)) {
                piVar7 = this->HASH_Buildings[1] + iVar8;
                do {
                    iVar4 = 1;
                    piVar5 = this->currentPlayerFullIDArray;
                    piVar6 = piVar7;
                    do {
                        piVar5 = piVar5 + 1;
                        if ((*piVar5 != -1) && (this->HASH_Buildings[this->currentPlayerSlotID][iVar8] != *piVar6)) {
                            this->DAT_GameCommandParam0 = iVar8;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_BUILDING);
                            this->currentPacketTotalSize
                                = this->currentPacketTotalSize + this->DAT_CurrentTransmitCommandPacketSize;
                            local_14 = local_14 + this->DAT_CurrentTransmitCommandPacketSize;
                            if (local_14 > (int)this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 1;
                                goto LAB_0048e84b;
                            }
                            break;
                        }
                        iVar4 = iVar4 + 1;
                        piVar6 = piVar6 + 2000;
                    } while (iVar4 < 9);
                    iVar8 = iVar8 + 1;
                    piVar7 = piVar7 + 1;
                } while (iVar8 < 2000);
            }
            iVar8 = 0;
        case 2:
            if ((this->sharedDesyncFlags[2] != 0) && (iVar8 < 2000)) {
                piVar7 = this->HASH_Trees[1] + iVar8;
                do {
                    iVar4 = 1;
                    piVar5 = this->currentPlayerFullIDArray;
                    piVar6 = piVar7;
                    do {
                        piVar5 = piVar5 + 1;
                        if ((*piVar5 != -1) && (this->HASH_Trees[this->currentPlayerSlotID][iVar8] != *piVar6)) {
                            this->DAT_GameCommandParam0 = iVar8;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_TREE);
                            this->currentPacketTotalSize
                                = this->currentPacketTotalSize + this->DAT_CurrentTransmitCommandPacketSize;
                            local_14 = local_14 + this->DAT_CurrentTransmitCommandPacketSize;
                            if (local_14 > (int)this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 2;
                                goto LAB_0048e84b;
                            }
                            break;
                        }
                        iVar4 = iVar4 + 1;
                        piVar6 = piVar6 + 2000;
                    } while (iVar4 < 9);
                    iVar8 = iVar8 + 1;
                    piVar7 = piVar7 + 1;
                } while (iVar8 < 2000);
            }
            iVar8 = 0;
        case 3:
            if ((this->sharedDesyncFlags[3] != 0) && (iVar8 < 0x4e2)) {
                piVar7 = this->HASH_Tribes[1] + iVar8;
                do {
                    iVar4 = 1;
                    piVar5 = this->currentPlayerFullIDArray;
                    piVar6 = piVar7;
                    do {
                        piVar5 = piVar5 + 1;
                        if ((*piVar5 != -1) && (this->HASH_Tribes[this->currentPlayerSlotID][iVar8] != *piVar6)) {
                            this->DAT_GameCommandParam0 = iVar8;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_UNITSELECTION);
                            this->currentPacketTotalSize
                                = this->currentPacketTotalSize + this->DAT_CurrentTransmitCommandPacketSize;
                            local_14 = local_14 + this->DAT_CurrentTransmitCommandPacketSize;
                            if (local_14 > (int)this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 3;
                                goto LAB_0048e84b;
                            }
                            break;
                        }
                        iVar4 = iVar4 + 1;
                        piVar6 = piVar6 + 0x4e2;
                    } while (iVar4 < 9);
                    iVar8 = iVar8 + 1;
                    piVar7 = piVar7 + 1;
                } while (iVar8 < 0x4e2);
            }
            iVar8 = 0;
        case 4:
            if ((this->sharedDesyncFlags[4] != 0) && (iVar8 < 9)) {
                piVar7 = this->HASH_PlayerDatas[1] + iVar8;
                do {
                    iVar4 = 1;
                    piVar5 = this->currentPlayerFullIDArray;
                    piVar6 = piVar7;
                    do {
                        piVar5 = piVar5 + 1;
                        if ((*piVar5 != -1) && (this->HASH_PlayerDatas[this->currentPlayerSlotID][iVar8] != *piVar6)) {
                            this->DAT_GameCommandParam0 = iVar8;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_PLAYERDATA);
                            this->currentPacketTotalSize
                                = this->currentPacketTotalSize + this->DAT_CurrentTransmitCommandPacketSize;
                            local_14 = local_14 + this->DAT_CurrentTransmitCommandPacketSize;
                            if (local_14 > (int)this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 4;
                                goto LAB_0048e84b;
                            }
                            break;
                        }
                        iVar4 = iVar4 + 1;
                        piVar6 = piVar6 + 9;
                    } while (iVar4 < 9);
                    iVar8 = iVar8 + 1;
                    piVar7 = piVar7 + 1;
                } while (iVar8 < 9);
            }
            iVar8 = 0;
        case 5:
            if ((this->sharedDesyncFlags[5] != 0) && (iVar8 < 0x14)) {
                piVar7 = this->HASH_Section1023[1] + iVar8;
                do {
                    iVar4 = 1;
                    piVar5 = this->currentPlayerFullIDArray;
                    piVar6 = piVar7;
                    do {
                        piVar5 = piVar5 + 1;
                        if ((*piVar5 != -1) && (this->HASH_Section1023[this->currentPlayerSlotID][iVar8] != *piVar6)) {
                            this->DAT_GameCommandParam0 = iVar8;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_UNKNOWN);
                            this->currentPacketTotalSize
                                = this->currentPacketTotalSize + this->DAT_CurrentTransmitCommandPacketSize;
                            local_14 = local_14 + this->DAT_CurrentTransmitCommandPacketSize;
                            if (local_14 > (int)this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 5;
                                goto LAB_0048e84b;
                            }
                            break;
                        }
                        iVar4 = iVar4 + 1;
                        piVar6 = piVar6 + 0x14;
                    } while (iVar4 < 9);
                    iVar8 = iVar8 + 1;
                    piVar7 = piVar7 + 1;
                } while (iVar8 < 0x14);
            }
            iVar8 = 0;
        case 6:
            if ((this->sharedDesyncFlags[7] != 0) && (iVar8 < 3000)) {
                piVar7 = this->HASH_Entities[1] + iVar8;
                do {
                    iVar4 = 1;
                    piVar5 = this->currentPlayerFullIDArray;
                    piVar6 = piVar7;
                    do {
                        piVar5 = piVar5 + 1;
                        if ((*piVar5 != -1) && (this->HASH_Entities[this->currentPlayerSlotID][iVar8] != *piVar6)) {
                            this->DAT_GameCommandParam0 = iVar8;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_ENTITY);
                            this->currentPacketTotalSize
                                = this->currentPacketTotalSize + this->DAT_CurrentTransmitCommandPacketSize;
                            local_14 = local_14 + this->DAT_CurrentTransmitCommandPacketSize;
                            if (local_14 > (int)this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 6;
                                goto LAB_0048e84b;
                            }
                            break;
                        }
                        iVar4 = iVar4 + 1;
                        piVar6 = piVar6 + 3000;
                    } while (iVar4 < 9);
                    iVar8 = iVar8 + 1;
                    piVar7 = piVar7 + 1;
                } while (iVar8 < 3000);
            }
            iVar8 = 0;
        case 7:
            if ((this->sharedDesyncFlags[8] != 0) && (iVar8 < 0xa0)) {
                piVar7 = this->HASH_Moats[1] + iVar8;
                iVar4 = this->currentPlayerSlotID;
                do {
                    iVar2 = 1;
                    piVar5 = this->currentPlayerFullIDArray;
                    piVar6 = piVar7;
                    do {
                        piVar5 = piVar5 + 1;
                        if ((*piVar5 != -1)
                            && (paiVar1 = this->HASH_Moats + iVar4, iVar4 = this->currentPlayerSlotID,
                                (*paiVar1)[iVar8] != *piVar6)) {
                            this->DAT_GameCommandParam0 = iVar8;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_MOAT);
                            this->currentPacketTotalSize
                                = this->currentPacketTotalSize + this->DAT_CurrentTransmitCommandPacketSize;
                            local_14 = local_14 + this->DAT_CurrentTransmitCommandPacketSize;
                            iVar4 = this->currentPlayerSlotID;
                            if (local_14 > (int)this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 7;
                                goto LAB_0048e84b;
                            }
                            break;
                        }
                        iVar2 = iVar2 + 1;
                        piVar6 = piVar6 + 0xa0;
                    } while (iVar2 < 9);
                    iVar8 = iVar8 + 1;
                    piVar7 = piVar7 + 1;
                } while (iVar8 < 0xa0);
            }
            iVar8 = 0;
        case 8:
            if ((this->sharedDesyncFlags[9] != 0) && (iVar8 < 200)) {
                piVar7 = this->HASH_ClimbData[1] + iVar8;
                do {
                    iVar4 = 1;
                    piVar5 = this->currentPlayerFullIDArray;
                    piVar6 = piVar7;
                    do {
                        piVar5 = piVar5 + 1;
                        if ((*piVar5 != -1) && (this->HASH_ClimbData[this->currentPlayerSlotID][iVar8] != *piVar6)) {
                            this->DAT_GameCommandParam0 = iVar8;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_CLIMB_DATA);
                            this->currentPacketTotalSize
                                = this->currentPacketTotalSize + this->DAT_CurrentTransmitCommandPacketSize;
                            local_14 = local_14 + this->DAT_CurrentTransmitCommandPacketSize;
                            if (local_14 > (int)this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 8;
                                goto LAB_0048e84b;
                            }
                            break;
                        }
                        iVar4 = iVar4 + 1;
                        piVar6 = piVar6 + 200;
                    } while (iVar4 < 9);
                    iVar8 = iVar8 + 1;
                    piVar7 = piVar7 + 1;
                } while (iVar8 < 200);
            }
            iVar8 = 0;
        case 9:
            if ((this->sharedDesyncFlags[10] != 0) && (iVar8 < 0x28)) {
                piVar7 = this->HASH_PitchDitches[1] + iVar8;
                do {
                    iVar4 = 1;
                    piVar5 = this->currentPlayerFullIDArray;
                    piVar6 = piVar7;
                    do {
                        piVar5 = piVar5 + 1;
                        if ((*piVar5 != -1) && (this->HASH_PitchDitches[this->currentPlayerSlotID][iVar8] != *piVar6)) {
                            this->DAT_GameCommandParam0 = iVar8;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_PITCH_DITCH);
                            this->currentPacketTotalSize
                                = this->currentPacketTotalSize + this->DAT_CurrentTransmitCommandPacketSize;
                            local_14 = local_14 + this->DAT_CurrentTransmitCommandPacketSize;
                            if (local_14 > (int)this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 9;
                                goto LAB_0048e84b;
                            }
                            break;
                        }
                        iVar4 = iVar4 + 1;
                        piVar6 = piVar6 + 0x28;
                    } while (iVar4 < 9);
                    iVar8 = iVar8 + 1;
                    piVar7 = piVar7 + 1;
                } while (iVar8 < 0x28);
            }
            iVar8 = 0;
        case 10:
            if ((this->sharedDesyncFlags[0xb] != 0) && (iVar8 < 0x28)) {
                piVar7 = this->HASH_Unknown2[1] + iVar8;
                do {
                    iVar4 = 1;
                    piVar5 = this->currentPlayerFullIDArray;
                    piVar6 = piVar7;
                    do {
                        piVar5 = piVar5 + 1;
                        if ((*piVar5 != -1) && (this->HASH_Unknown2[this->currentPlayerSlotID][iVar8] != *piVar6)) {
                            this->DAT_GameCommandParam0 = iVar8;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_UNKNOWN2);
                            this->currentPacketTotalSize
                                = this->currentPacketTotalSize + this->DAT_CurrentTransmitCommandPacketSize;
                            local_14 = local_14 + this->DAT_CurrentTransmitCommandPacketSize;
                            if (local_14 > (int)this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 10;
                                goto LAB_0048e84b;
                            }
                            break;
                        }
                        iVar4 = iVar4 + 1;
                        piVar6 = piVar6 + 0x28;
                    } while (iVar4 < 9);
                    iVar8 = iVar8 + 1;
                    piVar7 = piVar7 + 1;
                } while (iVar8 < 0x28);
            }
            iVar8 = 0;
        case 0xb:
            if (this->sharedDesyncFlags[6] != 0) {
                if (iVar8 < 0x80) {
                    piVar7 = this->HASH_LogicalTileMap[1].hashDataArray[0].componentArray + iVar8;
                    do {
                        iVar4 = 1;
                        piVar5 = this->currentPlayerFullIDArray;
                        piVar6 = piVar7;
                        do {
                            piVar5 = piVar5 + 1;
                            if ((*piVar5 != -1)
                                && (this->HASH_LogicalTileMap[this->currentPlayerSlotID]
                                        .hashDataArray[0]
                                        .componentArray[iVar8]
                                    != *piVar6)) {
                                this->DAT_GameCommandParam0 = 0;
                                this->DAT_GameCommandParam1 = iVar8;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_SEND_RESYNC_LOGICALTILEMAP);
                                this->currentPacketTotalSize
                                    = this->currentPacketTotalSize + this->DAT_CurrentTransmitCommandPacketSize;
                                local_14 = local_14 + this->DAT_CurrentTransmitCommandPacketSize;
                                if (local_14 > (int)this->resyncPacketBudget) {
                                    this->somePacketSubTypeUnk = 0xb;
                                    goto LAB_0048e84b;
                                }
                                break;
                            }
                            iVar4 = iVar4 + 1;
                            piVar6 = piVar6 + 0xf00;
                        } while (iVar4 < 9);
                        iVar8 = iVar8 + 1;
                        piVar7 = piVar7 + 1;
                    } while (iVar8 < 0x80);
                }
                iVar8 = 1;
                iVar4 = 0;
            switchD_0048e739_caseD_c:
                if (iVar8 < 10) {
                    local_8 = (int*)(iVar8 << 7);
                    do {
                        if (iVar4 < 0x40) {
                            local_c
                                = this->HASH_LogicalTileMap[1].hashDataArray[0].componentArray + (int)local_8 + iVar4;
                            do {
                                iVar2 = 1;
                                piVar7 = this->currentPlayerFullIDArray;
                                piVar5 = local_c;
                                do {
                                    piVar7 = piVar7 + 1;
                                    if ((*piVar7 != -1)
                                        && (this->HASH_LogicalTileMap[this->currentPlayerSlotID]
                                                .hashDataArray[iVar8]
                                                .componentArray[iVar4]
                                            != *piVar5)) {
                                        this->DAT_GameCommandParam0 = iVar8;
                                        this->DAT_GameCommandParam1 = iVar4;
                                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                            this)(Commands::GCT_SEND_RESYNC_TILEMAPDATA2);
                                        this->currentPacketTotalSize
                                            = this->currentPacketTotalSize + this->DAT_CurrentTransmitCommandPacketSize;
                                        local_14 = local_14 + this->DAT_CurrentTransmitCommandPacketSize;
                                        if (local_14 > (int)this->resyncPacketBudget) {
                                            this->resyncResumeInnerIndex = iVar4 + 1;
                                            this->somePacketSubTypeUnk = 0xc;
                                            this->resyncResumeOuterIndex = iVar8;
                                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                                this)(Commands::GCT_QUIT_MULTIPLAYERGAME);
                                        }
                                        break;
                                    }
                                    iVar2 = iVar2 + 1;
                                    piVar5 = piVar5 + 0xf00;
                                } while (iVar2 < 9);
                                local_c = local_c + 1;
                                iVar4 = iVar4 + 1;
                            } while (iVar4 < 0x40);
                        }
                        local_8 = (int*)((int)local_8 + 0x80);
                        iVar8 = iVar8 + 1;
                        iVar4 = 0;
                    } while ((int)local_8 < 0x500);
                }
                iVar8 = 10;
                iVar4 = 0;
                goto switchD_0048e739_caseD_d;
            }
        }
        iVar8 = 0;
    switchD_0048e739_caseD_e:
        if ((this->sharedDesyncFlags[0xc] != 0) && (iVar8 < 9)) {
            piVar7 = this->HASH_AIVS[1] + iVar8;
            do {
                iVar4 = 1;
                piVar5 = this->currentPlayerFullIDArray;
                piVar6 = piVar7;
                do {
                    piVar5 = piVar5 + 1;
                    if ((*piVar5 != -1) && (this->HASH_AIVS[this->currentPlayerSlotID][iVar8] != *piVar6)) {
                        this->DAT_GameCommandParam0 = iVar8;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                            Commands::GCT_HOST_SHARE_AIV);
                        this->currentPacketTotalSize
                            = this->currentPacketTotalSize + this->DAT_CurrentTransmitCommandPacketSize;
                        local_14 = local_14 + this->DAT_CurrentTransmitCommandPacketSize;
                        if (local_14 > (int)this->resyncPacketBudget) {
                            this->somePacketSubTypeUnk = 0xe;
                            goto LAB_0048e84b;
                        }
                        break;
                    }
                    iVar4 = iVar4 + 1;
                    piVar6 = piVar6 + 9;
                } while (iVar4 < 9);
                iVar8 = iVar8 + 1;
                piVar7 = piVar7 + 1;
            } while (iVar8 < 9);
        }
        iVar8 = 0;
        goto switchD_0048e739_caseD_f;
    }

}
}
