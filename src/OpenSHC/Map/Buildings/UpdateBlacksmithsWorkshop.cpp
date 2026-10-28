#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004130D0
    void Buildings::UpdateBlacksmithsWorkshop()
    {
        int const owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field138_0x1c2 = 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] != 0;
        DAT_GameState::instance.playerDataArray[owner].countArmorersAndBlacksmiths += 1;
        if (((DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].uid
                 + DAT_GameCore::instance.mapTimeInTicks)
                & 0xff)
            == 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingPlacementRotationPreview,
                DAT_TileMapState::ptr)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation
                = DAT_TileMapState::instance.uiBuildingRotation;
        }

        int animationDone = 0;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].producedItemTypeNext
            == OpenSHC::Game::Resources::RT_SWORD) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                char const frame
                    = DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames3
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 24;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 1) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0
                    && (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 24
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 34
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex
                            == 44)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_BS_ANVIL);
                }
                char const frame
                    = DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames6
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 24;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 2) {
                char const frame
                    = DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames4
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 24;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 3) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0
                    && (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 24
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 34
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex
                            == 44)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_BS_ANVIL);
                }
                char const frame
                    = DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames6
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 24;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 4) {
                char const frame
                    = DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames5
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 24;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 5) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0
                    && (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 24
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 34
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex
                            == 44)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_BS_ANVIL);
                }
                char const frame
                    = DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames6
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 24;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 6) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0
                    && (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 24
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 34
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex
                            == 44)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_BS_ANVIL);
                }
                char const frame
                    = DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames6
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 24;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 7) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0
                    && (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 30)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_BS_COOL);
                }
                char const frame
                    = DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames7
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 24;
                }
            }
            if (animationDone != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 1;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 1) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state
                        = DAT_GameSynchronyState::instance.currentGameMode != 0 ? 6 : 2;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 2) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 3;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 3) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 4;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 4) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 5;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 5) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 6;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 6) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 7;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 7) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCount += 1;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCompleted = 1;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 0;
                }
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].producedItemTypeNext
            == OpenSHC::Game::Resources::RT_MACE) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                if (DAT_GameSynchronyState::instance.currentGameMode == 0) {
                    if (DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames8
                            [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex]
                        <= 0) {
                        animationDone = 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                            = DAT_BuildingDefinedData::instance
                                  .BlacksmithsWorkshopAnimationFrames8[DAT_BuildingsState::instance
                                          .buildings[DAT_CurrentBuildingID::instance]
                                          .animationIndex]
                            + 110;
                    }
                } else {
                    if (DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames11
                            [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex]
                        <= 0) {
                        animationDone = 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                            = DAT_BuildingDefinedData::instance
                                  .BlacksmithsWorkshopAnimationFrames11[DAT_BuildingsState::instance
                                          .buildings[DAT_CurrentBuildingID::instance]
                                          .animationIndex]
                            + 110;
                    }
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 1) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0
                    && (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 24)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_BS_POUR);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0
                    && (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 60)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_BS_OPEN);
                }
                char const frame
                    = DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames9
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                        = frame + 110;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 2) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0
                    && (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 5
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 30
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 55
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 80
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex
                            == 109)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_BS_FILE);
                }
                if (DAT_GameSynchronyState::instance.currentGameMode == 0) {
                    if (DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames10
                            [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex]
                        <= 0) {
                        animationDone = 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                            = DAT_BuildingDefinedData::instance
                                  .BlacksmithsWorkshopAnimationFrames10[DAT_BuildingsState::instance
                                          .buildings[DAT_CurrentBuildingID::instance]
                                          .animationIndex]
                            + 175;
                    }
                } else {
                    if (DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames12
                            [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex]
                        <= 0) {
                        animationDone = 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                            = DAT_BuildingDefinedData::instance
                                  .BlacksmithsWorkshopAnimationFrames12[DAT_BuildingsState::instance
                                          .buildings[DAT_CurrentBuildingID::instance]
                                          .animationIndex]
                            + 175;
                    }
                }
            }
            if (animationDone != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 1;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 1) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 2;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 2) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCount += 1;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCompleted = 1;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 0;
                }
            }
        }

        int const workerID = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[0];
        if (workerID != 0) {
            if (DAT_UnitsState::instance.units[workerID].state.generic
                == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 1;
            } else if (DAT_UnitsState::instance.units[workerID].state.generic
                == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 0;
            }
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 0;
        }
        int const visuallyActive
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateVisuallyActiveState,
            DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance);
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }

        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
        if (visuallyActive == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 0;
        } else {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 == 0) {
                if (DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames1
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock]
                    <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3
                            = 0;
                    } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 2) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3
                            = 0;
                    } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 4) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3
                            = 0;
                    } else {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3
                            = 1;
                    }
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                    = DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames1
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock];
            } else {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock == 0
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock == 16) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_BS_BELLOW);
                }
                if (DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames2
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock]
                    <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3
                            = 0;
                    } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 2) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3
                            = 0;
                    } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 4) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3
                            = 0;
                    } else {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3
                            = 1;
                    }
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                    = DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames2
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock];
            }
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter += 1;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter > 3) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter = 0;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[0] == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 0;
        } else {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
            }
            if (DAT_BuildingDefinedData::instance.SecondaryOverlayAnimationFrames
                    [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1]
                <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                = DAT_BuildingDefinedData::instance.SecondaryOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1]
                + 16;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage += 1;
            if (DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                    [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage = 0;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID
                = DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage
                          / 2];
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID = 0;
        }
    }

}
}
