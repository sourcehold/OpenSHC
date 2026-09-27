#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FAAB0
    void TileMapState::clearBuildingTilesAndTrees(int buildingID, int surfaceArea)
    {
        int _treeID;
        Building* _pTileRef;
        int _tile;
        if (0 < surfaceArea) {
            _pTileRef = &DAT_BuildingsState::instance.buildings[buildingID];
            do {
                _tile = _pTileRef->tileRefs[0];
                if ((((this->LogicLayer[_tile] & L_FARM_FIELD_APPLE) != 0)
                        && (_treeID = (int)this->OrganismLayer[_tile], _treeID != 0))
                    && (_treeID < 2000)) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(_treeID);
                }
                this->LogicLayer[_tile] = this->LogicLayer[_tile]
                    & ~(L_BUILDING | L_FARM_FIELD_WHEAT | L_FARM_FIELD_HOP | L_FARM_FIELD_APPLE | L_FARM_FIELD_DAIRY);
                this->DamageLayer[_tile] = 0;
                this->BuildingLayer[_tile] = 0;
                if (DAT_BuildingsState::instance.buildings[buildingID].noRubble == 0) {
                    this->BuildingWasLayer[_tile] = '\0';
                }
                this->ChangedLayer[_tile] = 2;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                    DAT_PathFindingState::ptr)(
                    (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile], _tile);
                /*
                  process next tile
                 */
                _pTileRef = &_pTileRef->tileRefs[1];
                surfaceArea = surfaceArea + -1;
            } while (surfaceArea != 0);
        }
        return;
    }

}
}
