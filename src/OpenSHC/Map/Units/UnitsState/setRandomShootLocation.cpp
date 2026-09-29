#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x005330A0
        void UnitsState::setRandomShootLocation(int unitID, int microX, int microY, int z)
        {
            int _distanceX;
            if (this->units[unitID].microXPosition < microX) {
                _distanceX = microX - this->units[unitID].microXPosition;
            } else {
                _distanceX = this->units[unitID].microXPosition - microX;
            }
            int _distance;
            if (this->units[unitID].microYPosition < microY) {
                _distance = microY - this->units[unitID].microYPosition;
            } else {
                _distance = this->units[unitID].microYPosition - microY;
            }
            if (_distance <= _distanceX) {
                _distance = _distanceX;
            }
            int _rng = SEC_RNG::instance.currentNumber2;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            int _spreadAlong;
            int _spreadAcross;
            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                _spreadAlong = 0;
                if ((_rng & 3) == 0) {
                    _spreadAlong = _rng % 0x60 + -0x30;
                }
                _spreadAcross = (_rng / 256) % 0x60 + -0x30;
                z = z + -0x10 + (_rng / 128) % 0x20;
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_CATAPULT) {
                _spreadAlong = _rng % 0x80 - 0x60;
                _spreadAcross = (_rng / 256) % 0x60 + -0x30;
                z = z + -0x30 + (_rng / 128) % 0x40;
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_MANGONEL) {
                _spreadAlong = _rng % 0xe0 + -0x70;
                _spreadAcross = (_rng / 256) % 0x80 - 0x40;
                z = z + -0x40 + (_rng / 128) % 0x80;
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_BALLISTA) {
                if (this->units[unitID].targetingType == OpenSHC::Map::Units::UIT_ATTACK_LAND) {
                    _spreadAlong = _rng % 0x20 - 0x18;
                    _spreadAcross = (_rng / 256) % 0x28 + -0x14;
                    z = z + -0x14 + (_rng / 128) % 0x28;
                } else {
                    _spreadAlong = 0;
                    _spreadAcross = 0;
                }
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_FBALLISTA
                && this->units[unitID].targetingType != OpenSHC::Map::Units::UIT_ATTACK_LAND) {
                _spreadAlong = 0;
                _spreadAcross = 0;
                z = z + (_rng / 128) % 0x1e;
            } else {
                _spreadAlong = _rng % 0x60 + -0x30;
                _spreadAcross = (_rng / 256) % 0x50 + -0x28;
                z = z + -0x28 + (_rng / 128) % 0x50;
            }
            if (z < 8) {
                z = 8;
            } else if (z > 250) {
                z = 250;
            }
            if (_distance / 2 < _spreadAlong) {
                _spreadAlong = _spreadAlong / 2;
                _spreadAcross = _spreadAcross / 2;
            }
            if (_distance < _spreadAlong) {
                _spreadAlong = -_spreadAlong;
            }
            switch (this->units[unitID].facingDirection) {
            case 0:
                microY = microY + _spreadAlong;
                microX = microX + _spreadAcross;
                break;
            case 1:
                microX = microX + ((_spreadAcross * 3) / 4 - (_spreadAlong * 3) / 4);
                microY = microY + (_spreadAlong * 3) / 4 + (_spreadAcross * 3) / 4;
                break;
            case 2:
                microX = microX - _spreadAlong;
                microY = microY + _spreadAcross;
                break;
            case 3:
                microX = microX + (-((_spreadAlong * 3) / 4) - (_spreadAcross * 3) / 4);
                microY = microY + ((_spreadAcross * 3) / 4 - (_spreadAlong * 3) / 4);
                break;
            case 4:
                microY = microY - _spreadAlong;
                microX = microX + _spreadAcross;
                break;
            case 5:
                microX = microX + ((_spreadAlong * 3) / 4 - (_spreadAcross * 3) / 4);
                microY = microY + (-((_spreadAcross * 3) / 4) - (_spreadAlong * 3) / 4);
                break;
            case 6:
                microX = microX + _spreadAlong;
                microY = microY + _spreadAcross;
                break;
            case 7:
                microX = microX + (_spreadAlong * 3) / 4 + (_spreadAcross * 3) / 4;
                microY = microY + ((_spreadAlong * 3) / 4 - (_spreadAcross * 3) / 4);
            }
            this->units[unitID].shootTargetZ = (short)z;
            this->units[unitID].shootTargetMicroY = (short)microY;
            this->units[unitID].shootTargetMicroX = (short)microX;
        }

    }
}
}
