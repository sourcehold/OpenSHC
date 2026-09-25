#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitHasBecomeIdle.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00542D10
    void Units::UpdateCow()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        short owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        int building = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1;
        DAT_GameState::instance.playerDataArray[owner].nonInteractiveCitizenCountUnk += 1;
        DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = 0;
        DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
        DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            DAT_UnitsState::instance.units[unitID].movementSpeed = 2;
        }
        if (building == 0) {
            DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
        } else if (DAT_BuildingsState::instance.buildings[building].uid
            != DAT_UnitsState::instance.units[unitID].workplaceBuildingUID) {
            DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
        } else if (DAT_BuildingsState::instance.buildings[building].sleeping != false) {
            DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
        } else if (DAT_BuildingsState::instance.buildings[building].workerID[0] == 0) {
            DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
        } else if (DAT_UnitsState::instance.units[unitID].state.generic == (UnitState)4
            || DAT_UnitsState::instance.units[unitID].state.generic == (UnitState)5
            || DAT_UnitsState::instance.units[unitID].state.generic == (UnitState)6
            || DAT_UnitsState::instance.units[unitID].state.generic == OpenSHC::Map::Units::States::US_DISAPPEAR) {
            if (DAT_BuildingsState::instance.buildings[building]
                    .workerID[DAT_UnitsState::instance.units[unitID].workerIndex]
                == unitID) {
                DAT_BuildingsState::instance.buildings[building]
                    .workerID[DAT_UnitsState::instance.units[unitID].workerIndex] = 0;
            }
        } else {
            DAT_BuildingsState::instance.buildings[building].numberOfAnimals += 1;
        }
        if (DAT_UnitsState::instance.units[unitID]
                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
            != 0) {
            DAT_UnitsState::instance.units[unitID]
                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 -= 1;
            if (DAT_UnitsState::instance.units[unitID]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                == 0) {
                DAT_GameState::instance.playerDataArray[owner].counter -= 1;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
        }
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            if (DAT_UnitsState::instance.units[unitID].substate == -1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::sitDownIfStanding, DAT_UnitsState::ptr)(unitID);
            }
            if (DAT_UnitsState::instance.units[unitID].substate == 100) {
                if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 8
                    && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                        OpenSHC::DE::SHCDE::FX_COW_MOO);
                }
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field325_0x641c[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 0x65) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field326_0x6440[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 0x6a) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field327_0x646c[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 0x66) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field328_0x64fc[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 0x67) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field329_0x657c[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x79
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].substate == 0x65) {
                DAT_UnitsState::instance.units[unitID].substate = 0x6a;
                DAT_UnitsState::instance.units[unitID].seated = 1;
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].substate == 100) {
                DAT_UnitsState::instance.units[unitID].substate = 0x66;
                DAT_UnitsState::instance.units[unitID].seated = 0;
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].substate == 0x6a) {
                DAT_UnitsState::instance.units[unitID].substate = 100;
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].substate == 0x66) {
                DAT_UnitsState::instance.units[unitID].substate = 0x67;
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].substate == 0x67) {
                DAT_UnitsState::instance.units[unitID].substate = 0x65;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            return;
        }
        if (state == (UnitState)3) {
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 32;
            if ((char)DAT_BuildingsState::instance.buildings[building].field217_0x298 > 2
                && (char)DAT_BuildingsState::instance.buildings[building].field217_0x298 <= 4) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                unitID);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerManningSiegeStateRef_checkType
                = 0xff;
            return;
        }
        if (state == (UnitState)4) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 8;
            short target = DAT_UnitsState::instance.units[unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef;
            if (DAT_UnitsState::instance.units[unitID]
                        .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                    == DAT_UnitsState::instance.units[target].uid
                && DAT_UnitsState::instance.units[target].dying == 0) {
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(unitID)
                    != FALSE) {
                    DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[unitID].substate = 0;
                    DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)5;
                    DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                }
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                DAT_UnitsState::ptr)(unitID);
            DAT_GameState::instance.playerDataArray[owner].counter -= 1;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            return;
        }
        if (state == (UnitState)5) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 1000) {
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)6;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO) {
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown
                += DAT_UnitsState::instance.units[unitID].engineerManningSiegeStateRef_checkType;
            if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown < 0) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
            } else if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown >= 32) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 31;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker <= 32) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if ((char)DAT_UnitsState::instance.units[unitID].engineerManningSiegeStateRef_checkType < 0) {
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            if ((char)DAT_UnitsState::instance.units[unitID].engineerManningSiegeStateRef_checkType > 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(
                    unitID);
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)3;
            }
            return;
        }
        if (state == (UnitState)6 || state == OpenSHC::Map::Units::States::US_DEATH_03
            || state == OpenSHC::Map::Units::States::US_STONE_DEATH_01
            || state == OpenSHC::Map::Units::States::US_DEATH_01) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 4;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field330_0x66cc[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x180;
            }
            if (DAT_UnitsState::instance.units[unitID].state.generic != (UnitState)6
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                if (DAT_UnitsState::instance.units[unitID].animationFrame == 2) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                        OpenSHC::DE::SHCDE::FX_COW_MOO);
                }
                if (DAT_UnitsState::instance.units[unitID].animationFrame == 10) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                        OpenSHC::DE::SHCDE::FX_HORSE_FALL);
                }
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_GameState::instance.playerDataArray[owner].counter -= 1;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown += 1;
            if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown > 32) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 32;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 32) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            }
            return;
        }
        DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
            DAT_UnitsState::ptr)(unitID);
    }

}
}
