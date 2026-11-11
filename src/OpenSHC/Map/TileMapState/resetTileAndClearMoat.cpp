#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;
    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_TREE;
    using OpenSHC::Map::LogicHelpers::L_UNKNOWN_WALL_RELATED;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x00507350
    void TileMapState::resetTileAndClearMoat(int tile)
    {
        int const y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
        int const x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
        this->LogicLayer[tile] &= ~(L_PLAIN2_AND_PITCH | L_WALL_OR_GATEHOUSE | L_CRENEL | L_STAIRS
            | L_UNKNOWN_WALL_RELATED | L_CRENEL_VARIATIONUnk);
        this->HeightLayer[tile] = DAT_TileMapState::instance.DefaultHeightLayer[tile];
        this->DamageLayer[tile] = 0;
        if ((this->LogicLayer[tile] & L_TREE) != 0) {
            int treeID = this->OrganismLayer[tile];
            if (treeID < countof(DAT_LandscapeState::instance.trees)) {
                switch (DAT_LandscapeState::instance.trees[treeID].treeType) {
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 16:
                case 17:
                case 18:
                case 19:
                    DAT_LandscapeState::instance.trees[treeID].state = 3;
                }
            }
        }
        if ((this->LogicLayer[tile] & (L_MOAT | L_MOAT_DUG_OR_PLANNED)) != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoatDataAtTile, this)(x, y);
            this->LogicLayer[tile] &= ~(L_MOAT | L_MOAT_DUG_OR_PLANNED);
        }
        this->MiscDisplayLayer[tile] &= ~0x3c0;
    }

}
}
