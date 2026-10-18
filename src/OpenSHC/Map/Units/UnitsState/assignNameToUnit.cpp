#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052EED0
        void UnitsState::assignNameToUnit(int unitID)
        {
            this->units[unitID].rng1_to_70 = 0;
            int _unitType = this->units[unitID].unitType;
            if (_unitType == OpenSHC::Map::Units::UT_COW) {
                this->units[unitID].firstNameIndex = (char)(SEC_RNG::instance.currentNumber2 % 4) + 0x49;
                return;
            }
            if (_unitType == OpenSHC::Map::Units::UT_CHICKEN) {
                this->units[unitID].firstNameIndex = (char)(SEC_RNG::instance.currentNumber2 % 4) + 0x4d;
                return;
            }
            if (_unitType == OpenSHC::Map::Units::UT_HUNTERDOG) {
                this->units[unitID].firstNameIndex = (char)(SEC_RNG::instance.currentNumber2 % 4) + 0x51;
                return;
            }
            if (_unitType == OpenSHC::Map::Units::UT_QUARRYOX) {
                this->units[unitID].firstNameIndex = (char)(SEC_RNG::instance.currentNumber2 % 4) + 0x55;
                return;
            }
            if (_unitType == OpenSHC::Map::Units::UT_TANNER || _unitType == OpenSHC::Map::Units::UT_LADY
                || _unitType == OpenSHC::Map::Units::UT_MOTHER || _unitType == OpenSHC::Map::Units::UT_BREWER
                || (_unitType == OpenSHC::Map::Units::UT_CHILD && this->units[unitID].spriteID == 0x81)) {
                /* women */
                this->units[unitID].firstNameIndex = (char)(SEC_RNG::instance.currentNumber2 % 0x14) + 52;
            } else {
                /* men */
                this->units[unitID].firstNameIndex = (char)(SEC_RNG::instance.currentNumber2 % 0x32) + 1;
            }
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            this->units[unitID].rng1_to_70 = (char)(SEC_RNG::instance.currentNumber2 % 0x46) + 1;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        }

    }
}
}
