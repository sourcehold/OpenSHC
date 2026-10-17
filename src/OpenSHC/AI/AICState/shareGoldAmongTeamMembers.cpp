// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../AICState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace AI {

    // FIXME: The original function never sets a return value (eax is left over from the last computation),
    // so it was most likely a void function. The header declares int, which forces the "return 0"s below
    // and costs an extra "xor eax, eax" in the assembly. Change the return type to void in the header.

    // FUNCTION: STRONGHOLDCRUSADER 0x004D05D0
    void AICState::shareGoldAmongTeamMembers(int playerID, int gold)
    {
        int candidateCount = 0;
        int candidates[9];
        for (int i = 1; i < 9; i++) {
            if ((DAT_GameSynchronyState::instance.currentAIArray[i] != 0
                    || DAT_GameSynchronyState::instance.currentPlayerFullIDArray[i] != -1)
                && i != playerID
                && DAT_GameState::instance.mapAndTime.playerTeams[i]
                    == DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                && DAT_GameState::instance.playerDataArray[i].lordKilledByPlayerID == 0) {
                candidates[candidateCount] = i;
                candidateCount++;
            }
        }

        if (candidateCount == 0) {
            return;
        }

        int goldPerPlayer = gold / candidateCount;
        if (goldPerPlayer == 0) {
            return;
        }

        for (int j = 0; j < candidateCount; j++) {
            int targetPlayer = candidates[j];
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[targetPlayer] != -1) {
                // "Goods received from ally"
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_ALLIES2, 1));
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(targetPlayer, 0);

                // "Gold"
                MACRO_CALL(OS_Func::_sprintf)(DAT_GameSynchronyState::instance.receivedChatMessage, "%d %s - ",
                    goldPerPlayer,
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_GOODS, Game::Resources::RT_GOLD));
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(targetPlayer, playerID);
            }

            DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD]
                -= goldPerPlayer;
            DAT_GameState::instance.playerDataArray[targetPlayer].currentResources[Game::Resources::RT_GOLD]
                += goldPerPlayer;
        }
        return;
    }

}
}
