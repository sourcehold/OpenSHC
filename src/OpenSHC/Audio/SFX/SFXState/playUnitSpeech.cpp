// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../SFXState.func.hpp"

#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_LastSpeechSFXFilename.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_SpeechDefinedData.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044B210
        void SFXState::playUnitSpeech(UnitType unitType, int actionID)
        {
            int variationIndex = 0;

            int _soundSet;
            switch (unitType) {

            case Map::Units::UT_A_ARCHER:
                _soundSet = 0xb;
                break;
            case Map::Units::UT_A_SLINGER:
                _soundSet = 0xc;
                break;
            case Map::Units::UT_A_ASSASSIN:
                _soundSet = 0xd;
                break;
            case Map::Units::UT_A_SLAVE:
                _soundSet = 0xe;
                break;
            case Map::Units::UT_A_FIRETHROWER:
                _soundSet = 0xf;
                break;
            case Map::Units::UT_A_SWORDSMAN:
                _soundSet = 0x10;
                break;
            case Map::Units::UT_A_HARCHER:
                _soundSet = 0x11;
                break;
            case Map::Units::UT_E_ARCHER:
                _soundSet = 0;
                break;
            case Map::Units::UT_E_XBOW:
                _soundSet = 1;
                break;
            case Map::Units::UT_E_SPEAR:
                _soundSet = 2;
                break;
            case Map::Units::UT_E_PIKE:
                _soundSet = 4;
                break;
            case Map::Units::UT_E_MACE:
                _soundSet = 3;
                break;
            case Map::Units::UT_E_SWORD:
                _soundSet = 5;
                break;
            case Map::Units::UT_E_KNIGHT:
                _soundSet = 6;
                break;
            case Map::Units::UT_E_LADDER:
                _soundSet = 9;
                break;
            case Map::Units::UT_TUNNELER:
                _soundSet = 8;
                break;
            case Map::Units::UT_E_MONK:
                _soundSet = 7;
                break;
            case Map::Units::UT_E_ENGINEER:
                _soundSet = 10;
                break;
            case Map::Units::UT_S_CATAPULT:
                if (actionID == 0) {
                    MACRO_CALL_MEMBER(SFXState_Func::playUnitSpeechEffect, this)(1);
                    return;
                }
                if (actionID == 6) {
                    MACRO_CALL_MEMBER(SFXState_Func::playUnitSpeechEffect, this)(7);
                    return;
                }
                if (actionID == 0x10) {
                    MACRO_CALL_MEMBER(SFXState_Func::playUnitSpeechEffect, this)(0x10);
                    return;
                }
                _soundSet = 10;
                break;
            case Map::Units::UT_S_TREBUCHET:
                if (actionID == 0) {
                    MACRO_CALL_MEMBER(SFXState_Func::playUnitSpeechEffect, this)(2);
                    return;
                }
                if (actionID == 0x11) {
                    MACRO_CALL_MEMBER(SFXState_Func::playUnitSpeechEffect, this)(0x11);
                    return;
                }
                if (actionID == 6) {
                    return;
                }
                _soundSet = 10;
                break;
            case Map::Units::UT_S_MANGONEL:
                if (actionID == 0) {
                    MACRO_CALL_MEMBER(SFXState_Func::playUnitSpeechEffect, this)(0);
                    return;
                }
                if (actionID == 0xf) {
                    MACRO_CALL_MEMBER(SFXState_Func::playUnitSpeechEffect, this)(0xf);
                    return;
                }
                if (actionID == 6) {
                    return;
                }
                _soundSet = 10;
                break;
            case Map::Units::UT_S_TOWER:
                if (actionID == 0) {
                    MACRO_CALL_MEMBER(SFXState_Func::playUnitSpeechEffect, this)(3);
                    return;
                }
                if (actionID == 6) {
                    MACRO_CALL_MEMBER(SFXState_Func::playUnitSpeechEffect, this)(8);
                    return;
                }
                _soundSet = 10;
                break;
            case Map::Units::UT_S_BATTERINGRAM:
                if (actionID == 0) {
                    MACRO_CALL_MEMBER(SFXState_Func::playUnitSpeechEffect, this)(4);
                    return;
                }
                if (actionID == 6) {
                    MACRO_CALL_MEMBER(SFXState_Func::playUnitSpeechEffect, this)(9);
                    return;
                }
                if (actionID == 0x13) {
                    MACRO_CALL_MEMBER(SFXState_Func::playUnitSpeechEffect, this)(0x13);
                    return;
                }
                _soundSet = 10;
                break;
            case Map::Units::UT_S_SHIELD:
                if (actionID == 0) {
                    MACRO_CALL_MEMBER(SFXState_Func::playUnitSpeechEffect, this)(5);
                    return;
                }
                if (actionID == 6) {
                    MACRO_CALL_MEMBER(SFXState_Func::playUnitSpeechEffect, this)(10);
                    return;
                }
                _soundSet = 10;
                break;
            case Map::Units::UT_S_BALLISTA:
            case Map::Units::UT_S_FBALLISTA:
                if (actionID == 0) {
                    MACRO_CALL_MEMBER(SFXState_Func::playUnitSpeechEffect, this)(6);
                    return;
                }
                if (actionID == 0x12) {
                    MACRO_CALL_MEMBER(SFXState_Func::playUnitSpeechEffect, this)(0x12);
                    return;
                }
                if (actionID == 6) {
                    return;
                }
                _soundSet = 10;
                break;
            default:
                return;
            }

            if (actionID < 0 || _soundSet >= 18 || actionID >= 42
                || !DAT_SpeechDefinedData::instance.field6_0x41edd4[actionID].numberOfVariations) {
                return;
            }

            int numberOfVariations = DAT_SpeechDefinedData::instance.field6_0x41edd4[actionID].numberOfVariations;
            if (1 < numberOfVariations) {
                /* Calculate action speech variation. */
                variationIndex
                    = DAT_SpeechDefinedData::instance.field6_0x41edd4[actionID].variationCounter[_soundSet]++;
                if (DAT_SpeechDefinedData::instance.field6_0x41edd4[actionID].variationCounter[_soundSet]
                    >= numberOfVariations) {
                    DAT_SpeechDefinedData::instance.field6_0x41edd4[actionID].variationCounter[_soundSet] = 0;
                }
            }
            char _filename[64];
            MACRO_CALL(OS_Func::_sprintf)(_filename, s_fx_speech_s_005a4d68,
                DAT_SpeechDefinedData::instance.field6_0x41edd4[variationIndex + actionID].filenames[_soundSet]);
            if (MACRO_CALL(OS_Func::__stricmp)(_filename, DAT_LastSpeechSFXFilename::instance)
                || (!MACRO_CALL_MEMBER(MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                        MSS::enums::SND_STR_SPEECH_1)
                    && !MACRO_CALL_MEMBER(MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                        MSS::enums::SND_STR_SPEECH_2))) {
                strcpy(DAT_LastSpeechSFXFilename::instance, _filename);
                MACRO_CALL_MEMBER(MSS::SoundSystem_Func::playSoundOnSpeechStream, DAT_SoundSystemState::ptr)(_filename);
            }
        }

    }
}
}
