#include "../GameStateStructures.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00401090
    BOOLEnum GameStateStructures::isSameTeam(int playerID1, int playerID2)
    {
        return this->mapAndTime.playerTeams[playerID1] == this->mapAndTime.playerTeams[playerID2];
    }

}
}
