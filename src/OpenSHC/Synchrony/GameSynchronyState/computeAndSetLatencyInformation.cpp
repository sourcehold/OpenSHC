#include "../../Synchrony.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Synchrony {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004882A0
    void GameSynchronyState::computeAndSetLatencyInformation()
    {
        if (this->DPLAY_ReceiveData.packet.commandProtocol == 0x7e) {
            this->syncPacketType = 0x7f;
            this->syncRelatedCounter = this->DPLAY_ReceiveData.prefixedPacket.packet.commandProtocol;
            this->DPLAYX_SendAndReceiveREsult = this->DPLAYX_4A->SendEx(this->DPLAYX_PlayerHandle,
                this->DPLAYX_ReceivedPlayerID, DPSEND_NOSENDCOMPLETEMSG | DPSEND_ASYNC | DPSEND_GUARANTEED,
                &this->syncPacketType, 2, 65000, 0, (void*)0x0, (DWORD_PTR*)0x0);
            if (!this->DPLAYX_SendAndReceiveREsult) {
                return;
            }
            if (this->DPLAYX_SendAndReceiveREsult == -0x7ffffff6) {
                return;
            }
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::handleUnexpectedDPlayXResult, this)();
            return;
        }
        uint uVar1 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs,
            this)(this->DPLAYX_ReceivedPlayerID);
        /*
          playerID is never 0 in this logic, but it could be 0 with a mod
         */
        this->connectionLagInfoArray[uVar1].time = timeGetTime();
        if (this->connectionLagInfoArray[uVar1].counter
            != (int)(char)this->DPLAY_ReceiveData.prefixedPacket.packet.commandProtocol) {
            return;
        }
        this->connectionLagInfoArray[uVar1].subtractedMapTicks
            = (int)(DAT_GameCore::instance.mapTimeInTicks - this->connectionLagInfoArray[uVar1].mapTimeInTicks) / 2;
        this->connectionLagInfoArray[uVar1].subtractedTime
            = timeGetTime() - this->connectionLagInfoArray[uVar1].now >> 1;
        BOOLEnum BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        if (!BVar2) {
            return;
        }
        this->connectionLagInfoArray[uVar1].checkFor0 = 1;
        int _sum_2 = 0;
        int _sum = 0;
        /*
          stupid way of writing that if counter == -1, then this is the first time we   write data... why not set
          counter to 0? Maybe it rotates at some point back   to 0
         */
        if (this->counter == -1) {
            for (int _index = 0; _index < (int)this->limit; _index = _index + 1) {
                this->historicalLagInfoPerPlayer[uVar1][_index][0]
                    = this->connectionLagInfoArray[uVar1].subtractedMapTicks;
                this->historicalLagInfoPerPlayer[uVar1][_index][1]
                    = this->connectionLagInfoArray[uVar1].subtractedTime;
            }
        } else {
            this->historicalLagInfoPerPlayer[uVar1][this->counter][1]
                = this->connectionLagInfoArray[uVar1].subtractedTime;
            this->historicalLagInfoPerPlayer[uVar1][this->counter][0]
                = this->connectionLagInfoArray[uVar1].subtractedMapTicks;
            this->counter = this->counter + 1;
            if ((int)this->counter < (int)this->limit)
                goto LAB_00488429;
        }
        this->counter = 0;
    LAB_00488429:
        int _limit = this->limit;
        if (_limit) {
            if (0 < _limit) {
                int _countdown = this->limit;
                int* piVar3 = this->historicalLagInfoPerPlayer[uVar1][2] + 1;
                do {
                    _sum_2 = _sum_2 + piVar3[-5];
                    _sum = _sum + *piVar3;
                    piVar3 = piVar3 + 2;
                    _countdown = _countdown + -1;
                } while (_countdown);
            }
            int _div = _sum / _limit;
            this->connectionLagInfoArray[uVar1].average2 = _div;
            this->connectionLagInfoArray[uVar1].average1 = _sum_2 / _limit;
        }
    }

}
}
