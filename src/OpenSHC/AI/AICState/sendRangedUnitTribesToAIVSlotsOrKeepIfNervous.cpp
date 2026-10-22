#include "../AICState.func.hpp"

#include "OpenSHC/AI/AIVUnitType.hpp"
#include "OpenSHC/AI/AIVUnitTypeInt.hpp"
#include "OpenSHC/AI/Tribes/AIVUnitTypeMaxLocationPair.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"

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
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D4130
    void AICState::sendRangedUnitTribesToAIVSlotsOrKeepIfNervous(int playerID)
    {
        for (int i = 0; i < 5; i++) {
            int const count = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount
                                  [DAT_SkirmishDefinedData::instance.MaxAIVLocationForRangedUnits[i].aivUnitType];
            for (int j = 0; j < count; j++) {
                int const tribeID
                    = DAT_GameState::instance.playerDataArray[playerID]
                          .aiTribeIDs[DAT_SkirmishDefinedData::instance.MaxAIVLocationForRangedUnits[i].tribeArrayOffset
                              + j];
                if (tribeID == 0) {
                    continue;
                }
                if (DAT_TribesState::instance.tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID]
                        .aiTribeUIDs[DAT_SkirmishDefinedData::instance.MaxAIVLocationForRangedUnits[i].tribeArrayOffset
                            + j]) {
                    continue;
                }

                if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker > 0) {
                    if ((DAT_TileMapState::instance.LogicLayer[DAT_UnitsState::instance
                                 .units[DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID]
                                 .tile]
                            & (L_KEEP_NON_MANOR_HOUSE | L_WALL_OR_GATEHOUSE))
                        == 0) {
                        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(tribeID, playerID);
                    }
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendTribeToAIVLocationSlot, this)(tribeID,
                        (AIVUnitType)DAT_SkirmishDefinedData::instance.MaxAIVLocationForRangedUnits[i].aivUnitType, j);
                }
            }
        }
    }

}
}
