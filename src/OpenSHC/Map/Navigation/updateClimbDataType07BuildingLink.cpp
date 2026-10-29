#include "OpenSHC/Map/Navigation.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentClimbDataID.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    /* climb data linked to a building: valid while the building uid matches; the top is two rows above the bottom */
    // FUNCTION: STRONGHOLDCRUSADER 0x004A5230
    void __cdecl Navigation::updateClimbDataType07BuildingLink()
    {
        if (DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].sourceUID
            != DAT_BuildingsState::instance.buildings[DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].buildingID]
                   .uid) {
            DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].canBeUsed = 0;
        }
        DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].isRecognizedByPathfinding = 1;
        DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].topXPosition
            = DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].bottomXPosition;
        DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].topYPosition
            = DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].bottomYPosition - 2;
        DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].topTilePositionUnk
            = DAT_ViewportRenderState::instance
                  .translationMatrix[DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].topYPosition]
                  .addXgetTile
            + DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].topXPosition;
        DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].area = (short)DAT_TileMapState::instance
                                                                         .PathConnectionLayer[DAT_PathFindingState::instance
                                                                                 .climbData[DAT_CurrentClimbDataID::instance]
                                                                                 .bottomTilePosition];
        DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].wallGroupAreaID = (short)DAT_TileMapState::instance
                                                                            .PathConnectionLayer[DAT_PathFindingState::instance
                                                                                    .climbData[DAT_CurrentClimbDataID::instance]
                                                                                    .topTilePositionUnk];
        DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].buildingArea = -1;
    }

}
}
