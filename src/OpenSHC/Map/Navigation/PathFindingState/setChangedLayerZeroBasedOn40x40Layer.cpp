#include "../PathFindingState.func.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049AF50
        void PathFindingState::setChangedLayerZeroBasedOn40x40Layer(uint flag_and_offset)
        {
            if ((this->field10_0x28 == 0) && (flag_and_offset == 0)) {
                if (DAT_TileMapState::instance.someIndex <= DAT_TileMapState::instance.someLimit) {
                    int _index10 = DAT_TileMapState::instance.someIndex * 10;
                    /*
                      10 400x400 rows
                     */
                    int _index4000 = DAT_TileMapState::instance.someIndex * 4000;
                    int _someX = DAT_TileMapState::instance.someIndex * 120;
                    int _pMap4040 = DAT_TileMapState::instance.someIndex * 40 + 0x1f93438;
                    int _someYLikeLimit = DAT_TileMapState::instance.someYLikeLimit;
                    do {
                        if (DAT_TileMapState::instance.someYLike <= _someYLikeLimit) {
                            flag_and_offset = DAT_TileMapState::instance.someYLike * 10 + 1;
                            int _someY = DAT_TileMapState::instance.someYLike;
                            do {
                                if (*(char*)(_pMap4040 + _someY) != '\0') {
                                    /*
                                      update this part
                                     */
                                    *(undefined1*)(_pMap4040 + _someY) = 0;
                                    int _cur10 = 0;
                                    int _yOffset = _index4000;
                                    int _curX = _someX;
                                    do {
                                        uint _coord2 = _index10 + _cur10;
                                        int local_1c = 2;
                                        uint _x = flag_and_offset;
                                        do {
                                            if (_x - 1 <= 399 && _coord2 <= 399
                                                && DAT_ViewportRenderState::instance
                                                        .DAT_BinaryTileMap400x400[_yOffset + (_x - 1)]
                                                    != '\0') {
                                                /*
                                                  set changed layer to 0
                                                 */
                                                /*
                                                  is valid coordinate
                                                 */
                                                *(undefined1*)(_x + 0x1c5ad87
                                                    + *(int*)((int)&DAT_ViewportRenderState::instance
                                                                  .translationMatrix[0]
                                                                  .addXgetTile
                                                        + _curX)) = 0;
                                            }
                                            if (_x <= 399 && _coord2 <= 399
                                                && DAT_ViewportRenderState::instance
                                                        .DAT_BinaryTileMap400x400[_yOffset + _x]
                                                    != '\0') {
                                                *(undefined1*)(*(int*)((int)&DAT_ViewportRenderState::instance
                                                                           .translationMatrix[0]
                                                                           .addXgetTile
                                                                   + _curX)
                                                    + 0x1c5ad88 + _x) = 0;
                                            }
                                            if (_x + 1 <= 399 && _coord2 <= 399
                                                && DAT_ViewportRenderState::instance
                                                        .DAT_BinaryTileMap400x400[_yOffset + _x + 1]
                                                    != '\0') {
                                                *(undefined1*)(_x + 0x1c5ad89
                                                    + *(int*)((int)&DAT_ViewportRenderState::instance
                                                                  .translationMatrix[0]
                                                                  .addXgetTile
                                                        + _curX)) = 0;
                                            }
                                            if (_x + 2 <= 399 && _coord2 <= 399
                                                && DAT_ViewportRenderState::instance
                                                        .DAT_BinaryTileMap400x400[_yOffset + _x + 2]
                                                    != '\0') {
                                                *(undefined1*)(_x + 0x1c5ad8a
                                                    + *(int*)((int)&DAT_ViewportRenderState::instance
                                                                  .translationMatrix[0]
                                                                  .addXgetTile
                                                        + _curX)) = 0;
                                            }
                                            if (_x + 3 <= 399 && _coord2 <= 399
                                                && DAT_ViewportRenderState::instance
                                                        .DAT_BinaryTileMap400x400[_yOffset + _x + 3]
                                                    != '\0') {
                                                *(undefined1*)(_x + 0x1c5ad8b
                                                    + *(int*)((int)&DAT_ViewportRenderState::instance
                                                                  .translationMatrix[0]
                                                                  .addXgetTile
                                                        + _curX)) = 0;
                                            }
                                            _x = _x + 5;
                                            local_1c = local_1c + -1;
                                        } while (local_1c != 0);
                                        _cur10 = _cur10 + 1;
                                        _yOffset = _yOffset + 400;
                                        _curX = _curX + 0xc;
                                        _someYLikeLimit = DAT_TileMapState::instance.someYLikeLimit;
                                    } while (_cur10 < 10);
                                }
                                flag_and_offset = flag_and_offset + 10;
                                _someY = _someY + 1;
                            } while (_someY <= _someYLikeLimit);
                        }
                        _index4000 = _index4000 + 4000;
                        _index10 = _index10 + 10;
                        DAT_TileMapState::instance.someIndex = DAT_TileMapState::instance.someIndex + 1;
                        _pMap4040 = _pMap4040 + 40;
                        _someX = _someX + 120;
                    } while (DAT_TileMapState::instance.someIndex <= DAT_TileMapState::instance.someLimit);
                }
                this->mappingYRelated = 1000;
                this->yLimit = 0;
                DAT_TileMapState::instance.someIndex = 1000;
                DAT_TileMapState::instance.someLimit = 0;
                DAT_TileMapState::instance.someYLike = 1000;
                DAT_TileMapState::instance.someYLikeLimit = 0;
                return;
            }
            this->field10_0x28 = 0;
            this->mappingYRelated = 0;
            this->yLimit = 399;
            DAT_TileMapState::instance.someIndex = 0;
            DAT_TileMapState::instance.someLimit = 39;
            DAT_TileMapState::instance.someYLike = 0;
            DAT_TileMapState::instance.someYLikeLimit = 0x27;
            return;
        }

    }
}
}
