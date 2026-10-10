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

    // FUNCTION: STRONGHOLDCRUSADER 0x00413DC0
    void Buildings::UpdateArmorersWorkshop()
    {
        int* piVar1;
        short sVar2;
        UnitStateShort UVar3;
        bool bVar4;
        byte bVar5;
        short sVar6;
        int iVar7;
        int buildingID;
        int iVar8;
        sVar6 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field138_0x1c2 = 1;
        sVar2 = DAT_BuildingsState::instance.buildings[buildingID].workers[0];
        piVar1 = &DAT_GameState::instance.playerDataArray[sVar6].countArmorersAndBlacksmiths;
        *piVar1 = *piVar1 + 1;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = (ushort)(sVar2 != 0);
        if ((char)((char)DAT_BuildingsState::instance.buildings[buildingID].uid
                + (char)DAT_GameCore::instance.mapTimeInTicks)
            == '\0') {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingPlacementRotationPreview, DAT_TileMapState::ptr)(
                (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                (int)((short)DAT_BuildingsState::instance.buildings[buildingID].y));
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation
                = (short)DAT_TileMapState::instance.uiBuildingRotation;
        }
        iVar8 = buildingID * 0x32c;
        sVar6 = DAT_BuildingsState::instance.buildings[buildingID].state;
        if (sVar6 == 0) {
            if ((DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0)
                && (DAT_BuildingDefinedData::instance.ArmorersWorkshopAnimationFrames1
                        [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                    == 5)) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                    (int)((short)DAT_BuildingsState::instance.buildings[buildingID].y), DE::SHCDE::FX_ARMOUR_HIT);
                buildingID = DAT_CurrentBuildingID::instance;
            }
            iVar8 = buildingID * 0x32c;
            sVar6 = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                bVar5 = DAT_BuildingDefinedData::instance.ArmorersWorkshopAnimationFrames1[sVar6];
            } else {
                bVar5 = DAT_BuildingDefinedData::instance.ArmorersWorkshopAnimationFrames2[sVar6];
            }
            if ('\0' < (char)bVar5) {
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = (int)(char)bVar5;
            }
            bVar4 = '\0' >= (char)bVar5;
            if (DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0x1f;
            } else {
                sVar6 = DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength;
                if (0 < sVar6) {
                    sVar6 = sVar6 + -1;
                    goto LAB_00413f5c;
                }
            }
        LAB_00413f63:
            if (bVar4) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationIndex + iVar8) = 0;
                if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) == 0) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 1;
                } else {
                    piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].animationCycleCount + iVar8);
                    *piVar1 = *piVar1 + 1;
                    *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationCycleCompleted + iVar8) = 1;
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 0;
                }
            }
        } else if (sVar6 == 1) {
            bVar5 = DAT_BuildingDefinedData::instance.ArmorersWorkshopAnimationFrames3
                        [DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
            if ('\0' < (char)bVar5) {
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = (int)(char)bVar5;
            }
            bVar4 = '\0' >= (char)bVar5;
            sVar6 = DAT_BuildingsState::instance.buildings[buildingID].animationIndex * 2;
        LAB_00413f5c:
            *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -0x62) = sVar6;
            goto LAB_00413f63;
        }
        sVar6 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -0x62);
        if (sVar6 < 0x20) {
            if (sVar6 < 0) {
                *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -0x62) = 0;
            }
        } else {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -0x62) = 0x1f;
        }
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + iVar8) = 0;
        iVar7 = (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].workerID + iVar8);
        if (iVar7 != 0) {
            UVar3 = DAT_UnitsState::instance.units[iVar7].state.generic;
            if (UVar3 == Map::Units::States::US_FIRE_WEAPONUnk) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar8) = 1;
                goto LAB_00414007;
            }
            if (UVar3 == Map::Units::States::US_AIM_WEAPONUnk) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar8) = 1;
                goto LAB_00414007;
            }
            if (UVar3 == Map::Units::States::US_JESTER_ROAM_TO) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar8) = 1;
                goto LAB_00414007;
            }
        }
        *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar8) = 0;
    LAB_00414007:
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateVisuallyActiveState, DAT_BuildingsState::ptr)(
            buildingID);
        if (*(short*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar8)
            != *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -0x52)) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
            iVar8 = DAT_CurrentBuildingID::instance * 0x32c;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + iVar8) = 0;
        }
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + iVar8) = 1;
        piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar8);
        *piVar1 = *piVar1 + 1;
        if ((char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar8) / 2]
            < '\x01') {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar8) = 0;
        }
        *(int*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + iVar8)
            = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                  [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar8) / 2];
    }

}
}
