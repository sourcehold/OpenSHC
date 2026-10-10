#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/States/UnitStateShort.hpp"

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

    using DE::SHCDE::eSFX;
    using Game::GameMode;
    using Map::Units::States::UnitState;
    using Map::Units::States::UnitStateShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x00414B60
    void Buildings::UpdateBrewery()
    {
        undefined4* puVar1;
        int* piVar2;
        short sVar3;
        UnitStateShort UVar4;
        short sVar5;
        byte bVar6;
        int buildingID;
        int iVar7;
        bool bVar8;
        sVar3 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field138_0x1c2 = 1;
        iVar7 = (int)DAT_BuildingsState::instance.buildings[buildingID].workerID[0];
        if (!iVar7) {
        LAB_00414bea:
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
        } else {
            UVar4 = DAT_UnitsState::instance.units[iVar7].state.generic;
            if (UVar4 == Map::Units::States::US_FIRE_WEAPONUnk) {
                DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
            } else {
                if (UVar4 != Map::Units::States::US_AIM_WEAPONUnk)
                    goto LAB_00414bea;
                DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
            }
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].currentlyNeededEmployeeCount == 0) {
            puVar1 = &DAT_GameState::instance.playerDataArray[sVar3].someCount12;
            *puVar1 = *puVar1 + 1;
        }
        sVar5 = DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive;
        piVar2 = &DAT_GameState::instance.playerDataArray[sVar3].countBrewers;
        *piVar2 = *piVar2 + 1;
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateVisuallyActiveState, DAT_BuildingsState::ptr)(
            buildingID);
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
        if (!sVar5) {
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation
                = (ushort)(DAT_BuildingsState::instance.buildings[buildingID].workers[0] != 0);
        }
        DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
        if ((char)((char)DAT_BuildingsState::instance.buildings[buildingID].uid
                + (char)DAT_GameCore::instance.mapTimeInTicks)
            == '\0') {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingPlacementRotationPreview, DAT_TileMapState::ptr)(
                (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                (int)((int)((short)DAT_BuildingsState::instance.buildings[buildingID].y)));
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation
                = (short)DAT_TileMapState::instance.uiBuildingRotation;
        }
        iVar7 = buildingID * 0x32c;
        sVar3 = DAT_BuildingsState::instance.buildings[buildingID].state;
        if (!sVar3) {
            if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0
                && (((((sVar3 = DAT_BuildingsState::instance.buildings[buildingID].animationIndex,
                           sVar3 == 5 || (sVar3 == 0x34))
                          || (sVar3 == 100))
                         || ((sVar3 == 0x96 || (sVar3 == 200))))
                        || ((sVar3 == 0xfa || ((sVar3 == 300 || (sVar3 == 0x15e))))))
                    || (sVar3 == 400))) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                    (int)((int)((short)DAT_BuildingsState::instance.buildings[buildingID].y)), DE::SHCDE::FX_STIR);
                buildingID = DAT_CurrentBuildingID::instance;
            }
            bVar6 = DAT_BuildingDefinedData::instance
                        .BreweryAnimationFrames1[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
        LAB_00414d7d:
            iVar7 = buildingID * 0x32c;
            if ('\0' < (char)bVar6) {
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = (int)(char)bVar6;
                goto LAB_00415004;
            }
        } else if (sVar3 == 1) {
            if ('\0' < (char)DAT_BuildingDefinedData::instance
                    .BreweryAnimationFrames4[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]) {
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                    = (char)DAT_BuildingDefinedData::instance
                          .BreweryAnimationFrames4[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                    + 0x10;
                goto LAB_00415004;
            }
        } else if (sVar3 == 2) {
            if ((DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0)
                && (DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 5)) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                    (int)((int)((short)DAT_BuildingsState::instance.buildings[buildingID].y)), DE::SHCDE::FX_STIR);
                buildingID = DAT_CurrentBuildingID::instance;
            }
            bVar6 = DAT_BuildingDefinedData::instance
                        .BreweryAnimationFrames2[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
        LAB_00414e12:
            iVar7 = buildingID * 0x32c;
            if ('\0' < (char)bVar6) {
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = (int)(char)bVar6;
                goto LAB_00415004;
            }
        } else if (sVar3 == 3) {
            if ('\0' < (char)DAT_BuildingDefinedData::instance
                    .BreweryAnimationFrames4[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]) {
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                    = (char)DAT_BuildingDefinedData::instance
                          .BreweryAnimationFrames4[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                    + 0x10;
                goto LAB_00415004;
            }
        } else {
            if (sVar3 == 4) {
                if ((DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0)
                    && (DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 5)) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                        (int)((int)((short)DAT_BuildingsState::instance.buildings[buildingID].y)), DE::SHCDE::FX_STIR);
                    buildingID = DAT_CurrentBuildingID::instance;
                }
                bVar6 = DAT_BuildingDefinedData::instance
                            .BreweryAnimationFrames2[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                goto LAB_00414d7d;
            }
            if (sVar3 == 5) {
                if ('\0' < (char)DAT_BuildingDefinedData::instance
                        .BreweryAnimationFrames4[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                        = (char)DAT_BuildingDefinedData::instance.BreweryAnimationFrames4
                              [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                        + 0x10;
                    goto LAB_00415004;
                }
            } else {
                if (sVar3 != 6) {
                    if (sVar3 != 7)
                        goto LAB_00415004;
                    if ((DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0)
                        && (DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 5)) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                            (int)((int)((short)DAT_BuildingsState::instance.buildings[buildingID].y)),
                            DE::SHCDE::FX_STIR);
                        buildingID = DAT_CurrentBuildingID::instance;
                    }
                    bVar6 = DAT_BuildingDefinedData::instance.BreweryAnimationFrames3
                                [DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                    goto LAB_00414e12;
                }
                if ('\0' < (char)DAT_BuildingDefinedData::instance
                        .BreweryAnimationFrames5[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                        = (char)DAT_BuildingDefinedData::instance.BreweryAnimationFrames5
                              [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                        + 0x20;
                    goto LAB_00415004;
                }
            }
        }
        *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationIndex + iVar7) = 0;
        sVar3 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8);
        if (!sVar3) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 1;
        } else if (sVar3 == 1) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 2;
        } else if (sVar3 == 2) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 3;
        } else if (sVar3 == 3) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 4;
        } else if (sVar3 == 4) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 5;
        } else if (sVar3 == 5) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 6;
        } else if (sVar3 == 6) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 7;
        } else if (sVar3 == 7) {
            piVar2 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].animationCycleCount + iVar7);
            *piVar2 = *piVar2 + 1;
            bVar8 = DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY;
            *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationCycleCompleted + iVar7) = 1;
            *(ushort*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = -(ushort)bVar8 & 4;
        }
    LAB_00415004:
        if (!sVar5) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar7) = 0;
        } else {
            if (*(short*)((int)&DAT_BuildingsState::instance.buildings[0].animationActive + iVar7) != 0) {
                piVar2 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar7);
                *piVar2 = *piVar2 + 1;
            }
            if ((char)DAT_BuildingDefinedData::instance.BreweryAnimationFrames6[*(
                    int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar7)]
                < '\x01') {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar7) = 0;
            }
            *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar7)
                = (char)DAT_BuildingDefinedData::instance.BreweryAnimationFrames6[*(
                      int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar7)]
                + 0x30;
        }
        piVar2 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].animationTickCounter + iVar7);
        *piVar2 = *piVar2 + 1;
        if (3 < *(int*)((int)&DAT_BuildingsState::instance.buildings[0].animationTickCounter + iVar7)) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].animationTickCounter + iVar7) = 0;
        }
        if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].workerID + iVar7) == 0) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite2 + iVar7) = 0;
        } else {
            if (*(int*)((int)&DAT_BuildingsState::instance.buildings[0].animationTickCounter + iVar7) == 0) {
                piVar2 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar7);
                *piVar2 = *piVar2 + 1;
            }
            if ((char)DAT_BuildingDefinedData::instance.SecondaryOverlayAnimationFrames[*(
                    int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar7)]
                < '\x01') {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar7) = 0;
            }
            *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite2 + iVar7)
                = (char)DAT_BuildingDefinedData::instance.SecondaryOverlayAnimationFrames[*(
                      int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar7)]
                + 0x10;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + iVar7) = 1;
            piVar2 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar7);
            *piVar2 = *piVar2 + 1;
            if ((char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                    [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar7) / 2]
                < '\x01') {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar7) = 0;
            }
            *(int*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + iVar7)
                = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar7) / 2];
        }
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + iVar7) = 0;
    }

}
}
