#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004174E0
    void Buildings::UpdateStables()
    {
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::validateBuildingTetheredUnits,
            DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance);
        // A new horse every 550 ticks, up to four
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].numberOfAnimals < 4) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 += 1;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 > 550) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].numberOfAnimals += 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 = 0;
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::recountStablesAndHorses, DAT_GameState::ptr)();
            }
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter += 1;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter > 5) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter = 0;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter >= 1) {
            return;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].numberOfAnimals > 0) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].randomOutpostField > 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 42;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
                if (DAT_BuildingDefinedData::instance.StablesAnimationFrames
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock]
                    <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                    = DAT_BuildingDefinedData::instance.StablesAnimationFrames
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock];
            }
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 0;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].numberOfAnimals > 1) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].randomOutpostField > 1) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 41;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
                if (DAT_BuildingDefinedData::instance.StablesAnimationFrames
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1]
                    <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                    = DAT_BuildingDefinedData::instance.StablesAnimationFrames[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame1];
            }
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 0;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].numberOfAnimals > 2) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].randomOutpostField > 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 40;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
                if (DAT_BuildingDefinedData::instance.StablesAnimationFrames
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2]
                    <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                    = DAT_BuildingDefinedData::instance.StablesAnimationFrames[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame2];
            }
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 0;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].numberOfAnimals > 3) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].randomOutpostField > 3) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 39;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 += 1;
                if (DAT_BuildingDefinedData::instance.StablesAnimationFrames
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3]
                    <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 = 0;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4
                    = DAT_BuildingDefinedData::instance.StablesAnimationFrames[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame3];
            }
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 0;
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
