#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00422B80
        void BuildingsState::checkBuildingsNeedPeasants(int playerID)
        {
            int const campgroundArea
                = (short)DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_GameState::instance.playerDataArray[playerID].campground.tileEntry];
            this->DAT_CountOfBuildingsNeedPeasants = 0;
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState == BLS_NORMAL
                    && this->buildings[buildingID].owner == playerID
                    && this->buildings[buildingID].currentlyNeededEmployeeCount > 0
                    && this->buildings[buildingID].buildingType != BT_MERCENARYPOST
                    && this->buildings[buildingID].buildingType != BT_BARRACKS) {
                    MACRO_CALL_MEMBER(BuildingsState_Func::buildingIsAccessible, DAT_BuildingsState::ptr)(
                        buildingID, 0);
                    int const entryArea
                        = (short)DAT_TileMapState::instance
                              .PathConnectionLayer[DAT_ViewportRenderState::instance
                                                       .translationMatrix[this->buildings[buildingID].buildingEntryY]
                                                       .addXgetTile
                                  + this->buildings[buildingID].buildingEntryX];
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                              calculateCanPlayerUnitsNavigateToAreaFromArea,
                            DAT_PathFindingState::ptr)(this->buildings[buildingID].owner, entryArea, campgroundArea, 0)
                        != 0) {
                        this->DAT_BuildingIDsNeedPeasantsQueue[this->DAT_CountOfBuildingsNeedPeasants] = buildingID;
                        this->DAT_CountOfBuildingsNeedPeasants += 1;
                    }
                }
            }
        }

    }
}
}
