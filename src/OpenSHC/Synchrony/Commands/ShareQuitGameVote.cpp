// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048B330
    void Commands::ShareQuitGameVote()
    {
        // the vote: 0 yes, 1 no, 2 the vote is called off
        DAT_GameSynchronyState::instance.DAT_CommandSize = 4;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        int const voter = DAT_GameSynchronyState::instance.protocolInvokerPlayerID;
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == 2
            || DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == 1) {
            // a no, or the vote called off, ends the vote
            DAT_GameSynchronyState::instance.quitGameVoteRelated = 0;
            if (DAT_MenuModalComposition1::instance.activeModalDialogID
                == OpenSHC::UI::Enums::MMT_ONLINE_VOTE_QUIT_GAME) {
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            }
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == 1) {
                // "No"
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 23));
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(voter, 0);
            }
        } else if (DAT_GameSynchronyState::instance.quitGameVoteRelated == 2) {
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 != 0) {
                return;
            }
            // a yes is noted, and once every slot has voted yes the game is ended for everyone
            DAT_GameSynchronyState::instance.quitGameVoteArray[voter] = 1;
            BOOLEnum everyoneAgrees = TRUE;
            for (int slot = 1; slot < countof(DAT_GameSynchronyState::instance.quitGameVoteArray); ++slot) {
                if (DAT_GameSynchronyState::instance.quitGameVoteArray[slot] == 0) {
                    everyoneAgrees = FALSE;
                }
            }
            if (everyoneAgrees) {
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_KILL_GAME);
            }
        }
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == 0) {
            // "Yes"
            strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 22));
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                DAT_GameSynchronyState::ptr)(voter, 0);
        }
    }

}
}
