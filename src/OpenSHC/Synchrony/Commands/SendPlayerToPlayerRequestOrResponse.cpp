#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/Actions.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeMin1.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00486140
    void Commands::SendPlayerToPlayerRequestOrResponse()
    {
        // the kind of message, then four values that depend on it
        DAT_GameSynchronyState::instance.DAT_CommandSize = 18;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 2,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 4,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam2, 4,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam3, 4,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam4, 4,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        short messageKind;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&messageKind, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = messageKind;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 4,
            OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam2, 4,
            OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam3, 4,
            OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam4, 4,
            OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        switch (DAT_GameSynchronyState::instance.DAT_GameCommandParam0) {
        case 0:
            MACRO_CALL(OpenSHC::Synchrony::Actions_Func::ProcessAllyRequestAttackDefense)(
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1,
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2,
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3,
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4);
            break;
        case 1:
            MACRO_CALL(OpenSHC::Synchrony::Actions_Func::ProcessAllyRequestingGoods)(
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1,
                (OpenSHC::Game::Resources::ResourceTypeMin1)DAT_GameSynchronyState::instance.DAT_GameCommandParam2,
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3,
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4);
            break;
        case 2:
            MACRO_CALL(OpenSHC::Synchrony::Actions_Func::ProcessAllyGoodsRequest)(
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1,
                (OpenSHC::Game::Resources::ResourceType)DAT_GameSynchronyState::instance.DAT_GameCommandParam2,
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3,
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4);
            break;
        case 3:
            MACRO_CALL(OpenSHC::Synchrony::Actions_Func::ProcessAllyDeniesRequest)(
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1,
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4);
            break;
        case 4:
            MACRO_CALL(OpenSHC::Synchrony::Actions_Func::ProcessAllyAcceptsRequest)(
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1,
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4);
            break;
        case 5:
            MACRO_CALL(OpenSHC::Synchrony::Actions_Func::ProcessAllyDeniesRequest2)(
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1,
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4);
            break;
        }
    }

}
}
