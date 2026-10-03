#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/Actions.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::Game::Resources::ResourceType;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00486140
    void Commands::SendPlayerToPlayerRequestOrResponse()
    {
        short local_4[2];
        DAT_GameSynchronyState::instance.DAT_CommandSize = 0x12;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(local_4, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = (int)local_4[0];
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 4,
                    OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam2, 4,
                    OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam3, 4,
                    OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam4, 4,
                    OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                switch (DAT_GameSynchronyState::instance.DAT_GameCommandParam0) {
                case 0:
                    MACRO_CALL(OpenSHC::Synchrony::Actions_Func::ProcessAllyRequestAttackDefense)(
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1,
                        (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam2)),
                        (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam3)),
                        (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam4)));
                    return;
                case 1:
                    MACRO_CALL(OpenSHC::Synchrony::Actions_Func::ProcessAllyRequestingGoods)(
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1,
                        (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam2)),
                        (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam3)),
                        (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam4)));
                    return;
                case 2:
                    MACRO_CALL(OpenSHC::Synchrony::Actions_Func::ProcessAllyGoodsRequest)(
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1,
                        (ResourceType)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam2)),
                        (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam3)),
                        (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam4)));
                    return;
                case 3:
                    MACRO_CALL(OpenSHC::Synchrony::Actions_Func::ProcessAllyDeniesRequest)(
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1,
                        (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam4)));
                    return;
                case 4:
                    MACRO_CALL(OpenSHC::Synchrony::Actions_Func::ProcessAllyAcceptsRequest)(
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1,
                        (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam4)));
                    return;
                case 5:
                    MACRO_CALL(OpenSHC::Synchrony::Actions_Func::ProcessAllyDeniesRequest2)(
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1,
                        (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam4)));
                }
            }
            return;
        }
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
    }

}
}
