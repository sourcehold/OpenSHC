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
            if (unitID <= 0) {
                return 0;
            }
            if (this->units[unitID].dying != 0) {
                return 0;
            }
            UnitTypeShort unitType = this->units[unitID].unitType;
            int damage;
            if (unitType == OpenSHC::Map::Units::UT_LORD) {
                damage = 25;
            } else if (unitType == OpenSHC::Map::Units::UT_FIREFIGHTER) {
                damage = 1;
            } else if (unitType == OpenSHC::Map::Units::UT_A_FIRETHROWER) {
                damage = 10;
            } else {
                damage = 100;
            }
            if (halfTheDamage != 0) {
                damage = damage / 2;
            }
            if (playerID != 0 && playerID != this->units[unitID].owner) {
                this->units[unitID].lastEncounteredEnemyPlayerID = (short)playerID;
                this->units[unitID].lastEncounteredEnemyUnitIDUnk = 0;
            }
            this->units[unitID].health -= damage;
            if (this->units[unitID].health <= 0) {
                this->units[unitID].health = 0;
            }
            this->units[unitID].healthPercentage = this->units[unitID].maxHealth == 0
                ? 100
                : this->units[unitID].health * 100 / this->units[unitID].maxHealth;
            this->units[unitID].healthbar = this->units[unitID].healthPercentage / 10;
            if (this->units[unitID].health > 0) {
                return 1;
            }
            this->units[unitID].animationCycleNumber = 0;
            this->units[unitID].field323_0x442 = 1;
            if (unitType == OpenSHC::Map::Units::UT_LORD) {
                this->units[unitID].dying = 1;
                this->units[unitID].tunnelerFinishedDigging = 1;
                this->units[unitID].health = 0;
                this->units[unitID].animationCycleNumber = 0;
                this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
                return 1;
            }
            this->units[unitID].logicalState = OpenSHC::Map::Units::ULS_TRANSITIONING;
            this->units[unitID].state_2 = 0;
            int const unitTypeID = unitType;
            switch (unitTypeID) {
            case OpenSHC::Map::Units::UT_ANTELOPESHDEER:
                if (this->units[unitID].antelopeBasedRngValue == 2) {
                    this->units[unitID].unitTypeToChangeInto = OpenSHC::Map::Units::UT_BURNING_ANIMAL_SMALL;
                    this->units[unitID].state_2 = 1;
                    break;
                }
                this->units[unitID].unitTypeToChangeInto = OpenSHC::Map::Units::UT_BURNING_ANIMAL_BIG;
                this->units[unitID].state_2 = 1;
                break;
            case OpenSHC::Map::Units::UT_RABBIT:
            case OpenSHC::Map::Units::UT_HUNTERDOG:
            case OpenSHC::Map::Units::UT_CHICKEN:
                this->units[unitID].unitTypeToChangeInto = OpenSHC::Map::Units::UT_BURNING_ANIMAL_SMALL;
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
            default:
                this->units[unitID].unitTypeToChangeInto = OpenSHC::Map::Units::UT_BURNINGMAN;
            }
            if (this->units[unitID].isStalked != 0) {
                return 1;
            }
            /* if a male */
            if (unitTypeID != OpenSHC::Map::Units::UT_BREWER && unitTypeID != OpenSHC::Map::Units::UT_TANNER
                && unitTypeID != OpenSHC::Map::Units::UT_LADY && unitTypeID != OpenSHC::Map::Units::UT_MOTHER
                && (unitTypeID != OpenSHC::Map::Units::UT_CHILD || this->units[unitID].spriteID != 0x81)) {
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                if ((SEC_RNG::instance.currentNumber1 & 1) != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_MAN_BURN);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_MAN_BURN2);
                }
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
