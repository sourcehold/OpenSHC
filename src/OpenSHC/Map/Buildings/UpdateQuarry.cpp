#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using DE::SHCDE::eSFX;
    using Game::GameMode;
    using Game::Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041D510
    void Buildings::UpdateQuarry()
    {
        int* piVar1;
        short sVar2;
        int uVar3;
        int uVar4;
        bool bVar5;
        ushort uVar6;
        int iVar7;
        byte bVar8;
        byte bVar9;
        int buildingID;
        int iVar10;
        byte bVar11;
        bool bVar12;
        eSFX sfxOffsetInArray;
        iVar10 = DAT_CurrentBuildingID::instance;
        uVar6 = (ushort)(byte)SEC_RNG::instance.currentNumber2;
        bVar9 = (byte)SEC_RNG::instance.currentNumber2 & 3;
        buildingID
            = (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].quarryStockpileID;
        piVar1 = &DAT_GameState::instance
                      .playerDataArray[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
                      .countStoneQuarries;
        *piVar1 = *piVar1 + 1;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(iVar10);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar7 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[iVar7].displayOwnerFlag = 1;
        piVar1 = &DAT_BuildingsState::instance.buildings[iVar7].animationTickCounter;
        *piVar1 = *piVar1 + 1;
        iVar10 = DAT_BuildingsState::instance.buildings[iVar7].animationTickCounter;
        if (1 < iVar10) {
            DAT_BuildingsState::instance.buildings[iVar7].animationTickCounter = 0;
        }
        if ((iVar10 == 1) && (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY)) {}
        bVar11 = DAT_BuildingsState::instance.buildings[iVar7].workers[0] != 0;
        sVar2 = DAT_BuildingsState::instance.buildings[iVar7].workers[1];
        if (sVar2) {
            bVar11 = bVar11 + 1;
        }
        if (DAT_BuildingsState::instance.buildings[iVar7].workers[2] != 0) {
            bVar11 = bVar11 + 1;
        }
        if (!sVar2) {
            DAT_BuildingsState::instance.buildings[iVar7].state = 0;
            DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock = 0;
            DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1 = 0;
        } else if (bVar11 < 3) {
            DAT_BuildingsState::instance.buildings[iVar7].state = 0;
            DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock = 0;
            DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1 = 1;
        } else {
            sVar2 = DAT_BuildingsState::instance.buildings[iVar7].state;
            if (!sVar2) {
                DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock = 0;
                DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1 = 1;
            } else {
                if (sVar2 == 1) {
                    piVar1 = &DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock;
                    *piVar1 = *piVar1 + 1;
                    bVar8 = DAT_BuildingDefinedData::instance
                                .QuarryAnimationFrames1[DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock];
                    if ((char)bVar8 <= '\0') {
                        DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock = 0;
                    } else {
                        DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1 = (int)(char)bVar8;
                    }
                    bVar5 = (char)bVar8 < '\x01';
                    if (DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock == 1) {
                        sfxOffsetInArray = DE::SHCDE::FX_PULLER_LOWER;
                        goto LAB_0041d7b3;
                    }
                } else {
                    if (sVar2 == 2) {
                        DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock = 0;
                        DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1 = 0x21;
                        goto LAB_0041d7da;
                    }
                    if (sVar2 == 3) {
                        piVar1 = &DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock;
                        *piVar1 = *piVar1 + 1;
                        bVar8 = DAT_BuildingDefinedData::instance.QuarryAnimationFrames2
                                    [DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock];
                        if ((char)bVar8 <= '\0') {
                            DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock = 0;
                        } else {
                            DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1 = (char)bVar8 + 1;
                        }
                        bVar5 = (char)bVar8 < '\x01';
                        if (DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock == 3) {
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                (int)(short)DAT_BuildingsState::instance.buildings[iVar7].x,
                                (int)((short)DAT_BuildingsState::instance.buildings[iVar7].y),
                                DE::SHCDE::FX_PULLER_STRAIN);
                        }
                        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock
                            == 0x38) {
                            uVar3 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y;
                            uVar4 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x;
                            sfxOffsetInArray = DE::SHCDE::FX_PULLER_IMPACT;
                        LAB_0041d7c3:
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                (int)(short)uVar4, (int)((short)uVar3), sfxOffsetInArray);
                        }
                    } else {
                        if (sVar2 == 4) {
                            DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock = 0;
                            DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1 = 0x12;
                            goto LAB_0041d7da;
                        }
                        if (sVar2 == 5) {
                            piVar1 = &DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock;
                            *piVar1 = *piVar1 + 1;
                            bVar8 = DAT_BuildingDefinedData::instance.QuarryAnimationFrames3
                                        [DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock];
                            if ((char)bVar8 <= '\0') {
                                DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock = 0;
                            } else {
                                DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1 = (char)bVar8 + 1;
                            }
                            bVar5 = (char)bVar8 < '\x01';
                            if (DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock == 1) {
                                sfxOffsetInArray = DE::SHCDE::FX_PULLER_ROCK;
                            LAB_0041d7b3:
                                uVar3 = DAT_BuildingsState::instance.buildings[iVar7].y;
                                uVar4 = DAT_BuildingsState::instance.buildings[iVar7].x;
                                goto LAB_0041d7c3;
                            }
                        } else {
                            if (sVar2 != 6)
                                goto LAB_0041d875;
                            piVar1 = &DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock;
                            *piVar1 = *piVar1 + 1;
                            bVar8 = DAT_BuildingDefinedData::instance.QuarryAnimationFrames4
                                        [DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock];
                            if ((char)bVar8 <= '\0') {
                                DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock = 0;
                            } else {
                                DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1 = (char)bVar8 + 1;
                            }
                            bVar5 = (char)bVar8 < '\x01';
                            if (DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock == 1) {
                                sfxOffsetInArray = DE::SHCDE::FX_PULLER_RETURN;
                                goto LAB_0041d7b3;
                            }
                        }
                    }
                }
                if (!bVar5)
                    goto LAB_0041d875;
            }
        LAB_0041d7da:
            sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state;
            if (!sVar2) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 7) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 1;
                }
            } else if (sVar2 == 1) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 2;
            } else if (sVar2 == 2) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 9) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 3;
                }
            } else if (sVar2 == 3) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 4;
            } else if (sVar2 == 4) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e == 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 5;
                }
            } else if (sVar2 == 5) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 6;
            } else if (sVar2 == 6) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 0;
            }
        }
    LAB_0041d875:
        iVar10 = DAT_CurrentBuildingID::instance;
        iVar7 = DAT_CurrentBuildingID::instance * 0x32c;
        sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a;
        if (!sVar2) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite2 = 0x7a;
        LAB_0041d999:
            sVar2 = DAT_BuildingsState::instance.buildings[iVar10].field117_0x11a;
            if (!sVar2) {
                if (DAT_BuildingsState::instance.buildings[iVar10].killingPitField == 7) {
                    DAT_BuildingsState::instance.buildings[iVar10].field117_0x11a = 1;
                }
            } else if (sVar2 == 1) {
                DAT_BuildingsState::instance.buildings[iVar10].field117_0x11a = 2;
            } else if (sVar2 == 2) {
                if (DAT_BuildingsState::instance.buildings[iVar10].killingPitField == 9) {
                    DAT_BuildingsState::instance.buildings[iVar10].field117_0x11a = 3;
                }
            } else if (sVar2 == 3) {
                DAT_BuildingsState::instance.buildings[iVar10].field117_0x11a = 4;
            } else if (sVar2 == 4) {
                if (DAT_BuildingsState::instance.buildings[iVar10].field119_0x11e == 0) {
                    DAT_BuildingsState::instance.buildings[iVar10].field117_0x11a = 5;
                }
            } else if (sVar2 == 5) {
                DAT_BuildingsState::instance.buildings[iVar10].field117_0x11a = 6;
            } else if (sVar2 == 6) {
                DAT_BuildingsState::instance.buildings[iVar10].field117_0x11a = 0;
            }
        } else if (sVar2 == 1) {
            piVar1 = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1;
            *piVar1 = *piVar1 + 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .QuarryAnimationFrames5[DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame1]
                <= '\0')
                goto LAB_0041d993;
            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite2
                = (char)DAT_BuildingDefinedData::instance
                      .QuarryAnimationFrames5[DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame1]
                + 0x3d;
        } else {
            if (sVar2 == 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite2 = 0x55;
                goto LAB_0041d999;
            }
            if (sVar2 == 3) {
                piVar1 = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1;
                *piVar1 = *piVar1 + 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .QuarryAnimationFrames6[DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame1]
                    <= '\0')
                    goto LAB_0041d993;
                DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite2
                    = (char)DAT_BuildingDefinedData::instance
                          .QuarryAnimationFrames6[DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame1]
                    + 0x53;
            } else {
                if (sVar2 == 4) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                    DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite2 = 0x66;
                    goto LAB_0041d999;
                }
                if (sVar2 == 5) {
                    piVar1
                        = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1;
                    *piVar1 = *piVar1 + 1;
                    if ((char)DAT_BuildingDefinedData::instance.SomeAnimationNumbersUnk
                            [DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame1]
                        <= '\0') {
                    LAB_0041d993:
                        DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame1 = 0;
                        goto LAB_0041d999;
                    }
                    DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite2
                        = (char)DAT_BuildingDefinedData::instance.SomeAnimationNumbersUnk
                              [DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame1]
                        + 0x66;
                } else if (sVar2 == 6) {
                    piVar1
                        = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1;
                    *piVar1 = *piVar1 + 1;
                    if ((char)DAT_BuildingDefinedData::instance
                            .QuarryAnimationFrames7[DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame1]
                        <= '\0')
                        goto LAB_0041d993;
                    DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite2
                        = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames7
                              [DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame1]
                        + 0x6c;
                }
            }
        }
        bVar5 = false;
        if (DAT_BuildingsState::instance.buildings[iVar10].workers[0] == 0) {
            DAT_BuildingsState::instance.buildings[iVar10].killingPitField = 0;
            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 = 0;
            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite3 = 0;
        } else if (bVar11 < 3) {
            DAT_BuildingsState::instance.buildings[iVar10].killingPitField = 0;
            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 = 0;
            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite3 = 0x7b;
        } else {
            sVar2 = DAT_BuildingsState::instance.buildings[iVar10].killingPitField;
            if (!sVar2) {
                piVar1 = &DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2;
                *piVar1 = *piVar1 + 1;
                bVar8
                    = DAT_BuildingDefinedData::instance
                          .QuarryAnimationFrames8[DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2];
                if ((char)bVar8 <= '\0') {
                    DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 = 0;
                    goto LAB_0041ddf4;
                }
            LAB_0041da9f:
                DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite3 = (char)bVar8 + 0x7a;
            } else {
                if (sVar2 == 1) {
                    piVar1 = &DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2;
                    *piVar1 = *piVar1 + 1;
                    if ('\0' < (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames9
                            [DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2]) {
                        DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite3
                            = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames9
                                  [DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2]
                            + 0x7a;
                        goto LAB_0041ded2;
                    }
                    DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 = 0;
                } else if (sVar2 == 2) {
                    piVar1 = &DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2;
                    *piVar1 = *piVar1 + 1;
                    bVar8 = DAT_BuildingDefinedData::instance.QuarryAnimationFrames10
                                [DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2];
                    if ('\0' < (char)bVar8)
                        goto LAB_0041da9f;
                    DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 = 0;
                } else {
                    if (sVar2 == 3) {
                        piVar1 = &DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2;
                        *piVar1 = *piVar1 + 1;
                        if ((char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames11
                                [DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2]
                            <= '\0') {
                            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 = 0;
                            bVar5 = true;
                            bVar12 = false;
                        } else {
                            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite3
                                = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames11
                                      [DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2]
                                + 0x86;
                            bVar12 = DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 == 1;
                        }
                    LAB_0041dcd4:
                        if (bVar12) {
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                (int)*(
                                    short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -0x32),
                                (int)*(
                                    short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar7 + -0x30),
                                DE::SHCDE::FX_PRYER_LEVER);
                        }
                    } else {
                        if (sVar2 == 4) {
                            piVar1 = &DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2;
                            *piVar1 = *piVar1 + 1;
                            bVar8 = DAT_BuildingDefinedData::instance.QuarryAnimationFrames12
                                        [DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2];
                            if ((char)bVar8 <= '\0') {
                                DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 = 0;
                            } else {
                                DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite3
                                    = (char)bVar8 + 0x86;
                            }
                            bVar5 = (char)bVar8 < '\x01';
                            if (DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 == 1) {
                                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                    (int)(short)DAT_BuildingsState::instance.buildings[iVar10].x,
                                    (int)((short)DAT_BuildingsState::instance.buildings[iVar10].y),
                                    DE::SHCDE::FX_PRYER_LEVER);
                            }
                            iVar7 = DAT_CurrentBuildingID::instance * 0x32c;
                            bVar12 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                         .extraAnimationFrame2
                                == 0x17;
                            goto LAB_0041dcd4;
                        }
                        if (sVar2 == 5) {
                            piVar1 = &DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2;
                            *piVar1 = *piVar1 + 1;
                            bVar8 = DAT_BuildingDefinedData::instance.QuarryAnimationFrames13
                                        [DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2];
                            if ((char)bVar8 <= '\0') {
                                DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 = 0;
                            } else {
                                DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite3
                                    = (char)bVar8 + 0x86;
                            }
                            bVar5 = (char)bVar8 < '\x01';
                            if (DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 == 1) {
                                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                    (int)(short)DAT_BuildingsState::instance.buildings[iVar10].x,
                                    (int)((short)DAT_BuildingsState::instance.buildings[iVar10].y),
                                    DE::SHCDE::FX_PRYER_LEVER);
                            }
                            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                    .extraAnimationFrame2
                                == 0x17) {
                                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                    (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                        .x,
                                    (int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                            .y),
                                    DE::SHCDE::FX_PRYER_LEVER);
                            }
                            iVar7 = DAT_CurrentBuildingID::instance * 0x32c;
                            bVar12 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                         .extraAnimationFrame2
                                == 0x2d;
                            goto LAB_0041dcd4;
                        }
                        if (sVar2 == 6) {
                            piVar1 = &DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2;
                            *piVar1 = *piVar1 + 1;
                            bVar8 = DAT_BuildingDefinedData::instance.QuarryAnimationFrames14
                                        [DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2];
                            if ((char)bVar8 <= '\0') {
                                DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 = 0;
                            } else {
                                DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite3
                                    = (char)bVar8 + 0x86;
                            }
                            bVar5 = (char)bVar8 < '\x01';
                            if (DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 == 0x18) {
                                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                    (int)(short)DAT_BuildingsState::instance.buildings[iVar10].x,
                                    (int)((short)DAT_BuildingsState::instance.buildings[iVar10].y),
                                    DE::SHCDE::FX_PRYER_LEVER);
                            }
                            iVar7 = DAT_CurrentBuildingID::instance * 0x32c;
                            bVar12 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                         .extraAnimationFrame2
                                == 0x38;
                            goto LAB_0041dcd4;
                        }
                        if (sVar2 == 7) {
                            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 = 0;
                            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite3 = 0x8d;
                            goto LAB_0041ddf4;
                        }
                        if (sVar2 == 8) {
                            piVar1 = &DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2;
                            *piVar1 = *piVar1 + 1;
                            if ((char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames15
                                    [DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2]
                                <= '\0') {
                                DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 = 0;
                                goto LAB_0041ddf4;
                            }
                            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite3
                                = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames15
                                      [DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2]
                                + 0x8d;
                            goto LAB_0041ded2;
                        }
                        if (sVar2 == 9) {
                            piVar1 = &DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2;
                            *piVar1 = *piVar1 + 1;
                            if ((char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames16
                                    [DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2]
                                <= '\0') {
                                DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 = 0;
                                goto LAB_0041ddf4;
                            }
                            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite3
                                = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames16
                                      [DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2]
                                + 0xa5;
                            goto LAB_0041ded2;
                        }
                        if (sVar2 == 10) {
                            piVar1 = &DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2;
                            *piVar1 = *piVar1 + 1;
                            if ((char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames17
                                    [DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2]
                                <= '\0') {
                                DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 = 0;
                                goto LAB_0041ddf4;
                            }
                            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite3
                                = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames17
                                      [DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2]
                                + 0xb9;
                            goto LAB_0041ded2;
                        }
                        if (sVar2 != 0xb)
                            goto LAB_0041ded2;
                        piVar1 = &DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2;
                        *piVar1 = *piVar1 + 1;
                        bVar5 = 9 < DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2;
                        if (bVar5) {
                            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame2 = 0;
                        }
                        DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite3 = 0xbf;
                    }
                    if (!bVar5)
                        goto LAB_0041ded2;
                }
            LAB_0041ddf4:
                iVar10 = DAT_CurrentBuildingID::instance;
                sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField;
                if (sVar2 < 3) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField
                        = (uVar6 & 3) + 3;
                } else if (sVar2 < 7) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 7;
                } else if (sVar2 < 8) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 2) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 8;
                    }
                } else if (sVar2 < 9) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 9;
                } else if (sVar2 < 10) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 10;
                } else if (sVar2 < 0xb) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 0xb;
                } else if ((sVar2 < 0xc)
                    && (iVar7 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                            DAT_BuildingsState::ptr)(buildingID, DAT_BuildingsState::instance.buildings[buildingID].uid,
                            Game::Resources::RT_STONE),
                        iVar7 < 0x2f)) {
                    if (!bVar9) {
                        DAT_BuildingsState::instance.buildings[iVar10].killingPitField = 0;
                    } else {
                        DAT_BuildingsState::instance.buildings[iVar10].killingPitField = 2 - (ushort)((uVar6 & 3) != 1);
                    }
                }
            }
        }
    LAB_0041ded2:
        iVar10 = DAT_CurrentBuildingID::instance;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[2] == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e = 0;
            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame3 = 0;
            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite4 = 0;
            goto LAB_0041e1d9;
        }
        if (bVar11 < 3) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e = 0;
            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame3 = 0;
            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite4 = 0xc1;
            goto LAB_0041e1d9;
        }
        sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e;
        if (!sVar2) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 = 0;
            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite4 = 0xc1;
        } else if (sVar2 == 1) {
            piVar1 = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3;
            *piVar1 = *piVar1 + 1;
            bVar9 = DAT_BuildingDefinedData::instance
                        .QuarryAnimationFrames18[DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame3];
            if ((char)bVar9 <= '\0') {
                DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame3 = 0;
            } else {
                DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite4 = (char)bVar9 + 0xc1;
            }
            if (DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame3 == 0x2a) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[iVar10].x,
                    (int)((short)DAT_BuildingsState::instance.buildings[iVar10].y), DE::SHCDE::FX_MASON_CHIP);
                iVar10 = DAT_CurrentBuildingID::instance;
            }
            if (DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame3 == 0x34) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[iVar10].x,
                    (int)((short)DAT_BuildingsState::instance.buildings[iVar10].y), DE::SHCDE::FX_MASON_CHIP);
                iVar10 = DAT_CurrentBuildingID::instance;
            }
            if (DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame3 == 0x41) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[iVar10].x,
                    (int)((short)DAT_BuildingsState::instance.buildings[iVar10].y), DE::SHCDE::FX_MASON_CRUMBLE);
                iVar10 = DAT_CurrentBuildingID::instance;
            }
            if (DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame3 == 100) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[iVar10].x,
                    (int)((short)DAT_BuildingsState::instance.buildings[iVar10].y), DE::SHCDE::FX_MASON_CHIP);
                iVar10 = DAT_CurrentBuildingID::instance;
            }
            if (DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame3 == 0x73) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[iVar10].x,
                    (int)((short)DAT_BuildingsState::instance.buildings[iVar10].y), DE::SHCDE::FX_MASON_CRUMBLE);
                iVar10 = DAT_CurrentBuildingID::instance;
            }
            if (DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame3 == 0x8e) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[iVar10].x,
                    (int)((short)DAT_BuildingsState::instance.buildings[iVar10].y), DE::SHCDE::FX_MASON_CHIP);
                iVar10 = DAT_CurrentBuildingID::instance;
            }
            if (DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame3 == 0x96) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[iVar10].x,
                    (int)((short)DAT_BuildingsState::instance.buildings[iVar10].y), DE::SHCDE::FX_MASON_CRUMBLE);
                iVar10 = DAT_CurrentBuildingID::instance;
            }
            if ('\0' < (char)bVar9)
                goto LAB_0041e1d9;
        } else if (sVar2 == 2) {
            piVar1 = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3;
            *piVar1 = *piVar1 + 1;
            bVar9 = DAT_BuildingDefinedData::instance
                        .QuarryAnimationFrames19[DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame3];
            if ('\0' < (char)bVar9) {
            LAB_0041e140:
                DAT_BuildingsState::instance.buildings[iVar10].extraAnimationSprite4 = (char)bVar9 + 0xc1;
                goto LAB_0041e1d9;
            }
            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame3 = 0;
        } else if (sVar2 == 3) {
            piVar1 = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3;
            *piVar1 = *piVar1 + 1;
            bVar9 = DAT_BuildingDefinedData::instance
                        .QuarryAnimationFrames20[DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame3];
            if ('\0' < (char)bVar9)
                goto LAB_0041e140;
            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame3 = 0;
        } else {
            if (sVar2 != 4)
                goto LAB_0041e1d9;
            piVar1 = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3;
            *piVar1 = *piVar1 + 1;
            bVar9 = DAT_BuildingDefinedData::instance
                        .QuarryAnimationFrames21[DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame3];
            if ('\0' < (char)bVar9)
                goto LAB_0041e140;
            DAT_BuildingsState::instance.buildings[iVar10].extraAnimationFrame3 = 0;
        }
        sVar2 = DAT_BuildingsState::instance.buildings[iVar10].field119_0x11e;
        if (!sVar2) {
            if (DAT_BuildingsState::instance.buildings[iVar10].field117_0x11a == 6) {
                DAT_BuildingsState::instance.buildings[iVar10].field119_0x11e = 1;
            }
        } else if (sVar2 < 5) {
            DAT_BuildingsState::instance.buildings[iVar10].field119_0x11e = 0;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::addResourceToStockpile, DAT_BuildingsState::ptr)(
                buildingID, DAT_BuildingsState::instance.buildings[buildingID].uid, Game::Resources::RT_STONE, 1, 0x30,
                1);
            iVar10 = DAT_CurrentBuildingID::instance;
        }
    LAB_0041e1d9:
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[iVar10].overlayImageID = 0;
        }
        piVar1 = &DAT_BuildingsState::instance.buildings[iVar10].flagSlot.ownerFlagFrame;
        *piVar1 = *piVar1 + 1;
        if ((char)DAT_BuildingDefinedData::instance
                .SharedOverlayAnimationFrames[DAT_BuildingsState::instance.buildings[iVar10].flagSlot.ownerFlagFrame
                    / 2]
            <= '\0') {
            DAT_BuildingsState::instance.buildings[iVar10].flagSlot.ownerFlagFrame = 0;
        }
        DAT_BuildingsState::instance.buildings[iVar10].overlayImageID
            = (int)(char)DAT_BuildingDefinedData::instance
                  .SharedOverlayAnimationFrames[DAT_BuildingsState::instance.buildings[iVar10].flagSlot.ownerFlagFrame
                      / 2];
    }

}
}
