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
#include "OpenSHC/Globals/FLOAT_00b986f8.hpp"
#include "OpenSHC/Globals/FLOAT_00b98704.hpp"
#include "OpenSHC/Globals/FLOAT_00b98708.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        struct PriorityListEntry {
            int index;
            int ambientEventCounterRescaled;
        };

        // FUNCTION: STRONGHOLDCRUSADER 0x0044BCE0
        void SFXState::updateAmbientSoundStream()
        {
            int forcedAmbientEventUnk = -1;
            int sortedCount = 0;
            FLOAT_00b98708::instance = (float)timeGetTime();
            if (FLOAT_00b98708::instance == FLOAT_00b98704::instance) {
                FLOAT_00b98704::instance = FLOAT_00b98708::instance - 1.0f;
            }
            float fadeDelta = (FLOAT_00b98708::instance - FLOAT_00b98704::instance) * 0.0625f;
            if (fadeDelta > 20.0) {
                fadeDelta = 20.0;
            }
            FLOAT_00b98704::instance = FLOAT_00b98708::instance;
            if (DAT_SpeechDefinedData::instance.currentStreamID == -1) {
                DAT_SFXFadeDeltaAccumulator::instance += fadeDelta;
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
                    int datum = this->ambientEventCounters[i][0];
                    /* These 10 slots appear to be per-frame sound event accumulators (e.g. how many
                       sword clashes, arrows, fire crackles happened this frame), written by other
                       systems and consumed here. */
                    DAT_SFXAmbientEventCountersRescaled::instance[i] = datum;
                    if (i == 4) {
                        DAT_SFXAmbientEventCountersRescaled::instance[i] = datum >> 2;
                    }
                    if (i == 8) {
                        DAT_SFXAmbientEventCountersRescaled::instance[i] = datum >> 1;
                    }
                    if (i == 2) {
                        DAT_SFXAmbientEventCountersRescaled::instance[i] = datum >> 5;
                    }
                    if (i == 7) {
                        DAT_SFXAmbientEventCountersRescaled::instance[i] = datum >> 4;
                    }
                    if (i == 6) {
                        if (datum > 1) {
                            DAT_SFXAmbientEventCountersRescaled::instance[i] = 100;
                        } else {
                            DAT_SFXAmbientEventCountersRescaled::instance[i] = 0;
                        }
                    }
                    if (DAT_SFXAmbientEventCountersRescaled::instance[i] > 99) {
                        DAT_SFXAmbientEventCountersRescaled::instance[i] = 99;
                        if (i == 6) {
                            DAT_SFXAmbientEventCountersRescaled::instance[i] = 100;
                        }
                        if (i == 5) {
                            DAT_SFXAmbientEventCountersRescaled::instance[i] = 101;
                        }
                    }
                    this->ambientEventCounters[i][0] = 0;
                }
            }
            if (DAT_SFXAmbientEventCountersRescaled::instance[7] <= 3
                || (DAT_SpeechDefinedData::instance.currentStreamID == 6
                    && DAT_SFXFadeState::instance != SFXFS_FADE_OUT)
                || DAT_SFXAmbientEventCountersRescaled::instance[6] == 100) {
                if (DAT_SFXAmbientEventCountersRescaled::instance[8] > 10) {
                    MACRO_CALL_MEMBER(SFX::SFXState_Func::tweakVolume, this)(
                        8, fadeDelta, DAT_SpeechDefinedData::instance.currentStreamID);
                } else {
                    MACRO_CALL_MEMBER(SFX::SFXState_Func::tweakVolume, this)(
                        0, fadeDelta, DAT_SpeechDefinedData::instance.currentStreamID);
                }
            } else if (DAT_SFXAmbientEventCountersRescaled::instance[7] > 28) {
                MACRO_CALL_MEMBER(SFX::SFXState_Func::tweakVolume, this)(
                    7, fadeDelta, DAT_SpeechDefinedData::instance.currentStreamID);
            } else {
                MACRO_CALL_MEMBER(SFX::SFXState_Func::tweakVolume, this)(
                    8, fadeDelta, DAT_SpeechDefinedData::instance.currentStreamID);
            }

            if (DAT_SFXFadeState::instance == SFXFS_IDLE || DAT_SpeechDefinedData::instance.currentStreamID != -1) {
                if (DAT_SFXFadeState::instance == SFXFS_FADE_IN) {
                    FLOAT_00b986f8::instance += fadeDelta + fadeDelta;
                    if (FLOAT_00b986f8::instance > 100.0) {
                        DAT_SFXFadeState::instance = 100;
                    }
                    if (DAT_SpeechDefinedData::instance.currentStreamID == 6) {
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::setStreamAndSampleVolumeUnk,
                            DAT_SoundSystemState::ptr)(MSS::enums::SND_STR_SFX_1Unk,
                            (int)((DAT_SpeechDefinedData::instance.AmbientSounds[4].volumeUnk_0x28
                                          [DAT_SpeechDefinedData::instance.AmbientSounds[4].variationIndex]
                                      * FLOAT_00b986f8::instance)
                                / 100.0));
                    }
                    if (DAT_SpeechDefinedData::instance.currentStreamID == 5) {
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::setStreamAndSampleVolumeUnk,
                            DAT_SoundSystemState::ptr)(MSS::enums::SND_STR_SFX_1Unk,
                            (int)((DAT_SpeechDefinedData::instance.AmbientSounds[3].volumeUnk_0x28
                                          [DAT_SpeechDefinedData::instance.AmbientSounds[3].variationIndex]
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
                    FLOAT_00b986f8::instance -= 2 * fadeDelta;
                    if (FLOAT_00b986f8::instance < 1.0) {
                        FLOAT_00b986f8::instance = 1.0;
                    }
                    if (DAT_SpeechDefinedData::instance.currentStreamID == 6) {
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::setStreamAndSampleVolumeUnk,
                            DAT_SoundSystemState::ptr)(MSS::enums::SND_STR_SFX_1Unk,
                            (int)((DAT_SpeechDefinedData::instance.AmbientSounds[4].volumeUnk_0x28
                                          [DAT_SpeechDefinedData::instance.AmbientSounds[4].variationIndex]
                                      * FLOAT_00b986f8::instance)
                                / 100.0));
                    }
                    if (DAT_SpeechDefinedData::instance.currentStreamID == 5) {
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::setStreamAndSampleVolumeUnk,
                            DAT_SoundSystemState::ptr)(MSS::enums::SND_STR_SFX_1Unk,
                            (int)((DAT_SpeechDefinedData::instance.AmbientSounds[3].volumeUnk_0x28
                                          [DAT_SpeechDefinedData::instance.AmbientSounds[3].variationIndex]
                                      * FLOAT_00b986f8::instance)
                                / 100.0));
                    }
                    if (FLOAT_00b986f8::instance <= 1.0) {
                        DAT_SFXFadeState::instance = SFXFS_IDLE;
                        forcedAmbientEventUnk = DAT_SpeechDefinedData::instance.field_0x49d4b8;
                        MACRO_CALL_MEMBER(MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                            MSS::enums::SND_STR_SFX_1Unk);
                        DAT_SpeechDefinedData::instance.currentStreamID = -1;
                    }
                }
                if (DAT_SpeechDefinedData::instance.currentStreamID != -1) {
                    if (!MACRO_CALL_MEMBER(MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                            MSS::enums::SND_STR_SFX_1Unk)) {
                        DAT_SpeechDefinedData::instance.currentStreamID = -1;
                    } else if (DAT_SpeechDefinedData::instance.currentStreamID != -1
                        && DAT_SpeechDefinedData::instance.currentStreamID != 6
                        && DAT_SpeechDefinedData::instance.currentStreamID != 5) {
                        return;
                    }
                }
            } else {
                DAT_SFXFadeState::instance = SFXFS_IDLE;
            }

            PriorityListEntry prioritySortedList[10];
            for (int ambientEventIndex = 0; ambientEventIndex < 7; ++ambientEventIndex) {
                if (DAT_SFXAmbientEventCountersRescaled::instance[ambientEventIndex] == 0) {
                    continue;
                }
                if (sortedCount == 0) {
                    prioritySortedList[sortedCount].index = ambientEventIndex;
                    prioritySortedList[sortedCount].ambientEventCounterRescaled
                        = DAT_SFXAmbientEventCountersRescaled::instance[ambientEventIndex];
                    ++sortedCount;
                    continue;
                }

                // Reusing i across both loops and duplicating ++sortedCount in the append branch keeps
                // sortedCount in ebp and insertIndex in ecx (matching the original register allocation)
                int insertIndex = sortedCount;
                int i;
                for (i = 0; i < sortedCount; ++i) {
                    if (DAT_SFXAmbientEventCountersRescaled::instance[ambientEventIndex]
                        > prioritySortedList[i].ambientEventCounterRescaled) {
                        insertIndex = i;
                        break;
                    }
                }
                if (insertIndex == sortedCount) {
                    prioritySortedList[sortedCount].index = ambientEventIndex;
                    prioritySortedList[sortedCount].ambientEventCounterRescaled
                        = DAT_SFXAmbientEventCountersRescaled::instance[ambientEventIndex];
                    ++sortedCount;
                    continue;
                }
                for (i = sortedCount - 1; i >= insertIndex; --i) {
                    prioritySortedList[i + 1].index = prioritySortedList[i].index;
                    prioritySortedList[i + 1].ambientEventCounterRescaled
                        = prioritySortedList[i].ambientEventCounterRescaled;
                }
                prioritySortedList[insertIndex].index = ambientEventIndex;
                prioritySortedList[insertIndex].ambientEventCounterRescaled
                    = DAT_SFXAmbientEventCountersRescaled::instance[ambientEventIndex];
                ++sortedCount;
            }

            if ((DAT_SpeechDefinedData::instance.currentStreamID == 6
                    && DAT_SFXAmbientEventCountersRescaled::instance[6] == 0)
                || (DAT_SpeechDefinedData::instance.currentStreamID == 5
                    && DAT_SFXAmbientEventCountersRescaled::instance[5] == 0)) {
                if (DAT_SFXFadeState::instance == SFXFS_FADE_OUT) {
                    return;
                }
                FLOAT_00b986f8::instance = 100.0;
                DAT_SFXFadeState::instance = SFXFS_FADE_OUT;
                DAT_SpeechDefinedData::instance.field_0x49d4b8 = -1;
                return;
            }
            if (sortedCount == 0) {
                return;
            }
            if (DAT_SpeechDefinedData::instance.currentStreamID == 5
                && DAT_SFXAmbientEventCountersRescaled::instance[5] > 8) {
                return;
            }
            int pick = prioritySortedList[0].index;
            if (pick != 6) {
                if (forcedAmbientEventUnk > -1) {
                    if (DAT_SFXAmbientEventCountersRescaled::instance[forcedAmbientEventUnk] > 0
                        && (prioritySortedList[0].ambientEventCounterRescaled
                               - DAT_SFXAmbientEventCountersRescaled::instance[forcedAmbientEventUnk])
                            < 40) {
                        pick = forcedAmbientEventUnk;
                    }
                } else {
                    for (int i = 1; i < sortedCount; ++i) {
                        if (prioritySortedList[0].ambientEventCounterRescaled
                                - prioritySortedList[i].ambientEventCounterRescaled
                            < 20) {
                            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                            if (SEC_RNG::instance.currentNumber1 & 1) {
                                pick = prioritySortedList[i].index;
                            }
                        }
                    }
                }
            }
            if (pick == DAT_SpeechDefinedData::instance.currentStreamID) {
                return;
            }
            if (pick == 4 && DAT_LandscapeState::instance.wind.valueIs2 == 0
                && DAT_LandscapeState::instance.wind.valueIs1 == 0) {
                return;
            }
            if (DAT_SFXFadeDeltaAccumulator::instance < 300.0 && pick != 6 && pick != 5) {
                if (pick != 4) {
                    return;
                }
                if (DAT_SFXFadeDeltaAccumulator::instance < 150.0) {
                    return;
                }
            }
            if (DAT_SpeechDefinedData::instance.currentStreamID != 6
                && DAT_SpeechDefinedData::instance.currentStreamID != 5) {
                switch (pick) {
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
            FLOAT_00b986f8::instance = 100.0;
            DAT_SpeechDefinedData::instance.field_0x49d4b8 = pick;
            DAT_SFXFadeState::instance = SFXFS_FADE_OUT;
        }

    }
}
}
