#include "../../Synchrony.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using Game::GameMode;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048C660
    void GameSynchronyState::queueSynchronizedAutosaveProtocol()
    {
        if (this->currentGameMode != Game::GM_SOLITARY && this->currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER
            && this->isHost && this->skirmishAutoSaveEveryMinutes && this->timeSkirmishGameStart) {
            BOOLEnum BVar1 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if (BVar1 && !this->syncStatus && !this->saveRelated) {
                DWORD DVar2 = timeGetTime();
                if ((int)(DVar2 - this->timeSkirmishGameStart) > this->skirmishAutoSaveEveryMinutes * 60000) {
                    /*
                      autosave
                     */
                    this->lastAutoSaveTime = DVar2;
                    this->timeSkirmishGameStart = DVar2;
                    /*
                      Kept as a literal: s_autosave_005a74b4 from string-literals.hpp measures 100% -> 62.2%.
                     */
                    strcpy(DAT_GameSynchronyState::instance.shortMapName, "autosave");
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = DAT_GameCore::instance.mapTimeInTicks;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = MACRO_CALL_MEMBER(
                        Synchrony::GameSynchronyState_Func::computeSomeHashOnUnitArray, DAT_GameSynchronyState::ptr)();
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = 1;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_SAVE);
                }
            }
        }
    }

}
}
