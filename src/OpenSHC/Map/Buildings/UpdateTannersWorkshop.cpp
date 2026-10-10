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

    // FUNCTION: STRONGHOLDCRUSADER 0x004140B0
    void Buildings::UpdateTannersWorkshop()
    {
        int* piVar1;
        UnitStateShort UVar2;
        bool bVar3;
        byte bVar4;
        short sVar5;
        int iVar6;
        int buildingID;
        int iVar7;
        bVar3 = false;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field138_0x1c2 = 1;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation
            = (ushort)(DAT_BuildingsState::instance.buildings[buildingID].workers[0] != 0);
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
        iVar7 = buildingID * 0x32c;
        if (DAT_BuildingsState::instance.buildings[buildingID].state < 7) {
            DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX
                = DAT_BuildingDefinedData::instance
                      .SpriteOffsets1[(short)DAT_BuildingsState::instance.buildings[buildingID].buildingType][0][0]
                + 1;
            DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY
                = DAT_BuildingDefinedData::instance
                      .SpriteOffsets1[(short)DAT_BuildingsState::instance.buildings[buildingID].buildingType][1][0]
                + 1;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX
                = DAT_BuildingDefinedData::instance
                      .SpriteOffsets1[(short)DAT_BuildingsState::instance.buildings[buildingID].buildingType][0][0];
            DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY
                = DAT_BuildingDefinedData::instance
                      .SpriteOffsets1[(short)DAT_BuildingsState::instance.buildings[buildingID].buildingType][1][0];
        }
        sVar5 = DAT_BuildingsState::instance.buildings[buildingID].state;
        if (!sVar5) {
            sVar5 = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                bVar4 = DAT_BuildingDefinedData::instance.AnimTannerSolitary[sVar5];
            } else {
                bVar4 = DAT_BuildingDefinedData::instance.AnimTanner[sVar5];
            }
            if ('\0' < (char)bVar4) {
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = (int)(char)bVar4;
            }
            bVar3 = (char)bVar4 < '\x01';
            if (DAT_BuildingsState::instance.buildings[buildingID].animationIndex != 0)
                goto LAB_004143b4;
            DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0x1f;
            goto LAB_00414528;
        }
        if (sVar5 == 1 || sVar5 == 3 || sVar5 == 5) {
            if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {
                sVar5 = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                if (!sVar5 || sVar5 == 0xe || sVar5 == 0x1a || sVar5 == 0x29) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                        (int)((short)DAT_BuildingsState::instance.buildings[buildingID].y),
                        DE::SHCDE::FX_TANNER_BRUSH1);
                    buildingID = DAT_CurrentBuildingID::instance;
                }
                sVar5 = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                if (sVar5 == 7 || sVar5 == 0x15 || sVar5 == 0x21 || sVar5 == 0x2f) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                        (int)((short)DAT_BuildingsState::instance.buildings[buildingID].y),
                        DE::SHCDE::FX_TANNER_BRUSH2);
                    buildingID = DAT_CurrentBuildingID::instance;
                }
            }
            iVar7 = buildingID * 0x32c;
            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                if ((char)DAT_BuildingDefinedData::instance
                        .AnimTannerSolitary2[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                    < '\x01')
                    goto LAB_00414530;
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                    = (char)DAT_BuildingDefinedData::instance
                          .AnimTannerSolitary2[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                    + 0xc;
            } else {
                if ((char)DAT_BuildingDefinedData::instance
                        .AnimTanner2[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                    < '\x01')
                    goto LAB_00414530;
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                    = (char)DAT_BuildingDefinedData::instance
                          .AnimTanner2[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                    + 0xc;
            }
        } else {
            if ((sVar5 == 2) || (sVar5 == 4)) {
                if ((char)DAT_BuildingDefinedData::instance
                        .AnimTanner3[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                    < '\x01')
                    goto LAB_00414530;
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                    = (int)(char)DAT_BuildingDefinedData::instance
                          .AnimTanner3[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                goto LAB_00414611;
            }
            if (sVar5 == 6) {
                if ((char)DAT_BuildingDefinedData::instance
                        .AnimTanner4[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                    < '\x01') {
                LAB_00414515:
                    bVar3 = true;
                } else {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                        = (int)(char)DAT_BuildingDefinedData::instance
                              .AnimTanner4[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                }
            LAB_0041451a:
                sVar5 = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
            LAB_00414521:
                *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -0x62) = sVar5;
            } else {
                if (sVar5 != 7) {
                    if (sVar5 == 8) {
                        if ((char)DAT_BuildingDefinedData::instance
                                .AnimTanner5[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                            < '\x01')
                            goto LAB_00414515;
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                            = (char)DAT_BuildingDefinedData::instance
                                  .AnimTanner5[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                            + 0x19;
                    } else {
                        if (sVar5 == 9) {
                            sVar5 = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                                bVar4 = DAT_BuildingDefinedData::instance.AnimTannerSolitary4[sVar5];
                            } else {
                                bVar4 = DAT_BuildingDefinedData::instance.AnimTanner6[sVar5];
                            }
                            if ('\0' < (char)bVar4) {
                                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = (char)bVar4 + 0x33;
                            }
                            bVar3 = (char)bVar4 < '\x01';
                            if (DAT_BuildingsState::instance.buildings[buildingID].animationIndex != 0)
                                goto LAB_004143b4;
                            DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0x1f;
                            goto LAB_00414528;
                        }
                        if (sVar5 != 10)
                            goto LAB_00414611;
                        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                            || (char)DAT_BuildingDefinedData::instance
                                    .AnimTanner7[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                                < '\x01')
                            goto LAB_00414515;
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                            = (char)DAT_BuildingDefinedData::instance
                                  .AnimTanner7[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                            + 0x33;
                    }
                    goto LAB_0041451a;
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0
                    && (((sVar5 = DAT_BuildingsState::instance.buildings[buildingID].animationIndex,
                             sVar5 == 0xf || (sVar5 == 0x18))
                            || (sVar5 == 0x1e))
                        || ((sVar5 == 0x28 || (sVar5 == 0x2e))))) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                        (int)((short)DAT_BuildingsState::instance.buildings[buildingID].y), DE::SHCDE::FX_TANNER_CUT);
                    buildingID = DAT_CurrentBuildingID::instance;
                }
                iVar7 = buildingID * 0x32c;
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    if ((char)DAT_BuildingDefinedData::instance.TannersWorkshopAnimationFrames1
                            [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                        < '\x01') {
                        bVar3 = true;
                    } else {
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                            = (char)DAT_BuildingDefinedData::instance.TannersWorkshopAnimationFrames1
                                  [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                            + 0x19;
                    }
                } else if ((char)DAT_BuildingDefinedData::instance.TannersWorkshopAnimationFrames2
                               [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                    < '\x01') {
                    bVar3 = true;
                } else {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                        = (char)DAT_BuildingDefinedData::instance.TannersWorkshopAnimationFrames2
                              [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                        + 0x19;
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].animationIndex != 0) {
                LAB_004143b4:
                    sVar5 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -0x62);
                    if (sVar5 <= 0)
                        goto LAB_00414528;
                    sVar5 = sVar5 + -1;
                    goto LAB_00414521;
                }
                DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0x1f;
            }
        LAB_00414528:
            if (bVar3) {
            LAB_00414530:
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationIndex + iVar7) = 0;
                sVar5 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8);
                if (!sVar5) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 1;
                } else if (sVar5 == 1) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 2;
                } else if (sVar5 == 2) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 3;
                } else if (sVar5 == 3) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 4;
                } else if (sVar5 == 4) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 5;
                } else if (sVar5 == 5) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 6;
                } else if (sVar5 == 6) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 7;
                } else if (sVar5 == 7) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 8;
                } else if (sVar5 == 8) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 9;
                } else if (sVar5 == 9) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 10;
                } else if (sVar5 == 10) {
                    piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].animationCycleCount + iVar7);
                    *piVar1 = *piVar1 + 1;
                    *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationCycleCompleted + iVar7) = 1;
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -8) = 0;
                }
            }
        }
    LAB_00414611:
        sVar5 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -0x62);
        if (sVar5 < 0x20) {
            if (sVar5 < 0) {
                *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -0x62) = 0;
            }
        } else {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -0x62) = 0x1f;
        }
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + iVar7) = 0;
        iVar6 = (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].workerID + iVar7);
        if (iVar6) {
            UVar2 = DAT_UnitsState::instance.units[iVar6].state.generic;
            if (UVar2 == Map::Units::States::US_FIRE_WEAPONUnk) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar7) = 1;
                goto LAB_0041467c;
            }
            if (UVar2 == Map::Units::States::US_AIM_WEAPONUnk) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar7) = 1;
                goto LAB_0041467c;
            }
        }
        *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar7) = 0;
    LAB_0041467c:
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateVisuallyActiveState, DAT_BuildingsState::ptr)(
            buildingID);
        if (*(short*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar7)
            != *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -0x52)) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
            iVar7 = DAT_CurrentBuildingID::instance * 0x32c;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + iVar7) = 0;
        }
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + iVar7) = 1;
        piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar7);
        *piVar1 = *piVar1 + 1;
        if ((char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar7) / 2]
            < '\x01') {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar7) = 0;
        }
        *(int*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + iVar7)
            = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                  [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar7) / 2];
    }

}
}
