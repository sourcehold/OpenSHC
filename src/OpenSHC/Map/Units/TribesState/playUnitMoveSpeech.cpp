#include "../../../Map.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Audio::SFX::SpeechEffectID;

        /*
          The original tail-calls playSpeechSFX with 0x2e - it writes the argument into the
          incoming slot, pops and jumps - so one of the two call sites here ends the
          function. Adding the `return` to the stone-ammunition site costs 6.2 points
          (82.8% -> 76.6%) and dropping the `param_1 = 0x2e` write with it costs 11.0
          (82.8% -> 71.8%), so it is the other site, or the block layout costs more than
          the matched jump is worth. Needs the two sites told apart before trying again.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00521EF0
        void TribesState::playUnitMoveSpeech(undefined4 param_1)
        {
            int _unitID;
            UnitType _unitTypeID;
            _unitID = MACRO_CALL_MEMBER(
                Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
            /*
              bug: the second argument ("stack") does not want to be renamed, but is   sfxToPlay again.
             */
            _unitTypeID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getMajoritySelectedUnitType, this)(
                (param_1), (int*)(&param_1));
            switch (_unitTypeID) {
            case Map::Units::UT_E_ARCHER:
            case Map::Units::UT_E_XBOW:
            case Map::Units::UT_A_ARCHER:
            case Map::Units::UT_A_SLINGER:
            case Map::Units::UT_A_HARCHER:
            case Map::Units::UT_A_FIRETHROWER:
                /*
                  Any other ranged unit
                 */
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    _unitTypeID, 0x1d);
                return;
            case Map::Units::UT_S_CATAPULT:
                /*
                  Catapult
                 */
                if (DAT_UnitsState::instance.units[_unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    != 0) {
                    if (DAT_UnitsState::instance.units[_unitID].stoneAmmunition < 1) {
                        param_1 = 0x2e;
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                            Audio::SFX::SEID_RESOURCE_NEED25);
                    }
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        _unitTypeID, 0x10);
                }
                break;
            case Map::Units::UT_S_TREBUCHET:
                /*
                  Trebuchet
                 */
                if (DAT_UnitsState::instance.units[_unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    != 0) {
                    if (DAT_UnitsState::instance.units[_unitID].stoneAmmunition < 1) {
                        param_1 = 0x2e;
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                            Audio::SFX::SEID_RESOURCE_NEED25);
                    }
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        _unitTypeID, 0x11);
                }
                break;
            case Map::Units::UT_S_MANGONEL:
                /*
                  Mangonel
                 */
                if (DAT_UnitsState::instance.units[_unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    != 0) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        _unitTypeID, 0xf);
                }
                break;
            case Map::Units::UT_S_BATTERINGRAM:
                /*
                  Battering ram
                 */
                if (DAT_UnitsState::instance.units[_unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    != 0) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        _unitTypeID, 0x13);
                }
                break;
            case Map::Units::UT_S_BALLISTA:
            case Map::Units::UT_S_FBALLISTA:
                /*
                  Ballista and fire ballista
                 */
                if (DAT_UnitsState::instance.units[_unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    != 0) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        _unitTypeID, 0x12);
                }
            }
        }

    }
}
}
