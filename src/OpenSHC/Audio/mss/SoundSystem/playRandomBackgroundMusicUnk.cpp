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
            if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 != 5) {
                return;
            }
            if (!MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()
                && (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_SCENARIO_DESCRIPTION
                    || DAT_GameCore::instance.field25_0x64 == 0)) {
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 == 5) {
                    DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 = 1;
                }
                return;
            }
            int bVar7 = true;
            if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.troopValueLevel == 0) {
                switch (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.volumeLevel) {
                case 1: {
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker == 0) {
                        DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker = 1;
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.DAT_SFX_Pointers[23].musicFile);
                    } else {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.DAT_SFX_Pointers[23].musicFile);
                        if (DAT_GameSynchronyState::instance.DAT_CurrentGameMode != Game::GM_SOLITARY) {
                            DAT_GameCore::instance.battleLevel2 += 2000;
                        }
                    }
                    if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                        ++this->streamFlagsUnkAndLoopCount_0x34[0];
                    }
                    return;
                }
                case 2: {
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker == 0) {
                        DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker = 1;
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.DAT_SFX_Pointers[25].musicFile);
                    } else {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.DAT_SFX_Pointers[25].musicFile);
                        if (DAT_GameSynchronyState::instance.DAT_CurrentGameMode != Game::GM_SOLITARY) {
                            DAT_GameCore::instance.battleLevel2 += 2000;
                        }
                    }
                    if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                        ++this->streamFlagsUnkAndLoopCount_0x34[0];
                    }
                    return;
                }
                case 5: {
                    ++DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker;
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker > 2) {
                        DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker = 1;
                        if (DAT_GameSynchronyState::instance.DAT_CurrentGameMode != Game::GM_SOLITARY) {
                            DAT_GameCore::instance.battleLevel2 += 2000;
                        }

                    } else if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker != 1) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.DAT_SFX_Pointers[27].musicFile);
                        if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                            ++this->streamFlagsUnkAndLoopCount_0x34[0];
                        }
                        return;
                    }
                    MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                        DAT_SFXDefinedData::instance.DAT_SFX_Pointers[25].musicFile);
                    if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                        ++this->streamFlagsUnkAndLoopCount_0x34[0];
                    }
                    return;
                }
                }
            } else {
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.volumeLevel == 1) {
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field6_0x18 == 0) {
                        if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker == 0) {
                            MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                                DAT_SFXDefinedData::instance.DAT_SFX_Pointers[30].musicFile);
                        } else if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker == 1) {
                            MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                                DAT_SFXDefinedData::instance.DAT_SFX_Pointers[31].musicFile);
                        } else {
                            MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                                DAT_SFXDefinedData::instance.DAT_SFX_Pointers[31].musicFile);
                            if (DAT_GameSynchronyState::instance.DAT_CurrentGameMode != Game::GM_SOLITARY) {
                                DAT_GameCore::instance.battleLevel2 += 5000;
                            }
                        }
                        ++DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker;
                        if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                            ++this->streamFlagsUnkAndLoopCount_0x34[0];
                        }
                        return;
                    } else {
                        DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 = 1;
                        bVar7 = false;
                    }
                } else {
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field6_0x18 == 0) {
                        if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker == 0) {
                            if (this->sec_Section1055_0x3274 != 0x19) {
                                MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                                    DAT_SFXDefinedData::instance.DAT_SFX_Pointers[25].musicFile);
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
                                        DAT_SFXDefinedData::instance.DAT_SFX_Pointers[34].musicFile);
                                }
                                DAT_SoundEffectsHelperData1::instance.field21_0x70 = 34;
                            } else {
                                int iVar5 = DAT_SoundEffectsHelperData1::instance.field21_0x70 + -34;
                                int iVar6 = 0;
                                if (iVar5 < 0 || 7 < iVar5) {
                                    iVar5 = 0;
                                }

                                int aiStack_50[20];
                                for (int i = 0; i < 8; ++i) {
                                    if (iVar5 == i || DAT_SFXDefinedData::instance.field2_0x3a4[iVar5][i] == 0) {
                                        continue;
                                    }
                                    if (i == 4) {
                                        aiStack_50[iVar6++] = 4;
                                        aiStack_50[iVar6++] = 4;
                                        aiStack_50[iVar6++] = 4;
                                        aiStack_50[iVar6++] = 4;
                                        aiStack_50[iVar6++] = 4;
                                        aiStack_50[iVar6++] = 4;
                                        continue;
                                    }
                                    int iVar1 = DAT_SFXDefinedData::instance.field3_0x4a4[i];
                                    int field6_0x34 = DAT_SoundEffectsHelperData1::instance.field6_0x34;
                                    if ((iVar1 == 1 && iVar1 == field6_0x34) || (iVar1 == 2 && iVar1 == field6_0x34)) {
                                        continue;
                                    }
                                    aiStack_50[iVar6++] = i;
                                    if (field6_0x34 == 1 && iVar1 == 2) {
                                        aiStack_50[iVar6++] = i;
                                    } else if (field6_0x34 == 2 && iVar1 == 1) {
                                        aiStack_50[iVar6++] = i;
                                    }
                                }

                                if (iVar6 != 0) {
                                    MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                                    iVar5 = aiStack_50[SEC_RNG::instance.currentNumber1 % iVar6];
                                }
                                MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                                    DAT_SFXDefinedData::instance.DAT_SFX_Pointers[iVar5 + 34].musicFile);
                                DAT_SoundEffectsHelperData1::instance.field21_0x70 = iVar5 + 34;
                            }
                            if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                                ++this->streamFlagsUnkAndLoopCount_0x34[0];
                            }
                            return;
                        }
                    } else {
                        DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 = 1;
                        bVar7 = false;
                    }
                }
            }
            if (this->musicFileHandle_0x178 != -1) {
                DAT_SoundEffectsHelperData1::instance.field14_0x54 = TRUE;
                MACRO_CALL(OS_Func::_ucrt_close)(this->musicFileHandle_0x178);
                this->musicFileHandle_0x178 = -1;
                DAT_SoundEffectsHelperData1::instance.field14_0x54 = FALSE;
            }
            if (bVar7) {
                if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 1) {
                    this->streamFlagsUnkAndLoopCount_0x34[0] &= ~FLAG_SOUND_LOOP_COUNT_FIELD;
                }
                return;
            }
            if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                ++this->streamFlagsUnkAndLoopCount_0x34[0];
            }
            return;
        }

    }
}
}
