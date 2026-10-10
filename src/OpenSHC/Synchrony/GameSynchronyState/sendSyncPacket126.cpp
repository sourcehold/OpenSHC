#include "../../Synchrony.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Game::GameMode;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004880E0
    void GameSynchronyState::sendSyncPacket126()
    {
        DWORD _now;
        BOOLEnum BVar1;
        _now = timeGetTime();
        if (this->currentGameMode != Game::GM_SOLITARY && this->currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER
            && this->DPLAYX_4A != (IDirectPlay4A*)0x0) {
            BVar1 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if (BVar1) {
                this->syncRelatedCounter = this->syncRelated2 + '\x01';
                this->connectionLagInfoArray[0].mapTimeInTicks = DAT_GameCore::instance.mapTimeInTicks;
                this->connectionLagInfoArray[0].counter = (int)this->syncRelatedCounter;
                this->connectionLagInfoArray[1].mapTimeInTicks = DAT_GameCore::instance.mapTimeInTicks;
                this->connectionLagInfoArray[1].counter = (int)this->syncRelatedCounter;
                this->connectionLagInfoArray[2].mapTimeInTicks = DAT_GameCore::instance.mapTimeInTicks;
                this->connectionLagInfoArray[2].counter = (int)this->syncRelatedCounter;
                this->connectionLagInfoArray[3].mapTimeInTicks = DAT_GameCore::instance.mapTimeInTicks;
                this->connectionLagInfoArray[3].counter = (int)this->syncRelatedCounter;
                this->connectionLagInfoArray[4].mapTimeInTicks = DAT_GameCore::instance.mapTimeInTicks;
                this->connectionLagInfoArray[4].counter = (int)this->syncRelatedCounter;
                this->connectionLagInfoArray[5].mapTimeInTicks = DAT_GameCore::instance.mapTimeInTicks;
                this->connectionLagInfoArray[5].counter = (int)this->syncRelatedCounter;
                this->connectionLagInfoArray[6].mapTimeInTicks = DAT_GameCore::instance.mapTimeInTicks;
                this->connectionLagInfoArray[6].counter = (int)this->syncRelatedCounter;
                this->connectionLagInfoArray[7].mapTimeInTicks = DAT_GameCore::instance.mapTimeInTicks;
                this->connectionLagInfoArray[7].counter = (int)this->syncRelatedCounter;
                this->connectionLagInfoArray[8].mapTimeInTicks = DAT_GameCore::instance.mapTimeInTicks;
                this->connectionLagInfoArray[8].counter = (int)this->syncRelatedCounter;
                this->syncPacketType = 126;
                this->connectionLagInfoArray[0].now = _now;
                this->connectionLagInfoArray[1].now = _now;
                this->connectionLagInfoArray[2].now = _now;
                this->connectionLagInfoArray[3].now = _now;
                this->connectionLagInfoArray[4].now = _now;
                this->connectionLagInfoArray[5].now = _now;
                this->connectionLagInfoArray[6].now = _now;
                this->connectionLagInfoArray[7].now = _now;
                this->connectionLagInfoArray[8].now = _now;
                this->syncRelated2 = this->syncRelatedCounter;
                this->DPLAYX_SendAndReceiveREsult = this->DPLAYX_4A->SendEx(this->DPLAYX_PlayerHandle, 0,
                    1537 | 1537 | 1537, (void*)0x1998398, 2, 65000, 0, (void*)0x0, (DWORD_PTR*)0x0);
                if ((this->DPLAYX_SendAndReceiveREsult) && (this->DPLAYX_SendAndReceiveREsult != -0x7ffffff6)) {
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::handleUnexpectedDPlayXResult, this)();
                }
            }
        }
    }

}
}
