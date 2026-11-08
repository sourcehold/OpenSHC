#include "../UnitsState.func.hpp"

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
            if (microX > this->units[unitID].microXPosition) {
                _distanceX = microX - this->units[unitID].microXPosition;
            } else {
                _distanceX = this->units[unitID].microXPosition - microX;
            }
            int _distanceY;
            if (microY > this->units[unitID].microYPosition) {
                _distanceY = microY - this->units[unitID].microYPosition;
            } else {
                _distanceY = this->units[unitID].microYPosition - microY;
            }
            int _distance = _distanceX < _distanceY ? _distanceY : _distanceX;

            int _rng = SEC_RNG::instance.currentNumber2;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            int _spreadAlong;
            int _spreadAcross;
            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                _spreadAlong = 0;
                if ((_rng & 3) == 0) {
                    _spreadAlong = _rng % 96 - 48;
                }
                _spreadAcross = (_rng / 256) % 96 - 48;
                z = z - 16 + (_rng / 128) % 32;
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_CATAPULT) {
                _spreadAlong = _rng % 128 - 96;
                _spreadAcross = (_rng / 256) % 96 - 48;
                z = z - 48 + (_rng / 128) % 64;
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_MANGONEL) {
                _spreadAlong = _rng % 224 - 112;
                _spreadAcross = (_rng / 256) % 128 - 64;
                z = z - 64 + (_rng / 128) % 128;
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_BALLISTA) {
                if (this->units[unitID].targetingType == OpenSHC::Map::Units::UIT_ATTACK_LAND) {
                    _spreadAlong = _rng % 32 - 24;
                    _spreadAcross = (_rng / 256) % 40 - 20;
                    z = z - 20 + (_rng / 128) % 40;
                } else {
                    _spreadAlong = 0;
                    _spreadAcross = 0;
                }
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_FBALLISTA
                && this->units[unitID].targetingType != OpenSHC::Map::Units::UIT_ATTACK_LAND) {
                _spreadAlong = 0;
                _spreadAcross = 0;
                z = z + (_rng / 128) % 30;
            } else {
                _spreadAlong = _rng % 96 - 48;
                _spreadAcross = (_rng / 256) % 80 - 40;
                z = z - 40 + (_rng / 128) % 80;
            }
            if (z < 8) {
                z = 8;
            } else if (z > 250) {
                z = 250;
            }
            if (_spreadAlong > _distance / 2) {
                _spreadAlong = _spreadAlong / 2;
                _spreadAcross = _spreadAcross / 2;
            }
            if (_spreadAlong > _distance) {
                _spreadAlong = -_spreadAlong;
            }
            switch (this->units[unitID].facingDirection) {
            case 0:
                microY = microY + _spreadAlong;
                microX = microX + _spreadAcross;
                break;
            case 4:
                microY = microY - _spreadAlong;
                microX = microX + _spreadAcross;
                break;
            case 2:
                microX = microX - _spreadAlong;
                microY = microY + _spreadAcross;
                break;
            case 6:
                microX = microX + _spreadAlong;
                microY = microY + _spreadAcross;
                break;
            case 1:
                microX = microX + ((_spreadAcross * 3) / 4 - (_spreadAlong * 3) / 4);
                microY = microY + (_spreadAlong * 3) / 4 + (_spreadAcross * 3) / 4;
                break;
            case 7:
                microX = microX + (_spreadAlong * 3) / 4 + (_spreadAcross * 3) / 4;
                microY = microY + ((_spreadAlong * 3) / 4 - (_spreadAcross * 3) / 4);
                break;
            case 3:
                microX = microX + (-((_spreadAlong * 3) / 4) - (_spreadAcross * 3) / 4);
                microY = microY + ((_spreadAcross * 3) / 4 - (_spreadAlong * 3) / 4);
                break;
            case 5:
                microX = microX + ((_spreadAlong * 3) / 4 - (_spreadAcross * 3) / 4);
                microY = microY + (-((_spreadAcross * 3) / 4) - (_spreadAlong * 3) / 4);
                break;
            }
            this->units[unitID].shootTargetZ = z;
            this->units[unitID].shootTargetMicroY = microY;
            this->units[unitID].shootTargetMicroX = microX;
        }

    }
}
}
