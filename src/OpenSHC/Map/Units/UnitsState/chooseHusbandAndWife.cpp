#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_00ee0fe8.hpp"
#include "OpenSHC/Globals/DAT_00ee1028.hpp"
#include "OpenSHC/Globals/DAT_00ee102c.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00539DF0
        undefined4 UnitsState::chooseHusbandAndWife(int* husbandID, int* wifeID)
        {
            int _menIDs[100];
            int _womenIDs[100];
            int _menCount = 0;
            int _womenCount = 0;
            for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].logicalState == OpenSHC::Map::Units::ULS_INVISIBLE) {
                    continue;
                }
                if (this->units[unitID].unitType == (UnitType)0) {
                    continue;
                }
                if (unitID == DAT_00ee102c::instance || unitID == DAT_00ee1028::instance) {
                    continue;
                }
                switch (this->units[unitID].unitType) {
                case OpenSHC::Map::Units::UT_WOODCUTTER:
                case OpenSHC::Map::Units::UT_FLETCHER:
                case OpenSHC::Map::Units::UT_TUNNELER:
                case OpenSHC::Map::Units::UT_HUNTER:
                case OpenSHC::Map::Units::UT_QUARRYMASON:
                case OpenSHC::Map::Units::UT_QUARRYWORKER:
                case OpenSHC::Map::Units::UT_PITCHMAN:
                case OpenSHC::Map::Units::UT_WHEATFARMER:
                case OpenSHC::Map::Units::UT_HOPSFARMER:
                case OpenSHC::Map::Units::UT_APPLEFARMER:
                case OpenSHC::Map::Units::UT_DAIRYFARMER:
                case OpenSHC::Map::Units::UT_MILLER:
                case OpenSHC::Map::Units::UT_BAKER:
                case OpenSHC::Map::Units::UT_POLETURNER:
                case OpenSHC::Map::Units::UT_SMITH:
                case OpenSHC::Map::Units::UT_ARMORER:
                case OpenSHC::Map::Units::UT_MINER:
                case OpenSHC::Map::Units::UT_TRANSPORTMINER:
                case OpenSHC::Map::Units::UT_PRIEST:
                case OpenSHC::Map::Units::UT_HEALER:
                case OpenSHC::Map::Units::UT_DRUNK:
                case OpenSHC::Map::Units::UT_INNKEEPER:
                case OpenSHC::Map::Units::UT_TRADER:
                case OpenSHC::Map::Units::UT_JESTER:
                    if ((char)this->units[unitID].firstNameIndex < 51 && _menCount < 100) {
                        _menIDs[_menCount] = unitID;
                        _menCount = _menCount + 1;
                    }
                    break;
                case OpenSHC::Map::Units::UT_BREWER:
                case OpenSHC::Map::Units::UT_TANNER:
                case OpenSHC::Map::Units::UT_MOTHER:
                    if ((char)this->units[unitID].firstNameIndex > 52 && _womenCount < 100) {
                        _womenIDs[_womenCount] = unitID;
                        _womenCount = _womenCount + 1;
                    }
                }
            }
            if (_womenCount < 1 || _menCount < 1) {
                return 0;
            }
            int _husband = _menIDs[SEC_RNG::instance.currentNumber1 % _menCount];
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
            int _wife = _womenIDs[SEC_RNG::instance.currentNumber1 % _womenCount];
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
            /* the eight most recent couples live in the pair array at 0x00EE0FE8 */
            for (int i = 0; i < 8; ++i) {
                if (_husband == (&DAT_00ee0fe8::instance)[i * 2] && _wife == (&DAT_00ee0fe8::instance)[i * 2 + 1]) {
                    return 0;
                }
            }
            *husbandID = _husband;
            *wifeID = _wife;
            for (int i = 7; i > 0; --i) {
                (&DAT_00ee0fe8::instance)[i * 2] = (&DAT_00ee0fe8::instance)[(i - 1) * 2];
                (&DAT_00ee0fe8::instance)[i * 2 + 1] = (&DAT_00ee0fe8::instance)[(i - 1) * 2 + 1];
            }
            (&DAT_00ee0fe8::instance)[0] = _husband;
            (&DAT_00ee0fe8::instance)[1] = _wife;
            DAT_00ee102c::instance = _husband;
            DAT_00ee1028::instance = _wife;
            return 1;
        }

    }
}
}
