#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00483850
    void Commands::SharePlayerName()
    {
        char cVar1;
        char (*pacVar2)[250];
        int iVar3;
        int _receivedPlayerSlotID;
        int local_c;
        int _selectedLordType;
        int _somePlayerInformation;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 16;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&_receivedPlayerSlotID, 4,
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&_somePlayerInformation, 4,
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&local_c, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&_selectedLordType, 4,
                    OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                DAT_GameCore::instance.lordIcons[_receivedPlayerSlotID] = local_c;
                DAT_GameCore::instance.selectedLordTypes[_receivedPlayerSlotID] = _selectedLordType;
                if (DAT_GameSynchronyState::instance.isHost != FALSE) {
                    if (_receivedPlayerSlotID != _somePlayerInformation) {
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_receivedPlayerSlotID]
                            = DAT_GameSynchronyState::instance.DAT_CurrentPlayerFullIDArray2[_somePlayerInformation];
                        pacVar2 = DAT_GameSynchronyState::instance.playerNames2 + _somePlayerInformation;
                        iVar3 = (int)DAT_GameSynchronyState::instance.DAT_PlayerNames[_receivedPlayerSlotID]
                            - (int)pacVar2;
                        do {
                            cVar1 = (*pacVar2)[0];
                            *(char*)((int)pacVar2 + iVar3) = cVar1;
                            pacVar2 = (char (*)[250])(*pacVar2 + 1);
                        } while (cVar1 != '\0');
                    }
                    DAT_GameSynchronyState::instance.somePlayerRelatedArray[_receivedPlayerSlotID] = 1;
                    DAT_GameSynchronyState::instance.unknownPlayerInfo_01[_somePlayerInformation] = 1;
                }
                MACRO_CALL(OpenSHC::OS_Func::_memcpy)(
                    (void*)((_receivedPlayerSlotID + 0x13) * 0x2100
                        + (int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94),
                    (void*)((_somePlayerInformation + 0x1b) * 0x2100
                        + (int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94),
                    0x2100);
                DAT_TextureRenderCoreObject::instance.field69_0x98[_receivedPlayerSlotID + 0x13] = 8448;
            }
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.currentPlayerSlotID, 4,
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_SomePlayerID, 4,
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameCore::instance.lordIconUnk, 4,
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameCore::instance.selectedLordTypeUnk, 4,
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
        DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
    }

}
}
