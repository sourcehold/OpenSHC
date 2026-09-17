#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00501180
    int TileMapState::spreadFlagPlacementAlgorithm(int param_1, uint param_2, uint param_3)
    {
        return MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::spreadAlgorithmForFlagsAndBraziersUnk,
            DAT_PathFindingState::ptr)(param_1, param_2, param_3, 4, 0);
    }

}
}
