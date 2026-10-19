#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EA40
    int GameSynchronyState::countPlayersInSameTeam(int playerID)
    {
        int iVar2 = 0;
        int iVar1 = DAT_GameState::instance.mapAndTime.playerTeams[playerID];
        if ((this->currentPlayerFullIDArray[1] != -1) && (DAT_GameState::instance.mapAndTime.playerTeams[1] == iVar1)) {
            iVar2 = 1;
        }
        if ((this->currentPlayerFullIDArray[2] != -1) && (DAT_GameState::instance.mapAndTime.playerTeams[2] == iVar1)) {
            iVar2 = iVar2 + 1;
        }
        if ((this->currentPlayerFullIDArray[3] != -1) && (DAT_GameState::instance.mapAndTime.playerTeams[3] == iVar1)) {
            iVar2 = iVar2 + 1;
        }
        if ((this->currentPlayerFullIDArray[4] != -1) && (DAT_GameState::instance.mapAndTime.playerTeams[4] == iVar1)) {
            iVar2 = iVar2 + 1;
        }
        if ((this->currentPlayerFullIDArray[5] != -1) && (DAT_GameState::instance.mapAndTime.playerTeams[5] == iVar1)) {
            iVar2 = iVar2 + 1;
        }
        if ((this->currentPlayerFullIDArray[6] != -1) && (DAT_GameState::instance.mapAndTime.playerTeams[6] == iVar1)) {
            iVar2 = iVar2 + 1;
        }
        if ((this->currentPlayerFullIDArray[7] != -1) && (DAT_GameState::instance.mapAndTime.playerTeams[7] == iVar1)) {
            iVar2 = iVar2 + 1;
        }
        if ((this->currentPlayerFullIDArray[8] != -1) && (DAT_GameState::instance.mapAndTime.playerTeams[8] == iVar1)) {
            iVar2 = iVar2 + 1;
        }
        return iVar2;
    }

}
}
