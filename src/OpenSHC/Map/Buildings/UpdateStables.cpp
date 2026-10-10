#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    using Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x004174E0
    void Buildings::UpdateStables()
    {
        short* psVar1;
        char* pbVar2;
        int* piVar3;
        int buildingID;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::validateBuildingTetheredUnits, DAT_BuildingsState::ptr)(
            buildingID);
        if ((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals < '\x04'
            && (psVar1 = &DAT_BuildingsState::instance.buildings[buildingID].outpostRelatedUnk4, *psVar1 = *psVar1 + 1,
                0x226 < DAT_BuildingsState::instance.buildings[buildingID].outpostRelatedUnk4)) {
            pbVar2 = &DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals;
            *pbVar2 = *pbVar2 + 1;
            DAT_BuildingsState::instance.buildings[buildingID].outpostRelatedUnk4 = 0;
            MACRO_CALL_MEMBER(Game::GameStateStructures_Func::recountStablesAndHorses, DAT_GameState::ptr)();
            buildingID = DAT_CurrentBuildingID::instance;
        }
        DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
        piVar3 = &DAT_BuildingsState::instance.buildings[buildingID].animationTickCounter;
        *piVar3 = *piVar3 + 1;
        if (5 < DAT_BuildingsState::instance.buildings[buildingID].animationTickCounter) {
            DAT_BuildingsState::instance.buildings[buildingID].animationTickCounter = 0;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].animationTickCounter < 1) {
            if ((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals < '\x01') {
                DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite1 = 0;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField < '\x01') {
                piVar3 = &DAT_BuildingsState::instance.buildings[buildingID].campgroundVclock;
                *piVar3 = *piVar3 + 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .StablesAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].campgroundVclock]
                    < '\x01') {
                    DAT_BuildingsState::instance.buildings[buildingID].campgroundVclock = 0;
                }
                DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite1
                    = (int)(char)DAT_BuildingDefinedData::instance
                          .StablesAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].campgroundVclock];
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite1 = 0x2a;
            }
            if ((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals < '\x02') {
                DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2 = 0;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField < '\x02') {
                piVar3 = &DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame1;
                *piVar3 = *piVar3 + 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .StablesAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame1]
                    < '\x01') {
                    DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame1 = 0;
                }
                DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2
                    = (int)(char)DAT_BuildingDefinedData::instance.StablesAnimationFrames
                          [DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame1];
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2 = 0x29;
            }
            if ((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals < '\x03') {
                DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite3 = 0;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField < '\x03') {
                piVar3 = &DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame2;
                *piVar3 = *piVar3 + 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .StablesAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame2]
                    < '\x01') {
                    DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame2 = 0;
                }
                DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite3
                    = (int)(char)DAT_BuildingDefinedData::instance.StablesAnimationFrames
                          [DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame2];
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite3 = 0x28;
            }
            if ((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals < '\x04') {
                DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4 = 0;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField < '\x04') {
                piVar3 = &DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame3;
                *piVar3 = *piVar3 + 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .StablesAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame3]
                    < '\x01') {
                    DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame3 = 0;
                }
                DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4
                    = (int)(char)DAT_BuildingDefinedData::instance.StablesAnimationFrames
                          [DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame3];
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4 = 0x27;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
                piVar3 = &DAT_BuildingsState::instance.buildings[buildingID].flagSlot.ownerFlagFrame;
                *piVar3 = *piVar3 + 1;
                if ((char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                        [DAT_BuildingsState::instance.buildings[buildingID].flagSlot.ownerFlagFrame / 2]
                    < '\x01') {
                    DAT_BuildingsState::instance.buildings[buildingID].flagSlot.ownerFlagFrame = 0;
                }
                DAT_BuildingsState::instance.buildings[buildingID].overlayImageID
                    = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                          [DAT_BuildingsState::instance.buildings[buildingID].flagSlot.ownerFlagFrame / 2];
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = 0;
        }
    }

}
}
