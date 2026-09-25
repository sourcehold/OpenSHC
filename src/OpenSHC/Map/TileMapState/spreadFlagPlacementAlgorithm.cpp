#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00501180
    int TileMapState::spreadFlagPlacementAlgorithm(int playerID, uint x, uint y)
    {
        return MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::spreadAlgorithmForFlagsAndBraziersUnk,
            DAT_PathFindingState::ptr)(playerID, x, y, 4, 0);
    }

}
}
