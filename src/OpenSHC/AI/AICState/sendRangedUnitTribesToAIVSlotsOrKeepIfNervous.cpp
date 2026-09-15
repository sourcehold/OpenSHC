#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIVUnitType.hpp"
#include "OpenSHC/AI/AIVUnitTypeInt.hpp"
#include "OpenSHC/AI/Tribes/AIVUnitTypeMaxLocationPair.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIVUnitType;
    using OpenSHC::AI::AIVUnitTypeInt;
    using OpenSHC::AI::Tribes::AIVUnitTypeMaxLocationPair;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D4130
    void AICState ::sendRangedUnitTribesToAIVSlotsOrKeepIfNervous(int playerID)

    {

        AIVUnitTypeInt* _ptr = &DAT_SkirmishDefinedData::instance.MaxAIVLocationForRangedUnits[0].aivUnitType;

        do {

            int _limit = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[*_ptr];

            int _index = 0;

            if (0 < _limit) {

                do {

                    int _tribe = (int)DAT_GameState::instance.playerDataArray[playerID]
                                     .aiTribeIDs[((AIVUnitTypeMaxLocationPair*)(_ptr + -1))->tribeArrayOffset + _index];

                    if ((_tribe != 0)
                        && (DAT_TribesState::instance.tribes[_tribe].uid
                            == DAT_GameState::instance.playerDataArray[playerID]
                                .aiTribeUIDs[((AIVUnitTypeMaxLocationPair*)(_ptr + -1))->tribeArrayOffset + _index])) {

                        if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker > 0) {

                            if ((DAT_TileMapState::instance.LogicLayer[DAT_UnitsState::instance
                                         .units[DAT_TribesState::instance.tribes[_tribe].selectionTargetUnitID]
                                         .tile]
                                    & 0x10000100U)
                                == 0) {

                                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(_tribe, playerID);
                            }

                        } else {

                            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendTribeToAIVLocationSlot, this)(
                                _tribe, (AIVUnitType)((int)(*_ptr)), _index);
                        }
                    }

                    _index = _index + 1;

                } while (_index < _limit);
            }

            _ptr = _ptr + 2;

        } while ((int)_ptr < 0xb42744);

        return;
    }

}
}
