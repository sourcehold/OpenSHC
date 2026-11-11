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
        if (x > 399) {
            return;
        }
        if (y > 399) {
            return;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
            return;
        }
        /* every rock kind has its own footprint size and rock type */
        if ((short)kind == 0) {
            rockType = 1;
        } else if ((short)kind == 1) {
            rockType = 2;
        } else if ((short)kind == 2) {
            rockType = 3;
        } else if ((short)kind == 3) {
            rockType = 4;
        } else if ((short)kind == 4) {
            size = 2;
            rockType = 5;
        } else if ((short)kind == 5) {
            size = 2;
            rockType = 6;
        } else if ((short)kind == 6) {
            size = 2;
            rockType = 7;
        } else if ((short)kind == 7) {
            size = 2;
            rockType = 8;
        } else if ((short)kind == 8) {
            size = 3;
            rockType = 9;
        } else if ((short)kind == 9) {
            size = 3;
            rockType = 0xa;
        } else if ((short)kind == 0xa) {
            size = 3;
            rockType = 0xb;
        } else if ((short)kind == 0xb) {
            size = 3;
            rockType = 0xc;
        } else if ((short)kind == 0xc) {
            rockType = 0xd;
            size = 4;
        } else if ((short)kind == 0xd) {
            rockType = 0xe;
            size = 4;
        } else if ((short)kind == 0xe) {
            rockType = 0xf;
            size = 4;
        } else if ((short)kind == 0xf) {
            rockType = 0x10;
            size = 4;
        }

        /* the original reuses the kind parameter to hold the lowest height under the footprint */
        kind = 1000;
        int highest = 0;
        int index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, size);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
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

        int height = (int)(highest - kind) / 2 + kind;
        int rockID = MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::createRock, DAT_LandscapeState::ptr)(
            x, y, rockType, size, this->rockOrientation);
        /* ... and again for the organism id the rock is stamped with */
        kind = rockID + 2000;
        index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, size);
            index++;
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            this->HeightLayer[tile] = (byte)height;
            this->DefaultHeightLayer[tile] = (byte)height;
            this->LogicLayer[tile] &= ~(L_SEA | L_PLAIN2_AND_PITCH | L_UNNAMED_0x40 | L_BOULDERS | L_PEBBLES | L_IRON
                | L_RIVER | L_FORD | L_MARSH | L_MOAT | L_OIL);
            this->Logic2Layer[tile] = 0;
            this->LogicLayer[tile] |= L_ROCKY;
            this->OrganismLayer[tile] = (short)kind;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(9, x, y);
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        this->forceUpdateMacroLayerFlag = 1;
    }

}
}
