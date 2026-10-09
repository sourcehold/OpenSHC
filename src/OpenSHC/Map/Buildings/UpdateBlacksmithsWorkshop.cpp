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

    // FUNCTION: STRONGHOLDCRUSADER 0x004130D0
    void Buildings::UpdateBlacksmithsWorkshop()
    {
        int* piVar1;
        int sVar2;
        int sVar3;
        ResourceTypeShort RVar4;
        UnitStateShort UVar5;
        int iVar6;
        int iVar7;
        int iVar8;
        bool bVar9;
        sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar7 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field138_0x1c2 = 1;
        sVar3 = DAT_BuildingsState::instance.buildings[iVar7].workers[0];
        piVar1 = &DAT_GameState::instance.playerDataArray[sVar2].countArmorersAndBlacksmiths;
        *piVar1 = *piVar1 + 1;
        DAT_BuildingsState::instance.buildings[iVar7].renderAnimation = (ushort)(sVar3 != 0);
        if ((char)((char)DAT_BuildingsState::instance.buildings[iVar7].uid
                + (char)DAT_GameCore::instance.mapTimeInTicks)
            == '\0') {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingPlacementRotationPreview,
                DAT_TileMapState::ptr)((int)(short)DAT_BuildingsState::instance.buildings[iVar7].x,
                (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar7].y)));
            iVar7 = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation
                = (short)DAT_TileMapState::instance.uiBuildingRotation;
        }
        iVar8 = iVar7 * 0x32c;
        RVar4 = DAT_BuildingsState::instance.buildings[iVar7].producedItemTypeNext;
        if (RVar4 == Game::Resources::RT_SWORD) {
            sVar2 = DAT_BuildingsState::instance.buildings[iVar7].state;
            if (sVar2 == 0) {
                if ((char)DAT_BuildingDefinedData::instance
                        .BlacksmithsWorkshopAnimationFrames3[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                    < '\x01')
                    goto LAB_0041338d;
                DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                    = (char)DAT_BuildingDefinedData::instance
                          .BlacksmithsWorkshopAnimationFrames3[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                    + 0x18;
            } else if (sVar2 == 1) {
            LAB_004131d2:
                if ((DAT_BuildingsState::instance.buildings[iVar7].animationActive != 0)
                    && (((sVar2 = DAT_BuildingsState::instance.buildings[iVar7].animationIndex,
                             sVar2 == 0x18 || (sVar2 == 0x22))
                        || (sVar2 == 0x2c)))) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[iVar7].x,
                        (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar7].y)),
                        DE::SHCDE::FX_BS_ANVIL);
                    iVar7 = DAT_CurrentBuildingID::instance;
                }
                iVar8 = iVar7 * 0x32c;
                if ((char)DAT_BuildingDefinedData::instance
                        .BlacksmithsWorkshopAnimationFrames6[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                    < '\x01') {
                LAB_0041338d:
                    *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationIndex + iVar8) = 0;
                    sVar2 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8);
                    if (sVar2 == 0) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 1;
                    } else if (sVar2 == 1) {
                        *(ushort*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8)
                            = (ushort)(DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                                * 4
                            + 2;
                    } else if (sVar2 == 2) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 3;
                    } else if (sVar2 == 3) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 4;
                    } else if (sVar2 == 4) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 5;
                    } else if (sVar2 == 5) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 6;
                    } else {
                        if (sVar2 != 6) {
                            bVar9 = sVar2 == 7;
                            goto LAB_0041363b;
                        }
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 7;
                    }
                } else {
                    DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                        = (char)DAT_BuildingDefinedData::instance
                              .BlacksmithsWorkshopAnimationFrames6[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        + 0x18;
                }
            } else if (sVar2 == 2) {
                if ((char)DAT_BuildingDefinedData::instance
                        .BlacksmithsWorkshopAnimationFrames4[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                    < '\x01')
                    goto LAB_0041338d;
                DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                    = (char)DAT_BuildingDefinedData::instance
                          .BlacksmithsWorkshopAnimationFrames4[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                    + 0x18;
            } else {
                if (sVar2 == 3)
                    goto LAB_004131d2;
                if (sVar2 == 4) {
                    if ((char)DAT_BuildingDefinedData::instance
                            .BlacksmithsWorkshopAnimationFrames5[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        < '\x01')
                        goto LAB_0041338d;
                    DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                        = (char)DAT_BuildingDefinedData::instance
                              .BlacksmithsWorkshopAnimationFrames5[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        + 0x18;
                    goto LAB_00413651;
                }
                if (sVar2 == 5)
                    goto LAB_004131d2;
                if (sVar2 == 6) {
                    if ((DAT_BuildingsState::instance.buildings[iVar7].animationActive != 0)
                        && (((sVar2 = DAT_BuildingsState::instance.buildings[iVar7].animationIndex,
                                 sVar2 == 0x18 || (sVar2 == 0x22))
                            || (sVar2 == 0x2c)))) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[iVar7].x,
                            (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar7].y)),
                            DE::SHCDE::FX_BS_ANVIL);
                        iVar7 = DAT_CurrentBuildingID::instance;
                    }
                    iVar8 = iVar7 * 0x32c;
                    if ((char)DAT_BuildingDefinedData::instance
                            .BlacksmithsWorkshopAnimationFrames6[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        < '\x01')
                        goto LAB_0041338d;
                    DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                        = (char)DAT_BuildingDefinedData::instance
                              .BlacksmithsWorkshopAnimationFrames6[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        + 0x18;
                } else if (sVar2 == 7) {
                    if ((DAT_BuildingsState::instance.buildings[iVar7].animationActive != 0)
                        && (DAT_BuildingsState::instance.buildings[iVar7].animationIndex == 0x1e)) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[iVar7].x,
                            (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar7].y)),
                            DE::SHCDE::FX_BS_COOL);
                        iVar7 = DAT_CurrentBuildingID::instance;
                    }
                    iVar8 = iVar7 * 0x32c;
                    if ((char)DAT_BuildingDefinedData::instance
                            .BlacksmithsWorkshopAnimationFrames7[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        < '\x01')
                        goto LAB_0041338d;
                    DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                        = (char)DAT_BuildingDefinedData::instance
                              .BlacksmithsWorkshopAnimationFrames7[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        + 0x18;
                }
            }
        } else if (RVar4 == Game::Resources::RT_MACE) {
            sVar2 = DAT_BuildingsState::instance.buildings[iVar7].state;
            if (sVar2 == 0) {
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    if ((char)DAT_BuildingDefinedData::instance
                            .BlacksmithsWorkshopAnimationFrames8[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        < '\x01') {
                    LAB_00413604:
                        *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationIndex + iVar8) = 0;
                        sVar2 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8);
                        if (sVar2 == 0) {
                            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 1;
                        } else if (sVar2 == 1) {
                            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 2;
                        } else {
                            bVar9 = sVar2 == 2;
                        LAB_0041363b:
                            if (bVar9) {
                                piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].animationCycleCount + iVar8);
                                *piVar1 = *piVar1 + 1;
                                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationCycleCompleted + iVar8)
                                    = 1;
                                *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8)
                                    = 0;
                            }
                        }
                    } else {
                        DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                            = (char)DAT_BuildingDefinedData::instance
                                  .BlacksmithsWorkshopAnimationFrames8[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                            + 0x6e;
                    }
                } else {
                    if ((char)DAT_BuildingDefinedData::instance
                            .BlacksmithsWorkshopAnimationFrames11[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        < '\x01')
                        goto LAB_00413604;
                    DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                        = (char)DAT_BuildingDefinedData::instance
                              .BlacksmithsWorkshopAnimationFrames11[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        + 0x6e;
                }
            } else if (sVar2 == 1) {
                if ((DAT_BuildingsState::instance.buildings[iVar7].animationActive != 0)
                    && (DAT_BuildingsState::instance.buildings[iVar7].animationIndex == 0x18)) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[iVar7].x,
                        (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar7].y)),
                        DE::SHCDE::FX_BS_POUR);
                    iVar7 = DAT_CurrentBuildingID::instance;
                }
                if ((DAT_BuildingsState::instance.buildings[iVar7].animationActive != 0)
                    && (DAT_BuildingsState::instance.buildings[iVar7].animationIndex == 0x3c)) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[iVar7].x,
                        (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar7].y)),
                        DE::SHCDE::FX_BS_OPEN);
                    iVar7 = DAT_CurrentBuildingID::instance;
                }
                iVar8 = iVar7 * 0x32c;
                if ((char)DAT_BuildingDefinedData::instance
                        .BlacksmithsWorkshopAnimationFrames9[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                    < '\x01')
                    goto LAB_00413604;
                DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                    = (char)DAT_BuildingDefinedData::instance
                          .BlacksmithsWorkshopAnimationFrames9[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                    + 0x6e;
            } else if (sVar2 == 2) {
                if ((DAT_BuildingsState::instance.buildings[iVar7].animationActive != 0)
                    && ((((sVar2 = DAT_BuildingsState::instance.buildings[iVar7].animationIndex,
                              sVar2 == 5 || (sVar2 == 0x1e))
                             || (sVar2 == 0x37))
                        || ((sVar2 == 0x50 || (sVar2 == 0x6d)))))) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[iVar7].x,
                        (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar7].y)),
                        DE::SHCDE::FX_BS_FILE);
                    iVar7 = DAT_CurrentBuildingID::instance;
                }
                iVar8 = iVar7 * 0x32c;
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    if ((char)DAT_BuildingDefinedData::instance
                            .BlacksmithsWorkshopAnimationFrames10[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        < '\x01')
                        goto LAB_00413604;
                    DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                        = (char)DAT_BuildingDefinedData::instance
                              .BlacksmithsWorkshopAnimationFrames10[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        + 0xaf;
                } else {
                    if ((char)DAT_BuildingDefinedData::instance
                            .BlacksmithsWorkshopAnimationFrames12[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        < '\x01')
                        goto LAB_00413604;
                    DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                        = (char)DAT_BuildingDefinedData::instance
                              .BlacksmithsWorkshopAnimationFrames12[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        + 0xaf;
                }
            }
        }
    LAB_00413651:
        iVar6 = (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].workerID + iVar8);
        if (iVar6 == 0) {
        LAB_0041368b:
            *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar8) = 0;
        } else {
            UVar5 = DAT_UnitsState::instance.units[iVar6].state.generic;
            if (UVar5 == Map::Units::States::US_FIRE_WEAPONUnk) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar8) = 1;
            } else {
                if (UVar5 != Map::Units::States::US_AIM_WEAPONUnk)
                    goto LAB_0041368b;
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar8) = 1;
            }
        }
        sVar2 = *(short*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar8);
        MACRO_CALL_MEMBER(
            Map::Buildings::BuildingsState_Func::updateVisuallyActiveState, DAT_BuildingsState::ptr)(iVar7);
        if (*(short*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar8)
            != *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -0x52)) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                iVar7);
            iVar7 = DAT_CurrentBuildingID::instance;
            iVar8 = DAT_CurrentBuildingID::instance * 0x32c;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + iVar8) = 1;
        if (sVar2 == 0) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar8) = 0;
            goto LAB_00413819;
        }
        if (*(short*)((int)&DAT_BuildingsState::instance.buildings[0].animationActive + iVar8) != 0) {
            piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar8);
            *piVar1 = *piVar1 + 1;
        }
        if (*(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame3 + iVar8) == 0) {
            if ((char)DAT_BuildingDefinedData::instance
                    .BlacksmithsWorkshopAnimationFrames1[*(int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar8)]
                < '\x01') {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar8) = 0;
                sVar2 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8);
                if (sVar2 == 0) {
                    *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame3 + iVar8) = 0;
                    iVar7 = (int)(char)DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames1[*(
                        int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar8)];
                } else {
                    if (sVar2 != 2) {
                        *(uint*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame3 + iVar8)
                            = (uint)(sVar2 != 4);
                        goto LAB_00413771;
                    }
                    *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame3 + iVar8) = 0;
                    iVar7 = (int)(char)DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames1[*(
                        int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar8)];
                }
            } else {
            LAB_00413771:
                iVar7 = (int)(char)DAT_BuildingDefinedData::instance.BlacksmithsWorkshopAnimationFrames1[*(
                    int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar8)];
            }
        } else {
            iVar6 = *(int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar8);
            if ((iVar6 == 0) || (iVar6 == 0x10)) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -0x32),
                    (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -0x30),
                    DE::SHCDE::FX_BS_BELLOW);
                iVar7 = DAT_CurrentBuildingID::instance;
            }
            iVar8 = iVar7 * 0x32c;
            if ((char)DAT_BuildingDefinedData::instance
                    .BlacksmithsWorkshopAnimationFrames2[DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock]
                < '\x01') {
                DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock = 0;
                sVar2 = DAT_BuildingsState::instance.buildings[iVar7].state;
                if (sVar2 == 0) {
                    DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame3 = 0;
                } else if (sVar2 == 2) {
                    DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame3 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame3 = (uint)(sVar2 != 4);
                }
            }
            iVar7 = (int)(char)DAT_BuildingDefinedData::instance
                        .BlacksmithsWorkshopAnimationFrames2[DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock];
        }
        *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar8) = iVar7;
    LAB_00413819:
        piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].animationTickCounter + iVar8);
        *piVar1 = *piVar1 + 1;
        if (3 < *(int*)((int)&DAT_BuildingsState::instance.buildings[0].animationTickCounter + iVar8)) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].animationTickCounter + iVar8) = 0;
        }
        if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].workerID + iVar8) == 0) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite2 + iVar8) = 0;
        } else {
            if (*(int*)((int)&DAT_BuildingsState::instance.buildings[0].animationTickCounter + iVar8) == 0) {
                piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar8);
                *piVar1 = *piVar1 + 1;
            }
            if ((char)DAT_BuildingDefinedData::instance.SecondaryOverlayAnimationFrames[*(
                    int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar8)]
                < '\x01') {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar8) = 0;
            }
            *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite2 + iVar8)
                = (char)DAT_BuildingDefinedData::instance.SecondaryOverlayAnimationFrames[*(
                      int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar8)]
                + 0x10;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
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
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + iVar8) = 0;
    }

}
}
