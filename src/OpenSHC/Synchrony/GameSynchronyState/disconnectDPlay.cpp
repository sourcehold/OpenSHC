#include "../../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Game::GameMode;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E240
    void GameSynchronyState::disconnectDPlay()
    {
        void* pvVar1;
        int iVar2;
        DAT_MouseState::instance.waitCursorToggle = 1;
        MACRO_CALL(UI::Helpers_Func::SetCursorDependingOnProgramState)();
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::clearSessionsList, this)();
        iVar2 = 0;
        if (0 < this->scrollBarItemCount) {
            do {
                MACRO_CALL(OS_Func::_free_base)((void*)(DAT_GameSynchronyState::instance.providerNames[iVar2]));
                pvVar1 = GlobalHandle(DAT_GameSynchronyState::instance.guids[iVar2]);
                GlobalUnlock(pvVar1);
                pvVar1 = GlobalHandle(DAT_GameSynchronyState::instance.guids[iVar2]);
                GlobalFree(pvVar1);
                DAT_GameSynchronyState::instance.providerNames[iVar2] = (WCHAR*)0x0;
                DAT_GameSynchronyState::instance.guids[iVar2] = (GUID*)0x0;
                iVar2 = iVar2 + 1;
            } while (iVar2 < this->scrollBarItemCount);
        }
        iVar2 = 0;
        this->scrollBarItemCount = 0;
        if (0 < this->modemScrollbarCount) {
            do {
                MACRO_CALL(OS_Func::_free_base)(DAT_GameSynchronyState::instance.stringPointerArray[iVar2]);
                iVar2 = iVar2 + 1;
            } while (iVar2 < this->modemScrollbarCount);
        }
        this->modemScrollbarCount = 0;
        if (this->DPLAYX_4A != (IDirectPlay4A*)0x0) {
            this->DPLAYX_4A->CancelMessage(0, 0);
            this->DPLAYX_4A->DestroyPlayer(this->DPLAYX_PlayerHandle);
            this->DPLAYX_4A->Close();
            this->DPLAYX_4A = (IDirectPlay4A*)0x0;
        }
        if (this->DPLAYX_LOBBY != (IDirectPlayLobby3*)0x0) {
            this->DPLAYX_LOBBY->Release();
            this->DPLAYX_LOBBY = (IDirectPlayLobby3*)0x0;
        }
        if (this->DPLAYX_Connection) {
            pvVar1 = GlobalHandle((void*)this->DPLAYX_Connection);
            GlobalUnlock(pvVar1);
            pvVar1 = GlobalHandle((void*)this->DPLAYX_Connection);
            GlobalFree(pvVar1);
            this->DPLAYX_Connection = (void*)0x0;
        }
        this->scrollBarItemCount = 0;
        this->currentGameMode = Game::GM_SOLITARY;
        this->DAT_GameHalted = 0;
        this->syncStatus = 0;
        this->flag_0xbec = 0;
        this->useTCPIP = FALSE;
        this->quitGameVoteRelated = 0;
        this->saveRelated = 0;
        DAT_MouseState::instance.waitCursorToggle = 0;
    }

}
}
