#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CCFB0
    int AICState::checksAndGenerateAITribesForPlayerIfNotExisting(int playerID, int maxAmount, BOOLEnum checkOnly)
    {
        int offset = 0;
        int baseOffset = DAT_SkirmishDefinedData::instance.AITribeIDOffsetForAIVUnitType[1];
        for (; offset < maxAmount; offset++) {
            if (offset >= 10) {
                return 0;
            }
            int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[baseOffset + offset];
            if (tribeID == 0
                || DAT_TribesState::instance.tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[baseOffset + offset]) {
                if (checkOnly != FALSE) {
                    return 1;
                }
                int newTribeID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
                DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[baseOffset + offset] = (short)newTribeID;
                DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[baseOffset + offset]
                    = DAT_TribesState::instance.tribes[newTribeID].uid;
                return newTribeID;
            }
        }
        return 0;
    }

}
}
