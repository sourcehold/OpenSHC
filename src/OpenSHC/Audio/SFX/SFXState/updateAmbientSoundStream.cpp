#include "../SFXState.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_SFXAmbientEventCountersRescaled.hpp"
#include "OpenSHC/Globals/DAT_SFXFadeDeltaAccumulator.hpp"
#include "OpenSHC/Globals/DAT_SFXFadeState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_SpeechDefinedData.hpp"
#include "OpenSHC/Globals/DWORD_00b98708.hpp"
#include "OpenSHC/Globals/FLOAT_00b986f8.hpp"
#include "OpenSHC/Globals/FLOAT_00b98704.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // TODO: There is a similar SFX function: take structure from there

        // FUNCTION: STRONGHOLDCRUSADER 0x0044BCE0
        void SFXState::updateAmbientSoundStream()
        {
            int local_54 = -1;
            int iVar8 = 0;
            DWORD_00b98708::instance = (float)timeGetTime();
            if (DWORD_00b98708::instance == FLOAT_00b98704::instance) {
                FLOAT_00b98704::instance = DWORD_00b98708::instance - 1.0f;
            }
            float _fadeDelta = (DWORD_00b98708::instance - FLOAT_00b98704::instance) * 0.0625f;
            if (_fadeDelta > 20.0) {
                _fadeDelta = 20.0;
            }
            FLOAT_00b98704::instance = DWORD_00b98708::instance;
            if (DAT_SpeechDefinedData::instance.currentStreamID == -1) {
                DAT_SFXFadeDeltaAccumulator::instance += _fadeDelta;
            } else {
                DAT_SFXFadeDeltaAccumulator::instance = 0.0;
            }
            if (!MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
                for (int i = 0; i < 10; ++i) {
                    DAT_SFXAmbientEventCountersRescaled::instance[i] = 0;
                    this->ambientEventCounters[i][0] = 0;
                }
                MACRO_CALL_MEMBER(MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    MSS::enums::SND_STR_SFX_1Unk);
                DAT_SFXFadeState::instance = SFXFS_IDLE;
                DAT_SpeechDefinedData::instance.currentStreamID = -1;
            } else {
                for (int i = 0; i < 10; ++i) {
                    int _datum = this->ambientEventCounters[i][0];
                    /* These 10 slots appear to be per-frame sound event accumulators (e.g. how many
                       sword clashes, arrows, fire crackles happened this frame), written by other
                       systems and consumed here. */
                    DAT_SFXAmbientEventCountersRescaled::instance[i] = _datum;
                    if (i == 4) {
                        DAT_SFXAmbientEventCountersRescaled::instance[4] = _datum >> 2;
                    } else if (i == 8) {
                        DAT_SFXAmbientEventCountersRescaled::instance[8] = _datum >> 1;
                    } else if (i == 2) {
                        DAT_SFXAmbientEventCountersRescaled::instance[2] = _datum >> 5;
                    } else if (i == 7) {
                        DAT_SFXAmbientEventCountersRescaled::instance[7] = _datum >> 4;
                    } else if (i == 6) {
                        DAT_SFXAmbientEventCountersRescaled::instance[6] = (_datum > 1) ? 100 : 0;
                    }
                    if (99 < DAT_SFXAmbientEventCountersRescaled::instance[i]) {
                        DAT_SFXAmbientEventCountersRescaled::instance[i] = 99;
                        if (i == 6) {
                            DAT_SFXAmbientEventCountersRescaled::instance[6] = 100;
                        } else if (i == 5) {
                            DAT_SFXAmbientEventCountersRescaled::instance[5] = 101;
                        }
                    }
                    this->ambientEventCounters[i][0] = 0;
                }
            }
            if (DAT_SFXAmbientEventCountersRescaled::instance[7] <= 3
                || (DAT_SpeechDefinedData::instance.currentStreamID == 6
                    && DAT_SFXFadeState::instance != SFXFS_FADE_OUT)
                || DAT_SFXAmbientEventCountersRescaled::instance[6] == 100) {
                if (10 < DAT_SFXAmbientEventCountersRescaled::instance[8]) {
                    MACRO_CALL_MEMBER(SFX::SFXState_Func::tweakVolume, this)(
                        8, _fadeDelta, DAT_SpeechDefinedData::instance.currentStreamID);
                } else {
                    MACRO_CALL_MEMBER(SFX::SFXState_Func::tweakVolume, this)(
                        0, _fadeDelta, DAT_SpeechDefinedData::instance.currentStreamID);
                }
            } else if (DAT_SFXAmbientEventCountersRescaled::instance[7] < 29) {
                MACRO_CALL_MEMBER(SFX::SFXState_Func::tweakVolume, this)(
                    8, _fadeDelta, DAT_SpeechDefinedData::instance.currentStreamID);
            } else {
                MACRO_CALL_MEMBER(SFX::SFXState_Func::tweakVolume, this)(
                    7, _fadeDelta, DAT_SpeechDefinedData::instance.currentStreamID);
            }

            if (DAT_SFXFadeState::instance == SFXFS_IDLE || DAT_SpeechDefinedData::instance.currentStreamID != -1) {
                if (DAT_SFXFadeState::instance == SFXFS_FADE_IN) {
                    FLOAT_00b986f8::instance += _fadeDelta + _fadeDelta;
                    if (100.0 < FLOAT_00b986f8::instance) {
                        DAT_SFXFadeState::instance = 100;
                    }
                    if (DAT_SpeechDefinedData::instance.currentStreamID == 6) {
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::setStreamAndSampleVolumeUnk,
                            DAT_SoundSystemState::ptr)(MSS::enums::SND_STR_SFX_1Unk,
                            (int)((DAT_SpeechDefinedData::instance.field5_0x41eb04[4].volumeUnk_0x28
                                          [DAT_SpeechDefinedData::instance.field5_0x41eb04[4].field3_0x44]
                                      * FLOAT_00b986f8::instance)
                                / 100.0));
                    }
                    if (DAT_SpeechDefinedData::instance.currentStreamID == 5) {
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::setStreamAndSampleVolumeUnk,
                            DAT_SoundSystemState::ptr)(MSS::enums::SND_STR_SFX_1Unk,
                            (int)((DAT_SpeechDefinedData::instance.field5_0x41eb04[3].volumeUnk_0x28
                                          [DAT_SpeechDefinedData::instance.field5_0x41eb04[3].field3_0x44]
                                      * FLOAT_00b986f8::instance)
                                / 100.0));
                    }
                    if (!(FLOAT_00b986f8::instance >= 100.0f)) {
                        return;
                    }
                    DAT_SFXFadeState::instance = SFXFS_IDLE;
                    return;
                }
                if (DAT_SFXFadeState::instance == SFXFS_FADE_OUT) {
                    FLOAT_00b986f8::instance -= 2 * _fadeDelta;
                    if (FLOAT_00b986f8::instance < 1.0) {
                        FLOAT_00b986f8::instance = 1.0;
                    }
                    if (DAT_SpeechDefinedData::instance.currentStreamID == 6) {
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::setStreamAndSampleVolumeUnk,
                            DAT_SoundSystemState::ptr)(MSS::enums::SND_STR_SFX_1Unk,
                            (int)((DAT_SpeechDefinedData::instance.field5_0x41eb04[4].volumeUnk_0x28
                                          [DAT_SpeechDefinedData::instance.field5_0x41eb04[4].field3_0x44]
                                      * FLOAT_00b986f8::instance)
                                / 100.0));
                    }
                    if (DAT_SpeechDefinedData::instance.currentStreamID == 5) {
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::setStreamAndSampleVolumeUnk,
                            DAT_SoundSystemState::ptr)(MSS::enums::SND_STR_SFX_1Unk,
                            (int)((DAT_SpeechDefinedData::instance.field5_0x41eb04[3].volumeUnk_0x28
                                          [DAT_SpeechDefinedData::instance.field5_0x41eb04[3].field3_0x44]
                                      * FLOAT_00b986f8::instance)
                                / 100.0));
                    }
                    if (FLOAT_00b986f8::instance <= 1.0) {
                        local_54 = DAT_SpeechDefinedData::instance.field11_0x49d4b8;
                        DAT_SFXFadeState::instance = SFXFS_IDLE;
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                            MSS::enums::SND_STR_SFX_1Unk);
                        DAT_SpeechDefinedData::instance.currentStreamID = -1;
                    }
                }
                if (DAT_SpeechDefinedData::instance.currentStreamID != -1) {
                    if (!MACRO_CALL_MEMBER(MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                            MSS::enums::SND_STR_SFX_1Unk)) {
                        DAT_SpeechDefinedData::instance.currentStreamID = -1;
                    } else {
                        if (DAT_SpeechDefinedData::instance.currentStreamID != -1
                            && DAT_SpeechDefinedData::instance.currentStreamID != 6
                            && DAT_SpeechDefinedData::instance.currentStreamID != 5) {
                            return;
                        }
                    }
                }
            } else {
                DAT_SFXFadeState::instance = SFXFS_IDLE;
            }

            int _prioritySortedList[20];
            for (int iVar9 = 0; iVar9 < 7; ++iVar9) {
                int iVar2 = DAT_SFXAmbientEventCountersRescaled::instance[iVar9];
                if (iVar2 == 0) {
                    continue;
                }
                if (iVar8 == 0) {
                    _prioritySortedList[0] = iVar9;
                    _prioritySortedList[1] = iVar2;
                    iVar8 = 1;
                    continue;
                }

                int iVar7 = 0;
                if (iVar8 > 0) {
                    while (iVar2 <= _prioritySortedList[iVar7 * 2 + 1]) {
                        ++iVar7;
                        if (iVar7 < iVar8) {
                            continue;
                        }
                        _prioritySortedList[iVar8 * 2] = iVar9;
                        _prioritySortedList[iVar8 * 2 + 1] = iVar2;
                        ++iVar8;
                        goto outerLoopEnd;
                    }
                }

                if (iVar7 == iVar8) {
                    _prioritySortedList[iVar8 * 2] = iVar9;
                    _prioritySortedList[iVar8 * 2 + 1] = iVar2;
                    ++iVar8;
                    continue;
                }

                int iVar3 = iVar8;
                while (iVar3 = iVar3 + -1, iVar3 >= iVar7) {
                    _prioritySortedList[iVar3 * 2 + 2] = _prioritySortedList[iVar3 * 2];
                    _prioritySortedList[iVar3 * 2 + 3] = _prioritySortedList[iVar3 * 2 + 1];
                }
                _prioritySortedList[iVar7 * 2] = iVar9;
                _prioritySortedList[iVar7 * 2 + 1] = iVar2;
                ++iVar8;
            outerLoopEnd:;
            }

            int iVar9 = DAT_SFXAmbientEventCountersRescaled::instance[6];
            if (((DAT_SpeechDefinedData::instance.currentStreamID == 6)
                    || (iVar9 = DAT_SFXAmbientEventCountersRescaled::instance[5],
                        DAT_SpeechDefinedData::instance.currentStreamID == 5))
                && (iVar9 == 0)) {
                if (DAT_SFXFadeState::instance == SFXFS_FADE_OUT) {
                    return;
                }
                FLOAT_00b986f8::instance = 100.0;
                DAT_SFXFadeState::instance = SFXFS_FADE_OUT;
                DAT_SpeechDefinedData::instance.field11_0x49d4b8 = 0xffffffff;
                return;
            }
            if (iVar8 == 0) {
                return;
            }
            if ((DAT_SpeechDefinedData::instance.currentStreamID == 5)
                && (8 < DAT_SFXAmbientEventCountersRescaled::instance[5])) {
                return;
            }
            int _pick = _prioritySortedList[0];
            if (_prioritySortedList[0] != 6) {
                if (local_54 < 0) {
                    iVar9 = 1;
                    if (1 < iVar8) {
                        do {
                            if ((_prioritySortedList[1] - _prioritySortedList[iVar9 * 2 + 1] < 0x14)
                                && (MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)(),
                                    ((byte)SEC_RNG::instance.currentNumber1 & 1) != 0)) {
                                _pick = _prioritySortedList[iVar9 * 2];
                            }
                            iVar9 = iVar9 + 1;
                        } while (iVar9 < iVar8);
                    }
                } else if ((0 < DAT_SFXAmbientEventCountersRescaled::instance[local_54])
                    && (_prioritySortedList[1] - DAT_SFXAmbientEventCountersRescaled::instance[local_54] < 0x28)) {
                    _pick = local_54;
                }
            }
            if (_pick == DAT_SpeechDefinedData::instance.currentStreamID) {
                return;
            }
            if (_pick == 4 && DAT_LandscapeState::instance.wind.valueIs2 == 0
                && DAT_LandscapeState::instance.wind.valueIs1 == 0) {}
            if (DAT_SFXFadeDeltaAccumulator::instance < 300.0 && _pick != 6 && _pick != 5) {
                if (_pick != 4) {
                    return;
                }
                if (DAT_SFXFadeDeltaAccumulator::instance < 150.0) {
                    return;
                }
            }
            if (DAT_SpeechDefinedData::instance.currentStreamID != 6
                && DAT_SpeechDefinedData::instance.currentStreamID != 5) {
                switch (_pick) {
                case 4:
                    if (DAT_LandscapeState::instance.wind.valueIs2 != 0) {
                        MACRO_CALL_MEMBER(SFX::SFXState_Func::playAmbientSoundStreamUnk, this)(ASFXT_WIND_1);
                    } else if (DAT_LandscapeState::instance.wind.valueIs1 != 0) {
                        MACRO_CALL_MEMBER(SFX::SFXState_Func::playAmbientSoundStreamUnk, this)(ASFXT_WIND_0);
                    }
                    DAT_SpeechDefinedData::instance.currentStreamID = 4;
                    return;
                case 2:
                    MACRO_CALL_MEMBER(SFX::SFXState_Func::playAmbientSoundStreamUnk, this)(ASFXT_UNKNOWN);
                    DAT_SpeechDefinedData::instance.currentStreamID = 2;
                    return;
                case 5:
                    MACRO_CALL_MEMBER(SFX::SFXState_Func::playAmbientSoundStreamUnk, this)(ASFXT_HEAVY);
                    DAT_SpeechDefinedData::instance.currentStreamID = 5;
                    FLOAT_00b986f8::instance = 1.0;
                    DAT_SFXFadeState::instance = SFXFS_FADE_IN;
                    DAT_SoundSystemState::instance.streamFileVolumeNextUnk_0x48[1] = 1;
                    return;
                case 6:
                    MACRO_CALL_MEMBER(SFX::SFXState_Func::playAmbientSoundStreamUnk, this)(ASFXT_BATTLE_OR_INTENSE);
                    DAT_SpeechDefinedData::instance.currentStreamID = 6;
                    FLOAT_00b986f8::instance = 1.0;
                    DAT_SFXFadeState::instance = SFXFS_FADE_IN;
                    DAT_SoundSystemState::instance.streamFileVolumeNextUnk_0x48[1] = 1;
                    return;
                default:
                    return;
                }
            }
            if (DAT_SFXFadeState::instance == SFXFS_FADE_OUT) {
                return;
            }
            DAT_SpeechDefinedData::instance.field11_0x49d4b8 = _pick;
            FLOAT_00b986f8::instance = 100.0;
            DAT_SFXFadeState::instance = SFXFS_FADE_OUT;
            return;
        }

    }
}
}
