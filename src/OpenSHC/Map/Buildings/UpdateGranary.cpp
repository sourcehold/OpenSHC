#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using Game::GameMode2;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00415110
    void Buildings::UpdateGranary()
    {
        short* psVar1;
        int* piVar2;
        short sVar3;
        bool bVar4;
        int buildingID;
        uint uVar5;
        int iVar6;
        char cVar7;
        int _playerID;
        int iVar8;
        int iVar9;
        int local_1c;
        int local_18;
        int local_14;
        int local_c;
        int local_8;
        _playerID = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        bVar4 = false;
        local_1c = 0;
        local_8 = 0;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        if (!((byte)DAT_GameCore::instance.mapTimeInTicks & 3) && DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR
            && DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT
            && DAT_GameState::instance.playerDataArray[_playerID].someCountdown01 == 0) {
            iVar8 = DAT_GameState::instance.playerDataArray[_playerID].startResources[10];
            if ((0 < iVar8)
                && (uVar5 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                        DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance),
                    (int)uVar5 < 0xfa)) {
                bVar4 = true;
                piVar2 = DAT_GameState::instance.playerDataArray[_playerID].currentResources + 10;
                *piVar2 = *piVar2 + 1;
                piVar2 = DAT_BuildingsState::instance.buildings[buildingID].resources + 10;
                *piVar2 = *piVar2 + 1;
                DAT_GameState::instance.playerDataArray[_playerID].startResources[10] = iVar8 + -1;
                DAT_BuildingsState::instance.buildings[buildingID].resourceRelatedCountDown = 100;
            }
            iVar8 = DAT_GameState::instance.playerDataArray[_playerID].startResources[0xb];
            if ((0 < iVar8)
                && (uVar5 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                        DAT_BuildingsState::ptr)(buildingID),
                    (int)uVar5 < 0xfa)) {
                DAT_GameState::instance.playerDataArray[_playerID].startResources[0xb] = iVar8 + -1;
                piVar2 = DAT_GameState::instance.playerDataArray[_playerID].currentResources + 0xb;
                *piVar2 = *piVar2 + 1;
                piVar2 = DAT_BuildingsState::instance.buildings[buildingID].resources + 0xb;
                *piVar2 = *piVar2 + 1;
                DAT_BuildingsState::instance.buildings[buildingID].resourceRelatedCountDown = 100;
                bVar4 = true;
            }
            if ((0 < DAT_GameState::instance.playerDataArray[_playerID].startResources[0xc])
                && (uVar5 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                        DAT_BuildingsState::ptr)(buildingID),
                    (int)uVar5 < 0xfa)) {
                iVar8 = DAT_GameState::instance.playerDataArray[_playerID].startResources[0xc];
                piVar2 = DAT_GameState::instance.playerDataArray[_playerID].currentResources + 0xc;
                *piVar2 = *piVar2 + 1;
                DAT_GameState::instance.playerDataArray[_playerID].startResources[0xc] = iVar8 + -1;
                piVar2 = DAT_BuildingsState::instance.buildings[buildingID].resources + 0xc;
                *piVar2 = *piVar2 + 1;
                DAT_BuildingsState::instance.buildings[buildingID].resourceRelatedCountDown = 100;
                bVar4 = true;
            }
            if ((DAT_GameState::instance.playerDataArray[_playerID].startResources[0xd] <= 0)
                || (uVar5 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                        DAT_BuildingsState::ptr)(buildingID),
                    0xf9 < (int)uVar5)) {
                if (!bVar4)
                    goto LAB_004152e5;
            } else {
                iVar8 = DAT_GameState::instance.playerDataArray[_playerID].startResources[0xd];
                piVar2 = DAT_GameState::instance.playerDataArray[_playerID].currentResources + 0xd;
                *piVar2 = *piVar2 + 1;
                DAT_GameState::instance.playerDataArray[_playerID].startResources[0xd] = iVar8 + -1;
                piVar2 = DAT_BuildingsState::instance.buildings[buildingID].resources + 0xd;
                *piVar2 = *piVar2 + 1;
                DAT_BuildingsState::instance.buildings[buildingID].resourceRelatedCountDown = 100;
            }
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::countPlayerResources, DAT_BuildingsState::ptr)(
                _playerID);
        }
    LAB_004152e5:
        uVar5 = MACRO_CALL_MEMBER(
            Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding, DAT_BuildingsState::ptr)(buildingID);
        if ((int)uVar5 < 230) {
            DAT_GameState::instance.playerDataArray[_playerID].granaryIsAlmostFilledUp = FALSE;
        }
        if (DAT_GameState::instance.mapAndTime.playerTeams[_playerID]
                == DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
            || (sVar3 = DAT_BuildingsState::instance.buildings[buildingID].owner,
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[sVar3] == -1
                    && (DAT_GameSynchronyState::instance.currentAIArray[sVar3] != 0))) {
            if (DAT_BuildingsState::instance.buildings[buildingID].resourceRelatedCountDown == 0) {
                if (DAT_BuildingsState::instance.isFirstTickInLoop) {
                    DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
                }
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
                psVar1 = &DAT_BuildingsState::instance.buildings[buildingID].resourceRelatedCountDown;
                *psVar1 = *psVar1 + -1;
            }
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateVisuallyActiveState, DAT_BuildingsState::ptr)(
                buildingID);
        }
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite1 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite3 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage1 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage2 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage3 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage4 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage5 = 0;
        sVar3 = DAT_GameState::instance.playerDataArray[_playerID].isFoodTypeBanned[0];
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10 = 0;
        if ((!sVar3) && (local_8 = DAT_BuildingsState::instance.buildings[buildingID].resources[10], local_8)) {
            local_1c = local_8;
        }
        if (DAT_GameState::instance.playerDataArray[_playerID].isFoodTypeBanned[1] == 0) {
            iVar8 = DAT_BuildingsState::instance.buildings[buildingID].resources[0xb];
            if (iVar8) {
                local_1c = local_1c + iVar8;
            }
        } else {
            iVar8 = 0;
        }
        if (DAT_GameState::instance.playerDataArray[_playerID].isFoodTypeBanned[2] == 0) {
            iVar9 = DAT_BuildingsState::instance.buildings[buildingID].resources[0xc];
            if (iVar9) {
                local_1c = local_1c + iVar9;
            }
        } else {
            iVar9 = 0;
        }
        if (DAT_GameState::instance.playerDataArray[_playerID].isFoodTypeBanned[3] == 0) {
            iVar6 = DAT_BuildingsState::instance.buildings[buildingID].resources[0xd];
            if (iVar6) {
                local_1c = local_1c + iVar6;
            }
        } else {
            iVar6 = 0;
        }
        piVar2 = &DAT_GameState::instance.playerDataArray[_playerID].cheeseCount;
        *piVar2 = *piVar2 + iVar8;
        piVar2 = &DAT_GameState::instance.playerDataArray[_playerID].appleCount;
        *piVar2 = *piVar2 + iVar6;
        piVar2 = &DAT_GameState::instance.playerDataArray[_playerID].breadCount;
        *piVar2 = *piVar2 + local_8;
        piVar2 = &DAT_GameState::instance.playerDataArray[_playerID].meatCount;
        *piVar2 = *piVar2 + iVar9;
        piVar2 = &DAT_GameState::instance.playerDataArray[_playerID].totalFood;
        *piVar2 = *piVar2 + local_1c;
        local_c = DAT_BuildingsState::instance.buildings[buildingID].resources[0xd];
        local_14 = DAT_BuildingsState::instance.buildings[buildingID].resources[0xc];
        local_18 = DAT_BuildingsState::instance.buildings[buildingID].resources[0xb];
        _playerID = DAT_BuildingsState::instance.buildings[buildingID].resources[10];
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
        if ((0 < local_c + local_14 + local_18 + _playerID)
            && (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive != 0)) {
            iVar8 = 1;
            DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
            iVar9 = 0;
            do {
                cVar7 = 0 < _playerID;
                iVar6 = 0;
                if ((bool)cVar7) {
                    iVar6 = _playerID;
                }
                if (iVar6 < local_18) {
                    cVar7 = '\x02';
                    iVar6 = local_18;
                }
                if (iVar6 < local_14) {
                    cVar7 = '\x03';
                    iVar6 = local_14;
                }
                if (iVar6 < local_c) {
                    cVar7 = '\x04';
                    iVar6 = local_c;
                LAB_004155af:
                    if (iVar6 < 9)
                        goto LAB_004155bb;
                    iVar6 = 8;
                LAB_004155ed:
                    local_c = local_c - iVar6;
                    iVar8 = iVar6 + 0x98;
                } else {
                    if (cVar7 == '\0') {}
                    if (cVar7 == '\x01') {
                        if (iVar6 < 0x21)
                            goto LAB_004155bb;
                        _playerID = _playerID + -0x20;
                        iVar8 = 0x20;
                    } else {
                        if (cVar7 == '\x02') {
                            if (0x10 < iVar6) {
                                local_18 = local_18 + -0x10;
                                iVar8 = 0xb0;
                                goto LAB_004155f9;
                            }
                        } else if (cVar7 == '\x03') {
                            if (0x10 < iVar6) {
                                local_14 = local_14 + -0x10;
                                iVar8 = 0xc0;
                                goto LAB_004155f9;
                            }
                        } else if (cVar7 == '\x04')
                            goto LAB_004155af;
                    LAB_004155bb:
                        if (cVar7 == '\x01') {
                            _playerID = _playerID - iVar6;
                            iVar8 = iVar6;
                        } else if (cVar7 == '\x02') {
                            local_18 = local_18 - iVar6;
                            iVar8 = iVar6 + 0xa0;
                        } else if (cVar7 == '\x03') {
                            local_14 = local_14 - iVar6;
                            iVar8 = iVar6 + 0xb0;
                        } else if (cVar7 == '\x04')
                            goto LAB_004155ed;
                    }
                }
            LAB_004155f9:
                if (!iVar9) {
                    DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite1 = iVar8;
                } else if (iVar9 == 1) {
                    DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2 = iVar8;
                } else if (iVar9 == 2) {
                    DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite3 = iVar8;
                } else if (iVar9 == 3) {
                    DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4 = iVar8;
                } else if (iVar9 == 4) {
                    DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage1 = iVar8;
                } else if (iVar9 == 5) {
                    DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage2 = iVar8;
                } else if (iVar9 == 6) {
                    DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage3 = iVar8;
                } else if (iVar9 == 7) {
                    DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage4 = iVar8;
                } else if (iVar9 == 8) {
                    DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage5 = iVar8;
                } else if (iVar9 == 9) {
                    DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6 = iVar8;
                } else if (iVar9 == 10) {
                    DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7 = iVar8;
                } else if (iVar9 == 0xb) {
                    DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8 = iVar8;
                } else if (iVar9 == 0xc) {
                    DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9 = iVar8;
                } else if (iVar9 == 0xd) {
                    DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage = iVar8;
                } else if (iVar9 == 0xe) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = iVar8;
                } else if (iVar9 == 0xf) {
                    DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10 = iVar8;
                }
                iVar9 = iVar9 + 1;
            } while (iVar9 < 0x10);
        }
    }

}
}
