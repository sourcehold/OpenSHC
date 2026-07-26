#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
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

    using OpenSHC::AI::AIVUnitType;
    using OpenSHC::AI::AIVUnitTypeInt;
    using OpenSHC::AI::Tribes::AIVUnitTypeMaxLocationPair;
    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D4220
    void AICState ::sendCertainUnitTribesToAIVSlotsOrKeepIfNervousAndNotEnclosed(int playerID)

    {

        BOOLEnum _enclosed;

        AIVUnitTypeInt* _ptr;

        int _tribe;

        int _index;

        int _limit;

        int* _nervous;

        _enclosed = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::checkKeepEnclosed, DAT_GameState::ptr)(
            playerID);

        _ptr = &DAT_SkirmishDefinedData::instance.AIVUnitTypeMaxLocationPairArray_GroundUnits[0].aivUnitType;

        do {

            _limit = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[*_ptr];

            _index = 0;

            if (0 < _limit) {

                _nervous = &DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker;

                do {

                    _tribe = (int)DAT_GameState::instance.playerDataArray[playerID]
                                 .aiTribeIDs[((AIVUnitTypeMaxLocationPair*)(_ptr + -1))->tribeArrayOffset + _index];

                    if ((_tribe != 0)
                        && (DAT_TribesState::instance.tribes[_tribe].uid
                            == DAT_GameState::instance.playerDataArray[playerID]
                                .aiTribeUIDs[((AIVUnitTypeMaxLocationPair*)(_ptr + -1))->tribeArrayOffset + _index])) {

                        if ((*_nervous < 1) || (_enclosed != FALSE)) {

                            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendTribeToAIVLocationSlot, this)(
                                _tribe, (AIVUnitType)((int)(*_ptr)), _index);

                        }

                        else {

                            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(_tribe, playerID);
                        }
                    }

                    /*
                              bug:fixme: _tribe could be 0 */

                    if ((*_nervous < 1) || (_enclosed != FALSE)) {

                        DAT_TribesState::instance.tribes[_tribe].unitStance
                            = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;

                    }

                    else {

                        DAT_TribesState::instance.tribes[_tribe].unitStance
                            = OpenSHC::Map::Units::Behavior::USE_DEFENSIVE;
                    }

                    _index = _index + 1;

                } while (_index < _limit);
            }

            _ptr = _ptr + 2;

        } while ((int)_ptr < 0xb4277c);

        return;
    }

}
}
