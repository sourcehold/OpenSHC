#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/States/UnitState_HorseArcher.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Map::Entities::EntityType;
    using OpenSHC::Map::Units::UnitInstructionType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::Map::Units::States::UnitState_HorseArcher;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00575820
    void Units::UpdateHorseArcher_DoShooting(int unitID)
    {
        short variation = DAT_UnitsState::instance.units[unitID].horseArcherShootingVariation;
        if (variation == 0) {
            return;
        }
        DAT_UnitsState::instance.units[unitID].animationSpeed = 1;
        DAT_UnitsState::instance.units[unitID].field39_0x58 = 0;
        if (variation == 4) {
            short facingDirection = DAT_UnitsState::instance.units[unitID].facingDirection;
            if (DAT_UnitsState::instance.units[unitID].targetingType == OpenSHC::Map::Units::UIT_ATTACK_BUILDING) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setFacingDirectionTowardCoords,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                        .x,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                        .y);
            } else if (DAT_UnitsState::instance.units[unitID].targetingType == OpenSHC::Map::Units::UIT_ATTACK_LAND
                || DAT_UnitsState::instance.units[unitID].shootTargetedUnit == -2) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setFacingDirectionTowardCoords,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[unitID].shootTargetMicroX / 8,
                    DAT_UnitsState::instance.units[unitID].shootTargetMicroY / 8);
            } else {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::setFacingDirectionTowardUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_UnitsState::instance.units[unitID].shootTargetedUnit);
            }
            DAT_UnitsState::instance.units[unitID].assassinClimbingUpUnk_OR_previousFacingDirection
                = DAT_UnitsState::instance.units[unitID].facingDirection;
            DAT_UnitsState::instance.units[unitID].facingDirection = facingDirection;
        }
        int direction = (DAT_UnitsState::instance.units[unitID].assassinClimbingUpUnk_OR_previousFacingDirection
                            - DAT_TileMapState::instance.mapOrientation + 2)
            % 8;
        if (DAT_UnitsState::instance.units[unitID].animationCycleNumber >= 100) {
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
        }
        variation = DAT_UnitsState::instance.units[unitID].horseArcherShootingVariation;
        if (variation == 4) {
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .ANIM_Frames_HorseArcher_Shooting_1[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
        } else if (variation == 5) {
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .ANIM_Frames_HorseArcher_Shooting_2[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
        } else if (variation == 6) {
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .ANIM_Frames_HorseArcher_Shooting_3[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
        }
        if (DAT_UnitsState::instance.units[unitID].animationFrame > 0) {
            if (DAT_UnitsState::instance.units[unitID].state.generic
                == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x151;
            }
            DAT_UnitsState::instance.units[unitID].imageIDUnk
                = direction + 0x149 + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
        }
        if (variation == 4) {
            if (DAT_UnitsState::instance.units[unitID].animationFrame > 0) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].horseArcherShootingVariation = 5;
            return;
        }
        if (variation == 5) {
            if (DAT_UnitsState::instance.units[unitID].animationFrame > 0) {
                return;
            }
            int target = DAT_UnitsState::instance.units[unitID].shootTargetedUnit;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (target >= 0) {
                if (DAT_UnitsState::instance.units[target].logicalState != OpenSHC::Map::Units::ULS_NORMAL
                    || DAT_UnitsState::instance.units[unitID].targetUID != DAT_UnitsState::instance.units[target].uid
                    || DAT_UnitsState::instance.units[target].dying != 0) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::acquireShootTarget,
                            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)
                        != FALSE) {
                        return;
                    }
                    if (DAT_UnitsState::instance.units[unitID].state.generic
                        == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
                        DAT_UnitsState::instance.units[unitID].state.generic
                            = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    }
                    DAT_UnitsState::instance.units[unitID].horseArcherShootingVariation = 0;
                    return;
                }
                DAT_UnitsState::instance.units[unitID].shootTargetMicroX
                    = DAT_UnitsState::instance.units[target].microXPosition;
                DAT_UnitsState::instance.units[unitID].shootTargetMicroY
                    = DAT_UnitsState::instance.units[target].microYPosition;
                DAT_UnitsState::instance.units[unitID].shootTargetZ
                    = DAT_UnitsState::instance.units[target].buildingHeight
                    + DAT_UnitsState::instance.units[target].terrainOrClimbHeight;
            }
            DAT_UnitsState::instance.units[unitID].horseArcherShootingVariation = 6;
            return;
        }
        if (variation != 6) {
            return;
        }
        if (DAT_UnitsState::instance.units[unitID].animationFrame == 27
            && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
            int target = DAT_UnitsState::instance.units[unitID].shootTargetedUnit;
            DAT_UnitsState::instance.units[unitID].field298_0x40e = false;
            if (target > -1) {
                int distance = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::arrowShootingRelated,
                    DAT_EntityState::ptr)(DAT_UnitsState::instance.units[unitID].microXPosition,
                    DAT_UnitsState::instance.units[unitID].microYPosition,
                    DAT_UnitsState::instance.units[unitID].buildingHeight + 45
                        + DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight,
                    DAT_UnitsState::instance.units[target].microXPosition,
                    DAT_UnitsState::instance.units[target].microYPosition,
                    DAT_UnitsState::instance.units[target].buildingHeight + 26
                        + DAT_UnitsState::instance.units[target].terrainOrClimbHeight);
                if (distance <= 0
                    || DAT_UnitsState::instance.units[target].uid != DAT_UnitsState::instance.units[unitID].targetUID
                    || DAT_UnitsState::instance.units[target].logicalState != OpenSHC::Map::Units::ULS_NORMAL
                    || DAT_UnitsState::instance.units[target].dying != 0) {
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::acquireShootTarget, DAT_UnitsState::ptr)(unitID)
                        != FALSE) {
                        DAT_UnitsState::instance.units[unitID].horseArcherShootingVariation = 5;
                    } else {
                        if (DAT_UnitsState::instance.units[unitID].state.generic
                            == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
                            DAT_UnitsState::instance.units[unitID].state.generic
                                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                        }
                        DAT_UnitsState::instance.units[unitID].horseArcherShootingVariation = 0;
                    }
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::prepareProjectileTarget,
                        DAT_UnitsState::ptr)(unitID, target, distance);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::shootProjectile, DAT_UnitsState::ptr)(
                        unitID, OpenSHC::Map::Entities::ET_ARROW_AND_DEFAULT,
                        DAT_UnitsState::instance.units[unitID].shootTargetMicroX,
                        DAT_UnitsState::instance.units[unitID].shootTargetMicroY,
                        DAT_UnitsState::instance.units[unitID].shootTargetZ + 30);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                        OpenSHC::DE::SHCDE::FX_ARROW_FIRE);
                    DAT_UnitsState::instance.units[unitID].field283_0x3f8 = 0;
                }
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::prepareProjectileTarget, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, -1, 200);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::shootProjectile, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, (EntityType)0x18,
                    DAT_UnitsState::instance.units[unitID].shootTargetMicroX,
                    DAT_UnitsState::instance.units[unitID].shootTargetMicroY,
                    DAT_UnitsState::instance.units[unitID].shootTargetZ + 30);
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_ARROW_FIRE);
                DAT_UnitsState::instance.units[unitID].field283_0x3f8 = 0;
            }
        }
        if (DAT_UnitsState::instance.units[unitID].animationFrame > 0) {
            return;
        }
        DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
        if (DAT_UnitsState::instance.units[unitID].state.generic == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            DAT_UnitsState::instance.units[unitID].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
        }
        DAT_UnitsState::instance.units[unitID].horseArcherShootingVariation = 0;
    }

}
}
