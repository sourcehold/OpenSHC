#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x004A6520
        void PathFindingState::storeDestinationOptionsUnk(int signpostID)
        {
            this->calculations += 1;
            int _destinationCount = 0;
            this->searchQueue.readIndex = 0;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                uint y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                int _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                uint x = _tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                if (DAT_TileMapState::instance.CertainPathLayer[_tile] != 100) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::budgetFloodFillOnCertainPathLayer, this)(
                        x, y, 100, 30);
                    DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[signpostID][_destinationCount].x = x;
                    DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[signpostID][_destinationCount].y = y;
                    _destinationCount += 1;
                }
                if (_destinationCount
                    >= countof(DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[signpostID])) {
                    return;
                }
                this->searchQueue.readIndex += 1;
                if (MC_MAP_TILES_COUNT <= this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            }
        }

    }
}
}
