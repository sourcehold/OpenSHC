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
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B890
        void SoundSystem::playRandomAmbientMusic()
        {
            char* filename;
            BOOLEnum BVar1;
            DWORD _currentTime;
            int iVar2;
            uint uVar3;
            DWORD(__stdcall * _getTimeFunc)();
            DWORD(__stdcall * pcVar4)();
            bool bVar5;
            bool bVar6;
            int iVar7;

            _getTimeFunc = timeGetTime;
            if (((DAT_GameSynchronyState::instance.DAT_CurrentGameMode == Game::GM_SOLITARY)
                    && (BVar1 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)(),
                        BVar1 != FALSE))
                && (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)) {
                if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campgroundBuildingID
                        < 1)
                    || (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .lordID
                        < 1)) {
                    DAT_TroopValueState::instance.attackInfo.field128079_0x469dc = 0;
                } else {
                    if ((0 < DAT_TroopValueState::instance.attackInfo.field128080_0x469e0)
                        && (DAT_TroopValueState::instance.attackInfo.field128078_0x469d8 == 1)) {
                        DAT_TroopValueState::instance.attackInfo.field128078_0x469d8 = 2;
                        /* "the enemy has breached the walls!" */
                        MACRO_CALL_MEMBER(SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            s_General_Warning15_wav_005a6ce4);
                    }
                    if (DAT_TroopValueState::instance.attackInfo.field128079_0x469dc != 0) {
                        DAT_TroopValueState::instance.attackInfo.field128079_0x469dc = 0;
                        _currentTime = timeGetTime();
                        if (90000 < _currentTime
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
            if ((0 < this->sec_Section1055_0x3274) && (this->mbr_0x154 != 0)) {
                if (this->mbr_0x154 == 2) {
                    _currentTime = timeGetTime();
                    uVar3 = (_currentTime - this->someSoundTime_0x158) / 10;
                    if (uVar3 < 100) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::setStreamAndSampleVolumeUnk, this)(
                            enums::SND_STR_MUSIC, ((100 - uVar3) * this->streamFileVolumeNextUnk_0x48[0]) / 100);
                        return;
                    }
                    MACRO_CALL_MEMBER(SoundSystem_Func::stopMusicPlayback, this)();
                    this->sec_Section1055_0x3274 = 0;
                    this->mbr_0x154 = 0;
                }
                if (this->mbr_0x154 == 1) {
                    _currentTime = timeGetTime();
                    uVar3 = (_currentTime - this->someSoundTime_0x158) / 200;
                    if (uVar3 < 100) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::setStreamAndSampleVolumeUnk, this)(
                            enums::SND_STR_MUSIC, (this->streamFileVolumeNextUnk_0x48[0] * uVar3) / 100);
                        return;
                    }
                    MACRO_CALL_MEMBER(SoundSystem_Func::setStreamAndSampleVolumeUnk, this)(
                        enums::SND_STR_MUSIC, (this->streamFileVolumeNextUnk_0x48[0] * 100) / 100);
                    this->mbr_0x154 = 0;
                }
            }
            if ((this->currentSoundID_0x3278 != this->sec_Section1055_0x3274) && (0 < this->currentSoundID_0x3278)) {
                if (this->mbr_0x3280 == 1) {
                    this->mbr_0x154 = 1;
                    this->someSoundTime_0x158 = timeGetTime();
                    this->mbr_0x3280 = 0;
                }
                filename = DAT_SFXDefinedData::instance.DAT_SFX_Pointers[this->currentSoundID_0x3278].musicFile;
                if (DAT_SFXDefinedData::instance.DAT_SFX_Pointers[this->currentSoundID_0x3278].unknownFlag_0x4
                    == FALSE) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::playOrEndMusicUnk, this)(
                        filename, this->currentSoundIDVolumeUnk_0x327c);
                    this->sec_Section1055_0x3274 = this->currentSoundID_0x3278;
                    this->currentSoundID_0x3278 = 0;
                } else {
                    MACRO_CALL_MEMBER(SoundSystem_Func::playOrSetupMusicUnk, this)(
                        filename, this->currentSoundIDVolumeUnk_0x327c);
                    this->sec_Section1055_0x3274 = this->currentSoundID_0x3278;
                }
            }
            BVar1 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if ((((BVar1 == FALSE)
                     && ((DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_SCENARIO_DESCRIPTION
                         || (DAT_GameCore::instance.field25_0x64 == 0))))
                    || (DAT_GameCore::instance.gameMode_2 == Game::GM_CRUSADER_TUTORIAL))
                || (DAT_GameSynchronyState::instance.DAT_CurrentGameMode != Game::GM_SOLITARY)) {
                BVar1 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
                iVar7 = DAT_GameCore::instance.battleLevel2;
                if (BVar1 == FALSE) {
                    return;
                }
                if (DAT_GameSynchronyState::instance.DAT_CurrentGameMode == Game::GM_SOLITARY) {
                    return;
                }
                iVar2 = DAT_GameCore::instance.battleLevel2 + 2500;
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 == 5) {
                    if (DAT_GameCore::instance.battleLevel2 < 50000) {
                        DAT_GameCore::instance.battleLevel2 = DAT_GameCore::instance.battleLevel2 + 1;
                    }
                LAB_0047be08:
                    if (DAT_GameCore::instance.battleLevel < iVar7) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::handleBattleEndMusicTransition, this)();
                    }
                    pcVar4 = timeGetTime;
                    if (((DAT_SoundEffectsHelperData1::instance.SEC_Section1079.troopValueLevel != 0)
                            && (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.volumeLevel == 2))
                        && (_currentTime = timeGetTime(),
                            30000 < _currentTime - DAT_SoundEffectsHelperData1::instance.DAT_SomeSoundTime2)) {
                        MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                        if (SEC_RNG::instance.currentNumber1 % 3 == 0) {
                            DAT_SoundEffectsHelperData1::instance.field6_0x34 = 1;
                        } else {
                            DAT_SoundEffectsHelperData1::instance.field6_0x34
                                = (-(uint)(SEC_RNG::instance.currentNumber1 % 3 != 1) & 0xfffffffe) + 2;
                        }
                    }
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 == 5) {
                        return;
                    }
                } else {
                    if (0 < DAT_GameCore::instance.battleLevel2) {
                        DAT_GameCore::instance.battleLevel2 = DAT_GameCore::instance.battleLevel2 + -1;
                    }
                    if (iVar2 <= DAT_GameCore::instance.battleLevel) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::playRandomMusic02, this)(2);
                        DAT_GameCore::instance.battleLevel2 = 0;
                    }
                    pcVar4 = timeGetTime;
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 == 5)
                        goto LAB_0047be08;
                }
                if (this->sec_Section1055_0x3274 != 0) {
                    BVar1 = MACRO_CALL_MEMBER(SoundSystem_Func::isSampleOrStreamPlaying, this)(enums::SND_STR_MUSIC);
                    if (BVar1 == FALSE) {
                        if (9 < this->sec_Section1055_0x3274) {
                            this->mbr_0x3288 = (*pcVar4)();
                        }
                        this->sec_Section1055_0x3274 = 0;
                        this->currentSoundID_0x3278 = 0;
                    }
                    if (this->sec_Section1055_0x3274 != 0) {
                        return;
                    }
                }
                if (this->mbr_0x3288 == 0) {
                    this->mbr_0x3288 = (*pcVar4)();
                }
                if (this->sec_Section1055_0x3274 != 0) {
                    return;
                }
                iVar7 = (*pcVar4)();
                bVar5 = iVar7 - this->mbr_0x3288
                    < (uint)
                          DAT_SFXDefinedData::instance.field4_0x4c4[DAT_SoundEffectsHelperData1::instance.field16_0x5c];
                bVar6 = iVar7 - this->mbr_0x3288
                    == DAT_SFXDefinedData::instance.field4_0x4c4[DAT_SoundEffectsHelperData1::instance.field16_0x5c];
            } else {
                if ((DAT_TroopValueState::instance.attackInfo.field105458_0x25b00 != 0)
                    && (0
                        < DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .totalEnemyUnitsCount)) {
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field7_0x1c == 0) {
                        iVar7 = 1;
                    } else {
                        iVar7 = 2;
                    }
                    MACRO_CALL_MEMBER(SoundSystem_Func::playRandomMusic02, this)(iVar7);
                    DAT_TroopValueState::instance.attackInfo.field105458_0x25b00 = 0;
                }
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 == 5) {
                    if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .totalEnemyUnitsCount
                            == 0)
                        && (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field7_0x1c == 0)) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::handleBattleEndMusicTransition, this)();
                    }
                    if (((DAT_SoundEffectsHelperData1::instance.SEC_Section1079.troopValueLevel != 0)
                            && (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.volumeLevel == 2))
                        && (_currentTime = timeGetTime(),
                            30000 < _currentTime - DAT_SoundEffectsHelperData1::instance.DAT_SomeSoundTime2)) {
                        DAT_SoundEffectsHelperData1::instance.DAT_SomeSoundTime2 = timeGetTime();
                        MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::recountTotalTroopValue, DAT_TroopValueState::ptr)();
                        DAT_SoundEffectsHelperData1::instance.field2_0x8
                            = DAT_TroopValueState::instance.attackInfo
                                  .playerTotalTroopValueArray[DAT_GameSynchronyState::instance.currentPlayerSlotID];
                        DAT_SoundEffectsHelperData1::instance.field4_0x2c = 0;
                        if (DAT_GameSynchronyState::instance.currentPlayerSlotID != 1) {
                            DAT_SoundEffectsHelperData1::instance.field4_0x2c
                                = DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[1];
                        }
                        if (DAT_GameSynchronyState::instance.currentPlayerSlotID != 2) {
                            DAT_SoundEffectsHelperData1::instance.field4_0x2c
                                = DAT_SoundEffectsHelperData1::instance.field4_0x2c
                                + DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[2];
                        }
                        if (DAT_GameSynchronyState::instance.currentPlayerSlotID != 3) {
                            DAT_SoundEffectsHelperData1::instance.field4_0x2c
                                = DAT_SoundEffectsHelperData1::instance.field4_0x2c
                                + DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[3];
                        }
                        if (DAT_GameSynchronyState::instance.currentPlayerSlotID != 4) {
                            DAT_SoundEffectsHelperData1::instance.field4_0x2c
                                = DAT_SoundEffectsHelperData1::instance.field4_0x2c
                                + DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[4];
                        }
                        if (DAT_GameSynchronyState::instance.currentPlayerSlotID != 5) {
                            DAT_SoundEffectsHelperData1::instance.field4_0x2c
                                = DAT_SoundEffectsHelperData1::instance.field4_0x2c
                                + DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[5];
                        }
                        if (DAT_GameSynchronyState::instance.currentPlayerSlotID != 6) {
                            DAT_SoundEffectsHelperData1::instance.field4_0x2c
                                = DAT_SoundEffectsHelperData1::instance.field4_0x2c
                                + DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[6];
                        }
                        if (DAT_GameSynchronyState::instance.currentPlayerSlotID != 7) {
                            DAT_SoundEffectsHelperData1::instance.field4_0x2c
                                = DAT_SoundEffectsHelperData1::instance.field4_0x2c
                                + DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[7];
                        }
                        if (DAT_GameSynchronyState::instance.currentPlayerSlotID != 8) {
                            DAT_SoundEffectsHelperData1::instance.field4_0x2c
                                = DAT_SoundEffectsHelperData1::instance.field4_0x2c
                                + DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[8];
                        }
                        if (DAT_SoundEffectsHelperData1::instance.field12_0x4c < 1) {
                            DAT_SoundEffectsHelperData1::instance.field12_0x4c = 1;
                        }
                        iVar7 = (DAT_SoundEffectsHelperData1::instance.field2_0x8 * 100)
                            / DAT_SoundEffectsHelperData1::instance.field12_0x4c;
                        if (100 < iVar7) {
                            iVar7 = 100;
                        }
                        if (DAT_SoundEffectsHelperData1::instance.DAT_Music_TotalTroopValue < 1) {
                            DAT_SoundEffectsHelperData1::instance.DAT_Music_TotalTroopValue = 1;
                        }
                        iVar2 = (DAT_SoundEffectsHelperData1::instance.field4_0x2c * 100)
                            / DAT_SoundEffectsHelperData1::instance.DAT_Music_TotalTroopValue;
                        if (100 < iVar2) {
                            iVar2 = 100;
                        }
                        _getTimeFunc = timeGetTime;
                        if (iVar7 - iVar2 < 0x15) {
                            DAT_SoundEffectsHelperData1::instance.field6_0x34 = (-0x15 < iVar7 - iVar2) - 1 & 2;
                        } else {
                            DAT_SoundEffectsHelperData1::instance.field6_0x34 = 1;
                        }
                    }
                    if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 == 5) {
                        return;
                    }
                }
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field7_0x1c == 0) {
                    if ((0 < DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .totalEnemyUnitsCount)
                        && (DAT_TroopValueState::instance.attackInfo.lowTroopValueRelated == 0)) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::playRandomMusic02, this)(1);
                        MACRO_CALL_MEMBER(SoundSystem_Func::meth_0x47a580, this)();
                    }
                } else {
                    MACRO_CALL_MEMBER(SoundSystem_Func::playRandomMusic02, this)(2);
                }
                if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 == 5) {
                    return;
                }
                if (this->sec_Section1055_0x3274 != 0) {
                    BVar1 = MACRO_CALL_MEMBER(SoundSystem_Func::isSampleOrStreamPlaying, this)(enums::SND_STR_MUSIC);
                    if (BVar1 == FALSE) {
                        if (9 < this->sec_Section1055_0x3274) {
                            this->mbr_0x3288 = (*_getTimeFunc)();
                        }
                        this->sec_Section1055_0x3274 = 0;
                        this->currentSoundID_0x3278 = 0;
                    }
                    if (this->sec_Section1055_0x3274 != 0) {
                        return;
                    }
                }
                if (this->mbr_0x3288 == 0) {
                    this->mbr_0x3288 = (*_getTimeFunc)();
                }
                if (this->sec_Section1055_0x3274 != 0) {
                    return;
                }
                _currentTime = (*_getTimeFunc)();
                bVar5 = _currentTime - this->mbr_0x3288
                    < (uint)
                          DAT_SFXDefinedData::instance.field4_0x4c4[DAT_SoundEffectsHelperData1::instance.field16_0x5c];
                bVar6 = _currentTime - this->mbr_0x3288
                    == DAT_SFXDefinedData::instance.field4_0x4c4[DAT_SoundEffectsHelperData1::instance.field16_0x5c];
            }
            if (bVar5 || bVar6) {
                return;
            }
            DAT_SoundEffectsHelperData1::instance.field16_0x5c = DAT_SoundEffectsHelperData1::instance.field16_0x5c + 1;
            if (5 < DAT_SoundEffectsHelperData1::instance.field16_0x5c) {
                DAT_SoundEffectsHelperData1::instance.field16_0x5c = 0;
            }
            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
            if (((DAT_GameSynchronyState::instance.DAT_CurrentGameMode == Game::GM_SOLITARY)
                    || (0x31
                        < DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentPopulation))
                || ((DAT_GameSynchronyState::instance.DAT_CurrentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER
                    && (DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION)))) {
                uVar3 = SEC_RNG::instance.currentNumber1 % 5;
            } else {
                uVar3 = SEC_RNG::instance.currentNumber1 & 0x80000003;
                if ((int)uVar3 < 0) {
                    uVar3 = (uVar3 - 1 | 0xfffffffc) + 1;
                }
            }
            if (0 < (int)uVar3) {
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                uVar3 = SEC_RNG::instance.currentNumber1 & 0x80000001;
                bVar5 = uVar3 == 0;
                if ((int)uVar3 < 0) {
                    bVar5 = (uVar3 - 1 | 0xfffffffe) == 0xffffffff;
                }
                if (bVar5) {
                    MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                    DAT_SoundEffectsHelperData1::instance.DAT_NegativeCountdownMin1ToMin4Becomes0
                        = SEC_RNG::instance.currentNumber1 & 0x80000003;
                    if ((int)DAT_SoundEffectsHelperData1::instance.DAT_NegativeCountdownMin1ToMin4Becomes0 < 0) {
                        DAT_SoundEffectsHelperData1::instance.DAT_NegativeCountdownMin1ToMin4Becomes0
                            = (DAT_SoundEffectsHelperData1::instance.DAT_NegativeCountdownMin1ToMin4Becomes0 - 1
                                  | 0xfffffffc)
                            + 1;
                    }
                    MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                    DAT_SoundEffectsHelperData1::instance.DAT_RandomVariationCurrentPlayingMusic_01
                        = SEC_RNG::instance.currentNumber1 % 0x18;
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(
                        (eMusicIDs)(DAT_SoundEffectsHelperData1::instance.DAT_RandomVariationCurrentPlayingMusic_01
                            + DE::SHCDE::MUSIC_OUD1));
                    this->mbr_0x3288 = 0;
                    return;
                }
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                DAT_SoundEffectsHelperData1::instance.field13_0x50 = SEC_RNG::instance.currentNumber1 & 0x80000003;
                if ((int)DAT_SoundEffectsHelperData1::instance.field13_0x50 < 0) {
                    DAT_SoundEffectsHelperData1::instance.field13_0x50
                        = (DAT_SoundEffectsHelperData1::instance.field13_0x50 - 1 | 0xfffffffc) + 1;
                }
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                DAT_SoundEffectsHelperData1::instance.DAT_RandomVariationCurrentPlayingMusic_02
                    = SEC_RNG::instance.currentNumber1 % 0x13;
                MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(
                    (eMusicIDs)(DAT_SoundEffectsHelperData1::instance.DAT_RandomVariationCurrentPlayingMusic_02
                        + DE::SHCDE::MUSIC_FLUTE1));
                this->mbr_0x3288 = 0;
                return;
            }
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentPopulation
                < 50) {
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                switch (SEC_RNG::instance.currentNumber1 % 5) {
                case 0:
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_MAIN);
                    break;
                case 1:
                    if (DAT_SoundEffectsHelperData1::instance.field8_0x3c != 0) {
                        MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_AVG2);
                        break;
                    }
                case 2:
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_GOOD);
                    break;
                case 3:
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_AVG);
                    break;
                case 4:
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_SAD2);
                }
            } else {
                if (DAT_SoundEffectsHelperData1::instance.field18_0x64 == 0) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_HAPPY);
                }
                if (DAT_SoundEffectsHelperData1::instance.field18_0x64 == 1) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_HAPPY2);
                }
                if (DAT_SoundEffectsHelperData1::instance.field18_0x64 == 2) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_HAPPY3);
                }
                DAT_SoundEffectsHelperData1::instance.field18_0x64
                    = DAT_SoundEffectsHelperData1::instance.field18_0x64 + 1;
                if (2 < DAT_SoundEffectsHelperData1::instance.field18_0x64) {
                    DAT_SoundEffectsHelperData1::instance.field18_0x64 = 0;
                }
            }
            DAT_SoundEffectsHelperData1::instance.field8_0x3c = DAT_SoundEffectsHelperData1::instance.field8_0x3c + 1;
            this->mbr_0x3288 = 0;
            return;
        }

    }
}
}
