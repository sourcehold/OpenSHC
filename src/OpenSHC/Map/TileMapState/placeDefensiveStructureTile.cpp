
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BOULDERS;
    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
    using OpenSHC::Map::LogicHelpers::L_IRON;
    using OpenSHC::Map::LogicHelpers::L_PEBBLES;
    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_TREE;
    using OpenSHC::Map::LogicHelpers::L_UNKNOWN_WALL_RELATED;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Map::LogicHelpers::L_BOULDERS;
    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
    using OpenSHC::Map::LogicHelpers::L_IRON;
    using OpenSHC::Map::LogicHelpers::L_PEBBLES;
    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_TREE;
    using OpenSHC::Map::LogicHelpers::L_UNKNOWN_WALL_RELATED;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnumShort": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005034A0
    void TileMapState::placeDefensiveStructureTile(int playerID, uint x, uint y, MappersEnum mapper)
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::validateWallPlacementAtTile, this)(playerID, x, y, mapper);
        if (this->illegalBuild != FALSE) {
            return;
        }

        int tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        short command = (short)mapper;
        this->DamageLayer[tile] = 0;
        this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
        if (command == OpenSHC::Commands::M_MAPPER_WALL) {
            this->HeightLayer[tile] = this->DefaultHeightLayer[tile] + 0x5a;
        } else if (command == OpenSHC::Commands::M_MAPPER_WOODWALL) {
            this->HeightLayer[tile] = this->DefaultHeightLayer[tile] + 0x3c;
        } else {
            bool crenellated = true;
            if (command == OpenSHC::Commands::M_MAPPER_CRENAL) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_CRENEL;
                this->HeightLayer[tile] = this->HeightLayer[tile] + 0x62;
            } else if (command == OpenSHC::Commands::M_MAPPER_CRENAL2) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_CRENEL;
                this->HeightLayer[tile] = this->HeightLayer[tile] + 0x44;
            } else {
                crenellated = false;
                if (command == OpenSHC::Commands::M_MAPPER_STAIR1) {
                    this->LogicLayer[tile] = this->LogicLayer[tile] | L_STAIRS;
                    this->HeightLayer[tile] = this->HeightLayer[tile] + 0x50;
                } else if (command == OpenSHC::Commands::M_MAPPER_STAIR2) {
                    this->LogicLayer[tile] = this->LogicLayer[tile] | L_STAIRS;
                    this->HeightLayer[tile] = this->HeightLayer[tile] + 0x40;
                } else if (command == OpenSHC::Commands::M_MAPPER_STAIR3) {
                    this->LogicLayer[tile] = this->LogicLayer[tile] | L_STAIRS;
                    this->HeightLayer[tile] = this->HeightLayer[tile] + 0x30;
                } else if (command == OpenSHC::Commands::M_MAPPER_STAIR4) {
                    this->LogicLayer[tile] = this->LogicLayer[tile] | L_STAIRS;
                    this->HeightLayer[tile] = this->HeightLayer[tile] + 0x20;
                }
            }
            /* a crenel on an odd tile of one axis carries the alternate variation */
            if (crenellated && ((x & 1) == 0) != ((y & 1) == 0)) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_CRENEL_VARIATIONUnk;
            }
        }

        uint logic = this->LogicLayer[tile];
        this->LogicLayer[tile]
            = logic & ~(L_UNKNOWN_WALL_RELATED | L_BOULDERS | L_PEBBLES | L_IRON) | L_WALL_OR_GATEHOUSE;
        if ((logic & L_PLAIN2_AND_PITCH) != 0) {
            this->LogicLayer[tile]
                = logic & ~(L_PLAIN2_AND_PITCH | L_UNKNOWN_WALL_RELATED | L_BOULDERS | L_PEBBLES | L_IRON)
                | L_WALL_OR_GATEHOUSE;
            this->HeightLayer[tile] = this->HeightLayer[tile] + 4;
        }
        if ((this->LogicLayer[tile] & L_TREE) != 0 && this->OrganismLayer[tile] < 2000) {
            DAT_LandscapeState::instance.trees[this->OrganismLayer[tile]].state = 3;
        }
        if (command == OpenSHC::Commands::M_MAPPER_WOODWALL) {
            this->LogicLayer[tile] = this->LogicLayer[tile] | L_UNKNOWN_WALL_RELATED;
        }
        this->WallOwnerLayer[tile] = this->WallOwnerLayer[tile] & 0xf8 | (char)playerID - 1U;
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections, DAT_PathFindingState::ptr)(y, tile);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoat, this)(tile);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer, DAT_PathFindingState::ptr)(7, x, y);
        if (command != OpenSHC::Commands::M_MAPPER_STAIR1 && command != OpenSHC::Commands::M_MAPPER_STAIR2
            && command != OpenSHC::Commands::M_MAPPER_STAIR3 && command != OpenSHC::Commands::M_MAPPER_STAIR4
            && command != OpenSHC::Commands::M_MAPPER_STAIR5 && command != OpenSHC::Commands::M_MAPPER_STAIR6) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processWallBuildingLoss, DAT_BuildingsState::ptr)(playerID, 1, 0, 0);
        }
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::triggerMinimapRedraw, DAT_MinimapViewState::ptr)(1);
    }

}
}
