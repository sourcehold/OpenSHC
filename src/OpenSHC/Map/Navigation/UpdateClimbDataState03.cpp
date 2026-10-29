#include "OpenSHC/Map/Navigation.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentClimbDataID.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    /* climb data of a building ladder (bottom 7 tiles out, top 1 tileUnk behind the building origin); the same as
       states 04/05 with other offsets */
    // FUNCTION: STRONGHOLDCRUSADER 0x004A4E40
    void __cdecl Navigation::UpdateClimbDataState03()
    {
        int buildingID = DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].buildingID;
        DAT_BuildingsState::instance.buildings[buildingID].laddermanDataID = (short)DAT_CurrentClimbDataID::instance;
        if (DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].sourceUID
            != DAT_BuildingsState::instance.buildings[buildingID].uid) {
            DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].canBeUsed = 0;
        }
        DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].owner = DAT_BuildingsState::instance.buildings[buildingID].owner;
        DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].isRecognizedByPathfinding
            = DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2 != 2;
        if (DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].ladderDirection == 2) {
            DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].bottomXPosition
                = DAT_BuildingsState::instance.buildings[buildingID].x + 7;
            DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].bottomYPosition
                = DAT_BuildingsState::instance.buildings[buildingID].y + 3;
            DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].topXPosition
                = DAT_BuildingsState::instance.buildings[buildingID].x - 1;
            DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].topYPosition
                = DAT_BuildingsState::instance.buildings[buildingID].y + 3;
        } else if (DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].ladderDirection == 0) {
            DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].bottomXPosition
                = DAT_BuildingsState::instance.buildings[buildingID].x + 3;
            DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].bottomYPosition
                = DAT_BuildingsState::instance.buildings[buildingID].y + 7;
            DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].topXPosition
                = DAT_BuildingsState::instance.buildings[buildingID].x + 3;
            DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].topYPosition
                = DAT_BuildingsState::instance.buildings[buildingID].y - 1;
        }
        DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].bottomTilePosition
            = DAT_ViewportRenderState::instance
                  .translationMatrix[DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].bottomYPosition]
                  .addXgetTile
            + DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].bottomXPosition;
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
        DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].buildingArea
            = (short)DAT_TileMapState::instance.PathConnectionLayer
                  [DAT_ViewportRenderState::instance.translationMatrix[DAT_BuildingsState::instance.buildings[buildingID].y + 1]
                          .addXgetTile
                      + DAT_BuildingsState::instance.buildings[buildingID].x + 1];
    }

}
}
