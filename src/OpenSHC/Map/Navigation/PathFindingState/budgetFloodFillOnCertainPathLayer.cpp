#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Location/Point8IntXY.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Location::Point8IntXY;

        /*
          WARNING: Function: __alloca_probe replaced with injection: alloca_probe
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049DDC0
        void PathFindingState::budgetFloodFillOnCertainPathLayer(uint x, uint y, int marker, int budget)
        {
            int iVar1;
            int* piVar2;
            int* piVar3;
            uint _candidate;
            uint uVar4;
            short _distance;
            int _readIndex;
            uint _ys[1000];
            uint _xs[1000];
            uint _tilesQueue[1000];
            uint _tile;
            uint _xUnk;
            uint _yUnk;
            _tilesQueue[999] = 0x49ddca;
            _readIndex = 0;
            int _writeIndex = 1;
            if (x > 399 || y > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return;
            }
            this->DAT_Mini_spreads = this->DAT_Mini_spreads + 1;
            _ys[0] = y;
            _xs[0] = x;
            _tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            do {
                _tile = _tilesQueue[_readIndex];
                if (0x13a0f < _tile) {
                    return;
                }
                if (budget <= _writeIndex) {
                    return;
                }
                if (999 < _writeIndex) {
                    return;
                }
                _yUnk = _xs[_readIndex];
                _xUnk = _ys[_readIndex];
                _distance = (short)marker;
                DAT_TileMapState::instance.CertainPathLayer[_tile] = _distance;
                for (int _direction = 0; _direction < 8; _direction = _direction + 4) {
                    _candidate = DAT_TileMapState::instance.directionTranslationMatrix[_xUnk][_direction] + _tile;
                    if (DAT_TileMapState::instance.WalkLayer[_candidate] == this->searchGeneration) {
                        if (DAT_TileMapState::instance.CertainPathLayer[_candidate] == marker) {
                            budget = budget + -1;
                        } else if (0 < DAT_TileMapState::instance.CertainPathLayer[_candidate]) {
                            iVar1 = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                        .int_.xOffset;
                            _tilesQueue[_writeIndex] = _candidate;
                            _xs[_writeIndex] = iVar1 + _yUnk;
                            _ys[_writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                      .int_.yOffset
                                + _xUnk;
                            _writeIndex = _writeIndex + 1;
                            DAT_TileMapState::instance.CertainPathLayer[_candidate] = _distance;
                            if (999 < _writeIndex) {
                                _writeIndex = 0;
                            }
                        }
                    } else {
                        budget = budget + -1;
                    }
                    uVar4 = DAT_TileMapState::instance.directionTranslationMatrix[_xUnk][_direction + 1] + _tile;
                    if (DAT_TileMapState::instance.WalkLayer[uVar4] == this->searchGeneration) {
                        if (DAT_TileMapState::instance.CertainPathLayer[uVar4] == marker) {
                            budget = budget + -1;
                        } else if (0 < DAT_TileMapState::instance.CertainPathLayer[uVar4]) {
                            iVar1 = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 1]
                                        .int_.xOffset;
                            _tilesQueue[_writeIndex] = uVar4;
                            _xs[_writeIndex] = iVar1 + _yUnk;
                            _ys[_writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 1]
                                      .int_.yOffset
                                + _xUnk;
                            _writeIndex = _writeIndex + 1;
                            DAT_TileMapState::instance.CertainPathLayer[uVar4] = _distance;
                            if (999 < _writeIndex) {
                                _writeIndex = 0;
                            }
                        }
                    } else {
                        budget = budget + -1;
                    }
                    uVar4 = DAT_TileMapState::instance.directionTranslationMatrix[_xUnk][_direction + 2] + _tile;
                    if (DAT_TileMapState::instance.WalkLayer[uVar4] == this->searchGeneration) {
                        if (DAT_TileMapState::instance.CertainPathLayer[uVar4] == marker) {
                            budget = budget + -1;
                        } else if (0 < DAT_TileMapState::instance.CertainPathLayer[uVar4]) {
                            iVar1 = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 2]
                                        .int_.xOffset;
                            _tilesQueue[_writeIndex] = uVar4;
                            _xs[_writeIndex] = iVar1 + _yUnk;
                            _ys[_writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 2]
                                      .int_.yOffset
                                + _xUnk;
                            _writeIndex = _writeIndex + 1;
                            DAT_TileMapState::instance.CertainPathLayer[uVar4] = _distance;
                            if (999 < _writeIndex) {
                                _writeIndex = 0;
                            }
                        }
                    } else {
                        budget = budget + -1;
                    }
                    uVar4 = DAT_TileMapState::instance.directionTranslationMatrix[_xUnk][_direction + 3] + _tile;
                    if (DAT_TileMapState::instance.WalkLayer[uVar4] == this->searchGeneration) {
                        if (DAT_TileMapState::instance.CertainPathLayer[uVar4] == marker) {
                            budget = budget + -1;
                        } else if (0 < DAT_TileMapState::instance.CertainPathLayer[uVar4]) {
                            iVar1 = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 3]
                                        .int_.xOffset;
                            _tilesQueue[_writeIndex] = uVar4;
                            _xs[_writeIndex] = iVar1 + _yUnk;
                            _ys[_writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 3]
                                      .int_.yOffset
                                + _xUnk;
                            _writeIndex = _writeIndex + 1;
                            DAT_TileMapState::instance.CertainPathLayer[uVar4] = _distance;
                            if (999 < _writeIndex) {
                                _writeIndex = 0;
                            }
                        }
                    } else {
                        budget = budget + -1;
                    }
                }

                _readIndex = _readIndex + 1;
                if (999 < _readIndex) {
                    _readIndex = 0;
                }
            } while (_readIndex != _writeIndex);
            return;
        }

    }
}
}
