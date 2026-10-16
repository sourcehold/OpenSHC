#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
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
            int* _ptrTranslationMatrix;
            int _candidateTile;
            uint uVar2;
            uint _cp;
            uint uVar3;
            int iVar4;
            uint _rng;
            uint uVar5;
            int iVar6;
            int _direction;
            uint local_24;
            int _tile;
            int local_14;
            int _y;
            int _inBounds;
            uint _init_10;
            int _walkLayer;
            if (399 < (uint)this->unitX || 399 < (uint)this->unitY
                || (_inBounds = false,
                    DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[this->unitY * 400 + this->unitX]
                        == '\0')) {
                return 0;
            }
            _tile = DAT_ViewportRenderState::instance.translationMatrix[this->unitY].addXgetTile + this->unitX;
            _y = this->unitY;
            if ((short)DAT_TileMapState::instance.PathConnectionLayer[_tile] == 0) {
                return 0;
            }
            if (param_1 == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
                    DAT_PathFindingState::ptr)(this->unitX, this->unitY, -1, -1, 80, 0);
            } else if (param_1 == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
                    DAT_PathFindingState::ptr)(this->unitX, this->unitY, -1, -1, 200, 0);
            } else if (param_1 == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
                    DAT_PathFindingState::ptr)(this->unitX, this->unitY, -1, -1, 500, 0);
            } else if (param_1 == 3) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
                    DAT_PathFindingState::ptr)(this->unitX, this->unitY, -1, -1, 1000, 0);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
                    DAT_PathFindingState::ptr)(this->unitX, this->unitY, -1, -1, 2000, 0);
            }
            local_14 = 10;
            _walkLayer = (short)DAT_TileMapState::instance.WalkLayer[_tile];
            _rng = (short)SEC_RNG::instance.currentNumber2;
            this->searchQueue.pathPlanIndex = 0;
            iVar6 = 10;
            local_24 = 1;
            while (true) {
                while (true) {
                    if ((_inBounds) && ((int)local_24 <= 1)) {
                        return (uint)(this->searchQueue.pathPlanIndex);
                    }
                    iVar4 = 2;
                    param_1 = local_24;
                    _init_10 = local_24;
                    _direction = 8;
                    _ptrTranslationMatrix = DAT_TileMapState::instance.directionTranslationMatrix[_y] + 1;
                    do {
                        _candidateTile = (*(int (*)[8])(_ptrTranslationMatrix + -1))[0] + _tile;
                        if ((short)DAT_TileMapState::instance.WalkLayer[_candidateTile] == _walkLayer) {
                            _cp = (short)DAT_TileMapState::instance.CertainPathLayer[_candidateTile];
                            if (_inBounds == 0) {
                                if ((_cp & 0x8000) == 0 && (uVar3 = _cp & 0x3fff, (int)_init_10 <= (int)uVar3)
                                    && (param_3 == 0 || (uVar3 != _init_10))) {
                                    uVar2
                                        = ((DAT_TileMapState::instance.RandomLayer[_candidateTile] ^ _rng) & 7) + uVar3;
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
                            } else if (_inBounds == 1) {
                                if ((_cp & 0x4000) == 0 && (uVar3 = _cp & 0x3fff, (int)uVar3 <= (int)_init_10)
                                    && (param_3 == 0 || (uVar3 != _init_10))) {
                                    uVar2
                                        = uVar3 - ((DAT_TileMapState::instance.RandomLayer[_candidateTile] ^ _rng) & 7);
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
                            }
                        }
                        _candidateTile = *_ptrTranslationMatrix + _tile;
                        if ((short)DAT_TileMapState::instance.WalkLayer[_candidateTile] == _walkLayer) {
                            _cp = (short)DAT_TileMapState::instance.CertainPathLayer[_candidateTile];
                            if (_inBounds == 0) {
                                if ((_cp & 0x8000) == 0 && (uVar3 = _cp & 0x3fff, (int)_init_10 <= (int)uVar3)
                                    && (param_3 == 0 || (uVar3 != _init_10))) {
                                    uVar2
                                        = ((DAT_TileMapState::instance.RandomLayer[_candidateTile] ^ _rng) & 7) + uVar3;
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
                            } else if (_inBounds == 1) {
                                if ((_cp & 0x4000) == 0 && (uVar3 = _cp & 0x3fff, (int)uVar3 <= (int)_init_10)
                                    && (param_3 == 0 || (uVar3 != _init_10))) {
                                    uVar2
                                        = uVar3 - ((DAT_TileMapState::instance.RandomLayer[_candidateTile] ^ _rng) & 7);
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
                            }
                        }
                        _candidateTile = _ptrTranslationMatrix[1] + _tile;
                        if ((short)DAT_TileMapState::instance.WalkLayer[_candidateTile] == _walkLayer) {
                            _cp = (short)DAT_TileMapState::instance.CertainPathLayer[_candidateTile];
                            if (_inBounds == 0) {
                                if ((_cp & 0x8000) == 0 && (uVar3 = _cp & 0x3fff, (int)_init_10 <= (int)uVar3)
                                    && (param_3 == 0 || (uVar3 != _init_10))) {
                                    uVar2
                                        = ((DAT_TileMapState::instance.RandomLayer[_candidateTile] ^ _rng) & 7) + uVar3;
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
                            } else if (_inBounds == 1) {
                                if ((_cp & 0x4000) == 0 && (uVar3 = _cp & 0x3fff, (int)uVar3 <= (int)_init_10)
                                    && (param_3 == 0 || (uVar3 != _init_10))) {
                                    uVar2
                                        = uVar3 - ((DAT_TileMapState::instance.RandomLayer[_candidateTile] ^ _rng) & 7);
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
                            }
                        }
                        _candidateTile = _ptrTranslationMatrix[2] + _tile;
                        if ((short)DAT_TileMapState::instance.WalkLayer[_candidateTile] == _walkLayer) {
                            _cp = (short)DAT_TileMapState::instance.CertainPathLayer[_candidateTile];
                            if (_inBounds == 0) {
                                if ((_cp & 0x8000) == 0 && (uVar3 = _cp & 0x3fff, (int)_init_10 <= (int)uVar3)
                                    && (param_3 == 0 || (uVar3 != _init_10))) {
                                    uVar2
                                        = ((DAT_TileMapState::instance.RandomLayer[_candidateTile] ^ _rng) & 7) + uVar3;
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
                            } else if (_inBounds == 1) {
                                if ((_cp & 0x4000) == 0 && (uVar3 = _cp & 0x3fff, (int)uVar3 <= (int)_init_10)
                                    && (param_3 == 0 || (uVar3 != _init_10))) {
                                    uVar2
                                        = uVar3 - ((DAT_TileMapState::instance.RandomLayer[_candidateTile] ^ _rng) & 7);
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
                            }
                        }
                        _ptrTranslationMatrix = _ptrTranslationMatrix + 4;
                        iVar4 = iVar4 + 4;
                    } while (iVar4 + -2 < 8);
                    if (_inBounds == 0) {
                        DAT_TileMapState::instance.CertainPathLayer[_tile]
                            = DAT_TileMapState::instance.CertainPathLayer[_tile] | 0x8000;
                    } else {
                        DAT_TileMapState::instance.CertainPathLayer[_tile]
                            = DAT_TileMapState::instance.CertainPathLayer[_tile] | 0x4000;
                    }
                    if (_direction == 8)
                        break;
                    _tile = _tile + DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction];
                    _y = _y
                        + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.yOffset;
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
                _inBounds = 1;
            }
            return (uint)(this->searchQueue.pathPlanIndex);
        }

    }
}
}
