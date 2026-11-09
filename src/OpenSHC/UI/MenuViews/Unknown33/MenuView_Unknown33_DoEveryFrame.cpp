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

        // FUNCTION: STRONGHOLDCRUSADER 0x0042C090
        void Unknown33::MenuView_Unknown33_DoEveryFrame()
        {
            if (MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::checkAllPlayersReadyAndCleanupSlots,
                    DAT_GameSynchronyState::ptr)()) {
                if (DAT_GameSynchronyState::instance.isHost) {
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_HOST_SHARE_LOBBY_STATE);
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_TRIGGER_LOBBY_PLAYER_INFORMATION_REFRESH);
                }
                for (int playerID = 1; playerID < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray);
                    ++playerID) {
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
                        && (DAT_GameCore::instance.mapU4Int0 == 0
                            || (playerID != DAT_GameState::instance.mapAndTime.somePlayerID))
                        && DAT_GameSynchronyState::instance.currentAIArray[playerID] == 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::destroyPlayerCompletely,
                            DAT_GameState::ptr)(playerID);
                    }
                }
                MACRO_CALL(OpenSHC::Synchrony_Func::SetAIPlayerNickNames)();
                DAT_GameSynchronyState::instance.timeSkirmishGameStart = timeGetTime();
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = OpenSHC::UI::Enums::BASMTT_HUNTERSHUT;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                DAT_GameSynchronyState::instance.DAT_TwoIfNotHost = 0;
                for (int i = 0; i < countof(DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue); ++i) {
                    DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[i] = 0;
                }
                DAT_00b960f8::instance = 0;
                INT_00b960f0::instance = 0;
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 1;
            }
        }

    }
}
}
