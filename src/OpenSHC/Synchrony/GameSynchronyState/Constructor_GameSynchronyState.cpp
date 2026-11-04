#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/string-literals.hpp"
#include "OpenSHC/wstring-literals.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048C150
    GameSynchronyState* GameSynchronyState::Constructor_GameSynchronyState()
    {
        // the original reads some fields through the global instance rather than this, so they stay that way
        this->currentGameMode = Game::GM_SOLITARY;
        DAT_GameSynchronyState::instance.field301_0x109e8c = 1;
        this->DPLAYX_ReceivedPlayerID = 0;
        this->DPLAY_ToID = 0;
        this->DPLAYX_PlayerHandle = -1;
        this->currentPlayerSlotID = 0;
        this->field323_0x109ecc = GetTickCount();
        this->now2 = GetTickCount();
        this->field326_0x109ed8 = timeGetTime();
        this->field316_0x109ebc = 0;
        this->field317_0x109ec0 = 0;
        this->field313_0x109eb0 = 1;
        this->field314_0x109eb4 = 1;
        this->DAT_HostAnnounced = FALSE;
        // the first four bytes of this area are cleared with one dword store
        *(int*)this->field55_0x79c = 0;
        DAT_GameSynchronyState::instance.relativeTickTime = 0;
        // L"Crusader"
        MACRO_CALL(Global_Func::PrintToDestination)(this->DPLAYX_SessionName, u_Crusader_005a6f40);
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            // "Contestant"
            12, (void*)s_Contestant_005a74a8, this->DPLAY_PlayerShortName);
        this->scrollBarItemCount = 0;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::setupSkirmishLobby, this)();
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::readGameSpyConfig, this)();
        this->skirmishAutoSaveEveryMinutes = 10;
        return this;
    }

}
}
