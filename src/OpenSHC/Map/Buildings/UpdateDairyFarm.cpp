#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004167E0
    void Buildings::UpdateDairyFarm()
    {
        int const owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_GameState::instance.playerDataArray[owner].countFarms += 1;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] == 0) {
            DAT_GameState::instance.playerDataArray[owner].farmsWithoutWorkers += 1;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].numberOfAnimals > 0) {
            DAT_GameState::instance.playerDataArray[owner].someResourceCounter = 0;
        }
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] != 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter += 1;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter > 1) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 += 1;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagonsOfAleOrCheeseOrReleaseDogs
            != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagonsOfAleOrCheeseOrReleaseDogs
                -= 1;
        }

        // Stage 0 waits, 1-2 bring in a new cow, 3-6 milk one and make a cheese. The animation tables are declared
        // byte, but the original reads them signed
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].dairyProductionStage = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 0;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].dairyProductionStage == 0) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].numberOfAnimals < 3
                && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                        .flagonsOfAleOrCheeseOrReleaseDogs
                    == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 += 1;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 > 400) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].dairyProductionStage = 1;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 = 0;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 32;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                           .resources[OpenSHC::Game::Resources::RT_CHEESE]
                == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 += 1;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 > 400) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerRotationIndex += 1;
                    if ((char)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                            .workerRotationIndex
                        > 3) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerRotationIndex = 1;
                    }
                    int const slot = (char)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                         .workerRotationIndex;
                    int const cowID
                        = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[slot];
                    if (cowID == 0
                        || DAT_UnitsState::instance.units[cowID].uid
                            != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                .workerUID[slot]) {
                        return;
                    }
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 = 0;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].dairyProductionStage = 3;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 32;
                    DAT_UnitsState::instance.units[cowID].state.generic
                        = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                    DAT_UnitsState::instance.units[cowID].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[cowID].engineerManningSiegeStateRef_checkType = 1;
                }
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].dairyProductionStage == 1) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 70;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength -= 1;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].dairyProductionStage = 2;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].dairyProductionStage == 2) {
            char const frame
                = (char)DAT_BuildingDefinedData::instance.DairyFarmAnimationFrames1
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock];
            if (frame == 24) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength += 1;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength >= 32) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 32;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
                    // Find a free cow slot, or free the first one whose cow is gone
                    int slot;
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[1] == 0) {
                        slot = 0;
                    } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[2]
                        == 0) {
                        slot = 1;
                    } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[3]
                        == 0) {
                        slot = 2;
                    } else {
                        slot = 0;
                        for (int i = 1; i < 4; ++i) {
                            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID[i]
                                    != DAT_UnitsState::instance
                                        .units[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                                .workerID[i]]
                                        .uid
                                || DAT_UnitsState::instance
                                        .units[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                                .workerID[i]]
                                        .logicalState
                                    == OpenSHC::Map::Units::ULS_REMOVE) {
                                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[i] = 0;
                                slot = i - 1;
                                break;
                            }
                        }
                    }
                    int const tile
                        = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tileRefs[slot];
                    int const tileY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                    int const tileX = tile - DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile;
                    int const cowID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit,
                        DAT_UnitsState::ptr)(owner, 0, tileX * 8, tileY * 8,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].terrainHeightUnk,
                        OpenSHC::Map::Units::UT_COW);
                    if (cowID != 0) {
                        DAT_GameState::instance.playerDataArray[owner].counter += 1;
                        DAT_UnitsState::instance.units[cowID].workplaceBuildingUID
                            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].uid;
                        DAT_UnitsState::instance.units[cowID].engineerManningSiegeStateRef_checkType = 0xff;
                        DAT_UnitsState::instance.units[cowID].substate = -1;
                        DAT_UnitsState::instance.units[cowID].workplaceBuildingID_1 = DAT_CurrentBuildingID::instance;
                        DAT_UnitsState::instance.units[cowID].idInTribe = slot;
                        DAT_UnitsState::instance.units[cowID].state.generic
                            = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                        DAT_UnitsState::instance.units[cowID].disappearFadeAlphaCountdown = 32;
                        DAT_UnitsState::instance.units[cowID].facingDirection
                            = DAT_UnitsState::instance.units[cowID].fixedRng & 7;
                        DAT_UnitsState::instance.units[cowID].animationCycleNumber = 0;
                        if (slot == 0) {
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[1] = cowID;
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID[1]
                                = DAT_UnitsState::instance.units[cowID].uid;
                            DAT_UnitsState::instance.units[cowID].workerIndex = 1;
                            DAT_UnitsState::instance.units[cowID].buildingID = DAT_CurrentBuildingID::instance;
                        } else if (slot == 1) {
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[2] = cowID;
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID[2]
                                = DAT_UnitsState::instance.units[cowID].uid;
                            DAT_UnitsState::instance.units[cowID].workerIndex = 2;
                            DAT_UnitsState::instance.units[cowID].buildingID = DAT_CurrentBuildingID::instance;
                        } else if (slot == 2) {
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[3] = cowID;
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID[3]
                                = DAT_UnitsState::instance.units[cowID].uid;
                            DAT_UnitsState::instance.units[cowID].workerIndex = 3;
                            DAT_UnitsState::instance.units[cowID].buildingID = DAT_CurrentBuildingID::instance;
                        }
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].dairyProductionStage
                            = 0;
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                            = 0;
                    }
                }
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                    = frame + 55;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].dairyProductionStage == 3) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 16;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 28;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength -= 1;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].dairyProductionStage = 4;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].dairyProductionStage == 4) {
            if (DAT_BuildingDefinedData::instance.DairyFarmAnimationFrames3
                    [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1]
                == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 48;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 16;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength += 1;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength >= 32) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 32;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].dairyProductionStage = 5;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 0;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 0;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                }
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                    = (char)DAT_BuildingDefinedData::instance.DairyFarmAnimationFrames2
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                    = (char)DAT_BuildingDefinedData::instance.DairyFarmAnimationFrames3
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1]
                    + 16;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
                int const milk
                    = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1;
                if (milk / 12 < 30 && milk % 12 == 10) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_COW_MILK);
                }
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 == 368) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                    OpenSHC::DE::SHCDE::FX_MILK_POUR);
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].dairyProductionStage == 5) {
            char const frame
                = (char)DAT_BuildingDefinedData::instance.DairyFarmAnimationFrames4
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2];
            if (frame == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 54;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].dairyProductionStage = 6;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                    = frame + 47;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].dairyProductionStage == 6) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 55;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                .resources[OpenSHC::Game::Resources::RT_CHEESE] = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].dairyProductionStage = 0;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 0;
        }
        if (DAT_BuildingsState::instance.field4_0x10 != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingAreaTileGraphics,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance);
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].numberOfAnimals = 0;
        int const cow1 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[1];
        if (cow1 == 0
            || DAT_UnitsState::instance.units[cow1].uid
                != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID[1]) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[1] = 0;
        }
        int const cow2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[2];
        if (cow2 == 0
            || DAT_UnitsState::instance.units[cow2].uid
                != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID[2]) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[2] = 0;
        }
        int const cow3 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[3];
        if (cow3 == 0
            || DAT_UnitsState::instance.units[cow3].uid
                != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID[3]) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[3] = 0;
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
