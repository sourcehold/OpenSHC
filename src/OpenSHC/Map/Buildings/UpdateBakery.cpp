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

    // FUNCTION: STRONGHOLDCRUSADER 0x00414720
    void Buildings::UpdateBakery()
    {
        undefined4* puVar1;
        int* piVar2;
        short* psVar3;
        byte bVar4;
        int sVar5;
        UnitStateShort UVar6;
        bool bVar7;
        int iVar8;
        int iVar9;
        int iVar10;
        sVar5 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar8 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field138_0x1c2 = 1;
        DAT_BuildingsState::instance.buildings[iVar8].renderAnimation
            = (ushort)(DAT_BuildingsState::instance.buildings[iVar8].workers[0] != 0);
        if ((char)((char)DAT_BuildingsState::instance.buildings[iVar8].uid
                + (char)DAT_GameCore::instance.mapTimeInTicks)
            == '\0') {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingPlacementRotationPreview, DAT_TileMapState::ptr)(
                (int)(short)DAT_BuildingsState::instance.buildings[iVar8].x,
                (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar8].y)));
            iVar8 = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation
                = (short)DAT_TileMapState::instance.uiBuildingRotation;
        }
        iVar9 = iVar8 * 0x32c;
        if (DAT_BuildingsState::instance.buildings[iVar8].currentlyNeededEmployeeCount == 0) {
            puVar1 = &DAT_GameState::instance.playerDataArray[sVar5].someCount13;
            *puVar1 = *puVar1 + 1;
        }
        piVar2 = &DAT_GameState::instance.playerDataArray[sVar5].countBakers;
        *piVar2 = *piVar2 + 1;
        sVar5 = DAT_BuildingsState::instance.buildings[iVar8].state;
        if (!sVar5) {
            if (DAT_BuildingsState::instance.buildings[iVar8].animationActive != 0) {
                sVar5 = DAT_BuildingsState::instance.buildings[iVar8].animationIndex;
                if (sVar5 == 0x15 || sVar5 == 0x62 || sVar5 == 0x73 || sVar5 == 0xc0 || sVar5 == 0xd1 || sVar5 == 0x11e
                    || sVar5 == 0x12f || sVar5 == 0x17c) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[iVar8].x,
                        (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar8].y)), DE::SHCDE::FX_BAKE2);
                    iVar8 = DAT_CurrentBuildingID::instance;
                }
                sVar5 = DAT_BuildingsState::instance.buildings[iVar8].animationIndex;
                if (sVar5 == 0x23 || sVar5 == 0x81 || sVar5 == 0xdf || sVar5 == 0x13d) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[iVar8].x,
                        (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar8].y)), DE::SHCDE::FX_BAKE);
                    iVar8 = DAT_CurrentBuildingID::instance;
                }
            }
            iVar9 = iVar8 * 0x32c;
            bVar4 = DAT_BuildingDefinedData::instance
                        .BakeryAnimationFrames1[DAT_BuildingsState::instance.buildings[iVar8].animationIndex];
            if ('\0' < (char)bVar4) {
                DAT_BuildingsState::instance.buildings[iVar8].animationFrame = (int)(char)bVar4;
            }
            bVar7 = '\0' >= (char)bVar4;
            sVar5 = DAT_BuildingsState::instance.buildings[iVar8].animationIndex;
            if (!sVar5) {
                DAT_BuildingsState::instance.buildings[iVar8].animationFrame = 0;
                DAT_BuildingsState::instance.buildings[iVar8].renderBlendStrength = 0x1f;
            } else if (sVar5 < 0xf) {
                psVar3 = &DAT_BuildingsState::instance.buildings[iVar8].renderBlendStrength;
                *psVar3 = *psVar3 + -2;
            } else {
                DAT_BuildingsState::instance.buildings[iVar8].renderBlendStrength = 0;
            }
        LAB_0041495c:
            if (bVar7) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationIndex + iVar9) = 0;
                sVar5 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8);
                if (!sVar5) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8) = 1;
                } else if (sVar5 == 1) {
                    piVar2 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].animationCycleCount + iVar9);
                    *piVar2 = *piVar2 + 1;
                    *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationCycleCompleted + iVar9) = 1;
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8) = 0;
                }
            }
        } else if (sVar5 == 1) {
            bVar4 = DAT_BuildingDefinedData::instance
                        .BakeryAnimationFrames2[DAT_BuildingsState::instance.buildings[iVar8].animationIndex];
            if ('\0' < (char)bVar4) {
                DAT_BuildingsState::instance.buildings[iVar8].animationFrame = (int)(char)bVar4;
            }
            bVar7 = '\0' >= (char)bVar4;
            DAT_BuildingsState::instance.buildings[iVar8].renderBlendStrength
                = DAT_BuildingsState::instance.buildings[iVar8].animationIndex * 2;
            goto LAB_0041495c;
        }
        sVar5 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -0x62);
        if (sVar5 < 0x20) {
            if (sVar5 < 0) {
                *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -0x62) = 0;
            }
        } else {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -0x62) = 0x1f;
        }
        iVar10 = (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].workerID + iVar9);
        if (iVar10) {
            UVar6 = DAT_UnitsState::instance.units[iVar10].state.generic;
            if (UVar6 == Map::Units::States::US_RELOAD_WEAPONUnk) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar9) = 1;
                goto LAB_004149f5;
            }
            if (UVar6 == (UnitState)3) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar9) = 1;
                goto LAB_004149f5;
            }
        }
        *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar9) = 0;
    LAB_004149f5:
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateVisuallyActiveState, DAT_BuildingsState::ptr)(
            iVar8);
        if (*(short*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar9)
            != *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -0x52)) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(iVar8);
            iVar9 = DAT_CurrentBuildingID::instance * 0x32c;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
        iVar8 = 0;
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + iVar9) = 1;
        if (!iVar10) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar9) = 0;
        } else if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8) == 1) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar9) = 0x44;
        } else {
            sVar5 = *(short*)((int)&DAT_BuildingsState::instance.buildings[0].animationIndex + iVar9);
            if (sVar5 < 100) {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar9) = 0;
            } else if (sVar5 < 0xc2) {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar9) = 0x41;
            } else if (sVar5 < 0x120) {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar9) = 0x42;
            } else {
                *(uint*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar9)
                    = (0x17d < sVar5) + 0x43;
            }
        }
        piVar2 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].animationTickCounter + iVar9);
        *piVar2 = *piVar2 + 1;
        if (3 < *(int*)((int)&DAT_BuildingsState::instance.buildings[0].animationTickCounter + iVar9)) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].animationTickCounter + iVar9) = 0;
        }
        if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].workerID + iVar9) == 0) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite2 + iVar9) = 0;
        } else {
            if (*(int*)((int)&DAT_BuildingsState::instance.buildings[0].animationTickCounter + iVar9) == 0) {
                piVar2 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar9);
                *piVar2 = *piVar2 + 1;
            }
            if ((char)DAT_BuildingDefinedData::instance.SecondaryOverlayAnimationFrames[*(
                    int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar9)]
                < '\x01') {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar9) = 0;
            }
            *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite2 + iVar9)
                = (char)DAT_BuildingDefinedData::instance.SecondaryOverlayAnimationFrames[*(
                      int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar9)]
                + 0x10;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + iVar9) = 1;
            piVar2 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar9);
            *piVar2 = *piVar2 + 1;
            if ((char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                    [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar9) / 2]
                < '\x01') {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar9) = 0;
            }
            iVar8 = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                        [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar9) / 2];
        }
        *(int*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + iVar9) = iVar8;
    }

}
}
