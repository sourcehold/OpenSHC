#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B420
        BOOLEnum TroopValueState::placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers(
            int tribeID, MappersEnum commandBuildingType, uint strategicDistance, UnitInstructionType instruction)
        {
            dword _targetTile;
            uint x;
            uint y;
            int _targetUnitID = (int)DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
            _targetTile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findAppropriateLocationForSiegeTent,
                DAT_PathFindingState::ptr)(100, (uint)(DAT_UnitsState::instance.units[_targetUnitID].x),
                (uint)(DAT_UnitsState::instance.units[_targetUnitID].y), (undefined4)((int)(tribeID)),
                strategicDistance, DAT_TribesState::instance.tribes[tribeID].owner);
            if (!_targetTile
                && (_targetTile
                    = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findAppropriateLocationForSiegeTent,
                        DAT_PathFindingState::ptr)(200, (uint)(DAT_UnitsState::instance.units[_targetUnitID].x),
                        (uint)(DAT_UnitsState::instance.units[_targetUnitID].y), (undefined4)((int)(tribeID)),
                        strategicDistance, DAT_TribesState::instance.tribes[tribeID].owner),
                    _targetTile == 0)) {
                return FALSE;
            }
            int _buildingID = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_targetTile];
            x = (_targetTile - DAT_ViewportRenderState::instance.translationMatrix[_buildingID].addXgetTile) - 1;
            y = _buildingID - 1;
            if (399 < x || 399 < y
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                DAT_TileMapState::instance.buildingPlacementFail = TRUE;
                return FALSE;
            }
            if ((DAT_TileMapState::instance
                        .LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x]
                    & 0x4a5014b1)) {
                DAT_TileMapState::instance.buildingPlacementFail = TRUE;
                return FALSE;
            }
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                DAT_TribesState::instance.tribes[tribeID].owner, (int)(x), (int)(y), commandBuildingType, 3, 0xf);
            _buildingID = DAT_TileMapState::instance.placedBuildingID;
            if (DAT_TileMapState::instance.buildingPlacementFail) {
                return FALSE;
            }
            DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.placedBuildingID].attackWave
                = (int)DAT_TribesState::instance.tribes[tribeID].attackWave;
            DAT_BuildingsState::instance.buildings[_buildingID].unknownSiegeTentRelated01 = 2;
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                tribeID, instruction, _buildingID, DAT_BuildingsState::instance.buildings[_buildingID].uid, 0);
            return TRUE;
        }

    }
}
}
