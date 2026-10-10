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

    // FUNCTION: STRONGHOLDCRUSADER 0x004138D0
    void Buildings::UpdatePoleturnersWorkshop()
    {
        int* piVar1;
        short* psVar2;
        short sVar3;
        short sVar4;
        ResourceTypeShort RVar5;
        UnitStateShort UVar6;
        byte bVar7;
        int iVar8;
        int buildingID;
        int iVar9;
        bool bVar10;
        sVar3 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        bVar10 = false;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field138_0x1c2 = 1;
        sVar4 = DAT_BuildingsState::instance.buildings[buildingID].workers[0];
        piVar1 = &DAT_GameState::instance.playerDataArray[sVar3].countFletchersPoleturners;
        *piVar1 = *piVar1 + 1;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = (ushort)(sVar4);
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
        iVar9 = buildingID * 0x32c;
        RVar5 = DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext;
        if (RVar5 == Game::Resources::RT_SPEAR) {
            sVar3 = DAT_BuildingsState::instance.buildings[buildingID].state;
            if (!sVar3) {
                if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0
                    && (((sVar3 = DAT_BuildingsState::instance.buildings[buildingID].animationIndex,
                             sVar3 == 7 || (sVar3 == 0x27))
                            || (sVar3 == 0x4a))
                        || (((sVar3 == 0x6a || (sVar3 == 0x8c)) || (sVar3 == 0xaf))))) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                        (int)((short)DAT_BuildingsState::instance.buildings[buildingID].y), DE::SHCDE::FX_POLE_TURN);
                    buildingID = DAT_CurrentBuildingID::instance;
                }
                iVar9 = buildingID * 0x32c;
                sVar3 = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    bVar7 = DAT_BuildingDefinedData::instance.field78_0x54cc[sVar3];
                } else {
                    bVar7 = DAT_BuildingDefinedData::instance.PoleturnersWorkshopAnimationFrames4[sVar3];
                }
                if ('\0' < (char)bVar7) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = (char)bVar7 + 0x5e;
                }
                bVar10 = '\0' >= (char)bVar7;
                sVar3 = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                if (!sVar3) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0x1f;
                } else if (sVar3 < 0x1e) {
                    psVar2 = &DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength;
                    *psVar2 = *psVar2 + -1;
                } else {
                    DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0;
                }
            } else {
                if (sVar3 != 1)
                    goto LAB_00413cb2;
                bVar7 = DAT_BuildingDefinedData::instance.PoleturnersWorkshopAnimationFrames5
                            [DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                if ('\0' < (char)bVar7) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = (char)bVar7 + 0x5e;
                }
                bVar10 = (char)bVar7 < '\x01';
                DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength
                    = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
            }
            if (bVar10) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationIndex + iVar9) = 0;
                sVar3 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8);
                if (!sVar3) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8) = 1;
                } else {
                    bVar10 = sVar3 == 1;
                LAB_00413c9c:
                    if (bVar10) {
                        piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].animationCycleCount + iVar9);
                        *piVar1 = *piVar1 + 1;
                        *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationCycleCompleted + iVar9)
                            = 1;
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8) = 0;
                    }
                }
            }
        } else if (RVar5 == Game::Resources::RT_PIKE) {
            sVar3 = DAT_BuildingsState::instance.buildings[buildingID].state;
            if (!sVar3) {
                bVar7 = DAT_BuildingDefinedData::instance.PoleturnersWorkshopAnimationFrames1
                            [DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                if ('\0' < (char)bVar7) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = (int)(char)bVar7;
                }
                bVar10 = (char)bVar7 < '\x01';
                sVar3 = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                if (!sVar3) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0x1f;
                } else if (sVar3 < 0x1e) {
                    psVar2 = &DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength;
                    *psVar2 = *psVar2 + -1;
                } else {
                    if (DAT_BuildingsState::instance.buildings[buildingID].animationFrame != 0x3d)
                        goto LAB_00413c50;
                    psVar2 = &DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength;
                    *psVar2 = *psVar2 + 1;
                }
            } else if ((sVar3 == 1) || (sVar3 == 2)) {
                if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0
                    && (sVar3 = DAT_BuildingsState::instance.buildings[buildingID].animationIndex,
                        sVar3 == 2 || (sVar3 == 0x30))) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                        (int)((short)DAT_BuildingsState::instance.buildings[buildingID].y), DE::SHCDE::FX_POLE_GRIND);
                    buildingID = DAT_CurrentBuildingID::instance;
                }
                iVar9 = buildingID * 0x32c;
                sVar3 = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    bVar7 = DAT_BuildingDefinedData::instance.field75_0x53bc[sVar3];
                } else {
                    bVar7 = DAT_BuildingDefinedData::instance.PoleturnersWorkshopAnimationFrames2[sVar3];
                }
                if ('\0' < (char)bVar7) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = (char)bVar7 + 0x3d;
                }
                bVar10 = '\0' >= (char)bVar7;
                if (DAT_BuildingsState::instance.buildings[buildingID].animationIndex < 0x20) {
                    psVar2 = &DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength;
                    *psVar2 = *psVar2 + -1;
                } else {
                LAB_00413c50:
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -0x62) = 0;
                }
            } else {
                if (sVar3 != 3)
                    goto LAB_00413cb2;
                if ((char)DAT_BuildingDefinedData::instance.PoleturnersWorkshopAnimationFrames3
                        [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                    < '\x01') {
                    DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength
                        = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                    bVar10 = true;
                } else {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                        = (char)DAT_BuildingDefinedData::instance.PoleturnersWorkshopAnimationFrames3
                              [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                        + 0x3d;
                    DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength
                        = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                }
            }
            if (bVar10) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationIndex + iVar9) = 0;
                sVar3 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8);
                if (!sVar3) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8) = 1;
                } else if (sVar3 == 1) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8) = 2;
                } else {
                    if (sVar3 != 2) {
                        bVar10 = sVar3 == 3;
                        goto LAB_00413c9c;
                    }
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8) = 3;
                }
            }
        }
    LAB_00413cb2:
        sVar3 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -0x62);
        if (sVar3 < 0x20) {
            if (sVar3 < 0) {
                *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -0x62) = 0;
            }
        } else {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -0x62) = 0x1f;
        }
        iVar8 = (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].workerID + iVar9);
        if (iVar8) {
            UVar6 = DAT_UnitsState::instance.units[iVar8].state.generic;
            if (UVar6 == Map::Units::States::US_FIRE_WEAPONUnk) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar9) = 1;
                goto LAB_00413d10;
            }
            if (UVar6 == Map::Units::States::US_AIM_WEAPONUnk) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar9) = 1;
                goto LAB_00413d10;
            }
        }
        *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar9) = 0;
    LAB_00413d10:
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateVisuallyActiveState, DAT_BuildingsState::ptr)(
            buildingID);
        if (*(short*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar9)
            != *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -0x52)) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            iVar9 = DAT_CurrentBuildingID::instance * 0x32c;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
        bVar10 = DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY;
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + iVar9) = 1;
        if (bVar10) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + iVar9) = 0;
        }
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + iVar9) = 1;
        piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar9);
        *piVar1 = *piVar1 + 1;
        if ((char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar9) / 2]
            < '\x01') {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar9) = 0;
        }
        *(int*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + iVar9)
            = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                  [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar9) / 2];
    }

}
}
