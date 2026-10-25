#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Commands/GameCommandState.hpp"

#include "OpenSHC/Globals/DAT_ProtocolDefinedData.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandScheduling;
    using Commands::GameCommandState;

    // FUNCTION: STRONGHOLDCRUSADER 0x004892F0
    void GameSynchronyState::processWaitingCommands()
    {
        int _gameCommandID
            = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::getCommandIDFromCommandSelectionStuff, this)();
        if ((_gameCommandID) && (_gameCommandID = 0, 0 < this->someIndex)) {
            int (*_selected)[2] = this->selectedGameCommands;
            while (_gameCommandID < this->someIndex) {
                // process all commands that should have been executed by now.
                // Measured: indexing selectedGameCommands per iteration instead of walking
                // _selected costs the match, so the pointer stays.
                this->DAT_CurrentGameCommandID = (*_selected)[0];
                this->protocolInvokerPlayerID
                    = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs, this)(
                        this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].playerUnk);
                this->DAT_GameCommandParam5 = 0;
                this->DAT_GameCommandParam4 = 0;
                this->DAT_GameCommandParam3 = 0;
                this->DAT_GameCommandParam2 = 0;
                this->DAT_GameCommandParam1 = 0;
                this->DAT_GameCommandParam0 = 0;
                this->DAT_CommandActionPlan = Commands::GCS_EXECUTE;
                this->DAT_CommandParameterOffset = 0;
                (&DAT_ProtocolDefinedData::instance
                        .commandFunctions)[this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].commandType]();
                ++_gameCommandID;
                this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].stateUnk = Commands::GCS_PROCESSED;
                ++_selected;
            }
        }
    }

}
}
