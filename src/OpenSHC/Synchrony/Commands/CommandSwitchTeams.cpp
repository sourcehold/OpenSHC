#include "../../Synchrony.func.hpp"
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

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::DE::SHCDE::eTextSections;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0048ACB0
    void Commands::CommandSwitchTeams()
    {
        char cVar1;
        bool bVar2;
        int iVar3;
        DWORD DVar4;
        char* pcVar5;
        int iVar6;
        int iVar7;
        char* pcVar8;
        byte bVar9;
        short local_28[2];
        int aiStack_24[9];
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
        bVar2 = false;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(local_28, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = (int)local_28[0];
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(local_28, 1, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            iVar6 = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = (int)(char)local_28[0];
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam1 == 0) {
                if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                    == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    aiStack_24[1] = 0;
                    aiStack_24[2] = 0;
                    aiStack_24[3] = 0;
                    aiStack_24[4] = 0;
                    aiStack_24[5] = 0;
                    aiStack_24[6] = 0;
                    aiStack_24[7] = 0;
                    aiStack_24[8] = 0;
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[1]]
                            = aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[1]] + 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[2]]
                            = aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[2]] + 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[3]]
                            = aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[3]] + 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[4]]
                            = aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[4]] + 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[5]]
                            = aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[5]] + 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[6]]
                            = aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[6]] + 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[7]]
                            = aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[7]] + 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[8]]
                            = aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[8]] + 1;
                    }
                    bVar9 = aiStack_24[1] != 0;
                    if (aiStack_24[2] != 0) {
                        bVar9 = bVar9 + 1;
                    }
                    if (aiStack_24[3] != 0) {
                        bVar9 = bVar9 + 1;
                    }
                    if (aiStack_24[4] != 0) {
                        bVar9 = bVar9 + 1;
                    }
                    if (aiStack_24[5] != 0) {
                        bVar9 = bVar9 + 1;
                    }
                    if (aiStack_24[6] != 0) {
                        bVar9 = bVar9 + 1;
                    }
                    if (aiStack_24[7] != 0) {
                        bVar9 = bVar9 + 1;
                    }
                    if (aiStack_24[8] != 0) {
                        bVar9 = bVar9 + 1;
                    }
                    if ((2 < bVar9) || (aiStack_24[DAT_GameSynchronyState::instance.protocolInvokerPlayerID] != 1)) {
                        DVar4 = timeGetTime();
                        DAT_GameSynchronyState::instance
                            .unknownPlayerInfoArray_01[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]
                            = DVar4;
                        /*
                          "Wishes to become an ally"   added by script: "wishes to become an ally."
                         */
                        pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x25);
                        pcVar8 = DAT_GameSynchronyState::instance.receivedChatMessage;
                        do {
                            cVar1 = *pcVar5;
                            *pcVar8 = cVar1;
                            pcVar5 = pcVar5 + 1;
                            pcVar8 = pcVar8 + 1;
                        } while (cVar1 != '\0');
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                            DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.protocolInvokerPlayerID, 0);
                    }
                }
            } else {
                if (DAT_GameSynchronyState::instance.DAT_GameCommandParam1 == 2) {
                    aiStack_24[1] = 0;
                    aiStack_24[2] = 0;
                    aiStack_24[3] = 0;
                    aiStack_24[4] = 0;
                    aiStack_24[5] = 0;
                    aiStack_24[6] = 0;
                    aiStack_24[7] = 0;
                    aiStack_24[8] = 0;
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[1]] = 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[2]] = 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[3]] = 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[4]] = 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[5]] = 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[6]] = 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[7]] = 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[8]] = 1;
                    }
                    iVar6 = 1;
                    do {
                        if (aiStack_24[iVar6] == 0) {
                            DAT_GameState::instance.mapAndTime
                                .playerTeams[DAT_GameSynchronyState::instance.protocolInvokerPlayerID] = iVar6;
                            break;
                        }
                        iVar6 = iVar6 + 1;
                    } while (iVar6 < 9);
                    /*
                      "has cancelled the alliance"   added by script: "has cancelled the alliance"
                     */
                    pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x27);
                    pcVar8 = DAT_GameSynchronyState::instance.receivedChatMessage;
                    do {
                        cVar1 = *pcVar5;
                        *pcVar8 = cVar1;
                        pcVar5 = pcVar5 + 1;
                        pcVar8 = pcVar8 + 1;
                    } while (cVar1 != '\0');
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                        DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.protocolInvokerPlayerID, 0);
                }
                if (DAT_GameSynchronyState::instance.DAT_GameCommandParam1 == 1) {
                    aiStack_24[1] = 0;
                    aiStack_24[2] = 0;
                    aiStack_24[3] = 0;
                    aiStack_24[4] = 0;
                    aiStack_24[5] = 0;
                    aiStack_24[6] = 0;
                    aiStack_24[7] = 0;
                    aiStack_24[8] = 0;
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[1]]
                            = aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[1]] + 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[2]]
                            = aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[2]] + 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[3]]
                            = aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[3]] + 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[4]]
                            = aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[4]] + 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[5]]
                            = aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[5]] + 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[6]]
                            = aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[6]] + 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[7]]
                            = aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[7]] + 1;
                    }
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] != -1) {
                        aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[8]]
                            = aiStack_24[DAT_GameState::instance.mapAndTime.playerTeams[8]] + 1;
                    }
                    bVar9 = aiStack_24[1] != 0;
                    if (aiStack_24[2] != 0) {
                        bVar9 = bVar9 + 1;
                    }
                    if (aiStack_24[3] != 0) {
                        bVar9 = bVar9 + 1;
                    }
                    if (aiStack_24[4] != 0) {
                        bVar9 = bVar9 + 1;
                    }
                    if (aiStack_24[5] != 0) {
                        bVar9 = bVar9 + 1;
                    }
                    if (aiStack_24[6] != 0) {
                        bVar9 = bVar9 + 1;
                    }
                    if (aiStack_24[7] != 0) {
                        bVar9 = bVar9 + 1;
                    }
                    if (aiStack_24[8] != 0) {
                        bVar9 = bVar9 + 1;
                    }
                    if ((2 < bVar9) || (aiStack_24[DAT_GameSynchronyState::instance.DAT_GameCommandParam0] != 1)) {
                        bVar2 = true;
                    }
                    iVar7 = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::countPlayersInSameTeam,
                        DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
                    iVar3 = DAT_GameSynchronyState::instance.protocolInvokerPlayerID;
                    if (((iVar7 < 2)
                            && (iVar7
                                = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::countPlayersInSameTeam,
                                    DAT_GameSynchronyState::ptr)(
                                    DAT_GameSynchronyState::instance.protocolInvokerPlayerID),
                                iVar7 < 2))
                        && (bVar2)) {
                        DAT_GameState::instance.mapAndTime.playerTeams[iVar6]
                            = DAT_GameState::instance.mapAndTime.playerTeams[iVar3];
                        /*
                          "has joined with"   added by script: "has joined with"
                         */
                        pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x26);
                        pcVar8 = DAT_GameSynchronyState::instance.receivedChatMessage;
                        do {
                            cVar1 = *pcVar5;
                            *pcVar8 = cVar1;
                            pcVar5 = pcVar5 + 1;
                            pcVar8 = pcVar8 + 1;
                        } while (cVar1 != '\0');
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                            DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0,
                            (int)((int)(DAT_GameSynchronyState::instance.protocolInvokerPlayerID)));
                    }
                }
            }
        }
    }

}
}
