#include "../Commands.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00484B10
    void Commands::RemoveTowerSiegeEngine()
    {
        // what to remove (1 an entity, 2 a unit) and its ID
        DAT_GameSynchronyState::instance.DAT_CommandSize = 4;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 2,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 2,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        short readBuffer;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&readBuffer, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = readBuffer;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&readBuffer, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        int const id = readBuffer;
        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = id;
        switch (DAT_GameSynchronyState::instance.DAT_GameCommandParam0) {
        case 2: {
            // a unit is removed; a tower's mangonel or ballista also clears the tower's engine and refunds its cost
            OpenSHC::Map::Units::UnitTypeShort const unitType = DAT_UnitsState::instance.units[id].unitType;
            int const buildingID = DAT_TileMapState::instance.BuildingLayer[DAT_UnitsState::instance.units[id].tile];
            if (unitType == OpenSHC::Map::Units::UT_S_MANGONEL) {
                if (buildingID != 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].defensiveTowerEngineType = 0;
                }
                // -3 asks for a tower mangonel's cost
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                    DAT_BuildingsState::ptr)(-3, DAT_GameSynchronyState::instance.protocolInvokerPlayerID, 100);
            } else if (unitType == OpenSHC::Map::Units::UT_S_BALLISTA) {
                if (buildingID != 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].defensiveTowerEngineType = 0;
                }
                // -4 asks for a tower ballista's cost
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                    DAT_BuildingsState::ptr)(-4, DAT_GameSynchronyState::instance.protocolInvokerPlayerID, 100);
            }
            DAT_UnitsState::instance.units[id].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            break;
        }
        case 1:
            // 3 marks it destroyed, as markEntityDestroyed does
            DAT_EntityState::instance.entityArray[id].logicalState = 3;
            break;
        }
    }

}
}
