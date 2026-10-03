#include "../../Synchrony.func.hpp"
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

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::UnitTypeShort;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00484B10
    void Commands::RemoveTowerSiegeEngine()
    {
        UnitTypeShort UVar1;
        int iVar2;
        int _entity;
        short local_4[2];
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
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(local_4, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = (int)local_4[0];
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(local_4, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        _entity = (int)local_4[0];
        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _entity;
        switch (DAT_GameSynchronyState::instance.DAT_GameCommandParam0) {
        case 2:
            UVar1 = DAT_UnitsState::instance.units[_entity].unitType;
            iVar2 = (int)DAT_TileMapState::instance.BuildingLayer[DAT_UnitsState::instance.units[_entity].tile];
            if (UVar1 == OpenSHC::Map::Units::UT_S_MANGONEL) {
                if (iVar2 != 0) {
                    DAT_BuildingsState::instance.buildings[iVar2].containsSiegeMangonel1OrBallista2 = 0;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                    DAT_BuildingsState::ptr)(
                    -3, (int)((int)(DAT_GameSynchronyState::instance.protocolInvokerPlayerID)), 100);
            } else if (UVar1 == OpenSHC::Map::Units::UT_S_BALLISTA) {
                if (iVar2 != 0) {
                    DAT_BuildingsState::instance.buildings[iVar2].containsSiegeMangonel1OrBallista2 = 0;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                    DAT_BuildingsState::ptr)(
                    -4, (int)((int)(DAT_GameSynchronyState::instance.protocolInvokerPlayerID)), 100);
            }
            DAT_UnitsState::instance.units[_entity].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            return;
        case 1:
            DAT_EntityState::instance.entityArray[_entity].logicalState = 3;
            return;
        }
    }

}
}
