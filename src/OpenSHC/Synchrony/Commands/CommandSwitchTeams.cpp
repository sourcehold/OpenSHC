// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048ACB0
    void Commands::CommandSwitchTeams()
    {
        // a player's slot (two bytes) and what is asked for it (one byte)
        DAT_GameSynchronyState::instance.DAT_CommandSize = 3;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 2,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 1,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            return;
        }
        // FALSE before the plan is tested, as in the original: the flag shares its register with the constant 0
        // (declared above its test, or as one const expression, it loses the match under /GL too)
        BOOLEnum canSwitch = FALSE;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        // both parameters are received into the same four bytes, as in the original
        int received;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&received, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = (short)received;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&received, 1, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = (char)received;
        // one entry per team number, 1 to 8 (entry 0 is not used)
        int teamCounts[9];
        // 0: the sender asks the player in parameter 0 for an alliance; only that player's machine shows it
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam1 == 0) {
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                return;
            }
            // zeroed before the clears, here and in request 1, as in the original (declared above its counting
            // loop, either one loses the match)
            int teamCount = 0;
            for (int team = 1; team < countof(teamCounts); ++team) {
                teamCounts[team] = 0;
            }
            for (int slot = 1; slot < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray); ++slot) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[slot] != -1) {
                    teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[slot]]++;
                }
            }
            for (int team = 1; team < countof(teamCounts); ++team) {
                if (teamCounts[team] != 0) {
                    teamCount++;
                }
            }
            // shown with more than two teams in the game, or when the team numbered like the sender's slot doesn't
            // hold exactly one player
            if (teamCount > 2 || teamCounts[DAT_GameSynchronyState::instance.protocolInvokerPlayerID] != 1) {
                DAT_GameSynchronyState::instance
                    .unknownPlayerInfoArray_01[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]
                    = timeGetTime();
                // "wishes to become an ally."
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 37));
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.protocolInvokerPlayerID, 0);
            }
            return;
        }
        // 2: the sender leaves its team and takes the first team that no player is in
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam1 == 2) {
            for (int team = 1; team < countof(teamCounts); ++team) {
                teamCounts[team] = 0;
            }
            // here an entry only marks that its team has a player
            for (int slot = 1; slot < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray); ++slot) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[slot] != -1) {
                    teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[slot]] = 1;
                }
            }
            for (int team = 1; team < countof(teamCounts); ++team) {
                if (teamCounts[team] == 0) {
                    DAT_GameState::instance.mapAndTime
                        .playerTeams[DAT_GameSynchronyState::instance.protocolInvokerPlayerID] = team;
                    break;
                }
            }
            // "has cancelled the alliance"
            strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 39));
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.protocolInvokerPlayerID, 0);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam1 != 1) {
            return;
        }
        // 1: the player in parameter 0 joins the sender's team, if each of the two is alone in its team and the
        // same count test as for request 0 holds, here for parameter 0's slot
        int teamCount = 0;
        for (int team = 1; team < countof(teamCounts); ++team) {
            teamCounts[team] = 0;
        }
        for (int slot = 1; slot < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray); ++slot) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[slot] != -1) {
                teamCounts[DAT_GameState::instance.mapAndTime.playerTeams[slot]]++;
            }
        }
        for (int team = 1; team < countof(teamCounts); ++team) {
            if (teamCounts[team] != 0) {
                teamCount++;
            }
        }
        if (teamCount > 2 || teamCounts[DAT_GameSynchronyState::instance.DAT_GameCommandParam0] != 1) {
            canSwitch = TRUE;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::countPlayersInSameTeam,
                DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0)
            > 1) {
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::countPlayersInSameTeam,
                DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.protocolInvokerPlayerID)
            > 1) {
            return;
        }
        if (!canSwitch) {
            return;
        }
        DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
            = DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.protocolInvokerPlayerID];
        // "has joined with"
        strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 38));
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
            DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0,
            DAT_GameSynchronyState::instance.protocolInvokerPlayerID);
    }

}
}
