#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A6520
        void PathFindingState::storeDestinationOptionsUnk(int signpostID)
        {
            this->calculations = this->calculations + 1;
            int iVar2 = 0;
            this->searchQueue.readIndex = 0;
            if (this->searchQueue.writeIndex != 0) {
                do {
                    uint y = (uint)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    int iVar1 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    uint x = iVar1 - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                    if (DAT_TileMapState::instance.CertainPathLayer[iVar1] != 100) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::budgetFloodFillOnCertainPathLayer, this)(
                            x, y, 100, (int)(30));
                        DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[signpostID][iVar2].x = x;
                        DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[signpostID][iVar2].y = y;
                        iVar2 = iVar2 + 1;
                    }
                    if (iVar2 >= 40) {
                        return;
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (80400 < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            }
            return;
        }

    }
}
}
