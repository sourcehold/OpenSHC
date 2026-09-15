#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/AI/AIVUnitType.hpp"
#include "OpenSHC/AI/AIVUnitTypeInt.hpp"
#include "OpenSHC/AI/Tribes/AIVUnitTypeMaxLocationPair.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::AI::AIVUnitType;
    using OpenSHC::AI::AIVUnitTypeInt;
    using OpenSHC::AI::Tribes::AIVUnitTypeMaxLocationPair;
    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D4340
    void AICState ::sendWallPatrolUnitTribesToAIVLocations(int playerID)

    {

        BOOLEnum _enclosed;

        int _tribeID;

        AIVUnitTypeInt* _ptr;

        int _patrolGroupIndex;

        int _index;

        int _minCount;

        int _stepSize;

        int _defWallPatrolGroups;

        AITypeInt _aiType;

        int _count;

        _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;

        if (_aiType != OpenSHC::AI::AIT_NULL) {

            _enclosed = MACRO_CALL_MEMBER(
                OpenSHC::Game::GameStateStructures_Func::checkKeepEnclosed, DAT_GameState::ptr)(playerID);

            /*
                  defWallPatrolGroups */

            _ptr = &DAT_SkirmishDefinedData::instance.MaxAIVLocationForPatrolUnits[0].aivUnitType;

            do {

                _defWallPatrolGroups = *(int*)((int)this + (_aiType + ~OpenSHC::AI::AIT_NULL) * 0x2a4 + 0x114);

                _count = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[*_ptr];

                _index = 0;

                _minCount = _count;

                if (_defWallPatrolGroups < _count) {

                    _minCount = _defWallPatrolGroups;
                }

                if (0 < _minCount) {

                    _stepSize = _count / _minCount;

                    if (_stepSize < 1) {

                        _stepSize = 1;
                    }

                    if (0 < _minCount) {

                        _patrolGroupIndex = 0;

                        do {

                            _tribeID = (int)DAT_GameState::instance.playerDataArray[playerID]
                                           .aiTribeIDs[((AIVUnitTypeMaxLocationPair*)(_ptr + -1))->tribeArrayOffset
                                               + _index];

                            if ((_tribeID != 0)
                                && (DAT_TribesState::instance.tribes[_tribeID].uid
                                    == DAT_GameState::instance.playerDataArray[playerID]
                                        .aiTribeUIDs[((AIVUnitTypeMaxLocationPair*)(_ptr + -1))->tribeArrayOffset
                                            + _index])) {

                                if ((DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker < 1)
                                    || (_enclosed != FALSE)) {

                                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendTribeToAIVLocationSlot, this)(
                                        _tribeID, (AIVUnitType)((int)(*_ptr)),
                                        (DAT_GameState::instance.playerDataArray[playerID].defWallPatrolRallyTimeHits
                                            + _patrolGroupIndex)
                                            % _count);

                                }

                                else {

                                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(
                                        _tribeID, playerID);
                                }

                                if ((DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker < 1)
                                    || (_enclosed != FALSE)) {

                                    DAT_TribesState::instance.tribes[_tribeID].unitStance
                                        = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;

                                }

                                else {

                                    DAT_TribesState::instance.tribes[_tribeID].unitStance
                                        = OpenSHC::Map::Units::Behavior::USE_DEFENSIVE;
                                }
                            }

                            _patrolGroupIndex = _patrolGroupIndex + _stepSize;

                            _index = _index + 1;

                        } while (_index < _minCount);
                    }
                }

                _ptr = _ptr + 2;

            } while ((int)_ptr < 0xb42794);
        }

        return;
    }

}
}
