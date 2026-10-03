#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Buildings::BuildingTypeShort;

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
    // FUNCTION: STRONGHOLDCRUSADER 0x00485830
    void Commands::SetUnitAssemblyPoint()
    {
        BuildingTypeShort BVar1;
        uint uVar2;
        uint _y;
        int iVar3;
        short _x;
        short local_4[2];
        int _unitCategory;
        int _playerID;
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
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(local_4, 1, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = (int)(char)local_4[0];
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(local_4, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = (uint)local_4[0];
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(local_4, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            _playerID = DAT_GameSynchronyState::instance.protocolInvokerPlayerID;
            uVar2 = DAT_GameSynchronyState::instance.DAT_GameCommandParam1;
            _unitCategory = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
            _y = (uint)local_4[0];
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = _y;
            if (((DAT_GameSynchronyState::instance.DAT_GameCommandParam1 < 400) && (_y < 400))
                && (*(char*)(_y * 400 + 0x21aec98 + DAT_GameSynchronyState::instance.DAT_GameCommandParam1) != '\0')) {
                _x = (short)DAT_GameSynchronyState::instance.DAT_GameCommandParam1;
                if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 < 10) {
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]
                        .barracksAssemblyPoints[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                        .x = _x;
                    DAT_GameState::instance.playerDataArray[_playerID].barracksAssemblyPoints[_unitCategory].y
                        = local_4[0];
                    iVar3 = (int)DAT_TileMapState::instance
                                .BuildingLayer[DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile
                                    + uVar2];
                    if ((iVar3 != 0) && (DAT_BuildingsState::instance.buildings[iVar3].owner == _playerID)) {
                        switch (DAT_BuildingsState::instance.buildings[iVar3].buildingType) {
                        case OpenSHC::Map::Buildings::BT_MERCENARYPOST:
                        case OpenSHC::Map::Buildings::BT_BARRACKS:
                        case OpenSHC::Map::Buildings::BT_PARADEGROUND2:
                        case OpenSHC::Map::Buildings::BT_PARADEGROUND3:
                        case OpenSHC::Map::Buildings::BT_PARADEGROUND4:
                            DAT_GameState::instance.playerDataArray[_playerID].barracksAssemblyPoints[_unitCategory].x
                                = 0;
                            DAT_GameState::instance.playerDataArray[_playerID].barracksAssemblyPoints[_unitCategory].y
                                = 0;
                        }
                    }
                } else if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 < 0x14) {
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]
                        .mercenaryAssemblyPoints[DAT_GameSynchronyState::instance.DAT_GameCommandParam0 + -10][0] = _x;
                    DAT_GameState::instance.playerDataArray[_playerID].mercenaryAssemblyPoints[_unitCategory + -10][1]
                        = local_4[0];
                    iVar3 = (int)DAT_TileMapState::instance
                                .BuildingLayer[DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile
                                    + uVar2];
                    if ((iVar3 != 0) && (DAT_BuildingsState::instance.buildings[iVar3].owner == _playerID)) {
                        switch (DAT_BuildingsState::instance.buildings[iVar3].buildingType) {
                        case OpenSHC::Map::Buildings::BT_MERCENARYPOST:
                        case OpenSHC::Map::Buildings::BT_BARRACKS:
                        case OpenSHC::Map::Buildings::BT_PARADEGROUND2:
                        case OpenSHC::Map::Buildings::BT_PARADEGROUND3:
                        case OpenSHC::Map::Buildings::BT_PARADEGROUND4:
                            DAT_GameState::instance.playerDataArray[_playerID]
                                .mercenaryAssemblyPoints[_unitCategory + -10][0] = 0;
                            DAT_GameState::instance.playerDataArray[_playerID]
                                .mercenaryAssemblyPoints[_unitCategory + -10][1] = 0;
                        }
                    }
                } else if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 < 0x1e) {
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]
                        .mercenaryAssemblyPoints[DAT_GameSynchronyState::instance.DAT_GameCommandParam0 + 1][0] = _x;
                    DAT_GameState::instance.playerDataArray[_playerID].mercenaryAssemblyPoints[_unitCategory + 1][1]
                        = local_4[0];
                    iVar3 = (int)DAT_TileMapState::instance
                                .BuildingLayer[DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile
                                    + uVar2];
                    if (((iVar3 != 0) && (DAT_BuildingsState::instance.buildings[iVar3].owner == _playerID))
                        && ((BVar1 = DAT_BuildingsState::instance.buildings[iVar3].buildingType,
                            BVar1 == OpenSHC::Map::Buildings::BT_ENGINEERSGUILD
                                || (BVar1 == OpenSHC::Map::Buildings::BT_PARADEGROUND)))) {
                        DAT_GameState::instance.playerDataArray[_playerID].mercenaryAssemblyPoints[_unitCategory + 1][0]
                            = 0;
                        DAT_GameState::instance.playerDataArray[_playerID].mercenaryAssemblyPoints[_unitCategory + 1][1]
                            = 0;
                    }
                } else if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 < 0x28) {
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]
                        .tunnelersGuildAssemblyPointY = local_4[0];
                    iVar3 = (int)DAT_TileMapState::instance
                                .BuildingLayer[DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile
                                    + uVar2];
                    DAT_GameState::instance.playerDataArray[_playerID].tunnelersGuildAssemblyPointX = _x;
                    if (((iVar3 != 0) && (DAT_BuildingsState::instance.buildings[iVar3].owner == _playerID))
                        && ((BVar1 = DAT_BuildingsState::instance.buildings[iVar3].buildingType,
                            BVar1 == OpenSHC::Map::Buildings::BT_TUNNELERSGUILD
                                || (BVar1 == OpenSHC::Map::Buildings::BT_PARADEGROUND5)))) {
                        DAT_GameState::instance.playerDataArray[_playerID].tunnelersGuildAssemblyPointX = 0;
                        DAT_GameState::instance.playerDataArray[_playerID].tunnelersGuildAssemblyPointY = 0;
                    }
                } else if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 < 0x32) {
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]
                        .cathedralAssemblyPointY = local_4[0];
                    iVar3 = (int)DAT_TileMapState::instance
                                .BuildingLayer[DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile
                                    + uVar2];
                    DAT_GameState::instance.playerDataArray[_playerID].cathedralAssemblyPointX = _x;
                    if (((iVar3 != 0) && (DAT_BuildingsState::instance.buildings[iVar3].owner == _playerID))
                        && (DAT_BuildingsState::instance.buildings[iVar3].buildingType
                            == OpenSHC::Map::Buildings::BT_CATHEDRAL)) {
                        DAT_GameState::instance.playerDataArray[_playerID].cathedralAssemblyPointX = 0;
                        DAT_GameState::instance.playerDataArray[_playerID].cathedralAssemblyPointY = 0;
                    }
                }
            }
        }
    }

}
}
