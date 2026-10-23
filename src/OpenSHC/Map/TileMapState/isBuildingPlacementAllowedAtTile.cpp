#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_APPLE;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_DAIRY;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_HOP;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_WHEAT;
    using OpenSHC::Map::LogicHelpers::L_FORD;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_MARSH;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_PLAIN1_AND_FARM;
    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;
    using OpenSHC::Map::LogicHelpers::L_RIVER;
    using OpenSHC::Map::LogicHelpers::L_SEA;
    using OpenSHC::Map::LogicHelpers::L_TREE;
    using OpenSHC::Map::LogicHelpers::L_TREE_VARIATION;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      @return int 0 if allowed, 1 if not allowed, 2 not allowed because of clashing building placement decompilerscript:
      committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F9A60
    int TileMapState::isBuildingPlacementAllowedAtTile(
        int tile, int playerID, MappersEnum commandBuildingType, int param_4)
    {
        uint logic = this->LogicLayer[tile];
        uint wallOrGate = logic & L_WALL_OR_GATEHOUSE;
        uint height = this->HeightLayer[tile];
        if (wallOrGate != 0 && (this->WallOwnerLayer[tile] & 7) + 1 == playerID) {
            /* a gate or tower on our own wall is measured against the ground, not the wall top */
            switch (commandBuildingType) {
            case OpenSHC::Commands::M_MAPPER_GATEHOUSE:
            case OpenSHC::Commands::M_MAPPER_GATE_MAIN:
            case OpenSHC::Commands::M_MAPPER_GATE_INNER:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD:
            case OpenSHC::Commands::M_MAPPER_GATE_POSTERN:
            case OpenSHC::Commands::M_MAPPER_TOWER1:
            case OpenSHC::Commands::M_MAPPER_TOWER2:
            case OpenSHC::Commands::M_MAPPER_TOWER3:
            case OpenSHC::Commands::M_MAPPER_TOWER4:
            case OpenSHC::Commands::M_MAPPER_TOWER5:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1A:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1B:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1C:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1D:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE1A:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE1B:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE2A:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE2B:
                height = this->DefaultHeightLayer[tile];
            }
        }

        if (this->buildingHeightLimit < 0) {
            if ((int)height < -this->buildingHeightLimit) {
                return 1;
            }
        } else if (this->buildingHeightLimit < (int)height) {
            if (commandBuildingType == OpenSHC::Commands::M_MAPPER_CATTLEFARM) {
                this->placementWarning = 1;
                return 1;
            }
            if (commandBuildingType == OpenSHC::Commands::M_MAPPER_APPLEFARM) {
                this->placementWarning = 2;
                return 1;
            }
            if (commandBuildingType == OpenSHC::Commands::M_MAPPER_HOPSFARM) {
                this->placementWarning = 3;
                return 1;
            }
            if (commandBuildingType != OpenSHC::Commands::M_MAPPER_WHEATFARM) {
                return 1;
            }
            this->placementWarning = 4;
            return 1;
        }
        if (this->buildingMaxHeightDifference + this->buildingMinHeight < (int)height) {
            return 1;
        }
        if ((logic & L_PLAIN2_AND_PITCH) != 0 && commandBuildingType == OpenSHC::Commands::M_MAPPER_PITCH_DITCH) {
            return 1;
        }
        if (this->BuildingLayer[tile] != 0) {
            return 2;
        }

        if (this->UnitLayer[tile] != 0) {
            int unitID = (short)this->UnitLayer[tile];
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer, DAT_GameSynchronyState::ptr)(playerID)
                == FALSE) {
                if (DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_CHICKEN) {
                    return 1;
                }
            } else {
                if (DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_LORD) {
                    return 1;
                }
                if (DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime != 0
                    && DAT_UnitsState::instance.units[unitID].owner != playerID) {
                    return 1;
                }
            }
        }

        if ((logic & L_SEA) != 0) {
            return 1;
        }
        if ((logic & (L_BORDER | L_BORDER_EDGE)) != 0) {
            return 1;
        }
        if ((logic & L_RIVER) != 0) {
            return 1;
        }
        if (wallOrGate != 0) {
            if ((this->WallOwnerLayer[tile] & 7) + 1 != playerID) {
                return 1;
            }
            /* only a gate or a tower may be built onto a wall */
            switch (commandBuildingType) {
            case OpenSHC::Commands::M_MAPPER_GATEHOUSE:
            case OpenSHC::Commands::M_MAPPER_GATE_MAIN:
            case OpenSHC::Commands::M_MAPPER_GATE_INNER:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD:
            case OpenSHC::Commands::M_MAPPER_GATE_POSTERN:
            case OpenSHC::Commands::M_MAPPER_TOWER1:
            case OpenSHC::Commands::M_MAPPER_TOWER2:
            case OpenSHC::Commands::M_MAPPER_TOWER3:
            case OpenSHC::Commands::M_MAPPER_TOWER4:
            case OpenSHC::Commands::M_MAPPER_TOWER5:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1A:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1B:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1C:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1D:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE1A:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE1B:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE2A:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE2B:
                break;
            default:
                return 1;
            }
        }
        if ((logic & L_PLAIN1_AND_FARM) != 0 && param_4 == 0) {
            return 1;
        }
        if ((logic & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
            return 1;
        }

        if ((logic & (L_TREE | L_TREE_VARIATION)) != 0 && this->OrganismLayer[tile] != 0
            && this->OrganismLayer[tile] < 2000) {
            /* scrub can be built over, a real tree cannot, except by the AI outside solitary */
            switch (DAT_LandscapeState::instance.trees[this->OrganismLayer[tile]].treeType) {
            case (TreeType)5:
            case (TreeType)6:
            case (TreeType)7:
            case (TreeType)8:
            case (TreeType)9:
            case (TreeType)0xa:
            case (TreeType)0xb:
            case (TreeType)0xc:
            case (TreeType)0xd:
            case (TreeType)0xe:
            case (TreeType)0x10:
            case (TreeType)0x11:
            case (TreeType)0x12:
            case (TreeType)0x13:
                break;
            default:
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                    return 1;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                        DAT_GameSynchronyState::ptr)(playerID)
                    == 0) {
                    return 1;
                }
            }
        }

        if ((logic & (L_FARM_FIELD_WHEAT | L_FARM_FIELD_HOP | L_FARM_FIELD_APPLE | L_FARM_FIELD_DAIRY)) != 0
            && param_4 == 0) {
            return 1;
        }
        if ((logic & L_FORD) != 0) {
            return 1;
        }

        bool onRock = false;
        if ((char)logic < 0 && wallOrGate == 0) {
            onRock = true;
        }
        if ((!onRock || this->buildingPlacementProperty_4 != 0)
            && ((logic & L_MOAT) == 0 || this->buildingPlacementProperty_7 != 0)
            && (this->buildingPlacementProperty_6 == 2 || (logic & L_MARSH) == 0
                || this->buildingPlacementProperty_6 != 0)) {
            return 0;
        }
        return 1;
    }

}
}
