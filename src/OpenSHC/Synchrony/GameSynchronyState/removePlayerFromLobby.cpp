#include "../../Synchrony.func.hpp"

#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Synchrony/Actions.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00490380
    void GameSynchronyState::removePlayerFromLobby(int playerID)
    {
        GameCommandType commandType;
        this->syncRelatedStatusArray[playerID] = 1;
        BOOLEnum BVar1 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        if ((BVar1) && (playerID != this->currentPlayerSlotID)) {
            this->DAT_GameCommandParam0 = playerID;
            this->DAT_GameCommandParam1 = this->kickDueToLagStatusUnk;
            if ((!this->syncStatus) && (!this->saveRelated)) {
                commandType = (Commands::GameCommandType)(Commands::GCT_SEND_RESYNC_TILEMAPDATA2
                    | Commands::GCT_HOST_ANNOUNCE_TEAMS_AND_POSITIONS);
            } else {
                commandType = Commands::GCT_LEAVE_GAME;
            }
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(commandType);
            this->unknownIncrementBy40_01 = this->unknownIncrementBy40_01 + 0x28;
            this->unknownPlayerInfo_03[playerID] = 1;
        }
        this->DAT_PlayerNames[playerID][0] = '\0';
        this->currentPlayerFullIDArray[playerID] = -1;
        this->DAT_PlayerSlotArraySomeValue[playerID] = 0;
        this->reparseMaps = TRUE;
        MACRO_CALL_MEMBER(AI::AIVState_Func::hostChecksLobbyAIVAvailability, DAT_AIVState::ptr)();
        this->isIncludedPlayer[playerID] = FALSE;
        this->DAT_ReceivedAIVFileAvailabilityPerAIArray[playerID][0] = -1;
        MACRO_CALL(Synchrony::Actions_Func::RemovePositionOfPlayer)(playerID);
        this->DAT_MultiplayerGameVersions[playerID] = 0;
        this->slotActionPending[playerID] = 0;
        if ((playerID != this->currentPlayerSlotID) && (this->isHost)) {
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions, this)();
        }
    }

}
}
