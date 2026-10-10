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
        uint uVar1;
        int* piVar3;
        int _counter;
        int _sum_2;
        int _countdown;
        uint _offset;
        if (this->DPLAY_ReceiveData.packet.commandProtocol == 0x7e) {
            this->syncPacketType = 0x7f;
            this->syncRelatedCounter = this->DPLAY_ReceiveData.prefixedPacket.packet.commandProtocol;
            this->DPLAYX_SendAndReceiveREsult = this->DPLAYX_4A->SendEx(this->DPLAYX_PlayerHandle,
                this->DPLAYX_ReceivedPlayerID, DPSEND_NOSENDCOMPLETEMSG | DPSEND_ASYNC | DPSEND_GUARANTEED,
                (void*)0x1998398, 2, 65000, 0, (void*)0x0, (DWORD_PTR*)0x0);
            if (!this->DPLAYX_SendAndReceiveREsult) {}
            if (this->DPLAYX_SendAndReceiveREsult == -0x7ffffff6) {}
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::handleUnexpectedDPlayXResult, this)();
        }
        uVar1 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs, this)(
            this->DPLAYX_ReceivedPlayerID);
        /*
          playerID is never 0 in this logic, but it could be 0 with a mod
         */
        DWORD _now_1 = timeGetTime();
        this->connectionLagInfoArray[uVar1].time = _now_1;
        if (this->connectionLagInfoArray[uVar1].counter
            != (int)(char)this->DPLAY_ReceiveData.prefixedPacket.packet.commandProtocol) {}
        this->connectionLagInfoArray[uVar1].subtractedMapTicks
            = (int)(DAT_GameCore::instance.mapTimeInTicks - this->connectionLagInfoArray[uVar1].mapTimeInTicks) / 2;
        DWORD _now_2 = timeGetTime();
        this->connectionLagInfoArray[uVar1].subtractedTime = _now_2 - this->connectionLagInfoArray[uVar1].now >> 1;
        BOOLEnum BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        if (!BVar2) {}
        this->connectionLagInfoArray[uVar1].checkFor0 = 1;
        _sum_2 = 0;
        /*
          stupid way of writing that if counter == -1, then this is the first time we   write data... why not set
          counter to 0? Maybe it rotates at some point back   to 0
         */
        if (this->counter == -1) {
            _counter = 0;
            if (0 < this->limit) {
                piVar3 = this->historicalLagInfoPerPlayer[uVar1][0] + 1;
                do {
                    (*(int (*)[2])(piVar3 + -1))[0] = this->connectionLagInfoArray[uVar1].subtractedMapTicks;
                    *piVar3 = this->connectionLagInfoArray[uVar1].subtractedTime;
                    _counter = _counter + 1;
                    piVar3 = piVar3 + 2;
                } while (_counter < this->limit);
            }
        } else {
            this->historicalLagInfoPerPlayer[uVar1][this->counter][1]
                = this->connectionLagInfoArray[uVar1].subtractedTime;
            this->historicalLagInfoPerPlayer[uVar1][this->counter][0]
                = this->connectionLagInfoArray[uVar1].subtractedMapTicks;
            this->counter = this->counter + 1;
            if (this->counter < this->limit)
                goto LAB_00488429;
        }
        this->counter = 0;
    LAB_00488429:
        int _sum = 0;
        if (this->limit) {
            if (0 < this->limit) {
                piVar3 = this->historicalLagInfoPerPlayer[uVar1][2] + 1;
                _countdown = this->limit;
                do {
                    _sum_2 = _sum_2 + piVar3[-5];
                    _sum = _sum + *piVar3;
                    piVar3 = piVar3 + 2;
                    _countdown = _countdown + -1;
                } while (_countdown);
            }
            int _div = _sum_2 / this->limit;
            this->connectionLagInfoArray[uVar1].average2 = _sum / this->limit;
            this->connectionLagInfoArray[uVar1].average1 = _div;
        }
    }

}
}
