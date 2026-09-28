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
        // FUNCTION: STRONGHOLDCRUSADER 0x00496EC0
        int PathFindingState::findClosestTileToStartingTile(int param_1)
        {
            int* _pResultTile;
            int _match;
            int _d;
            int _closest;
            int _tile;
            _closest = 4000;
            _match = 0;
            _pResultTile = this->searchQueue.tilesQueue + DAT_TribesState::instance.ALG_ResultTileIndex;
            do {
                _tile = *_pResultTile;
                _d = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                if (0 < _d
                    && (_d - DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]]) % param_1
                        == 0
                    && _d < _closest) {
                    _match = DAT_TribesState::instance.ALG_ResultTileIndex;
                    _closest = _d;
                }
                DAT_TribesState::instance.ALG_ResultTileIndex = DAT_TribesState::instance.ALG_ResultTileIndex + 1;
                _pResultTile = _pResultTile + 1;
            } while ((DAT_TribesState::instance.ALG_ResultTileIndex < 4000)
                && (DAT_TileMapState::instance.WalkLayer[_tile]
                    == DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]]));
            _tile = this->searchQueue.tilesQueue[_match];
            DAT_TribesState::instance.ALG_ResultY = (int)this->searchQueue.yQueue[_match];
            DAT_TribesState::instance.ALG_ResultTileIndex = _match;
            DAT_TribesState::instance.ALG_ResultX = _tile
                - DAT_ViewportRenderState::instance.translationMatrix[DAT_TribesState::instance.ALG_ResultY]
                      .addXgetTile;
            return _tile;
        }

    }
}
}
