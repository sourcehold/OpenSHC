#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::Map::Units::States::UnitState;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053DCC0
        BOOLEnum UnitsState::setDestinationNearTargetedBuilding(int unitID, int shortenedDistance)
        {
            dword _areaAtUnitTile
                = DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile];
            DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].targetedBuildingTile]
                = _areaAtUnitTile;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                  findFreeSpaceNextToEnemyDefensiveStructureInSameAreaWithinDistance,
                DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[unitID].targetedBuildingTile, 1,
                (int*)_areaAtUnitTile, DAT_UnitsState::instance.units[unitID].owner, shortenedDistance,
                DAT_UnitsState::instance.units[unitID].facingDirection);
            if (DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1 == 0) {
                return FALSE;
            }
            if (DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile2OrAHelper == 0) {
                return FALSE;
            }
            int _destinationY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                                    [DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1];
            int _destinationX = DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1
                - DAT_ViewportRenderState::instance.translationMatrix[_destinationY].addXgetTile;
            DAT_UnitsState::instance.units[unitID].plannedDestinationX = _destinationX;
            DAT_UnitsState::instance.units[unitID].targetingType = (UnitInstructionType)0;
            DAT_PathFindingState::instance.notAllAssassinsUnk = 1;
            DAT_UnitsState::instance.units[unitID].plannedDestinationY = _destinationY;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                unitID, _destinationX, _destinationY, 0);
            if (DAT_UnitsState::instance.units[unitID].field_0x90 != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByAmount, DAT_UnitsState::ptr)(
                    unitID, 2);
            }
            DAT_UnitsState::instance.units[unitID].attackAtTileY
                = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                      [DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile2OrAHelper];
            DAT_UnitsState::instance.units[unitID].targetedBuildingTile
                = DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile2OrAHelper;
            DAT_UnitsState::instance.units[unitID].attackAtTileX
                = DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile2OrAHelper
                - DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_UnitsState::instance.units[unitID].attackAtTileY]
                      .addXgetTile;
            return TRUE;
        }

    }
}
}
