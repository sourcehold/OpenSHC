#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A9760
        PathFindingState* PathFindingState::Constructor_PathFindingState()
        {
            this->field40_0x70 = 0;
            this->field41_0x74 = 0;
            this->DAT_lWys = 0;
            this->notAllAssassinsUnk = 0;
            this->DAT_Easy = 0;
            this->DAT_Hard = 0;
            this->DAT_Test_likely = 0;
            this->DAT_Test_gatehouse = 0;
            this->searchNonmatchCount = 0;
            this->searchMatchCounter = 0;
            this->DAT_Ass = 0;
            this->calculations = 0;
            this->DAT_Mini_spreads = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearPathFindingTileMaps, this)();
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearAllClimbData, this)();
            this->searchGeneration = 1;
            return this;
        }

    }
}
}
