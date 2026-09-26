#include "../AICState.func.hpp"

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

    // FUNCTION: STRONGHOLDCRUSADER 0x004D4220
    void AICState::sendCertainUnitTribesToAIVSlotsOrKeepIfNervousAndNotEnclosed(int playerID)
    {
        BOOLEnum enclosed = MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::checkKeepEnclosed, DAT_GameState::ptr)(playerID);

        for (int i = 0; i < 6; i++) {
            int count = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount
                            [DAT_SkirmishDefinedData::instance.MaxAIVLocationForGroundUnits[i].aivUnitType];
            for (int j = 0; j < count; j++) {
                int tribeID
                    = DAT_GameState::instance.playerDataArray[playerID]
                          .aiTribeIDs[DAT_SkirmishDefinedData::instance.MaxAIVLocationForGroundUnits[i].tribeArrayOffset
                              + j];
                if (tribeID != 0
                    && DAT_TribesState::instance.tribes[tribeID].uid
                        == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs
                            [DAT_SkirmishDefinedData::instance.MaxAIVLocationForGroundUnits[i].tribeArrayOffset + j]) {
                    if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker <= 0
                        || enclosed != FALSE) {
                        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendTribeToAIVLocationSlot, this)(tribeID,
                            (AIVUnitType)DAT_SkirmishDefinedData::instance.MaxAIVLocationForGroundUnits[i].aivUnitType,
                            j);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(tribeID, playerID);
                    }
                }

                // NOTE: the original sets the stance even when the tribe is invalid (tribeID may be 0)
                if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker <= 0
                    || enclosed != FALSE) {
                    DAT_TribesState::instance.tribes[tribeID].unitStance
                        = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
                } else {
                    DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_DEFENSIVE;
                }
            }
        }
    }

}
}
