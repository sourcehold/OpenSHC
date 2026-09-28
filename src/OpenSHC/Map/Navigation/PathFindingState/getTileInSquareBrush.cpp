#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Function: __alloca_probe replaced with injection: alloca_probe
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          fixme:bug: the index parameter is off by -1 for brush indices larger than 6. Phrased differently,   index 7 is
          faulty   decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049BE60
        void PathFindingState::getTileInSquareBrush(int brushTileIndex, uint x, uint y)
        {
            int (*_dirAtTile)[8];
            int _index_3;
            int _tracker_3;
            int _tracker;
            uint _yArray[1000];
            int _tileArray[1000];
            int _tile_2;
            uint _y;
            int _yTranslationUnk;
            /*
              __chkstk
             */
            _tileArray[999] = 0x49be6a;
            _index_3 = 1;
            this->calculations = this->calculations + 1;
            this->searchGeneration = this->searchGeneration + 1;
            _tracker = 0;
            _tracker_3 = 0;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    160800, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->resultTile = 0;
            this->resultY = 0;
            this->resultX = 0;
            if (x < 400 && y < 400 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != '\0') {
                _tileArray[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                _yArray[0] = y;
                if (brushTileIndex < 1) {
                    this->resultY = y;
                    this->resultTile = _tileArray[0];
                    return;
                }
                while ((_tile_2 = _tileArray[_tracker_3], -1 < _tile_2 && (_tile_2 < 80400))) {
                    _y = _yArray[_tracker_3];
                    if ((DAT_TileMapState::instance.LogicLayer[_tile_2] & 0x30) == 0) {
                        int _direction = 0;
                        _dirAtTile = DAT_TileMapState::instance.directionTranslationMatrix + _y;
                        do {
                            int _currentTile = (*_dirAtTile)[0] + _tile_2;
                            if (DAT_TileMapState::instance.WalkLayer[_currentTile] != this->searchGeneration) {
                                _tracker = _tracker + 1;
                                if (brushTileIndex <= _tracker) {
                                    this->resultY = *(int*)((int)DAT_TerrainDefinedData::instance
                                                                .clockwiseCardinalTranslationMatrix
                                                        + _direction * 8 + 4)
                                        + _y;
                                    this->resultTile = _currentTile;
                                    return;
                                }
                                DAT_TileMapState::instance.WalkLayer[_currentTile] = (short)this->searchGeneration;
                                _yTranslationUnk
                                    = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                        + _direction * 8 + 4);
                                _tileArray[_index_3] = _currentTile;
                                _yArray[_index_3] = _yTranslationUnk + _y;
                                _index_3 = _index_3 + 1;
                                if (80400 < _index_3) {
                                    _index_3 = 0;
                                }
                            }
                            _direction = _direction + 2;
                            _dirAtTile = (int (*)[8])(*_dirAtTile + 2);
                        } while (_direction < 8);
                    }
                    _tracker_3 = _tracker_3 + 1;
                    if (80400 < _tracker_3) {
                        _tracker_3 = 0;
                    }
                    if (_tracker_3 == _index_3) {
                        return;
                    }
                }
            }
            return;
        }

    }
}
}
