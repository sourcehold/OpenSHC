#include "../../Map.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00405680
    void Entities::UpdateFireEntity()
    {
        short* psVar1;
        uint _totalHeightAtTile;
        uint uVar2;
        int _entityOffset;
        int iVar3;
        int _y;
        uint _heightDerivative;
        int _x;
        uint uVar4;
        uint _height;
        int _tile;
        short _fireIntensity0;
        short _0xb6;
        int _entityTile;
        short _height0;
        short _playerID;
        uVar2 = DAT_CurrentEntityID::instance;
        _height0 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6;
        if (_height0 == 5) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = 8;
        } else if (_height0 == 4) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = 9;
        } else if (_height0 == 3) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = 0xc;
        } else if (_height0 == 2) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = 0xe;
        } else {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = 0x10;
        }
        DAT_EntityState::instance.entityArray[uVar2].gmID = 0x76;
        _height0 = DAT_EntityState::instance.entityArray[uVar2].someTracker;
        if (_height0 < 0) {
            DAT_EntityState::instance.entityArray[uVar2].unkMinusOne = 0x20;
            psVar1 = &DAT_EntityState::instance.entityArray[uVar2].someTracker;
            *psVar1 = *psVar1 + 1;
            iVar3 = 1;
        LAB_00405715:
            DAT_EntityState::instance.entityArray[uVar2].graphicType2 = iVar3;
        } else {
            if (!_height0) {
                _height0 = DAT_EntityState::instance.entityArray[uVar2].fireParameter_0xb6;
                if (_height0 < 3) {
                LAB_004058a7:
                    if (_height0 == 2) {
                        iVar3 = (int)(char)DAT_EntityDefinedData::instance.FireAnimationFrames1
                                    [DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated];
                    } else {
                        iVar3 = (int)(char)DAT_EntityDefinedData::instance.FireAnimationFrames2
                                    [DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated];
                    }
                } else if (!(DAT_EntityState::instance.entityArray[uVar2].rng_1 & 0x80)) {
                    DAT_EntityState::instance.entityArray[uVar2].gmID = 0x90;
                    iVar3
                        = (int)(char)DAT_EntityDefinedData::instance
                              .FireAnimationFrames5[DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated];
                } else {
                    iVar3
                        = (int)(char)DAT_EntityDefinedData::instance
                              .FireAnimationFrames3[DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated];
                }
            LAB_004058ca:
                if (0 < iVar3)
                    goto LAB_00405715;
            } else {
                if (_height0 == 1) {
                    _height0 = DAT_EntityState::instance.entityArray[uVar2].fireParameter_0xb6;
                    if (_height0 < 3)
                        goto LAB_004058a7;
                    if (!(DAT_EntityState::instance.entityArray[uVar2].rng_1 & 0x80)) {
                        DAT_EntityState::instance.entityArray[uVar2].gmID = 0x90;
                        iVar3 = (int)(char)DAT_EntityDefinedData::instance.FireAnimationFrames8
                                    [DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated];
                    } else {
                        iVar3 = (int)(char)DAT_EntityDefinedData::instance.FireAnimationFrames7
                                    [DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated];
                    }
                    goto LAB_004058ca;
                }
                if (_height0 == 2) {
                    _height0 = DAT_EntityState::instance.entityArray[uVar2].fireParameter_0xb6;
                    if (_height0 < 3)
                        goto LAB_004058a7;
                    if (!(DAT_EntityState::instance.entityArray[uVar2].rng_1 & 0x80)) {
                        DAT_EntityState::instance.entityArray[uVar2].gmID = 0x90;
                        iVar3 = (int)(char)DAT_EntityDefinedData::instance.FireAnimationFrames6
                                    [DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated];
                    } else {
                        iVar3 = (int)(char)DAT_EntityDefinedData::instance.FireAnimationFrames4
                                    [DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated];
                    }
                    goto LAB_004058ca;
                }
            }
            DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated = 0;
            _height0 = DAT_EntityState::instance.entityArray[uVar2].someTracker;
            if (!_height0) {
                DAT_EntityState::instance.entityArray[uVar2].someTracker = 1;
            } else if (_height0 == 1) {
                psVar1 = &DAT_EntityState::instance.entityArray[uVar2].someCounter_OR_hitGround;
                *psVar1 = *psVar1 + 1;
                if ((DAT_EntityState::instance.entityArray[uVar2].someCounter_OR_hitGround == 6)
                    && (2 < DAT_EntityState::instance.entityArray[uVar2].fireParameter_0xb6)) {
                    DAT_EntityState::instance.entityArray[uVar2].fireParameter_0xb6 = 2;
                }
                psVar1 = &DAT_EntityState::instance.entityArray[uVar2].someCounter_OR_hitGround;
                *psVar1 = *psVar1 + 1;
                if (8 < DAT_EntityState::instance.entityArray[uVar2].someCounter_OR_hitGround) {
                    DAT_EntityState::instance.entityArray[uVar2].someTracker = 2;
                }
                if ((DAT_TileMapState::instance.BuildingLayer[DAT_EntityState::instance.entityArray[uVar2].tile] != 0)
                    && (iVar3 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor,
                            DAT_BuildingsState::ptr)((int)DAT_TileMapState::instance
                                .BuildingLayer[DAT_EntityState::instance.entityArray[uVar2].tile]),
                        uVar2 = DAT_CurrentEntityID::instance, iVar3)) {
                    if (DAT_BuildingsState::instance
                            .buildings[DAT_TileMapState::instance.BuildingLayer
                                    [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].tile]]
                            .fireDuration
                        == 0) {
                        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker = 2;
                    } else {
                        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6
                            < 3) {
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6 = 3;
                        }
                        DAT_EntityState::instance.entityArray[uVar2].someTracker = 1;
                        DAT_EntityState::instance.entityArray[uVar2].someCounter_OR_hitGround = 0;
                    }
                }
            } else if (_height0 == 2) {
                DAT_EntityState::instance.entityArray[uVar2].logicalState = 3;
            }
        }
        _entityOffset = DAT_CurrentEntityID::instance * 0xe8;
        if ((DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker != 0)
            || (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated != 1))
            goto LAB_00405b3d;
        _height0 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field79_0xb8;
        _tile = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].tile;
        _height = (uint)DAT_TileMapState::instance.HeightLayer[_tile];
        if ((3 < _height0)
            || (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6 < 2))
            goto LAB_00405b3d;
        if (!_height0) {
            _totalHeightAtTile = MACRO_CALL_MEMBER(
                Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(_tile + -1);
            _heightDerivative = (int)(_height - _totalHeightAtTile) >> 0x1f;
            if (0x18 < (int)((_height - _totalHeightAtTile ^ _heightDerivative) - _heightDerivative))
                goto LAB_00405b2a;
            _fireIntensity0 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireIntensity;
            _0xb6 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6;
            _height0 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].height;
            _y = (int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microY;
            _x = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microX + -8;
        LAB_00405b18:
            _playerID = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner;
        LAB_00405b22:
            MACRO_CALL(Map::Entities_Func::IgniteFireAtMiniTile)((int)_playerID, _x, _y,
                (int)((int)(_height0)), (int)((int)(_0xb6 + -1)), (int)((int)(_fireIntensity0)));
        } else {
            if (_height0 == 1) {
                uVar2 = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                    _tile + 1);
                uVar4 = (int)(_height - uVar2) >> 0x1f;
                if (0x18 < (int)((_height - uVar2 ^ uVar4) - uVar4))
                    goto LAB_00405b2a;
                _fireIntensity0 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireIntensity;
                _0xb6 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6;
                _height0 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].height;
                _y = (int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microY;
                _playerID = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner;
                _x = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microX + 8;
                goto LAB_00405b22;
            }
            if (_height0 == 2) {
                uVar2 = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                    (int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].xPosition
                    + DAT_ViewportRenderState::instance
                        .translationMatrix
                            [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].yPosition + 1]
                        .addXgetTile);
                uVar4 = (int)(_height - uVar2) >> 0x1f;
                if ((int)((_height - uVar2 ^ uVar4) - uVar4) < 0x19) {
                    _fireIntensity0
                        = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireIntensity;
                    _0xb6 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6;
                    _y = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microY + 8;
                LAB_00405b09:
                    _height0 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].height;
                    _x = (int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microX;
                    goto LAB_00405b18;
                }
            } else if ((_height0 == 3)
                && (uVar2
                    = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                        (int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].xPosition
                        + DAT_ViewportRenderState::instance
                            .translationMatrix
                                [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].yPosition + -1]
                            .addXgetTile),
                    uVar4 = (int)(_height - uVar2) >> 0x1f, (int)((_height - uVar2 ^ uVar4) - uVar4) < 0x19)) {
                _fireIntensity0 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireIntensity;
                _0xb6 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireParameter_0xb6;
                _y = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microY + -8;
                goto LAB_00405b09;
            }
        }
    LAB_00405b2a:
        _entityOffset = DAT_CurrentEntityID::instance * 0xe8;
        psVar1 = &DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field79_0xb8;
        *psVar1 = *psVar1 + 1;
    LAB_00405b3d:
        iVar3 = *(int*)(DAT_EntityState::instance.entityArray[0].unused_0x48 + _entityOffset + 4);
        if (!(DAT_TileMapState::instance.LogicLayer[iVar3] & 0xba7001b1U)) {
            MACRO_CALL_MEMBER(
                Map::Entities::EntityState_Func::processFireDamageToUnitsAtTile, DAT_EntityState::ptr)(iVar3,
                (int)*(short*)(DAT_EntityState::instance.entityArray[0].unused_0x2e + _entityOffset + -2),
                (int)*(short*)(DAT_EntityState::instance.entityArray[0].unused_0xe0 + _entityOffset + -8));
        }
    }

}
}
