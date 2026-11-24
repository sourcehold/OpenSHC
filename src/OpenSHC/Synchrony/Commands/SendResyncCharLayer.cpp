#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00483A00
    void Commands::SendResyncCharLayer()
    {
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        // the layer's number, the chunk's number and one chunk of the layer: 2512 tiles of one byte each
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
            case 10:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .DamageLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 11:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .LuminesenceLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 12:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .WallOwnerLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 13:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .PathLinkageLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 14:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .OccupancyLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 15:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .HeightLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 16:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .AIInfoLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 17:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .AIZoneLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 18:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .SEC_TileMap1104[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 19:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .unitDeathHeatMap[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 20:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .SEC_PathfindingCostTileMap1105[0]
                                                       [DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 21:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .SEC_PathfindingCostTileMap1105[1]
                                                       [DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 22:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .SEC_PathfindingCostTileMap1105[2]
                                                       [DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 23:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .SEC_PathfindingCostTileMap1105[3]
                                                       [DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 24:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .SEC_PathfindingCostTileMap1105[4]
                                                       [DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 25:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .SEC_PathfindingCostTileMap1105[5]
                                                       [DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 26:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .SEC_PathfindingCostTileMap1105[6]
                                                       [DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 27:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .SEC_PathfindingCostTileMap1105[7]
                                                       [DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                    2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
                break;
            case 28:
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(
                    &DAT_TileMapState::instance
                        .SEC_PathfindingCostTileMap1105[8]
                                                       [DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
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
        case 10:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance.DamageLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 11:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .LuminesenceLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 12:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .WallOwnerLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 13:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .PathLinkageLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 14:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .OccupancyLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 15:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance.HeightLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 16:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance.AIInfoLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 17:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance.AIZoneLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 18:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .SEC_TileMap1104[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 19:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .unitDeathHeatMap[DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 20:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .SEC_PathfindingCostTileMap1105[0][DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 21:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .SEC_PathfindingCostTileMap1105[1][DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 22:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .SEC_PathfindingCostTileMap1105[2][DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 23:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .SEC_PathfindingCostTileMap1105[3][DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 24:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .SEC_PathfindingCostTileMap1105[4][DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 25:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .SEC_PathfindingCostTileMap1105[5][DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 26:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .SEC_PathfindingCostTileMap1105[6][DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 27:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .SEC_PathfindingCostTileMap1105[7][DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        case 28:
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(
                &DAT_TileMapState::instance
                    .SEC_PathfindingCostTileMap1105[8][DAT_GameSynchronyState::instance.DAT_GameCommandParam1 * 2512],
                2512, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            break;
        }
    }

}
}
