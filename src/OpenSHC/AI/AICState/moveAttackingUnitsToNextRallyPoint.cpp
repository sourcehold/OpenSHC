#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2F80
    void AICState ::moveAttackingUnitsToNextRallyPoint(int playerID)

    {

        short sVar1;

        short* _ptrAttackingUnitsTribeID;

        BOOLEnum _allArrived;

        int _rallyPointIndex;

        uint _x;

        uint _y;

        int _tribeID;

        bool bVar2;

        bool bVar3;

        bool bVar4;

        int _counter;

        short _totalRallyPointSteps;

        short _targetUnitID;

        if (DAT_GameState::instance.playerDataArray[playerID].aiType != OpenSHC::AI::AIT_NULL) {

            _ptrAttackingUnitsTribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs + 0xbe;

            _counter = 0;

            do {

                _tribeID = (int)*_ptrAttackingUnitsTribeID;

                if ((_tribeID != 0)
                    && (DAT_TribesState::instance.tribes[_tribeID].uid
                        == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[_counter + 0xbe])) {

                    DAT_TribesState::instance.tribes[_tribeID].unitStance
                        = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;

                    _allArrived
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::allUnitsReachedTheirDestination,
                            DAT_TribesState::ptr)(_tribeID);

                    if (_allArrived != FALSE) {

                        DAT_TribesState::instance.tribes[_tribeID].unknownAttackRelatedUpdateCounter = 0;

                        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addRallyPointForTribe, this)(_tribeID);

                        _totalRallyPointSteps = DAT_TribesState::instance.tribes[_tribeID].rallyPointCount;

                        _rallyPointIndex = DAT_TribesState::instance.tribes[_tribeID].currentRallyPointIndex + 1;

                        if (_totalRallyPointSteps <= _rallyPointIndex) {

                            _rallyPointIndex = 0;
                        }

                        _x = (uint)DAT_TribesState::instance.tribes[_tribeID].rallyPointArray[_rallyPointIndex][0];

                        _y = (uint)DAT_TribesState::instance.tribes[_tribeID].rallyPointArray[_rallyPointIndex][1];

                        _targetUnitID = DAT_TribesState::instance.tribes[_tribeID].selectionTargetUnitID;

                        DAT_TribesState::instance.tribes[_tribeID].currentRallyPointIndex = (short)_rallyPointIndex;

                        if (0 < _totalRallyPointSteps) {

                            if (_totalRallyPointSteps < 2) {

                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                                    DAT_DirectionAlgorithmState::ptr)(
                                    (int)DAT_UnitsState::instance.units[_targetUnitID].x,
                                    (int)((int)(DAT_UnitsState::instance.units[_targetUnitID].y)), (int)((int)(_x)),
                                    (int)((int)(_y)));

                                bVar4 = (DAT_DirectionAlgorithmState::instance.distanceHigh < 5);

                                bVar3 = DAT_DirectionAlgorithmState::instance.distanceHigh + -5 < 0;

                                bVar2 = DAT_DirectionAlgorithmState::instance.distanceHigh == 5;

                            }

                            else {

                                sVar1 = DAT_UnitsState::instance.units[_targetUnitID].closestEnemyMicroDistance;

                                bVar4 = (sVar1 < 96);

                                bVar3 = (short)(sVar1 + 96) < 0;

                                bVar2 = sVar1 == 96;
                            }

                            if (!bVar2 && bVar4 == bVar3) {

                                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction,
                                    DAT_TribesState::ptr)(
                                    _tribeID, _x, _y, 0, 0, OpenSHC::Map::Units::Instructions::UMSE_0);
                            }
                        }
                    }
                }

                _counter = _counter + 1;

                _ptrAttackingUnitsTribeID = _ptrAttackingUnitsTribeID + 1;

            } while (_counter < 2);
        }

        return;
    }

}
}
