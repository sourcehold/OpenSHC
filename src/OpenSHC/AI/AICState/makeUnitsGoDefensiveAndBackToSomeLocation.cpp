#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CEA50
    void AICState::makeUnitsGoDefensiveAndBackToSomeLocation(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL)
            return;
        if (DAT_GameState::instance.playerDataArray[playerID].someTile == 0)
            return;

        for (int i = 0; i < 11; i++) {
            int tribeType = DAT_SkirmishDefinedData::instance.MaxAttackTribes1[i].tribeType;
            int tribeCount = DAT_SkirmishDefinedData::instance.MaxAttackTribes1[i].tribeCount;
            for (int j = 0; j < tribeCount; j++) {
                int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[tribeType + j];
                if (tribeID == 0)
                    continue;
                if (DAT_TribesState::instance.tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[j + tribeType])
                    continue;

                DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_DEFENSIVE;
                uint result = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction,
                    DAT_TribesState::ptr)(tribeID, DAT_GameState::instance.playerDataArray[playerID].someX,
                    DAT_GameState::instance.playerDataArray[playerID].someY, 0, 0,
                    OpenSHC::Map::Units::Instructions::UMSE_0);
                if (result == 0)
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::removeAllTribeUnits, DAT_TribesState::ptr)(
                        tribeID);
            }
        }
    }

}
}
