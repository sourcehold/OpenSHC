#include "../../Synchrony.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using Game::GameMode;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048C660
    void GameSynchronyState::queueSynchronizedAutosaveProtocol()
    {
        BOOLEnum BVar1;
        DWORD DVar2;
        if (this->currentGameMode != Game::GM_SOLITARY && this->currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER
            && this->isHost && this->skirmishAutoSaveEveryMinutes && this->timeSkirmishGameStart) {
            BVar1 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if (BVar1 && !this->syncStatus && !this->saveRelated) {
                DVar2 = timeGetTime();
                if (this->skirmishAutoSaveEveryMinutes * 60000 < (int)(DVar2 - this->timeSkirmishGameStart)) {
                    /*
                      autosave
                     */
                    strcpy(this->shortMapName, "autosave");
                    this->DAT_GameCommandParam0 = DAT_GameCore::instance.mapTimeInTicks;
                    this->lastAutoSaveTime = DVar2;
                    this->timeSkirmishGameStart = DVar2;
                    this->DAT_GameCommandParam1
                        = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::computeSomeHashOnUnitArray, this)();
                    this->DAT_GameCommandParam2 = 1;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(Commands::GCT_SAVE);
                }
            }
        }
    }

}
}
