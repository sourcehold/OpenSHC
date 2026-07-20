#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC9B0
    int AICState::smallestTribeOfUnitType(int playerID, short* unitType)
    {
        int iVar7 = 0;
        int _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (_aiType == AITA_NULL) {
            return 0;
        }
        int iVar3 = (int)this->aics[_aiType - 1].defWallPatrolGroups;
        int iVar6 = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[(int)unitType];
        int _tribeID = 0;
        int local_c = 0;
        short sVar4 = 1000;
        if ((iVar3 < iVar6)
            && (((unitType == (short*)0x8 || (unitType == (short*)0xa)) || (unitType == (short*)0x11)))) {
            iVar6 = iVar3;
        }
        iVar3 = DAT_SkirmishDefinedData::instance.DAT_AiTribeIDOffsetForUnitType[(int)unitType];
        if (0 < iVar6) {
            unitType = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs + iVar3;
            do {
                int iVar5 = (int)*unitType;
                if ((iVar5 == 0)
                    || (DAT_TribesState::instance.tribes[iVar5].uid
                        != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[iVar3 + iVar7])) {
                    _tribeID = MACRO_CALL_MEMBER(
                        Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
                    goto LAB_004ccaae;
                }
                short sVar1 = DAT_TribesState::instance.tribes[iVar5].size;
                if (sVar1 < sVar4) {
                    _tribeID = iVar5;
                    local_c = iVar7;
                    sVar4 = sVar1;
                }
                unitType = unitType + 1;
                iVar7 = iVar7 + 1;
            } while (iVar7 < iVar6);
            iVar7 = local_c;
            if (_tribeID != 0) {
            LAB_004ccaae:
                DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[iVar3 + iVar7] = (short)_tribeID;
                DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[iVar3 + iVar7]
                    = DAT_TribesState::instance.tribes[_tribeID].uid;
                return _tribeID;
            }
        }
        return 0;
    }
}
}
