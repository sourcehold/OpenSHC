#include "../Commands.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004826C0
    void Commands::ClickDestroy()
    {
        DAT_GameSynchronyState::instance.DAT_CommandSize = 5;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 1,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
            OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        char readBuffer;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&readBuffer, 1, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = readBuffer;
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam1 == -1) {
            uint const moatID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile,
                DAT_TileMapState::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
            int const tile = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
            if (moatID != 0) {
                DAT_TileMapState::instance.moats[moatID].fillProgress = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::removeMoat, DAT_TileMapState::ptr)(moatID, tile);
            }
            DAT_TileMapState::instance.MiscDisplayLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                &= ~1024;
            return;
        }
        if (DAT_TileMapState::instance.HeightLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                - DAT_TileMapState::instance.DefaultHeightLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
            <= 60) {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                = (int)DAT_GameSynchronyState::instance.DAT_GameCommandParam1 / 2;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
            DAT_BuildingsState::ptr)(-1, DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::spawnEraserTileEffect, DAT_TileMapState::ptr)(
            DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
    }

}
}
