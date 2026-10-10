#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Map {

    using DE::SHCDE::eSFX;
    using Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x00410D20
    void Buildings::UpdateWoodcuttersHut()
    {
        int* piVar1;
        byte bVar2;
        short sVar3;
        int iVar4;
        int iVar5;
        int iVar6;
        iVar4 = DAT_CurrentBuildingID::instance;
        sVar3 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation
            = (ushort)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] != 0);
        if (DAT_BuildingsState::instance.buildings[iVar4].currentlyNeededEmployeeCount == 0) {
            piVar1 = &DAT_GameState::instance.playerDataArray[sVar3].noLabourerBuildingCount;
            *piVar1 = *piVar1 + 1;
        } else {
            piVar1 = &DAT_GameState::instance.playerDataArray[sVar3].countWoodcutters;
            *piVar1 = *piVar1 + 1;
        }
        iVar6 = MACRO_CALL_MEMBER(AI::AICState_Func::destroyBuildingIfNoWorker, DAT_AICState::ptr)(iVar4);
        iVar4 = DAT_CurrentBuildingID::instance;
        if (!iVar6) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field242_0x2c8 != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field246_0x2d4 = 0;
            }
            iVar6 = (int)DAT_BuildingsState::instance.buildings[iVar4].field246_0x2d4;
            if (DAT_GameState::instance.playerDataArray[sVar3].someCount10 < iVar6) {
                DAT_GameState::instance.playerDataArray[sVar3].someCount10 = iVar6;
                DAT_GameState::instance.playerDataArray[sVar3].someCount11 = iVar4;
            }
            MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(iVar4);
            MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
                DAT_CurrentBuildingID::instance);
            iVar4 = DAT_CurrentBuildingID::instance;
            if ((char)DAT_BuildingDefinedData::instance.WoodcuttersHutAnimationFrames
                    [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex]
                < '\x01') {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                piVar1 = &DAT_BuildingsState::instance.buildings[iVar4].animationCycleCount;
                *piVar1 = *piVar1 + 1;
                DAT_BuildingsState::instance.buildings[iVar4].animationCycleCompleted = 1;
            }
            bVar2 = DAT_BuildingDefinedData::instance
                        .WoodcuttersHutAnimationFrames[DAT_BuildingsState::instance.buildings[iVar4].animationIndex];
            DAT_BuildingsState::instance.buildings[iVar4].animationFrame = (int)(char)bVar2;
            if ((char)bVar2 == 0x10 && DAT_BuildingsState::instance.buildings[iVar4].animationActive != 0) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[iVar4].x,
                    (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar4].y)), DE::SHCDE::FX_SAW);
            }
            iVar5 = GMTotalPicturesProcessed::instance[0x43];
            iVar6 = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
            iVar4 = DAT_BuildingsState::instance.buildings[iVar6].resources[1];
            if (!iVar4) {
                DAT_BuildingsState::instance.buildings[iVar6].extraAnimationSprite1 = 0;
            } else {
                DAT_BuildingsState::instance.buildings[iVar6].extraAnimationSprite1 = iVar4 + 0x12 + iVar5;
            }
            iVar4 = DAT_BuildingsState::instance.buildings[iVar6].resources[2];
            if (!iVar4) {
                DAT_BuildingsState::instance.buildings[iVar6].extraAnimationSprite2 = 0;
            } else {
                DAT_BuildingsState::instance.buildings[iVar6].extraAnimationSprite2 = iVar4 + 0x15 + iVar5;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                piVar1 = &DAT_BuildingsState::instance.buildings[iVar6].flagSlot.ownerFlagFrame;
                *piVar1 = *piVar1 + 1;
                if ((char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                        [DAT_BuildingsState::instance.buildings[iVar6].flagSlot.ownerFlagFrame / 2]
                    < '\x01') {
                    DAT_BuildingsState::instance.buildings[iVar6].flagSlot.ownerFlagFrame = 0;
                }
                DAT_BuildingsState::instance.buildings[iVar6].overlayImageID
                    = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                          [DAT_BuildingsState::instance.buildings[iVar6].flagSlot.ownerFlagFrame / 2];
            }
            DAT_BuildingsState::instance.buildings[iVar6].overlayImageID = 0;
        }
    }

}
}
