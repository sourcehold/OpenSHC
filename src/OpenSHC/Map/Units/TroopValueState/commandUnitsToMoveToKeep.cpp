#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using AI::Tribes::AITribeType;
        using Map::Buildings::BuildingType;
        using Map::Buildings::BuildingTypeShort;
        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;
        using Map::Units::Instructions::UnitMatchSpeedEnum;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051C800
        void TroopValueState::commandUnitsToMoveToKeep()
        {
            UnitTypeShort UVar1;
            int _swordsTribe;
            int _archersTribe;
            BOOLEnum BVar2;
            uint y1;
            uint _unitID;
            Unit* _pUnit;
            uint x1;
            int _playerID;
            uint _keep;
            int _theTribe;
            BuildingTypeShort _buildingType;
            uint _max;
            _playerID = this->attackInfo.pitchRelatedPlayerID;
            _keep = DAT_GameState::instance.playerDataArray[this->attackInfo.pitchRelatedPlayerID].keep.id;
            if (0 < (int)_keep) {
                _buildingType = DAT_BuildingsState::instance.buildings[_keep].buildingType;
                if (_buildingType == Map::Buildings::BT_MANORHOUSE) {
                    x1 = (int)(short)DAT_BuildingsState::instance.buildings[_keep].x + 3;
                    y1 = (int)(short)DAT_BuildingsState::instance.buildings[_keep].y + 8;
                } else if (_buildingType == Map::Buildings::BT_STONEKEEP) {
                    x1 = (int)(short)DAT_BuildingsState::instance.buildings[_keep].x + 3;
                    y1 = (int)(short)DAT_BuildingsState::instance.buildings[_keep].y + 3;
                } else if (_buildingType == Map::Buildings::BT_STRONGHOLD) {
                    x1 = (int)(short)DAT_BuildingsState::instance.buildings[_keep].x + 3;
                    y1 = (int)(short)DAT_BuildingsState::instance.buildings[_keep].y + 3;
                } else if (_buildingType == Map::Buildings::BT_KEEPFOUR) {
                    x1 = (int)(short)DAT_BuildingsState::instance.buildings[_keep].x + 4;
                    y1 = (int)(short)DAT_BuildingsState::instance.buildings[_keep].y + 4;
                } else {
                    if (_buildingType != Map::Buildings::BT_KEEPFIVE) {}
                    x1 = (int)(short)DAT_BuildingsState::instance.buildings[_keep].x + 5;
                    y1 = (int)(short)DAT_BuildingsState::instance.buildings[_keep].y + 5;
                }
                _swordsTribe = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe,
                    DAT_TribesState::ptr)(this->attackInfo.pitchRelatedPlayerID, 0);
                DAT_TribesState::instance.tribes[_swordsTribe].tribeType = AI::Tribes::AITT_SWORDSMEN;
                _archersTribe = MACRO_CALL_MEMBER(
                    Map::Units::TribesState_Func::createTribe, DAT_TribesState::ptr)(_playerID, 0);
                _max = DAT_UnitsState::instance.maxUnitCount;
                _unitID = 1;
                DAT_TribesState::instance.tribes[_archersTribe].tribeType = AI::Tribes::AITT_ARCHERS;
                if (1 < (int)_max) {
                    _pUnit = &DAT_UnitsState::instance.units[1];
                    do {
                        if ((((_pUnit->logicalState != Map::Units::ULS_INVISIBLE)
                                 && (BVar2
                                     = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep,
                                         this)((int)_pUnit->owner),
                                     BVar2))
                                && ((
                                    (UVar1 = _pUnit->unitType,
                                        UVar1 == Map::Units::UT_E_MACE
                                            || ((UVar1 == Map::Units::UT_E_SWORD || (UVar1 == Map::Units::UT_E_SPEAR))))
                                    || (((UVar1 == Map::Units::UT_E_ARCHER || (UVar1 == Map::Units::UT_E_XBOW))
                                        && (!(DAT_TileMapState::instance.LogicLayer[_pUnit->tile] & 0x10000100U)))))))
                            && (MACRO_CALL_MEMBER(
                                    Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                                    DAT_DirectionAlgorithmState::ptr)(
                                    (int)_pUnit->x, (int)((int)(_pUnit->y)), (int)((int)(x1)), (int)((int)(y1))),
                                DAT_DirectionAlgorithmState::instance.distanceHigh < 30)) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromTribe,
                                DAT_TribesState::ptr)(_unitID, (int)((int)(_pUnit->tribeID)));
                            _theTribe = _archersTribe;
                            if (_pUnit->unitType == Map::Units::UT_E_SWORD) {
                                _theTribe = _swordsTribe;
                            }
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe,
                                DAT_TribesState::ptr)(_unitID, _theTribe);
                        }
                        _unitID = _unitID + 1;
                        _pUnit = _pUnit + 0x248;
                    } while ((int)_unitID < DAT_UnitsState::instance.maxUnitCount);
                }
                if (DAT_TribesState::instance.tribes[_swordsTribe].size < 1) {
                    DAT_TribesState::instance.tribes[_swordsTribe].tribeState = 3;
                } else {
                    MACRO_CALL_MEMBER(
                        Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                        _swordsTribe, x1, y1 + 1, 0, 0, Map::Units::Instructions::UMSE_0);
                }
                if (DAT_TribesState::instance.tribes[_archersTribe].size < 1) {
                    DAT_TribesState::instance.tribes[_archersTribe].tribeState = 3;
                }
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction,
                    DAT_TribesState::ptr)(_archersTribe, x1, y1, 0, 0, Map::Units::Instructions::UMSE_0);
            }
        }

    }
}
}
