#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053CBD0
        int UnitsState::prepareProjectileTarget(int shooterID, int targetID, int param_3)
        {
            uint _targetFixedRng = 0;
            if (targetID == -1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setRandomShootLocation, this)(shooterID,
                    this->units[shooterID].shootTargetMicroX, this->units[shooterID].shootTargetMicroY,
                    this->units[shooterID].shootTargetZ);
            } else {
                _targetFixedRng = this->units[targetID].fixedRng;
                this->units[shooterID].shootTargetMicroX = this->units[targetID].x * 8 + 4;
                this->units[shooterID].shootTargetMicroY = this->units[targetID].y * 8 + 4;
                this->units[shooterID].shootTargetZ
                    = this->units[targetID].buildingHeight + this->units[targetID].terrainOrClimbHeight;
                if (this->units[targetID].tunnelerFinishedDigging == 2) {
                    int _lead = (param_3 * 133) / 100;
                    short _adjustment;
                    /* todo:fixme:ucp: this if-else should be improved to also trigger when the
                       targetID has negative height (walking in pitch or moat) */
                    if (this->units[targetID].stateBasedSpeed == 0) {
                        if (this->units[targetID].calculatedMovementSpeed < 2) {
                            _adjustment = (short)((_lead + (_lead >> 0x1f & 0xfU)) >> 4);
                        } else {
                            _adjustment = (short)(_lead / (this->units[targetID].calculatedMovementSpeed << 4));
                        }
                    } else {
                        _adjustment = (short)((_lead + (_lead >> 0x1f & 7U)) >> 3);
                    }
                    switch (this->units[targetID].facingDirection) {
                    case 0:
                        this->units[shooterID].shootTargetMicroY
                            = this->units[shooterID].shootTargetMicroY - _adjustment;
                        break;
                    case 1:
                        this->units[shooterID].shootTargetMicroY
                            = this->units[shooterID].shootTargetMicroY - _adjustment;
                        this->units[shooterID].shootTargetMicroX
                            = this->units[shooterID].shootTargetMicroX + _adjustment;
                        break;
                    case 2:
                        this->units[shooterID].shootTargetMicroX
                            = this->units[shooterID].shootTargetMicroX + _adjustment;
                        break;
                    case 3:
                        this->units[shooterID].shootTargetMicroY
                            = this->units[shooterID].shootTargetMicroY + _adjustment;
                        this->units[shooterID].shootTargetMicroX
                            = this->units[shooterID].shootTargetMicroX + _adjustment;
                        break;
                    case 4:
                        this->units[shooterID].shootTargetMicroY
                            = this->units[shooterID].shootTargetMicroY + _adjustment;
                        break;
                    case 5:
                        this->units[shooterID].shootTargetMicroY
                            = this->units[shooterID].shootTargetMicroY + _adjustment;
                        this->units[shooterID].shootTargetMicroX
                            = this->units[shooterID].shootTargetMicroX - _adjustment;
                        break;
                    case 6:
                        this->units[shooterID].shootTargetMicroX
                            = this->units[shooterID].shootTargetMicroX - _adjustment;
                        break;
                    case 7:
                        this->units[shooterID].shootTargetMicroY
                            = this->units[shooterID].shootTargetMicroY - _adjustment;
                        this->units[shooterID].shootTargetMicroX
                            = this->units[shooterID].shootTargetMicroX - _adjustment;
                    }
                }
            }
            int _result = (short)this->units[shooterID].unitType + -0x16;
            int _scatter;
            if (this->units[shooterID].shootTargetZ < this->units[shooterID].terrainOrClimbHeight) {
                switch (this->units[shooterID].unitType) {
                case OpenSHC::Map::Units::UT_S_CATAPULT:
                case OpenSHC::Map::Units::UT_S_BALLISTA:
                    _scatter = 0x14;
                    break;
                case OpenSHC::Map::Units::UT_S_TREBUCHET:
                    _scatter = 0x32;
                    break;
                case OpenSHC::Map::Units::UT_S_MANGONEL:
                    _scatter = 0x3c;
                    break;
                case OpenSHC::Map::Units::UT_S_FBALLISTA:
                    _scatter = 10;
                    break;
                default:
                    return _result;
                }
            } else {
                _scatter = this->units[shooterID].shootTargetZ - this->units[shooterID].terrainOrClimbHeight;
                if (_scatter > 0x4b) {
                    _scatter = _scatter + _scatter / 2;
                }
                switch (this->units[shooterID].unitType) {
                case OpenSHC::Map::Units::UT_S_CATAPULT:
                case OpenSHC::Map::Units::UT_S_BALLISTA:
                    _scatter = _scatter + 0x28;
                    break;
                case OpenSHC::Map::Units::UT_S_TREBUCHET:
                    _scatter = _scatter + 0x3c;
                    break;
                case OpenSHC::Map::Units::UT_S_MANGONEL:
                    _scatter = _scatter + 0x46;
                    break;
                case OpenSHC::Map::Units::UT_S_FBALLISTA:
                    return _result;
                }
                if (_scatter <= 0) {
                    return _result;
                }
                if (_scatter > 0x118) {
                    _scatter = 0x118;
                }
            }
            uint _rng = SEC_RNG::instance.currentNumber2;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            _result = ((int)_rng / 300) * 300;
            if ((int)_rng % 300 >= _scatter) {
                return _result;
            }
            if ((_rng & 7) < 2) {
                _scatter = (_scatter + (_scatter >> 0x1f & 3U)) >> 2;
                if (_scatter == 0) {
                    _scatter = 1;
                }
                int _horizontalRng
                    = ((int)(_rng + ((int)_rng >> 0x1f & 0x1ffU)) >> 9) + this->units[shooterID].fixedRng;
                if (_horizontalRng < 0) {
                    _horizontalRng = -_horizontalRng;
                }
                this->units[shooterID].shootTargetMicroX = this->units[shooterID].shootTargetMicroX
                    + ((short)(_horizontalRng % _scatter) - (short)(_scatter / 2));
                int _verticalRng = _rng + _targetFixedRng;
                if (_verticalRng < 0) {
                    _verticalRng = -_verticalRng;
                }
                this->units[shooterID].shootTargetMicroY = this->units[shooterID].shootTargetMicroY
                    + ((short)(_verticalRng % _scatter) - (short)(_scatter / 2));
                return _verticalRng / _scatter;
            }
            if ((_rng & 7) < 6) {
                _scatter = _scatter / 6;
                if (_scatter == 0) {
                    _scatter = 1;
                }
                int _heightRng = this->units[shooterID].fixedRng + _rng;
                if (_heightRng < 0) {
                    _heightRng = -_heightRng;
                }
                int _heightOffset = _heightRng % _scatter + 0x14;
                if (_heightRng % _scatter + 0x1c <= (int)this->units[shooterID].shootTargetZ) {
                    _result = (ushort)this->units[shooterID].shootTargetZ - _heightOffset;
                } else {
                    _result = (ushort)this->units[shooterID].shootTargetZ + _heightOffset;
                }
                this->units[shooterID].shootTargetZ = (short)_result;
                return _result;
            }
            _scatter = _scatter / 6;
            if (_scatter == 0) {
                _scatter = 1;
            }
            int _heightRng = _rng + _targetFixedRng;
            if (_heightRng < 0) {
                _heightRng = -_heightRng;
            }
            this->units[shooterID].shootTargetZ
                = this->units[shooterID].shootTargetZ + (short)(_heightRng % _scatter) + 0x28;
            return _heightRng / _scatter;
        }

    }
}
}
