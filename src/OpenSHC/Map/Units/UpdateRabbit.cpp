#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitHasBecomeIdle.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00542630
    void Units::UpdateRabbit()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        DAT_GameState::instance.mapAndTime.field3166_0x277c += 1;
        short tribe = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex
            = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng & 0xf;
        if (DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex == 9) {
            DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = 2;
        } else if (DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex == 10
            || DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex == 11) {
            DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = 3;
        } else if (DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex == 12) {
            DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = 4;
        } else if (DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex == 13) {
            DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = 6;
        } else if (DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex == 14) {
            DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = 8;
        } else if (DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex == 15) {
            DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = 3;
        }
        DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
        if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown > 0
            && DAT_UnitsState::instance.units[unitID].state.generic != OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown -= 1;
        }
        // rabbits eat the crops on their tile and on the four neighbouring tiles
        int tile = DAT_UnitsState::instance.units[unitID].tile;
        if ((DAT_TileMapState::instance.LogicLayer[tile]
                & (OpenSHC::Map::LogicHelpers::L_FARM_FIELD_WHEAT | OpenSHC::Map::LogicHelpers::L_FARM_FIELD_HOP))
            != 0) {
            DAT_TileMapState::instance.DamageLayer[tile] = 0;
        }
        int neighbour
            = DAT_TileMapState::instance.directionTranslationMatrix[DAT_UnitsState::instance.units[unitID].y][0] + tile;
        if ((DAT_TileMapState::instance.LogicLayer[neighbour]
                & (OpenSHC::Map::LogicHelpers::L_FARM_FIELD_WHEAT | OpenSHC::Map::LogicHelpers::L_FARM_FIELD_HOP))
            != 0) {
            DAT_TileMapState::instance.DamageLayer[neighbour] = 0;
        }
        neighbour
            = DAT_TileMapState::instance.directionTranslationMatrix[DAT_UnitsState::instance.units[unitID].y][4] + tile;
        if ((DAT_TileMapState::instance.LogicLayer[neighbour]
                & (OpenSHC::Map::LogicHelpers::L_FARM_FIELD_WHEAT | OpenSHC::Map::LogicHelpers::L_FARM_FIELD_HOP))
            != 0) {
            DAT_TileMapState::instance.DamageLayer[neighbour] = 0;
        }
        neighbour
            = DAT_TileMapState::instance.directionTranslationMatrix[DAT_UnitsState::instance.units[unitID].y][2] + tile;
        if ((DAT_TileMapState::instance.LogicLayer[neighbour]
                & (OpenSHC::Map::LogicHelpers::L_FARM_FIELD_WHEAT | OpenSHC::Map::LogicHelpers::L_FARM_FIELD_HOP))
            != 0) {
            DAT_TileMapState::instance.DamageLayer[neighbour] = 0;
        }
        neighbour
            = DAT_TileMapState::instance.directionTranslationMatrix[DAT_UnitsState::instance.units[unitID].y][6] + tile;
        if ((DAT_TileMapState::instance.LogicLayer[neighbour]
                & (OpenSHC::Map::LogicHelpers::L_FARM_FIELD_WHEAT | OpenSHC::Map::LogicHelpers::L_FARM_FIELD_HOP))
            != 0) {
            DAT_TileMapState::instance.DamageLayer[neighbour] = 0;
        }
        switch (DAT_UnitsState::instance.units[unitID].state.generic) {
        case OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk:
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[unitID].closestEnemyMicroDistance <= 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)0xcc;
                return;
            }
            if ((unitID & 1) != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionTowardsTarget,
                    DAT_UnitsState::ptr)(unitID, DAT_TribesState::instance.tribes[tribe].selectionTargetUnitID);
            }
            DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)0xcb;
            return;
        case OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION:
        case 120:
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker = 0;
            DAT_UnitsState::instance.units[unitID].moveDelay = 0;
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].field180_0x32d = 2;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 1;
            if (DAT_UnitsState::instance.units[unitID].substate == 100) {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 40;
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
                DAT_UnitsState::instance.units[unitID].animationSpeed = 4;
                DAT_UnitsState::instance.units[unitID].rabbitMovementSlowdown += 1;
                if ((char)(DAT_UnitsState::instance.units[unitID].fixedRng & 0xf)
                    < DAT_UnitsState::instance.units[unitID].rabbitMovementSlowdown) {
                    DAT_UnitsState::instance.units[unitID].substate = 0;
                    DAT_UnitsState::instance.units[unitID].movementSpeed
                        = (DAT_UnitsState::instance.units[unitID].fixedRng & 1) + 1;
                }
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field359_0x720c[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                    DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[unitID].seated = 0;
                    DAT_UnitsState::instance.units[unitID].substate = 0;
                    DAT_UnitsState::instance.units[unitID].movementSpeed
                        = (DAT_UnitsState::instance.units[unitID].fixedRng & 1) + 1;
                }
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0xf9
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
                return;
            }
            DAT_UnitsState::instance.units[unitID].movementSpeed
                = (DAT_UnitsState::instance.units[unitID].fixedRng & 1) + 1;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].substate = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        case OpenSHC::Map::Units::States::US_DISAPPEAR:
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown += 1;
            if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown > 32) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 32;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 32) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            }
            return;
        case OpenSHC::Map::Units::States::US_DEATH_01:
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 4;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field362_0x72e0[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame > 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x180;
            } else {
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)117;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE
                && DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_RABBIT_DIE);
            }
            return;
        case OpenSHC::Map::Units::States::US_DEATH_02:
        case OpenSHC::Map::Units::States::US_DEATH_03:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_01:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_02:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_03:
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 4;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field363_0x7310[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame > 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x198;
            } else {
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)117;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE
                && DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_RABBIT_DIE);
            }
            return;
        case 117:
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 5) {
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        case 0xcb:
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field250_0x3c2 = 1;
            DAT_UnitsState::instance.units[unitID].seated = 1;
            if ((unitID & 3) == 0) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field356_0x7178[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if ((unitID & 3) == 1) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field357_0x71a0[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if ((unitID & 3) == 2) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field358_0x71d4[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field360_0x7268[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitHasBecomeIdle::instance = 1;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            if ((unitID & 3) == 3) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0xf9
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x79
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        case 0xcc:
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].seated = 1;
            if (DAT_UnitsState::instance.units[unitID].substate == 0) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field360_0x7268[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 1) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field361_0x72a0[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0xf9
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].substate += 1;
                if (DAT_UnitsState::instance.units[unitID].substate > 1) {
                    DAT_UnitsState::instance.units[unitID].substate = 0;
                }
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        case 0xd1:
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            if (((DAT_UnitsState::instance.units[unitID].fixedRng ^ DAT_GameCore::instance.mapTimeInTicks) & 0x7f)
                == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID, DAT_UnitsState::instance.units[unitID].targetX,
                    DAT_UnitsState::instance.units[unitID].targetY, 0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
            }
            return;
        }
    }

}
}
