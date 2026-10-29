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
            int _i;
            int _gen0;
            int _d0;
            _gen0 = (int)DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]];
            _d0 = (int)DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]];
            _i = DAT_TribesState::instance.ALG_ResultTileIndex;
            _closest = 4000;
            _match = 0;
            _pResultTile = this->searchQueue.tilesQueue + _i;
            do {
                _tile = *_pResultTile;
                _d = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                if (0 < _d && (_d - _d0) % param_1 == 0 && _d < _closest) {
                    _closest = _d;
                    _match = _i;
                }
                _i = _i + 1;
                _pResultTile = _pResultTile + 1;
            } while (_i <= 4000 && (int)DAT_TileMapState::instance.WalkLayer[_tile] == _gen0);
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
