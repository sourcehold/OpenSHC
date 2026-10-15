#include "../PathFindingState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049C5C0
        BOOLEnum PathFindingState::findDestinationCostLowerThan6(int tile, int maxDistance)
        {
            uint _cost;
            this->searchQueue.readIndex = 0;
            if (this->searchQueue.writeIndex != 0) {
                byte* _pCost = DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[tile];
                do {
                    int _y = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    int _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    int _x = _tile - DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;
                    if (DAT_TileMapState::instance.WalkLayer[_tile] == this->searchGeneration
                        && (_cost = (uint)_pCost[_tile], _cost != 0) && _cost - 0x28 < 6
                        && DAT_TileMapState::instance.CertainPathLayer[_tile] >= maxDistance) {
                        this->ALG_ResultX = _x;
                        this->ALG_ResultY = _y;
                        this->ALG_ResultTile = _tile;
                        return TRUE;
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a10 <= (int)this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            }
            return FALSE;
        }

    }
}
}
