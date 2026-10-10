#include "../Unknown33.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b960f8.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00b960f0.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using Commands::GameCommandType;
        using UI::Enums::BuildingsAndStatusMenuTabType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0042C090
        void Unknown33::MenuView_Unknown33_DoEveryFrame()
        {
            int iVar1 = MACRO_CALL_MEMBER(
                Synchrony::GameSynchronyState_Func::checkAllPlayersReadyAndCleanupSlots, DAT_GameSynchronyState::ptr)();
            if (iVar1) {
                if (DAT_GameSynchronyState::instance.isHost) {
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_HOST_SHARE_LOBBY_STATE);
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_TRIGGER_LOBBY_PLAYER_INFORMATION_REFRESH);
                }
                for (iVar1 = 1; iVar1 < 9; iVar1++) {
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar1] == -1
                        && (!DAT_GameCore::instance.mapU4Int0
                            || (iVar1 != DAT_GameState::instance.mapAndTime.somePlayerID))
                        && DAT_GameSynchronyState::instance.currentAIArray[iVar1] == 0) {
                        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::destroyPlayerCompletely, DAT_GameState::ptr)(
                            iVar1);
                    }
                }
                MACRO_CALL(Synchrony_Func::SetAIPlayerNickNames)();
                DAT_GameSynchronyState::instance.timeSkirmishGameStart = timeGetTime();
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = UI::Enums::BASMTT_HUNTERSHUT;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_BUILD_MENU, 0);
                DAT_GameSynchronyState::instance.DAT_TwoIfNotHost = 0;
                DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[0] = 0;
                DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[1] = 0;
                DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[2] = 0;
                DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[3] = 0;
                DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[4] = 0;
                DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[5] = 0;
                DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[6] = 0;
                DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[7] = 0;
                DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[8] = 0;
                DAT_00b960f8::instance = 0;
                INT_00b960f0::instance = 0;
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 1;
            }
        }

    }
}
}
