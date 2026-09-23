#include "../AICState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB3A0
    undefined4 AICState::aiRequiresExtraOxtethers(int playerID)
    {
        int quarryID
            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_QUARRY);
        int highestStonePerTether = 0;
        int highestQuarryID = 0;
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::countBuildingsForPlayer,
                DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_OXTETHER, 1)
            >= 10)
            return 0;

        DAT_GameState::instance.playerDataArray[playerID].highestLoadedQuarryUnk = 0;
        if (quarryID == 0)
            return 0;

        for (; quarryID != 0;
            quarryID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findNextBuildingForPlayerAndType,
                DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_QUARRY, quarryID)) {
            int stone = DAT_BuildingsState::instance
                            .buildings[(short)DAT_BuildingsState::instance.buildings[quarryID].quarryStockpileID]
                            .resources[Game::Resources::RT_STONE];
            int tetherCount = 0;
            for (int i = 0; i < 3; i++) {
                int tetherID = DAT_BuildingsState::instance.buildings[quarryID].quarryLinkedOxTethers[i];
                if (tetherID == 0)
                    continue;
                if (DAT_BuildingsState::instance.buildings[tetherID].buildingType
                        == OpenSHC::Map::Buildings::BT_OXTETHER
                    && DAT_BuildingsState::instance.buildings[tetherID].oxtetherLinkedQuarryID == quarryID)
                    tetherCount++;
                else
                    DAT_BuildingsState::instance.buildings[quarryID].quarryLinkedOxTethers[i] = 0;
            }

            if (tetherCount <= 0) {
                DAT_GameState::instance.playerDataArray[playerID].highestLoadedQuarryUnk = quarryID;
                return 1;
            }
            if (stone / tetherCount > highestStonePerTether) {
                highestQuarryID = quarryID;
                highestStonePerTether = stone / tetherCount;
            }
        }

        if (highestStonePerTether <= 20)
            return 0;
        DAT_GameState::instance.playerDataArray[playerID].highestLoadedQuarryUnk = highestQuarryID;
        return 1;
    }

}
}
