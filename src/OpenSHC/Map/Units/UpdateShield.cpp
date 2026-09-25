#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Map::Units::UnitInstructionType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0053C300
    void Units::UpdateShield()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        short tribe = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID;
        int owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        DAT_GameState::instance.playerDataArray[owner].armySize += 1;
        DAT_GameState::instance.playerDataArray[owner].currentSiegeWeaponCount += 1;
        DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime = 1;
        DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = owner;
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[unitID].substate = -1;
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 9;
            DAT_UnitsState::instance.units[unitID].state.generic
                = DAT_UnitsState::instance.units[unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    != 1
                ? OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk
                : OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            DAT_UnitsState::instance.units[unitID].field39_0x58 = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            // an AI shield starts moving once its engineer stands next to it
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_UnitsState::instance.units[unitID].owner]
                    == -1
                && DAT_UnitsState::instance.units[unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    == 1) {
                int engineersInPlace = 0;
                for (int i = 0; i < 1; ++i) {
                    int engineer = DAT_UnitsState::instance.units[unitID].manningEngineerRef[i];
                    if (DAT_UnitsState::instance.units[unitID].manningEngineerUIDRef[i]
                        != DAT_UnitsState::instance.units[engineer].uid) {
                        break;
                    }
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination,
                            DAT_UnitsState::ptr)(engineer)
                        == FALSE) {
                        break;
                    }
                    if (abs(DAT_UnitsState::instance.units[engineer].buildingHeight
                            - DAT_UnitsState::instance.units[unitID].buildingHeight
                            - DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight
                            + DAT_UnitsState::instance.units[engineer].terrainOrClimbHeight)
                        > 16) {
                        break;
                    }
                    int distanceX;
                    if (DAT_UnitsState::instance.units[unitID].microXPosition
                        < DAT_UnitsState::instance.units[engineer].microXPosition) {
                        distanceX = DAT_UnitsState::instance.units[engineer].microXPosition
                            - DAT_UnitsState::instance.units[unitID].microXPosition;
                    } else {
                        distanceX = DAT_UnitsState::instance.units[unitID].microXPosition
                            - DAT_UnitsState::instance.units[engineer].microXPosition;
                    }
                    int distance;
                    if (DAT_UnitsState::instance.units[unitID].microYPosition
                        < DAT_UnitsState::instance.units[engineer].microYPosition) {
                        distance = DAT_UnitsState::instance.units[engineer].microYPosition
                            - DAT_UnitsState::instance.units[unitID].microYPosition;
                    } else {
                        distance = DAT_UnitsState::instance.units[unitID].microYPosition
                            - DAT_UnitsState::instance.units[engineer].microYPosition;
                    }
                    if (distance < distanceX) {
                        distance = distanceX;
                    }
                    if (distance < 30) {
                        engineersInPlace += 1;
                    }
                }
                if (engineersInPlace == 1) {
                    short engineer
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[0];
                    DAT_UnitsState::instance.units[engineer].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[engineer].state.generic
                        = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                    DAT_UnitsState::instance.units[engineer].disappearFadeAlphaCountdown = 0;
                    DAT_UnitsState::instance.units[engineer].engineerManningSiegeStateRef_checkType = 2;
                    DAT_UnitsState::instance.units[engineer].cachedState
                        = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                    DAT_UnitsState::instance.units[engineer].updateTickTracker = 0;
                    DAT_UnitsState::instance.units[unitID].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                }
            }
            // an unmanned shield is captured by the first player with an engineer next to it
            if (((DAT_UnitsState::instance.units[unitID].fixedRng ^ DAT_GameState::instance.mapAndTime.totalGameTicksUnk
                     ^ 0xfffffff8)
                    & 0xf)
                    != 0
                || DAT_UnitsState::instance.units[unitID].state.generic
                    != OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                return;
            }
            int engineerCounts[9];
            int engineerIDs[9];
            for (int player = 0; player < 9; ++player) {
                engineerCounts[player] = 0;
            }
            for (int i = 1; i < (int)DAT_UnitsState::instance.maxUnitCount; ++i) {
                if (DAT_UnitsState::instance.units[i].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                    && DAT_UnitsState::instance.units[i].dying == 0
                    && DAT_UnitsState::instance.units[i].unitType == OpenSHC::Map::Units::UT_E_ENGINEER
                    && DAT_UnitsState::instance.units[i].targetingType == OpenSHC::Map::Units::UIT_MAN_SIEGE_EQUIPMENT
                    && DAT_UnitsState::instance.units[i].targetedUnitID__OR__engineerMannedSiegeEngineRef
                        == DAT_CurrentUnitSlotID::instance
                    && abs(DAT_UnitsState::instance.units[i].terrainOrClimbHeight
                           - DAT_UnitsState::instance.units[unitID].buildingHeight
                           - DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight
                           + DAT_UnitsState::instance.units[i].buildingHeight)
                        < 17) {
                    int distanceX;
                    if (DAT_UnitsState::instance.units[unitID].microXPosition
                        < DAT_UnitsState::instance.units[i].microXPosition) {
                        distanceX = DAT_UnitsState::instance.units[i].microXPosition
                            - DAT_UnitsState::instance.units[unitID].microXPosition;
                    } else {
                        distanceX = DAT_UnitsState::instance.units[unitID].microXPosition
                            - DAT_UnitsState::instance.units[i].microXPosition;
                    }
                    int distance;
                    if (DAT_UnitsState::instance.units[unitID].microYPosition
                        < DAT_UnitsState::instance.units[i].microYPosition) {
                        distance = DAT_UnitsState::instance.units[i].microYPosition
                            - DAT_UnitsState::instance.units[unitID].microYPosition;
                    } else {
                        distance = DAT_UnitsState::instance.units[unitID].microYPosition
                            - DAT_UnitsState::instance.units[i].microYPosition;
                    }
                    if (distance < distanceX) {
                        distance = distanceX;
                    }
                    if (distance < 30 && engineerCounts[DAT_UnitsState::instance.units[i].owner] <= 0) {
                        engineerIDs[DAT_UnitsState::instance.units[i].owner
                            + engineerCounts[DAT_UnitsState::instance.units[i].owner]] = i;
                        engineerCounts[DAT_UnitsState::instance.units[i].owner] += 1;
                    }
                }
            }
            int newOwner = DAT_UnitsState::instance.units[unitID].owner;
            if (engineerCounts[newOwner] != 1) {
                newOwner = 1;
                while (engineerCounts[newOwner] != 1) {
                    newOwner += 1;
                    if (newOwner > 8) {
                        return;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection,
                    DAT_UnitsState::ptr)(DAT_UnitsState::instance.units[unitID].owner, unitID, 0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner = (short)newOwner;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex
                        = newOwner;
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].displayColorPlayerID != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].displayColorPlayerID
                        = (short)newOwner;
                }
                int newTribe = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribe,
                    DAT_TribesState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner, 0);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                    newTribe, DAT_CurrentUnitSlotID::instance);
            }
            int engineer = engineerIDs[newOwner];
            DAT_UnitsState::instance.units[engineer].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[engineer].state.generic = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
            DAT_UnitsState::instance.units[engineer].disappearFadeAlphaCountdown = 0;
            DAT_UnitsState::instance.units[engineer].engineerManningSiegeStateRef_checkType = 2;
            DAT_UnitsState::instance.units[engineer].cachedState = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
            DAT_UnitsState::instance.units[engineer].updateTickTracker = 0;
            DAT_UnitsState::instance.units[engineer].targetingType = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[0] = (short)engineer;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerUIDRef[0]
                = DAT_UnitsState::instance.units[engineer].uid;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(engineer);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection,
                DAT_UnitsState::ptr)(DAT_UnitsState::instance.units[engineer].owner, engineer, 0);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 = 1;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION
            || state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 9;
            if (DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker == 0) {
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 9;
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 1;
            } else if (DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker <= 70) {
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            } else {
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = -1;
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitsState::instance.units[unitID].field248_0x3bc = 0;
                if (DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_UnitsState::instance.units[unitID].owner]
                    == -1) {
                    DAT_UnitsState::instance.units[unitID].facingDirection
                        = DAT_TribesState::instance.tribes[tribe].orientation;
                }
            }
            return;
        }
        if (state == (UnitState)0x6c) {
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_01 || state == OpenSHC::Map::Units::States::US_DEATH_03
            || state == OpenSHC::Map::Units::States::US_STONE_DEATH_01) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 10000;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].gfxNumber = 0x89;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE
                && DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_DEATH_SHIELD);
            }
            // the engineers pushing a destroyed shield die with it
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].killedFlagUnk == 0) {
                for (int i = 0; i < DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                    ++i) {
                    if (DAT_UnitsState::instance
                            .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                    .manningEngineerRef[i]]
                            .uid
                        != DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerUIDRef[i]) {
                        continue;
                    }
                    DAT_UnitsState::instance
                        .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[i]]
                        .logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                    if (owner == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_GameState::instance.mapAndTime
                            .ownLossesArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                    .lastEncounteredEnemyPlayerID] += 1;
                    } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                   .lastEncounteredEnemyPlayerID
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_GameState::instance.mapAndTime.emenyHitArray[owner] += 1;
                    }
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber > 200) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_REMOVE;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DISAPPEAR
            || state == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO) {
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown += 1;
            if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown > 32) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 32;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker <= 32) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            if (DAT_UnitsState::instance.units[unitID].killedFlagUnk != 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[unitID]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::processUnitLossStatistic,
                    DAT_GameState::ptr)(owner, DAT_CurrentUnitSlotID::instance);
            }
            if (owner == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                DAT_GameState::instance.mapAndTime.ownLossesArray
                    [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].lastEncounteredEnemyPlayerID] += 1;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].lastEncounteredEnemyPlayerID
                == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                DAT_GameState::instance.mapAndTime.emenyHitArray[owner] += 1;
            }
            return;
        }
    }

}
}
