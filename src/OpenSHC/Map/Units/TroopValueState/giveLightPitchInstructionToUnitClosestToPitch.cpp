#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitInstructionType;
        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;
        using Map::Units::States::UnitState;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051BF70
        undefined4 TroopValueState::giveLightPitchInstructionToUnitClosestToPitch(int tile)
        {
            int _ditchID;
            BOOLEnum BVar1;
            int _shot;
            int _unitY;
            int _ditchY;
            int _ditchX;
            int _unitX;
            int _distancePyth;
            Unit* _pUnit;
            int _unitID;
            int _minDistance;
            int _minUnitID;
            int _ditchUID;
            byte _height;
            _ditchID = MACRO_CALL_MEMBER(
                Map::TileMapState_Func::getPitchDitchIDForTile, DAT_TileMapState::ptr)(tile);
            _minUnitID = 0;
            _minDistance = 100000000;
            _unitID = 1;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                _pUnit = &DAT_UnitsState::instance.units[1];
                do {
                    if ((((_pUnit->logicalState != Map::Units::ULS_INVISIBLE)
                             && (BVar1 = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep,
                                     this)((int)_pUnit->owner),
                                 BVar1))
                            && ((_pUnit->unitType == Map::Units::UT_E_ARCHER
                                || (_pUnit->unitType == Map::Units::UT_A_ARCHER))))
                        && (((!_pUnit->dying && (_pUnit->field297_0x40d != false))
                            && (_pUnit->targetingType != Map::Units::UIT_LIGHT_PITCH)))) {
                        _ditchY = (int)DAT_TileMapState::instance.pitchDitches[_ditchID].y;
                        _ditchX = (int)DAT_TileMapState::instance.pitchDitches[_ditchID].x;
                        _unitY = _ditchY - _pUnit->y;
                        _unitX = _ditchX - _pUnit->x;
                        _distancePyth = _unitX * _unitX + _unitY * _unitY;
                        if (((_distancePyth < 2500)
                                && (_shot
                                    = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::arrowShootingRelated,
                                        DAT_EntityState::ptr)((int)_pUnit->microXPosition,
                                        (int)((int)(_pUnit->microYPosition)),
                                        (int)((int)(_pUnit->buildingHeight + 30 + _pUnit->terrainOrClimbHeight)),
                                        _ditchX * 8 + 4, _ditchY * 8 + 4,
                                        (int)((int)((uint)DAT_TileMapState::instance
                                                .HeightLayer[DAT_TileMapState::instance.pitchDitches[_ditchID].tile]))),
                                    0 < _shot))
                            && (_distancePyth < _minDistance)) {
                            _minUnitID = _unitID;
                            _minDistance = _distancePyth;
                        }
                    }
                    _unitID = _unitID + 1;
                    _pUnit = _pUnit + 0x248;
                } while (_unitID < DAT_UnitsState::instance.maxUnitCount);
                if (_minUnitID) {
                    DAT_UnitsState::instance.units[_minUnitID].shootTargetMicroX
                        = DAT_TileMapState::instance.pitchDitches[_ditchID].x * 8 + 4;
                    DAT_UnitsState::instance.units[_minUnitID].shootTargetMicroY
                        = DAT_TileMapState::instance.pitchDitches[_ditchID].y * 8 + 4;
                    _height = DAT_TileMapState::instance
                                  .HeightLayer[DAT_TileMapState::instance.pitchDitches[_ditchID].tile];
                    DAT_UnitsState::instance.units[_minUnitID].targetID_OR_targetBuildingID = (short)_ditchID;
                    _ditchUID = DAT_TileMapState::instance.pitchDitches[_ditchID].uid;
                    DAT_UnitsState::instance.units[_minUnitID].shootTargetZ = (ushort)_height;
                    DAT_UnitsState::instance.units[_minUnitID].shootTargetedUnit = -1;
                    DAT_UnitsState::instance.units[_minUnitID]
                        .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                        = _ditchUID;
                    DAT_UnitsState::instance.units[_minUnitID].field253_0x3c5 = 0x22;
                    DAT_UnitsState::instance.units[_minUnitID].targetingType = Map::Units::UIT_LIGHT_PITCH;
                    DAT_UnitsState::instance.units[_minUnitID].field283_0x3f8 = 0;
                    MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                        DAT_UnitsState::ptr)(_minUnitID);
                    DAT_UnitsState::instance.units[_minUnitID].state.generic
                        = Map::Units::States::US_FIRE_WEAPONUnk;
                    DAT_UnitsState::instance.units[_minUnitID].field298_0x40e = true;
                    return (undefined4)(1);
                }
            }
            return (undefined4)(0);
        }

    }
}
}
