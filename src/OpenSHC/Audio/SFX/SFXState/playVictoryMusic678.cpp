#include "../SFXState.func.hpp"

#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_VictoryMusicVariation.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044A620
        void SFXState::playVictoryMusic678()
        {
            if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT) {
                return;
            }
            if ((DAT_VictoryMusicVariation::instance == 0 || DAT_VictoryMusicVariation::instance == 2)
                && (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campground.id
                        <= 0
                    || DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .lordID
                        <= 0)) {
                DAT_VictoryMusicVariation::instance = 1;
            }
            if (DAT_VictoryMusicVariation::instance == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, this)(
                    s_general_victory6_wav_005a4dc0);
            }
            if (DAT_VictoryMusicVariation::instance == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, this)(
                    s_general_victory7_wav_005a4da8);
            }
            if (DAT_VictoryMusicVariation::instance == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, this)(
                    s_general_victory8_wav_005a4d90);
            }
            ++DAT_VictoryMusicVariation::instance;
            if (2 < DAT_VictoryMusicVariation::instance) {
                DAT_VictoryMusicVariation::instance = 0;
            }
        }

    }
}
}
