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
        dword PathFindingState::pathFindingResultBased(int param_1, int ySpace, int y, int extraDistance)
        {
            int _generation = DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]];
            int _index = DAT_TribesState::instance.ALG_ResultTileIndex;
            int* _tilesPointer = &this->searchQueue.tilesQueue[_index];
            int _tile;
            do {
                _tile = *_tilesPointer;
                int _tileY = (short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];
                int _distance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x10000100U) != 0 && 0 < _distance) {
                    if (_distance > extraDistance + 0xc) {
                        return (dword)(0);
                    }
                    int _absX = abs(_tile - DAT_ViewportRenderState::instance.translationMatrix[_tileY].addXgetTile - ySpace);
                    if ((_absX + abs(_tileY - y)) % param_1 == 0 && _distance < 4000) {
                        dword dVar1 = this->searchQueue.tilesQueue[_index];
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
            } while (DAT_TileMapState::instance.WalkLayer[_tile] == _generation);
            return (dword)(0);
        }

    }
}
}
