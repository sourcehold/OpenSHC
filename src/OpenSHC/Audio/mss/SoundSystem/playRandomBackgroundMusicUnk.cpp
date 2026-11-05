#include "../SoundSystem.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Audio/mss/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

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

            BOOLEnum shouldStartNewTrackUnk = TRUE;
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
                shouldStartNewTrackUnk = FALSE;
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
                            DAT_SoundEffectsHelperData1::instance.field_0x70 = 34;
                        } else {
                            int musicSetIndex = DAT_SoundEffectsHelperData1::instance.field_0x70 - 34;
                            int candidateCount = 0;
                            if (musicSetIndex < 0 || 7 < musicSetIndex) {
                                musicSetIndex = 0;
                            }

                            int candidateTrackIndices[20];
                            for (int i = 0; i < 8; ++i) {
                                if (musicSetIndex == i
                                    || DAT_SFXDefinedData::instance.field_0x3a4[musicSetIndex][i] == 0) {
                                    continue;
                                }
                                if (i == 4) {
                                    candidateTrackIndices[candidateCount++] = i;
                                    candidateTrackIndices[candidateCount++] = i;
                                    candidateTrackIndices[candidateCount++] = i;
                                    candidateTrackIndices[candidateCount++] = i;
                                    candidateTrackIndices[candidateCount++] = i;
                                    candidateTrackIndices[candidateCount++] = i;
                                    continue;
                                }
                                int trackMoodUnk = DAT_SFXDefinedData::instance.field_0x4a4[i];
                                int battleMoodState = DAT_SoundEffectsHelperData1::instance.battleMoodState;
                                if ((trackMoodUnk == 1 && trackMoodUnk == battleMoodState)
                                    || (trackMoodUnk == 2 && trackMoodUnk == battleMoodState)) {
                                    continue;
                                }
                                candidateTrackIndices[candidateCount++] = i;
                                if (battleMoodState == 1 && trackMoodUnk == 2) {
                                    candidateTrackIndices[candidateCount++] = i;
                                } else if (battleMoodState == 2 && trackMoodUnk == 1) {
                                    candidateTrackIndices[candidateCount++] = i;
                                }
                            }

                            int sfxIndex;
                            if (candidateCount == 0) {
                                sfxIndex = musicSetIndex + 34;
                            } else {
                                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                                sfxIndex
                                    = candidateTrackIndices[SEC_RNG::instance.currentNumber1 % candidateCount] + 34;
                            }
                            MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                                DAT_SFXDefinedData::instance.Pointers[sfxIndex].musicFile);
                            DAT_SoundEffectsHelperData1::instance.field_0x70 = sfxIndex;
                        }
                        if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                            ++this->streamFlagsUnkAndLoopCount_0x34[0];
                        }
                        return;
                    }
                } else {
                    DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicState = 1;
                    shouldStartNewTrackUnk = FALSE;
                }
            }
            if (this->musicFileHandle_0x178 != -1) {
                DAT_SoundEffectsHelperData1::instance.field_0x54 = TRUE;
                MACRO_CALL(OS_Func::_ucrt_close)(this->musicFileHandle_0x178);
                this->musicFileHandle_0x178 = -1;
                DAT_SoundEffectsHelperData1::instance.field_0x54 = FALSE;
            }
            if (shouldStartNewTrackUnk) {
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
