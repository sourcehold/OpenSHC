#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00415E80
    void Buildings::UpdateOilSmelter()
    {
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCompleted = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter += 1;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter > 1) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter = 0;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 1;

        // OilSmelterAnimationFrames* are declared byte, but the original reads them signed
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 2;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 1) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 0;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 2) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -16;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -92;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 31;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 3;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 3) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -16;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -92;
            int const frame
                = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames1
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 4;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 32;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 4;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength -= 1;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 4) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -16;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -92;
            int const frame
                = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames2
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 5;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 32;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 28
                && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a = 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                    .resources[OpenSHC::Game::Resources::RT_PITCH] += 1;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 5) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -16;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -92;
            int const frame
                = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames3
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame > 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 32;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCompleted = 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 1;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength < 31) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength += 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCompleted = 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 1;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 6) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -72;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -84;
            int const frame
                = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames4
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 7;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 7;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength -= 1;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 7) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0
                && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 10) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                    OpenSHC::DE::SHCDE::FX_POT_OPEN);
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0
                && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 13) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                    OpenSHC::DE::SHCDE::FX_OIL_REFILL);
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -72;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -84;
            int const frame
                = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames5
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 8;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                    .resources[OpenSHC::Game::Resources::RT_PITCH] -= 1;
                // Unit state 9 has no UnitState constant.
                int const engineerID
                    = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].engineerUnitID;
                if (engineerID != 0
                    && DAT_UnitsState::instance.units[engineerID].unitType == OpenSHC::Map::Units::UT_E_ENGINEER
                    && DAT_UnitsState::instance.units[engineerID].state.generic == 9) {
                    DAT_UnitsState::instance.units[engineerID].resourceToDeposit = 1;
                }
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 8) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -72;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -84;
            int const frame
                = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames6
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCompleted = 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 32;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength < 31) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength += 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCompleted = 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 1;
            }
        }

        int smoke;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                .resources[OpenSHC::Game::Resources::RT_PITCH]
            >= 1) {
            smoke = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames8
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
        } else {
            smoke = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames7
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
        }
        if (smoke <= 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = smoke + 61;
        }

        // The pot shows one of nine fill levels, or the flare-up after a refill
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 1) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                    OpenSHC::DE::SHCDE::FX_POT_FLARE_UP);
            }
            int const frame
                = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames10
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a = 0;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                    = frame + 122;
            }
        } else {
            int const pitch = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                  .resources[OpenSHC::Game::Resources::RT_PITCH];
            if (pitch <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
            } else if (pitch <= 1) {
                int const frame
                    = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames9[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame1];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                        = frame + 77;
                }
            } else if (pitch <= 2) {
                int const frame
                    = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames9[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame1];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                        = frame + 82;
                }
            } else if (pitch <= 3) {
                int const frame
                    = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames9[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame1];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                        = frame + 87;
                }
            } else if (pitch <= 4) {
                int const frame
                    = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames9[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame1];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                        = frame + 92;
                }
            } else if (pitch <= 5) {
                int const frame
                    = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames9[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame1];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                        = frame + 97;
                }
            } else if (pitch <= 6) {
                int const frame
                    = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames9[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame1];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                        = frame + 102;
                }
            } else if (pitch <= 7) {
                int const frame
                    = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames9[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame1];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                        = frame + 107;
                }
            } else if (pitch <= 8) {
                int const frame
                    = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames9[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame1];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                        = frame + 112;
                }
            } else {
                int const frame
                    = (char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames9[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame1];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                        = frame + 117;
                }
            }
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState == -1) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState = 0;
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
