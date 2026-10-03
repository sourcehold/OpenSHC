#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00485380
    void Commands::SomePlayerNameUpdateCommand()
    {
        char* lpMultiByteStr;
        char (*_playerName)[250];
        char (*_clickerPlayerName)[250];
        int _clickedByPlayer;
        char (*_finalResultsName)[90];
        char (*pacVar1)[250];
        ChatEvent* _chatEventArray;
        WCHAR local_20c[260];
        uint local_4;
        char _character;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)local_20c;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 500;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(local_20c, 500, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                    DAT_WideCharMultiByteState::ptr)(
                    DAT_GameSynchronyState::instance
                        .DAT_PlayerNames[DAT_GameSynchronyState::instance.protocolInvokerPlayerID],
                    (LPWSTR)((int)(local_20c)), 0xfa);
                _playerName = DAT_GameSynchronyState::instance.DAT_PlayerNames
                    + DAT_GameSynchronyState::instance.protocolInvokerPlayerID;
                _finalResultsName = DAT_GameSynchronyState::instance.finalResults.names
                    + DAT_GameSynchronyState::instance.protocolInvokerPlayerID;
                do {
                    _character = (*_playerName)[0];
                    (*_finalResultsName)[0] = _character;
                    _playerName = (char (*)[250])(*_playerName + 1);
                    _finalResultsName = (char (*)[90])(*_finalResultsName + 1);
                } while (_character != '\0');
                _playerName = DAT_GameSynchronyState::instance.DAT_ChatMessageObjectPlayerNameArray;
                _chatEventArray = DAT_GameSynchronyState::instance.DAT_ChatEventArray;
                _clickedByPlayer = DAT_GameSynchronyState::instance.protocolInvokerPlayerID;
                do {
                    if (_chatEventArray->flag == 1) {
                        if (_chatEventArray->subjectPlayer == _clickedByPlayer) {
                            _clickerPlayerName = DAT_GameSynchronyState::instance.DAT_PlayerNames + _clickedByPlayer;
                            pacVar1 = _playerName + -0x14;
                            do {
                                _character = (*_clickerPlayerName)[0];
                                (*pacVar1)[0] = _character;
                                _clickerPlayerName = (char (*)[250])(*_clickerPlayerName + 1);
                                pacVar1 = (char (*)[250])(*pacVar1 + 1);
                                _clickedByPlayer = DAT_GameSynchronyState::instance.protocolInvokerPlayerID;
                            } while (_character != '\0');
                        }
                        if (_chatEventArray->objectPlayer == _clickedByPlayer) {
                            _clickerPlayerName = DAT_GameSynchronyState::instance.DAT_PlayerNames + _clickedByPlayer;
                            pacVar1 = _playerName;
                            do {
                                _character = (*_clickerPlayerName)[0];
                                (*pacVar1)[0] = _character;
                                _clickerPlayerName = (char (*)[250])(*_clickerPlayerName + 1);
                                pacVar1 = (char (*)[250])(*pacVar1 + 1);
                                _clickedByPlayer = DAT_GameSynchronyState::instance.protocolInvokerPlayerID;
                            } while (_character != '\0');
                        }
                    }
                    _chatEventArray = _chatEventArray + 1;
                    _playerName = _playerName + 1;
                } while ((int)_chatEventArray < 0x1a22f20);
            };
            return;
        }
        _clickedByPlayer = 0xfa;
        lpMultiByteStr = MACRO_CALL_MEMBER(
            OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0);
        MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::multiByteToWideCharWithSize,
            DAT_WideCharMultiByteState::ptr)(local_20c, (LPCSTR)((int)(lpMultiByteStr)), _clickedByPlayer);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(local_20c, 500, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
        DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
        ;
    }

}
}
