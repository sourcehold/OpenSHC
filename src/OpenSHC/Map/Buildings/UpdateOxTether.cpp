#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
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
    using Map::Units::UnitType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041CA00
    void Buildings::UpdateOxTether()
    {
        int* piVar1;
        short sVar2;
        short sVar3;
        int iVar4;
        int iVar5;
        int iVar6;
        iVar5 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        iVar6 = DAT_BuildingDefinedData::instance
                    .Building_Sprite_ID_Array_1[(short)DAT_BuildingsState::instance.buildings[iVar5].buildingType]
            + DAT_BuildingsState::instance.buildings[iVar5].resources[4] * 4;
        DAT_BuildingsState::instance.buildings[iVar5].spriteID = iVar6;
        if (iVar6 != DAT_BuildingsState::instance.buildings[iVar5].oldVisualActiveState) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                iVar5);
            iVar5 = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = (short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID;
        }
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(iVar5);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar6 = DAT_CurrentBuildingID::instance;
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID = 0;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
            piVar1 = &DAT_BuildingsState::instance.buildings[iVar6].flagSlot.ownerFlagFrame;
            *piVar1 = *piVar1 + 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .SharedOverlayAnimationFrames[DAT_BuildingsState::instance.buildings[iVar6].flagSlot.ownerFlagFrame
                        / 2]
                <= '\0') {
                DAT_BuildingsState::instance.buildings[iVar6].flagSlot.ownerFlagFrame = 0;
            }
            DAT_BuildingsState::instance.buildings[iVar6].overlayImageID
                = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[iVar6].flagSlot.ownerFlagFrame / 2];
        }
        sVar2 = DAT_BuildingsState::instance.buildings[iVar6].outpostRelatedUnk4;
        if (0 < sVar2) {
            DAT_BuildingsState::instance.buildings[iVar6].outpostRelatedUnk4 = sVar2 + -1;
        }
        sVar2 = DAT_BuildingsState::instance.buildings[iVar6].oxTetherRelatedUnitID;
        if (sVar2 < 1) {
            if ((DAT_BuildingsState::instance.buildings[iVar6].workerID[0] != 0)
                && (piVar1 = &DAT_BuildingsState::instance.buildings[iVar6].animationTickCounter, *piVar1 = *piVar1 + 1,
                    99 < DAT_BuildingsState::instance.buildings[iVar6].animationTickCounter)) {
                DAT_BuildingsState::instance.buildings[iVar6].animationTickCounter = 0;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::setBuildingInitialEntryTileTry,
                    DAT_BuildingsState::ptr)(iVar6, 1);
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea,
                    DAT_BuildingsState::ptr)(iVar6, 1, TRUE);
                sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX;
                iVar6 = DAT_CurrentBuildingID::instance;
                if ((sVar2)
                    && (sVar3 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY,
                        sVar3 != 0)) {
                    iVar5 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                        (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner, 0,
                        (int)((int)(sVar2 * 8)), (int)((int)(sVar3 * 8)),
                        (int)((int)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                .terrainHeightUnk)),
                        Map::Units::UT_QUARRYOX);
                    iVar6 = DAT_CurrentBuildingID::instance;
                    if (iVar5) {
                        DAT_UnitsState::instance.units[iVar5].workplaceBuildingUID
                            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].uid;
                        DAT_UnitsState::instance.units[iVar5].targetX_2
                            = DAT_BuildingsState::instance.buildings[iVar6].buildingEntryX;
                        sVar2 = DAT_BuildingsState::instance.buildings[iVar6].buildingEntryY;
                        DAT_BuildingsState::instance.buildings[iVar6].oxTetherRelatedUnitID = (short)iVar5;
                        iVar4 = DAT_UnitsState::instance.units[iVar5].uid;
                        DAT_UnitsState::instance.units[iVar5].targetY_2 = sVar2;
                        DAT_UnitsState::instance.units[iVar5].workplaceBuildingID_1 = (short)iVar6;
                        DAT_BuildingsState::instance.buildings[iVar6].oxTetherRelatedUnitUID = iVar4;
                    }
                }
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::setBuildingInitialEntryTileTry,
                    DAT_BuildingsState::ptr)(iVar6, 0);
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea,
                    DAT_BuildingsState::ptr)(iVar6, 1, FALSE);
            }
        } else {
            if (DAT_BuildingsState::instance.buildings[iVar6].oxTetherRelatedUnitUID
                != DAT_UnitsState::instance.units[sVar2].uid) {
                DAT_BuildingsState::instance.buildings[iVar6].oxTetherRelatedUnitID = 0;
            }
            if (DAT_UnitsState::instance.units[sVar2].unitType == Map::Units::UT_BURNING_ANIMAL_BIG) {
                DAT_BuildingsState::instance.buildings[iVar6].outpostRelatedUnk4 = 300;
            }
        }
    }

}
}
