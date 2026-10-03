#include "../../Synchrony.func.hpp"
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
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0048B330
    void Commands::ShareQuitGameVote()
    {
        char cVar1;
        int subjectPlayerID;
        char* pcVar2;
        char* pcVar3;
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
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            subjectPlayerID = DAT_GameSynchronyState::instance.protocolInvokerPlayerID;
            if ((DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == 2)
                || (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == 1)) {
                DAT_GameSynchronyState::instance.quitGameVoteRelated = 0;
                if (DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_ONLINE_VOTE_QUIT_GAME) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                }
                if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == 1) {
                    /*
                      added by script: "No"
                     */
                    pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 0x17);
                    pcVar3 = DAT_GameSynchronyState::instance.receivedChatMessage;
                    do {
                        cVar1 = *pcVar2;
                        *pcVar3 = cVar1;
                        pcVar2 = pcVar2 + 1;
                        pcVar3 = pcVar3 + 1;
                    } while (cVar1 != '\0');
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                        DAT_GameSynchronyState::ptr)(subjectPlayerID, 0);
                }
            } else if (DAT_GameSynchronyState::instance.quitGameVoteRelated == 2) {
                if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 != 0) {}
                DAT_GameSynchronyState::instance
                    .field122_0xc70[DAT_GameSynchronyState::instance.protocolInvokerPlayerID] = 1;
                if ((DAT_GameSynchronyState::instance.field122_0xc70[8] != 0)
                    && (DAT_GameSynchronyState::instance.field122_0xc70[7] != 0
                        && (DAT_GameSynchronyState::instance.field122_0xc70[6] != 0
                            && (DAT_GameSynchronyState::instance.field122_0xc70[5] != 0
                                && (DAT_GameSynchronyState::instance.field122_0xc70[4] != 0
                                    && (DAT_GameSynchronyState::instance.field122_0xc70[3] != 0
                                        && (DAT_GameSynchronyState::instance.field122_0xc70[2] != 0
                                            && DAT_GameSynchronyState::instance.field122_0xc70[1] != 0))))))) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_KILL_GAME);
                }
            }
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == 0) {
                /*
                  added by script: "Yes"
                 */
                pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 0x16);
                pcVar3 = DAT_GameSynchronyState::instance.receivedChatMessage;
                do {
                    cVar1 = *pcVar2;
                    *pcVar3 = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pcVar3 = pcVar3 + 1;
                } while (cVar1 != '\0');
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(subjectPlayerID, 0);
            }
        }
    }

}
}
