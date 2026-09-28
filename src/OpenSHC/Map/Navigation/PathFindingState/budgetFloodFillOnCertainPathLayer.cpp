#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Map/Location/Point8IntXY.hpp"

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
            int _writeIndex;
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
            _writeIndex = 1;
            if (((x < 400) && (y < 400)) && (*(char*)(y * 400 + 0x21aec98 + x) != '\0')) {
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
                    piVar2 = DAT_TileMapState::instance.directionTranslationMatrix[_xUnk] + 1;
                    _distance = (short)marker;
                    DAT_TileMapState::instance.CertainPathLayer[_tile] = _distance;
                    piVar3 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].int_.yOffset;
                    do {
                        _candidate = (*(int (*)[8])(piVar2 + -1))[0] + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[_candidate] == this->searchGeneration) {
                            if (DAT_TileMapState::instance.CertainPathLayer[_candidate] == marker) {
                                budget = budget + -1;
                            } else if (0 < DAT_TileMapState::instance.CertainPathLayer[_candidate]) {
                                iVar1 = ((Point8IntXY*)(piVar3 + -1))->xOffset;
                                _tilesQueue[_writeIndex] = _candidate;
                                _xs[_writeIndex] = iVar1 + _yUnk;
                                _ys[_writeIndex] = *piVar3 + _xUnk;
                                _writeIndex = _writeIndex + 1;
                                DAT_TileMapState::instance.CertainPathLayer[_candidate] = _distance;
                                if (999 < _writeIndex) {
                                    _writeIndex = 0;
                                }
                            }
                        } else {
                            budget = budget + -1;
                        }
                        uVar4 = *piVar2 + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[uVar4] == this->searchGeneration) {
                            if (DAT_TileMapState::instance.CertainPathLayer[uVar4] == marker) {
                                budget = budget + -1;
                            } else if (0 < DAT_TileMapState::instance.CertainPathLayer[uVar4]) {
                                iVar1 = piVar3[1];
                                _tilesQueue[_writeIndex] = uVar4;
                                _xs[_writeIndex] = iVar1 + _yUnk;
                                _ys[_writeIndex] = piVar3[2] + _xUnk;
                                _writeIndex = _writeIndex + 1;
                                DAT_TileMapState::instance.CertainPathLayer[uVar4] = _distance;
                                if (999 < _writeIndex) {
                                    _writeIndex = 0;
                                }
                            }
                        } else {
                            budget = budget + -1;
                        }
                        uVar4 = piVar2[1] + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[uVar4] == this->searchGeneration) {
                            if (DAT_TileMapState::instance.CertainPathLayer[uVar4] == marker) {
                                budget = budget + -1;
                            } else if (0 < DAT_TileMapState::instance.CertainPathLayer[uVar4]) {
                                iVar1 = piVar3[3];
                                _tilesQueue[_writeIndex] = uVar4;
                                _xs[_writeIndex] = iVar1 + _yUnk;
                                _ys[_writeIndex] = piVar3[4] + _xUnk;
                                _writeIndex = _writeIndex + 1;
                                DAT_TileMapState::instance.CertainPathLayer[uVar4] = _distance;
                                if (999 < _writeIndex) {
                                    _writeIndex = 0;
                                }
                            }
                        } else {
                            budget = budget + -1;
                        }
                        uVar4 = piVar2[2] + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[uVar4] == this->searchGeneration) {
                            if (DAT_TileMapState::instance.CertainPathLayer[uVar4] == marker) {
                                budget = budget + -1;
                            } else if (0 < DAT_TileMapState::instance.CertainPathLayer[uVar4]) {
                                iVar1 = piVar3[5];
                                _tilesQueue[_writeIndex] = uVar4;
                                _xs[_writeIndex] = iVar1 + _yUnk;
                                _ys[_writeIndex] = piVar3[6] + _xUnk;
                                _writeIndex = _writeIndex + 1;
                                DAT_TileMapState::instance.CertainPathLayer[uVar4] = _distance;
                                if (999 < _writeIndex) {
                                    _writeIndex = 0;
                                }
                            }
                        } else {
                            budget = budget + -1;
                        }
                        piVar2 = piVar2 + 4;
                        piVar3 = piVar3 + 8;
                    } while ((int)piVar3 < 0xb4908c);
                    _readIndex = _readIndex + 1;
                    if (999 < _readIndex) {
                        _readIndex = 0;
                    }
                } while (_readIndex != _writeIndex);
            }
            return;
        }

    }
}
}
