#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B890
        void SoundSystem::playRandomAmbientMusic()
        {
            if (DAT_GameSynchronyState::instance.DAT_CurrentGameMode == Game::GM_SOLITARY
                && MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()
                && DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campgroundBuildingID
                        <= 0
                    || DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .lordID
                        <= 0) {
                    DAT_TroopValueState::instance.attackInfo.field128079_0x469dc = 0;
                } else {
                    if (0 < DAT_TroopValueState::instance.attackInfo.field128080_0x469e0
                        && DAT_TroopValueState::instance.attackInfo.field128078_0x469d8 == 1) {
                        DAT_TroopValueState::instance.attackInfo.field128078_0x469d8 = 2;
                        /* "the enemy has breached the walls!" */
                        MACRO_CALL_MEMBER(SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            s_General_Warning15_wav_005a6ce4);
                    }
                    if (DAT_TroopValueState::instance.attackInfo.field128079_0x469dc != 0) {
                        DAT_TroopValueState::instance.attackInfo.field128079_0x469dc = 0;
                        if (90000 < timeGetTime()
                                - DAT_SoundEffectsHelperData1::instance
                                    .DAT_enemyInsideCastleSoundWarningCooldownTimer) {
                            /* the enemy are inside the castle! */
                            MACRO_CALL_MEMBER(SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                s_General_Warning4_wav_005a6ccc);
                            DAT_SoundEffectsHelperData1::instance.DAT_enemyInsideCastleSoundWarningCooldownTimer
                                = timeGetTime();
                        }
                    }
                }
            }
            if (200 < DAT_GameCore::instance.mapTimeInTicks - DAT_GameCore::instance.someSoundMatchTime_1) {
                DAT_GameCore::instance.battleLevel = DAT_GameCore::instance.cowPoisonTrackerUnk;
                DAT_GameCore::instance.someSoundMatchTime_1 = DAT_GameCore::instance.mapTimeInTicks;
                DAT_GameCore::instance.cowPoisonTrackerUnk = 0;
            }
            if (0 < this->sec_Section1055_0x3274 && this->mbr_0x154 != 0) {
                if (this->mbr_0x154 == 2) {
                    unsigned int const transitionPercent = (timeGetTime() - this->someSoundTime_0x158) / 10;
                    if (transitionPercent >= 100) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::stopMusicPlayback, this)();
                        this->sec_Section1055_0x3274 = 0;
                        this->mbr_0x154 = 0;
                    } else {
                        MACRO_CALL_MEMBER(SoundSystem_Func::setStreamAndSampleVolumeUnk, this)(enums::SND_STR_MUSIC,
                            ((100 - transitionPercent) * this->streamFileVolumeNextUnk_0x48[0]) / 100);
                        return;
                    }
                }
                if (this->mbr_0x154 == 1) {
                    unsigned int const transitionPercent = (timeGetTime() - this->someSoundTime_0x158) / 200;
                    if (transitionPercent >= 100) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::setStreamAndSampleVolumeUnk, this)(
                            enums::SND_STR_MUSIC, (100 * this->streamFileVolumeNextUnk_0x48[0]) / 100);
                        this->mbr_0x154 = 0;
                    } else {
                        MACRO_CALL_MEMBER(SoundSystem_Func::setStreamAndSampleVolumeUnk, this)(
                            enums::SND_STR_MUSIC, (transitionPercent * this->streamFileVolumeNextUnk_0x48[0]) / 100);
                        return;
                    }
                }
            }
            if (this->currentSoundID_0x3278 != this->sec_Section1055_0x3274 && 0 < this->currentSoundID_0x3278) {
                if (this->mbr_0x3280 == 1) {
                    this->mbr_0x154 = 1;
                    this->someSoundTime_0x158 = timeGetTime();
                    this->mbr_0x3280 = 0;
                }
                if (DAT_SFXDefinedData::instance.DAT_SFX_Pointers[this->currentSoundID_0x3278].unknownFlag_0x4) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::playOrSetupMusicUnk, this)(
                        DAT_SFXDefinedData::instance.DAT_SFX_Pointers[this->currentSoundID_0x3278].musicFile,
                        this->currentSoundIDVolumeUnk_0x327c);
                    this->sec_Section1055_0x3274 = this->currentSoundID_0x3278;
                } else {
                    MACRO_CALL_MEMBER(SoundSystem_Func::playOrEndMusicUnk, this)(
                        DAT_SFXDefinedData::instance.DAT_SFX_Pointers[this->currentSoundID_0x3278].musicFile,
                        this->currentSoundIDVolumeUnk_0x327c);
                    this->sec_Section1055_0x3274 = this->currentSoundID_0x3278;
                    this->currentSoundID_0x3278 = 0;
                }
            }

            if ((MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()
                    || (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_SCENARIO_DESCRIPTION
                        && DAT_GameCore::instance.field25_0x64 != 0))
                && DAT_GameCore::instance.gameMode_2 != Game::GM_CRUSADER_TUTORIAL
                && DAT_GameSynchronyState::instance.DAT_CurrentGameMode == Game::GM_SOLITARY) {
                if (DAT_TroopValueState::instance.attackInfo.field105458_0x25b00 != 0
                    && 0 < DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .totalEnemyUnitsCount) {
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field7_0x1c) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::playRandomMusic02, this)(2);
                    } else {
                        MACRO_CALL_MEMBER(SoundSystem_Func::playRandomMusic02, this)(1);
                    }
                    DAT_TroopValueState::instance.attackInfo.field105458_0x25b00 = 0;
                }
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 == 5) {
                    if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .totalEnemyUnitsCount
                            == 0)
                        && (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field7_0x1c == 0)) {
                        MACRO_CALL_MEMBER(
                            SoundSystem_Func::handleBattleEndMusicTransition, DAT_SoundSystemState::ptr)();
                    }
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.troopValueLevel != 0
                        && DAT_SoundEffectsHelperData1::instance.SEC_Section1079.volumeLevel == 2
                        && 30000 < timeGetTime() - DAT_SoundEffectsHelperData1::instance.DAT_SomeSoundTime2) {
                        DAT_SoundEffectsHelperData1::instance.DAT_SomeSoundTime2 = timeGetTime();
                        MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::recountTotalTroopValue, DAT_TroopValueState::ptr)();

                        int const currentPlayerTotalTroopValue
                            = DAT_TroopValueState::instance.attackInfo
                                  .playerTotalTroopValueArray[DAT_GameSynchronyState::instance.currentPlayerSlotID];

                        int enemyPlayerTotalTroopValue = 0;
                        for (int i = 1; i < 9; ++i) {
                            if (DAT_GameSynchronyState::instance.currentPlayerSlotID == i) {
                                continue;
                            }
                            enemyPlayerTotalTroopValue
                                += DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[i];
                        }

                        if (DAT_SoundEffectsHelperData1::instance.field12_0x4c < 1) {
                            DAT_SoundEffectsHelperData1::instance.field12_0x4c = 1;
                        }
                        int somePercentage1
                            = (currentPlayerTotalTroopValue * 100) / DAT_SoundEffectsHelperData1::instance.field12_0x4c;
                        if (100 < somePercentage1) {
                            somePercentage1 = 100;
                        }
                        DAT_SoundEffectsHelperData1::instance.field2_0x8 = currentPlayerTotalTroopValue;

                        if (DAT_SoundEffectsHelperData1::instance.DAT_Music_TotalTroopValue < 1) {
                            DAT_SoundEffectsHelperData1::instance.DAT_Music_TotalTroopValue = 1;
                        }
                        int somePercentage2 = (enemyPlayerTotalTroopValue * 100)
                            / DAT_SoundEffectsHelperData1::instance.DAT_Music_TotalTroopValue;
                        if (100 < somePercentage2) {
                            somePercentage2 = 100;
                        }
                        DAT_SoundEffectsHelperData1::instance.field4_0x2c = enemyPlayerTotalTroopValue;

                        int const someValue = somePercentage1 - somePercentage2;
                        if (someValue > 20) {
                            DAT_SoundEffectsHelperData1::instance.field6_0x34 = 1;
                        } else if (someValue < -20) {
                            DAT_SoundEffectsHelperData1::instance.field6_0x34 = 2;
                        } else {
                            DAT_SoundEffectsHelperData1::instance.field6_0x34 = 0;
                        }
                    }
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 == 5) {
                        return;
                    }
                }
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field7_0x1c != 0) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::playRandomMusic02, this)(2);
                } else if (0
                        < DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .totalEnemyUnitsCount
                    && DAT_TroopValueState::instance.attackInfo.lowTroopValueRelated == 0) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::playRandomMusic02, this)(1);
                    MACRO_CALL_MEMBER(SoundSystem_Func::meth_0x47a580, this)();
                }

                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 == 5) {
                    return;
                }

                if (this->sec_Section1055_0x3274 != 0) {
                    if (!MACRO_CALL_MEMBER(SoundSystem_Func::isSampleOrStreamPlaying, this)(enums::SND_STR_MUSIC)) {
                        if (9 < this->sec_Section1055_0x3274) {
                            this->mbr_0x3288 = timeGetTime();
                        }
                        this->sec_Section1055_0x3274 = 0;
                        this->currentSoundID_0x3278 = 0;
                    }
                    if (this->sec_Section1055_0x3274 != 0) {
                        return;
                    }
                }
                if (this->mbr_0x3288 == 0) {
                    this->mbr_0x3288 = timeGetTime();
                }
                if (this->sec_Section1055_0x3274 != 0) {
                    return;
                }

                if (timeGetTime() - this->mbr_0x3288
                    <= DAT_SFXDefinedData::instance.field4_0x4c4[DAT_SoundEffectsHelperData1::instance.field16_0x5c]) {
                    return;
                }

                ++DAT_SoundEffectsHelperData1::instance.field16_0x5c;
                if (DAT_SoundEffectsHelperData1::instance.field16_0x5c >= 6) {
                    DAT_SoundEffectsHelperData1::instance.field16_0x5c = 0;
                }
                MACRO_CALL_MEMBER(SoundSystem_Func::FUN_0047a340, this)();
            } else {
                if (!MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
                    return;
                }
                if (DAT_GameSynchronyState::instance.DAT_CurrentGameMode == Game::GM_SOLITARY) {
                    return;
                }

                int const battleLevelTemp = DAT_GameCore::instance.battleLevel2 + 2500;
                int const iVar7 = DAT_GameCore::instance.battleLevel2;
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 != 5) {
                    if (0 < DAT_GameCore::instance.battleLevel2) {
                        --DAT_GameCore::instance.battleLevel2;
                    }
                    if (DAT_GameCore::instance.battleLevel >= battleLevelTemp) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::playRandomMusic02, this)(2);
                        DAT_GameCore::instance.battleLevel2 = 0;
                    }
                } else {
                    if (DAT_GameCore::instance.battleLevel2 < 50000) {
                        DAT_GameCore::instance.battleLevel2 = DAT_GameCore::instance.battleLevel2 + 1;
                    }
                }
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 == 5) {
                    if (DAT_GameCore::instance.battleLevel < iVar7) {
                        MACRO_CALL_MEMBER(
                            SoundSystem_Func::handleBattleEndMusicTransition, DAT_SoundSystemState::ptr)();
                    }
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.troopValueLevel != 0
                        && DAT_SoundEffectsHelperData1::instance.SEC_Section1079.volumeLevel == 2
                        && 30000 < timeGetTime() - DAT_SoundEffectsHelperData1::instance.DAT_SomeSoundTime2) {
                        MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                        int const randomNumber = SEC_RNG::instance.currentNumber1 % 3;
                        if (randomNumber == 0)
                            DAT_SoundEffectsHelperData1::instance.field6_0x34 = 1;
                        else if (randomNumber == 1)
                            DAT_SoundEffectsHelperData1::instance.field6_0x34 = 2;
                        else
                            DAT_SoundEffectsHelperData1::instance.field6_0x34 = 0;
                    }
                }

                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 == 5) {
                    return;
                }

                if (this->sec_Section1055_0x3274 != 0) {
                    if (!MACRO_CALL_MEMBER(SoundSystem_Func::isSampleOrStreamPlaying, this)(enums::SND_STR_MUSIC)) {
                        if (9 < this->sec_Section1055_0x3274) {
                            this->mbr_0x3288 = timeGetTime();
                        }
                        this->sec_Section1055_0x3274 = 0;
                        this->currentSoundID_0x3278 = 0;
                    }
                    if (this->sec_Section1055_0x3274 != 0) {
                        return;
                    }
                }
                if (this->mbr_0x3288 == 0) {
                    this->mbr_0x3288 = timeGetTime();
                }
                if (this->sec_Section1055_0x3274 != 0) {
                    return;
                }

                if (timeGetTime() - this->mbr_0x3288
                    <= DAT_SFXDefinedData::instance.field4_0x4c4[DAT_SoundEffectsHelperData1::instance.field16_0x5c]) {
                    return;
                }

                ++DAT_SoundEffectsHelperData1::instance.field16_0x5c;
                if (DAT_SoundEffectsHelperData1::instance.field16_0x5c >= 6) {
                    DAT_SoundEffectsHelperData1::instance.field16_0x5c = 0;
                }
                MACRO_CALL_MEMBER(SoundSystem_Func::FUN_0047a340, this)();
            }
        }

    }
}
}
