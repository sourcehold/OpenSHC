#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
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
    using Game::Resources::ResourceType;
    using Map::Units::States::UnitState;
    using Map::Units::States::UnitStateShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x00412D50
    void Buildings::UpdateFletchersWorkshop()
    {
        int* piVar1;
        short* psVar2;
        short sVar3;
        short sVar4;
        UnitStateShort UVar5;
        bool bVar6;
        byte animcycle;
        int iVar7;
        int buildingID_00;
        int buildingID;
        sVar3 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID_00 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field138_0x1c2 = 1;
        sVar4 = DAT_BuildingsState::instance.buildings[buildingID_00].workers[0];
        piVar1 = &DAT_GameState::instance.playerDataArray[sVar3].countFletchersPoleturners;
        *piVar1 = *piVar1 + 1;
        DAT_BuildingsState::instance.buildings[buildingID_00].renderAnimation = (ushort)(sVar4);
        DAT_BuildingsState::instance.buildings[buildingID_00].displayOwnerFlag = 0;
        if ((char)((char)DAT_BuildingsState::instance.buildings[buildingID_00].uid
                + (char)DAT_GameCore::instance.mapTimeInTicks)
            == '\0') {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingPlacementRotationPreview, DAT_TileMapState::ptr)(
                (int)(short)DAT_BuildingsState::instance.buildings[buildingID_00].x,
                (int)((short)DAT_BuildingsState::instance.buildings[buildingID_00].y));
            buildingID_00 = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation
                = (short)DAT_TileMapState::instance.uiBuildingRotation;
        }
        buildingID = buildingID_00 * 0x32c;
        bVar6 = true;
        sVar3 = DAT_BuildingsState::instance.buildings[buildingID_00].state;
        if (DAT_BuildingsState::instance.buildings[buildingID_00].producedItemTypeNext == Game::Resources::RT_BOW) {
            if (!sVar3) {
                if (DAT_BuildingsState::instance.buildings[buildingID_00].animationActive != 0
                    && (sVar3 = DAT_BuildingsState::instance.buildings[buildingID_00].animationIndex,
                        sVar3 == 8 || (sVar3 == 0x3a))) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[buildingID_00].x,
                        (int)((short)DAT_BuildingsState::instance.buildings[buildingID_00].y),
                        DE::SHCDE::FX_FLETCH_LONG);
                    buildingID_00 = DAT_CurrentBuildingID::instance;
                }
                bVar6 = true;
                buildingID = buildingID_00 * 0x32c;
                sVar3 = DAT_BuildingsState::instance.buildings[buildingID_00].animationIndex;
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    animcycle = DAT_BuildingDefinedData::instance.field43_0x430c[sVar3];
                } else {
                    animcycle = DAT_BuildingDefinedData::instance.FletcherWorkshopAnimationCycle[sVar3];
                }
                if ('\0' < (char)animcycle) {
                    iVar7 = (int)(char)animcycle;
                LAB_00412f15:
                    *(int*)((int)&DAT_BuildingsState::instance.buildings[0].animationFrame + buildingID) = iVar7;
                    bVar6 = false;
                }
            LAB_00412f1b:
                sVar3 = *(short*)((int)&DAT_BuildingsState::instance.buildings[0].animationIndex + buildingID);
                if (!sVar3) {
                    *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].animationFrame + buildingID) = 0;
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + buildingID + -0x62)
                        = 0x1f;
                } else if (sVar3 < 0x1e) {
                    psVar2 = (short*)((int)DAT_BuildingsState::instance.buildings[0].resources + buildingID + -0x62);
                    *psVar2 = *psVar2 + -1;
                } else {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + buildingID + -0x62) = 0;
                }
            } else {
                if (sVar3 != 1)
                    goto LAB_00412fc8;
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    if ((char)DAT_BuildingDefinedData::instance.FletchersWorkshopAnimationFrames1
                            [DAT_BuildingsState::instance.buildings[buildingID_00].animationIndex]
                        < '\x01') {
                        bVar6 = true;
                    } else {
                        iVar7 = (int)(char)DAT_BuildingDefinedData::instance.FletchersWorkshopAnimationFrames1
                                    [DAT_BuildingsState::instance.buildings[buildingID_00].animationIndex];
                    LAB_00412f7b:
                        DAT_BuildingsState::instance.buildings[buildingID_00].animationFrame = iVar7;
                        bVar6 = false;
                    }
                }
            LAB_00412f81:
                DAT_BuildingsState::instance.buildings[buildingID_00].renderBlendStrength
                    = DAT_BuildingsState::instance.buildings[buildingID_00].animationIndex;
            }
            if (bVar6) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationIndex + buildingID) = 0;
                sVar3 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + buildingID + -8);
                if (!sVar3) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + buildingID + -8) = 1;
                } else if (sVar3 == 1) {
                    piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].animationCycleCount + buildingID);
                    /*
                      Done working on product
                     */
                    *piVar1 = *piVar1 + 1;
                    *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationCycleCompleted + buildingID)
                        = 1;
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + buildingID + -8) = 0;
                }
            }
        } else {
            if (!sVar3) {
                sVar3 = DAT_BuildingsState::instance.buildings[buildingID_00].animationIndex;
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    animcycle = DAT_BuildingDefinedData::instance.field45_0x44e4[sVar3];
                } else {
                    animcycle = DAT_BuildingDefinedData::instance.field46_0x4674[sVar3];
                }
                if ('\0' < (char)animcycle) {
                    iVar7 = (char)animcycle + 0x24;
                    goto LAB_00412f15;
                }
                bVar6 = true;
                goto LAB_00412f1b;
            }
            if (sVar3 == 1) {
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    if ('\0' < (char)DAT_BuildingDefinedData::instance.FletchersWorkshopAnimationFrames2
                            [DAT_BuildingsState::instance.buildings[buildingID_00].animationIndex]) {
                        iVar7 = (char)DAT_BuildingDefinedData::instance.FletchersWorkshopAnimationFrames2
                                    [DAT_BuildingsState::instance.buildings[buildingID_00].animationIndex]
                            + 0x24;
                        goto LAB_00412f7b;
                    }
                    bVar6 = true;
                } else {
                    bVar6 = true;
                }
                goto LAB_00412f81;
            }
        }
    LAB_00412fc8:
        sVar3 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + buildingID + -0x62);
        if (sVar3 < 0x20) {
            if (sVar3 < 0) {
                *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + buildingID + -0x62) = 0;
            }
        } else {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + buildingID + -0x62) = 0x1f;
        }
        iVar7 = (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].workerID + buildingID);
        if (iVar7) {
            UVar5 = DAT_UnitsState::instance.units[iVar7].state.generic;
            if (UVar5 == Map::Units::States::US_AIM_WEAPONUnk) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + buildingID)
                    = 1;
                goto LAB_00413026;
            }
            if (UVar5 == Map::Units::States::US_RELOAD_WEAPONUnk) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + buildingID)
                    = 1;
                goto LAB_00413026;
            }
        }
        *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + buildingID) = 0;
    LAB_00413026:
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateVisuallyActiveState, DAT_BuildingsState::ptr)(
            buildingID_00);
        if (*(short*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + buildingID)
            != *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + buildingID + -0x52)) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            buildingID = DAT_CurrentBuildingID::instance * 0x32c;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + buildingID) = 0;
        }
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + buildingID) = 1;
        piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + buildingID);
        *piVar1 = *piVar1 + 1;
        if ((char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + buildingID) / 2]
            < '\x01') {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + buildingID) = 0;
        }
        *(int*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + buildingID)
            = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                  [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + buildingID) / 2];
    }

}
}
