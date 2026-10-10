#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using WindowsHelper::Enums::BOOLEnum;

    /*
      Full desync detection and resync broadcast pass. Compares the local player's hash arrays against   all other
      connected players for every game state category: Units, Buildings, Trees, Tribes,   PlayerDatas, Section1023,
      Entities, Moats, ClimbData, PitchDitches, Unknown2, AIVS, HeatMaps, and   LogicalTileMap. For each mismatch found,
      queues the appropriate GCT_SEND_RESYNC_* command. After   all categories, computes the worst-case lag average and
      sets syncStatus to 2, queuing   GCT_BROADCAST_SYNC_RELATED_STATUS.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0048DC50
    void GameSynchronyState::broadcastDesyncResyncCommands()
    {
        int* piVar1;
        int iVar2;
        DWORD DVar3;
        HashData* pHVar4;
        HashData* pHVar5;
        int iVar6;
        int (*paiVar7)[2500];
        int (*paiVar8)[2000];
        int (*paiVar9)[1250];
        int (*paiVar10)[20];
        int (*paiVar11)[3000];
        int (*paiVar12)[160];
        int (*paiVar13)[200];
        int (*paiVar14)[40];
        int (*paiVar15)[9];
        int (*paiVar16)[80];
        HashDataContainer* pHVar17;
        int (*paiVar18)[2500];
        int (*paiVar19)[2000];
        int (*paiVar20)[1250];
        int (*paiVar21)[20];
        int (*paiVar22)[3000];
        int (*paiVar23)[160];
        int (*paiVar24)[200];
        int (*paiVar25)[40];
        int (*paiVar26)[9];
        int (*paiVar27)[80];
        HashDataContainer* pHVar28;
        int* piVar29;
        int local_10;
        int local_c;
        HashData* local_8;
        HashData* local_4;
        piVar29 = this->receivedSyncStatusByPlayerUnk + 1;
        this->receivedSyncStatusByPlayerUnk[this->currentPlayerSlotID] = 1;
        iVar6 = 1;
        piVar1 = piVar29;
        while (piVar1[-0x404f9] == -1 || *piVar1 != 0) {
            iVar6 = iVar6 + 1;
            piVar1 = piVar1 + 1;
            if (8 < iVar6)
                goto LAB_0048dc9c;
        }
        if (!this->announcementReceivedBool) {
            DVar3 = timeGetTime();
            if (DVar3 - this->announcementReceiveTime < 0xea61) {}
            this->DAT_GameCommandParam0 = 0;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(Commands::GCT_KILL_GAME);
        }
        DVar3 = timeGetTime();
        if (DVar3 - this->announcementReceiveTime < 0xafc9) {}
        iVar6 = 1;
        do {
            if ((piVar29[-0x404f9] != -1) && (*piVar29 == 0)) {
                this->DAT_GameCommandParam1 = 0x3f;
                this->DAT_GameCommandParam0 = iVar6;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(Commands::GCT_LEAVE_GAME);
                *piVar29 = 2;
            }
            iVar6 = iVar6 + 1;
            piVar29 = piVar29 + 1;
        } while (iVar6 < 9);
    LAB_0048dc9c:
        iVar6 = 0;
        this->field65_0xb9c = 0;
        this->field66_0xba0 = 0;
        this->field67_0xba4 = 1;
        local_10 = 0;
        if (this->sharedDesyncFlags[0] != 0) {
            paiVar18 = this->HASH_Units + 1;
            do {
                iVar2 = 1;
                piVar29 = this->currentPlayerFullIDArray;
                paiVar7 = paiVar18;
                do {
                    piVar29 = piVar29 + 1;
                    if ((*piVar29 != -1) && (this->HASH_Units[this->currentPlayerSlotID][iVar6] != (*paiVar7)[0])) {
                        this->DAT_GameCommandParam0 = iVar6;
                        iVar2 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync, this)(
                            Commands::GCT_SEND_RESYNC_UNIT);
                        local_10 = local_10 + iVar2;
                        break;
                    }
                    iVar2 = iVar2 + 1;
                    paiVar7 = paiVar7 + 1;
                } while (iVar2 < 9);
                iVar6 = iVar6 + 1;
                paiVar18 = (int (*)[2500])(*paiVar18 + 1);
            } while (iVar6 < 0x9c4);
        }
        if (this->sharedDesyncFlags[1] != 0) {
            iVar6 = 0;
            paiVar19 = this->HASH_Buildings + 1;
            do {
                iVar2 = 1;
                piVar29 = this->currentPlayerFullIDArray;
                paiVar8 = paiVar19;
                do {
                    piVar29 = piVar29 + 1;
                    if ((*piVar29 != -1) && (this->HASH_Buildings[this->currentPlayerSlotID][iVar6] != (*paiVar8)[0])) {
                        this->DAT_GameCommandParam0 = iVar6;
                        iVar2 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync, this)(
                            Commands::GCT_SEND_RESYNC_BUILDING);
                        local_10 = local_10 + iVar2;
                        break;
                    }
                    iVar2 = iVar2 + 1;
                    paiVar8 = paiVar8 + 1;
                } while (iVar2 < 9);
                iVar6 = iVar6 + 1;
                paiVar19 = (int (*)[2000])(*paiVar19 + 1);
            } while (iVar6 < 2000);
        }
        if (this->sharedDesyncFlags[2] != 0) {
            iVar6 = 0;
            paiVar19 = this->HASH_Trees + 1;
            do {
                iVar2 = 1;
                piVar29 = this->currentPlayerFullIDArray;
                paiVar8 = paiVar19;
                do {
                    piVar29 = piVar29 + 1;
                    if ((*piVar29 != -1) && (this->HASH_Trees[this->currentPlayerSlotID][iVar6] != (*paiVar8)[0])) {
                        this->DAT_GameCommandParam0 = iVar6;
                        iVar2 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync, this)(
                            Commands::GCT_SEND_RESYNC_TREE);
                        local_10 = local_10 + iVar2;
                        break;
                    }
                    iVar2 = iVar2 + 1;
                    paiVar8 = paiVar8 + 1;
                } while (iVar2 < 9);
                iVar6 = iVar6 + 1;
                paiVar19 = (int (*)[2000])(*paiVar19 + 1);
            } while (iVar6 < 2000);
        }
        if (this->sharedDesyncFlags[3] != 0) {
            iVar6 = 0;
            paiVar20 = this->HASH_Tribes + 1;
            do {
                iVar2 = 1;
                piVar29 = this->currentPlayerFullIDArray;
                paiVar9 = paiVar20;
                do {
                    piVar29 = piVar29 + 1;
                    if ((*piVar29 != -1) && (this->HASH_Tribes[this->currentPlayerSlotID][iVar6] != (*paiVar9)[0])) {
                        this->DAT_GameCommandParam0 = iVar6;
                        iVar2 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync, this)(
                            Commands::GCT_SEND_RESYNC_UNITSELECTION);
                        local_10 = local_10 + iVar2;
                        break;
                    }
                    iVar2 = iVar2 + 1;
                    paiVar9 = paiVar9 + 1;
                } while (iVar2 < 9);
                iVar6 = iVar6 + 1;
                paiVar20 = (int (*)[1250])(*paiVar20 + 1);
            } while (iVar6 < 0x4e2);
        }
        if (this->sharedDesyncFlags[4] != 0) {
            iVar6 = 0;
            paiVar26 = this->HASH_PlayerDatas + 1;
            do {
                iVar2 = 1;
                piVar29 = this->currentPlayerFullIDArray;
                paiVar15 = paiVar26;
                do {
                    piVar29 = piVar29 + 1;
                    if ((*piVar29 != -1)
                        && (this->HASH_PlayerDatas[this->currentPlayerSlotID][iVar6] != (*paiVar15)[0])) {
                        this->DAT_GameCommandParam0 = iVar6;
                        iVar2 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync, this)(
                            Commands::GCT_SEND_RESYNC_PLAYERDATA);
                        local_10 = local_10 + iVar2;
                        break;
                    }
                    iVar2 = iVar2 + 1;
                    paiVar15 = paiVar15 + 1;
                } while (iVar2 < 9);
                iVar6 = iVar6 + 1;
                paiVar26 = (int (*)[9])(*paiVar26 + 1);
            } while (iVar6 < 9);
        }
        if (this->sharedDesyncFlags[5] != 0) {
            paiVar21 = this->HASH_Section1023 + 1;
            iVar6 = 0;
            do {
                iVar2 = 1;
                piVar29 = this->currentPlayerFullIDArray;
                paiVar10 = paiVar21;
                do {
                    piVar29 = piVar29 + 1;
                    if ((*piVar29 != -1)
                        && (this->HASH_Section1023[this->currentPlayerSlotID][iVar6] != (*paiVar10)[0])) {
                        this->DAT_GameCommandParam0 = iVar6;
                        iVar2 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync, this)(
                            Commands::GCT_SEND_RESYNC_UNKNOWN);
                        local_10 = local_10 + iVar2;
                        break;
                    }
                    iVar2 = iVar2 + 1;
                    paiVar10 = paiVar10 + 1;
                } while (iVar2 < 9);
                iVar6 = iVar6 + 1;
                paiVar21 = (int (*)[20])(*paiVar21 + 1);
            } while (iVar6 < 0x14);
        }
        if (this->sharedDesyncFlags[7] != 0) {
            iVar6 = 0;
            paiVar22 = this->HASH_Entities + 1;
            do {
                iVar2 = 1;
                piVar29 = this->currentPlayerFullIDArray;
                paiVar11 = paiVar22;
                do {
                    piVar29 = piVar29 + 1;
                    if ((*piVar29 != -1) && (this->HASH_Entities[this->currentPlayerSlotID][iVar6] != (*paiVar11)[0])) {
                        this->DAT_GameCommandParam0 = iVar6;
                        iVar2 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync, this)(
                            Commands::GCT_SEND_RESYNC_ENTITY);
                        local_10 = local_10 + iVar2;
                        break;
                    }
                    iVar2 = iVar2 + 1;
                    paiVar11 = paiVar11 + 1;
                } while (iVar2 < 9);
                iVar6 = iVar6 + 1;
                paiVar22 = (int (*)[3000])(*paiVar22 + 1);
            } while (iVar6 < 3000);
        }
        if (this->sharedDesyncFlags[8] != 0) {
            iVar6 = 0;
            paiVar23 = this->HASH_Moats + 1;
            do {
                iVar2 = 1;
                piVar29 = this->currentPlayerFullIDArray;
                paiVar12 = paiVar23;
                do {
                    piVar29 = piVar29 + 1;
                    if ((*piVar29 != -1) && (this->HASH_Moats[this->currentPlayerSlotID][iVar6] != (*paiVar12)[0])) {
                        this->DAT_GameCommandParam0 = iVar6;
                        iVar2 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync, this)(
                            Commands::GCT_SEND_RESYNC_MOAT);
                        local_10 = local_10 + iVar2;
                        break;
                    }
                    iVar2 = iVar2 + 1;
                    paiVar12 = paiVar12 + 1;
                } while (iVar2 < 9);
                iVar6 = iVar6 + 1;
                paiVar23 = (int (*)[160])(*paiVar23 + 1);
            } while (iVar6 < 0xa0);
        }
        if (this->sharedDesyncFlags[9] != 0) {
            iVar6 = 0;
            paiVar24 = this->HASH_ClimbData + 1;
            do {
                iVar2 = 1;
                piVar29 = this->currentPlayerFullIDArray;
                paiVar13 = paiVar24;
                do {
                    piVar29 = piVar29 + 1;
                    if ((*piVar29 != -1)
                        && (this->HASH_ClimbData[this->currentPlayerSlotID][iVar6] != (*paiVar13)[0])) {
                        this->DAT_GameCommandParam0 = iVar6;
                        iVar2 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync, this)(
                            Commands::GCT_SEND_RESYNC_CLIMB_DATA);
                        local_10 = local_10 + iVar2;
                        break;
                    }
                    iVar2 = iVar2 + 1;
                    paiVar13 = paiVar13 + 1;
                } while (iVar2 < 9);
                iVar6 = iVar6 + 1;
                paiVar24 = (int (*)[200])(*paiVar24 + 1);
            } while (iVar6 < 200);
        }
        if (this->sharedDesyncFlags[10] != 0) {
            iVar6 = 0;
            paiVar25 = this->HASH_PitchDitches + 1;
            do {
                iVar2 = 1;
                piVar29 = this->currentPlayerFullIDArray;
                paiVar14 = paiVar25;
                do {
                    piVar29 = piVar29 + 1;
                    if ((*piVar29 != -1)
                        && (this->HASH_PitchDitches[this->currentPlayerSlotID][iVar6] != (*paiVar14)[0])) {
                        this->DAT_GameCommandParam0 = iVar6;
                        iVar2 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync, this)(
                            Commands::GCT_SEND_RESYNC_PITCH_DITCH);
                        local_10 = local_10 + iVar2;
                        break;
                    }
                    iVar2 = iVar2 + 1;
                    paiVar14 = paiVar14 + 1;
                } while (iVar2 < 9);
                iVar6 = iVar6 + 1;
                paiVar25 = (int (*)[40])(*paiVar25 + 1);
            } while (iVar6 < 0x28);
        }
        if (this->sharedDesyncFlags[0xb] != 0) {
            iVar6 = 0;
            paiVar25 = this->HASH_Unknown2 + 1;
            do {
                iVar2 = 1;
                piVar29 = this->currentPlayerFullIDArray;
                paiVar14 = paiVar25;
                do {
                    piVar29 = piVar29 + 1;
                    if ((*piVar29 != -1) && (this->HASH_Unknown2[this->currentPlayerSlotID][iVar6] != (*paiVar14)[0])) {
                        this->DAT_GameCommandParam0 = iVar6;
                        iVar2 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync, this)(
                            Commands::GCT_SEND_RESYNC_UNKNOWN2);
                        local_10 = local_10 + iVar2;
                        break;
                    }
                    iVar2 = iVar2 + 1;
                    paiVar14 = paiVar14 + 1;
                } while (iVar2 < 9);
                iVar6 = iVar6 + 1;
                paiVar25 = (int (*)[40])(*paiVar25 + 1);
            } while (iVar6 < 0x28);
        }
        if (this->sharedDesyncFlags[0xc] != 0) {
            iVar6 = 0;
            paiVar26 = this->HASH_AIVS + 1;
            do {
                iVar2 = 1;
                piVar29 = this->currentPlayerFullIDArray;
                paiVar15 = paiVar26;
                do {
                    piVar29 = piVar29 + 1;
                    if ((*piVar29 != -1) && (this->HASH_AIVS[this->currentPlayerSlotID][iVar6] != (*paiVar15)[0])) {
                        this->DAT_GameCommandParam0 = iVar6;
                        iVar2 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync, this)(
                            Commands::GCT_HOST_SHARE_AIV);
                        local_10 = local_10 + iVar2;
                        break;
                    }
                    iVar2 = iVar2 + 1;
                    paiVar15 = paiVar15 + 1;
                } while (iVar2 < 9);
                iVar6 = iVar6 + 1;
                paiVar26 = (int (*)[9])(*paiVar26 + 1);
            } while (iVar6 < 9);
        }
        if (this->sharedDesyncFlags[0xd] != 0) {
            paiVar27 = this->HASH_HeatMaps + 1;
            iVar6 = 0;
            do {
                iVar2 = 1;
                piVar29 = this->currentPlayerFullIDArray;
                paiVar16 = paiVar27;
                do {
                    piVar29 = piVar29 + 1;
                    if ((*piVar29 != -1) && (this->HASH_HeatMaps[this->currentPlayerSlotID][iVar6] != (*paiVar16)[0])) {
                        this->DAT_GameCommandParam0 = iVar6;
                        iVar2 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync, this)(
                            Commands::GCT_HOST_SHARE_HEATMAP);
                        local_10 = local_10 + iVar2;
                        break;
                    }
                    iVar2 = iVar2 + 1;
                    paiVar16 = paiVar16 + 1;
                } while (iVar2 < 9);
                iVar6 = iVar6 + 1;
                paiVar27 = (int (*)[80])(*paiVar27 + 1);
            } while (iVar6 < 0x50);
        }
        if (this->sharedDesyncFlags[6] != 0) {
            iVar6 = 0;
            pHVar28 = this->HASH_LogicalTileMap + 1;
            do {
                iVar2 = 1;
                piVar29 = this->currentPlayerFullIDArray;
                pHVar17 = pHVar28;
                do {
                    piVar29 = piVar29 + 1;
                    if ((*piVar29 != -1)
                        && (this->HASH_LogicalTileMap[this->currentPlayerSlotID].hashDataArray[0].componentArray[iVar6]
                            != pHVar17->hashDataArray[0].componentArray[0])) {
                        this->DAT_GameCommandParam0 = 0;
                        this->DAT_GameCommandParam1 = iVar6;
                        iVar2 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync, this)(
                            Commands::GCT_SEND_RESYNC_LOGICALTILEMAP);
                        local_10 = local_10 + iVar2;
                        break;
                    }
                    iVar2 = iVar2 + 1;
                    pHVar17 = pHVar17 + 1;
                } while (iVar2 < 9);
                iVar6 = iVar6 + 1;
                pHVar28 = (HashDataContainer*)(pHVar28->hashDataArray[0].componentArray + 1);
            } while (iVar6 < 128);
            local_c = 1;
            local_4 = this->HASH_LogicalTileMap[1].hashDataArray;
            do {
                local_4 = local_4 + 1;
                iVar6 = 0;
                pHVar4 = local_4;
                do {
                    iVar2 = 1;
                    piVar29 = this->currentPlayerFullIDArray;
                    pHVar5 = pHVar4;
                    do {
                        piVar29 = piVar29 + 1;
                        if ((*piVar29 != -1)
                            && (this->HASH_LogicalTileMap[this->currentPlayerSlotID]
                                    .hashDataArray[local_c]
                                    .componentArray[iVar6]
                                != pHVar5->componentArray[0])) {
                            this->DAT_GameCommandParam0 = local_c;
                            this->DAT_GameCommandParam1 = iVar6;
                            iVar2 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                                this)(Commands::GCT_SEND_RESYNC_TILEMAPDATA2);
                            local_10 = local_10 + iVar2;
                            break;
                        }
                        iVar2 = iVar2 + 1;
                        pHVar5 = pHVar5 + 0x1e;
                    } while (iVar2 < 9);
                    iVar6 = iVar6 + 1;
                    pHVar4 = (HashData*)(pHVar4->componentArray + 1);
                } while (iVar6 < 0x40);
                local_c = local_c + 1;
            } while (local_c < 10);
            local_c = 10;
            local_8 = this->HASH_LogicalTileMap[1].hashDataArray + 10;
            do {
                iVar6 = 0;
                pHVar4 = local_8;
                do {
                    iVar2 = 1;
                    piVar29 = this->currentPlayerFullIDArray;
                    pHVar5 = pHVar4;
                    do {
                        piVar29 = piVar29 + 1;
                        if ((*piVar29 != -1)
                            && (this->HASH_LogicalTileMap[this->currentPlayerSlotID]
                                    .hashDataArray[local_c]
                                    .componentArray[iVar6]
                                != pHVar5->componentArray[0])) {
                            this->DAT_GameCommandParam0 = local_c;
                            this->DAT_GameCommandParam1 = iVar6;
                            iVar2 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                                this)(Commands::GCT_SEND_RESYNC_TILEMAPDATA1);
                            local_10 = local_10 + iVar2;
                            break;
                        }
                        iVar2 = iVar2 + 1;
                        pHVar5 = pHVar5 + 0x1e;
                    } while (iVar2 < 9);
                    iVar6 = iVar6 + 1;
                    pHVar4 = (HashData*)(pHVar4->componentArray + 1);
                } while (iVar6 < 0x20);
                local_c = local_c + 1;
                local_8 = local_8 + 1;
            } while (local_c < 0x1e);
        }
        iVar6 = 0;
        if ((this->currentPlayerFullIDArray[1] != -1) && (0 < this->connectionLagInfoArray[1].average1)) {
            iVar6 = this->connectionLagInfoArray[1].average1;
        }
        if ((this->currentPlayerFullIDArray[2] != -1) && (iVar6 < this->connectionLagInfoArray[2].average1)) {
            iVar6 = this->connectionLagInfoArray[2].average1;
        }
        if ((this->currentPlayerFullIDArray[3] != -1) && (iVar6 < this->connectionLagInfoArray[3].average1)) {
            iVar6 = this->connectionLagInfoArray[3].average1;
        }
        if ((this->currentPlayerFullIDArray[4] != -1) && (iVar6 < this->connectionLagInfoArray[4].average1)) {
            iVar6 = this->connectionLagInfoArray[4].average1;
        }
        if ((this->currentPlayerFullIDArray[5] != -1) && (iVar6 < this->connectionLagInfoArray[5].average1)) {
            iVar6 = this->connectionLagInfoArray[5].average1;
        }
        if ((this->currentPlayerFullIDArray[6] != -1) && (iVar6 < this->connectionLagInfoArray[6].average1)) {
            iVar6 = this->connectionLagInfoArray[6].average1;
        }
        if ((this->currentPlayerFullIDArray[7] != -1) && (iVar6 < this->connectionLagInfoArray[7].average1)) {
            iVar6 = this->connectionLagInfoArray[7].average1;
        }
        if ((this->currentPlayerFullIDArray[8] != -1) && (iVar6 < this->connectionLagInfoArray[8].average1)) {
            iVar6 = this->connectionLagInfoArray[8].average1;
        }
        if (iVar6 < 2) {
            this->resyncPacketBudget = 40000;
        } else {
            this->resyncPacketBudget = (-(uint)(iVar6 != 2) & 0xffff8ad0) + 40000;
        }
        this->somePacketSubTypeUnk = 0;
        this->resyncResumeOuterIndex = 0;
        this->resyncResumeInnerIndex = 0;
        this->syncRelatedStatusArray[0] = 1;
        this->syncRelatedStatusArray[1] = 1;
        this->syncRelatedStatusArray[2] = 1;
        this->syncRelatedStatusArray[3] = 1;
        this->syncRelatedStatusArray[4] = 1;
        this->syncRelatedStatusArray[5] = 1;
        this->syncRelatedStatusArray[6] = 1;
        this->syncRelatedStatusArray[7] = 1;
        this->syncRelatedStatusArray[8] = 1;
        this->resyncTransferTotalSize = local_10;
        this->currentPacketTotalSize = 0;
        this->syncStatus = 2;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
            (Commands::GameCommandType)(Commands::GCT_BROADCAST_SYNC_RELATED_STATUS_1
                | Commands::GCT_MULTIPLAYER_INITIATE_ANNOUNCE_HOST));
    }

}
}
