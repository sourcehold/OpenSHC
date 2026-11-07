#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x0049A1C0
        void PathFindingState::updatePathLinkageTileMapRelatedToKeeps(int buildingID)
        {
            // links the tile in front of the keep's entrance with the entrance tile, on the side it faces
            short const orientation = DAT_BuildingsState::instance.buildings[buildingID].orientation;
            if (orientation == 4) {
                int const row = DAT_BuildingsState::instance.buildings[buildingID].y - 1;
                int const x = (int)DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight / 2
                    + DAT_BuildingsState::instance.buildings[buildingID].x;
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[row].addXgetTile + x;
                DAT_TileMapState::instance.PathLinkageLayer[tile] |= 0x10;
                int const tileBelow = DAT_ViewportRenderState::instance.translationMatrix[row + 1].addXgetTile + x;
                DAT_TileMapState::instance.PathLinkageLayer[tileBelow] |= 1;
                return;
            }
            int x;
            int row;
            if (orientation == 6) {
                x = DAT_BuildingsState::instance.buildings[buildingID].x - 1;
                row = (int)DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight / 2
                    + DAT_BuildingsState::instance.buildings[buildingID].y;
            } else if (orientation == 2) {
                x = DAT_BuildingsState::instance.buildings[buildingID].x
                    + DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight - 1;
                row = DAT_BuildingsState::instance.buildings[buildingID].y
                    + (int)DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight / 2;
            } else {
                row = DAT_BuildingsState::instance.buildings[buildingID].y
                    + DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight - 1;
                x = DAT_BuildingsState::instance.buildings[buildingID].x
                    + (int)DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight / 2;
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[row].addXgetTile + x;
                DAT_TileMapState::instance.PathLinkageLayer[tile] |= 0x10;
                int const tileBelow = DAT_ViewportRenderState::instance.translationMatrix[row + 1].addXgetTile + x;
                DAT_TileMapState::instance.PathLinkageLayer[tileBelow] |= 1;
                return;
            }
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[row].addXgetTile + x;
            DAT_TileMapState::instance.PathLinkageLayer[tile] |= 4;
            DAT_TileMapState::instance.PathLinkageLayer[tile + 1] |= 0x40;
        }

    }
}
}
