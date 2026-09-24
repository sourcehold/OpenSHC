#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_CopyOfScenarioGold.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace UI {
    namespace Helpers {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B8210
        void RestoreScenarioGold()
        {
            DAT_GameState::instance.mapAndTime.scenarioGold = (short)DAT_CopyOfScenarioGold::instance;
        }

    }
}
}
