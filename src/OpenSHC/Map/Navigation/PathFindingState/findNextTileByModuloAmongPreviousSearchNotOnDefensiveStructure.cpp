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
        dword PathFindingState::findNextTileByModuloAmongPreviousSearchNotOnDefensiveStructure(int modulo, int x, int y)
        {
            uint _xDistance;
            uint _yDistance;
            int* _pTile;
            uint _absX;
            uint _absY;
            int iVar1;
            dword _result;
            int _tile;
            _pTile = this->searchQueue.tilesQueue + DAT_TribesState::instance.ALG_ResultTileIndex;
            iVar1 = DAT_TribesState::instance.ALG_ResultTileIndex;
            while (true) {
                _tile = *_pTile;
                /*
                  manhatten distance
                 */
                if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x10000100U) == 0
                    && 0 < DAT_TileMapState::instance.CertainPathLayer[_tile]
                    && (_xDistance = (_tile
                                         - DAT_ViewportRenderState::instance
                                             .translationMatrix[DAT_ViewportRenderState::instance
                                                     .tileTranslationMatrix_YComponent[_tile]]
                                             .addXgetTile)
                            - x,
                        _absX = (int)_xDistance >> 0x1f,
                        _yDistance
                        = (short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile] - y,
                        _absY = (int)_yDistance >> 0x1f,
                        (int)(((_yDistance ^ _absY) - _absY) + ((_xDistance ^ _absX) - _absX)) % modulo == 0)
                    && DAT_TileMapState::instance.CertainPathLayer[_tile] < 4000)
                    break;
                iVar1 = iVar1 + 1;
                _pTile = _pTile + 1;
                if ((4000 < iVar1)
                    || (DAT_TileMapState::instance.WalkLayer[_tile]
                        != DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]])) {
                    return (dword)(0);
                }
            }
            _result = this->searchQueue.tilesQueue[iVar1];
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
