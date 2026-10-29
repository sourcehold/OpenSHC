#include "OpenSHC/Map/Navigation.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_CurrentClimbDataID.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    /* climb data of a ladderman holding a ladder: valid while the same unit (climbDataRelated) stands in state 3 and is alive;
       the ladder leads from the unit's tileUnk one step in its facing direction */
    // FUNCTION: STRONGHOLDCRUSADER 0x004A4D60
    void __cdecl Navigation::UpdateClimbDataState01()
    {
        int unitID = DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].unitID;
        bool ladderStillHeld
            = DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].sourceUID
                == DAT_UnitsState::instance.units[unitID].climbDataRelated
            && DAT_UnitsState::instance.units[unitID].state.generic == OpenSHC::Map::Units::States::US_STATE_3Unk
            && DAT_UnitsState::instance.units[unitID].dying == 0;
        if (!ladderStillHeld) {
            DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].canBeUsed = 0;
            return;
        }
        DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].isRecognizedByPathfinding = 1;
        DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].ladderDirection
            = DAT_UnitsState::instance.units[unitID].facingDirection;
        DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].topXPosition
            = DAT_TerrainDefinedData::instance
                  .clockwiseCardinalTranslationMatrix[DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].ladderDirection]
                  .int_.xOffset
            + DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].bottomXPosition;
        DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].topYPosition
            = DAT_TerrainDefinedData::instance
                  .clockwiseCardinalTranslationMatrix[DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].ladderDirection]
                  .int_.yOffset
            + DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].bottomYPosition;
        DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].topTilePositionUnk
            = DAT_TileMapState::instance.directionTranslationMatrix
                  [DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].bottomYPosition]
                  [DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].ladderDirection]
            + DAT_PathFindingState::instance.climbData[DAT_CurrentClimbDataID::instance].bottomTilePosition;
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
