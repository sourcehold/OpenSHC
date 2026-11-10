#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048DC50
    void GameSynchronyState::broadcastDesyncResyncCommands()
    {
        // Reading the player slot, and queuing the leave and kill commands, through the global instance is needed
        // for the match.
        this->receivedSyncStatusByPlayerUnk[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
        // Wait for every player's sync status: 45 seconds after the announcement the missing players are dropped,
        // and without an announcement the game is ended after 60 seconds.
        for (int player = 1; player < 9; ++player) {
            if (this->currentPlayerFullIDArray[player] == -1 || this->receivedSyncStatusByPlayerUnk[player] != 0) {
                continue;
            }
            if (this->announcementReceivedBool) {
                if (timeGetTime() - this->announcementReceiveTime <= 45000) {
                    return;
                }
                for (int other = 1; other < 9; ++other) {
                    if (this->currentPlayerFullIDArray[other] != -1
                        && this->receivedSyncStatusByPlayerUnk[other] == 0) {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = other;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 63;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(Commands::GCT_LEAVE_GAME);
                        this->receivedSyncStatusByPlayerUnk[other] = 2;
                    }
                }
                break;
            }
            if (timeGetTime() - this->announcementReceiveTime <= 60000) {
                return;
            }
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                Commands::GCT_KILL_GAME);
            return;
        }
        this->field_0xb9c = 0;
        this->field_0xba0 = 0;
        this->field_0xba4 = 1;
        // Add up the size of the resync command for every entry whose hash differs from an active player's.
        int resyncSize = 0;
        if (this->sharedDesyncFlags[0]) {
            for (int index = 0; index < 2500; ++index) {
                for (int player = 1; player < 9; ++player) {
                    if (this->currentPlayerFullIDArray[player] != -1
                        && this->HASH_Units[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                            != this->HASH_Units[player][index]) {
                        this->DAT_GameCommandParam0 = index;
                        resyncSize += MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                            this)(Commands::GCT_SEND_RESYNC_UNIT);
                        break;
                    }
                }
            }
        }
        if (this->sharedDesyncFlags[1]) {
            for (int index = 0; index < 2000; ++index) {
                for (int player = 1; player < 9; ++player) {
                    if (this->currentPlayerFullIDArray[player] != -1
                        && this->HASH_Buildings[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                            != this->HASH_Buildings[player][index]) {
                        this->DAT_GameCommandParam0 = index;
                        resyncSize += MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                            this)(Commands::GCT_SEND_RESYNC_BUILDING);
                        break;
                    }
                }
            }
        }
        if (this->sharedDesyncFlags[2]) {
            for (int index = 0; index < 2000; ++index) {
                for (int player = 1; player < 9; ++player) {
                    if (this->currentPlayerFullIDArray[player] != -1
                        && this->HASH_Trees[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                            != this->HASH_Trees[player][index]) {
                        this->DAT_GameCommandParam0 = index;
                        resyncSize += MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                            this)(Commands::GCT_SEND_RESYNC_TREE);
                        break;
                    }
                }
            }
        }
        if (this->sharedDesyncFlags[3]) {
            for (int index = 0; index < 1250; ++index) {
                for (int player = 1; player < 9; ++player) {
                    if (this->currentPlayerFullIDArray[player] != -1
                        && this->HASH_Tribes[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                            != this->HASH_Tribes[player][index]) {
                        this->DAT_GameCommandParam0 = index;
                        resyncSize += MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                            this)(Commands::GCT_SEND_RESYNC_UNITSELECTION);
                        break;
                    }
                }
            }
        }
        if (this->sharedDesyncFlags[4]) {
            for (int index = 0; index < 9; ++index) {
                for (int player = 1; player < 9; ++player) {
                    if (this->currentPlayerFullIDArray[player] != -1
                        && this->HASH_PlayerDatas[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                            != this->HASH_PlayerDatas[player][index]) {
                        this->DAT_GameCommandParam0 = index;
                        resyncSize += MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                            this)(Commands::GCT_SEND_RESYNC_PLAYERDATA);
                        break;
                    }
                }
            }
        }
        if (this->sharedDesyncFlags[5]) {
            for (int index = 0; index < 20; ++index) {
                for (int player = 1; player < 9; ++player) {
                    if (this->currentPlayerFullIDArray[player] != -1
                        && this->HASH_Section1023[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                            != this->HASH_Section1023[player][index]) {
                        this->DAT_GameCommandParam0 = index;
                        resyncSize += MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                            this)(Commands::GCT_SEND_RESYNC_UNKNOWN);
                        break;
                    }
                }
            }
        }
        if (this->sharedDesyncFlags[7]) {
            for (int index = 0; index < 3000; ++index) {
                for (int player = 1; player < 9; ++player) {
                    if (this->currentPlayerFullIDArray[player] != -1
                        && this->HASH_Entities[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                            != this->HASH_Entities[player][index]) {
                        this->DAT_GameCommandParam0 = index;
                        resyncSize += MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                            this)(Commands::GCT_SEND_RESYNC_ENTITY);
                        break;
                    }
                }
            }
        }
        if (this->sharedDesyncFlags[8]) {
            for (int index = 0; index < 160; ++index) {
                for (int player = 1; player < 9; ++player) {
                    if (this->currentPlayerFullIDArray[player] != -1
                        && this->HASH_Moats[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                            != this->HASH_Moats[player][index]) {
                        this->DAT_GameCommandParam0 = index;
                        resyncSize += MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                            this)(Commands::GCT_SEND_RESYNC_MOAT);
                        break;
                    }
                }
            }
        }
        if (this->sharedDesyncFlags[9]) {
            for (int index = 0; index < 200; ++index) {
                for (int player = 1; player < 9; ++player) {
                    if (this->currentPlayerFullIDArray[player] != -1
                        && this->HASH_ClimbData[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                            != this->HASH_ClimbData[player][index]) {
                        this->DAT_GameCommandParam0 = index;
                        resyncSize += MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                            this)(Commands::GCT_SEND_RESYNC_CLIMB_DATA);
                        break;
                    }
                }
            }
        }
        if (this->sharedDesyncFlags[10]) {
            for (int index = 0; index < 40; ++index) {
                for (int player = 1; player < 9; ++player) {
                    if (this->currentPlayerFullIDArray[player] != -1
                        && this->HASH_PitchDitches[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                            != this->HASH_PitchDitches[player][index]) {
                        this->DAT_GameCommandParam0 = index;
                        resyncSize += MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                            this)(Commands::GCT_SEND_RESYNC_PITCH_DITCH);
                        break;
                    }
                }
            }
        }
        if (this->sharedDesyncFlags[11]) {
            for (int index = 0; index < 40; ++index) {
                for (int player = 1; player < 9; ++player) {
                    if (this->currentPlayerFullIDArray[player] != -1
                        && this->HASH_Unknown2[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                            != this->HASH_Unknown2[player][index]) {
                        this->DAT_GameCommandParam0 = index;
                        resyncSize += MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                            this)(Commands::GCT_SEND_RESYNC_UNKNOWN2);
                        break;
                    }
                }
            }
        }
        if (this->sharedDesyncFlags[12]) {
            for (int index = 0; index < 9; ++index) {
                for (int player = 1; player < 9; ++player) {
                    if (this->currentPlayerFullIDArray[player] != -1
                        && this->HASH_AIVS[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                            != this->HASH_AIVS[player][index]) {
                        this->DAT_GameCommandParam0 = index;
                        resyncSize += MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                            this)(Commands::GCT_HOST_SHARE_AIV);
                        break;
                    }
                }
            }
        }
        if (this->sharedDesyncFlags[13]) {
            for (int index = 0; index < 80; ++index) {
                for (int player = 1; player < 9; ++player) {
                    if (this->currentPlayerFullIDArray[player] != -1
                        && this->HASH_HeatMaps[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                            != this->HASH_HeatMaps[player][index]) {
                        this->DAT_GameCommandParam0 = index;
                        resyncSize += MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                            this)(Commands::GCT_HOST_SHARE_HEATMAP);
                        break;
                    }
                }
            }
        }
        // One row counter for both tile map loops: a counter per loop changes the stack slots.
        int row;
        if (this->sharedDesyncFlags[6]) {
            for (int index = 0; index < 128; ++index) {
                for (int player = 1; player < 9; ++player) {
                    if (this->currentPlayerFullIDArray[player] != -1
                        && this->HASH_LogicalTileMap[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .hashDataArray[0]
                                .componentArray[index]
                            != this->HASH_LogicalTileMap[player].hashDataArray[0].componentArray[index]) {
                        this->DAT_GameCommandParam0 = 0;
                        this->DAT_GameCommandParam1 = index;
                        resyncSize += MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                            this)(Commands::GCT_SEND_RESYNC_LOGICALTILEMAP);
                        break;
                    }
                }
            }
            for (row = 1; row < 10; ++row) {
                for (int entry = 0; entry < 64; ++entry) {
                    for (int player = 1; player < 9; ++player) {
                        if (this->currentPlayerFullIDArray[player] != -1
                            && this->HASH_LogicalTileMap[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .hashDataArray[row]
                                    .componentArray[entry]
                                != this->HASH_LogicalTileMap[player].hashDataArray[row].componentArray[entry]) {
                            this->DAT_GameCommandParam0 = row;
                            this->DAT_GameCommandParam1 = entry;
                            resyncSize
                                += MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                                    this)(Commands::GCT_SEND_RESYNC_TILEMAPDATA2);
                            break;
                        }
                    }
                }
            }
            for (row = 10; row < 30; ++row) {
                for (int entry = 0; entry < 32; ++entry) {
                    for (int player = 1; player < 9; ++player) {
                        if (this->currentPlayerFullIDArray[player] != -1
                            && this->HASH_LogicalTileMap[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .hashDataArray[row]
                                    .componentArray[entry]
                                != this->HASH_LogicalTileMap[player].hashDataArray[row].componentArray[entry]) {
                            this->DAT_GameCommandParam0 = row;
                            this->DAT_GameCommandParam1 = entry;
                            resyncSize
                                += MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendLongerDataSuchAsResync,
                                    this)(Commands::GCT_SEND_RESYNC_TILEMAPDATA1);
                            break;
                        }
                    }
                }
            }
        }
        // A slow connection gets a smaller budget per resync step.
        int worstLag = 0;
        for (int player = 1; player < 9; ++player) {
            if (this->currentPlayerFullIDArray[player] != -1
                && this->connectionLagInfoArray[player].average1 > worstLag) {
                worstLag = this->connectionLagInfoArray[player].average1;
            }
        }
        if (worstLag < 2) {
            this->resyncPacketBudget = 40000;
        } else if (worstLag == 2) {
            this->resyncPacketBudget = 40000;
        } else {
            this->resyncPacketBudget = 10000;
        }
        this->somePacketSubTypeUnk = 0;
        this->resyncResumeOuterIndex = 0;
        this->resyncResumeInnerIndex = 0;
        for (int player = 0; player < 9; ++player) {
            this->syncRelatedStatusArray[player] = 1;
        }
        this->resyncTransferTotalSize = resyncSize;
        this->currentPacketTotalSize = 0;
        this->syncStatus = 2;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(Commands::GCT_UNKNOWN_90);
    }

}
}
