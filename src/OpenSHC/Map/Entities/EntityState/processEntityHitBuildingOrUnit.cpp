#include "../../../Map.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using Commands::MappersEnum;
        using DE::SHCDE::eSFX;
        using Game::GameMode2;
        using Map::Buildings::BuildingType;
        using Map::Buildings::BuildingTypeShort;
        using Map::Entities::EntityType;
        using Map::Units::UnitType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00407190
        undefined4 EntityState::processEntityHitBuildingOrUnit(int entityID)
        {
            int* piVar1;
            short* psVar2;
            EntityTypeShort EVar3;
            int uVar4;
            short sVar5;
            BuildingTypeShort BVar6;
            short sVar7;
            uint _y;
            BOOLEnum BVar8;
            int _buildingHealth;
            int _entityOriginUnitID;
            uint _x;
            int iVar9;
            int _randomNumber;
            Point8IntXY* pPVar10;
            int _someTile;
            int iVar11;
            uint _collateralDamageUnk;
            int _randomNumber2;
            uint _damageUnk;
            int _buildingID;
            EntityState* local_10;
            int local_c;
            int _tile;
            uint local_4;
            short _entityType;
            short _entityType_2;
            short _playerID;
            short _yPosition;
            short _xPosition;
            local_10 = this;
            _someTile = (int)this->entityArray[entityID].microX;
            _buildingID = (int)this->entityArray[entityID].microY;
            sVar7 = (short)((int)(_buildingID + (_buildingID >> 0x1f & 7U)) >> 3);
            this->entityArray[entityID].yPosition = sVar7;
            _y = (uint)sVar7;
            sVar7 = (short)((int)(_someTile + (_someTile >> 0x1f & 7U)) >> 3);
            this->entityArray[entityID].xPosition = sVar7;
            _x = (uint)sVar7;
            _entityType = this->entityArray[entityID].entityType;
            _someTile = DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile + _x;
            local_c = 1;
            this->entityArray[entityID].tile = _someTile;
            if (_entityType == 0x1d) {
                if ((((_x < 400) && (_y < 400)) && (*(char*)(_y * 400 + 0x21aec98 + _x) != '\0'))
                    && ((!(DAT_TileMapState::instance.LogicLayer[_someTile] & 0x30)
                        && (0 < this->entityArray[entityID].height)))) {
                    this->entityArray[entityID].nextEntityOnThisTileByID
                        = DAT_TileMapState::instance.EntityLayer[_someTile];
                    DAT_TileMapState::instance.EntityLayer[_someTile] = (short)entityID;
                    return (undefined4)(1);
                }
                this->entityArray[entityID].tile = 0;
                return (undefined4)(0);
            }
            if (((399 < _x) || (399 < _y)) || (*(char*)(_y * 400 + 0x21aec98 + _x) == '\0')) {
                this->entityArray[entityID].logicalState = 3;
                return (undefined4)(0);
            }
            if ((DAT_TileMapState::instance.LogicLayer[_someTile] & 0x30)) {
                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::markEntityDestroyed, this)(entityID);
                return (undefined4)(0);
            }
            _tile = _someTile * 2;
            if ((int)_entityType - 10U < 6) {
                DAT_TileMapState::instance.MiscDisplayLayer[_someTile]
                    = DAT_TileMapState::instance.MiscDisplayLayer[_someTile] | 0x1000;
                EVar3 = this->entityArray[entityID].entityType;
                if ((EVar3 == Map::Entities::ET_BRAZIER)
                    || (EVar3 == Map::Entities::ET_HEADS_ON_SPIKES)) {
                    _buildingID = this->entityArray[entityID].tile;
                    if (DAT_TileMapState::instance.BuildingLayer[_buildingID] == 0) {
                        if ((DAT_TileMapState::instance.LogicLayer[_buildingID] & 0x100U)) {
                            if (DAT_TileMapState::instance.DamageLayer[_buildingID] == 0) {
                                this->entityArray[entityID].height
                                    = (ushort)DAT_TileMapState::instance.HeightLayer[_buildingID];
                            } else {
                                this->entityArray[entityID].height
                                    = DAT_TileMapState::instance.HeightLayer[_buildingID] + 0xf;
                            }
                            goto LAB_00408150;
                        }
                    } else {
                        switch (DAT_BuildingsState::instance
                                .buildings[DAT_TileMapState::instance.BuildingLayer[_buildingID]]
                                .buildingType) {
                        case Map::Buildings::BT_STONEKEEP:
                        case Map::Buildings::BT_STRONGHOLD:
                        case Map::Buildings::BT_KEEPFOUR:
                        case Map::Buildings::BT_KEEPFIVE:
                        case Map::Buildings::BT_GATEHOUSELARGE:
                        case Map::Buildings::BT_GATEHOUSESMALL:
                        case Map::Buildings::BT_TOWER1:
                        case Map::Buildings::BT_TOWER2:
                        case Map::Buildings::BT_TOWER3:
                        case Map::Buildings::BT_TOWER4:
                        case Map::Buildings::BT_TOWER5:
                            _y = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAtTile,
                                DAT_TileMapState::ptr)(_buildingID);
                            this->entityArray[entityID].height = (short)_y;
                            goto LAB_00408150;
                        }
                    }
                    if (DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT) {
                        MACRO_CALL_MEMBER(
                            Map::Buildings::BuildingsState_Func::getBuildingCost, DAT_BuildingsState::ptr)(
                            Commands::M_MAPPER_BRAZIER, (int*)&local_10, (int*)&local_4);
                        piVar1 = DAT_GameState::instance
                                     .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                     .startResources
                            + 0xf;
                        *piVar1 = *piVar1 + local_4;
                    }
                    MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::markEntityDestroyed, this)(entityID);
                } else {
                    _buildingID = this->entityArray[entityID].tile;
                    _y = DAT_TileMapState::instance.LogicLayer[_buildingID];
                    if (!_y) {
                        if (DAT_TileMapState::instance.BuildingLayer[_buildingID] == 0) {
                            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::markEntityDestroyed, this)(
                                entityID);
                        }
                    } else if (DAT_TileMapState::instance.DamageLayer[_buildingID] != 0) {
                        if (!(_y & 0x400000)) {
                            if (!(_y & 0x200)) {
                                this->entityArray[entityID].height
                                    = (ushort)DAT_TileMapState::instance.HeightLayer[_buildingID];
                            } else {
                                this->entityArray[entityID].height
                                    = DAT_TileMapState::instance.HeightLayer[_buildingID] + 10;
                            }
                        } else {
                            this->entityArray[entityID].height
                                = DAT_TileMapState::instance.HeightLayer[_buildingID] + 0x14;
                        }
                    }
                }
                goto LAB_00408150;
            }
            uVar4 = (short)DAT_TileMapState::instance.UnitLayer[_someTile];
            if ((_entityType != 1) || (this->entityArray[entityID].rng_2 != 2)) {
                if (((_entityType == 0x16) || (((_entityType == 3 || (_entityType == 2)) || (_entityType == 4))))
                    || (0x50 < this->entityArray[entityID].velocityUnk)) {
                    while (_buildingID = (int)(short)uVar4, _buildingID) {
                        if ((this->entityArray[entityID].logicalState == 2)
                            && (BVar8 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::processEntityDamageToUnit,
                                    DAT_UnitsState::ptr)(_buildingID, entityID, 0),
                                BVar8)) {
                            if (this->entityArray[entityID].entityType != Map::Entities::ET_COW_FLYING) {
                                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::markEntityDestroyed, this)(
                                    entityID);
                                return (undefined4)(0);
                            }
                            _y = MACRO_CALL_MEMBER(
                                Map::TileMapState_Func::returnSomeHeight, DAT_TileMapState::ptr)(_someTile, 0);
                            this->entityArray[entityID].height = (short)_y;
                            goto LAB_004079b4;
                        }
                        uVar4 = DAT_UnitsState::instance.units[_buildingID].nextUnitOnTheSameTile;
                    }
                }
                EVar3 = this->entityArray[entityID].entityType;
                if (((EVar3 == Map::Entities::ET_TREBUCHET) || (EVar3 == Map::Entities::ET_CATAPULT))
                    || ((EVar3 == Map::Entities::ET_MANGONEL
                        || (0x50 < this->entityArray[entityID].velocityUnk)))) {
                    _buildingID = 1;
                    do {
                        uVar4 = DAT_TileMapState::instance
                                    .UnitLayer[DAT_TileMapState::instance.directionTranslationMatrix
                                                   [this->entityArray[entityID].yPosition][_buildingID]
                                        + _someTile];
                        while (iVar11 = (int)(short)uVar4, iVar11) {
                            if (((DAT_UnitsState::instance.units[iVar11].field64_0x90 != 0)
                                    && (this->entityArray[entityID].logicalState == 2))
                                && (BVar8 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::processEntityDamageToUnit,
                                        DAT_UnitsState::ptr)(iVar11, entityID, 1),
                                    BVar8)) {
                                MACRO_CALL_MEMBER(
                                    Map::Entities::EntityState_Func::markEntityDestroyed, local_10)(entityID);
                                return (undefined4)(0);
                            }
                            uVar4 = DAT_UnitsState::instance.units[iVar11].nextUnitOnTheSameTile;
                        }
                        _buildingID = _buildingID + 2;
                    } while (_buildingID < 8);
                }
            }
            if (this->entityArray[entityID].entityType == Map::Entities::ET_COW_POISON_CLOUD) {
                local_4 = MACRO_CALL_MEMBER(
                    Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(_someTile);
                _buildingID = 0;
                do {
                    iVar11 = DAT_TileMapState::instance
                                 .directionTranslationMatrix[this->entityArray[entityID].yPosition][_buildingID]
                        + _someTile;
                    uVar4 = (short)DAT_TileMapState::instance.UnitLayer[iVar11];
                    while (iVar9 = (int)(short)uVar4, iVar9) {
                        _y = MACRO_CALL_MEMBER(
                            Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(iVar11);
                        _x = (int)(local_4 - _y) >> 0x1f;
                        if (((int)((local_4 - _y ^ _x) - _x) < 0x78)
                            && (this->entityArray[entityID].logicalState == 2)) {
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::processEntityDamageToUnit,
                                DAT_UnitsState::ptr)(iVar9, entityID, 1);
                        }
                        uVar4 = DAT_UnitsState::instance.units[iVar9].nextUnitOnTheSameTile;
                    }
                    _buildingID = _buildingID + 1;
                } while (_buildingID < 8);
                pPVar10 = DAT_EntityDefinedData::instance.EntityBlastTileOffsets;
                do {
                    _buildingID = MACRO_CALL_MEMBER(Map::TileMapState_Func::computeTileAlongAxisOffset,
                        DAT_TileMapState::ptr)(_someTile, pPVar10->xOffset, (uint)((int)(pPVar10->yOffset)));
                    uVar4 = (short)DAT_TileMapState::instance.UnitLayer[_buildingID];
                    while (iVar11 = (int)(short)uVar4, iVar11) {
                        _y = MACRO_CALL_MEMBER(
                            Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(_buildingID);
                        _x = (int)(local_4 - _y) >> 0x1f;
                        if (((int)((local_4 - _y ^ _x) - _x) < 0x78)
                            && (this->entityArray[entityID].logicalState == 2)) {
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::processEntityDamageToUnit,
                                DAT_UnitsState::ptr)(iVar11, entityID, 2);
                        }
                        uVar4 = DAT_UnitsState::instance.units[iVar11].nextUnitOnTheSameTile;
                    }
                    pPVar10 = pPVar10 + 1;
                } while ((int)pPVar10 < 0x5b6e08);
            }
            if ((((this->entityArray[entityID].entityType == Map::Entities::ET_FIRE)
                     && (_buildingID = this->entityArray[entityID].tile,
                         (DAT_TileMapState::instance.LogicLayer[_buildingID] & 8) != 0))
                    && (_buildingID = MACRO_CALL_MEMBER(Map::TileMapState_Func::getPitchDitchIDForTile,
                            DAT_TileMapState::ptr)(_buildingID),
                        _buildingID != 0))
                && (DAT_TileMapState::instance.pitchDitches[_buildingID].state == 1)) {
                MACRO_CALL(Map::Entities_Func::SetPlaceOnFire)((int)this->entityArray[entityID].owner,
                    (int)((int)(DAT_TileMapState::instance.pitchDitches[_buildingID].x * 8)),
                    (int)((int)(DAT_TileMapState::instance.pitchDitches[_buildingID].y * 8)),
                    (int)((int)((uint)DAT_TileMapState::instance
                            .HeightLayer[DAT_TileMapState::instance.pitchDitches[_buildingID].tile])),
                    3);
                DAT_TileMapState::instance.pitchDitches[_buildingID].state = 2;
            }
            _y = MACRO_CALL_MEMBER(Map::TileMapState_Func::returnSomeHeight, DAT_TileMapState::ptr)(
                _someTile, 0);
            _buildingID = (int)*(short*)((int)DAT_TileMapState::instance.BuildingLayer + _tile);
            if (((_buildingID)
                    && ((_buildingID = (int)(short)DAT_BuildingsState::instance.buildings[_buildingID].buildingType,
                        _buildingID == 0x3d || (_buildingID - 0x4aU < 5))))
                && ((this->entityArray[entityID].rng_1 & 4))) {
                _y = _y + 0x14;
            }
            sVar7 = this->entityArray[entityID].height;
            _buildingID = (int)sVar7;
            if ((int)_y <= _buildingID)
                goto LAB_00408150;
            EVar3 = this->entityArray[entityID].entityType;
            if (EVar3 == ((EntityType)0x20)) {
                if (((_buildingID < (int)(uint)DAT_TileMapState::instance.DefaultHeightLayer[_someTile])
                        && (this->entityArray[entityID].someCounter_OR_hitGround = 1,
                            (DAT_TileMapState::instance.LogicLayer[_someTile] & 0x10000100U) == 0))
                    && (((int)(uint)DAT_TileMapState::instance.DefaultHeightLayer[_someTile]
                            < this->entityArray[entityID].startingHeight_2 + 0x32
                        && ((MACRO_CALL(Map::Entities_Func::IgniteFireAtMiniTile_Convenience)(
                                 (int)this->entityArray[entityID].owner,
                                 (int)((int)(this->entityArray[entityID].microX)),
                                 (int)((int)(this->entityArray[entityID].microY)),
                                 (int)((int)(DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile]
                                     - 8)),
                                 2),
                            (DAT_TileMapState::instance.LogicLayer[_someTile] & 8) != 0
                                && (_buildingID
                                    = MACRO_CALL_MEMBER(Map::TileMapState_Func::getPitchDitchIDForTile,
                                        DAT_TileMapState::ptr)(_someTile),
                                    _buildingID != 0)))))) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)this->entityArray[entityID].xPosition, (int)((int)(this->entityArray[entityID].yPosition)),
                        DE::SHCDE::FX_IGNITE_PITCH);
                    MACRO_CALL(Map::Entities_Func::SetPlaceOnFire)((int)this->entityArray[entityID].owner,
                        (int)((int)(DAT_TileMapState::instance.pitchDitches[_buildingID].x * 8)),
                        (int)((int)(DAT_TileMapState::instance.pitchDitches[_buildingID].y * 8)),
                        (int)((int)((uint)DAT_TileMapState::instance
                                .HeightLayer[DAT_TileMapState::instance.pitchDitches[_buildingID].tile])),
                        3);
                    if (DAT_TileMapState::instance.pitchDitches[_buildingID].state == 1) {
                        DAT_TileMapState::instance.pitchDitches[_buildingID].state = 2;
                    }
                }
                goto LAB_00408150;
            }
            if (EVar3 == ((EntityType)0x1b)) {
                if (((_buildingID <= (int)(uint)DAT_TileMapState::instance.DefaultHeightLayer[_someTile])
                        && (this->entityArray[entityID].someCounter_OR_hitGround = 1,
                            (DAT_TileMapState::instance.LogicLayer[_someTile] & 0x40100001U) != 0))
                    && (this->entityArray[entityID].unitID_OR_seaGullID == 0)) {
                    iVar11 = (int)this->entityArray[entityID].microY;
                    iVar9 = (int)this->entityArray[entityID].microX;
                    _buildingID = DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] + 2;
                    MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity, local_10)(
                        1, 0, 0, iVar9, iVar11, _buildingID, iVar9, iVar11, _buildingID, ((EntityType)0x1f), 0);
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)this->entityArray[entityID].xPosition, (int)((int)(this->entityArray[entityID].yPosition)),
                        DE::SHCDE::FX_MED_PLOP);
                }
                goto LAB_00408150;
            }
            if (EVar3 == ((EntityType)8)) {
                _y = _buildingID - this->entityArray[entityID].targetZ;
                _x = (int)_y >> 0x1f;
                if (((int)((_y ^ _x) - _x) < 0x14) || (sVar7 < 9)) {
                    this->entityArray[entityID].someCounter_OR_hitGround = 1;
                }
                goto LAB_00408150;
            }
            if (((EVar3 == Map::Entities::ET_ARROW_AND_DEFAULT)
                    || (EVar3 == Map::Entities::ET_CROSSBOWARROW))
                || ((EVar3 == Map::Entities::ET_BALLISTA
                    || ((EVar3 == Map::Entities::ET_SLINGER
                        || (EVar3 == Map::Entities::ET_FIRETHROWER)))))) {
                if (this->entityArray[entityID].rng_2 == 2) {
                    _buildingID = 0;
                    do {
                        iVar11 = DAT_TileMapState::instance
                                     .directionTranslationMatrix[this->entityArray[entityID].yPosition][_buildingID]
                            + _someTile;
                        if (((DAT_TileMapState::instance.LogicLayer[iVar11] & 8))
                            && (iVar11 = MACRO_CALL_MEMBER(
                                    Map::TileMapState_Func::getPitchDitchIDForTile, DAT_TileMapState::ptr)(iVar11),
                                iVar11 != 0))
                            goto LAB_00407f73;
                        _buildingID = _buildingID + 1;
                    } while (_buildingID < 8);
                }
                _buildingID = (int)*(short*)((int)DAT_TileMapState::instance.BuildingLayer + _tile);
                if ((int)this->entityArray[entityID].travelledDistance
                    <= (int)this->entityArray[entityID].totalFlightDistance / 2)
                    goto LAB_00408150;
                _y = DAT_TileMapState::instance.LogicLayer[_someTile];
                if ((_y & 0x40100001)) {
                    iVar11 = (int)this->entityArray[entityID].microY;
                    iVar9 = (int)this->entityArray[entityID].microX;
                    _buildingID = DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] + 2;
                    MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity, local_10)(
                        1, 0, 0, iVar9, iVar11, _buildingID, iVar9, iVar11, _buildingID, ((EntityType)0x1f), 0);
                    sVar7 = this->entityArray[entityID].yPosition;
                    sVar5 = this->entityArray[entityID].xPosition;
                    this->entityArray[entityID].logicalState = 3;
                    local_c = 0;
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)sVar5, (int)((int)(sVar7)), DE::SHCDE::FX_LITTLE_PLOP);
                    goto LAB_00408150;
                }
                if ((!(_y & 0x10000100))
                    && ((!_buildingID
                        || ((((BVar6 = DAT_BuildingsState::instance.buildings[_buildingID].buildingType,
                                  BVar6 != Map::Buildings::BT_STONEKEEP && (BVar6 != Map::Buildings::BT_STRONGHOLD))
                                 && (BVar6 != Map::Buildings::BT_KEEPFOUR))
                            && (BVar6 != Map::Buildings::BT_KEEPFIVE)))))) {
                    if (!(_y & 8)) {
                        if (!_buildingID) {
                            this->entityArray[entityID].someCounter_OR_hitGround = 40;
                        } else {
                            _entityOriginUnitID = (int)this->entityArray[entityID].unitID_OR_seaGullID;
                            /*
                              if buildingtype is a tower (1 to 5)
                             */
                            BVar6 = DAT_BuildingsState::instance.buildings[_buildingID].buildingType;
                            if (((0x49 < (short)BVar6) && ((short)BVar6 < 0x4f))
                                || ((DAT_BuildingsState::instance.buildings[_buildingID].currentHealth == 0
                                    || ((_y & 0xf000000)))))
                                goto LAB_00408150;
                            if (DAT_UnitsState::instance.units[_entityOriginUnitID].unitType
                                == Map::Units::UT_S_FBALLISTA) {
                                MACRO_CALL_MEMBER(Map::TileMapState_Func::processDamageToBuilding,
                                    DAT_TileMapState::ptr)(_someTile,
                                    (uint)((int)((int)this->entityArray[entityID].xPosition)),
                                    (uint)((int)((int)this->entityArray[entityID].yPosition)), 10, 0,
                                    (int)((int)(this->entityArray[entityID].owner)), FALSE, _entityOriginUnitID);
                                _buildingHealth = MACRO_CALL_MEMBER(
                                    Map::TileMapState_Func::getNonFarmFieldBuildingHealthAtTileOr1000,
                                    DAT_TileMapState::ptr)(_someTile);
                                if (_buildingHealth < 50) {
                                    MACRO_CALL(Map::Entities_Func::SetPlaceOnFire)(
                                        (int)this->entityArray[entityID].owner,
                                        (int)((int)(this->entityArray[entityID].xPosition * 8)),
                                        (int)((int)(this->entityArray[entityID].yPosition * 8)),
                                        (int)((int)((uint)DAT_TileMapState::instance
                                                .HeightLayer[this->entityArray[entityID].tile])),
                                        3);
                                    this->entityArray[entityID].someCounter_OR_hitGround = 1;
                                    goto LAB_00408148;
                                }
                            } else {
                                if (this->entityArray[entityID].entityType == Map::Entities::ET_BALLISTA) {
                                    _playerID = this->entityArray[entityID].owner;
                                    _yPosition = this->entityArray[entityID].yPosition;
                                    _xPosition = this->entityArray[entityID].xPosition;
                                    _buildingID = 2;
                                } else {
                                    _playerID = this->entityArray[entityID].owner;
                                    _yPosition = this->entityArray[entityID].yPosition;
                                    _xPosition = this->entityArray[entityID].xPosition;
                                    _buildingID = 1;
                                }
                                MACRO_CALL_MEMBER(Map::TileMapState_Func::processDamageToBuilding,
                                    DAT_TileMapState::ptr)(_someTile, (uint)((int)((int)_xPosition)),
                                    (uint)((int)((int)_yPosition)), _buildingID, 0, (int)((int)(_playerID)), FALSE,
                                    _entityOriginUnitID);
                            }
                            this->entityArray[entityID].someCounter_OR_hitGround = 1;
                        }
                    } else {
                        if ((this->entityArray[entityID].rng_2 == 2)
                            && (iVar11 = MACRO_CALL_MEMBER(Map::TileMapState_Func::getPitchDitchIDForTile,
                                    DAT_TileMapState::ptr)(_someTile),
                                iVar11 != 0)) {
                        LAB_00407f73:
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                (int)this->entityArray[entityID].xPosition,
                                (int)((int)(this->entityArray[entityID].yPosition)),
                                DE::SHCDE::FX_IGNITE_PITCH);
                            MACRO_CALL(Map::Entities_Func::SetPlaceOnFire)(
                                (int)this->entityArray[entityID].owner,
                                (int)((int)(DAT_TileMapState::instance.pitchDitches[iVar11].x * 8)),
                                (int)((int)(DAT_TileMapState::instance.pitchDitches[iVar11].y * 8)),
                                (int)((int)((uint)DAT_TileMapState::instance
                                        .HeightLayer[DAT_TileMapState::instance.pitchDitches[iVar11].tile])),
                                3);
                            if (DAT_TileMapState::instance.pitchDitches[iVar11].state == 1) {
                                DAT_TileMapState::instance.pitchDitches[iVar11].state = 2;
                            }
                        }
                        this->entityArray[entityID].someCounter_OR_hitGround = 1;
                    }
                } else {
                    if (((this->entityArray[entityID].rotationFrameIndex < 3)
                            && (this->entityArray[entityID].startingAngle < 0))
                        || ((this->entityArray[entityID].hasDoneEffectUnk != 0
                            || (0 < this->entityArray[entityID].clearanceStepsRemaining))))
                        goto LAB_00408150;
                    MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::handleProjectileWallBounce, local_10)(
                        entityID);
                }
            } else if (((EVar3 == Map::Entities::ET_TREBUCHET)
                           || (EVar3 == Map::Entities::ET_CATAPULT))
                || (EVar3 == Map::Entities::ET_MANGONEL)) {
                this->entityArray[entityID].someCounter_OR_hitGround = 1;
                _y = DAT_TileMapState::instance.LogicLayer[_someTile];
                _damageUnk = 10;
                local_4 = _y & 0x40100001;
                _collateralDamageUnk = 10;
                if (local_4) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)this->entityArray[entityID].xPosition, (int)((int)(this->entityArray[entityID].yPosition)),
                        DE::SHCDE::FX_ROCK_SPLASH);
                }
                _x = _y & 0x100;
                if (((!_x) && (!(_y & 0x10000400)))
                    && (*(short*)((int)DAT_TileMapState::instance.BuildingLayer + _tile) == 0)) {
                    psVar2
                        = &DAT_UnitsState::instance.units[this->entityArray[entityID].unitID_OR_seaGullID].field98_0xd2;
                    *psVar2 = *psVar2 + 1;
                    if (!(_y & 0x4a5014b1)) {
                        local_4 = _x;
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)this->entityArray[entityID].xPosition,
                            (int)((int)(this->entityArray[entityID].yPosition)),
                            DE::SHCDE::FX_ROCK_HIT_GROUND);
                        _y = this->entityArray[entityID].rng_1 & 0x80000007;
                        this->entityArray[entityID].someCounter_OR_hitGround = 0x28;
                        local_c = 0;
                        if ((int)_y < 0) {
                            _y = (_y - 1 | 0xfffffff8) + 1;
                        }
                        if (_y != 0xfffffffb && -1 < (int)(_y + 5)) {
                            do {
                                _buildingID = (int)this->entityArray[entityID].microY;
                                iVar11 = (int)this->entityArray[entityID].microX;
                                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity,
                                    local_10)(2, 0, 0, iVar11, _buildingID,
                                    (int)((int)(DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile]
                                        + 2)),
                                    (int)SEC_RNG::instance.currentNumber2 % 0x50 + -0x28 + iVar11,
                                    ((int)SEC_RNG::instance.currentNumber2 >> 8) % 0x50 + -0x28 + _buildingID, 8,
                                    ((EntityType)0x1b), 0);
                                local_c = local_c + 1;
                                _y = this->entityArray[entityID].rng_1 & 0x80000007;
                                if ((int)_y < 0) {
                                    _y = (_y - 1 | 0xfffffff8) + 1;
                                }
                            } while (local_c < (int)(_y + 5));
                        }
                    } else if (local_4) {
                        _y = this->entityArray[entityID].rng_1 & 0x8000000f;
                        local_c = 0;
                        if ((int)_y < 0) {
                            _y = (_y - 1 | 0xfffffff0) + 1;
                        }
                        local_4 = 0;
                        if (_y != 0xfffffff6 && -1 < (int)(_y + 10)) {
                            do {
                                _buildingID = (int)this->entityArray[entityID].microY;
                                iVar11 = (int)this->entityArray[entityID].microX;
                                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity,
                                    local_10)(1, 0, 0, iVar11, _buildingID,
                                    (int)((int)(DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile]
                                        + 2)),
                                    (int)SEC_RNG::instance.currentNumber2 % 0x50 + -0x28 + iVar11,
                                    ((int)SEC_RNG::instance.currentNumber2 >> 8) % 0x50 + -0x28 + _buildingID, 8,
                                    ((EntityType)0x1b), 0);
                                local_c = local_c + 1;
                                _y = this->entityArray[entityID].rng_1 & 0x8000000f;
                                if ((int)_y < 0) {
                                    _y = (_y - 1 | 0xfffffff0) + 1;
                                }
                            } while (local_c < (int)(_y + 10));
                        }
                        iVar11 = (int)this->entityArray[entityID].microY;
                        iVar9 = (int)this->entityArray[entityID].microX;
                        _buildingID = DAT_TileMapState::instance.HeightLayer[this->entityArray[entityID].tile] + 2;
                        MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity, local_10)(
                            0, 0, 0, iVar9, iVar11, _buildingID, iVar9, iVar11, _buildingID, ((EntityType)0x1f), 0);
                    }
                } else {
                    local_4 = _x;
                    MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileImpactDebris, local_10)(
                        entityID);
                    _entityType_2 = this->entityArray[entityID].entityType;
                    if (_entityType_2 == 3) {
                        _damageUnk = 60;
                        _collateralDamageUnk = 0x1e;
                    } else if (_entityType_2 == 2) {
                        _damageUnk = 20;
                    } else if (_entityType_2 == 4) {
                        _damageUnk = 5;
                        _collateralDamageUnk = 0;
                    }
                    _buildingID = (int)*(short*)((int)DAT_TileMapState::instance.BuildingLayer + _tile);
                    if (!_buildingID) {
                        if ((local_4)
                            && (DAT_GameState::instance.mapAndTime.playerTeams[this->entityArray[entityID].owner]
                                == DAT_GameState::instance.mapAndTime
                                    .playerTeams[(DAT_TileMapState::instance.WallOwnerLayer[_someTile] & 7) + 1])) {
                            _damageUnk = 0;
                            _collateralDamageUnk = 0;
                        }
                    } else if (DAT_GameState::instance.mapAndTime
                                   .playerTeams[DAT_BuildingsState::instance.buildings[_buildingID].owner]
                        == DAT_GameState::instance.mapAndTime.playerTeams[this->entityArray[entityID].owner]) {
                        _damageUnk = 0;
                        _collateralDamageUnk = 0;
                    }
                    if (_entityType_2 == 4) {
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::processDamageToBuilding,
                            DAT_TileMapState::ptr)(_someTile, (uint)((int)((int)this->entityArray[entityID].xPosition)),
                            (uint)((int)((int)this->entityArray[entityID].yPosition)), (int)((int)(_damageUnk)), 0,
                            (int)((int)(-this->entityArray[entityID].owner)), FALSE,
                            (int)((int)(this->entityArray[entityID].unitID_OR_seaGullID)));
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::processEntityDamageToBuildingCollateral,
                            DAT_TileMapState::ptr)(_someTile, (uint)((int)((int)this->entityArray[entityID].xPosition)),
                            (uint)((int)((int)this->entityArray[entityID].yPosition)),
                            (int)((int)(_collateralDamageUnk)), (int)((int)(-this->entityArray[entityID].owner)), 0,
                            (int)((int)(this->entityArray[entityID].unitID_OR_seaGullID)));
                    } else {
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::processDamageToBuilding,
                            DAT_TileMapState::ptr)(_someTile, (uint)((int)((int)this->entityArray[entityID].xPosition)),
                            (uint)((int)((int)this->entityArray[entityID].yPosition)), (int)((int)(_damageUnk)), 0,
                            (int)((int)(this->entityArray[entityID].owner)), FALSE,
                            (int)((int)(this->entityArray[entityID].unitID_OR_seaGullID)));
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::processEntityDamageToBuildingCollateralThunk,
                            DAT_TileMapState::ptr)(_someTile, (uint)((int)((int)this->entityArray[entityID].xPosition)),
                            (uint)((int)((int)this->entityArray[entityID].yPosition)),
                            (int)((int)(_collateralDamageUnk)), (int)((int)(this->entityArray[entityID].owner)), 0);
                    }
                    /*
                      woodhit_02.wav ?
                     */
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)this->entityArray[entityID].xPosition, (int)((int)(this->entityArray[entityID].yPosition)),
                        DE::SHCDE::FX_ROCK_HIT_WALL);
                }
            } else {
                if (EVar3 != Map::Entities::ET_COW_FLYING)
                    goto LAB_00408150;
            LAB_004079b4:
                if (this->entityArray[entityID].hasDoneEffectUnk == 0) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)this->entityArray[entityID].xPosition, (int)((int)(this->entityArray[entityID].yPosition)),
                        DE::SHCDE::FX_COW_SPLAT);
                    this->entityArray[entityID].hasDoneEffectUnk = 1;
                    if (!(DAT_TileMapState::instance.LogicLayer[_someTile] & 0x401000b1U)) {
                        this->entityArray[entityID].someCounter_OR_hitGround = 0x28;
                        DAT_GameCore::instance.cowPoisonTrackerUnk = DAT_GameCore::instance.cowPoisonTrackerUnk + 500;
                        _randomNumber = (int)SEC_RNG::instance.currentNumber2 % 5 + -2;
                        if (_randomNumber < 8) {
                            _randomNumber2 = 8 - _randomNumber;
                            do {
                                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity,
                                    this)(0, (undefined4)((int)((int)this->entityArray[entityID].owner)), 0,
                                    (int)((int)(this->entityArray[entityID].microX)),
                                    (int)((int)(this->entityArray[entityID].microY)),
                                    (int)((int)(this->entityArray[entityID].height)), 0, 0, 0,
                                    Map::Entities::ET_COW_POISON_CLOUD, 0);
                                _randomNumber2 = _randomNumber2 + -1;
                            } while (_randomNumber2);
                        }
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)this->entityArray[entityID].xPosition,
                            (int)((int)(this->entityArray[entityID].yPosition)), DE::SHCDE::FX_FLIES);
                    } else {
                        this->entityArray[entityID].someCounter_OR_hitGround = 1;
                    }
                }
            }
        LAB_00408148:
            local_c = 0;
        LAB_00408150:
            if (entityID) {
                if (entityID < 25) {
                    this->entityArray[entityID].nextEntityOnThisTileByID
                        = (ushort)(byte)DAT_TileMapState::instance.EntityLayerLT25[_someTile];
                    DAT_TileMapState::instance.EntityLayerLT25[_someTile] = (char)entityID;
                    return (undefined4)(local_c);
                }
                this->entityArray[entityID].nextEntityOnThisTileByID
                    = *(short*)((int)DAT_TileMapState::instance.EntityLayer + _tile);
                *(short*)((int)DAT_TileMapState::instance.EntityLayer + _tile) = (short)entityID;
            }
            return (undefined4)(local_c);
        }

    }
}
}
