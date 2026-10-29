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
        // FUNCTION: STRONGHOLDCRUSADER 0x00497180
        dword PathFindingState::findNextTileByModuloAmongPreviousSearchNotOnDefensiveStructure(int modulo, int ySpace, int y)
        {
            int _generation = DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]];
            int iVar1 = DAT_TribesState::instance.ALG_ResultTileIndex;
            int* _pTile = &this->searchQueue.tilesQueue[iVar1];
            while (true) {
                int _tile = *_pTile;
                int _tileY = (short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];
                int _distance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                /*
                  manhatten distance
                 */
                if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x10000100U) == 0 && 0 < _distance) {
                    int _absX = abs(_tile - DAT_ViewportRenderState::instance.translationMatrix[_tileY].addXgetTile - ySpace);
                    if ((_absX + abs(_tileY - y)) % modulo == 0 && _distance < 4000)
                        break;
                }
                iVar1 = iVar1 + 1;
                _pTile = _pTile + 1;
                if ((4000 < iVar1) || (DAT_TileMapState::instance.WalkLayer[_tile] != _generation)) {
                    return (dword)(0);
                }
            }
            dword _result = this->searchQueue.tilesQueue[iVar1];
            DAT_TribesState::instance.ALG_ResultY = (int)this->searchQueue.yQueue[iVar1];
            DAT_TribesState::instance.ALG_ResultTileIndex = iVar1;
            DAT_TribesState::instance.ALG_ResultX = _result
                - DAT_ViewportRenderState::instance.translationMatrix[DAT_TribesState::instance.ALG_ResultY]
                      .addXgetTile;
            return (dword)(_result);
        }

    }
}
}
