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
            if (this->units[unitID].healthPercentage <= 0xa) {
                return;
            }
            if (this->units[unitID].isStalked != 0) {
                return;
            }
            int _unitType = this->units[unitID].unitType;
            if (_unitType <= 0) {
                return;
            }
            if (_unitType == OpenSHC::Map::Units::UT_S_CATAPULT || _unitType == OpenSHC::Map::Units::UT_S_TREBUCHET
                || _unitType == OpenSHC::Map::Units::UT_S_MANGONEL || _unitType == OpenSHC::Map::Units::UT_S_BALLISTA
                || _unitType == OpenSHC::Map::Units::UT_S_TOWER
                || _unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_ATTACK_WOOD);
                return;
            }
            if (_unitType == OpenSHC::Map::Units::UT_S_SHIELD) {
                if (this->units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 == 0) {
                    return;
                }
            } else if (_unitType == OpenSHC::Map::Units::UT_BREWER || _unitType == OpenSHC::Map::Units::UT_TANNER
                || _unitType == OpenSHC::Map::Units::UT_LADY || _unitType == OpenSHC::Map::Units::UT_MOTHER
                || (_unitType == OpenSHC::Map::Units::UT_CHILD && this->units[unitID].spriteID == 0x81)) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_GIRL_GRUNT);
                return;
            }
            if ((this->units[unitID].fixedRng & 7) == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT);
            } else if ((this->units[unitID].fixedRng & 7) == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT2);
            } else if ((this->units[unitID].fixedRng & 7) == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT3);
            } else if ((this->units[unitID].fixedRng & 7) == 3) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT4);
            } else if ((this->units[unitID].fixedRng & 7) == 4) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT5);
            } else if ((this->units[unitID].fixedRng & 7) == 5) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT6);
            } else if ((this->units[unitID].fixedRng & 7) == 6) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT7);
            } else if ((this->units[unitID].fixedRng & 7) == 7) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->units[unitID].x, this->units[unitID].y, OpenSHC::DE::SHCDE::FX_BODY_HIT8);
            }
        }

    }
}
}
