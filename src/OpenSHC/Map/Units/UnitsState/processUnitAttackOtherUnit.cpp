#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Audio::SFX::SoundEffectID;
        using OpenSHC::DE::SHCDE::eSFX;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00531220
        undefined4 UnitsState::processUnitAttackOtherUnit(int unitID, int unit2ID)
        {
            int _tribeID = this->units[unit2ID].tribeID;
            UnitTypeShort _unit2Type = this->units[unit2ID].unitType;
            /* get the damage from the array based: row is unit1ID type, column is unit2ID type */
            int _damage = DAT_UnitPropertiesDefinedData::instance
                              .MELEE_DAMAGE[(short)this->units[unitID].unitType][(short)_unit2Type];
            /* if unit 1 is not a lord */
            if (this->units[unitID].unitType != OpenSHC::Map::Units::UT_LORD) {
                _damage = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::computeDamageFearFactorBonus, this)(
                    _damage, DAT_UnitsState::instance.units[unitID].owner);
            }
            if (this->units[unitID].owner != 0 && this->units[unit2ID].owner != this->units[unitID].owner) {
                /* let unit 2 know we attacked them? */
                this->units[unit2ID].lastEncounteredEnemyUnitIDUnk = (short)unitID;
                this->units[unit2ID].lastEncounteredEnemyPlayerID = this->units[unitID].owner;
            }
            /* decrement the health of unit 2 by damage */
            this->units[unit2ID].health = this->units[unit2ID].health - _damage;
            if (this->units[unit2ID].health <= 0) {
                this->units[unit2ID].health = 0;
            }
            /* compute the health bar in percentages */
            short _healthPercentage;
            if (this->units[unit2ID].maxHealth == 0) {
                _healthPercentage = 100;
            } else {
                _healthPercentage = (short)((this->units[unit2ID].health * 100) / this->units[unit2ID].maxHealth);
            }
            this->units[unit2ID].healthPercentage = _healthPercentage;
            this->units[unit2ID].healthbar = _healthPercentage / 10;
            if (this->units[unit2ID].health <= 0 && this->units[unit2ID].isStalked != 0) {
                switch (this->units[unitID].unitType) {
                case OpenSHC::Map::Units::UT_WOODCUTTER:
                case OpenSHC::Map::Units::UT_LORD:
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_LORD_HIT);
                    break;
                case OpenSHC::Map::Units::UT_E_SPEAR:
                case OpenSHC::Map::Units::UT_A_ARCHER:
                case OpenSHC::Map::Units::UT_A_SLINGER:
                case OpenSHC::Map::Units::UT_A_HARCHER:
                case OpenSHC::Map::Units::UT_A_FIRETHROWER:
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_SPEAR_HIT);
                    break;
                case OpenSHC::Map::Units::UT_E_PIKE:
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_PIKE_HIT);
                    break;
                case OpenSHC::Map::Units::UT_E_MACE:
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_MACE_HIT);
                    break;
                case OpenSHC::Map::Units::UT_E_SWORD:
                case OpenSHC::Map::Units::UT_E_KNIGHT:
                case OpenSHC::Map::Units::UT_A_ASSASSIN:
                case OpenSHC::Map::Units::UT_A_SWORDSMAN:
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_SWORD_HIT);
                    break;
                }
            }
            if (this->units[unit2ID].health > 0) {
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                    && this->units[unit2ID].owner == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXWeAreUnderAttack, DAT_SFXState::ptr)();
                }
                return 0;
            }
            this->units[unit2ID].dying = 1;
            if (_tribeID > 0) {
                DAT_TribesState::instance.tribes[_tribeID].field133_0x278 = 1;
            }
            DAT_UnitsState::instance.units[unit2ID].animationCycleNumber = 0;
            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_E_SWORD) {
                this->units[unit2ID].state.generic = OpenSHC::Map::Units::States::US_DEATH_03;
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_E_KNIGHT) {
                this->units[unit2ID].state.generic = OpenSHC::Map::Units::States::US_DEATH_03;
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_E_SPEAR) {
                this->units[unit2ID].state.generic = OpenSHC::Map::Units::States::US_DEATH_03;
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_E_PIKE) {
                this->units[unit2ID].state.generic = OpenSHC::Map::Units::States::US_DEATH_03;
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_E_XBOW) {
                this->units[unit2ID].state.generic = OpenSHC::Map::Units::States::US_DEATH_03;
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_E_ARCHER) {
                this->units[unit2ID].state.generic = OpenSHC::Map::Units::States::US_DEATH_03;
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_A_ARCHER) {
                this->units[unit2ID].state.generic = OpenSHC::Map::Units::States::US_DEATH_03;
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_A_ASSASSIN) {
                this->units[unit2ID].state.generic = OpenSHC::Map::Units::States::US_DEATH_03;
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_A_HARCHER) {
                this->units[unit2ID].state.generic = OpenSHC::Map::Units::States::US_DEATH_03;
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_A_SWORDSMAN) {
                this->units[unit2ID].state.generic = OpenSHC::Map::Units::States::US_DEATH_03;
            } else {
                this->units[unit2ID].state.generic
                    = (this->units[unitID].unitType != OpenSHC::Map::Units::UT_A_FIRETHROWER)
                    + OpenSHC::Map::Units::States::US_DEATH_03;
            }
            uint _deathVariant = this->units[unit2ID].fixedRng & 1;
            this->units[unit2ID].tunnelerFinishedDigging = 1;
            if (this->units[unit2ID].isStalked != 0) {
                return 1;
            }
            switch (_unit2Type) {
            case OpenSHC::Map::Units::UT_S_CATAPULT:
            case OpenSHC::Map::Units::UT_S_MANGONEL:
            case OpenSHC::Map::Units::UT_S_TOWER:
            case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
            case OpenSHC::Map::Units::UT_S_BALLISTA:
            case OpenSHC::Map::Units::UT_S_FBALLISTA:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_SIEGE_DIE);
                return 1;
            case OpenSHC::Map::Units::UT_S_TREBUCHET:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_TR_DIE);
                return 1;
            case OpenSHC::Map::Units::UT_S_SHIELD:
                if (this->units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 > 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT);
                    return 1;
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_SIEGE_DIE);
                return 1;
            }
            bool _hasSpecialDeathSound = false;
            if (_unit2Type == OpenSHC::Map::Units::UT_BREWER || _unit2Type == OpenSHC::Map::Units::UT_TANNER
                || _unit2Type == OpenSHC::Map::Units::UT_LADY || _unit2Type == OpenSHC::Map::Units::UT_MOTHER
                || (_unit2Type == OpenSHC::Map::Units::UT_CHILD && this->units[unitID].spriteID == 0x81)) {
                _hasSpecialDeathSound = true;
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_GIRL_DIE);
            }
            if (_unit2Type == OpenSHC::Map::Units::UT_LORD) {
                if (this->units[unit2ID].owner == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_PLAYER_LORD_DEATH);
                    if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
                    }
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_AI_LORD_DEATH);
                }
                _hasSpecialDeathSound = true;
            } else if (_unit2Type == OpenSHC::Map::Units::UT_JESTER) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_JESTER_DIE);
                _hasSpecialDeathSound = true;
            }
            switch (this->units[unitID].unitType) {
            case OpenSHC::Map::Units::UT_WOODCUTTER:
                if (_hasSpecialDeathSound) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_LORD_HIT);
                    return 1;
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_LORD_KILL);
                return 1;
            case OpenSHC::Map::Units::UT_E_SPEAR:
            case OpenSHC::Map::Units::UT_A_ARCHER:
            case OpenSHC::Map::Units::UT_A_SLINGER:
            case OpenSHC::Map::Units::UT_A_HARCHER:
            case OpenSHC::Map::Units::UT_A_FIRETHROWER:
                if (_hasSpecialDeathSound) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_SPEAR_HIT);
                    return 1;
                }
                if (_deathVariant == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_DEATH_SPEAR);
                    return 1;
                }
                if (_deathVariant == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_DEATH_SPEAR2);
                    return 1;
                }
                return 1;
            case OpenSHC::Map::Units::UT_E_PIKE:
                if (_hasSpecialDeathSound) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_PIKE_HIT);
                    return 1;
                }
                if (_deathVariant == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_DEATH_SPEAR);
                    return 1;
                }
                if (_deathVariant == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_DEATH_SPEAR2);
                    return 1;
                }
                return 1;
            case OpenSHC::Map::Units::UT_E_MACE:
                if (_hasSpecialDeathSound) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_MACE_HIT);
                    return 1;
                }
                if (_deathVariant == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_DEATH_CLUB);
                    return 1;
                }
                if (_deathVariant == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_DEATH_CLUB2);
                    return 1;
                }
                return 1;
            case OpenSHC::Map::Units::UT_E_SWORD:
            case OpenSHC::Map::Units::UT_E_KNIGHT:
            case OpenSHC::Map::Units::UT_A_ASSASSIN:
            case OpenSHC::Map::Units::UT_A_SWORDSMAN:
                if (_hasSpecialDeathSound) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_SWORD_HIT);
                    return 1;
                }
                if (_deathVariant == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_DEATH_SWORD);
                    return 1;
                }
                if (_deathVariant == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_DEATH_SWORD2);
                    return 1;
                }
                return 1;
            case OpenSHC::Map::Units::UT_LORD:
                if (_hasSpecialDeathSound) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_LORD_HIT);
                    return 1;
                }
                if (this->units[unitID].unknownLordTypeBasedMissionSpecificValue_01 == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_LORD_KILL);
                    return 1;
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_ARAB_LORD_KILL);
                return 1;
            default:
                if (_hasSpecialDeathSound) {
                    return 1;
                }
                if ((this->units[unit2ID].fixedRng & 7) == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT);
                    return 1;
                }
                if ((this->units[unit2ID].fixedRng & 7) == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT2);
                    return 1;
                }
                if ((this->units[unit2ID].fixedRng & 7) == 2) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT3);
                    return 1;
                }
                if ((this->units[unit2ID].fixedRng & 7) == 3) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT4);
                    return 1;
                }
                if ((this->units[unit2ID].fixedRng & 7) == 4) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT5);
                    return 1;
                }
                if ((this->units[unit2ID].fixedRng & 7) == 5) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT6);
                    return 1;
                }
                if ((this->units[unit2ID].fixedRng & 7) == 6) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT7);
                    return 1;
                }
                if ((this->units[unit2ID].fixedRng & 7) == 7) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unit2ID].x, this->units[unit2ID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT8);
                    return 1;
                }
                return 1;
            }
        }

    }
}
}
