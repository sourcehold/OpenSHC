#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00496F90
        void PathFindingState::findNextTileInExistingSearchThatIsModuloDistanceAway(int modulo, int x, int y)
        {
            int _dx;
            int _dy;
            int _firstTileWalk = DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]];
            int _index = DAT_TribesState::instance.ALG_ResultTileIndex;
            int local_10 = 0;
            int* _pLastTile = this->searchQueue.tilesQueue + _index;
            while (true) {
                int iVar1 = *_pLastTile;
                int _tileY = (short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[iVar1];
                int _dist = DAT_TileMapState::instance.CertainPathLayer[iVar1];
                if (0 < _dist
                    && (_dx = (iVar1 - DAT_ViewportRenderState::instance.translationMatrix[_tileY].addXgetTile) - x,
                        _dy = _tileY - y, (abs(_dx) + abs(_dy)) % modulo == 0)
                    && _dist < 4000) {
                    local_10 = _index;
                    break;
                }
                _index = _index + 1;
                _pLastTile = _pLastTile + 1;
                if (4000 < _index || DAT_TileMapState::instance.WalkLayer[iVar1] != _firstTileWalk)
                    break;
            }
            DAT_TribesState::instance.ALG_ResultY = (int)this->searchQueue.yQueue[local_10];
            DAT_TribesState::instance.ALG_ResultX = this->searchQueue.tilesQueue[local_10]
                - DAT_ViewportRenderState::instance.translationMatrix[DAT_TribesState::instance.ALG_ResultY]
                      .addXgetTile;
            DAT_TribesState::instance.ALG_ResultTileIndex = local_10;
            return;
        }

    }
}
}
