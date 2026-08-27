#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x005011A0
    void TileMapState::spreadBrazierPlacementAlgorithm(int playerID, uint x, uint y)

    {
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::spreadAlgorithmForFlagsAndBraziersUnk,
            DAT_PathFindingState::ptr)(playerID, x, y, 4, 1);
        return;
    }

}
}
