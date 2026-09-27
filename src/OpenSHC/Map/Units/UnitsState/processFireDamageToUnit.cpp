#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::DE::SHCDE::eSFX;
        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00532460
        undefined4 UnitsState::processFireDamageToUnit(int unitID, int playerID, int halfTheDamage)
        {
            if (unitID < 1) {
                return 0;
            }
            if (this->units[unitID].dying != 0) {
                return 0;
            }
            UnitTypeShort _unitType = this->units[unitID].unitType;
            uint _damage;
            if (_unitType == OpenSHC::Map::Units::UT_LORD) {
                _damage = 25;
            } else if (_unitType == OpenSHC::Map::Units::UT_FIREFIGHTER) {
                _damage = 1;
            } else if (_unitType == OpenSHC::Map::Units::UT_A_FIRETHROWER) {
                _damage = 10;
            } else {
                _damage = 100;
            }
            if (halfTheDamage != 0) {
                _damage = _damage / 2;
            }
            if (playerID != 0 && playerID != this->units[unitID].owner) {
                this->units[unitID].lastEncounteredEnemyPlayerID = (short)playerID;
                this->units[unitID].lastEncounteredEnemyUnitIDUnk = 0;
            }
            this->units[unitID].health = this->units[unitID].health - _damage;
            if (this->units[unitID].health < 1) {
                this->units[unitID].health = 0;
            }
            if (this->units[unitID].maxHealth == 0) {
                this->units[unitID].healthPercentage = 100;
            } else {
                this->units[unitID].healthPercentage
                    = (short)((this->units[unitID].health * 100) / this->units[unitID].maxHealth);
            }
            this->units[unitID].healthbar = this->units[unitID].healthPercentage / 10;
            if (this->units[unitID].health > 0) {
                return 1;
            }
            this->units[unitID].animationCycleNumber = 0;
            this->units[unitID].field323_0x442 = 1;
            if (_unitType == OpenSHC::Map::Units::UT_LORD) {
                this->units[unitID].dying = 1;
                this->units[unitID].tunnelerFinishedDigging = 1;
                this->units[unitID].health = 0;
                this->units[unitID].animationCycleNumber = 0;
                this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
                return 1;
            }
            this->units[unitID].logicalState = OpenSHC::Map::Units::ULS_TRANSITIONING;
            this->units[unitID].state_2 = 0;
            switch (_unitType) {
            case OpenSHC::Map::Units::UT_ANTELOPESHDEER:
                if (this->units[unitID].antelopeBasedRngValue == 2) {
                    this->units[unitID].unitTypeToChangeInto = OpenSHC::Map::Units::UT_BURNING_ANIMAL_SMALL;
                    this->units[unitID].state_2 = 1;
                    break;
                }
                this->units[unitID].unitTypeToChangeInto = OpenSHC::Map::Units::UT_BURNING_ANIMAL_BIG;
                this->units[unitID].state_2 = 1;
                break;
            case OpenSHC::Map::Units::UT_QUARRYOX:
            case OpenSHC::Map::Units::UT_LIONSHWOLF:
            case OpenSHC::Map::Units::UT_CAMELSHBEAR:
            case OpenSHC::Map::Units::UT_COW:
            case OpenSHC::Map::Units::UT_CAGEDOG:
                this->units[unitID].unitTypeToChangeInto = OpenSHC::Map::Units::UT_BURNING_ANIMAL_BIG;
                this->units[unitID].state_2 = 1;
                break;
            case OpenSHC::Map::Units::UT_RABBIT:
            case OpenSHC::Map::Units::UT_HUNTERDOG:
            case OpenSHC::Map::Units::UT_CHICKEN:
                this->units[unitID].unitTypeToChangeInto = OpenSHC::Map::Units::UT_BURNING_ANIMAL_SMALL;
                this->units[unitID].state_2 = 1;
                break;
            default:
                this->units[unitID].unitTypeToChangeInto = OpenSHC::Map::Units::UT_BURNINGMAN;
            }
            if (this->units[unitID].isStalked != 0) {
                return 1;
            }
            /* if a male */
            if (_unitType != OpenSHC::Map::Units::UT_BREWER && _unitType != OpenSHC::Map::Units::UT_TANNER
                && _unitType != OpenSHC::Map::Units::UT_LADY && _unitType != OpenSHC::Map::Units::UT_MOTHER
                && (_unitType != OpenSHC::Map::Units::UT_CHILD || this->units[unitID].spriteID != 0x81)) {
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                if (((byte)SEC_RNG::instance.currentNumber1 & 1) == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_MAN_BURN2);
                    return 1;
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_MAN_BURN);
                return 1;
            }
            /* if female */
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_GIRL_SCREAM);
            return 1;
        }

    }
}
}
