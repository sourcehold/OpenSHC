#include "../../../Map.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode;
        using Map::Units::UnitInstructionType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051C1A0
        void TroopValueState::lightPitchIfNecessary(int unitID, int unitID2)
        {
            int _playerID;
            int _targetID;
            BOOLEnum _yes;
            int _pitchDitchUID;
            int _tile;
            int _unit2Tile;
            short _y;
            if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                _playerID = (int)DAT_UnitsState::instance.units[unitID].owner;
                if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerID] == -1)
                    && (DAT_GameSynchronyState::instance.currentAIArray[_playerID] != 0)) {
                    _unit2Tile = DAT_UnitsState::instance.units[unitID2].tile;
                    if (((DAT_TileMapState::instance.LogicLayer[_unit2Tile] & 8))
                        && ((_targetID = MACRO_CALL_MEMBER(
                                 Map::TileMapState_Func::getPitchDitchIDForTile, DAT_TileMapState::ptr)(_unit2Tile),
                            _targetID != 0
                                && (_yes = MACRO_CALL_MEMBER(
                                        Map::Units::TroopValueState_Func::shouldLightPitchBasedOnTroopValue, this)(
                                        _unit2Tile, _playerID,
                                        (int)((int)(DAT_UnitsState::instance.units[unitID2].owner))),
                                    _yes)))) {
                        _y = DAT_TileMapState::instance.pitchDitches[_targetID].y;
                        DAT_UnitsState::instance.units[unitID].shootTargetMicroX
                            = DAT_TileMapState::instance.pitchDitches[_targetID].x * 8 + 4;
                        _tile = DAT_TileMapState::instance.pitchDitches[_targetID].tile;
                        DAT_UnitsState::instance.units[unitID].shootTargetMicroY = _y * 8 + 4;
                        _pitchDitchUID = DAT_TileMapState::instance.pitchDitches[_targetID].uid;
                        DAT_UnitsState::instance.units[unitID].shootTargetZ
                            = (ushort)DAT_TileMapState::instance.HeightLayer[_tile];
                        DAT_UnitsState::instance.units[unitID].shootTargetedUnit = -1;
                        DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID = (short)_targetID;
                        DAT_UnitsState::instance.units[unitID]
                            .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                            = _pitchDitchUID;
                        DAT_UnitsState::instance.units[unitID].field253_0x3c5 = 0x22;
                        DAT_UnitsState::instance.units[unitID].targetingType = Map::Units::UIT_LIGHT_PITCH;
                        DAT_UnitsState::instance.units[unitID].field283_0x3f8 = 0;
                        DAT_UnitsState::instance.units[unitID].field298_0x40e = true;
                    }
                }
            }
        }

    }
}
}
