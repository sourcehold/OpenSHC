#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using DE::SHCDE::eSFX;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00417B90
    void Buildings::UpdateDrawBridge()
    {
        undefined2* puVar1;
        byte bVar2;
        short sVar3;
        ushort uVar4;
        ushort uVar5;
        int iVar6;
        BOOLEnum BVar7;
        int iVar8;
        int iVar9;
        eSFX sfxOffsetInArray;
        iVar8 = DAT_CurrentBuildingID::instance;
        sVar3 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        iVar9 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation
            - DAT_TileMapState::instance.mapOrientation;
        if (iVar9 < 0) {
            iVar9 = iVar9 + 8;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 0;
        DAT_BuildingsState::instance.buildings[iVar8].extraAnimationSprite1 = 0;
        DAT_BuildingsState::instance.buildings[iVar8].extraAnimationSprite2 = 0;
        DAT_BuildingsState::instance.buildings[iVar8].extraAnimationSprite3 = 0;
        DAT_BuildingsState::instance.buildings[iVar8].extraAnimationSprite4 = 0;
        DAT_BuildingsState::instance.buildings[iVar8].animationIncrement = 1;
        bVar2 = DAT_BuildingsState::instance.buildings[iVar8].drawBridgeState1;
        if (!bVar2) {
            iVar6 = DAT_BuildingDefinedData::instance.DrawBridgeAnimationFrames[iVar9 / 2];
            DAT_BuildingsState::instance.buildings[iVar8].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[iVar8].animationFrame = iVar6;
            if ((DAT_BuildingsState::instance.buildings[iVar8].drawbridgeState2 == 10)
                && (BVar7 = MACRO_CALL_MEMBER(
                        Map::TileMapState_Func::isUnitBlockingSizeFiveFootprint, DAT_TileMapState::ptr)(iVar8),
                    iVar8 = DAT_CurrentBuildingID::instance, !BVar7)) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawBridgeState1 = 1;
                DAT_BuildingsState::instance.buildings[iVar8].animationIndex = 0;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::floodMoatUnderRemovedBuilding, DAT_TileMapState::ptr)(iVar8);
                iVar8 = DAT_CurrentBuildingID::instance;
                puVar1 = &DAT_GameState::instance.playerDataArray[sVar3].someCount31;
                *puVar1 = *puVar1 + 1;
                DAT_BuildingsState::instance.buildings[iVar8].drawbridgeState2 = 0xc;
            }
            DAT_BuildingsState::instance.buildings[iVar8].displayOwnerFlag = 1;
            if (!iVar9) {
                DAT_BuildingsState::instance.buildings[iVar8].extraAnimationSprite1 = 0x4f;
                goto LAB_00417f35;
            }
            if (iVar9 == 2) {
                DAT_BuildingsState::instance.buildings[iVar8].extraAnimationSprite2 = 0x50;
                goto LAB_00417f5a;
            }
            if (iVar9 == 4) {
                DAT_BuildingsState::instance.buildings[iVar8].extraAnimationSprite3 = 0x4d;
                goto LAB_00417f7f;
            }
            if (iVar9 == 6) {
                DAT_BuildingsState::instance.buildings[iVar8].extraAnimationSprite4 = 0x4e;
                goto LAB_00417fa4;
            }
        } else if (bVar2 == 2) {
            puVar1 = &DAT_GameState::instance.playerDataArray[sVar3].someCount31;
            *puVar1 = *puVar1 + 1;
            iVar6 = DAT_BuildingDefinedData::instance.DrawBridgeAnimationFrames[iVar9 / 2];
            DAT_BuildingsState::instance.buildings[iVar8].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[iVar8].animationFrame = iVar6 + 7;
            if (DAT_BuildingsState::instance.buildings[iVar8].drawbridgeState2 == 0xb) {
                DAT_BuildingsState::instance.buildings[iVar8].drawBridgeState1 = 3;
                DAT_BuildingsState::instance.buildings[iVar8].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[iVar8].drawbridgeState2 = 0xc;
            }
        } else if (bVar2 == 1) {
            puVar1 = &DAT_GameState::instance.playerDataArray[sVar3].someCount31;
            *puVar1 = *puVar1 + 1;
            DAT_BuildingsState::instance.buildings[iVar8].renderAnimation = 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .DrawBridgeAnimationFrames1[DAT_BuildingsState::instance.buildings[iVar8].animationIndex]
                < '\x01') {
                DAT_BuildingsState::instance.buildings[iVar8].drawBridgeState1 = 2;
                DAT_BuildingsState::instance.buildings[iVar8].animationIndex = 0;
            } else {
                DAT_BuildingsState::instance.buildings[iVar8].animationFrame
                    = (int)(char)DAT_BuildingDefinedData::instance
                          .DrawBridgeAnimationFrames1[DAT_BuildingsState::instance.buildings[iVar8].animationIndex]
                    + DAT_BuildingDefinedData::instance.DrawBridgeAnimationFrames[iVar9 / 2];
                if ((DAT_BuildingsState::instance.buildings[iVar8].animationIndex == 1)
                    && (DAT_BuildingsState::instance.buildings[iVar8].animationActive != 0)) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[iVar8].x,
                        (int)((short)DAT_BuildingsState::instance.buildings[iVar8].y),
                        DE::SHCDE::FX_DRAWBRIDGE_RAISING);
                    iVar8 = DAT_CurrentBuildingID::instance;
                }
                if ((DAT_BuildingsState::instance.buildings[iVar8].animationIndex == 0x18)
                    && (DAT_BuildingsState::instance.buildings[iVar8].animationActive != 0)) {
                    uVar4 = DAT_BuildingsState::instance.buildings[iVar8].y;
                    uVar5 = DAT_BuildingsState::instance.buildings[iVar8].x;
                    sfxOffsetInArray = DE::SHCDE::FX_DRAWBRIDGE_RAISED;
                LAB_00417f21:
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)uVar5, (int)((short)uVar4), sfxOffsetInArray);
                    iVar8 = DAT_CurrentBuildingID::instance;
                }
            }
        } else if (bVar2 == 3) {
            puVar1 = &DAT_GameState::instance.playerDataArray[sVar3].someCount31;
            *puVar1 = *puVar1 + 1;
            DAT_BuildingsState::instance.buildings[iVar8].renderAnimation = 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .DrawBridgeAnimationFrames2[DAT_BuildingsState::instance.buildings[iVar8].animationIndex]
                < '\x01') {
                DAT_BuildingsState::instance.buildings[iVar8].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[iVar8].drawBridgeState1 = 0;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::createWaterForDrawBridge, DAT_TileMapState::ptr)(iVar8);
                iVar8 = DAT_CurrentBuildingID::instance;
            } else {
                DAT_BuildingsState::instance.buildings[iVar8].animationFrame
                    = (int)(char)DAT_BuildingDefinedData::instance
                          .DrawBridgeAnimationFrames2[DAT_BuildingsState::instance.buildings[iVar8].animationIndex]
                    + DAT_BuildingDefinedData::instance.DrawBridgeAnimationFrames[iVar9 / 2];
                if ((DAT_BuildingsState::instance.buildings[iVar8].animationIndex == 1)
                    && (DAT_BuildingsState::instance.buildings[iVar8].animationActive != 0)) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[iVar8].x,
                        (int)((short)DAT_BuildingsState::instance.buildings[iVar8].y),
                        DE::SHCDE::FX_DRAWBRIDGE_CONTROL);
                    iVar8 = DAT_CurrentBuildingID::instance;
                }
                if ((DAT_BuildingsState::instance.buildings[iVar8].animationIndex == 5)
                    && (DAT_BuildingsState::instance.buildings[iVar8].animationActive != 0)) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[iVar8].x,
                        (int)((short)DAT_BuildingsState::instance.buildings[iVar8].y),
                        DE::SHCDE::FX_DRAWBRIDGE_LOWERING);
                    iVar8 = DAT_CurrentBuildingID::instance;
                }
                if ((DAT_BuildingsState::instance.buildings[iVar8].animationIndex == 0x1c)
                    && (DAT_BuildingsState::instance.buildings[iVar8].animationActive != 0)) {
                    uVar4 = DAT_BuildingsState::instance.buildings[iVar8].y;
                    uVar5 = DAT_BuildingsState::instance.buildings[iVar8].x;
                    sfxOffsetInArray = DE::SHCDE::FX_DRAWBRIDGE_LOWERED;
                    goto LAB_00417f21;
                }
            }
        }
        if (iVar9) {
            if (iVar9 != 2) {
                if (iVar9 != 4) {
                    if (iVar9 != 6) {}
                LAB_00417fa4:
                    DAT_BuildingsState::instance.buildings[iVar8].spriteOffetX = -0x62;
                    DAT_BuildingsState::instance.buildings[iVar8].spriteOffetY = -0x9c;
                }
            LAB_00417f7f:
                DAT_BuildingsState::instance.buildings[iVar8].spriteOffetX = -0x65;
                DAT_BuildingsState::instance.buildings[iVar8].spriteOffetY = -0x99;
            }
        LAB_00417f5a:
            DAT_BuildingsState::instance.buildings[iVar8].spriteOffetX = -0x57;
            DAT_BuildingsState::instance.buildings[iVar8].spriteOffetY = -0x98;
        }
    LAB_00417f35:
        DAT_BuildingsState::instance.buildings[iVar8].spriteOffetX = -0x59;
        DAT_BuildingsState::instance.buildings[iVar8].spriteOffetY = -0x9a;
    }

}
}
