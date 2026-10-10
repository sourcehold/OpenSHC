#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using Commands::MappersEnum;
    using Game::GameMode;
    using Game::GameMode2;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00412730
    void Buildings::UpdateArmory()
    {
        short* psVar1;
        int* piVar2;
        short sVar3;
        int buildingID;
        uint uVar4;
        int iVar5;
        char cVar6;
        int _playerID;
        int iVar7;
        int iVar8;
        bool bVar9;
        int local_20;
        int local_1c;
        int local_18;
        int local_14;
        int local_10;
        int local_c;
        int local_8;
        _playerID = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        bVar9 = false;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        if (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_NULL) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].someResourceNumber = 0;
        }
        if ((((!((byte)DAT_GameCore::instance.mapTimeInTicks & 3))
                 && (DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR))
                && (DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT))
            && (DAT_GameState::instance.playerDataArray[_playerID].someCountdown01 == 0)) {
            iVar7 = DAT_GameState::instance.playerDataArray[_playerID].startResources[0x11];
            if ((0 < iVar7)
                && (uVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft,
                        DAT_BuildingsState::ptr)(buildingID, 0x11, _playerID, 1),
                    uVar4 != 0)) {
                bVar9 = true;
                piVar2 = DAT_GameState::instance.playerDataArray[_playerID].currentResources + 0x11;
                *piVar2 = *piVar2 + 1;
                piVar2 = DAT_BuildingsState::instance.buildings[buildingID].resources + 0x11;
                *piVar2 = *piVar2 + 1;
                DAT_GameState::instance.playerDataArray[_playerID].startResources[0x11] = iVar7 + -1;
                DAT_BuildingsState::instance.buildings[buildingID].resourceRelatedCountDown = 100;
            }
            if ((0 < DAT_GameState::instance.playerDataArray[_playerID].startResources[0x12])
                && (uVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft,
                        DAT_BuildingsState::ptr)(buildingID, 0x12, _playerID, 1),
                    uVar4 != 0)) {
                iVar7 = DAT_GameState::instance.playerDataArray[_playerID].startResources[0x12];
                piVar2 = DAT_GameState::instance.playerDataArray[_playerID].currentResources + 0x12;
                *piVar2 = *piVar2 + 1;
                DAT_GameState::instance.playerDataArray[_playerID].startResources[0x12] = iVar7 + -1;
                piVar2 = DAT_BuildingsState::instance.buildings[buildingID].resources + 0x12;
                *piVar2 = *piVar2 + 1;
                DAT_BuildingsState::instance.buildings[buildingID].resourceRelatedCountDown = 100;
                bVar9 = true;
            }
            if ((0 < DAT_GameState::instance.playerDataArray[_playerID].startResources[0x13])
                && (uVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft,
                        DAT_BuildingsState::ptr)(buildingID, 0x13, _playerID, 1),
                    uVar4 != 0)) {
                iVar7 = DAT_GameState::instance.playerDataArray[_playerID].startResources[0x13];
                piVar2 = DAT_GameState::instance.playerDataArray[_playerID].currentResources + 0x13;
                *piVar2 = *piVar2 + 1;
                DAT_GameState::instance.playerDataArray[_playerID].startResources[0x13] = iVar7 + -1;
                piVar2 = DAT_BuildingsState::instance.buildings[buildingID].resources + 0x13;
                *piVar2 = *piVar2 + 1;
                DAT_BuildingsState::instance.buildings[buildingID].resourceRelatedCountDown = 100;
                bVar9 = true;
            }
            if ((0 < DAT_GameState::instance.playerDataArray[_playerID].startResources[0x14])
                && (uVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft,
                        DAT_BuildingsState::ptr)(buildingID, 0x14, _playerID, 1),
                    uVar4 != 0)) {
                iVar7 = DAT_GameState::instance.playerDataArray[_playerID].startResources[0x14];
                piVar2 = DAT_GameState::instance.playerDataArray[_playerID].currentResources + 0x14;
                *piVar2 = *piVar2 + 1;
                DAT_GameState::instance.playerDataArray[_playerID].startResources[0x14] = iVar7 + -1;
                piVar2 = DAT_BuildingsState::instance.buildings[buildingID].resources + 0x14;
                *piVar2 = *piVar2 + 1;
                DAT_BuildingsState::instance.buildings[buildingID].resourceRelatedCountDown = 100;
                bVar9 = true;
            }
            if ((0 < DAT_GameState::instance.playerDataArray[_playerID].startResources[0x15])
                && (uVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft,
                        DAT_BuildingsState::ptr)(buildingID, 0x15, _playerID, 1),
                    uVar4 != 0)) {
                iVar7 = DAT_GameState::instance.playerDataArray[_playerID].startResources[0x15];
                piVar2 = DAT_GameState::instance.playerDataArray[_playerID].currentResources + 0x15;
                *piVar2 = *piVar2 + 1;
                DAT_GameState::instance.playerDataArray[_playerID].startResources[0x15] = iVar7 + -1;
                piVar2 = DAT_BuildingsState::instance.buildings[buildingID].resources + 0x15;
                *piVar2 = *piVar2 + 1;
                DAT_BuildingsState::instance.buildings[buildingID].resourceRelatedCountDown = 100;
                bVar9 = true;
            }
            if ((0 < DAT_GameState::instance.playerDataArray[_playerID].startResources[0x16])
                && (uVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft,
                        DAT_BuildingsState::ptr)(buildingID, 0x16, _playerID, 1),
                    uVar4 != 0)) {
                iVar7 = DAT_GameState::instance.playerDataArray[_playerID].startResources[0x16];
                piVar2 = DAT_GameState::instance.playerDataArray[_playerID].currentResources + 0x16;
                *piVar2 = *piVar2 + 1;
                DAT_GameState::instance.playerDataArray[_playerID].startResources[0x16] = iVar7 + -1;
                piVar2 = DAT_BuildingsState::instance.buildings[buildingID].resources + 0x16;
                *piVar2 = *piVar2 + 1;
                DAT_BuildingsState::instance.buildings[buildingID].resourceRelatedCountDown = 100;
                bVar9 = true;
            }
            if ((0 < DAT_GameState::instance.playerDataArray[_playerID].startResources[0x17])
                && (uVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft,
                        DAT_BuildingsState::ptr)(buildingID, 0x17, _playerID, 1),
                    uVar4 != 0)) {
                iVar7 = DAT_GameState::instance.playerDataArray[_playerID].startResources[0x17];
                piVar2 = DAT_GameState::instance.playerDataArray[_playerID].currentResources + 0x17;
                *piVar2 = *piVar2 + 1;
                DAT_GameState::instance.playerDataArray[_playerID].startResources[0x17] = iVar7 + -1;
                piVar2 = DAT_BuildingsState::instance.buildings[buildingID].resources + 0x17;
                *piVar2 = *piVar2 + 1;
                DAT_BuildingsState::instance.buildings[buildingID].resourceRelatedCountDown = 100;
                bVar9 = true;
            }
            if ((DAT_GameState::instance.playerDataArray[_playerID].startResources[0x18] <= 0)
                || (uVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft,
                        DAT_BuildingsState::ptr)(buildingID, 0x18, _playerID, 1),
                    uVar4 == 0)) {
                if (!bVar9)
                    goto LAB_00412a53;
            } else {
                DAT_GameState::instance.playerDataArray[_playerID].startResources[0x18]
                    = DAT_GameState::instance.playerDataArray[_playerID].startResources[0x18] + -1;
                piVar2 = DAT_BuildingsState::instance.buildings[buildingID].resources + 0x18;
                *piVar2 = *piVar2 + 1;
                DAT_GameState::instance.playerDataArray[_playerID].currentResources[0x18] = 1;
                DAT_BuildingsState::instance.buildings[buildingID].resourceRelatedCountDown = 100;
            }
            MACRO_CALL_MEMBER(
                Map::Buildings::BuildingsState_Func::countPlayerResources, DAT_BuildingsState::ptr)(_playerID);
        }
    LAB_00412a53:
        uVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
            DAT_BuildingsState::ptr)(buildingID);
        if ((int)uVar4 < 10) {
            DAT_GameState::instance.playerDataArray[_playerID].isArmouryAlmostFilledUp = 0;
        }
        sVar3 = DAT_BuildingsState::instance.buildings[buildingID].owner;
        if ((DAT_GameState::instance.mapAndTime.playerTeams[sVar3]
                == DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])
            || ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[sVar3] == -1
                && (DAT_GameSynchronyState::instance.currentAIArray[sVar3] != 0)))) {
            if (DAT_BuildingsState::instance.buildings[buildingID].resourceRelatedCountDown == 0) {
                if (DAT_BuildingsState::instance.isFirstTickInLoop) {
                    DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
                }
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
                psVar1 = &DAT_BuildingsState::instance.buildings[buildingID].resourceRelatedCountDown;
                *psVar1 = *psVar1 + -1;
            }
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateVisuallyActiveState,
                DAT_BuildingsState::ptr)(buildingID);
        }
        bVar9 = DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage1 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage3 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = 0;
        local_20 = DAT_BuildingsState::instance.buildings[buildingID].resources[0x12];
        local_1c = DAT_BuildingsState::instance.buildings[buildingID].resources[0x13];
        local_18 = DAT_BuildingsState::instance.buildings[buildingID].resources[0x14];
        _playerID = DAT_BuildingsState::instance.buildings[buildingID].resources[0x11];
        local_14 = DAT_BuildingsState::instance.buildings[buildingID].resources[0x15];
        local_10 = DAT_BuildingsState::instance.buildings[buildingID].resources[0x16];
        local_8 = DAT_BuildingsState::instance.buildings[buildingID].resources[0x17];
        local_c = DAT_BuildingsState::instance.buildings[buildingID].resources[0x18];
        if (bVar9) {
            DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8 = 0;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
            piVar2 = &DAT_BuildingsState::instance.buildings[buildingID].flagSlot.ownerFlagFrame;
            *piVar2 = *piVar2 + 1;
            if ((char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                    [DAT_BuildingsState::instance.buildings[buildingID].flagSlot.ownerFlagFrame / 2]
                <= '\0') {
                DAT_BuildingsState::instance.buildings[buildingID].flagSlot.ownerFlagFrame = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8
                = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[buildingID].flagSlot.ownerFlagFrame / 2];
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive != 0) {
            iVar7 = 1;
            DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
            for (iVar8 = 0; iVar8 < 4; iVar8++) {
                iVar5 = 0;
                if (0 < _playerID) {
                    iVar5 = _playerID;
                }
                cVar6 = 0 < _playerID;
                if (iVar5 < local_20) {
                    cVar6 = '\x02';
                    iVar5 = local_20;
                }
                if (iVar5 < local_1c) {
                    cVar6 = '\x03';
                    iVar5 = local_1c;
                }
                if (iVar5 < local_18) {
                    cVar6 = '\x04';
                    iVar5 = local_18;
                }
                if (iVar5 < local_14) {
                    cVar6 = '\x05';
                    iVar5 = local_14;
                }
                if (iVar5 < local_10) {
                    cVar6 = '\x06';
                    iVar5 = local_10;
                }
                if (iVar5 < local_c) {
                    cVar6 = '\a';
                    iVar5 = local_c;
                }
                if (iVar5 < local_8) {
                    cVar6 = '\b';
                    iVar5 = local_8;
                } else if (cVar6 == '\0') {
                }
                if (0x10 < iVar5) {
                    iVar5 = 0x10;
                }
                if (cVar6 == '\x01') {
                    _playerID = _playerID - iVar5;
                    iVar7 = iVar5 + 0x20;
                } else if (cVar6 == '\x02') {
                    local_20 = local_20 - iVar5;
                    iVar7 = iVar5 + 0x30;
                } else if (cVar6 == '\x03') {
                    local_1c = local_1c - iVar5;
                    iVar7 = iVar5 + 0x40;
                } else if (cVar6 == '\x04') {
                    local_18 = local_18 - iVar5;
                    iVar7 = iVar5 + 0x50;
                } else if (cVar6 == '\x05') {
                    local_14 = local_14 - iVar5;
                    iVar7 = iVar5 + 0x60;
                } else if (cVar6 == '\x06') {
                    local_10 = local_10 - iVar5;
                    iVar7 = iVar5 + 0x70;
                } else if (cVar6 == '\a') {
                    local_c = local_c - iVar5;
                    iVar7 = iVar5;
                } else if (cVar6 == '\b') {
                    local_8 = local_8 - iVar5;
                    iVar7 = iVar5 + 0x80;
                }
                if (!iVar8) {
                    DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage1 = iVar7;
                } else if (iVar8 == 1) {
                    DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage3 = iVar7;
                } else if (iVar8 == 2) {
                    DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9 = iVar7;
                } else if (iVar8 == 3) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = iVar7;
                }
            }
        }
    }

}
}
