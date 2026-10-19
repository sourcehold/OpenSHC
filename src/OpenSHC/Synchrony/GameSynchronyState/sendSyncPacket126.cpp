#include "../../Synchrony.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Game::GameMode;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004880E0
    void GameSynchronyState::sendSyncPacket126()
    {
        DWORD _now = timeGetTime();
        if (this->currentGameMode != Game::GM_SOLITARY && this->currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER
            && this->DPLAYX_4A != (IDirectPlay4A*)0x0) {
            BOOLEnum BVar1 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if (BVar1) {
                this->syncRelated2 = this->syncRelated2 + '';
                for (int i = 0; i < 9; i = i + 1) {
                    this->connectionLagInfoArray[i].mapTimeInTicks = DAT_GameCore::instance.mapTimeInTicks;
                    this->connectionLagInfoArray[i].counter = (char)this->syncRelated2;
                    this->connectionLagInfoArray[i].now = _now;
                }
                this->syncPacketType = 126;
                this->syncRelatedCounter = this->syncRelated2;
                this->DPLAYX_SendAndReceiveREsult = this->DPLAYX_4A->SendEx(this->DPLAYX_PlayerHandle, 0,
                    1537 | 1537 | 1537, &this->syncPacketType, 2, 65000, 0, (void*)0x0, (DWORD_PTR*)0x0);
                if ((this->DPLAYX_SendAndReceiveREsult) && (this->DPLAYX_SendAndReceiveREsult != -0x7ffffff6)) {
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::handleUnexpectedDPlayXResult, this)();
                }
            }
        }
    }

}
}
