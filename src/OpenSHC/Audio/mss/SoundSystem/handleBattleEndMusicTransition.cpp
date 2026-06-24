#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047AF50
        void SoundSystem::handleBattleEndMusicTransition()
        {
            if (DAT_GameCore::ptr->gameMode_2 == Game::GM_EDITOR
                || DAT_GameCore::ptr->gameMode_2 == Game::GM_SIEGE_THAT) {
                return;
            }
            if (DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.field0_0x0 != 5
                || DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.field6_0x18 != 0) {
                return;
            }
            DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.field6_0x18 = 1;
            if (DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.troopValueLevel == 0) {
                int const volumeLevel = DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.volumeLevel;
                if (volumeLevel < 1 || volumeLevel > 5) {
                    return;
                }

                MACRO_CALL_MEMBER(SoundSystem_Func::setSomeSoundTime, this)();
                DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.field0_0x0 = 1;
                if (DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.troopValueLevel == 0) {
                    return;
                }
            }

            switch (DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.volumeLevel) {
            case 1:
                if (DAT_GameSynchronyState::ptr->DAT_CurrentGameMode != Game::GM_SOLITARY) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::setSomeSoundTime, this)();
                    DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.field0_0x0 = 1;
                } else {
                    MACRO_CALL_MEMBER(SoundSystem_Func::stopMusicPlayback, this)();
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundIDWithMultiplier, this)(
                        DE::SHCDE::MUSIC_TUNE_BATTLE_L1D, 100);
                    MACRO_CALL_MEMBER(SFX::SFXState_Func::playVictoryMusic678, DAT_SFXState::ptr)();
                }
                break;
            case 2:
                MACRO_CALL_MEMBER(SoundSystem_Func::setSomeSoundTime, this)();
                if (DAT_GameSynchronyState::ptr->DAT_CurrentGameMode == Game::GM_SOLITARY) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundIDWithMultiplier, this)(
                        (eMusicIDs)(DAT_SoundEffectsHelperData1::ptr->DAT_WinMusicVariation
                            + DE::SHCDE::MUSIC_TUNE_WIN1),
                        100);
                    ++DAT_SoundEffectsHelperData1::ptr->DAT_WinMusicVariation;
                    if (DAT_SoundEffectsHelperData1::ptr->DAT_WinMusicVariation > 2) {
                        DAT_SoundEffectsHelperData1::ptr->DAT_WinMusicVariation = 0;
                    }
                } else {
                    DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.field0_0x0 = 1;
                }
                MACRO_CALL_MEMBER(SFX::SFXState_Func::playVictoryMusic678, DAT_SFXState::ptr)();
                break;
            }
        }

    }
}
}
