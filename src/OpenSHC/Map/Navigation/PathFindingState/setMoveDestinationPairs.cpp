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
        // FUNCTION: STRONGHOLDCRUSADER 0x004A66D0
        void PathFindingState::setMoveDestinationPairs(int playerIDmin1, int playerID, int maxCost)
        {
            int iVar1 = 0;
            if (100 < maxCost) {
                maxCost = 100;
            }
            this->searchQueue.readIndex = 0;
            if (this->searchQueue.writeIndex != 0) {
                do {
                    uint _y = (uint)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    int _tileCandidate = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    uint _cost = (uint) * (byte*)(playerID * 0x13a10 + 0x1ee2998 + _tileCandidate);
                    uint _x = _tileCandidate - DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;
                    if (_cost != 0 && maxCost <= (int)_cost && (int)_cost <= maxCost + 10
                        && DAT_TileMapState::instance.CertainPathLayer[_tileCandidate] != 100) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::budgetFloodFillOnCertainPathLayer, this)(
                            _x, _y, 100, 200);
                        DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[playerIDmin1][iVar1].x = _x;
                        DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[playerIDmin1][iVar1].y = _y;
                        iVar1 = iVar1 + 1;
                    }
                    if (0x13 < iVar1) {
                        return;
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a10 <= this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            }
            return;
        }

    }
}
}
