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
            int iVar1;
            int iVar2;
            BOOLEnum BVar3;
            int iVar4;
            int iVar5;
            int iVar6;
            bool bVar7;
            char* pcVar8;
            int aiStack_50[20];

            if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 != 5) {
                return;
            }
            BVar3 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if ((BVar3 == FALSE)
                && ((DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_SCENARIO_DESCRIPTION
                    || (DAT_GameCore::instance.field25_0x64 == 0)))) {
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 != 5) {
                    return;
                }
                DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 = 1;
                return;
            }
            bVar7 = true;
            if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.troopValueLevel == 0) {
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.volumeLevel == 1) {
                    pcVar8 = DAT_SFXDefinedData::instance.DAT_SFX_Pointers[23].musicFile;
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker != 0) {
                    LAB_0047c00f:
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(pcVar8);
                        if (DAT_GameSynchronyState::instance.DAT_CurrentGameMode != Game::GM_SOLITARY) {
                            DAT_GameCore::instance.battleLevel2 = DAT_GameCore::instance.battleLevel2 + 2000;
                        }
                        goto LAB_0047bfca;
                    }
                    /* sfx file: suspense1b */
                    DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker = 1;
                } else if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.volumeLevel == 2) {
                    pcVar8 = DAT_SFXDefinedData::instance.DAT_SFX_Pointers[25].musicFile;
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker != 0)
                        goto LAB_0047c00f;
                    /* sfx file: suspense2b */
                    DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker = 1;
                } else {
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.volumeLevel != 5)
                        goto LAB_0047c386;
                    DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker
                        = DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker + 1;
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker < 3) {
                        pcVar8 = DAT_SFXDefinedData::instance.DAT_SFX_Pointers[27].musicFile;
                        /* sfx file: drumloop1c */
                        if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker != 1)
                            goto LAB_0047bfc5;
                    } else {
                        DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker = 1;
                        if (DAT_GameSynchronyState::instance.DAT_CurrentGameMode != Game::GM_SOLITARY) {
                            DAT_GameCore::instance.battleLevel2 = DAT_GameCore::instance.battleLevel2 + 2000;
                        }
                    }
                LAB_0047bfbd:
                    /* sfx file: suspense2b */
                    pcVar8 = DAT_SFXDefinedData::instance.DAT_SFX_Pointers[25].musicFile;
                }
            LAB_0047bfc5:
                MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(pcVar8);
                goto LAB_0047bfca;
            }
            if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.volumeLevel == 1) {
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field6_0x18 == 0) {
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker == 0) {

                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.DAT_SFX_Pointers[30].musicFile);
                        DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker
                            = DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker + 1;
                    } else if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker == 1) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.DAT_SFX_Pointers[31].musicFile);
                        DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker
                            = DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker + 1;
                    } else {
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.DAT_SFX_Pointers[31].musicFile);
                        if (DAT_GameSynchronyState::instance.DAT_CurrentGameMode != Game::GM_SOLITARY) {
                            DAT_GameCore::instance.battleLevel2 = DAT_GameCore::instance.battleLevel2 + 5000;
                        }
                        DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker
                            = DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker + 1;
                    }
                    goto LAB_0047bfca;
                }
            LAB_0047c37e:
                bVar7 = false;
                DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 = 1;
            } else {
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field6_0x18 != 0)
                    goto LAB_0047c37e;
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker != 0) {
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker < 2) {
                        DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker
                            = DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker + 1;
                        if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicTracker == 2) {
                            MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                                DAT_SFXDefinedData::instance.DAT_SFX_Pointers[34].musicFile);
                        }
                        DAT_SoundEffectsHelperData1::instance.field21_0x70 = 0x22;
                    } else {
                        iVar5 = DAT_SoundEffectsHelperData1::instance.field21_0x70 + -0x22;
                        iVar6 = 0;
                        if ((iVar5 < 0) || (7 < iVar5)) {
                            iVar5 = 0;
                        }
                        iVar4 = 0;
                        do {
                            if ((iVar5 != iVar4) && (DAT_SFXDefinedData::instance.field2_0x3a4[iVar5][iVar4] != 0)) {
                                if (iVar4 == 4) {
                                    aiStack_50[iVar6] = 4;
                                    aiStack_50[iVar6 + 1] = 4;
                                    aiStack_50[iVar6 + 2] = 4;
                                    aiStack_50[iVar6 + 3] = 4;
                                    aiStack_50[iVar6 + 4] = 4;
                                    iVar6 = iVar6 + 5;
                                    aiStack_50[iVar6] = 4;
                                LAB_0047c1b8:
                                    iVar6 = iVar6 + 1;
                                } else {
                                    iVar1 = DAT_SFXDefinedData::instance.field3_0x4a4[iVar4];
                                    if (((iVar1 != 1) && (iVar1 != 2))
                                        || (DAT_SoundEffectsHelperData1::instance.field6_0x34 != iVar1)) {
                                        aiStack_50[iVar6] = iVar4;
                                        iVar6 = iVar6 + 1;
                                        if (DAT_SoundEffectsHelperData1::instance.field6_0x34 == 1) {
                                            bVar7 = iVar1 == 2;
                                        } else {
                                            if (DAT_SoundEffectsHelperData1::instance.field6_0x34 != 2)
                                                goto LAB_0047c1bb;
                                            bVar7 = iVar1 == 1;
                                        }
                                        if (bVar7) {
                                            aiStack_50[iVar6] = iVar4;
                                            goto LAB_0047c1b8;
                                        }
                                    }
                                }
                            }
                        LAB_0047c1bb:
                            iVar1 = iVar4 + 1;
                            if ((iVar5 != iVar1)
                                && (DAT_SFXDefinedData::instance.field2_0x3a4[iVar5][iVar4 + 1] != 0)) {
                                if (iVar1 == 4) {
                                    aiStack_50[iVar6] = 4;
                                    aiStack_50[iVar6 + 1] = 4;
                                    aiStack_50[iVar6 + 2] = 4;
                                    aiStack_50[iVar6 + 3] = 4;
                                    aiStack_50[iVar6 + 4] = 4;
                                    iVar6 = iVar6 + 5;
                                    aiStack_50[iVar6] = 4;
                                LAB_0047c234:
                                    iVar6 = iVar6 + 1;
                                } else {
                                    iVar2 = DAT_SFXDefinedData::instance.field3_0x4a4[iVar4 + 1];
                                    if (((iVar2 != 1) && (iVar2 != 2))
                                        || (DAT_SoundEffectsHelperData1::instance.field6_0x34 != iVar2)) {
                                        aiStack_50[iVar6] = iVar1;
                                        iVar6 = iVar6 + 1;
                                        if (DAT_SoundEffectsHelperData1::instance.field6_0x34 == 1) {
                                            bVar7 = iVar2 == 2;
                                        } else {
                                            if (DAT_SoundEffectsHelperData1::instance.field6_0x34 != 2)
                                                goto LAB_0047c237;
                                            bVar7 = iVar2 == 1;
                                        }
                                        if (bVar7) {
                                            aiStack_50[iVar6] = iVar1;
                                            goto LAB_0047c234;
                                        }
                                    }
                                }
                            }
                        LAB_0047c237:
                            iVar1 = iVar4 + 2;
                            if ((iVar5 != iVar1)
                                && (DAT_SFXDefinedData::instance.field2_0x3a4[iVar5][iVar4 + 2] != 0)) {
                                if (iVar1 == 4) {
                                    aiStack_50[iVar6] = 4;
                                    aiStack_50[iVar6 + 1] = 4;
                                    aiStack_50[iVar6 + 2] = 4;
                                    aiStack_50[iVar6 + 3] = 4;
                                    aiStack_50[iVar6 + 4] = 4;
                                    iVar6 = iVar6 + 5;
                                    aiStack_50[iVar6] = 4;
                                LAB_0047c2b0:
                                    iVar6 = iVar6 + 1;
                                } else {
                                    iVar2 = DAT_SFXDefinedData::instance.field3_0x4a4[iVar4 + 2];
                                    if (((iVar2 != 1) && (iVar2 != 2))
                                        || (DAT_SoundEffectsHelperData1::instance.field6_0x34 != iVar2)) {
                                        aiStack_50[iVar6] = iVar1;
                                        iVar6 = iVar6 + 1;
                                        if (DAT_SoundEffectsHelperData1::instance.field6_0x34 == 1) {
                                            bVar7 = iVar2 == 2;
                                        } else {
                                            if (DAT_SoundEffectsHelperData1::instance.field6_0x34 != 2)
                                                goto LAB_0047c2b3;
                                            bVar7 = iVar2 == 1;
                                        }
                                        if (bVar7) {
                                            aiStack_50[iVar6] = iVar1;
                                            goto LAB_0047c2b0;
                                        }
                                    }
                                }
                            }
                        LAB_0047c2b3:
                            iVar1 = iVar4 + 3;
                            if ((iVar5 != iVar1)
                                && (DAT_SFXDefinedData::instance.field2_0x3a4[iVar5][iVar4 + 3] != 0)) {
                                if (iVar1 == 4) {
                                    aiStack_50[iVar6] = 4;
                                    aiStack_50[iVar6 + 1] = 4;
                                    aiStack_50[iVar6 + 2] = 4;
                                    aiStack_50[iVar6 + 3] = 4;
                                    aiStack_50[iVar6 + 4] = 4;
                                    iVar6 = iVar6 + 5;
                                    aiStack_50[iVar6] = 4;
                                LAB_0047c32c:
                                    iVar6 = iVar6 + 1;
                                } else {
                                    iVar2 = DAT_SFXDefinedData::instance.field3_0x4a4[iVar4 + 3];
                                    if (((iVar2 != 1) && (iVar2 != 2))
                                        || (DAT_SoundEffectsHelperData1::instance.field6_0x34 != iVar2)) {
                                        aiStack_50[iVar6] = iVar1;
                                        iVar6 = iVar6 + 1;
                                        if (DAT_SoundEffectsHelperData1::instance.field6_0x34 == 1) {
                                            bVar7 = iVar2 == 2;
                                        } else {
                                            if (DAT_SoundEffectsHelperData1::instance.field6_0x34 != 2)
                                                goto LAB_0047c32f;
                                            bVar7 = iVar2 == 1;
                                        }
                                        if (bVar7) {
                                            aiStack_50[iVar6] = iVar1;
                                            goto LAB_0047c32c;
                                        }
                                    }
                                }
                            }
                        LAB_0047c32f:
                            iVar4 = iVar4 + 4;
                        } while (iVar4 < 8);
                        if (iVar6 != 0) {
                            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                            iVar5 = aiStack_50[SEC_RNG::instance.currentNumber1 % iVar6];
                        }
                        MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                            DAT_SFXDefinedData::instance.DAT_SFX_Pointers[iVar5 + 34].musicFile);
                        DAT_SoundEffectsHelperData1::instance.field21_0x70 = iVar5 + 34;
                    }
                    goto LAB_0047bfca;
                }
                if (this->sec_Section1055_0x3274 != 0x19)
                    goto LAB_0047bfbd;
            }
        LAB_0047c386:
            if (this->musicFileHandle_0x178 != -1) {
                DAT_SoundEffectsHelperData1::instance.field14_0x54 = TRUE;
                MACRO_CALL(OS_Func::_ucrt_close)(this->musicFileHandle_0x178);
                this->musicFileHandle_0x178 = -1;
                DAT_SoundEffectsHelperData1::instance.field14_0x54 = FALSE;
            }
            if (bVar7) {
                if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) != 1) {
                    return;
                }
                this->streamFlagsUnkAndLoopCount_0x34[0]
                    = this->streamFlagsUnkAndLoopCount_0x34[0] & ~FLAG_SOUND_LOOP_COUNT_FIELD;
                return;
            }
        LAB_0047bfca:
            if ((this->streamFlagsUnkAndLoopCount_0x34[0] & FLAG_SOUND_LOOP_COUNT_FIELD) == 0) {
                this->streamFlagsUnkAndLoopCount_0x34[0] = this->streamFlagsUnkAndLoopCount_0x34[0] + 1;
            }
            return;
        }

    }
}
}
