#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00532F60
        int UnitsState::getArmySize(int playerID) { return DAT_GameState::instance.playerDataArray[playerID].armySize; }

    }
}
}
