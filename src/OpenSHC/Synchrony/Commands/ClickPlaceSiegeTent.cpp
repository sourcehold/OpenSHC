#include "../Commands.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/WallAndPitchState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004827E0
    void Commands::ClickPlaceSiegeTent()
    {
        // the unit's x, y and terrain height (two bytes each) and its type (one byte)
        DAT_GameSynchronyState::instance.DAT_CommandSize = 7;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 2,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 2,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam2, 2,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam3, 1,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        // each parameter is cleared before its low bytes are received
        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 2,
            OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 2,
            OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = 0;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam2, 2,
            OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam3, 1,
            OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        // outside single player the sender needs the resources for the engine
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            OpenSHC::Commands::MappersEnum mapper = OpenSHC::Commands::M_MAPPER_NULL;
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam3 == OpenSHC::Map::Units::UT_S_MANGONEL) {
                mapper = OpenSHC::Commands::M_MAPPER_MANGONEL;
            } else if (DAT_GameSynchronyState::instance.DAT_GameCommandParam3 == OpenSHC::Map::Units::UT_S_BALLISTA) {
                mapper = OpenSHC::Commands::M_MAPPER_BALLISTA;
            }
            if (mapper != OpenSHC::Commands::M_MAPPER_NULL
                && !MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy,
                    DAT_GameState::ptr)(mapper, DAT_GameSynchronyState::instance.protocolInvokerPlayerID, FALSE)) {
                return;
            }
        }
        // a tower that already carries an engine takes no second one
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam3 == OpenSHC::Map::Units::UT_S_MANGONEL
            || DAT_GameSynchronyState::instance.DAT_GameCommandParam3 == OpenSHC::Map::Units::UT_S_BALLISTA) {
            int const buildingID
                = DAT_TileMapState::instance.BuildingLayer
                      [DAT_ViewportRenderState::instance
                              .translationMatrix[(int)DAT_GameSynchronyState::instance.DAT_GameCommandParam1 / 8]
                              .addXgetTile
                          + DAT_GameSynchronyState::instance.DAT_GameCommandParam0 / 8];
            if (buildingID != 0 && DAT_BuildingsState::instance.buildings[buildingID].defensiveTowerEngineType != 0) {
                return;
            }
        }
        int const unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
            DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
            DAT_GameSynchronyState::instance.protocolInvokerPlayerID,
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0,
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1,
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2,
            (OpenSHC::Map::Units::UnitType)DAT_GameSynchronyState::instance.DAT_GameCommandParam3);
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam3 == OpenSHC::Map::Units::UT_S_MANGONEL) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processPlacementResourceLossForBuildingType,
                DAT_BuildingsState::ptr)(
                DAT_GameSynchronyState::instance.protocolInvokerPlayerID, OpenSHC::Map::Buildings::BT_MANGONEL, 0);
        } else if (DAT_GameSynchronyState::instance.DAT_GameCommandParam3 == OpenSHC::Map::Units::UT_S_BALLISTA) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processPlacementResourceLossForBuildingType,
                DAT_BuildingsState::ptr)(
                DAT_GameSynchronyState::instance.protocolInvokerPlayerID, OpenSHC::Map::Buildings::BT_BALLISTA, 0);
        }
        // the tower under the new engine counts as occupied
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam3 == OpenSHC::Map::Units::UT_S_MANGONEL
            || DAT_GameSynchronyState::instance.DAT_GameCommandParam3 == OpenSHC::Map::Units::UT_S_BALLISTA) {
            int const buildingID
                = DAT_TileMapState::instance.BuildingLayer
                      [DAT_ViewportRenderState::instance
                              .translationMatrix[(int)DAT_GameSynchronyState::instance.DAT_GameCommandParam1 / 8]
                              .addXgetTile
                          + DAT_GameSynchronyState::instance.DAT_GameCommandParam0 / 8];
            if (buildingID != 0) {
                int const buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
                if (buildingType == OpenSHC::Map::Buildings::BT_TOWER1
                    || buildingType == OpenSHC::Map::Buildings::BT_TOWER4) {
                    DAT_BuildingsState::instance.buildings[buildingID].hasUnitsOntop = 1;
                    DAT_BuildingsState::instance.buildings[buildingID].tileScanCountdown = 100;
                }
            }
        }
        if (DAT_GameSynchronyState::instance.protocolInvokerPlayerID
            == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            MACRO_CALL_MEMBER(OpenSHC::Map::WallAndPitchState_Func::startUnitDestructionConfirmation,
                DAT_WallAndPitchState::ptr)(unitID);
        }
    }

}
}
