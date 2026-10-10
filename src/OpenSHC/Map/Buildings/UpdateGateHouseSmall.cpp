#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using DE::SHCDE::eSFX;

    // FUNCTION: STRONGHOLDCRUSADER 0x00423CD0
    void Buildings::UpdateGateHouseSmall()
    {
        int iVar4;
        int local_10[4];
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int local_14 = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation;
        MACRO_CALL_MEMBER(
            Map::Buildings::BuildingsState_Func::updateGateDrawBridgeOpenCloseLogic, DAT_BuildingsState::ptr)();
        int iVar2 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].someX
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x + 3;
        DAT_BuildingsState::instance.buildings[iVar2].someY = DAT_BuildingsState::instance.buildings[iVar2].y + 2;
        if ((DAT_TileMapState::instance.mapOrientation == 2) || (DAT_TileMapState::instance.mapOrientation == 6)) {
            local_14 = local_14 + 1;
        }
        if (0x51 < local_14) {
            local_14 = 0x50;
        }
        DAT_BuildingsState::instance.buildings[iVar2].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[iVar2].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[iVar2].extraAnimationSprite1 = 0;
        DAT_BuildingsState::instance.buildings[iVar2].extraAnimationSprite2 = 0;
        DAT_BuildingsState::instance.buildings[iVar2].extraAnimationSprite3 = 0;
        DAT_BuildingsState::instance.buildings[iVar2].extraAnimationSprite4 = 0;
        if (local_14 == 0x50) {
            DAT_BuildingsState::instance.buildings[iVar2].extraAnimationSprite3 = 0xb;
        } else {
            DAT_BuildingsState::instance.buildings[iVar2].extraAnimationSprite4 = 0xc;
        }
        DAT_BuildingsState::instance.buildings[iVar2].damageDecoration[0] = 0;
        DAT_BuildingsState::instance.buildings[iVar2].damageDecoration[1] = 0;
        DAT_BuildingsState::instance.buildings[iVar2].damageDecoration[2] = 0;
        DAT_BuildingsState::instance.buildings[iVar2].damageDecoration[3] = 0;
        DAT_BuildingsState::instance.buildings[iVar2].damageDecoration[4] = 0;
        DAT_BuildingsState::instance.buildings[iVar2].damageDecoration[5] = 0;
        DAT_BuildingsState::instance.buildings[iVar2].damageDecoration[6] = 0;
        local_10[1] = 0;
        DAT_BuildingsState::instance.buildings[iVar2].damageDecoration[7] = 0;
        local_10[0] = 0;
        local_10[2] = 0;
        local_10[3] = 0;
        iVar4 = 5
            - (DAT_BuildingsState::instance.buildings[iVar2].currentHealth * 5)
                / (int)DAT_BuildingsState::instance.buildings[iVar2].maxHealth;
        if (iVar4 < 5) {
            if (!iVar4)
                goto LAB_00423e8d;
        } else {
            iVar4 = 4;
        }
        if (0 < iVar4) {
            uint uVar6 = DAT_BuildingsState::instance.buildings[iVar2].fireRelatedRNG1;
            uint uVar3 = (int)uVar6 >> 8;
            do {
                uint uVar7 = uVar6 & 0xf;
                uint uVar5 = uVar3 & 3;
                uVar6 = uVar6 + 1;
                uVar3 = uVar3 + 1;
                iVar4 = iVar4 + -1;
                local_10[uVar5] = uVar7 + 1;
            } while (iVar4);
        }
        if (local_14 == 0x50) {
            DAT_BuildingsState::instance.buildings[iVar2].damageDecoration[0] = local_10[0];
            DAT_BuildingsState::instance.buildings[iVar2].damageDecoration[1] = local_10[1];
            DAT_BuildingsState::instance.buildings[iVar2].damageDecoration[2] = local_10[2];
            DAT_BuildingsState::instance.buildings[iVar2].damageDecoration[3] = local_10[3];
        } else {
            DAT_BuildingsState::instance.buildings[iVar2].damageDecoration[4] = local_10[0];
            DAT_BuildingsState::instance.buildings[iVar2].damageDecoration[5] = local_10[1];
            DAT_BuildingsState::instance.buildings[iVar2].damageDecoration[6] = local_10[2];
            DAT_BuildingsState::instance.buildings[iVar2].damageDecoration[7] = local_10[3];
        }
    LAB_00423e8d:
        DAT_BuildingsState::instance.buildings[iVar2].extraOverlayImage1 = 0;
        DAT_BuildingsState::instance.buildings[iVar2].extraOverlayImage2 = 0;
        DAT_BuildingsState::instance.buildings[iVar2].animationIncrement = 1;
        DAT_BuildingsState::instance.buildings[iVar2].renderAnimation = 1;
        byte bVar1 = DAT_BuildingsState::instance.buildings[iVar2].pathLinkageRelated2;
        if (!bVar1) {
            if (DAT_BuildingsState::instance.buildings[iVar2].gateState == 10) {
                DAT_BuildingsState::instance.buildings[iVar2].pathLinkageRelated2 = 1;
                DAT_BuildingsState::instance.buildings[iVar2].gateState = 0xc;
                DAT_BuildingsState::instance.buildings[iVar2].animationIndex = 0;
            }
        } else {
            if (bVar1 == 2) {
                if (DAT_BuildingsState::instance.buildings[iVar2].gateState == 0xb) {
                    DAT_BuildingsState::instance.buildings[iVar2].pathLinkageRelated2 = 3;
                    DAT_BuildingsState::instance.buildings[iVar2].gateState = 0xc;
                    DAT_BuildingsState::instance.buildings[iVar2].animationIndex = 0;
                }
                if (local_14 != 0x50) {
                    DAT_BuildingsState::instance.buildings[iVar2].extraOverlayImage2 = 6;
                }
                DAT_BuildingsState::instance.buildings[iVar2].extraOverlayImage1 = 0xc;
            }
            if (bVar1 == 1) {
                if (DAT_BuildingsState::instance.buildings[iVar2].animationActive != 0) {
                    if (DAT_BuildingsState::instance.buildings[iVar2].animationIndex == 1) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[iVar2].x,
                            (int)((short)DAT_BuildingsState::instance.buildings[iVar2].y), DE::SHCDE::FX_PC_DROP);
                    }
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex
                        == 0x14) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                            (int)((
                                int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y)),
                            DE::SHCDE::FX_PC_SLAM);
                    }
                }
                iVar2 = DAT_CurrentBuildingID::instance;
                bVar1 = DAT_BuildingDefinedData::instance.GateHouseOverlayAnimationFrames
                            [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if ('\0' < (char)bVar1) {
                    if (local_14 != 0x50) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage2
                            = (int)(char)bVar1;
                    }
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage1
                        = (char)bVar1 + 6;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 = 2;
                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                    DAT_PathFindingState::ptr)(iVar2);
                if (local_14 != 0x50) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage2 = 6;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage1 = 0xc;
            }
            if (bVar1 == 3) {
                if ((DAT_BuildingsState::instance.buildings[iVar2].animationActive != 0)
                    && (DAT_BuildingsState::instance.buildings[iVar2].animationIndex == 1)) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[iVar2].x,
                        (int)((short)DAT_BuildingsState::instance.buildings[iVar2].y), DE::SHCDE::FX_PC_LIFT);
                }
                iVar2 = DAT_CurrentBuildingID::instance;
                bVar1 = DAT_BuildingDefinedData::instance.GateHouseLargeAnimationFrames
                            [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if ((char)bVar1 <= '\0') {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 = 0;
                    MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                        DAT_PathFindingState::ptr)(iVar2);
                }
                if (local_14 == 0x50) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage1
                        = (char)bVar1 + 6;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage2
                    = (int)(char)bVar1;
            }
        }
    }

}
}
