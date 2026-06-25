#include "../SoundSystem.func.hpp"

#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047a340
        void SoundSystem::FUN_0047a340()
        {
            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
            int someState;
            if (DAT_GameSynchronyState::instance.DAT_CurrentGameMode == Game::GM_SOLITARY
                || 50 <= DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentPopulation
                || (DAT_GameSynchronyState::instance.DAT_CurrentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION)) {
                someState = SEC_RNG::instance.currentNumber1 % 5;
            } else {
                someState = SEC_RNG::instance.currentNumber1 % 4;
            }

            if (0 < someState) {
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                if (SEC_RNG::instance.currentNumber1 % 2 == 0) {
                    MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                    DAT_SoundEffectsHelperData1::instance.DAT_NegativeCountdownMin1ToMin4Becomes0
                        = SEC_RNG::instance.currentNumber1 % 4;
                    MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                    DAT_SoundEffectsHelperData1::instance.DAT_RandomVariationCurrentPlayingMusic_01
                        = SEC_RNG::instance.currentNumber1 % 24;
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(
                        (eMusicIDs)(DAT_SoundEffectsHelperData1::instance.DAT_RandomVariationCurrentPlayingMusic_01
                            + DE::SHCDE::MUSIC_OUD1));
                } else {
                    MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                    DAT_SoundEffectsHelperData1::instance.field13_0x50 = SEC_RNG::instance.currentNumber1 % 4;
                    MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                    DAT_SoundEffectsHelperData1::instance.DAT_RandomVariationCurrentPlayingMusic_02
                        = SEC_RNG::instance.currentNumber1 % 19;
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(
                        (eMusicIDs)(DAT_SoundEffectsHelperData1::instance.DAT_RandomVariationCurrentPlayingMusic_02
                            + DE::SHCDE::MUSIC_FLUTE1));
                }
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
                    break;
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
            this->mbr_0x3288 = 0;
            ++DAT_SoundEffectsHelperData1::instance.field8_0x3c;
            this->mbr_0x3288 = 0;
        }

    }
}
}
