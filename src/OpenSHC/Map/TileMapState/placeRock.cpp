#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_BOULDERS;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_FORD;
    using OpenSHC::Map::LogicHelpers::L_IRON;
    using OpenSHC::Map::LogicHelpers::L_MARSH;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_OIL;
    using OpenSHC::Map::LogicHelpers::L_PEBBLES;
    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;
    using OpenSHC::Map::LogicHelpers::L_RIVER;
    using OpenSHC::Map::LogicHelpers::L_ROCKY;
    using OpenSHC::Map::LogicHelpers::L_SEA;
    using OpenSHC::Map::LogicHelpers::L_UNNAMED_0x40;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FB4D0
    void TileMapState::placeRock(uint x, uint y, uint kind)
    {
        int rockType = 0;
        int size = 1;
        if (x > 399 || y > 399) {
            return;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
            return;
        }
        // every rock kind has its own footprint size and rock type
        short const rockKind = kind;
        if (rockKind == 0) {
            rockType = 1;
        } else if (rockKind == 1) {
            rockType = 2;
        } else if (rockKind == 2) {
            rockType = 3;
        } else if (rockKind == 3) {
            rockType = 4;
        } else if (rockKind == 4) {
            size = 2;
            rockType = 5;
        } else if (rockKind == 5) {
            size = 2;
            rockType = 6;
        } else if (rockKind == 6) {
            size = 2;
            rockType = 7;
        } else if (rockKind == 7) {
            size = 2;
            rockType = 8;
        } else if (rockKind == 8) {
            size = 3;
            rockType = 9;
        } else if (rockKind == 9) {
            size = 3;
            rockType = 10;
        } else if (rockKind == 10) {
            size = 3;
            rockType = 11;
        } else if (rockKind == 11) {
            size = 3;
            rockType = 12;
        } else if (rockKind == 12) {
            rockType = 13;
            size = 4;
        } else if (rockKind == 13) {
            rockType = 14;
            size = 4;
        } else if (rockKind == 14) {
            rockType = 15;
            size = 4;
        } else if (rockKind == 15) {
            rockType = 16;
            size = 4;
        }

        // the original reuses the kind parameter to hold the lowest height under the footprint
        kind = 1000;
        int highest = 0;
        int index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, size);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                return;
            }
            if ((this->LogicLayer[tile] & L_BUILDING) != 0) {
                return;
            }
            if (this->OrganismLayer[tile] != 0) {
                return;
            }
            if (this->HeightLayer[tile] > highest) {
                highest = this->HeightLayer[tile];
            }
            if (this->HeightLayer[tile] < (int)kind) {
                kind = this->HeightLayer[tile];
            }
            index++;
        } while (index < this->constructionTileCount);

        int const height = (int)(highest - kind) / 2 + kind;
        int const rockID = MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::createRock, DAT_LandscapeState::ptr)(
            x, y, rockType, size, this->rockOrientation);
        // ... and again for the organism id the rock is stamped with
        kind = rockID + 2000;
        index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, size);
            index++;
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            this->HeightLayer[tile] = height;
            this->DefaultHeightLayer[tile] = height;
            this->LogicLayer[tile] &= ~(L_SEA | L_PLAIN2_AND_PITCH | L_UNNAMED_0x40 | L_BOULDERS | L_PEBBLES | L_IRON
                | L_RIVER | L_FORD | L_MARSH | L_MOAT | L_OIL);
            this->Logic2Layer[tile] = 0;
            this->LogicLayer[tile] |= L_ROCKY;
            this->OrganismLayer[tile] = kind;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(9, x, y);
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        this->forceUpdateMacroLayerFlag = 1;
    }

}
}
