#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
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
        DWORD _now = timeGetTime();
        if (this->currentGameMode != Game::GM_SOLITARY && this->currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER
            && this->DPLAYX_4A != (IDirectPlay4A*)0x0) {
            BOOLEnum _inGameMenu = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if (_inGameMenu) {
                ++this->syncRelated2;
                for (int _player = 0; _player < 9; ++_player) {
                    this->connectionLagInfoArray[_player].mapTimeInTicks = DAT_GameCore::instance.mapTimeInTicks;
                    this->connectionLagInfoArray[_player].counter = (char)this->syncRelated2;
                    this->connectionLagInfoArray[_player].now = _now;
                }
                this->syncPacketType = 126;
                this->syncRelatedCounter = this->syncRelated2;
                // dwDataSize covers the two adjacent fields set just above. The 65000 is
                // dwPriority, a plain number below dplay.h's DPSEND_MAX_PRIORITY (0xFFFF).
                size_t const _packetSize = sizeof(this->syncPacketType) + sizeof(this->syncRelatedCounter);
                this->DPLAYX_SendAndReceiveREsult = this->DPLAYX_4A->SendEx(this->DPLAYX_PlayerHandle, 0,
                    DPSEND_GUARANTEED | DPSEND_ASYNC | DPSEND_NOSENDCOMPLETEMSG, &this->syncPacketType, _packetSize,
                    65000, 0, (void*)0x0, (DWORD_PTR*)0x0);
                if ((this->DPLAYX_SendAndReceiveREsult) && (this->DPLAYX_SendAndReceiveREsult != -0x7ffffff6)) {
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::handleUnexpectedDPlayXResult, this)();
                }
            }
        }
    }

}
}
