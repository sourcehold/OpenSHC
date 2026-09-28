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
        // FUNCTION: STRONGHOLDCRUSADER 0x00497080
        dword PathFindingState::pathFindingResultBased(int param_1, int x, int y, int extraDistance)
        {
            dword dVar1;
            uint _someX;
            uint _someY;
            int* _tilesPointer;
            uint _isNegativeNumberX;
            uint _isNegativeNumberY;
            int _index;
            int _distance;
            int _tile;
            _tilesPointer = this->searchQueue.tilesQueue + DAT_TribesState::instance.ALG_ResultTileIndex;
            _index = DAT_TribesState::instance.ALG_ResultTileIndex;
            do {
                _tile = *_tilesPointer;
                _distance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                if (((DAT_TileMapState::instance.LogicLayer[_tile] & 0x10000100U) != 0) && (0 < _distance)) {
                    if (extraDistance + 0xc < _distance) {
                        return (dword)(0);
                    }
                    _someX = (_tile
                                 - DAT_ViewportRenderState::instance
                                     .translationMatrix[DAT_ViewportRenderState::instance
                                             .tileTranslationMatrix_YComponent[_tile]]
                                     .addXgetTile)
                        - x;
                    _isNegativeNumberX = (int)_someX >> 0x1f;
                    _someY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile] - y;
                    _isNegativeNumberY = (int)_someY >> 0x1f;
                    if (((int)(((_someY ^ _isNegativeNumberY) - _isNegativeNumberY)
                             + ((_someX ^ _isNegativeNumberX) - _isNegativeNumberX))
                                % param_1
                            == 0)
                        && (_distance < 4000)) {
                        dVar1 = this->searchQueue.tilesQueue[_index];
                        DAT_TribesState::instance.ALG_ResultY = (int)this->searchQueue.yQueue[_index];
                        DAT_TribesState::instance.ALG_ResultTileIndex = _index;
                        DAT_TribesState::instance.ALG_ResultX = dVar1
                            - DAT_ViewportRenderState::instance.translationMatrix[DAT_TribesState::instance.ALG_ResultY]
                                  .addXgetTile;
                        return (dword)(dVar1);
                    }
                }
                _index = _index + 1;
                _tilesPointer = _tilesPointer + 1;
                if (4000 < _index) {
                    return (dword)(0);
                }
            } while (DAT_TileMapState::instance.WalkLayer[_tile]
                == DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]]);
            return (dword)(0);
        }

    }
}
}
