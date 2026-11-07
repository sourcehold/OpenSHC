#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x004A66D0
        void PathFindingState::setMoveDestinationPairs(int playerIDmin1, int playerID, int maxCost)
        {
            int _destinationCount = 0;
            if (100 < maxCost) {
                maxCost = 100;
            }
            this->searchQueue.readIndex = 0;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                uint _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                int _tileCandidate = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                uint _x = _tileCandidate - DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;
                int _cost = DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[playerID][_tileCandidate];
                if (_cost != 0 && _cost >= maxCost && _cost <= maxCost + 10
                    && DAT_TileMapState::instance.CertainPathLayer[_tileCandidate] != 100) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::budgetFloodFillOnCertainPathLayer, this)(
                        _x, _y, 100, 200);
                    DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[playerIDmin1][_destinationCount].x
                        = _x;
                    DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[playerIDmin1][_destinationCount].y
                        = _y;
                    _destinationCount += 1;
                }
                if (_destinationCount >= 20) {
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
