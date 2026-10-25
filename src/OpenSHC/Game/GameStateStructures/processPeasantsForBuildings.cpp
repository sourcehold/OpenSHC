#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Game {

    

    // FUNCTION: STRONGHOLDCRUSADER 0x004589E0
    void GameStateStructures::processPeasantsForBuildings()
    {
        if (DAT_GameCore::instance.gameMode_2 == GM_SIEGE_THAT) {
            return;
        }
        for (int playerID = 1; playerID < 9; ++playerID) {
            if (this->playerDataArray[playerID].keep.id > 0 && this->playerDataArray[playerID].campground.id > 0) {
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateLordLadyJesterAndGhostUnits,
                    DAT_BuildingsState::ptr)(playerID);
                if (DAT_GameCore::instance.gameMode_2 != GM_EDITOR
                    && this->playerDataArray[playerID].countEconomyBuilding_fixme > 0
                    && this->playerDataArray[playerID].availablePeasantsAtFire > 0) {
                    MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::checkBuildingsNeedPeasants,
                        DAT_BuildingsState::ptr)(playerID);
                    if ((int)DAT_BuildingsState::instance.DAT_CountOfBuildingsNeedPeasants > 0) {
                        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::sortBuildingIDsNeedPeasantsQueue,
                            DAT_BuildingsState::ptr)(playerID);
                        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processBuildingIDsNeedPeasantsQueue,
                            DAT_BuildingsState::ptr)(playerID);
                    }
                }
            }
        }
    }

}
}
