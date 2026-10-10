#include "../../Synchrony.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Commands/GameCommandState.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_ProtocolDefinedData.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandScheduling;
    using Commands::GameCommandState;

    /*
      juggernaunt: MultiplayerManager_SendCmdAddress   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00489100
    void GameSynchronyState::queueCommand(GameCommandType commandType)
    {
        this->DAT_CurrentGameCommandID = this->DAT_GameCommandArrayIndex;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            1260, '\0', (void*)((int)(&this->DAT_GameCommandArray[this->DAT_GameCommandArrayIndex].parameters)));
        this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].stateUnk = Commands::GCS_UNPROCESSED;
        this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].playerUnk = this->DPLAYX_PlayerHandle;
        byte _commandType = (byte)commandType;
        this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].commandType = _commandType;
        if (this->mapTimeInTicksSinglePlayer < (int)DAT_GameCore::instance.mapTimeInTicks) {
            this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].time
                = this->commandDelay + DAT_GameCore::instance.mapTimeInTicks;
        } else {
            this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].time
                = this->commandDelay + this->mapTimeInTicksSinglePlayer;
        }
        this->DAT_CommandActionPlan = Commands::GCS_SCHEDULE_AND_SEND;
        this->DAT_PlayerIDReceiver = 0;
        this->DAT_CommandParameterOffset = 0;
        /*
          Calls the callback function for a specific command. See "GameCommandType" for   possible commands. Includes
          placing buildings, walls, moving units,..
         */
        ((void (*)())DAT_ProtocolDefinedData::instance
                .commandFunctions[this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].commandType + 0x15])();
        this->DAT_CommandParameterOffset = 0;
        dword _time = this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].time;
        if ((int)_time < 1) {
            /*
              time == 0 means it is an immediate (out of game time) command, commands that   don't change game state
              (gold, buildings, units, etc.), but rather operate on   a meta level
             */
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::transmitCommand, this)(_commandType,
                (undefined4)((int)(_time)), (char*)((int)(this->DAT_GameCommandFixedParameterLocation)),
                (size_t)((int)(this->DAT_CommandSize)), this->DAT_PlayerIDReceiver);
            if (this->DAT_CommandActionPlan == Commands::GCS_EXECUTE) {
                this->DAT_GameCommandParam5 = 0;
                this->DAT_GameCommandParam4 = 0;
                this->DAT_GameCommandParam3 = 0;
                this->DAT_GameCommandParam2 = 0;
                this->DAT_GameCommandParam1 = 0;
                this->DAT_GameCommandParam0 = 0;
                this->DPLAYX_ReceivedPlayerID = this->DPLAYX_PlayerHandle;
                this->protocolInvokerPlayerID = this->currentPlayerSlotID;
                ((void (*)())DAT_ProtocolDefinedData::instance
                        .commandFunctions[this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].commandType
                            + 0x15])();
            }
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::clearGameCommandEntry, this)(
                this->DAT_CurrentGameCommandID);
        } else {
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::transmitCommand, this)(_commandType,
                (undefined4)((int)(_time)),
                (char*)((int)(&this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].parameters)),
                (size_t)((int)(this->DAT_CommandSize)), this->DAT_PlayerIDReceiver);
            this->DAT_GameCommandArrayIndex = this->DAT_GameCommandArrayIndex + 1;
            if (199 < this->DAT_GameCommandArrayIndex) {
                this->DAT_GameCommandArrayIndex = 0;
            }
        }
    }

}
}
