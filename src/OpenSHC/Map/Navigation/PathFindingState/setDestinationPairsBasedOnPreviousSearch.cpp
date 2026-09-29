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
        // FUNCTION: STRONGHOLDCRUSADER 0x004A65E0
        void PathFindingState::setDestinationPairsBasedOnPreviousSearch(int playerIDMin1, int attackedPlayerID)
        {
            int _pair = 0;
            this->searchQueue.readIndex = 0;
            if (this->searchQueue.writeIndex != 0) {
                do {
                    uint y = (uint)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    int _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    uint _attackedDistance = (uint) * (byte*)(attackedPlayerID * 0x13a10 + 0x1ee2998 + _tile);
                    uint x = _tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                    if (DAT_TileMapState::instance.WalkLayer[_tile] == this->searchGeneration && _attackedDistance != 0
                        && _attackedDistance - 4294967224 < 4
                        && DAT_TileMapState::instance.CertainPathLayer[_tile] < 0x4c
                        && DAT_TileMapState::instance.CertainPathLayer[_tile] != 100) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::budgetFloodFillOnCertainPathLayer, this)(
                            x, y, (int)(100), (int)(50));
                        DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[playerIDMin1][_pair].x = x;
                        DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[playerIDMin1][_pair].y = y;
                        _pair = _pair + 1;
                    }
                    if (_pair >= 40) {
                        return;
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            }
            return;
        }

    }
}
}
