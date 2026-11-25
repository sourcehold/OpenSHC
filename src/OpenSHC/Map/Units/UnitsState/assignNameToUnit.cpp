#include "../UnitsState.func.hpp"

#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0052EED0
        void UnitsState::assignNameToUnit(int unitID)
        {
            this->units[unitID].rng1_to_70 = 0;
            int _unitType = this->units[unitID].unitType;
            if (_unitType == OpenSHC::Map::Units::UT_COW) {
                this->units[unitID].firstNameIndex = (SEC_RNG::instance.currentNumber2 % 4) + 73;
                return;
            }
            if (_unitType == OpenSHC::Map::Units::UT_CHICKEN) {
                this->units[unitID].firstNameIndex = (SEC_RNG::instance.currentNumber2 % 4) + 77;
                return;
            }
            if (_unitType == OpenSHC::Map::Units::UT_HUNTERDOG) {
                this->units[unitID].firstNameIndex = (SEC_RNG::instance.currentNumber2 % 4) + 81;
                return;
            }
            if (_unitType == OpenSHC::Map::Units::UT_QUARRYOX) {
                this->units[unitID].firstNameIndex = (SEC_RNG::instance.currentNumber2 % 4) + 85;
                return;
            }
            if (_unitType == OpenSHC::Map::Units::UT_TANNER || _unitType == OpenSHC::Map::Units::UT_LADY
                || _unitType == OpenSHC::Map::Units::UT_MOTHER || _unitType == OpenSHC::Map::Units::UT_BREWER
                || (_unitType == OpenSHC::Map::Units::UT_CHILD && this->units[unitID].spriteID == 0x81)) {
                /* women */
                this->units[unitID].firstNameIndex = (SEC_RNG::instance.currentNumber2 % 20) + 52;
            } else {
                /* men */
                this->units[unitID].firstNameIndex = (SEC_RNG::instance.currentNumber2 % 50) + 1;
            }
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            this->units[unitID].rng1_to_70 = (SEC_RNG::instance.currentNumber2 % 70) + 1;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        }

    }
}
}
