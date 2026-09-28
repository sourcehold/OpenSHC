#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00498FD0
        uint PathFindingState::commitUnitPathPlanUsingWalkLayer(uint param_1, int param_2, int param_3)
        {
            int iVar1;
            int* _ptrTranslationMatrix;
            int _candidateTile1;
            uint uVar2;
            int _candidateTile2;
            uint _cp3;
            int _candidateTile4;
            uint _cp1;
            uint uVar3;
            uint _cp2;
            int _candidateTile3;
            uint _cp4;
            int iVar4;
            uint _rng;
            uint uVar5;
            int iVar6;
            int _direction;
            uint local_24;
            int _tile;
            int local_14;
            int _y;
            bool _inBounds;
            uint _init_10;
            short _walkLayer;
            if (((399 < (uint)this->unitX) || (399 < (uint)this->unitY))
                || (_inBounds = false, *(char*)(this->unitY * 400 + 0x21aec98 + this->unitX) == '\0')) {
                return 0;
            }
            _tile = DAT_ViewportRenderState::instance.translationMatrix[this->unitY].addXgetTile + this->unitX;
            _y = this->unitY;
            if (DAT_TileMapState::instance.PathConnectionLayer[_tile] == 0) {
                return 0;
            }
            if (param_1 == 0) {
                iVar6 = 80;
            } else if (param_1 == 1) {
                iVar6 = 200;
            } else if (param_1 == 2) {
                iVar6 = 500;
            } else if (param_1 == 3) {
                iVar6 = 1000;
            } else {
                iVar6 = 2000;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk, this)(
                this->unitX, this->unitY, -1, -1, iVar6, 0);
            _walkLayer = DAT_TileMapState::instance.WalkLayer[_tile];
            _rng = (uint)SEC_RNG::instance.currentNumber2;
            this->searchQueue.pathPlanIndex = 0;
            iVar6 = 10;
            local_24 = 1;
            local_14 = 10;
            while (true) {
                while (true) {
                    _init_10 = local_24;
                    if ((_inBounds) && (local_24 < 2)) {
                        return (uint)(this->searchQueue.pathPlanIndex);
                    }
                    _ptrTranslationMatrix = DAT_TileMapState::instance.directionTranslationMatrix[_y] + 1;
                    _direction = 8;
                    param_1 = local_24;
                    iVar4 = 2;
                    do {
                        _candidateTile1 = (*(int (*)[8])(_ptrTranslationMatrix + -1))[0] + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[_candidateTile1] == _walkLayer) {
                            _cp1 = (uint)DAT_TileMapState::instance.CertainPathLayer[_candidateTile1];
                            if (_inBounds) {
                                if ((((_cp1 & 0x4000) == 0) && (uVar3 = _cp1 & 0x3fff, uVar3 <= _init_10))
                                    && ((param_3 == 0 || (uVar3 != _init_10)))) {
                                    uVar2 = uVar3
                                        - ((DAT_TileMapState::instance.RandomLayer[_candidateTile1] ^ _rng) & 7);
                                    uVar5 = uVar2;
                                    if (iVar4 + -2 == iVar6) {
                                        uVar5 = uVar2 - 1;
                                    }
                                    if ((int)uVar5 < (int)param_1) {
                                        param_1 = uVar2;
                                        _direction = iVar4 + -2;
                                        local_24 = uVar3;
                                    }
                                    _rng = (int)_rng >> 1 & 0x7fffU | (_rng & 1) << 0xf;
                                    iVar6 = local_14;
                                }
                            } else if ((((_cp1 & 0x8000) == 0) && (uVar3 = _cp1 & 0x3fff, _init_10 <= uVar3))
                                && ((param_3 == 0 || (uVar3 != _init_10)))) {
                                uVar2 = ((DAT_TileMapState::instance.RandomLayer[_candidateTile1] ^ _rng) & 7) + uVar3;
                                uVar5 = uVar2;
                                if (iVar4 + -2 == iVar6) {
                                    uVar5 = uVar2 + 1;
                                }
                                if ((int)param_1 < (int)uVar5) {
                                    param_1 = uVar2;
                                    _direction = iVar4 + -2;
                                    local_24 = uVar3;
                                }
                                _rng = (int)_rng >> 1 & 0x7fffU | (_rng & 1) << 0xf;
                                iVar6 = local_14;
                            }
                        }
                        _candidateTile2 = *_ptrTranslationMatrix + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[_candidateTile2] == _walkLayer) {
                            _cp2 = (uint)DAT_TileMapState::instance.CertainPathLayer[_candidateTile2];
                            if (_inBounds) {
                                if ((((_cp2 & 0x4000) == 0) && (uVar3 = _cp2 & 0x3fff, uVar3 <= _init_10))
                                    && ((param_3 == 0 || (uVar3 != _init_10)))) {
                                    uVar2 = uVar3
                                        - ((DAT_TileMapState::instance.RandomLayer[_candidateTile2] ^ _rng) & 7);
                                    uVar5 = uVar2;
                                    if (iVar4 + -1 == iVar6) {
                                        uVar5 = uVar2 - 1;
                                    }
                                    if ((int)uVar5 < (int)param_1) {
                                        param_1 = uVar2;
                                        _direction = iVar4 + -1;
                                        local_24 = uVar3;
                                    }
                                    _rng = (int)_rng >> 1 & 0x7fffU | (_rng & 1) << 0xf;
                                    iVar6 = local_14;
                                }
                            } else if ((((_cp2 & 0x8000) == 0) && (uVar3 = _cp2 & 0x3fff, _init_10 <= uVar3))
                                && ((param_3 == 0 || (uVar3 != _init_10)))) {
                                uVar2 = ((DAT_TileMapState::instance.RandomLayer[_candidateTile2] ^ _rng) & 7) + uVar3;
                                uVar5 = uVar2;
                                if (iVar4 + -1 == iVar6) {
                                    uVar5 = uVar2 + 1;
                                }
                                if ((int)param_1 < (int)uVar5) {
                                    param_1 = uVar2;
                                    _direction = iVar4 + -1;
                                    local_24 = uVar3;
                                }
                                _rng = (int)_rng >> 1 & 0x7fffU | (_rng & 1) << 0xf;
                                iVar6 = local_14;
                            }
                        }
                        _candidateTile3 = _ptrTranslationMatrix[1] + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[_candidateTile3] == _walkLayer) {
                            _cp3 = (uint)DAT_TileMapState::instance.CertainPathLayer[_candidateTile3];
                            if (_inBounds) {
                                if ((((_cp3 & 0x4000) == 0) && (uVar3 = _cp3 & 0x3fff, uVar3 <= _init_10))
                                    && ((param_3 == 0 || (uVar3 != _init_10)))) {
                                    uVar2 = uVar3
                                        - ((DAT_TileMapState::instance.RandomLayer[_candidateTile3] ^ _rng) & 7);
                                    uVar5 = uVar2;
                                    if (iVar4 == iVar6) {
                                        uVar5 = uVar2 - 1;
                                    }
                                    if ((int)uVar5 < (int)param_1) {
                                        param_1 = uVar2;
                                        _direction = iVar4;
                                        local_24 = uVar3;
                                    }
                                    _rng = (int)_rng >> 1 & 0x7fffU | (_rng & 1) << 0xf;
                                }
                            } else if ((((_cp3 & 0x8000) == 0) && (uVar3 = _cp3 & 0x3fff, _init_10 <= uVar3))
                                && ((param_3 == 0 || (uVar3 != _init_10)))) {
                                uVar2 = ((DAT_TileMapState::instance.RandomLayer[_candidateTile3] ^ _rng) & 7) + uVar3;
                                uVar5 = uVar2;
                                if (iVar4 == iVar6) {
                                    uVar5 = uVar2 + 1;
                                }
                                if ((int)param_1 < (int)uVar5) {
                                    param_1 = uVar2;
                                    _direction = iVar4;
                                    local_24 = uVar3;
                                }
                                _rng = (int)_rng >> 1 & 0x7fffU | (_rng & 1) << 0xf;
                            }
                        }
                        _candidateTile4 = _ptrTranslationMatrix[2] + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[_candidateTile4] == _walkLayer) {
                            _cp4 = (uint)DAT_TileMapState::instance.CertainPathLayer[_candidateTile4];
                            if (_inBounds) {
                                if ((((_cp4 & 0x4000) == 0) && (uVar3 = _cp4 & 0x3fff, uVar3 <= _init_10))
                                    && ((param_3 == 0 || (uVar3 != _init_10)))) {
                                    uVar2 = uVar3
                                        - ((DAT_TileMapState::instance.RandomLayer[_candidateTile4] ^ _rng) & 7);
                                    uVar5 = uVar2;
                                    if (iVar4 + 1 == iVar6) {
                                        uVar5 = uVar2 - 1;
                                    }
                                    if ((int)uVar5 < (int)param_1) {
                                        param_1 = uVar2;
                                        _direction = iVar4 + 1;
                                        local_24 = uVar3;
                                    }
                                    _rng = (int)_rng >> 1 & 0x7fffU | (_rng & 1) << 0xf;
                                    iVar6 = local_14;
                                }
                            } else if ((((_cp4 & 0x8000) == 0) && (uVar3 = _cp4 & 0x3fff, _init_10 <= uVar3))
                                && ((param_3 == 0 || (uVar3 != _init_10)))) {
                                uVar2 = ((DAT_TileMapState::instance.RandomLayer[_candidateTile4] ^ _rng) & 7) + uVar3;
                                uVar5 = uVar2;
                                if (iVar4 + 1 == iVar6) {
                                    uVar5 = uVar2 + 1;
                                }
                                if ((int)param_1 < (int)uVar5) {
                                    param_1 = uVar2;
                                    _direction = iVar4 + 1;
                                    local_24 = uVar3;
                                }
                                _rng = (int)_rng >> 1 & 0x7fffU | (_rng & 1) << 0xf;
                                iVar6 = local_14;
                            }
                        }
                        _ptrTranslationMatrix = _ptrTranslationMatrix + 4;
                        iVar1 = iVar4 + 2;
                        iVar4 = iVar4 + 4;
                    } while (iVar1 < 8);
                    if (_inBounds) {
                        DAT_TileMapState::instance.CertainPathLayer[_tile]
                            = DAT_TileMapState::instance.CertainPathLayer[_tile] | 0x4000;
                    } else {
                        DAT_TileMapState::instance.CertainPathLayer[_tile]
                            = DAT_TileMapState::instance.CertainPathLayer[_tile] | 0x8000;
                    }
                    if (_direction == 8)
                        break;
                    _tile = _tile + DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction];
                    _y = _y
                        + *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                            + _direction * 8 + 4);
                    if ((this->searchQueue.pathPlanIndex & 1) == 0) {
                        this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2] = (byte)_direction;
                    } else {
                        this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2]
                            = this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2] & 0xf;
                        this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2]
                            = this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2]
                            + (byte)_direction * '\x10';
                    }
                    this->searchQueue.pathPlanIndex = this->searchQueue.pathPlanIndex + 1;
                    iVar6 = _direction;
                    local_14 = _direction;
                    if (799 < (int)this->searchQueue.pathPlanIndex) {
                        return (uint)(this->searchQueue.pathPlanIndex);
                    }
                }
                if (param_2 == 0) {
                    return (uint)(this->searchQueue.pathPlanIndex);
                }
                if (_inBounds)
                    break;
                _inBounds = true;
            }
            return (uint)(this->searchQueue.pathPlanIndex);
        }

    }
}
}
