#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          maybe fromArea is the third argument, and toArea is the second?   decompilerscript: committed: 2025-01-30
          21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A5320
        int PathFindingState::calculateCanPlayerUnitsNavigateToAreaFromArea(
            int playerID, dword fromArea, dword toArea, int permitClimb)
        {
            int iVar1;
            dword dVar2;
            dword dVar3;
            dword dVar4;
            ClimbData* piVar7;
            int iVar7;
            bool bVar8;
            int local_96c;
            int local_968;
            dword adStack_960[200];
            int aiStack_640[400];
            if (fromArea != toArea) {
                int iVar5 = 0;
                if ((toArea == 0) || (fromArea == 0)) {
                    return 0;
                }
                iVar7 = 1;
                this->DAT_Test_likely = this->DAT_Test_likely + 1;
                local_96c = 0;
                local_968 = 0;
                if (1 < this->maxClimbDataCount) {
                    piVar7 = &this->climbData[1];
                    do {
                        if ((piVar7->canBeUsed == 1) && (piVar7->isRecognizedByPathfinding != 0)) {
                            if (piVar7->type == 1) {
                                bVar8 = permitClimb == 0;
                            } else {
                                bVar8 = permitClimb == 2;
                            }
                            if (!bVar8
                                && ((playerID == 0
                                        || (DAT_GameState::instance.mapAndTime.playerTeams[piVar7->owner]
                                            == DAT_GameState::instance.mapAndTime.playerTeams[playerID]))
                                    || (DAT_BuildingsState::instance.buildings[piVar7->buildingID].field241_0x2c6
                                        != 0))) {
                                aiStack_640[local_96c * 2 + 1] = 0;
                                aiStack_640[local_96c * 2] = iVar7;
                                local_96c = local_96c + 1;
                            }
                        }
                        iVar7 = iVar7 + 1;
                        piVar7 = piVar7 + 0x81;
                    } while (iVar7 < this->maxClimbDataCount);
                }
                int iVar6 = 0;
                this->field63_0xc0 = 0;
                iVar7 = iVar5;
                if (0 < local_96c) {
                    do {
                        iVar1 = aiStack_640[iVar6 * 2];
                        iVar5 = iVar7;
                        if (this->climbData[iVar1].type != 1) {
                            dVar2 = this->climbData[iVar1].area;
                            if (dVar2 == toArea) {
                                dVar2 = this->climbData[iVar1].wallGroupAreaID;
                                if ((dVar2 == fromArea)
                                    || (dVar3 = this->climbData[iVar1].buildingArea, dVar3 == fromArea)) {
                                    return (int)(toArea);
                                }
                                adStack_960[iVar7] = dVar2;
                                aiStack_640[iVar6 * 2 + 1] = 1;
                                iVar5 = iVar7 + 1;
                                if (0 < (int)dVar3) {
                                    adStack_960[iVar7 + 1] = dVar3;
                                    iVar5 = iVar7 + 2;
                                }
                            } else {
                                dVar3 = this->climbData[iVar1].wallGroupAreaID;
                                if (dVar3 == toArea) {
                                    if (dVar2 == fromArea) {
                                        this->field63_0xc0 = 0;
                                        return (int)(toArea);
                                    }
                                    dVar3 = this->climbData[iVar1].buildingArea;
                                    if (dVar3 == fromArea) {
                                        this->field63_0xc0 = 0;
                                        return (int)(toArea);
                                    }
                                    adStack_960[iVar7] = dVar2;
                                    aiStack_640[iVar6 * 2 + 1] = 1;
                                    iVar5 = iVar7 + 1;
                                    if (0 < (int)dVar3) {
                                        adStack_960[iVar7 + 1] = dVar3;
                                        iVar5 = iVar7 + 2;
                                    }
                                } else if (this->climbData[iVar1].buildingArea == toArea) {
                                    if (dVar2 == fromArea) {
                                        this->field63_0xc0 = 0;
                                        return (int)(toArea);
                                    }
                                    if (dVar3 == fromArea) {
                                        this->field63_0xc0 = 0;
                                        return (int)(toArea);
                                    }
                                    adStack_960[iVar7] = dVar2;
                                    adStack_960[iVar7 + 1] = dVar3;
                                    aiStack_640[iVar6 * 2 + 1] = 1;
                                    iVar5 = iVar7 + 2;
                                }
                            }
                        }
                        iVar6 = iVar6 + 1;
                        iVar7 = iVar5;
                    } while (iVar6 < local_96c);
                    if (0 < iVar5) {
                        do {
                            dVar2 = adStack_960[local_968];
                            local_968 = local_968 + 1;
                            iVar6 = 0;
                            iVar7 = iVar5;
                            do {
                                iVar5 = iVar7;
                                if ((aiStack_640[iVar6 * 2 + 1] != 1)
                                    && (iVar1 = aiStack_640[iVar6 * 2], this->climbData[iVar1].type != 1)) {
                                    /*
                                      not a ladder
                                     */
                                    dVar3 = this->climbData[iVar1].area;
                                    if (dVar3 == dVar2) {
                                        dVar3 = this->climbData[iVar1].wallGroupAreaID;
                                        if (dVar3 == fromArea) {
                                            this->field63_0xc0 = 0;
                                            return (int)(dVar2);
                                        }
                                        dVar4 = this->climbData[iVar1].buildingArea;
                                        if (dVar4 == fromArea) {
                                            this->field63_0xc0 = 0;
                                            return (int)(dVar2);
                                        }
                                        adStack_960[iVar7] = dVar3;
                                        aiStack_640[iVar6 * 2 + 1] = 1;
                                        iVar5 = iVar7 + 1;
                                        if (0 < (int)dVar4) {
                                            adStack_960[iVar7 + 1] = dVar4;
                                            iVar5 = iVar7 + 2;
                                        }
                                    } else {
                                        dVar4 = this->climbData[iVar1].wallGroupAreaID;
                                        if (dVar4 == dVar2) {
                                            if (dVar3 == fromArea) {
                                                this->field63_0xc0 = 0;
                                                return (int)(dVar2);
                                            }
                                            dVar4 = this->climbData[iVar1].buildingArea;
                                            if (dVar4 == fromArea) {
                                                this->field63_0xc0 = 0;
                                                return (int)(dVar2);
                                            }
                                            adStack_960[iVar7] = dVar3;
                                            aiStack_640[iVar6 * 2 + 1] = 1;
                                            iVar5 = iVar7 + 1;
                                            if (0 < (int)dVar4) {
                                                adStack_960[iVar7 + 1] = dVar4;
                                            LAB_004a5605:
                                                iVar5 = iVar7 + 2;
                                            }
                                        } else if (this->climbData[iVar1].buildingArea == dVar2) {
                                            if (dVar3 == fromArea) {
                                                this->field63_0xc0 = 0;
                                                return (int)(dVar2);
                                            }
                                            if (dVar4 == fromArea) {
                                                this->field63_0xc0 = 0;
                                                return (int)(dVar2);
                                            }
                                            adStack_960[iVar7] = dVar3;
                                            aiStack_640[iVar6 * 2 + 1] = 1;
                                            adStack_960[iVar7 + 1] = dVar4;
                                            goto LAB_004a5605;
                                        }
                                    }
                                }
                                iVar6 = iVar6 + 1;
                                iVar7 = iVar5;
                            } while (iVar6 < local_96c);
                        } while (local_968 < iVar5);
                    }
                }
                iVar6 = 0;
                this->field63_0xc0 = 1;
                this->field50_0x98 = 1;
                iVar7 = iVar5;
                if (0 < local_96c) {
                    do {
                        iVar1 = aiStack_640[iVar6 * 2];
                        dVar2 = this->climbData[iVar1].area;
                        aiStack_640[iVar6 * 2 + 1] = 0;
                        if (dVar2 == toArea) {
                            dVar2 = this->climbData[iVar1].wallGroupAreaID;
                            if ((dVar2 == fromArea)
                                || (dVar3 = this->climbData[iVar1].buildingArea, dVar3 == fromArea)) {
                                return (int)(toArea);
                            }
                            adStack_960[iVar7] = dVar2;
                            aiStack_640[iVar6 * 2 + 1] = 1;
                            iVar5 = iVar7 + 1;
                            if (0 < (int)dVar3) {
                                adStack_960[iVar7 + 1] = dVar3;
                                iVar5 = iVar7 + 2;
                            }
                        } else {
                            dVar3 = this->climbData[iVar1].wallGroupAreaID;
                            if (dVar3 == toArea) {
                                if (dVar2 == fromArea) {
                                    this->field50_0x98 = 1;
                                    this->field63_0xc0 = 1;
                                    return (int)(toArea);
                                }
                                dVar3 = this->climbData[iVar1].buildingArea;
                                if (dVar3 == fromArea) {
                                    this->field50_0x98 = 1;
                                    this->field63_0xc0 = 1;
                                    return (int)(toArea);
                                }
                                adStack_960[iVar7] = dVar2;
                                aiStack_640[iVar6 * 2 + 1] = 1;
                                iVar5 = iVar7 + 1;
                                if (0 < (int)dVar3) {
                                    adStack_960[iVar7 + 1] = dVar3;
                                    iVar5 = iVar7 + 2;
                                }
                            } else {
                                iVar5 = iVar7;
                                if (this->climbData[iVar1].buildingArea == toArea) {
                                    if ((dVar2 == fromArea) || (dVar3 == fromArea)) {
                                        return (int)(toArea);
                                    }
                                    adStack_960[iVar7] = dVar2;
                                    adStack_960[iVar7 + 1] = dVar3;
                                    aiStack_640[iVar6 * 2 + 1] = 1;
                                    iVar5 = iVar7 + 2;
                                }
                            }
                        }
                        iVar6 = iVar6 + 1;
                        iVar7 = iVar5;
                    } while (iVar6 < local_96c);
                }
                if (local_968 < iVar5) {
                    do {
                        dVar2 = adStack_960[local_968];
                        local_968 = local_968 + 1;
                        iVar6 = 0;
                        iVar7 = iVar5;
                        if (0 < local_96c) {
                            do {
                                iVar7 = iVar5;
                                if (aiStack_640[iVar6 * 2 + 1] != 1) {
                                    iVar1 = aiStack_640[iVar6 * 2];
                                    dVar3 = this->climbData[iVar1].area;
                                    if (dVar3 == dVar2) {
                                        dVar3 = this->climbData[iVar1].wallGroupAreaID;
                                        if (dVar3 == fromArea) {
                                            this->field50_0x98 = 1;
                                            this->field63_0xc0 = 1;
                                            return (int)(dVar2);
                                        }
                                        dVar4 = this->climbData[iVar1].buildingArea;
                                        if (dVar4 == fromArea) {
                                            this->field50_0x98 = 1;
                                            this->field63_0xc0 = 1;
                                            return (int)(dVar2);
                                        }
                                        adStack_960[iVar5] = dVar3;
                                        aiStack_640[iVar6 * 2 + 1] = 1;
                                        iVar7 = iVar5 + 1;
                                        if (0 < (int)dVar4) {
                                            adStack_960[iVar5 + 1] = dVar4;
                                            iVar7 = iVar5 + 2;
                                        }
                                    } else {
                                        dVar4 = this->climbData[iVar1].wallGroupAreaID;
                                        if (dVar4 == dVar2) {
                                            if (dVar3 == fromArea) {
                                                this->field50_0x98 = 1;
                                                this->field63_0xc0 = 1;
                                                return (int)(dVar2);
                                            }
                                            dVar4 = this->climbData[iVar1].buildingArea;
                                            if (dVar4 == fromArea) {
                                                this->field50_0x98 = 1;
                                                this->field63_0xc0 = 1;
                                                return (int)(dVar2);
                                            }
                                            adStack_960[iVar5] = dVar3;
                                            aiStack_640[iVar6 * 2 + 1] = 1;
                                            iVar7 = iVar5 + 1;
                                            if (0 < (int)dVar4) {
                                                adStack_960[iVar5 + 1] = dVar4;
                                            LAB_004a584f:
                                                iVar7 = iVar5 + 2;
                                            }
                                        } else if (this->climbData[iVar1].buildingArea == dVar2) {
                                            if (dVar3 == fromArea) {
                                                this->field50_0x98 = 1;
                                                this->field63_0xc0 = 1;
                                                return (int)(dVar2);
                                            }
                                            if (dVar4 == fromArea) {
                                                this->field50_0x98 = 1;
                                                this->field63_0xc0 = 1;
                                                return (int)(dVar2);
                                            }
                                            adStack_960[iVar5] = dVar3;
                                            aiStack_640[iVar6 * 2 + 1] = 1;
                                            adStack_960[iVar5 + 1] = dVar4;
                                            goto LAB_004a584f;
                                        }
                                    }
                                }
                                iVar6 = iVar6 + 1;
                                iVar5 = iVar7;
                            } while (iVar6 < local_96c);
                        }
                        iVar5 = iVar7;
                    } while (local_968 < iVar7);
                }
                this->field50_0x98 = 0;
                fromArea = 0;
            }
            return (int)(fromArea);
        }

    }
}
}
