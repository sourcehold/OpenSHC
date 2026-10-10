#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using Game::GameMode;
    using Map::Units::UnitLogicState;
    using Map::Units::UnitType;
    using Map::Units::States::UnitState;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00416F80
    void Buildings::UpdateMill()
    {
        int* piVar1;
        byte bVar2;
        int sVar3;
        int sVar4;
        int buildingID;
        BOOLEnum BVar5;
        ushort uVar6;
        int iVar7;
        char cVar8;
        bool bVar9;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation
            = (ushort)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] != 0);
        DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
        piVar1 = &DAT_BuildingsState::instance.buildings[buildingID].animationTickCounter;
        *piVar1 = *piVar1 + 1;
        iVar7 = DAT_BuildingsState::instance.buildings[buildingID].animationTickCounter;
        if (1 < iVar7) {
            DAT_BuildingsState::instance.buildings[buildingID].animationTickCounter = 0;
        }
        if (iVar7 == 1) {}
        cVar8 = DAT_BuildingsState::instance.buildings[buildingID].workers[0] != 0;
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[1] != 0) {
            cVar8 = cVar8 + '\x01';
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[2] != 0) {
            cVar8 = cVar8 + '\x01';
        }
        iVar7 = (int)DAT_BuildingsState::instance.buildings[buildingID].unitID;
        if (!iVar7) {
        LAB_00417070:
            if (DAT_BuildingsState::instance.buildings[buildingID].unitID != 0)
                goto LAB_00417079;
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
        } else {
            if (DAT_UnitsState::instance.units[iVar7].logicalState != Map::Units::ULS_NORMAL) {
                DAT_BuildingsState::instance.buildings[buildingID].unitID = 0;
            }
            if (DAT_UnitsState::instance.units[iVar7].unitType != Map::Units::UT_MILLER) {
                DAT_BuildingsState::instance.buildings[buildingID].unitID = 0;
            }
            if (DAT_UnitsState::instance.units[iVar7].state.generic != Map::Units::States::US_AIM_WEAPONUnk) {
                DAT_BuildingsState::instance.buildings[buildingID].unitID = 0;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].unitID == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].killingPitField = 0;
                goto LAB_00417070;
            }
        LAB_00417079:
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
        }
        BVar5 = DAT_BuildingsState::instance.isFirstTickInLoop;
        DAT_BuildingsState::instance.isFirstTickInLoop = TRUE;
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateVisuallyActiveState, DAT_BuildingsState::ptr)(
            buildingID);
        sVar3 = DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive;
        DAT_BuildingsState::instance.isFirstTickInLoop = BVar5;
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
        if (cVar8 == '\0') {
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame3 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4 = 1;
        } else {
            sVar4 = DAT_BuildingsState::instance.buildings[buildingID].outpostRelatedUnk4;
            if (sVar4 < 1) {
                DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame3 = 0;
                DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4 = 1;
            } else {
                uVar6 = sVar4 - 1;
                DAT_BuildingsState::instance.buildings[buildingID].outpostRelatedUnk4 = uVar6;
                if ((short)uVar6 < 0x33) {
                    if ((short)uVar6 < 0x1f) {
                        if ((short)uVar6 < 0x15) {
                            bVar9 = (uVar6 & 7) == 0;
                        } else {
                            bVar9 = (uVar6 & 3) == 0;
                        }
                    } else {
                        bVar9 = (uVar6 & 1) == 0;
                    }
                    if (bVar9)
                        goto LAB_0041713a;
                } else {
                LAB_0041713a:
                    piVar1 = &DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame3;
                    *piVar1 = *piVar1 + 1;
                }
                if ((char)DAT_BuildingDefinedData::instance
                        .MillAnimationFrames1[DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame3]
                    < '\x01') {
                    DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame3 = 0;
                }
                DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4
                    = (int)(char)DAT_BuildingDefinedData::instance.MillAnimationFrames1
                          [DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame3];
            }
        }
        if (cVar8 == '\0' || sVar3
            || (uVar6 = DAT_BuildingsState::instance.buildings[buildingID].outpostRelatedUnk4, !uVar6)) {
            DAT_BuildingsState::instance.buildings[buildingID].campgroundVclock = 0;
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite1 = 0;
        } else {
            if ((short)uVar6 < 0x33) {
                if ((short)uVar6 < 0x1f) {
                    if ((short)uVar6 < 0x15) {
                        bVar9 = (uVar6 & 7) == 0;
                    } else {
                        bVar9 = (uVar6 & 3) == 0;
                    }
                } else {
                    bVar9 = (uVar6 & 1) == 0;
                }
                if (bVar9)
                    goto LAB_004171bf;
            } else {
            LAB_004171bf:
                piVar1 = &DAT_BuildingsState::instance.buildings[buildingID].campgroundVclock;
                *piVar1 = *piVar1 + 1;
            }
            bVar2 = DAT_BuildingDefinedData::instance
                        .MillAnimationFrames2[DAT_BuildingsState::instance.buildings[buildingID].campgroundVclock];
            if ((char)bVar2 < '\x01') {
                DAT_BuildingsState::instance.buildings[buildingID].campgroundVclock = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite1
                = (char)DAT_BuildingDefinedData::instance
                      .MillAnimationFrames2[DAT_BuildingsState::instance.buildings[buildingID].campgroundVclock]
                + 0xf;
            if ((char)bVar2 < '\x01') {
                DAT_BuildingsState::instance.buildings[buildingID].killingPitField = 0;
            }
        }
        if ((cVar8 == '\0') || (!sVar3)) {
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame1 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2 = 0;
        } else {
            piVar1 = &DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame1;
            *piVar1 = *piVar1 + 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .MillAnimationFrames3[DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame1]
                < '\x01') {
                DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame1 = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2
                = (char)DAT_BuildingDefinedData::instance
                      .MillAnimationFrames3[DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame1]
                + 0x1e;
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2
                = (char)DAT_BuildingDefinedData::instance
                      .MillAnimationFrames1[DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame3]
                + 0x1e;
        }
        if ((cVar8 == '\0') || (DAT_BuildingsState::instance.buildings[buildingID].unitID == 0)) {
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame2 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite3 = 0;
            if (DAT_BuildingsState::instance.buildings[buildingID].outpostRelatedUnk4 == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].killingPitField = 0;
            }
            goto LAB_00417366;
        }
        sVar3 = DAT_BuildingsState::instance.buildings[buildingID].killingPitField;
        if (!sVar3) {
        LAB_00417289:
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame2 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite3 = 0x2e;
        } else {
            if (sVar3 == 1) {
                piVar1 = &DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame2;
                *piVar1 = *piVar1 + 1;
                bVar2 = DAT_BuildingDefinedData::instance.MillAnimationFrames4
                            [DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame2];
                if ((char)bVar2 < '\x01') {
                    DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame2 = 0;
                }
                iVar7
                    = (char)DAT_BuildingDefinedData::instance
                          .MillAnimationFrames4[DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame2]
                    + 0x2d;
            } else {
                if (sVar3 != 2) {
                    if (sVar3 != 3)
                        goto LAB_00417366;
                    goto LAB_00417289;
                }
                piVar1 = &DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame2;
                *piVar1 = *piVar1 + 1;
                bVar2 = DAT_BuildingDefinedData::instance.MillAnimationFrames5
                            [DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame2];
                if ((char)bVar2 < '\x01') {
                    DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame2 = 0;
                }
                iVar7
                    = (char)DAT_BuildingDefinedData::instance
                          .MillAnimationFrames5[DAT_BuildingsState::instance.buildings[buildingID].extraAnimationFrame2]
                    + 0x3d;
            }
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite3 = iVar7;
            if ('\0' < (char)bVar2)
                goto LAB_00417366;
        }
        sVar3 = DAT_BuildingsState::instance.buildings[buildingID].killingPitField;
        if (!sVar3) {
            DAT_BuildingsState::instance.buildings[buildingID].killingPitField = 1;
        } else if (sVar3 == 1 || sVar3 == 2 || sVar3 == 3) {
            DAT_BuildingsState::instance.buildings[buildingID].killingPitField = 3;
        }
    LAB_00417366:
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = 0;
        }
        DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
        piVar1 = &DAT_BuildingsState::instance.buildings[buildingID].flagSlot.ownerFlagFrame;
        *piVar1 = *piVar1 + 1;
        if ((char)DAT_BuildingDefinedData::instance
                .SharedOverlayAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].flagSlot.ownerFlagFrame
                    / 2]
            < '\x01') {
            DAT_BuildingsState::instance.buildings[buildingID].flagSlot.ownerFlagFrame = 0;
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayImageID
            = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                  [DAT_BuildingsState::instance.buildings[buildingID].flagSlot.ownerFlagFrame / 2];
    }

}
}
