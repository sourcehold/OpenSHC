#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00485830
    void Commands::SetUnitAssemblyPoint()
    {
        // the unit category (one byte) and the point's x and y (two bytes each)
        DAT_GameSynchronyState::instance.DAT_CommandSize = 5;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 1,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 2,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam2, 2,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        // the three parameters are received one after the other into the same four bytes, as in the original
        int received;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&received, 1, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = (char)received;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&received, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = (short)received;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&received, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        int const playerID = DAT_GameSynchronyState::instance.protocolInvokerPlayerID;
        uint const x = DAT_GameSynchronyState::instance.DAT_GameCommandParam1;
        uint const y = (short)received;
        DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = y;
        // the point has to be on the map
        if (x > OpenSHC::Map::MC_MAP_XY_LIMIT_INCLUSIVE || y > OpenSHC::Map::MC_MAP_XY_LIMIT_INCLUSIVE) {
            return;
        }
        if (!DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * OpenSHC::Map::MC_MAP_XY_LIMIT + x]) {
            return;
        }
        // the category is read from the parameter each time (a local for it loses the match)
        // 0 to 9, the barracks' units: a point on the sender's own barracks, mercenary post or parade ground clears it
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 < 10) {
            DAT_GameState::instance.playerDataArray[playerID]
                .barracksAssemblyPoints[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                .x = x;
            DAT_GameState::instance.playerDataArray[playerID]
                .barracksAssemblyPoints[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                .y = y;
            int const buildingID
                = DAT_TileMapState::instance
                      .BuildingLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
            if (buildingID == 0) {
                return;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].owner != playerID) {
                return;
            }
            switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
            case OpenSHC::Map::Buildings::BT_MERCENARYPOST:
            case OpenSHC::Map::Buildings::BT_BARRACKS:
            case OpenSHC::Map::Buildings::BT_PARADEGROUND2:
            case OpenSHC::Map::Buildings::BT_PARADEGROUND3:
            case OpenSHC::Map::Buildings::BT_PARADEGROUND4:
                DAT_GameState::instance.playerDataArray[playerID]
                    .barracksAssemblyPoints[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                    .x = 0;
                DAT_GameState::instance.playerDataArray[playerID]
                    .barracksAssemblyPoints[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                    .y = 0;
                break;
            }
            return;
        }
        // 10 to 19, the mercenary post's units, cleared on the same buildings
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 < 20) {
            DAT_GameState::instance.playerDataArray[playerID]
                .mercenaryAssemblyPoints[DAT_GameSynchronyState::instance.DAT_GameCommandParam0 - 10][0] = x;
            DAT_GameState::instance.playerDataArray[playerID]
                .mercenaryAssemblyPoints[DAT_GameSynchronyState::instance.DAT_GameCommandParam0 - 10][1] = y;
            int const buildingID
                = DAT_TileMapState::instance
                      .BuildingLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
            if (buildingID == 0) {
                return;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].owner != playerID) {
                return;
            }
            switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
            case OpenSHC::Map::Buildings::BT_MERCENARYPOST:
            case OpenSHC::Map::Buildings::BT_BARRACKS:
            case OpenSHC::Map::Buildings::BT_PARADEGROUND2:
            case OpenSHC::Map::Buildings::BT_PARADEGROUND3:
            case OpenSHC::Map::Buildings::BT_PARADEGROUND4:
                DAT_GameState::instance.playerDataArray[playerID]
                    .mercenaryAssemblyPoints[DAT_GameSynchronyState::instance.DAT_GameCommandParam0 - 10][0] = 0;
                DAT_GameState::instance.playerDataArray[playerID]
                    .mercenaryAssemblyPoints[DAT_GameSynchronyState::instance.DAT_GameCommandParam0 - 10][1] = 0;
                break;
            }
            return;
        }
        // 20 to 29, the engineers guild's units
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 < 30) {
            DAT_GameState::instance.playerDataArray[playerID]
                .specialBuildingAssemblyPoints[DAT_GameSynchronyState::instance.DAT_GameCommandParam0 - 20]
                .x = x;
            DAT_GameState::instance.playerDataArray[playerID]
                .specialBuildingAssemblyPoints[DAT_GameSynchronyState::instance.DAT_GameCommandParam0 - 20]
                .y = y;
            int const buildingID
                = DAT_TileMapState::instance
                      .BuildingLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
            if (buildingID == 0) {
                return;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].owner != playerID) {
                return;
            }
            int const buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
            if (buildingType == OpenSHC::Map::Buildings::BT_ENGINEERSGUILD
                || buildingType == OpenSHC::Map::Buildings::BT_PARADEGROUND) {
                DAT_GameState::instance.playerDataArray[playerID]
                    .specialBuildingAssemblyPoints[DAT_GameSynchronyState::instance.DAT_GameCommandParam0 - 20]
                    .x = 0;
                DAT_GameState::instance.playerDataArray[playerID]
                    .specialBuildingAssemblyPoints[DAT_GameSynchronyState::instance.DAT_GameCommandParam0 - 20]
                    .y = 0;
            }
            return;
        }
        // 30 to 39, the tunnelers guild's units
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 < 40) {
            DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[2].x = x;
            DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[2].y = y;
            int const buildingID
                = DAT_TileMapState::instance
                      .BuildingLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
            if (buildingID == 0) {
                return;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].owner != playerID) {
                return;
            }
            int const buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
            if (buildingType == OpenSHC::Map::Buildings::BT_TUNNELERSGUILD
                || buildingType == OpenSHC::Map::Buildings::BT_PARADEGROUND5) {
                DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[2].x = 0;
                DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[2].y = 0;
            }
            return;
        }
        // 40 to 49, the cathedral's units
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 < 50) {
            DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[3].x = x;
            DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[3].y = y;
            int const buildingID
                = DAT_TileMapState::instance
                      .BuildingLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
            if (buildingID == 0) {
                return;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].owner != playerID) {
                return;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_CATHEDRAL) {
                DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[3].x = 0;
                DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[3].y = 0;
            }
        }
    }

}
}
