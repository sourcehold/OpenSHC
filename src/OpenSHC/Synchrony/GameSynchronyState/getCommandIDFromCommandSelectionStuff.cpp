#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Commands/GameCommandState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Synchrony {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00480440
    BOOLEnum GameSynchronyState::getCommandIDFromCommandSelectionStuff()
    {
        this->selectedCommandsCount = 0;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->selectedGameCommands), 0, this->selectedGameCommands);
        for (int command = this->gameCommandID; command < countof(this->DAT_GameCommandArray); ++command) {
            // The command is not processed yet, is to be processed, and its time has come.
            if (this->DAT_GameCommandArray[command].stateUnk != 0
                && this->DAT_GameCommandArray[command].stateUnk < Commands::GCS_PROCESSED
                && (int)this->DAT_GameCommandArray[command].time <= (int)DAT_GameCore::instance.mapTimeInTicks) {
                this->protocolInvokerPlayerID
                    = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs, this)(
                        this->DAT_GameCommandArray[command].playerUnk);
                this->selectedGameCommands[this->selectedCommandsCount][0] = command;
                this->selectedGameCommands[this->selectedCommandsCount][1] = this->protocolInvokerPlayerID;
                ++this->selectedCommandsCount;
                if (this->selectedCommandsCount >= 100) {
                    break;
                }
            }
        }
        if (this->selectedCommandsCount <= 0) {
            return FALSE;
        }
        // Sort the selected commands so that lower player IDs are processed first (at most 100 passes).
        BOOLEnum swapped = TRUE;
        // The pass is counted at the top of the body: stepping it in the for header compiles to a different loop.
        for (int pass = 0; pass < 100 && swapped;) {
            ++pass;
            swapped = FALSE;
            for (int i = 1; i < this->selectedCommandsCount; ++i) {
                int const nextPlayerID = this->selectedGameCommands[i][1];
                int const commandID = this->selectedGameCommands[i - 1][0];
                int const playerID = this->selectedGameCommands[i - 1][1];
                if (nextPlayerID == 0) {
                    return FALSE;
                }
                if (nextPlayerID < playerID) {
                    this->selectedGameCommands[i - 1][0] = this->selectedGameCommands[i][0];
                    this->selectedGameCommands[i - 1][1] = nextPlayerID;
                    this->selectedGameCommands[i][0] = commandID;
                    this->selectedGameCommands[i][1] = playerID;
                    swapped = TRUE;
                }
            }
        }
        return TRUE;
    }

}
}
