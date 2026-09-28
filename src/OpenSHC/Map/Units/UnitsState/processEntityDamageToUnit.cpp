#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
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
            int _cowDiseaseDamage;
            int _unitHeight;
            eSFX sfxOffsetInArray;
            UnitTypeShort _entityType_2;

            /*
              unclear what it does, but this function removes health from a unit, ranged
               and melee
             */

            int _unknown = (int)this->units[unitID].tribeID;
            int _unitIsSiegeEngine = 0;
            int _siegeProjectile = 0;
            int _usesFemaleDeathScream = 0;
            UnitTypeShort _unitType = this->units[unitID].unitType;
            short _entityShootingUnitID = DAT_EntityState::instance.entityArray[entityID].unitID_OR_seaGullID;
            int _entityShootingUnitID_2 = (int)_entityShootingUnitID;
            if (unitID <= 0) {
                return FALSE;
            }
            if (_entityShootingUnitID_2 == unitID) {
                return FALSE;
            }
            EntityTypeShort _entityType = DAT_EntityState::instance.entityArray[entityID].entityType;
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
                _entityShootingUnitID_2 = DAT_UnitsState::instance.units[unitID].tile;
                /*
                  if the tile that the unit is on has some properties, don't bother either.
                 */

                if ((DAT_TileMapState::instance.LogicLayer[_entityShootingUnitID_2] & 0x10000100U) != 0) {
                    return FALSE;
                }
                /*
                  if the unit is standing on a building, and that building is a defensive
                   building, return 0
                 */

                if (DAT_TileMapState::instance.BuildingLayer[_entityShootingUnitID_2] != 0) {
                    switch (DAT_BuildingsState::instance
                            .buildings[DAT_TileMapState::instance.BuildingLayer[_entityShootingUnitID_2]]
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

                if (DAT_UnitPropertiesDefinedData::instance.UnitClimbStateFlags[0][(short)this->units[unitID].unitType]
                    == 0) {
                    return FALSE;
                }
                if (tileDistance == 0) {
                    _cowDiseaseDamage = 400;
                } else {
                    _cowDiseaseDamage = tileDistance == 1 ? 200 : 150;
                }
                int _healerCount = DAT_GameState::instance.playerDataArray[this->units[unitID].owner].healerCount;
                if (_healerCount >= 3) {
                    /* * 40 */
                    _cowDiseaseDamage = (_cowDiseaseDamage * 0x28) / 100;
                } else if (_healerCount == 2) {
                    /* * 60 */
                    _cowDiseaseDamage = (_cowDiseaseDamage * 0x3c) / 100;
                } else if (_healerCount == 1) {
                    /* * 80 */
                    _cowDiseaseDamage = (_cowDiseaseDamage * 0x50) / 100;
                }
                this->units[unitID].health = this->units[unitID].health - _cowDiseaseDamage;
                if (this->units[unitID].health < 1) {
                    this->units[unitID].health = 0;
                    this->units[unitID].dying = 1;
                    this->units[unitID].animationCycleNumber = 0;
                    this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_STONE_DEATH_02;
                    this->units[unitID].tunnelerFinishedDigging = 1;
                }
                int _healthPercentage
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHealthPercentage,
                        DAT_DirectionAlgorithmState::ptr)(this->units[unitID].health, this->units[unitID].maxHealth);
                this->units[unitID].healthPercentage = (short)_healthPercentage;
                this->units[unitID].healthbar = (short)_healthPercentage / 10;
                return FALSE;
            }
            if (_unitType == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                _unitHeight = tileDistance == 0 ? 0x50 : 0x28;
                _unitIsSiegeEngine = 1;
            } else if (_unitType == OpenSHC::Map::Units::UT_S_TOWER) {
                _unitHeight = 0x50;
                _unitIsSiegeEngine = 1;
            } else if (_unitType == OpenSHC::Map::Units::UT_S_CATAPULT) {
                _unitHeight = 0x32;
                _unitIsSiegeEngine = 1;
            } else if (_unitType == OpenSHC::Map::Units::UT_S_SHIELD) {
                _unitHeight = 0x5a;
                _unitIsSiegeEngine = 1;
            } else if (_unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                _unitHeight = 0x28;
                _unitIsSiegeEngine = 1;
            } else if (_unitType == OpenSHC::Map::Units::UT_S_MANGONEL) {
                _unitHeight = 0x46;
                _unitIsSiegeEngine = 1;
            } else {
                if ((_unitType == OpenSHC::Map::Units::UT_S_BALLISTA)
                    || (_unitType == OpenSHC::Map::Units::UT_S_FBALLISTA)) {
                    _unitIsSiegeEngine = 1;
                }
                _unitHeight = 42;
            }
            if (_entityType == OpenSHC::Map::Entities::ET_TREBUCHET
                || _entityType == OpenSHC::Map::Entities::ET_CATAPULT
                || _entityType == OpenSHC::Map::Entities::ET_MANGONEL
                || _entityType == OpenSHC::Map::Entities::ET_BALLISTA
                || _entityType == OpenSHC::Map::Entities::ET_FIREBALLISTA) {
                _siegeProjectile = 1;
            }
            short _unitPlayerID = this->units[unitID].owner;
            short _entityPlayerID = DAT_EntityState::instance.entityArray[entityID].owner;
            if (((DAT_GameState::instance.mapAndTime.playerTeams[_entityPlayerID]
                     == DAT_GameState::instance.mapAndTime.playerTeams[_unitPlayerID])
                    && ((
                        ((!_siegeProjectile
                             || (_entityType = DAT_EntityState::instance.entityArray[entityID].entityType,
                                 _entityType == OpenSHC::Map::Entities::ET_BALLISTA))
                            || ((_entityType == OpenSHC::Map::Entities::ET_MANGONEL
                                && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_entityPlayerID] == -1))))
                        || ((((_entityType == OpenSHC::Map::Entities::ET_FIREBALLISTA
                                  || (_unitType == OpenSHC::Map::Units::UT_S_SHIELD))
                                 || (_unitType == OpenSHC::Map::Units::UT_S_TOWER))
                            || (_unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM))))))
                || this->units[unitID].dying != 0) {
                return FALSE;
            }
            int _unitAltitude = (int)this->units[unitID].terrainOrClimbHeight + (int)this->units[unitID].buildingHeight;
            int _damage = (int)DAT_EntityState::instance.entityArray[entityID].height;
            if (_damage < _unitAltitude) {
                return FALSE;
            }
            if (_unitAltitude + _unitHeight < _damage) {
                return FALSE;
            }
            if ((_entityPlayerID != 0) && (_entityPlayerID != this->units[unitID].owner)) {
                this->units[unitID].lastEncounteredEnemyPlayerID = _entityPlayerID;
                this->units[unitID].lastEncounteredEnemyUnitIDUnk
                    = DAT_EntityState::instance.entityArray[entityID].unitID_OR_seaGullID;
            }
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                && (_unitPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID)) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXWeAreUnderAttack, DAT_SFXState::ptr)();
            }
            int _unitYPosition_2 = this->units[unitID].y;
            int _unitXPosition_2 = this->units[unitID].x;
            _entityType = DAT_EntityState::instance.entityArray[entityID].entityType;
            if (_siegeProjectile) {
                if (_entityType == OpenSHC::Map::Entities::ET_COW_FLYING) {
                    _entityType_2 = this->units[unitID].unitType;
                    if (_entityType_2 == OpenSHC::Map::Units::UT_LORD) {
                        _damage = 0x32;
                    } else {
                        /* flying cow: 50 against a shield, 500 against anything else */
                        _damage = _entityType_2 == OpenSHC::Map::Units::UT_S_SHIELD ? 0x32 : 0x1f4;
                    }
                } else if (_entityType == OpenSHC::Map::Entities::ET_MANGONEL) {
                    /*
                      mangonel damage
                     */

                    _entityType_2 = this->units[unitID].unitType;
                    if (_entityType_2 == OpenSHC::Map::Units::UT_LORD) {
                        _damage = 0x32;
                    } else if (_entityType_2 == OpenSHC::Map::Units::UT_S_SHIELD) {
                        _damage = 1500;
                    } else if (_entityType_2 == OpenSHC::Map::Units::UT_S_BALLISTA) {
                        _damage = 1000;
                    } else if (_entityType_2 == OpenSHC::Map::Units::UT_S_FBALLISTA) {
                        _damage = 1000;
                    } else if (_entityType_2 == OpenSHC::Map::Units::UT_S_MANGONEL) {
                        _damage = 500;
                    } else if (_entityType_2 == OpenSHC::Map::Units::UT_S_CATAPULT) {
                        _damage = 5000;
                    } else if (_entityType_2 == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                        _damage = 5000;
                    } else if (_entityType_2 == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                        _damage = 10000;
                    } else {
                        _damage = _entityType_2 == OpenSHC::Map::Units::UT_S_TOWER ? 10000 : 30000;
                    }
                } else {
                    if (_entityType != OpenSHC::Map::Entities::ET_BALLISTA) {
                        /* every other siege projectile: 50 against the lord, 30000 otherwise */
                        _damage = this->units[unitID].unitType == OpenSHC::Map::Units::UT_LORD ? 0x32 : 0x7530;
                    }
                    /*
                      tower ballista and fire ballista damage
                     */

                    UnitTypeShort _targetUnitType = this->units[unitID].unitType;
                    if (_targetUnitType == OpenSHC::Map::Units::UT_LORD) {
                        _damage = 0x32;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_SHIELD) {
                        _damage = 500;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_BALLISTA) {
                        _damage = 2000;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_MANGONEL) {
                        _damage = 2000;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_FBALLISTA) {
                        _damage = 2000;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_CATAPULT) {
                        _damage = 0x9c4;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                        _damage = 4000;
                    } else if (_targetUnitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                        _damage = 20000;
                    } else {
                        /*
                          10000 if not siege tower else 20000
                         */

                        _damage = _targetUnitType == OpenSHC::Map::Units::UT_S_TOWER ? 20000 : 10000;
                    }
                    if (DAT_EntityState::instance.entityArray[entityID].field90_0xd0 != 0) {
                        /*
                          if is fire ballista
                         */

                        _damage = (_damage * 2) / 3;
                    }
                }
                DAT_GameCore::instance.cowPoisonTrackerUnk = DAT_GameCore::instance.cowPoisonTrackerUnk + 0x32;
                if (20000 < _damage) {
                    this->units[unitID].dying = 1;
                    if (0 < _unknown) {
                        DAT_TribesState::instance.tribes[_unknown].field133_0x278 = 1;
                    }
                    short _unitYPosition = this->units[unitID].y;
                    short _unitXPosition = this->units[unitID].x;
                    this->units[unitID].animationCycleNumber = 0;
                    this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
                    this->units[unitID].tunnelerFinishedDigging = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)_unitXPosition, (int)(_unitYPosition), OpenSHC::DE::SHCDE::FX_SPLAT);
                    this->units[unitID].health = 0;
                    return TRUE;
                }
            } else {
                if (_entityType == OpenSHC::Map::Entities::ET_ARROW_AND_DEFAULT) {
                    _entityType_2 = this->units[unitID].unitType;
                    _damage = DAT_UnitPropertiesDefinedData::instance.ARROW_DAMAGE[(short)_entityType_2];
                    if (_entityType_2 == OpenSHC::Map::Units::UT_E_LADDER
                        && this->units[unitID].state.generic == (UnitState)3) {
                        /* the compiler's biased shift matches here where a plain /4 does not */
                        _damage = (int)(_damage + (_damage >> 0x1f & 3U)) >> 2;
                    }
                } else if (_entityType == OpenSHC::Map::Entities::ET_SLINGER) {
                    _damage = DAT_UnitPropertiesDefinedData::instance.STONE_DAMAGE[(short)this->units[unitID].unitType];
                } else {
                    _damage = DAT_UnitPropertiesDefinedData::instance.BOLT_DAMAGE[(short)this->units[unitID].unitType];
                }
                _damage = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::computeDamageFearFactorBonus, this)(
                    _damage, (int)(DAT_EntityState::instance.entityArray[entityID].owner));
                if (_unitIsSiegeEngine) {
                    _damage = _damage / 2;
                }
                if (this->units[unitID].isStalked == 0) {
                    DAT_GameCore::instance.cowPoisonTrackerUnk = DAT_GameCore::instance.cowPoisonTrackerUnk + 0x32;
                }
            }
            if ((int)DAT_EntityState::instance.entityArray[entityID].startingHeight
                < DAT_EntityState::instance.entityArray[entityID].targetZ + -0x1e) {
                if ((this->units[unitID].unitType == OpenSHC::Map::Units::UT_E_ENGINEER)
                    && (this->units[unitID].resourceToDeposit != 0)) {
                    _damage = _damage / 0x14;
                } else if (_entityType == OpenSHC::Map::Entities::ET_BALLISTA) {
                    _damage = _damage / 2;
                } else {
                    _damage = _damage / 3;
                }
            }
            this->units[unitID].health = this->units[unitID].health - _damage;
            if (this->units[unitID].health < 1) {
                this->units[unitID].health = 0;
            }
            if (_entityShootingUnitID_2 != 0) {
                if (this->units[unitID].field97_0xd0 < 1000) {
                    this->units[unitID].field97_0xd0 = this->units[unitID].field97_0xd0 + 200;
                }
                DAT_TribesState::instance.tribes[_unknown].someUnitArrayIndex
                    = DAT_TribesState::instance.tribes[_unknown].someUnitArrayIndex + 1;
                DAT_TribesState::instance.tribes[_unknown].countdown = 100;
                if (9 < DAT_TribesState::instance.tribes[_unknown].someUnitArrayIndex) {
                    DAT_TribesState::instance.tribes[_unknown].someUnitArrayIndex = 0;
                }
                DAT_TribesState::instance.tribes[_unknown]
                    .someUnitArray[DAT_TribesState::instance.tribes[_unknown].someUnitArrayIndex]
                    = _entityShootingUnitID;
                DAT_TribesState::instance.tribes[_unknown]
                    .someUnitUIDArray[DAT_TribesState::instance.tribes[_unknown].someUnitArrayIndex]
                    = this->units[_entityShootingUnitID_2].uid;
            }
            int _unitHealth = this->units[unitID].health;
            int _healthPercentage_2
                = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHealthPercentage,
                    DAT_DirectionAlgorithmState::ptr)(_unitHealth, this->units[unitID].maxHealth);
            this->units[unitID].healthPercentage = (short)_healthPercentage_2;
            this->units[unitID].healthbar = this->units[unitID].healthPercentage / 10;
            if (_unitType == OpenSHC::Map::Units::UT_BREWER || _unitType == OpenSHC::Map::Units::UT_TANNER
                || _unitType == OpenSHC::Map::Units::UT_LADY || _unitType == OpenSHC::Map::Units::UT_MOTHER
                || (_unitType == OpenSHC::Map::Units::UT_CHILD && (this->units[unitID].spriteID == 0x81))) {
                _usesFemaleDeathScream = 1;
            }
            bool _shootingUnitID = this->units[_entityShootingUnitID_2].unitType == OpenSHC::Map::Units::UT_A_SLINGER;
            if ((_unitHealth < 1) && (this->units[unitID].dying == 0)) {
                this->units[unitID].dying = 1;
                if (0 < _unknown) {
                    DAT_TribesState::instance.tribes[_unknown].field133_0x278 = 1;
                }
                this->units[unitID].animationCycleNumber = 0;
                _entityType = DAT_EntityState::instance.entityArray[entityID].entityType;
                if (_entityType == OpenSHC::Map::Entities::ET_COW_FLYING) {
                    this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
                } else {
                    this->units[unitID].state.generic = _entityType == OpenSHC::Map::Entities::ET_SLINGER
                        ? OpenSHC::Map::Units::States::US_STONE_DEATH_01
                        : (UnitState)(OpenSHC::Map::Units::States::US_STONE_DEATH_01 - 3);
                }
                /* read before the write below, which the original also ordered this way */
                byte _wasStalked = this->units[unitID].isStalked;
                this->units[unitID].tunnelerFinishedDigging = 1;
                if (_wasStalked == 0) {
                    switch (this->units[unitID].unitType) {
                    case OpenSHC::Map::Units::UT_S_CATAPULT:
                    case OpenSHC::Map::Units::UT_S_MANGONEL:
                    case OpenSHC::Map::Units::UT_S_TOWER:
                    case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                    case OpenSHC::Map::Units::UT_S_BALLISTA:
                    case OpenSHC::Map::Units::UT_S_FBALLISTA:
                        sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_SIEGE_DIE;
                        break;
                    case OpenSHC::Map::Units::UT_S_TREBUCHET:
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)this->units[unitID].x, (int)(this->units[unitID].y), OpenSHC::DE::SHCDE::FX_TR_DIE);
                        break;
                    case OpenSHC::Map::Units::UT_S_SHIELD:
                        if ((this->units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                != 0)
                            && (!_shootingUnitID)) {
                            sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_DEATH_ARROW;
                            break;
                        }
                        sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_SIEGE_DIE;
                        break;
                    }
                    if (_usesFemaleDeathScream) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_GIRL_DIE);
                        if (_shootingUnitID) {
                            sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_HIT_SLINGSTONE;
                        } else {
                            sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_ARROW_HIT;
                        }
                    } else if (!_shootingUnitID) {
                        sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_DEATH_ARROW;
                    } else {
                        sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_DEATH_SLINGSTONE;
                    }
                } else if (_shootingUnitID) {
                    sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_HIT_SLINGSTONE;
                } else {
                    sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_ARROW_HIT_ANIMAL;
                }
            } else {
                if (this->units[unitID].isStalked != 0) {
                    if (_shootingUnitID) {
                        sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_HIT_SLINGSTONE;
                    } else {
                        sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_ARROW_HIT_ANIMAL;
                    }
                } else {
                    switch (this->units[unitID].unitType) {
                    case OpenSHC::Map::Units::UT_S_CATAPULT:
                    case OpenSHC::Map::Units::UT_S_TREBUCHET:
                    case OpenSHC::Map::Units::UT_S_MANGONEL:
                    case OpenSHC::Map::Units::UT_S_TOWER:
                    case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                    case OpenSHC::Map::Units::UT_S_BALLISTA:
                    case OpenSHC::Map::Units::UT_S_FBALLISTA:
                        sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_WOOD_HIT;
                        break;
                    default: {
                        uint _hitSoundVariant = this->units[unitID].fixedRng & 7;
                        if (_hitSoundVariant != 0) {
                            if (_hitSoundVariant == 1) {
                                sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_BODY_HIT2;
                                break;
                            }
                            if (_hitSoundVariant == 2) {
                                sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_BODY_HIT3;
                                break;
                            }
                            if (_hitSoundVariant == 3) {
                                sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_BODY_HIT4;
                                break;
                            }
                            if (_hitSoundVariant == 4) {
                                sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_BODY_HIT5;
                            } else {
                                if (_hitSoundVariant == 5) {
                                    sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_BODY_HIT6;
                                    break;
                                }
                                if (_hitSoundVariant == 6) {
                                    sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_BODY_HIT7;
                                    break;
                                }
                                if (_hitSoundVariant != 7) {
                                    return TRUE;
                                }
                                sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_BODY_HIT8;
                            }
                            break;
                        }
                        sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_BODY_HIT;
                        break;
                    }
                    case OpenSHC::Map::Units::UT_LORD:
                        return TRUE;
                    case OpenSHC::Map::Units::UT_S_SHIELD:
                        if (this->units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            < 1) {
                            return TRUE;
                        }
                        sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_BODY_HIT2;
                        break;
                    }
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                _unitXPosition_2, _unitYPosition_2, sfxOffsetInArray);
            return TRUE;
        }

    }
}
}
