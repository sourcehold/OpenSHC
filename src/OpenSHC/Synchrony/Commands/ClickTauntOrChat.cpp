#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/Audio/mss/SoundFlagsAndLoopCount.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_ProtocolDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Audio::MSS::SoundFlagsAndLoopCount;
    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::IO::FileResourceType;

    /*
      WARNING: Type propagation algorithm not settling
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004895E0
    void Commands::ClickTauntOrChat()
    {
        char cVar1;
        char* pcVar2;
        char* pcVar3;
        int iVar4;
        SoundFlagsAndLoopCount SVar5;
        int _tauntOrChat[10];
        WCHAR _messageRaw[260];
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)_tauntOrChat;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 0x220;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            if ((DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE)
                && (DAT_GameSynchronyState::instance.protocolInvokerPlayerID - 1U < 8)) {
                _tauntOrChat[1] = 0;
                _tauntOrChat[2] = 0;
                _tauntOrChat[3] = 0;
                _tauntOrChat[4] = 0;
                _tauntOrChat[5] = 0;
                _tauntOrChat[6] = 0;
                _tauntOrChat[7] = 0;
                _tauntOrChat[8] = 0;
                _tauntOrChat[9] = 0;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(_tauntOrChat, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(_messageRaw, 500, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                    DAT_WideCharMultiByteState::ptr)(DAT_GameSynchronyState::instance.receivedChatMessage,
                    (LPWSTR)((int)(_messageRaw)), (int)((int)(250)));
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(_tauntOrChat + 1, (size_t)((int)(36)),
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                if (_tauntOrChat[DAT_GameSynchronyState::instance.currentPlayerSlotID + 1] != 0) {
                    /*
                      message is meant for this player
                     */
                    if (_tauntOrChat[0] == 10000) {
                        iVar4 = 0;
                    } else if (_tauntOrChat[0] < 0) {
                        _tauntOrChat[0] = -1 - _tauntOrChat[0];
                        pcVar2 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_INSULTS, (int)((int)(_tauntOrChat[0])));
                        pcVar3 = DAT_GameSynchronyState::instance.receivedChatMessage;
                        do {
                            cVar1 = *pcVar2;
                            *pcVar3 = cVar1;
                            pcVar2 = pcVar2 + 1;
                            pcVar3 = pcVar3 + 1;
                        } while (cVar1 != '\0');
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                            DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_GFX_SPEECH,
                            (char const*)((int)(DAT_ProtocolDefinedData::instance.commandFunctions[_tauntOrChat[0]])));
                        SVar5 = -536870911;
                        pcVar2
                            = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::getFileNameOfCurrentActiveResource,
                                DAT_ResourceManager::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk,
                            DAT_SoundSystemState::ptr)(pcVar2, SVar5);
                        iVar4 = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
                    } else {
                        iVar4 = DAT_GameSynchronyState::instance.protocolInvokerPlayerID;
                        if (_tauntOrChat[0] != 0) {
                            pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_INSULTS, (int)((int)(_tauntOrChat[0])));
                            pcVar3 = DAT_GameSynchronyState::instance.receivedChatMessage;
                            do {
                                cVar1 = *pcVar2;
                                *pcVar3 = cVar1;
                                pcVar2 = pcVar2 + 1;
                                pcVar3 = pcVar3 + 1;
                            } while (cVar1 != '\0');
                            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                                DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_GFX_SPEECH,
                                (char const*)((
                                    int)(DAT_ProtocolDefinedData::instance.commandFunctions[_tauntOrChat[0]])));
                            SVar5 = -536870911;
                            pcVar2 = MACRO_CALL_MEMBER(
                                OpenSHC::IO::ResourceManager_Func::getFileNameOfCurrentActiveResource,
                                DAT_ResourceManager::ptr)();
                            MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk,
                                DAT_SoundSystemState::ptr)(pcVar2, SVar5);
                            iVar4 = DAT_GameSynchronyState::instance.protocolInvokerPlayerID;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                        DAT_GameSynchronyState::ptr)(iVar4, 0);
                }
            };
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage, 4,
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
        iVar4 = 0xfa;
        pcVar2
            = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::multiByteToWideCharWithSize,
            DAT_WideCharMultiByteState::ptr)(_messageRaw, (LPCSTR)((int)(pcVar2)), iVar4);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(_messageRaw, 500, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray, 0x24,
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
        DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
        ;
    }

}
}
