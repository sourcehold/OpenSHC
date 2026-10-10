#include "../../Synchrony.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Commands/GameCommandState.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_ProtocolDefinedData.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandScheduling;
    using Commands::GameCommandState;

    /*
      juggernaunt: MultiplayerManager_RecieveCmdAddress   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00480210
    void GameSynchronyState::scheduleReceivedCommand(
        GameCommandType commandCategory, DWORD dxPlayerHandle, dword time, void* address)
    {
        uint _playerID;
        if (this->DAT_GameCommandArrayIndex < 200) {
            if ((undefined1)commandCategory
                == (Commands::GCT_SEND_RESYNC_TILEMAPDATA2 | Commands::GCT_HOST_ANNOUNCE_TEAMS_AND_POSITIONS)) {
                DAT_GameSynchronyState::instance.unknownIncrementBy40_01
                    = DAT_GameSynchronyState::instance.unknownIncrementBy40_01 + 40;
                _playerID = MACRO_CALL_MEMBER(
                    Synchrony::GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs, this)(dxPlayerHandle);
                if (_playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandArray[this->DAT_CurrentGameCommandID].time
                        = DAT_GameCore::instance.mapTimeInTicks + 1;
                }
            }
            if (time) {
                if ((int)DAT_GameCore::instance.mapTimeInTicks < (int)time) {
                    if ((int)(time - DAT_GameCore::instance.mapTimeInTicks) < (int)DAT_GameSynchronyState::instance
                            .DAT_LagIndicatorPerPlayer[DAT_GameSynchronyState::instance.currentPlayerSlotID]) {
                        DAT_GameSynchronyState::instance
                            .DAT_LagIndicatorPerPlayer[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            = (short)time - (short)DAT_GameCore::instance.mapTimeInTicks;
                    }
                } else {
                    this->lateCommandPenalty = this->lateCommandPenalty + 2;
                }
            }
            this->DAT_CurrentGameCommandID = this->DAT_GameCommandArrayIndex;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(0x4ec, '\0',
                (void*)((int)(&DAT_GameSynchronyState::instance.DAT_GameCommandArray[this->DAT_GameCommandArrayIndex]
                        .parameters)));
            DAT_GameSynchronyState::instance.DAT_GameCommandArray[this->DAT_CurrentGameCommandID].stateUnk
                = Commands::GCS_UNPROCESSED;
            DAT_GameSynchronyState::instance.DAT_GameCommandArray[this->DAT_CurrentGameCommandID].playerUnk
                = dxPlayerHandle;
            DAT_GameSynchronyState::instance.DAT_GameCommandArray[this->DAT_CurrentGameCommandID].commandType
                = (undefined1)commandCategory;
            DAT_GameSynchronyState::instance.DAT_GameCommandArray[this->DAT_CurrentGameCommandID].time = time;
            this->DAT_CommandParameterOffset = 0;
            this->DAT_CommandActionPlan = Commands::GCS_SCHEDULE_RECEIVED_COMMAND;
            ((void (*)())DAT_ProtocolDefinedData::instance.commandFunctions
                    [DAT_GameSynchronyState::instance.DAT_GameCommandArray[this->DAT_CurrentGameCommandID].commandType
                        + 0x15])();
            if ((int)DAT_GameSynchronyState::instance.DAT_GameCommandArray[this->DAT_CurrentGameCommandID].time <= 0) {
                MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                    this->DAT_CommandSize, address, (void*)((int)(this->DAT_GameCommandFixedParameterLocation)));
                int iVar1 = this->DAT_CurrentGameCommandID;
                this->protocolInvokerPlayerID = MACRO_CALL_MEMBER(
                    Synchrony::GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs, this)(
                    DAT_GameSynchronyState::instance.DAT_GameCommandArray[this->DAT_CurrentGameCommandID].playerUnk);
                this->DAT_GameCommandParam5 = 0;
                this->DAT_GameCommandParam4 = 0;
                this->DAT_GameCommandParam3 = 0;
                this->DAT_GameCommandParam2 = 0;
                this->DAT_GameCommandParam1 = 0;
                this->DAT_GameCommandParam0 = 0;
                this->DAT_CommandActionPlan = Commands::GCS_EXECUTE;
                this->DAT_CommandParameterOffset = 0;
                ((void (*)())DAT_ProtocolDefinedData::instance
                        .commandFunctions[this->DAT_GameCommandArray[iVar1].commandType + 0x15])();
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::clearGameCommandEntry, this)(
                    this->DAT_CurrentGameCommandID);
            } else {
                MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(this->DAT_CommandSize,
                    address,
                    (void*)((int)(&DAT_GameSynchronyState::instance.DAT_GameCommandArray[this->DAT_CurrentGameCommandID]
                            .parameters)));
                this->DAT_GameCommandArrayIndex = this->DAT_GameCommandArrayIndex + 1;
                if (199 < this->DAT_GameCommandArrayIndex) {
                    this->DAT_GameCommandArrayIndex = 0;
                }
            }
        }
    }

}
}
