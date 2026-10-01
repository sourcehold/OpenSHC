#include "../GameSynchronyState.func.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00480440
    int GameSynchronyState::getCommandIDFromCommandSelectionStuff()
    {
        this->MBR_someIndex = 0;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->MBR_SelectedGameCommands), 0, this->MBR_SelectedGameCommands);

        // Scan only the remaining physical ring entries. Wrapping and further
        // batches belong to the caller; sorting here must not cross that boundary.
        for (int slot = this->MBR_GameCommandID; slot < 200; ++slot) {
            Commands::GameCommand& command = this->DAT_GameCommandArray[slot];
            if (command.stateUnk != 0 && static_cast<signed char>(command.stateUnk) < 10
                && static_cast<int>(command.time) <= static_cast<int>(DAT_GameCore::instance.mapTimeInTicks)) {
                this->protocolInvokerPlayerID
                    = MACRO_CALL_MEMBER(GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs, this)(
                        command.playerUnk);
                this->MBR_SelectedGameCommands[this->MBR_someIndex][0] = slot;
                this->MBR_SelectedGameCommands[this->MBR_someIndex][1] = this->protocolInvokerPlayerID;
                ++this->MBR_someIndex;
                if (static_cast<int>(this->MBR_someIndex) >= 100)
                    break;
            }
        }

        int pass = 0;
        if (static_cast<int>(this->MBR_someIndex) > 0) {
            // Stable ascending player order: equal-player commands retain ring order.
            int swapped = 1;
            do {
                if (!swapped)
                    break;
                ++pass;
                swapped = 0;
                for (int index = 1; index < static_cast<int>(this->MBR_someIndex); ++index) {
                    int* previous = this->MBR_SelectedGameCommands[index - 1];
                    int* next = this->MBR_SelectedGameCommands[index];
                    int nextPlayer = next[1];
                    int previousSlot = previous[0];
                    int previousPlayer = previous[1];
                    // Preserve the native asymmetry: only the right-hand player is
                    // checked. A sole unknown player (or one first in order) passes.
                    if (nextPlayer == 0)
                        return 0;
                    if (nextPlayer < previousPlayer) {
                        previous[0] = next[0];
                        previous[1] = nextPlayer;
                        next[0] = previousSlot;
                        next[1] = previousPlayer;
                        swapped = 1;
                    }
                }
            } while (pass < 100);
            pass = 1;
        }
        return pass;
    }

} // namespace Synchrony
} // namespace OpenSHC
