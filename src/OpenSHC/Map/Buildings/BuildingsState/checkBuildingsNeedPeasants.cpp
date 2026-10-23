#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
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

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00422B80
        void BuildingsState::checkBuildingsNeedPeasants(int playerID)
        {
            // Collects the buildings of the player that need workers and can be reached from the campground
            int campgroundArea
                = (short)DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_GameState::instance.playerDataArray[playerID].campground.tileEntry];
            this->DAT_CountOfBuildingsNeedPeasants = 0;
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != BLS_NORMAL || this->buildings[i].owner != playerID
                    || this->buildings[i].currentlyNeededEmployeeCount <= 0
                    || this->buildings[i].buildingType == BT_MERCENARYPOST
                    || this->buildings[i].buildingType == BT_BARRACKS) {
                    continue;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible, DAT_BuildingsState::ptr)(i, 0);
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                        DAT_PathFindingState::ptr)(this->buildings[i].owner,
                        (short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_ViewportRenderState::instance
                                                     .translationMatrix[this->buildings[i].buildingEntryY]
                                                     .addXgetTile
                                + this->buildings[i].buildingEntryX],
                        campgroundArea, 0)
                    != 0) {
                    this->DAT_BuildingIDsNeedPeasantsQueue[this->DAT_CountOfBuildingsNeedPeasants] = i;
                    ++this->DAT_CountOfBuildingsNeedPeasants;
                }
            }
        }

    }
}
}
