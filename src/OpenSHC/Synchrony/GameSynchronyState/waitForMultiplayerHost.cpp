#include "../../Synchrony.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using Game::GameMode;
    using UI::Enums::MenuModalType;
    using UI::Enums::MenuViewType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00490920
    void GameSynchronyState::waitForMultiplayerHost()
    {
        this->currentGameMode = Game::GM_MULTIPLAYER;
        DAT_GameCore::instance.solitaryAllBuildingsAreFree = FALSE;
        DAT_GameCore::instance.solitaryAltUDungeon = FALSE;
        if (this->isHost) {
            this->DAT_HostAnnounced = 1;
            return;
        }
        this->DAT_HostAnnounced = 0;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
            Commands::GCT_MULTIPLAYER_INITIATE_ANNOUNCE_HOST);
        this->DAT_TickCount = GetTickCount();
        DWORD DVar1 = GetTickCount();
        uint uVar2 = DVar1 - this->DAT_TickCount;
        /*
          20 seconds? 2 seconds? wait
         */
        while (uVar2 < 20000 && !this->DAT_HostAnnounced) {
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::receiveAllTransmittedCommands, this)();
            DVar1 = GetTickCount();
            uVar2 = DVar1 - this->DAT_TickCount;
        }
        if (!this->DAT_HostAnnounced) {
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::disconnectDPlay, this)();
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::initializeMultiplayerLobby, this)();
            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                UI::Enums::MVT_MP_CONNECTION, 0);
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                UI::Enums::MMT_CHOOSE_NETWORK_SERVICE_PROVIDER, FALSE);
        }
        this->DAT_HostAnnounced = 1;
    }

}
}
