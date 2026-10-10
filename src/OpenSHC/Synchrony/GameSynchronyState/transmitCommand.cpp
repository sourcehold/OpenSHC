#include "../../Synchrony.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Synchrony {
    using Game::GameMode;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00487C50
    void GameSynchronyState::transmitCommand(byte commandCategory, undefined4 time,
        char* addressOfFullCommandObjectOrCommandParameters, size_t size, undefined4 idTo)
    {
        int iVar1;
        char* _src;
        size_t local_3f0;
        char local_3ec[1000];
        uint local_4;
        DWORD _dwFlags;
        DWORD _dwPriority;
        int _packetSize = size;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)&_src;
        _src = addressOfFullCommandObjectOrCommandParameters;
        if (this->currentGameMode == Game::GM_SOLITARY || this->currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER
            || this->DPLAYX_4A == (IDirectPlay4A*)0x0)
            goto LAB_00487e0f;
        this->transmissionCounterUnk = this->transmissionCounterUnk + 1;
        if ((int)size < 200 || commandCategory == 65) {
            this->DAT_Packet.packet.commandProtocol = commandCategory;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::moveLowerThreeBytesIntoParam2, DAT_LowLevelMemory::ptr)(
                &time, (void*)((int)(((int)&this->DAT_Packet + 1))));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                _packetSize, (void*)((int)(_src)), (void*)((int)(((int)&this->DAT_Packet + 4))));
        } else {
            this->DAT_Packet.packet.commandProtocol = 125;
            this->DAT_Packet.prefixedPacket.packet.commandProtocol = commandCategory;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::moveLowerThreeBytesIntoParam2, DAT_LowLevelMemory::ptr)(
                &time, (void*)((int)(((int)&this->DAT_Packet + 2))));
            local_3f0 = _packetSize;
            iVar1 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::compressOrCreateLengthPrefixedPacketUnk,
                this)(_packetSize, _src, (void*)((int)(((int)&this->DAT_Packet + 5))));
            _packetSize = iVar1 + 1;
            if ((int)local_3f0 < _packetSize) {
                MACRO_CALL(OS_Func::_sprintf)(local_3ec, "packet size:%d new size:%d type:%d", local_3f0, _packetSize,
                    (int)(char)commandCategory);
            }
        }
        this->DAT_CurrentTransmitCommandPacketSize = _packetSize;
        if (commandCategory == 117) {
            BOOLEnum BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            _dwPriority = 0xfffd;
            if (!BVar2) {
            LAB_00487dc7:
                _dwFlags = 1536 | 1536;
                goto LAB_00487dda;
            }
            /*
              SendEx(idFrom, idTo, dwFlags, lpData, dwDataSize, dwPriority, dwTimeout,   lpContext, lpdwMsgID)
             */
            this->DPLAYX_SendAndReceiveREsult = this->DPLAYX_4A->SendEx(this->DPLAYX_PlayerHandle, idTo,
                1537 | 1537 | 1537, &this->DAT_Packet, _packetSize + 4, 0xfffd, 0, (void*)0x0, (DWORD_PTR*)0x0);
        } else {
            /*
              0xc
             */
            if (commandCategory == 12) {
                _dwPriority = 0xfffe;
                goto LAB_00487dc7;
            }
            _dwPriority = 0xffff;
            _dwFlags = DPSEND_NOSENDCOMPLETEMSG | DPSEND_ASYNC | DPSEND_GUARANTEED;
        LAB_00487dda:
            /*
              DPLAYX.DirectPlayEnumerate+88C0
             */
            this->DPLAYX_SendAndReceiveREsult = this->DPLAYX_4A->SendEx(this->DPLAYX_PlayerHandle, idTo, _dwFlags,
                &this->DAT_Packet, _packetSize + 4, _dwPriority, 0, (void*)0x0, (DWORD_PTR*)0x0);
        }
        if ((this->DPLAYX_SendAndReceiveREsult) && (this->DPLAYX_SendAndReceiveREsult != -0x7ffffff6)) {
            /*
              unsuccessfull transmission?
             */
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::handleUnexpectedDPlayXResult, this)();
        }
    LAB_00487e0f:;
        return;
    }

}
}
