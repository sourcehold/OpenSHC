#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004840C0
    void Commands::ResyncShortLayer()
    {
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        // the layer's number, the chunk's number and one chunk of the layer: 1256 tiles, 2512 bytes
        DAT_GameSynchronyState::instance.DAT_CommandSize = 2520;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            switch (DAT_GameSynchronyState::instance.DAT_GameCommandParam0) {
            case 1:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .RandomLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 2:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .WalkLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 3:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .OrganismLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 4:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .BuildingLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 5:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .UnitLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 6:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .EntityLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 7:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .CertainPathLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 8:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .PathConnectionLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 9:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .MacroLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            }
            return;
        }
        // only the clients take the host's copy of the layer
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE
            || DAT_GameSynchronyState::instance.isHost) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 4,
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        switch (DAT_GameSynchronyState::instance.DAT_GameCommandParam0) {
        case 1:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance.RandomLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 2:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance.WalkLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 3:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .OrganismLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 4:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .BuildingLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 5:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance.UnitLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 6:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance.EntityLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 7:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .CertainPathLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 8:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .PathConnectionLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 9:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance.MacroLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 1256],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        }
    }

}
}
