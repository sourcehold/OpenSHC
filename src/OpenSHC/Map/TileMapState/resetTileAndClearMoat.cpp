
#include "OpenSHC/Map/TileMapState.func.hpp"

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

    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;
    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_TREE;
    using OpenSHC::Map::LogicHelpers::L_UNKNOWN_WALL_RELATED;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00507350
    void TileMapState::resetTileAndClearMoat(int tile)
    {
        int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
        int rowTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
        this->LogicLayer[tile] = this->LogicLayer[tile]
            & ~(L_PLAIN2_AND_PITCH | L_WALL_OR_GATEHOUSE | L_CRENEL | L_STAIRS | L_UNKNOWN_WALL_RELATED
                | L_CRENEL_VARIATIONUnk);
        this->HeightLayer[tile] = DAT_TileMapState::instance.DefaultHeightLayer[tile];
        this->DamageLayer[tile] = 0;
        if ((this->LogicLayer[tile] & L_TREE) != 0) {
            int treeID = this->OrganismLayer[tile];
            if (treeID < 2000) {
                switch (DAT_LandscapeState::instance.trees[treeID].treeType) {
                case (TreeType)5:
                case (TreeType)6:
                case (TreeType)7:
                case (TreeType)8:
                case (TreeType)9:
                case (TreeType)10:
                case (TreeType)11:
                case (TreeType)12:
                case (TreeType)13:
                case (TreeType)14:
                case (TreeType)16:
                case (TreeType)17:
                case (TreeType)18:
                case (TreeType)19:
                    DAT_LandscapeState::instance.trees[treeID].state = 3;
                }
            }
        }
        if ((this->LogicLayer[tile] & (L_MOAT | L_MOAT_DUG_OR_PLANNED)) != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoatDataAtTile, this)(tile - rowTile, y);
            this->LogicLayer[tile] = this->LogicLayer[tile] & ~(L_MOAT | L_MOAT_DUG_OR_PLANNED);
        }
        this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] & 0xfc3f;
    }

}
}
