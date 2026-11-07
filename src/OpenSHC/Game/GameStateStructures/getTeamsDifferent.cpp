#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004596D0
    BOOLEnum GameStateStructures::getTeamsDifferent(int firstPlayerId, int secondPlayerId)
    {
        if (firstPlayerId == 0) {
            return FALSE;
        }
        if (secondPlayerId == 0) {
            return FALSE;
        }
        return this->mapAndTime.playerTeams[firstPlayerId] != this->mapAndTime.playerTeams[secondPlayerId];
    }

}
}
