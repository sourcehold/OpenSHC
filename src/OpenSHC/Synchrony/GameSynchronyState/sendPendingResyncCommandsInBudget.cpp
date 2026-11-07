#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048E680
    void GameSynchronyState::sendPendingResyncCommandsInBudget()
    {
        int index = this->resyncResumeOuterIndex;
        int entry = this->resyncResumeInnerIndex;
        int sentSize = 0;
        // 45 seconds after the announcement, players whose sync status is still 0 are dropped.
        for (int player = 1; player < 9; ++player) {
            if (this->syncRelatedStatusArray[player] != 0) {
                continue;
            }
            if (!this->announcementReceivedBool) {
                return;
            }
            if (timeGetTime() - this->announcementReceiveTime <= 45000) {
                return;
            }
            for (int other = 1; other < 9; ++other) {
                if (this->syncRelatedStatusArray[other] == 0) {
                    // Queuing the leave command through the global instance is needed for the match.
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = other;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 63;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_LEAVE_GAME);
                    this->syncRelatedStatusArray[other] = 1;
                }
            }
            break;
        }
        // Resume where the last call ran out of budget; each category falls through to the next. Reading the slot
        // through the global instance is needed for the match.
        // One row counter for both tile map loops: a counter per loop changes the stack slots.
        int row;
        switch (this->somePacketSubTypeUnk) {
        default:
            index = 0;
        case 0:
            if (this->sharedDesyncFlags[0]) {
                for (; index < 2500; ++index) {
                    for (int player = 1; player < 9; ++player) {
                        if (this->currentPlayerFullIDArray[player] != -1
                            && this->HASH_Units[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                                != this->HASH_Units[player][index]) {
                            this->DAT_GameCommandParam0 = index;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_UNIT);
                            this->currentPacketTotalSize += this->DAT_CurrentTransmitCommandPacketSize;
                            sentSize += this->DAT_CurrentTransmitCommandPacketSize;
                            if (sentSize > this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 0;
                                this->resyncResumeOuterIndex = index + 1;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_QUIT_MULTIPLAYERGAME);
                                return;
                            }
                            break;
                        }
                    }
                }
            }
            index = 0;
        case 1:
            if (this->sharedDesyncFlags[1]) {
                for (; index < 2000; ++index) {
                    for (int player = 1; player < 9; ++player) {
                        if (this->currentPlayerFullIDArray[player] != -1
                            && this->HASH_Buildings[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                                != this->HASH_Buildings[player][index]) {
                            this->DAT_GameCommandParam0 = index;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_BUILDING);
                            this->currentPacketTotalSize += this->DAT_CurrentTransmitCommandPacketSize;
                            sentSize += this->DAT_CurrentTransmitCommandPacketSize;
                            if (sentSize > this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 1;
                                this->resyncResumeOuterIndex = index + 1;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_QUIT_MULTIPLAYERGAME);
                                return;
                            }
                            break;
                        }
                    }
                }
            }
            index = 0;
        case 2:
            if (this->sharedDesyncFlags[2]) {
                for (; index < 2000; ++index) {
                    for (int player = 1; player < 9; ++player) {
                        if (this->currentPlayerFullIDArray[player] != -1
                            && this->HASH_Trees[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                                != this->HASH_Trees[player][index]) {
                            this->DAT_GameCommandParam0 = index;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_TREE);
                            this->currentPacketTotalSize += this->DAT_CurrentTransmitCommandPacketSize;
                            sentSize += this->DAT_CurrentTransmitCommandPacketSize;
                            if (sentSize > this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 2;
                                this->resyncResumeOuterIndex = index + 1;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_QUIT_MULTIPLAYERGAME);
                                return;
                            }
                            break;
                        }
                    }
                }
            }
            index = 0;
        case 3:
            if (this->sharedDesyncFlags[3]) {
                for (; index < 1250; ++index) {
                    for (int player = 1; player < 9; ++player) {
                        if (this->currentPlayerFullIDArray[player] != -1
                            && this->HASH_Tribes[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                                != this->HASH_Tribes[player][index]) {
                            this->DAT_GameCommandParam0 = index;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_UNITSELECTION);
                            this->currentPacketTotalSize += this->DAT_CurrentTransmitCommandPacketSize;
                            sentSize += this->DAT_CurrentTransmitCommandPacketSize;
                            if (sentSize > this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 3;
                                this->resyncResumeOuterIndex = index + 1;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_QUIT_MULTIPLAYERGAME);
                                return;
                            }
                            break;
                        }
                    }
                }
            }
            index = 0;
        case 4:
            if (this->sharedDesyncFlags[4]) {
                for (; index < 9; ++index) {
                    for (int player = 1; player < 9; ++player) {
                        if (this->currentPlayerFullIDArray[player] != -1
                            && this->HASH_PlayerDatas[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                                != this->HASH_PlayerDatas[player][index]) {
                            this->DAT_GameCommandParam0 = index;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_PLAYERDATA);
                            this->currentPacketTotalSize += this->DAT_CurrentTransmitCommandPacketSize;
                            sentSize += this->DAT_CurrentTransmitCommandPacketSize;
                            if (sentSize > this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 4;
                                this->resyncResumeOuterIndex = index + 1;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_QUIT_MULTIPLAYERGAME);
                                return;
                            }
                            break;
                        }
                    }
                }
            }
            index = 0;
        case 5:
            if (this->sharedDesyncFlags[5]) {
                for (; index < 20; ++index) {
                    for (int player = 1; player < 9; ++player) {
                        if (this->currentPlayerFullIDArray[player] != -1
                            && this->HASH_Section1023[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                                != this->HASH_Section1023[player][index]) {
                            this->DAT_GameCommandParam0 = index;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_UNKNOWN);
                            this->currentPacketTotalSize += this->DAT_CurrentTransmitCommandPacketSize;
                            sentSize += this->DAT_CurrentTransmitCommandPacketSize;
                            if (sentSize > this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 5;
                                this->resyncResumeOuterIndex = index + 1;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_QUIT_MULTIPLAYERGAME);
                                return;
                            }
                            break;
                        }
                    }
                }
            }
            index = 0;
        case 6:
            if (this->sharedDesyncFlags[7]) {
                for (; index < 3000; ++index) {
                    for (int player = 1; player < 9; ++player) {
                        if (this->currentPlayerFullIDArray[player] != -1
                            && this->HASH_Entities[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                                != this->HASH_Entities[player][index]) {
                            this->DAT_GameCommandParam0 = index;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_ENTITY);
                            this->currentPacketTotalSize += this->DAT_CurrentTransmitCommandPacketSize;
                            sentSize += this->DAT_CurrentTransmitCommandPacketSize;
                            if (sentSize > this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 6;
                                this->resyncResumeOuterIndex = index + 1;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_QUIT_MULTIPLAYERGAME);
                                return;
                            }
                            break;
                        }
                    }
                }
            }
            index = 0;
        case 7:
            if (this->sharedDesyncFlags[8]) {
                for (; index < 160; ++index) {
                    for (int player = 1; player < 9; ++player) {
                        if (this->currentPlayerFullIDArray[player] != -1
                            && this->HASH_Moats[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                                != this->HASH_Moats[player][index]) {
                            this->DAT_GameCommandParam0 = index;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_MOAT);
                            this->currentPacketTotalSize += this->DAT_CurrentTransmitCommandPacketSize;
                            sentSize += this->DAT_CurrentTransmitCommandPacketSize;
                            if (sentSize > this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 7;
                                this->resyncResumeOuterIndex = index + 1;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_QUIT_MULTIPLAYERGAME);
                                return;
                            }
                            break;
                        }
                    }
                }
            }
            index = 0;
        case 8:
            if (this->sharedDesyncFlags[9]) {
                for (; index < 200; ++index) {
                    for (int player = 1; player < 9; ++player) {
                        if (this->currentPlayerFullIDArray[player] != -1
                            && this->HASH_ClimbData[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                                != this->HASH_ClimbData[player][index]) {
                            this->DAT_GameCommandParam0 = index;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_CLIMB_DATA);
                            this->currentPacketTotalSize += this->DAT_CurrentTransmitCommandPacketSize;
                            sentSize += this->DAT_CurrentTransmitCommandPacketSize;
                            if (sentSize > this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 8;
                                this->resyncResumeOuterIndex = index + 1;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_QUIT_MULTIPLAYERGAME);
                                return;
                            }
                            break;
                        }
                    }
                }
            }
            index = 0;
        case 9:
            if (this->sharedDesyncFlags[10]) {
                for (; index < 40; ++index) {
                    for (int player = 1; player < 9; ++player) {
                        if (this->currentPlayerFullIDArray[player] != -1
                            && this->HASH_PitchDitches[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                                != this->HASH_PitchDitches[player][index]) {
                            this->DAT_GameCommandParam0 = index;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_PITCH_DITCH);
                            this->currentPacketTotalSize += this->DAT_CurrentTransmitCommandPacketSize;
                            sentSize += this->DAT_CurrentTransmitCommandPacketSize;
                            if (sentSize > this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 9;
                                this->resyncResumeOuterIndex = index + 1;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_QUIT_MULTIPLAYERGAME);
                                return;
                            }
                            break;
                        }
                    }
                }
            }
            index = 0;
        case 10:
            if (this->sharedDesyncFlags[11]) {
                for (; index < 40; ++index) {
                    for (int player = 1; player < 9; ++player) {
                        if (this->currentPlayerFullIDArray[player] != -1
                            && this->HASH_Unknown2[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                                != this->HASH_Unknown2[player][index]) {
                            this->DAT_GameCommandParam0 = index;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_UNKNOWN2);
                            this->currentPacketTotalSize += this->DAT_CurrentTransmitCommandPacketSize;
                            sentSize += this->DAT_CurrentTransmitCommandPacketSize;
                            if (sentSize > this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 10;
                                this->resyncResumeOuterIndex = index + 1;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_QUIT_MULTIPLAYERGAME);
                                return;
                            }
                            break;
                        }
                    }
                }
            }
            index = 0;
        case 11:
            if (this->sharedDesyncFlags[6]) {
                for (; index < 128; ++index) {
                    for (int player = 1; player < 9; ++player) {
                        if (this->currentPlayerFullIDArray[player] != -1
                            && this->HASH_LogicalTileMap[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .hashDataArray[0]
                                    .componentArray[index]
                                != this->HASH_LogicalTileMap[player].hashDataArray[0].componentArray[index]) {
                            this->DAT_GameCommandParam0 = 0;
                            this->DAT_GameCommandParam1 = index;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_SEND_RESYNC_LOGICALTILEMAP);
                            this->currentPacketTotalSize += this->DAT_CurrentTransmitCommandPacketSize;
                            sentSize += this->DAT_CurrentTransmitCommandPacketSize;
                            if (sentSize > this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 11;
                                this->resyncResumeOuterIndex = index + 1;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_QUIT_MULTIPLAYERGAME);
                                return;
                            }
                            break;
                        }
                    }
                }
                index = 1;
                entry = 0;
            // Cases 12 and 13 resume inside the tile map block.
            case 12:
                for (row = index; row < 10; ++row) {
                    for (; entry < 64; ++entry) {
                        for (int player = 1; player < 9; ++player) {
                            if (this->currentPlayerFullIDArray[player] != -1
                                && this->HASH_LogicalTileMap[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .hashDataArray[row]
                                        .componentArray[entry]
                                    != this->HASH_LogicalTileMap[player].hashDataArray[row].componentArray[entry]) {
                                this->DAT_GameCommandParam0 = row;
                                this->DAT_GameCommandParam1 = entry;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_SEND_RESYNC_TILEMAPDATA2);
                                this->currentPacketTotalSize += this->DAT_CurrentTransmitCommandPacketSize;
                                sentSize += this->DAT_CurrentTransmitCommandPacketSize;
                                if (sentSize > this->resyncPacketBudget) {
                                    this->somePacketSubTypeUnk = 12;
                                    this->resyncResumeOuterIndex = row;
                                    this->resyncResumeInnerIndex = entry + 1;
                                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                        Commands::GCT_QUIT_MULTIPLAYERGAME);
                                    return;
                                }
                                break;
                            }
                        }
                    }
                    entry = 0;
                }
                index = 10;
                entry = 0;
            case 13:
                for (row = index; row < 30; ++row) {
                    for (; entry < 32; ++entry) {
                        for (int player = 1; player < 9; ++player) {
                            if (this->currentPlayerFullIDArray[player] != -1
                                && this->HASH_LogicalTileMap[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .hashDataArray[row]
                                        .componentArray[entry]
                                    != this->HASH_LogicalTileMap[player].hashDataArray[row].componentArray[entry]) {
                                this->DAT_GameCommandParam0 = row;
                                this->DAT_GameCommandParam1 = entry;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_SEND_RESYNC_TILEMAPDATA1);
                                this->currentPacketTotalSize += this->DAT_CurrentTransmitCommandPacketSize;
                                sentSize += this->DAT_CurrentTransmitCommandPacketSize;
                                if (sentSize > this->resyncPacketBudget) {
                                    this->somePacketSubTypeUnk = 13;
                                    this->resyncResumeOuterIndex = row;
                                    this->resyncResumeInnerIndex = entry + 1;
                                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                        Commands::GCT_QUIT_MULTIPLAYERGAME);
                                    return;
                                }
                                break;
                            }
                        }
                    }
                    entry = 0;
                }
            }
            index = 0;
        case 14:
            if (this->sharedDesyncFlags[12]) {
                for (; index < 9; ++index) {
                    for (int player = 1; player < 9; ++player) {
                        if (this->currentPlayerFullIDArray[player] != -1
                            && this->HASH_AIVS[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                                != this->HASH_AIVS[player][index]) {
                            this->DAT_GameCommandParam0 = index;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_HOST_SHARE_AIV);
                            this->currentPacketTotalSize += this->DAT_CurrentTransmitCommandPacketSize;
                            sentSize += this->DAT_CurrentTransmitCommandPacketSize;
                            if (sentSize > this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 14;
                                this->resyncResumeOuterIndex = index + 1;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_QUIT_MULTIPLAYERGAME);
                                return;
                            }
                            break;
                        }
                    }
                }
            }
            index = 0;
        case 15:
            if (this->sharedDesyncFlags[13]) {
                for (; index < 80; ++index) {
                    for (int player = 1; player < 9; ++player) {
                        if (this->currentPlayerFullIDArray[player] != -1
                            && this->HASH_HeatMaps[DAT_GameSynchronyState::instance.currentPlayerSlotID][index]
                                != this->HASH_HeatMaps[player][index]) {
                            this->DAT_GameCommandParam0 = index;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                Commands::GCT_HOST_SHARE_HEATMAP);
                            this->currentPacketTotalSize += this->DAT_CurrentTransmitCommandPacketSize;
                            sentSize += this->DAT_CurrentTransmitCommandPacketSize;
                            if (sentSize > this->resyncPacketBudget) {
                                this->somePacketSubTypeUnk = 15;
                                this->resyncResumeOuterIndex = index + 1;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    Commands::GCT_QUIT_MULTIPLAYERGAME);
                                return;
                            }
                            break;
                        }
                    }
                }
            }
        }
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(Commands::GCT_CHECK_GAME_SYNCUnk);
        // Setting the status through the global instance is needed for the match.
        DAT_GameSynchronyState::instance.syncStatus = 3;
    }

}
}
