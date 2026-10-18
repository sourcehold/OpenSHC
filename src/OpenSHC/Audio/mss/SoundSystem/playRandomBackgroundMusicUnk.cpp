#include "../SoundSystem.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Audio/mss/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0047BF20
        void SoundSystem::playRandomBackgroundMusicUnk()
        {
            if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicState != 5) {
                return;
            }

            // NOTE: Current state has a mismatch with the bytes of this condition: The following early return is
            //   directly placed under it. So resolve this, one can move the first early return inside this if as or,
            //   which will produce the proper code for this position, but messes with the rest of the function in such
            //   a way that is produces a lower match. Due to the amount of time already spend, the function is kept in
            //   this state and maybe one day tackled again when the last once are cleaned up.
            if (!MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()
                && (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_SCENARIO_DESCRIPTION
                    || !DAT_GameCore::instance.gameSuspended)) {
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicState == 5) {
                    DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicState = 1;
                }
                return;
            }

            BOOLEnum shouldClearLoopFlag = TRUE;
            if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.troopValueLevel == 0) {
                switch (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.volumeLevel) {
                case 1:
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker == 0) {
                        DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker = 1;
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[23].musicFile);
                    } else {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[23].musicFile);
                        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                            DAT_GameCore::instance.battleLevel2 += 2000;
                        }
                    }
                    if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                        ++this->streamFlagsUnkAndLoopCount_0x34[0];
                    }
                    return;

                case 2:
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker == 0) {
                        DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker = 1;
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[25].musicFile);
                    } else {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[25].musicFile);
                        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                            DAT_GameCore::instance.battleLevel2 += 2000;
                        }
                    }
                    if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                        ++this->streamFlagsUnkAndLoopCount_0x34[0];
                    }
                    return;

                case 5:
                    ++DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker;
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker > 2) {
                        DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker = 1;
                        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                            DAT_GameCore::instance.battleLevel2 += 2000;
                        }
                    }
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker == 1) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[25].musicFile);
                        if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                            ++this->streamFlagsUnkAndLoopCount_0x34[0];
                        }
                    } else {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[27].musicFile);
                        if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                            ++this->streamFlagsUnkAndLoopCount_0x34[0];
                        }
                    }
                    return;
                }
            } else if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.volumeLevel == 1) {
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleEndHandled == 0) {
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker == 0) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[30].musicFile);
                    } else if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker == 1) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[31].musicFile);
                    } else {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.Pointers[31].musicFile);
                        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                            DAT_GameCore::instance.battleLevel2 += 5000;
                        }
                    }
                    ++DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker;
                    if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                        ++this->streamFlagsUnkAndLoopCount_0x34[0];
                    }
                    return;
                }
                DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicState = 1;
                shouldClearLoopFlag = FALSE;
            } else {
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.battleEndHandled == 0) {
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker == 0) {
                        if (this->sec_Section1055_0x3274 != 25) {
                            MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                                DAT_SFXDefinedData::instance.Pointers[25].musicFile);
                            if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                                ++this->streamFlagsUnkAndLoopCount_0x34[0];
                            }
                            return;
                        }
                    } else {
                        if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker < 2) {
                            ++DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker;
                            if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker == 2) {
                                MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                                    DAT_SFXDefinedData::instance.Pointers[34].musicFile);
                            }
                            DAT_SoundEffectsHelperData1::instance.field21_0x70 = 34;
                        } else {
                            int currentTrackIndex = DAT_SoundEffectsHelperData1::instance.field21_0x70 + -34;
                            int candidateCount = 0;
                            if (currentTrackIndex < 0 || 7 < currentTrackIndex) {
                                currentTrackIndex = 0;
                            }

                            int candidateTracks[20];
                            for (int i = 0; i < 8; ++i) {
                                if (currentTrackIndex == i
                                    || DAT_SFXDefinedData::instance.field2_0x3a4[currentTrackIndex][i] == 0) {
                                    continue;
                                }
                                if (i == 4) {
                                    // Track 4 is weighted six times. A loop over the six stores took the match
                                    // from 97.5% to 50%, so the original really is straight-line code here.
                                    candidateTracks[candidateCount++] = i;
                                    candidateTracks[candidateCount++] = i;
                                    candidateTracks[candidateCount++] = i;
                                    candidateTracks[candidateCount++] = i;
                                    candidateTracks[candidateCount++] = i;
                                    candidateTracks[candidateCount++] = i;
                                    continue;
                                }
                                int trackMoodState = DAT_SFXDefinedData::instance.field3_0x4a4[i];
                                int const battleMoodState = DAT_SoundEffectsHelperData1::instance.battleMoodState;
                                if ((trackMoodState == 1 && trackMoodState == battleMoodState)
                                    || (trackMoodState == 2 && trackMoodState == battleMoodState)) {
                                    continue;
                                }
                                candidateTracks[candidateCount++] = i;
                                if (battleMoodState == 1 && trackMoodState == 2) {
                                    candidateTracks[candidateCount++] = i;
                                } else if (battleMoodState == 2 && trackMoodState == 1) {
                                    candidateTracks[candidateCount++] = i;
                                }
                            }

                            int sfxIndex;
                            if (candidateCount == 0) {
                                sfxIndex = currentTrackIndex + 34;
                            } else {
                                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                                sfxIndex = candidateTracks[SEC_RNG::instance.currentNumber1 % candidateCount] + 34;
                            }
                            MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                                DAT_SFXDefinedData::instance.Pointers[sfxIndex].musicFile);
                            DAT_SoundEffectsHelperData1::instance.field21_0x70 = sfxIndex;
                        }
                        if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                            ++this->streamFlagsUnkAndLoopCount_0x34[0];
                        }
                        return;
                    }
                } else {
                    DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicState = 1;
                    shouldClearLoopFlag = FALSE;
                }
            }
            if (this->musicFileHandle_0x178 != -1) {
                DAT_SoundEffectsHelperData1::instance.field14_0x54 = TRUE;
                MACRO_CALL(OS_Func::_ucrt_close)(this->musicFileHandle_0x178);
                this->musicFileHandle_0x178 = -1;
                DAT_SoundEffectsHelperData1::instance.field14_0x54 = FALSE;
            }
            if (shouldClearLoopFlag) {
                if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 1) {
                    this->streamFlagsUnkAndLoopCount_0x34[0] &= ~FLAG_SOUND_LOOP_COUNT_FIELD;
                }
            } else {
                if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                    ++this->streamFlagsUnkAndLoopCount_0x34[0];
                }
            }
        }

    }
}
}
