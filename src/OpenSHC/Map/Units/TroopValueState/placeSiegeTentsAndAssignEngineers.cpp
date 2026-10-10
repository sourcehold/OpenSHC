#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using AI::Tribes::AITribeType;
        using Game::GameMode2;
        using Map::MapType2;
        using Map::Units::UnitInstructionType;
        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B710
        void TroopValueState::placeSiegeTentsAndAssignEngineers(int param_1, int param_2)
        {
            int iVar4;
            Tribe* piVar6;
            int _tribeID2;
            int iVar6;
            int iVar7;
            int iVar8;
            int iVar9;
            Unit* _ptrPlayerID;
            int _unitID;
            int local_10;
            byte(*local_c)[10];
            int _tribeID;
            int _unitCount;
            uint _maxUnits;
            local_10 = (int)(char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[param_1];
            if (!local_10) {
                local_10 = 2;
            }
            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk)
                && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE)) {
                local_10 = 2;
            }
            int iVar5 = 0;
            local_c = DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore + param_1;
            iVar8 = 0;
            DAT_TroopValueState::instance.attackInfo.createTribeAmount = 0;
            iVar6 = 0;
            do {
                byte bVar1 = (*local_c)[0];
                MappersEnum MVar3 = *(MappersEnum*)((int)DAT_AttackInfoDefinedData::instance.field5_0xc8 + iVar6);
                iVar4 = *(int*)((int)DAT_AttackInfoDefinedData::instance.field1461_0x9ec + iVar6);
                iVar7 = 0;
                if (0 < (char)bVar1) {
                    do {
                        DAT_TroopValueState::instance.attackInfo.engineerBuildQueue[iVar5].engineerBuildingType = MVar3;
                        DAT_TroopValueState::instance.attackInfo
                            .engineerBuildQueue[DAT_TroopValueState::instance.attackInfo.createTribeAmount]
                            .engineerCount = iVar4;
                        iVar5 = DAT_TroopValueState::instance.attackInfo.createTribeAmount + 1;
                        iVar8 = iVar8 + iVar4;
                        DAT_TroopValueState::instance.attackInfo.createTribeAmount = iVar5;
                        if (250 < iVar5)
                            break;
                        iVar7 = iVar7 + 1;
                    } while (iVar7 < (char)bVar1);
                }
                iVar7 = DAT_AttackInfoDefinedData::instance.field1474_0xa0c;
                iVar4 = DAT_AttackInfoDefinedData::instance.field9_0xe8;
                local_c = (byte(*)[10])(*local_c + 1);
                iVar6 = iVar6 + 4;
            } while (iVar6 < 16);
            iVar9 = (int)(char)DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore[param_1][8];
            iVar6 = 0;
            if (0 < iVar9) {
                do {
                    if (0xf9 < iVar5)
                        break;
                    DAT_TroopValueState::instance.attackInfo.engineerBuildQueue[iVar5].engineerBuildingType
                        = (Commands::MappersEnum)(iVar4);
                    DAT_TroopValueState::instance.attackInfo
                        .engineerBuildQueue[DAT_TroopValueState::instance.attackInfo.createTribeAmount]
                        .engineerCount = iVar7;
                    iVar5 = DAT_TroopValueState::instance.attackInfo.createTribeAmount + 1;
                    iVar6 = iVar6 + 1;
                    iVar8 = iVar8 + iVar7;
                    DAT_TroopValueState::instance.attackInfo.createTribeAmount = iVar5;
                } while (iVar6 < iVar9);
            }
            iVar5 = 0;
            _tribeID = 1;
            DAT_TroopValueState::instance.attackInfo.tribeIDArraySize = 0;
            piVar6 = &DAT_TribesState::instance.tribes[1];
            do {
                if ((((piVar6->tribeState) && (piVar6->owner == local_10)) && (piVar6->attackWave == param_1))
                    && (piVar6->tribeType == AI::Tribes::AITT_ENGINEERS)) {
                    DAT_TroopValueState::instance.attackInfo.tribeIDArray[iVar5] = _tribeID;
                    iVar5 = DAT_TroopValueState::instance.attackInfo.tribeIDArraySize + 1;
                    DAT_TroopValueState::instance.attackInfo.tribeIDArraySize = iVar5;
                }
                piVar6 = piVar6 + 0xcd;
                _tribeID = _tribeID + 1;
            } while ((int)piVar6 < 0x176238c);
            if (iVar5) {
                for (iVar6 = 0; iVar6 < iVar5; iVar6++) {
                    _tribeID = DAT_TroopValueState::instance.attackInfo.tribeIDArray[iVar6];
                    short sVar2 = DAT_TribesState::instance.tribes[_tribeID].size;
                    for (; (sVar2 && (iVar5 = DAT_TroopValueState::instance.attackInfo.tribeIDArraySize, 0 < iVar8));
                        iVar8 = iVar8 + -1) {
                        MACRO_CALL_MEMBER(
                            Map::Units::TribesState_Func::popUnitFromTribe, DAT_TribesState::ptr)(_tribeID);
                        sVar2 = DAT_TribesState::instance.tribes[_tribeID].size;
                        iVar5 = DAT_TroopValueState::instance.attackInfo.tribeIDArraySize;
                    }
                }
                _unitID = 0;
                param_1 = 0;
                if (0 < DAT_TroopValueState::instance.attackInfo.createTribeAmount) {
                LAB_0051b904:
                    _unitCount = DAT_TroopValueState::instance.attackInfo.engineerBuildQueue[param_1].engineerCount;
                    _tribeID2 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe,
                        DAT_TribesState::ptr)(DAT_TribesState::instance.tribes[_tribeID].owner, 0);
                    _maxUnits = DAT_UnitsState::instance.maxUnitCount;
                    DAT_TribesState::instance.tribes[_tribeID2].tribeType = 11;
                    DAT_TribesState::instance.tribes[_tribeID2].tribeBehaviorType = 1040;
                    DAT_TribesState::instance.tribes[_tribeID2].attackWave
                        = DAT_TribesState::instance.tribes[_tribeID].attackWave;
                    DAT_TribesState::instance.tribes[_tribeID2].attackInfo_someCounter1
                        = DAT_TribesState::instance.tribes[_tribeID].attackInfo_someCounter1;
                    if (_unitID < (int)_maxUnits) {
                        _ptrPlayerID = &DAT_UnitsState::instance.units[_unitID];
                        do {
                            if (((_ptrPlayerID->logicalState == Map::Units::ULS_NORMAL)
                                    && (_ptrPlayerID->owner == local_10))
                                && ((!_ptrPlayerID->dying
                                    && ((_ptrPlayerID->unitType == Map::Units::UT_E_ENGINEER
                                        && (!_ptrPlayerID->tribeID)))))) {
                                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe,
                                    DAT_TribesState::ptr)(_unitID, _tribeID2);
                                _unitCount = _unitCount + -1;
                                if (_unitCount < 1)
                                    goto LAB_0051b9cb;
                            }
                            _unitID = _unitID + 1;
                            _ptrPlayerID = _ptrPlayerID + 0x248;
                            if (DAT_UnitsState::instance.maxUnitCount <= _unitID) {}
                        } while (true);
                    }
                }
            }
            return;
        LAB_0051b9cb:
            _unitID = _unitID + 1;
            if (DAT_UnitsState::instance.maxUnitCount <= _unitID) {}
            if (!param_2) {
                MACRO_CALL_MEMBER(
                    Map::Units::TroopValueState_Func::placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers, this)(
                    _tribeID2,
                    DAT_TroopValueState::instance.attackInfo.engineerBuildQueue[param_1].engineerBuildingType, 0,
                    Map::Units::UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED);
            } else {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::placeSiegeTentAtAttackAngle, this)(_tribeID2,
                    DAT_TroopValueState::instance.attackInfo.engineerBuildQueue[param_1].engineerBuildingType);
            }
            param_1 = param_1 + 1;
            if (DAT_TroopValueState::instance.attackInfo.createTribeAmount <= param_1) {}
            goto LAB_0051b904;
        }

    }
}
}
