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
        this->currentGameMode = Game::GM_SOLITARY;
        DAT_GameSynchronyState::instance.field303_0x109e8c = 1;
        this->DPLAYX_ReceivedPlayerID = 0;
        this->DPLAY_ToID = 0;
        this->DPLAYX_PlayerHandle = -1;
        this->currentPlayerSlotID = 0;
        this->field325_0x109ecc = GetTickCount();
        this->now2 = GetTickCount();
        this->field328_0x109ed8 = timeGetTime();
        this->field318_0x109ebc = 0;
        this->field319_0x109ec0 = 0;
        this->field315_0x109eb0 = 1;
        this->field316_0x109eb4 = 1;
        this->DAT_HostAnnounced = 0;
        // The original clears the first four bytes of this area with a single dword store.
        *(int*)this->field57_0x79c = 0;
        DAT_GameSynchronyState::instance.relativeTickTime = 0;
        // L"Crusader"
        MACRO_CALL(Global_Func::PrintToDestination)(this->DPLAYX_SessionName, u_Crusader_005a6f40);
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            12, (void*)s_Contestant_005a74a8, this->DPLAY_PlayerShortName); // "Contestant"
        this->scrollBarItemCount = 0;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::setupSkirmishLobby, this)();
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::readGameSpyConfig, this)();
        this->skirmishAutoSaveEveryMinutes = 10;
        return this;
    }

}
}
