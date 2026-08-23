#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_CopyOfScenarioGold.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004B8210
void UI::RestoreScenarioGold()
{
    DAT_GameState::instance.mapAndTime.scenarioGold = (short)DAT_CopyOfScenarioGold::instance;
}

}
