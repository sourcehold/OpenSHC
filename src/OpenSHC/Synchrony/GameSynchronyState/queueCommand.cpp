#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Commands/GameCommandState.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_ProtocolDefinedData.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandScheduling;
    using Commands::GameCommandState;

    // FUNCTION: STRONGHOLDCRUSADER 0x00489100
    void GameSynchronyState::queueCommand(GameCommandType commandType)
    {
        this->DAT_CurrentGameCommandID = this->DAT_GameCommandArrayIndex;
        // No sizeof fits: GameCommand::parameters is typed as a single undefined1
        // followed by padding_0xb[1261], so neither the field nor the struct gives the
        // 1260 bytes the original clears. Needs the parameter block typed in Ghidra.
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            1260, '\0', &this->DAT_GameCommandArray[this->DAT_GameCommandArrayIndex].parameters);
        this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].stateUnk = Commands::GCS_UNPROCESSED;
        this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].playerUnk = this->DPLAYX_PlayerHandle;
        byte _commandType = (byte)commandType;
        this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].commandType = _commandType;
        if ((int)DAT_GameCore::instance.mapTimeInTicks > this->mapTimeInTicksSinglePlayer) {
            this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].time
                = this->commandDelay + DAT_GameCore::instance.mapTimeInTicks;
        } else {
            this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].time
                = this->commandDelay + this->mapTimeInTicksSinglePlayer;
        }
        this->DAT_CommandActionPlan = Commands::GCS_SCHEDULE_AND_SEND;
        this->DAT_PlayerIDReceiver = 0;
        this->DAT_CommandParameterOffset = 0;
        // Calls the callback function for a specific command. See "GameCommandType" for possible
        // commands: placing buildings, walls, moving units, ...
        (&DAT_ProtocolDefinedData::instance
                .commandFunctions)[this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].commandType]();
        this->DAT_CommandParameterOffset = 0;
        dword _time = this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].time;
        if (0 < (int)_time) {
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::transmitCommand, this)(_commandType, _time,
                (char*)&this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].parameters, this->DAT_CommandSize,
                this->DAT_PlayerIDReceiver);
            ++this->DAT_GameCommandArrayIndex;
            if (200 <= this->DAT_GameCommandArrayIndex) {
                this->DAT_GameCommandArrayIndex = 0;
            }
        } else {
            // time == 0 means an immediate (out of game time) command: one that does not change
            // game state (gold, buildings, units, ...) but operates on a meta level
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::transmitCommand, this)(_commandType, _time,
                (char*)this->DAT_GameCommandFixedParameterLocation, this->DAT_CommandSize, this->DAT_PlayerIDReceiver);
            if (this->DAT_CommandActionPlan == Commands::GCS_EXECUTE) {
                this->DAT_GameCommandParam5 = 0;
                this->DAT_GameCommandParam4 = 0;
                this->DAT_GameCommandParam3 = 0;
                this->DAT_GameCommandParam2 = 0;
                this->DAT_GameCommandParam1 = 0;
                this->DAT_GameCommandParam0 = 0;
                this->DPLAYX_ReceivedPlayerID = this->DPLAYX_PlayerHandle;
                this->protocolInvokerPlayerID = this->currentPlayerSlotID;
                (&DAT_ProtocolDefinedData::instance
                        .commandFunctions)[this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].commandType]();
            }
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::clearGameCommandEntry, this)(
                this->DAT_CurrentGameCommandID);
        }
    }

}
}
