#include "../UnitsState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Entities/EntityTypeShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::DE::SHCDE::eSFX;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Entities::EntityType;
        using OpenSHC::Map::Entities::EntityTypeShort;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00531920
        BOOLEnum UnitsState::processEntityDamageToUnit(int unitID, int entityID, int tileDistance)

        {
            /*
              removes health from a unit hit by an entity: projectiles of every kind, and the
               disease cloud of a poisoned cow
             */

            int const _tribeID = this->units[unitID].tribeID;
            BOOLEnum _unitIsSiegeEngine = FALSE;
            BOOLEnum _siegeProjectile = FALSE;
            BOOLEnum _usesFemaleDeathScream = FALSE;
            UnitTypeShort const _unitType = this->units[unitID].unitType;
            int const _victimType = _unitType;
            int const _shooterID = DAT_EntityState::instance.entityArray[entityID].unitID_OR_seaGullID;
            if (unitID <= 0) {
                return FALSE;
            }
            if (_shooterID == unitID) {
                return FALSE;
            }
            EntityTypeShort const _entityType = DAT_EntityState::instance.entityArray[entityID].entityType;
            if (_entityType == OpenSHC::Map::Entities::ET_FIRE) {
                return FALSE;
            }
            if (_entityType == OpenSHC::Map::Entities::ET_FIRETHROWER) {
                return FALSE;
            }
            if (_entityType == OpenSHC::Map::Entities::ET_COW_POISON_CLOUD) {
                /*
                  if the unit is dead, don't bother
                 */

                if (this->units[unitID].dying != 0) {
                    return FALSE;
                }
                int const _unitTile = DAT_UnitsState::instance.units[unitID].tile;
                /*
                  if the tile that the unit is on has some properties, don't bother either.
                 */

                if ((DAT_TileMapState::instance.LogicLayer[_unitTile] & 0x10000100U) != 0) {
                    return FALSE;
                }
                /*
                  if the unit is standing on a building, and that building is a defensive
                   building, return 0
                 */

                if (DAT_TileMapState::instance.BuildingLayer[_unitTile] != 0) {
                    switch (DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.BuildingLayer[_unitTile]]
                            .buildingType) {
                    case OpenSHC::Map::Buildings::BT_MANORHOUSE:
                    case OpenSHC::Map::Buildings::BT_STONEKEEP:
                    case OpenSHC::Map::Buildings::BT_STRONGHOLD:
                    case OpenSHC::Map::Buildings::BT_KEEPFOUR:
                    case OpenSHC::Map::Buildings::BT_KEEPFIVE:
                    case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                    case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                    case OpenSHC::Map::Buildings::BT_WOODGATE1:
                    case OpenSHC::Map::Buildings::BT_TOWER1:
                    case OpenSHC::Map::Buildings::BT_TOWER2:
                    case OpenSHC::Map::Buildings::BT_TOWER3:
                    case OpenSHC::Map::Buildings::BT_TOWER4:
                    case OpenSHC::Map::Buildings::BT_TOWER5:
                        return FALSE;
                    }
                }
                /*
                  if the unit is of a type that is invulnerable to disease clouds, return 0
                 */

                if (DAT_UnitPropertiesDefinedData::instance
                        .UnitClimbStateFlags[0][DAT_UnitsState::instance.units[unitID].unitType]
                    == 0) {
                    return FALSE;
                }
                int _cowDiseaseDamage;
                if (tileDistance == 0) {
                    _cowDiseaseDamage = 400;
                } else {
                    _cowDiseaseDamage = tileDistance == 1 ? 200 : 150;
                }
                int const _healerCount = DAT_GameState::instance.playerDataArray[this->units[unitID].owner].healerCount;
                if (_healerCount >= 3) {
                    /* * 40 */
                    _cowDiseaseDamage = (_cowDiseaseDamage * 40) / 100;
                } else if (_healerCount == 2) {
                    /* * 60 */
                    _cowDiseaseDamage = (_cowDiseaseDamage * 60) / 100;
                } else if (_healerCount == 1) {
                    /* * 80 */
                    _cowDiseaseDamage = (_cowDiseaseDamage * 80) / 100;
                }
                this->units[unitID].health = this->units[unitID].health - _cowDiseaseDamage;
                if (this->units[unitID].health <= 0) {
                    this->units[unitID].health = 0;
                    this->units[unitID].dying = 1;
                    this->units[unitID].animationCycleNumber = 0;
                    this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_STONE_DEATH_02;
                    this->units[unitID].tunnelerFinishedDigging = 1;
                }
                int const _healthPercentage
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHealthPercentage,
                        DAT_DirectionAlgorithmState::ptr)(this->units[unitID].health, this->units[unitID].maxHealth);
                this->units[unitID].healthPercentage = _healthPercentage;
                this->units[unitID].healthbar = (short)_healthPercentage / 10;
                return FALSE;
            }
            int _unitHeight;
            if (_unitType == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                _unitHeight = tileDistance == 0 ? 80 : 40;
                _unitIsSiegeEngine = TRUE;
            } else if (_unitType == OpenSHC::Map::Units::UT_S_TOWER) {
                _unitHeight = 80;
                _unitIsSiegeEngine = TRUE;
            } else if (_unitType == OpenSHC::Map::Units::UT_S_CATAPULT) {
                _unitHeight = 50;
                _unitIsSiegeEngine = TRUE;
            } else if (_unitType == OpenSHC::Map::Units::UT_S_SHIELD) {
                _unitHeight = 90;
                _unitIsSiegeEngine = TRUE;
            } else if (_unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                _unitHeight = 40;
                _unitIsSiegeEngine = TRUE;
            } else if (_unitType == OpenSHC::Map::Units::UT_S_MANGONEL) {
                _unitHeight = 70;
                _unitIsSiegeEngine = TRUE;
            } else {
                if (_unitType == OpenSHC::Map::Units::UT_S_BALLISTA
                    || _unitType == OpenSHC::Map::Units::UT_S_FBALLISTA) {
                    _unitIsSiegeEngine = TRUE;
                }
                _unitHeight = 42;
            }
            if (_entityType == OpenSHC::Map::Entities::ET_TREBUCHET
                || _entityType == OpenSHC::Map::Entities::ET_CATAPULT
                || _entityType == OpenSHC::Map::Entities::ET_MANGONEL
                || _entityType == OpenSHC::Map::Entities::ET_BALLISTA
                || _entityType == OpenSHC::Map::Entities::ET_FIREBALLISTA) {
                _siegeProjectile = TRUE;
            }
            int const _unitPlayerID = this->units[unitID].owner;
            short const _entityPlayerID = DAT_EntityState::instance.entityArray[entityID].owner;
            if (DAT_GameState::instance.mapAndTime.playerTeams[_entityPlayerID]
                == DAT_GameState::instance.mapAndTime.playerTeams[_unitPlayerID]) {
                /*
                  friendly fire only hurts from siege projectiles, and not from every kind
                 */

                if (!_siegeProjectile) {
                    return FALSE;
                }
                EntityTypeShort const _projectileType = DAT_EntityState::instance.entityArray[entityID].entityType;
                if (_projectileType == OpenSHC::Map::Entities::ET_BALLISTA) {
                    return FALSE;
                }
                if (_projectileType == OpenSHC::Map::Entities::ET_MANGONEL
                    && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_entityPlayerID] == -1) {
                    return FALSE;
                }
                if (_projectileType == OpenSHC::Map::Entities::ET_FIREBALLISTA) {
                    return FALSE;
                }
                if (_unitType == OpenSHC::Map::Units::UT_S_SHIELD) {
                    return FALSE;
                }
                if (_unitType == OpenSHC::Map::Units::UT_S_TOWER) {
                    return FALSE;
                }
                if (_unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                    return FALSE;
                }
            }
            if (this->units[unitID].dying != 0) {
                return FALSE;
            }
            int const _unitAltitude = this->units[unitID].terrainOrClimbHeight + this->units[unitID].buildingHeight;
            int const _entityHeight = DAT_EntityState::instance.entityArray[entityID].height;
            if (_unitAltitude > _entityHeight) {
                return FALSE;
            }
            if (_unitAltitude + _unitHeight < _entityHeight) {
                return FALSE;
            }
            if (_entityPlayerID != 0 && _entityPlayerID != this->units[unitID].owner) {
                this->units[unitID].lastEncounteredEnemyPlayerID = _entityPlayerID;
                this->units[unitID].lastEncounteredEnemyUnitIDUnk
                    = DAT_EntityState::instance.entityArray[entityID].unitID_OR_seaGullID;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && _unitPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXWeAreUnderAttack, DAT_SFXState::ptr)();
            }
            EntityTypeShort const _projectileType = DAT_EntityState::instance.entityArray[entityID].entityType;
            int _damage;
            if (!_siegeProjectile) {
                if (_projectileType == OpenSHC::Map::Entities::ET_ARROW_AND_DEFAULT) {
                    UnitTypeShort const _targetUnitType = this->units[unitID].unitType;
                    _damage = DAT_UnitPropertiesDefinedData::instance.ARROW_DAMAGE[_targetUnitType];
                    if (_targetUnitType == OpenSHC::Map::Units::UT_E_LADDER
                        && this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_STATE_3Unk) {
                        _damage = _damage / 4;
                    }
                } else if (_projectileType == OpenSHC::Map::Entities::ET_SLINGER) {
                    _damage = DAT_UnitPropertiesDefinedData::instance.STONE_DAMAGE[this->units[unitID].unitType];
                } else {
                    _damage = DAT_UnitPropertiesDefinedData::instance.BOLT_DAMAGE[this->units[unitID].unitType];
                }
                _damage = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::computeDamageFearFactorBonus, this)(
                    _damage, DAT_EntityState::instance.entityArray[entityID].owner);
                if (_unitIsSiegeEngine) {
                    _damage = _damage / 2;
                }
                if (this->units[unitID].isStalked == 0) {
                    DAT_GameCore::instance.cowPoisonTrackerUnk = DAT_GameCore::instance.cowPoisonTrackerUnk + 50;
                }
            } else {
                if (_projectileType == OpenSHC::Map::Entities::ET_COW_FLYING) {
                    if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_LORD) {
                        _damage = 50;
                    } else {
                        /* flying cow: 50 against a shield, 500 against anything else */
                        _damage = this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_SHIELD ? 50 : 500;
                    }
                } else if (_projectileType == OpenSHC::Map::Entities::ET_MANGONEL) {
                    UnitTypeShort const _targetUnitType = this->units[unitID].unitType;
                    if (_targetUnitType == OpenSHC::Map::Units::UT_LORD) {
                        _damage = 50;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_SHIELD) {
                        _damage = 1500;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_BALLISTA) {
                        _damage = 1000;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_FBALLISTA) {
                        _damage = 1000;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_MANGONEL) {
                        _damage = 500;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_CATAPULT) {
                        _damage = 5000;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                        _damage = 5000;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                        _damage = 10000;
                    } else {
                        _damage = _targetUnitType == OpenSHC::Map::Units::UT_S_TOWER ? 10000 : 30000;
                    }
                } else if (_projectileType == OpenSHC::Map::Entities::ET_BALLISTA) {
                    /*
                      tower ballista and fire ballista damage
                     */

                    UnitTypeShort const _targetUnitType = this->units[unitID].unitType;
                    if (_targetUnitType == OpenSHC::Map::Units::UT_LORD) {
                        _damage = 50;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_SHIELD) {
                        _damage = 500;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_BALLISTA) {
                        _damage = 2000;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_MANGONEL) {
                        _damage = 2000;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_FBALLISTA) {
                        _damage = 2000;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_CATAPULT) {
                        _damage = 2500;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                        _damage = 4000;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                        _damage = 20000;
                    } else {
                        _damage = _targetUnitType == OpenSHC::Map::Units::UT_S_TOWER ? 20000 : 10000;
                    }
                    if (DAT_EntityState::instance.entityArray[entityID].field_0xd0 != 0) {
                        /*
                          if is fire ballista
                         */

                        _damage = (_damage * 2) / 3;
                    }
                } else {
                    /* every other siege projectile: 50 against the lord, 30000 otherwise */
                    _damage = this->units[unitID].unitType == OpenSHC::Map::Units::UT_LORD ? 50 : 30000;
                }
                DAT_GameCore::instance.cowPoisonTrackerUnk = DAT_GameCore::instance.cowPoisonTrackerUnk + 50;
                if (_damage > 20000) {
                    this->units[unitID].dying = 1;
                    if (_tribeID > 0) {
                        DAT_TribesState::instance.tribes[_tribeID].predatorNearby = 1;
                    }
                    this->units[unitID].animationCycleNumber = 0;
                    this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
                    this->units[unitID].tunnelerFinishedDigging = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_SPLAT);
                    this->units[unitID].health = 0;
                    return TRUE;
                }
            }
            if (DAT_EntityState::instance.entityArray[entityID].startingHeight
                < DAT_EntityState::instance.entityArray[entityID].targetZ - 30) {
                /* shot down from above */
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_E_ENGINEER
                    && this->units[unitID].resourceToDeposit != 0) {
                    _damage = _damage / 20;
                } else if (_projectileType == OpenSHC::Map::Entities::ET_BALLISTA) {
                    _damage = _damage / 2;
                } else {
                    _damage = _damage / 3;
                }
            }
            this->units[unitID].health = this->units[unitID].health - _damage;
            if (this->units[unitID].health <= 0) {
                this->units[unitID].health = 0;
            }
            if (_shooterID != 0) {
                if (this->units[unitID].field_0xd0 < 1000) {
                    this->units[unitID].field_0xd0 = this->units[unitID].field_0xd0 + 200;
                }
                /* the tribe remembers the last ten units that shot at it */
                DAT_TribesState::instance.tribes[_tribeID].someUnitArrayIndex
                    = DAT_TribesState::instance.tribes[_tribeID].someUnitArrayIndex + 1;
                DAT_TribesState::instance.tribes[_tribeID].countdown = 100;
                if (DAT_TribesState::instance.tribes[_tribeID].someUnitArrayIndex >= 10) {
                    DAT_TribesState::instance.tribes[_tribeID].someUnitArrayIndex = 0;
                }
                DAT_TribesState::instance.tribes[_tribeID]
                    .someUnitArray[DAT_TribesState::instance.tribes[_tribeID].someUnitArrayIndex] = _shooterID;
                DAT_TribesState::instance.tribes[_tribeID]
                    .someUnitUIDArray[DAT_TribesState::instance.tribes[_tribeID].someUnitArrayIndex]
                    = this->units[_shooterID].uid;
            }
            int const _unitHealth = this->units[unitID].health;
            int const _healthPercentage
                = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHealthPercentage,
                    DAT_DirectionAlgorithmState::ptr)(_unitHealth, this->units[unitID].maxHealth);
            this->units[unitID].healthPercentage = _healthPercentage;
            this->units[unitID].healthbar = (short)_healthPercentage / 10;
            if (_victimType == OpenSHC::Map::Units::UT_BREWER || _victimType == OpenSHC::Map::Units::UT_TANNER
                || _victimType == OpenSHC::Map::Units::UT_LADY || _victimType == OpenSHC::Map::Units::UT_MOTHER
                || (_victimType == OpenSHC::Map::Units::UT_CHILD && this->units[unitID].spriteID == 129)) {
                _usesFemaleDeathScream = TRUE;
            }
            BOOLEnum _shotBySlinger = FALSE;
            if (this->units[_shooterID].unitType == OpenSHC::Map::Units::UT_A_SLINGER) {
                _shotBySlinger = TRUE;
            }
            if (_unitHealth <= 0 && this->units[unitID].dying == 0) {
                this->units[unitID].dying = 1;
                if (_tribeID > 0) {
                    DAT_TribesState::instance.tribes[_tribeID].predatorNearby = 1;
                }
                this->units[unitID].animationCycleNumber = 0;
                EntityTypeShort const _killingType = DAT_EntityState::instance.entityArray[entityID].entityType;
                if (_killingType == OpenSHC::Map::Entities::ET_COW_FLYING) {
                    this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
                } else {
                    this->units[unitID].state.generic = _killingType == OpenSHC::Map::Entities::ET_SLINGER
                        ? OpenSHC::Map::Units::States::US_STONE_DEATH_01
                        : OpenSHC::Map::Units::States::US_DEATH_01;
                }
                this->units[unitID].tunnelerFinishedDigging = 1;
                if (this->units[unitID].isStalked != 0) {
                    if (!_shotBySlinger) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_ARROW_HIT_ANIMAL);
                    } else if (_shotBySlinger == TRUE) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_HIT_SLINGSTONE);
                    }
                    return TRUE;
                }
                switch (this->units[unitID].unitType) {
                case OpenSHC::Map::Units::UT_S_SHIELD:
                    if (this->units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 != 0
                        && !_shotBySlinger) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_DEATH_ARROW);
                        return TRUE;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_SIEGE_DIE);
                    return TRUE;
                case OpenSHC::Map::Units::UT_S_CATAPULT:
                case OpenSHC::Map::Units::UT_S_MANGONEL:
                case OpenSHC::Map::Units::UT_S_TOWER:
                case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                case OpenSHC::Map::Units::UT_S_BALLISTA:
                case OpenSHC::Map::Units::UT_S_FBALLISTA:
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_SIEGE_DIE);
                    return TRUE;
                case OpenSHC::Map::Units::UT_S_TREBUCHET:
                    /* the trebuchet also gets the crew's death scream below */
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_TR_DIE);
                    break;
                }
                if (_usesFemaleDeathScream) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_GIRL_DIE);
                    if (!_shotBySlinger) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_ARROW_HIT);
                    } else if (_shotBySlinger == TRUE) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_HIT_SLINGSTONE);
                    }
                } else if (!_shotBySlinger) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_DEATH_ARROW);
                } else if (_shotBySlinger == TRUE) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_DEATH_SLINGSTONE);
                }
                return TRUE;
            }
            if (this->units[unitID].isStalked != 0) {
                if (!_shotBySlinger) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_ARROW_HIT_ANIMAL);
                } else if (_shotBySlinger == TRUE) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_HIT_SLINGSTONE);
                }
                return TRUE;
            }
            switch (this->units[unitID].unitType) {
            case OpenSHC::Map::Units::UT_S_SHIELD:
                if (this->units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 <= 0) {
                    return TRUE;
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT2);
                return TRUE;
            case OpenSHC::Map::Units::UT_S_CATAPULT:
            case OpenSHC::Map::Units::UT_S_TREBUCHET:
            case OpenSHC::Map::Units::UT_S_MANGONEL:
            case OpenSHC::Map::Units::UT_S_TOWER:
            case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
            case OpenSHC::Map::Units::UT_S_BALLISTA:
            case OpenSHC::Map::Units::UT_S_FBALLISTA:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_WOOD_HIT);
                return TRUE;
            case OpenSHC::Map::Units::UT_LORD:
                return TRUE;
            }
            /* one of eight body-hit sounds, fixed per unit */
            uint const _hitSound = this->units[unitID].fixedRng & 7;
            if (_hitSound == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT);
            } else if (_hitSound == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT2);
            } else if (_hitSound == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT3);
            } else if (_hitSound == 3) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT4);
            } else if (_hitSound == 4) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT5);
            } else if (_hitSound == 5) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT6);
            } else if (_hitSound == 6) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT7);
            } else if (_hitSound == 7) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT8);
            }
            return TRUE;
        }

    }
}
}
