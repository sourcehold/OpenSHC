#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Commands/CommandBuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::Tribes::AITribeType;
    using OpenSHC::Commands::CommandBuildingType;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Units::SomeTribeBehaviorType;
    using OpenSHC::Map::Units::Unit;
    using OpenSHC::Map::Units::UnitInstructionType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CD2A0
    void AICState ::recruitHarrassingSiegeEngines(int playerID)

    {

        uint _unitID;

        int iVar1;

        Unit* pUVar4;

        int _unit;

        int _tribeID;

        int _harrassingSiegeEnginesMax;

        int _recruitTimeoutValue;

        int _engineersGuild;

        int _aiType;

        int _tribeUID;

        int _buildingID;

        int _aicEnginesArrayIndex;

        CommandBuildingType _siegeEngineToBuild;

        _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;

        _engineersGuild = DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id;

        if ((_aiType != 0) && (499 < DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf])) {

            _harrassingSiegeEnginesMax = *(int*)((int)this + (_aiType + -1) * 0x2a4 + 0x1ec);

            if (0 < _harrassingSiegeEnginesMax) {

                _recruitTimeoutValue = DAT_GameState::instance.playerDataArray[playerID].harrasingEngineRecruitTimeout;

                if (_recruitTimeoutValue != 0) {

                    DAT_GameState::instance.playerDataArray[playerID].harrasingEngineRecruitTimeout
                        = _recruitTimeoutValue + -1;

                    return;
                }

                if ((DAT_GameState::instance.playerDataArray[playerID].harassingSiegeEnginesCountUnk
                        < _harrassingSiegeEnginesMax)
                    && (DAT_GameState::instance.playerDataArray[playerID].unknownHarrassingSiegeRelated < 0x14)) {

                    _tribeID = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0xa5];

                    if ((_tribeID == 0)
                        || ((DAT_TribesState::instance.tribes[_tribeID].uid
                                != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xa5]
                            || (DAT_TribesState::instance.tribes[_tribeID].size < 2)))) {

                        if (DAT_GameState::instance.playerDataArray[playerID].canStartSpending == 0) {

                            return;
                        }

                        if (DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf] < 30) {

                            return;
                        }

                        if (_engineersGuild < 1) {

                            return;
                        }

                        if (DAT_BuildingsState::instance.buildings[_engineersGuild].buildingType
                            != OpenSHC::Map::Buildings::BT_ENGINEERSGUILD) {

                            return;
                        }

                        _unitID = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                            OpenSHC::Map::Units::UT_E_ENGINEER, (undefined4)((int)(_engineersGuild)), playerID, 0);

                        if (_unitID == 0) {

                            return;
                        }

                        if ((_tribeID == 0)
                            || (DAT_TribesState::instance.tribes[_tribeID].uid
                                != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xa5])) {

                            _tribeID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribeForPlayer,
                                DAT_TribesState::ptr)(playerID);
                        }

                        _tribeUID = DAT_TribesState::instance.tribes[_tribeID].uid;

                        DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0xa5] = (short)_tribeID;

                        DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xa5] = _tribeUID;

                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                            _unitID, _tribeID);

                        DAT_UnitsState::instance.units[_unitID].aiUnitBehaviourType = 0x16;

                    }

                    else {

                        if (7 < DAT_GameState::instance.playerDataArray[playerID].harrassingSiegeEnginesIndex) {

                            DAT_GameState::instance.playerDataArray[playerID].harrassingSiegeEnginesIndex = 0;
                        }

                        iVar1 = (_aiType + -1) * 0xa9;

                        if (*(int*)((int)this
                                + (DAT_GameState::instance.playerDataArray[playerID].harrassingSiegeEnginesIndex
                                      + iVar1)
                                    * 4
                                + 0x1cc)
                            == 0) {

                            DAT_GameState::instance.playerDataArray[playerID].harrassingSiegeEnginesIndex = 0;
                        }

                        _aicEnginesArrayIndex
                            = DAT_GameState::instance.playerDataArray[playerID].harrassingSiegeEnginesIndex;

                        _siegeEngineToBuild
                            = *(CommandBuildingType*)((int)this + (iVar1 + _aicEnginesArrayIndex) * 4 + 0x1cc);

                        DAT_GameState::instance.playerDataArray[playerID].harrassingSiegeEnginesIndex
                            = _aicEnginesArrayIndex + 1;

                        iVar1 = MACRO_CALL_MEMBER(
                            OpenSHC::AI::AIVState_Func::findSpotNearEngineersGuild, DAT_AIVState::ptr)(playerID);

                        if (iVar1 == 0) {

                            return;
                        }

                        iVar1 = DAT_AIVState::instance.DAT_BuildingAppropriateGridYPosition * 5;

                        _aicEnginesArrayIndex = DAT_AIVState::instance.DAT_BuildingApproriateGridXPosition * 5;

                        DAT_TribesState::instance.tribes[_tribeID].tribeType = OpenSHC::AI::Tribes::AITT_ENGINEERS;

                        DAT_TribesState::instance.tribes[_tribeID].tribeBehaviorType
                            = OpenSHC::Map::Units::STBT_0x410_SIEGE_EQUIPMENT_CONSTRUCTION;

                        /*
                                    palce siege engine tent? */

                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                            playerID, _aicEnginesArrayIndex, iVar1, _siegeEngineToBuild, 3, 0xf);

                        _buildingID = DAT_TileMapState::instance.DAT_PlacedBuildingID;

                        if (DAT_TileMapState::instance.buildingPlacementFail != FALSE) {

                            return;
                        }

                        DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.DAT_PlacedBuildingID]
                            .attackWave = 0;

                        DAT_BuildingsState::instance.buildings[_buildingID].unknownSiegeTentRelated01 = 2;

                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeAnInstruction,
                            DAT_TribesState::ptr)(_tribeID,
                            OpenSHC::Map::Units::UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED, _buildingID,
                            DAT_BuildingsState::instance.buildings[_buildingID].uid, 0);
                    }

                    _unit = 1;

                    if (1 < (int)DAT_UnitsState::instance.maxUnitCount) {

                        pUVar4 = &DAT_UnitsState::instance.units[1];

                        do {

                            if ((((pUVar4->logicalState != OpenSHC::Map::Units::ULS_INVISIBLE) && (pUVar4->dying == 0))
                                    && ((pUVar4->unitType == OpenSHC::Map::Units::UT_S_CATAPULT
                                        || (pUVar4->unitType == OpenSHC::Map::Units::UT_S_FBALLISTA))))
                                && (pUVar4->aiUnitBehaviourType == 0x15)) {

                                pUVar4->siegeTargetPlayerID
                                    = (short)DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID;
                            }

                            _unit = _unit + 1;

                            pUVar4 = pUVar4 + 0x248;

                        } while (_unit < (int)DAT_UnitsState::instance.maxUnitCount);
                    }

                    DAT_GameState::instance.playerDataArray[playerID].harrasingEngineRecruitTimeout = 8;
                }
            }
        }

        return;
    }

}
}
