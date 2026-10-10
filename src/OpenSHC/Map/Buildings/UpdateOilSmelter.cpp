#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
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

    using DE::SHCDE::eSFX;
    using Game::GameMode;
    using Map::Units::UnitType;
    using Map::Units::States::UnitState;

    // FUNCTION: STRONGHOLDCRUSADER 0x00415E80
    void Buildings::UpdateOilSmelter()
    {
        int* piVar1;
        byte bVar2;
        short sVar3;
        int iVar4;
        int iVar5;
        int iVar6;
        int iVar7;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar5 = DAT_CurrentBuildingID::instance;
        iVar6 = DAT_CurrentBuildingID::instance * 0x32c;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[iVar5].animationCycleCompleted = 0;
        DAT_BuildingsState::instance.buildings[iVar5].currentEmployeeCount = 0;
        piVar1 = &DAT_BuildingsState::instance.buildings[iVar5].animationTickCounter;
        *piVar1 = *piVar1 + 1;
        if (1 < DAT_BuildingsState::instance.buildings[iVar5].animationTickCounter) {
            DAT_BuildingsState::instance.buildings[iVar5].animationTickCounter = 0;
        }
        DAT_BuildingsState::instance.buildings[iVar5].buildingIsVisuallyActive = 1;
        sVar3 = DAT_BuildingsState::instance.buildings[iVar5].state;
        if (!sVar3) {
            DAT_BuildingsState::instance.buildings[iVar5].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[iVar5].animationFrame = 0;
            DAT_BuildingsState::instance.buildings[iVar5].state = 2;
        } else if (sVar3 == 1) {
            DAT_BuildingsState::instance.buildings[iVar5].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[iVar5].animationFrame = 0;
        } else if (sVar3 == 2) {
            DAT_BuildingsState::instance.buildings[iVar5].spriteOffetX = -0x10;
            DAT_BuildingsState::instance.buildings[iVar5].spriteOffetY = -0x5c;
            DAT_BuildingsState::instance.buildings[iVar5].animationFrame = 1;
            DAT_BuildingsState::instance.buildings[iVar5].renderBlendStrength = 0x1f;
            DAT_BuildingsState::instance.buildings[iVar5].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[iVar5].state = 3;
        } else if (sVar3 == 3) {
            DAT_BuildingsState::instance.buildings[iVar5].spriteOffetX = -0x10;
            DAT_BuildingsState::instance.buildings[iVar5].spriteOffetY = -0x5c;
            if ((char)DAT_BuildingDefinedData::instance
                    .OilSmelterAnimationFrames1[DAT_BuildingsState::instance.buildings[iVar5].animationIndex]
                < 1) {
                DAT_BuildingsState::instance.buildings[iVar5].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[iVar5].state = 4;
            } else {
                DAT_BuildingsState::instance.buildings[iVar5].animationFrame
                    = (char)DAT_BuildingDefinedData::instance
                          .OilSmelterAnimationFrames1[DAT_BuildingsState::instance.buildings[iVar5].animationIndex]
                    + 0x20;
            }
            sVar3 = DAT_BuildingsState::instance.buildings[iVar5].renderBlendStrength;
            if (sVar3 < 1) {
                DAT_BuildingsState::instance.buildings[iVar5].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[iVar5].state = 4;
            } else {
            LAB_004160fb:
                DAT_BuildingsState::instance.buildings[iVar5].renderBlendStrength = sVar3 + -1;
            }
        } else if (sVar3 == 4) {
            DAT_BuildingsState::instance.buildings[iVar5].spriteOffetX = -0x10;
            DAT_BuildingsState::instance.buildings[iVar5].spriteOffetY = -0x5c;
            if ((char)DAT_BuildingDefinedData::instance
                    .OilSmelterAnimationFrames2[DAT_BuildingsState::instance.buildings[iVar5].animationIndex]
                < 1) {
                DAT_BuildingsState::instance.buildings[iVar5].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[iVar5].state = 5;
            } else {
                DAT_BuildingsState::instance.buildings[iVar5].animationFrame
                    = (char)DAT_BuildingDefinedData::instance
                          .OilSmelterAnimationFrames2[DAT_BuildingsState::instance.buildings[iVar5].animationIndex]
                    + 0x20;
            }
            if ((DAT_BuildingsState::instance.buildings[iVar5].animationIndex == 0x1c)
                && (DAT_BuildingsState::instance.buildings[iVar5].animationActive != 0)) {
                DAT_BuildingsState::instance.buildings[iVar5].field117_0x11a = 1;
                DAT_BuildingsState::instance.buildings[iVar5].extraAnimationFrame1 = 0;
                piVar1 = DAT_BuildingsState::instance.buildings[iVar5].resources + 7;
                *piVar1 = *piVar1 + 1;
            }
        } else if (sVar3 == 5) {
            DAT_BuildingsState::instance.buildings[iVar5].spriteOffetX = -0x10;
            DAT_BuildingsState::instance.buildings[iVar5].spriteOffetY = -0x5c;
            if ((char)DAT_BuildingDefinedData::instance
                    .OilSmelterAnimationFrames3[DAT_BuildingsState::instance.buildings[iVar5].animationIndex]
                < 1) {
            LAB_0041622f:
                DAT_BuildingsState::instance.buildings[iVar5].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[iVar5].animationCycleCompleted = 1;
                DAT_BuildingsState::instance.buildings[iVar5].state = 1;
            } else {
                iVar4 = (char)DAT_BuildingDefinedData::instance
                            .OilSmelterAnimationFrames3[DAT_BuildingsState::instance.buildings[iVar5].animationIndex]
                    + 0x20;
            LAB_00416072:
                DAT_BuildingsState::instance.buildings[iVar5].animationFrame = iVar4;
            }
            sVar3 = DAT_BuildingsState::instance.buildings[iVar5].renderBlendStrength;
            if (sVar3 < 0x1f) {
                DAT_BuildingsState::instance.buildings[iVar5].renderBlendStrength = sVar3 + 1;
            } else {
                DAT_BuildingsState::instance.buildings[iVar5].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[iVar5].animationCycleCompleted = 1;
                DAT_BuildingsState::instance.buildings[iVar5].state = 1;
            }
        } else if (sVar3 == 6) {
            DAT_BuildingsState::instance.buildings[iVar5].spriteOffetX = -0x48;
            DAT_BuildingsState::instance.buildings[iVar5].spriteOffetY = -0x54;
            if ((char)DAT_BuildingDefinedData::instance
                    .OilSmelterAnimationFrames4[DAT_BuildingsState::instance.buildings[iVar5].animationIndex]
                < 1) {
                DAT_BuildingsState::instance.buildings[iVar5].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[iVar5].state = 7;
            } else {
                DAT_BuildingsState::instance.buildings[iVar5].animationFrame
                    = (int)(char)DAT_BuildingDefinedData::instance
                          .OilSmelterAnimationFrames4[DAT_BuildingsState::instance.buildings[iVar5].animationIndex];
            }
            sVar3 = DAT_BuildingsState::instance.buildings[iVar5].renderBlendStrength;
            if (0 < sVar3)
                goto LAB_004160fb;
            DAT_BuildingsState::instance.buildings[iVar5].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[iVar5].state = 7;
        } else if (sVar3 == 7) {
            if ((DAT_BuildingsState::instance.buildings[iVar5].animationActive != 0)
                && (DAT_BuildingsState::instance.buildings[iVar5].animationIndex == 10)) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[iVar5].x,
                    (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar5].y)), DE::SHCDE::FX_POT_OPEN);
            }
            if ((DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0)
                && (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 0xd)) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                    (int)((int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y)),
                    DE::SHCDE::FX_OIL_REFILL);
            }
            iVar5 = DAT_CurrentBuildingID::instance;
            iVar6 = DAT_CurrentBuildingID::instance * 0x32c;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -0x48;
            DAT_BuildingsState::instance.buildings[iVar5].spriteOffetY = -0x54;
            if ((char)DAT_BuildingDefinedData::instance
                    .OilSmelterAnimationFrames5[DAT_BuildingsState::instance.buildings[iVar5].animationIndex]
                < 1) {
                DAT_BuildingsState::instance.buildings[iVar5].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[iVar5].state = 8;
                piVar1 = DAT_BuildingsState::instance.buildings[iVar5].resources + 7;
                *piVar1 = *piVar1 + -1;
                iVar5 = DAT_BuildingsState::instance.buildings[iVar5].engineerUnitID;
                if (iVar5 && DAT_UnitsState::instance.units[iVar5].unitType == Map::Units::UT_E_ENGINEER
                    && DAT_UnitsState::instance.units[iVar5].state.generic
                        == (Map::Units::States::US_STAND_UPUnk | Map::Units::States::US_IDLEUnk)) {
                    DAT_UnitsState::instance.units[iVar5].resourceToDeposit = 1;
                }
            } else {
                DAT_BuildingsState::instance.buildings[iVar5].animationFrame
                    = (int)(char)DAT_BuildingDefinedData::instance
                          .OilSmelterAnimationFrames5[DAT_BuildingsState::instance.buildings[iVar5].animationIndex];
            }
        } else if (sVar3 == 8) {
            DAT_BuildingsState::instance.buildings[iVar5].spriteOffetX = -0x48;
            DAT_BuildingsState::instance.buildings[iVar5].spriteOffetY = -0x54;
            iVar4 = (int)(char)DAT_BuildingDefinedData::instance
                        .OilSmelterAnimationFrames6[DAT_BuildingsState::instance.buildings[iVar5].animationIndex];
            if (iVar4 < 1)
                goto LAB_0041622f;
            goto LAB_00416072;
        }
        iVar5 = *(int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar6);
        if (*(int*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar6 + 0x1c) < 1) {
            bVar2 = DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames7[iVar5];
        } else {
            bVar2 = DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames8[iVar5];
        }
        *(int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar6) = iVar5 + 1;
        if ((char)bVar2 < 1) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar6) = 0;
        } else {
            *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar6) = (char)bVar2 + 0x3d;
        }
        if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar6 + -6) == 1) {
            if (*(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) == 1) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar6 + -0x32),
                    (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar6 + -0x30),
                    DE::SHCDE::FX_POT_FLARE_UP);
            }
            iVar4 = DAT_CurrentBuildingID::instance;
            iVar6 = DAT_CurrentBuildingID::instance * 0x32c;
            iVar5 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1;
            bVar2 = DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames10[iVar5];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = iVar5 + 1;
            if ((char)bVar2 < 1) {
                DAT_BuildingsState::instance.buildings[iVar4].extraAnimationFrame1 = 0;
                DAT_BuildingsState::instance.buildings[iVar4].field117_0x11a = 0;
                goto LAB_004164bc;
            }
            iVar7 = (char)bVar2 + 0x7a;
        } else {
            iVar5 = *(int*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar6 + 0x1c);
            if (iVar5 < 1) {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite2 + iVar6) = 0;
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) = 0;
                goto LAB_004164bc;
            }
            if (iVar5 < 2) {
                iVar5 = *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6);
                bVar2 = DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames9[iVar5];
                *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) = iVar5 + 1;
                if ((char)bVar2 < 1) {
                    *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) = 0;
                    goto LAB_004164bc;
                }
                iVar7 = (char)bVar2 + 0x4d;
            } else if (iVar5 < 3) {
                iVar5 = *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6);
                bVar2 = DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames9[iVar5];
                *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) = iVar5 + 1;
                if ((char)bVar2 < 1) {
                    *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) = 0;
                    goto LAB_004164bc;
                }
                iVar7 = (char)bVar2 + 0x52;
            } else if (iVar5 < 4) {
                iVar5 = *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6);
                bVar2 = DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames9[iVar5];
                *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) = iVar5 + 1;
                if ((char)bVar2 < 1) {
                    *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) = 0;
                    goto LAB_004164bc;
                }
                iVar7 = (char)bVar2 + 0x57;
            } else if (iVar5 < 5) {
                iVar5 = *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6);
                bVar2 = DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames9[iVar5];
                *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) = iVar5 + 1;
                if ((char)bVar2 < 1) {
                    *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) = 0;
                    goto LAB_004164bc;
                }
                iVar7 = (char)bVar2 + 0x5c;
            } else if (iVar5 < 6) {
                iVar5 = *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6);
                bVar2 = DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames9[iVar5];
                *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) = iVar5 + 1;
                if ((char)bVar2 < 1) {
                    *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) = 0;
                    goto LAB_004164bc;
                }
                iVar7 = (char)bVar2 + 0x61;
            } else if (iVar5 < 7) {
                iVar5 = *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6);
                bVar2 = DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames9[iVar5];
                *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) = iVar5 + 1;
                if ((char)bVar2 < 1) {
                    *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) = 0;
                    goto LAB_004164bc;
                }
                iVar7 = (char)bVar2 + 0x66;
            } else if (iVar5 < 8) {
                iVar5 = *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6);
                bVar2 = DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames9[iVar5];
                *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) = iVar5 + 1;
                if ((char)bVar2 < 1) {
                    *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) = 0;
                    goto LAB_004164bc;
                }
                iVar7 = (char)bVar2 + 0x6b;
            } else {
                iVar4 = *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6);
                iVar7 = (int)(char)DAT_BuildingDefinedData::instance.OilSmelterAnimationFrames9[iVar4];
                if (iVar5 < 9) {
                    *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) = iVar4 + 1;
                    if (iVar7 < 1) {
                        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6)
                            = 0;
                        goto LAB_004164bc;
                    }
                    iVar7 = iVar7 + 0x70;
                } else {
                    *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6) = iVar4 + 1;
                    if (iVar7 < 1) {
                        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar6)
                            = 0;
                        goto LAB_004164bc;
                    }
                    iVar7 = iVar7 + 0x75;
                }
            }
        }
        *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite2 + iVar6) = iVar7;
    LAB_004164bc:
        if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar6 + -0x52) == -1) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            iVar6 = DAT_CurrentBuildingID::instance * 0x32c;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState = 0;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + iVar6) = 1;
            piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar6);
            *piVar1 = *piVar1 + 1;
            if ((char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                    [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar6) / 2]
                < '\x01') {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar6) = 0;
            }
            *(int*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + iVar6)
                = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar6) / 2];
        }
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + iVar6) = 0;
    }

}
}
