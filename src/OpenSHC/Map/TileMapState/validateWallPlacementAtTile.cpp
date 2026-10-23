#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_FORD;
    using OpenSHC::Map::LogicHelpers::L_MARSH;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_PLAIN1_AND_FARM;
    using OpenSHC::Map::LogicHelpers::L_RIVER;
    using OpenSHC::Map::LogicHelpers::L_ROCKY;
    using OpenSHC::Map::LogicHelpers::L_SEA;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F94A0
    void TileMapState::validateWallPlacementAtTile(int playerID, uint x, uint y, MappersEnum param_4)
    {
        this->illegalBuild = TRUE;
        int tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        uint logic = this->LogicLayer[tile];
        if ((logic & L_WALL_OR_GATEHOUSE) != 0 && (char)this->DamageLayer[tile] <= 11) {
            return;
        }
        if ((logic & L_BUILDING) != 0) {
            return;
        }
        if (this->BuildingLayer[tile] != 0) {
            return;
        }
        if ((logic & (L_PLAIN1_AND_FARM | L_BORDER)) != 0) {
            return;
        }
        if ((logic & (L_SEA | L_ROCKY | L_RIVER | L_FORD | L_MARSH | L_MOAT)) != 0) {
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                DAT_PathFindingState::ptr)(playerID, x, y, 5)
            != FALSE) {
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSomeSuitableLocationUnk,
                DAT_PathFindingState::ptr)(playerID, x, y, 2)
            != 0) {
            return;
        }

        if (this->UnitLayer[tile] != 0 && (this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) == 0
            && ((undefined2)param_4 == OpenSHC::Commands::M_MAPPER_CRENAL
                || (undefined2)param_4 == OpenSHC::Commands::M_MAPPER_CRENAL2)) {
            DAT_UnitsState::instance.units[(short)this->UnitLayer[tile]].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
        }
        this->illegalBuild = FALSE;
    }

}
}
