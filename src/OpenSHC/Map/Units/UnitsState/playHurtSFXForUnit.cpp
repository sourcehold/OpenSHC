#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::DE::SHCDE::eSFX;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x005300B0
        void UnitsState::playHurtSFXForUnit(int unitID)
        {
            if (unitID == 0) {
                return;
            }
            if (this->units[unitID].healthPercentage < 0xb) {
                return;
            }
            if (this->units[unitID].isStalked != 0) {
                return;
            }
            if ((short)this->units[unitID].unitType <= 0) {
                return;
            }
            eSFX _sfxOffsetInArray;
            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_CATAPULT
                || this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_TREBUCHET
                || this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_MANGONEL
                || this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_BALLISTA
                || this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_TOWER
                || this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                _sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_ATTACK_WOOD;
            } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_BREWER
                || this->units[unitID].unitType == OpenSHC::Map::Units::UT_TANNER
                || this->units[unitID].unitType == OpenSHC::Map::Units::UT_LADY
                || this->units[unitID].unitType == OpenSHC::Map::Units::UT_MOTHER
                || (this->units[unitID].unitType == OpenSHC::Map::Units::UT_CHILD
                    && this->units[unitID].spriteID == 0x81)) {
                _sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_GIRL_GRUNT;
            } else {
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_SHIELD
                    && this->units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                        == 0) {
                    return;
                }
                if ((this->units[unitID].fixedRng & 7) == 0) {
                    _sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_BODY_HIT;
                } else if ((this->units[unitID].fixedRng & 7) == 1) {
                    _sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_BODY_HIT2;
                } else if ((this->units[unitID].fixedRng & 7) == 2) {
                    _sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_BODY_HIT3;
                } else if ((this->units[unitID].fixedRng & 7) == 3) {
                    _sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_BODY_HIT4;
                } else if ((this->units[unitID].fixedRng & 7) == 4) {
                    _sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_BODY_HIT5;
                } else if ((this->units[unitID].fixedRng & 7) == 5) {
                    _sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_BODY_HIT6;
                } else if ((this->units[unitID].fixedRng & 7) == 6) {
                    _sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_BODY_HIT7;
                } else if ((this->units[unitID].fixedRng & 7) == 7) {
                    _sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_BODY_HIT8;
                } else {
                    return;
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                this->units[unitID].x, this->units[unitID].y, _sfxOffsetInArray);
        }

    }
}
}
