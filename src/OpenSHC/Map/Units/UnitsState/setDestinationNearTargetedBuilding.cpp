#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053DCC0
        undefined4 UnitsState::setDestinationNearTargetedBuilding(int unitID, int param_2)
        {
            dword _areaAtUnitTile
                = (short)DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile];
            DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].targetedBuildingTile]
                = _areaAtUnitTile;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                  findFreeSpaceNextToEnemyDefensiveStructureInSameAreaWithinDistance,
                DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[unitID].targetedBuildingTile, 1,
                (int*)(short)_areaAtUnitTile, DAT_UnitsState::instance.units[unitID].owner, param_2,
                DAT_UnitsState::instance.units[unitID].facingDirection);
            if (DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1 == 0) {
                return 0;
            }
            if (DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile2OrAHelper == 0) {
                return 0;
            }
            short _destinationY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                                      [DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1];
            int _destinationX = DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1
                - DAT_ViewportRenderState::instance.translationMatrix[_destinationY].addXgetTile;
            DAT_UnitsState::instance.units[unitID].plannedDestinationX = (short)_destinationX;
            DAT_UnitsState::instance.units[unitID].targetingType = (UnitInstructionType)0;
            DAT_PathFindingState::instance.notAllAssassinsUnk = 1;
            DAT_UnitsState::instance.units[unitID].plannedDestinationY = _destinationY;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, this)(
                unitID, _destinationX, _destinationY, 0);
            if (DAT_UnitsState::instance.units[unitID].field64_0x90 != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByAmount, this)(unitID, 2);
            }
            short _attackTileY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                                     [DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile2OrAHelper];
            DAT_UnitsState::instance.units[unitID].targetedBuildingTile
                = DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile2OrAHelper;
            DAT_UnitsState::instance.units[unitID].attackAtTileX
                = (short)DAT_UnitsState::instance.units[unitID].targetedBuildingTile
                - (short)DAT_ViewportRenderState::instance.translationMatrix[_attackTileY].addXgetTile;
            DAT_UnitsState::instance.units[unitID].attackAtTileY = _attackTileY;
            return 1;
        }

    }
}
}
