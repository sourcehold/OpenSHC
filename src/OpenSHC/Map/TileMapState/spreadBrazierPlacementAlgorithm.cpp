#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005011A0
    void TileMapState::spreadBrazierPlacementAlgorithm(int playerID, uint x, uint y)
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::spreadAlgorithmForFlagsAndBraziersUnk,
            DAT_PathFindingState::ptr)(playerID, x, y, 4, 1);
    }

}
}
