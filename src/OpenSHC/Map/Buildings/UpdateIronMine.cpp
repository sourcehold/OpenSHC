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

namespace OpenSHC {
namespace Map {

    using DE::SHCDE::eSFX;
    using Game::GameMode;
    using Game::Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041CC70
    void Buildings::UpdateIronMine()
    {
        int* piVar1;
        byte bVar2;
        short sVar3;
        int iVar4;
        int iVar5;
        bool bVar6;
        bool bVar7;
        int iVar8;
        iVar4 = DAT_CurrentBuildingID::instance;
        piVar1 = &DAT_GameState::instance
                      .playerDataArray[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
                      .countIronMines;
        *piVar1 = *piVar1 + 1;
        DAT_BuildingsState::instance.buildings[iVar4].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[iVar4].displayOwnerFlag = 1;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(iVar4);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar4 = DAT_CurrentBuildingID::instance;
        iVar5 = DAT_CurrentBuildingID::instance * 0x32c;
        piVar1 = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter;
        *piVar1 = *piVar1 + 1;
        if (DAT_BuildingsState::instance.buildings[iVar4].animationTickCounter < 2) {}
        DAT_BuildingsState::instance.buildings[iVar4].animationTickCounter = 0;
        if (DAT_BuildingsState::instance.buildings[iVar4].workers[0] == 0) {
            DAT_BuildingsState::instance.buildings[iVar4].state = 0;
            DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock = 0;
            DAT_BuildingsState::instance.buildings[iVar4].extraAnimationSprite1 = 0;
        } else {
            sVar3 = DAT_BuildingsState::instance.buildings[iVar4].state;
            if (!sVar3) {
                piVar1 = &DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock;
                *piVar1 = *piVar1 + 1;
                bVar7 = (char)DAT_BuildingDefinedData::instance
                            .IronMineAnimationFrames1[DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock]
                    < '\0';
                bVar6 = DAT_BuildingDefinedData::instance
                            .IronMineAnimationFrames1[DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock]
                    == 0;
            LAB_0041ce0a:
                if (bVar6 || bVar7) {
                LAB_0041ce10:
                    *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar5) = 0;
                    sVar3 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -8);
                    if (!sVar3) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -8) = 1;
                    } else if (sVar3 == 1) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -8) = 2;
                    } else if (sVar3 == 2) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -8) = 3;
                    } else if (sVar3 == 3) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -8) = 4;
                    } else if (sVar3 == 4) {
                        if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -6) == 1) {
                            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -8) = 5;
                        }
                    } else {
                        if (sVar3 == 5) {
                            iVar8 = *(int*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -0x48);
                        } else {
                            if (sVar3 != 6)
                                goto LAB_0041ceb6;
                            iVar8 = *(int*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -0x48);
                        }
                        iVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                            DAT_BuildingsState::ptr)(iVar4, iVar8, Game::Resources::RT_IRON);
                        *(ushort*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -8)
                            = (iVar4 < 7) - 1 & 6;
                    }
                }
            } else {
                if (sVar3 == 1) {
                    piVar1 = &DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock;
                    *piVar1 = *piVar1 + 1;
                    bVar7
                        = (char)DAT_BuildingDefinedData::instance
                              .IronMineAnimationFrames3[DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock]
                        < '\0';
                    bVar6
                        = DAT_BuildingDefinedData::instance
                              .IronMineAnimationFrames3[DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock]
                        == 0;
                    goto LAB_0041ce0a;
                }
                if (sVar3 == 2) {
                    piVar1 = &DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock;
                    *piVar1 = *piVar1 + 1;
                    bVar7
                        = (char)DAT_BuildingDefinedData::instance
                              .IronMineAnimationFrames2[DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock]
                        < '\0';
                    bVar6
                        = DAT_BuildingDefinedData::instance
                              .IronMineAnimationFrames2[DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock]
                        == 0;
                    goto LAB_0041ce0a;
                }
                if (sVar3 == 3) {
                    iVar5 = DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock;
                    if (!iVar5 || iVar5 == 0x18 || iVar5 == 0x30 || iVar5 == 0x48) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[iVar4].x,
                            (int)((short)DAT_BuildingsState::instance.buildings[iVar4].y), DE::SHCDE::FX_IRON_PULL);
                        iVar4 = DAT_CurrentBuildingID::instance;
                    }
                    iVar5 = iVar4 * 0x32c;
                    piVar1 = &DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock;
                    *piVar1 = *piVar1 + 1;
                    bVar7
                        = (char)DAT_BuildingDefinedData::instance
                              .IronMineAnimationFrames4[DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock]
                        < '\0';
                    bVar6
                        = DAT_BuildingDefinedData::instance
                              .IronMineAnimationFrames4[DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock]
                        == 0;
                    goto LAB_0041ce0a;
                }
                if (sVar3 == 4)
                    goto LAB_0041ce10;
                if (sVar3 == 5) {
                    piVar1 = &DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock;
                    *piVar1 = *piVar1 + 1;
                    bVar7
                        = (char)DAT_BuildingDefinedData::instance
                              .IronMineAnimationFrames5[DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock]
                        < '\0';
                    bVar6
                        = DAT_BuildingDefinedData::instance
                              .IronMineAnimationFrames5[DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock]
                        == 0;
                    goto LAB_0041ce0a;
                }
                if (sVar3 == 6) {
                    piVar1 = &DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock;
                    *piVar1 = *piVar1 + 1;
                    bVar7
                        = (char)DAT_BuildingDefinedData::instance
                              .IronMineAnimationFrames6[DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock]
                        < '\0';
                    bVar6
                        = DAT_BuildingDefinedData::instance
                              .IronMineAnimationFrames6[DAT_BuildingsState::instance.buildings[iVar4].campgroundVclock]
                        == 0;
                    goto LAB_0041ce0a;
                }
            }
        LAB_0041ceb6:
            sVar3 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -8);
            if (!sVar3) {
                *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar5)
                    = (int)(char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames1[*(
                        int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar5)];
            } else if (sVar3 == 1) {
                *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar5)
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames3[*(
                          int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar5)]
                    + 0x76;
            } else if (sVar3 == 2) {
                iVar4 = (int)(char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames2[*(
                    int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar5)];
            LAB_0041cf6f:
                *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar5) = iVar4;
            } else if (sVar3 == 3) {
                *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar5)
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames4[*(
                          int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar5)]
                    + 0x26;
            } else if (sVar3 == 4) {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar5) = 0x3b;
            } else if (sVar3 == 5) {
                *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar5)
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames5[*(
                          int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar5)]
                    + 0x3a;
            } else if (sVar3 == 6) {
                iVar4 = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames6[*(
                            int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar5)]
                    + 0x4e;
                goto LAB_0041cf6f;
            }
        }
        if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].workers + iVar5) == 0) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -4) = 0;
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame2 + iVar5) = 0;
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite3 + iVar5) = 0;
        } else {
            sVar3 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -4);
            if (!sVar3) {
            LAB_0041cfdc:
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame2 + iVar5) = 0;
                sVar3 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -4);
                if (!sVar3) {
                    if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -8) == 3
                        && *(int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar5) == 0x50) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -4) = 1;
                    }
                } else if (sVar3 == 1) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -4) = 2;
                } else if (sVar3 == 2) {
                    if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -8) == 0) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -4) = 3;
                    }
                } else if (sVar3 == 3) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -4) = 0;
                }
            } else if (sVar3 == 1) {
                piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame2 + iVar5);
                *piVar1 = *piVar1 + 1;
                bVar2 = DAT_BuildingDefinedData::instance.IronMineAnimationFrames7[*(
                    int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame2 + iVar5)];
            LAB_0041cfda:
                if ((char)bVar2 <= '\0')
                    goto LAB_0041cfdc;
            } else {
                if (sVar3 == 2)
                    goto LAB_0041cfdc;
                if (sVar3 == 3) {
                    piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame2 + iVar5);
                    *piVar1 = *piVar1 + 1;
                    bVar2 = DAT_BuildingDefinedData::instance.IronMineAnimationFrames8[*(
                        int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame2 + iVar5)];
                    goto LAB_0041cfda;
                }
            }
            sVar3 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -4);
            if (!sVar3) {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite3 + iVar5) = 0;
            } else if (sVar3 == 1) {
                *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite3 + iVar5)
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames7[*(
                          int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame2 + iVar5)]
                    + 0x32;
            } else if (sVar3 == 2) {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite3 + iVar5) = 0;
            } else if (sVar3 == 3) {
                *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite3 + iVar5)
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames8[*(
                          int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame2 + iVar5)]
                    + 0x32;
            }
        }
        if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].workers + iVar5) == 0) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -6) = 0;
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar5) = 0;
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite2 + iVar5) = 0;
        } else {
            sVar3 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -6);
            if (!sVar3) {
                piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar5);
                *piVar1 = *piVar1 + 1;
                bVar7 = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames9[*(
                            int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar5)]
                    < '\0';
                bVar6 = DAT_BuildingDefinedData::instance.IronMineAnimationFrames9[*(
                            int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar5)]
                    == 0;
            LAB_0041d1f7:
                if (bVar6 || bVar7) {
                    *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar5) = 0;
                    sVar3 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -6);
                    if (!sVar3) {
                        if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -8) == 4) {
                            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -6) = 1;
                        }
                    } else if (sVar3 == 1) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -6) = 2;
                    } else if (sVar3 == 2) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -6) = 0;
                    }
                }
            } else {
                if (sVar3 == 1) {
                    if (*(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar5) == 0x14) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -0x32),
                            (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -0x30),
                            DE::SHCDE::FX_IRON_STRAIN);
                    }
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1
                        == 0x37) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                            (int)((
                                int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y)),
                            DE::SHCDE::FX_IRON_DUMP);
                    }
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1
                        == 0x41) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                            (int)((
                                int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y)),
                            DE::SHCDE::FX_IRON_LDUMP);
                    }
                    iVar4
                        = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1;
                    if (iVar4 == 100 || iVar4 == 0xbe || iVar4 == 0x118 || iVar4 == 0x172) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                            (int)((
                                int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y)),
                            DE::SHCDE::FX_IRON_BOIL);
                    }
                    iVar4 = DAT_CurrentBuildingID::instance;
                    iVar5 = DAT_CurrentBuildingID::instance * 0x32c;
                    piVar1
                        = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1;
                    *piVar1 = *piVar1 + 1;
                    bVar7 = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames10
                                [DAT_BuildingsState::instance.buildings[iVar4].extraAnimationFrame1]
                        < '\0';
                    bVar6 = DAT_BuildingDefinedData::instance.IronMineAnimationFrames10
                                [DAT_BuildingsState::instance.buildings[iVar4].extraAnimationFrame1]
                        == 0;
                    goto LAB_0041d1f7;
                }
                if (sVar3 == 2) {
                    piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar5);
                    *piVar1 = *piVar1 + 1;
                    bVar7 = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames11[*(
                                int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar5)]
                        < '\0';
                    bVar6 = DAT_BuildingDefinedData::instance.IronMineAnimationFrames11[*(
                                int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar5)]
                        == 0;
                    goto LAB_0041d1f7;
                }
            }
            sVar3 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -6);
            if (!sVar3) {
                *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite2 + iVar5)
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames9[*(
                          int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar5)]
                    + 0x7e;
            } else if (sVar3 == 1) {
                *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite2 + iVar5)
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames10[*(
                          int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar5)]
                    + 0x86;
            } else if (sVar3 == 2) {
                *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite2 + iVar5)
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames11[*(
                          int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar5)]
                    + 0x86;
            }
            sVar3 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -6);
            if (sVar3 == 1) {
                bVar2 = DAT_BuildingDefinedData::instance.IronMineAnimationFrames10[*(
                    int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar5)];
                if ((char)bVar2 < '\x04') {
                    *(undefined1*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar5 + -0x38)
                        = 0x18;
                } else if ((char)bVar2 < '\b') {
                    *(undefined1*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar5 + -0x38)
                        = 0x14;
                } else if ((char)bVar2 < '\f') {
                    *(undefined1*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar5 + -0x38)
                        = 0x10;
                } else if ((char)bVar2 < '\x10') {
                    *(undefined1*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar5 + -0x38)
                        = 0xc;
                } else if ((char)bVar2 < '\x14') {
                    *(undefined1*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar5 + -0x38)
                        = 0x10;
                } else {
                    *(char*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar5 + -0x38)
                        = ('\x17' < (char)bVar2) * '\x04' + '\x14';
                }
            } else if (sVar3 == 2) {
                bVar2 = DAT_BuildingDefinedData::instance.IronMineAnimationFrames11[*(
                    int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame1 + iVar5)];
                if ((char)bVar2 < '\x04') {
                    *(undefined1*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar5 + -0x38)
                        = 0x18;
                } else if ((char)bVar2 < '\b') {
                    *(undefined1*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar5 + -0x38)
                        = 0x14;
                } else if ((char)bVar2 < '\f') {
                    *(undefined1*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar5 + -0x38)
                        = 0x10;
                } else if ((char)bVar2 < '\x10') {
                    *(undefined1*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar5 + -0x38)
                        = 0xc;
                } else if ((char)bVar2 < '\x14') {
                    *(undefined1*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar5 + -0x38)
                        = 0x10;
                } else {
                    *(char*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar5 + -0x38)
                        = ('\x17' < (char)bVar2) * '\x04' + '\x14';
                }
            }
        }
        if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].workers + iVar5) == 0) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -2) = 0;
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame3 + iVar5) = 0;
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite4 + iVar5) = 0;
            goto LAB_0041d47e;
        }
        sVar3 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -2);
        if (!sVar3) {
        LAB_0041d3f4:
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame3 + iVar5) = 0;
            iVar4 = DAT_CurrentBuildingID::instance;
            sVar3 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -2);
            if (!sVar3) {
                if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -6) == 2) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -2) = 1;
                }
            } else if (sVar3 == 1) {
                *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -2) = 0;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::addResourceToStockpile, DAT_BuildingsState::ptr)(
                    iVar4, *(int*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -0x48),
                    Game::Resources::RT_IRON, 1, 8, 1);
            }
        } else if (sVar3 == 1) {
            if (*(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationFrame3 + iVar5) == 0) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -0x32),
                    (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + -0x30),
                    DE::SHCDE::FX_IRON_POUR);
            }
            iVar4 = DAT_CurrentBuildingID::instance;
            iVar5 = DAT_CurrentBuildingID::instance * 0x32c;
            piVar1 = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3;
            *piVar1 = *piVar1 + 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .IronMineAnimationFrames12[DAT_BuildingsState::instance.buildings[iVar4].extraAnimationFrame3]
                <= '\0')
                goto LAB_0041d3f4;
        }
        iVar5 = DAT_CurrentBuildingID::instance * 0x32c;
        sVar3 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e;
        if (!sVar3) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 0;
        } else if (sVar3 == 1) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4
                = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames12
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3]
                + 0x5e;
        }
    LAB_0041d47e:
        iVar4 = *(int*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar5 + 0x18);
        if (iVar4 <= 0) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraOverlayImage1 + iVar5) = 0;
        } else if (iVar4 < 8) {
            *(int*)((int)&DAT_BuildingsState::instance.buildings[0].extraOverlayImage1 + iVar5) = iVar4 + 0xa2;
        } else {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraOverlayImage1 + iVar5) = 0xaa;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + iVar5) = 0;
        }
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + iVar5) = 1;
        piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar5);
        *piVar1 = *piVar1 + 1;
        if ((char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar5) / 2]
            <= '\0') {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar5) = 0;
        }
        *(int*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + iVar5)
            = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                  [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar5) / 2];
    }

}
}
