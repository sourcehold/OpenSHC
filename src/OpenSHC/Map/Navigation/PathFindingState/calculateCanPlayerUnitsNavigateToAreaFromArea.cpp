#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

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
            dword adStack_960[200];
            int aiStack_640[400];
            if (fromArea != toArea) {
                int iVar5 = 0;
                if (toArea == 0) {
                    return 0;
                }
                if (fromArea == 0) {
                    return 0;
                }
                int iVar7 = 1;
                this->DAT_Test_likely = this->DAT_Test_likely + 1;
                int local_96c = 0;
                int local_968 = 0;
                for (iVar7 = 1; iVar7 < this->maxClimbDataCount; iVar7 = iVar7 + 1) {
                    if (this->climbData[iVar7].canBeUsed == 1
                        && this->climbData[iVar7].isRecognizedByPathfinding != 0) {
                        if (this->climbData[iVar7].type == 1) {
                            if (permitClimb == 0) {
                                continue;
                            }
                        } else if (permitClimb == 2) {
                            continue;
                        }
                        if (((playerID == 0
                                    || (DAT_GameState::instance.mapAndTime.playerTeams[this->climbData[iVar7].owner]
                                        == DAT_GameState::instance.mapAndTime.playerTeams[playerID]))
                                || (DAT_BuildingsState::instance.buildings[this->climbData[iVar7].buildingID]
                                        .field239_0x2c6
                                    != 0))) {
                            aiStack_640[local_96c * 2 + 1] = 0;
                            aiStack_640[local_96c * 2] = iVar7;
                            local_96c = local_96c + 1;
                        }
                    }
                }
                int iVar6 = 0;
                this->field63_0xc0 = 0;
                if (0 < local_96c) {
                    do {
                        iVar1 = aiStack_640[iVar6 * 2];
                        if (this->climbData[iVar1].type != 1) {
                            dVar2 = this->climbData[iVar1].area;
                            if (dVar2 == toArea) {
                                dVar2 = this->climbData[iVar1].wallGroupAreaID;
                                if ((dVar2 == fromArea)
                                    || (dVar3 = this->climbData[iVar1].buildingArea, dVar3 == fromArea)) {
                                    return (int)(toArea);
                                }
                                adStack_960[iVar5] = dVar2;
                                iVar5 = iVar5 + 1;
                                aiStack_640[iVar6 * 2 + 1] = 1;
                                if (0 < (int)dVar3) {
                                    adStack_960[iVar5] = dVar3;
                                    iVar5 = iVar5 + 1;
                                }
                            } else {
                                dVar3 = this->climbData[iVar1].wallGroupAreaID;
                                if (dVar3 == toArea) {
                                    if (dVar2 == fromArea) {
                                        return (int)(toArea);
                                    }
                                    dVar3 = this->climbData[iVar1].buildingArea;
                                    if (dVar3 == fromArea) {
                                        return (int)(toArea);
                                    }
                                    adStack_960[iVar5] = dVar2;
                                    aiStack_640[iVar6 * 2 + 1] = 1;
                                    iVar5 = iVar5 + 1;
                                    if (0 < (int)dVar3) {
                                        adStack_960[iVar5] = dVar3;
                                        iVar5 = iVar5 + 1;
                                    }
                                } else if (this->climbData[iVar1].buildingArea == toArea) {
                                    if (dVar2 == fromArea) {
                                        return (int)(toArea);
                                    }
                                    if (dVar3 == fromArea) {
                                        return (int)(toArea);
                                    }
                                    adStack_960[iVar5] = dVar2;
                                    iVar5 = iVar5 + 1;
                                    adStack_960[iVar5] = dVar3;
                                    iVar5 = iVar5 + 1;
                                    aiStack_640[iVar6 * 2 + 1] = 1;
                                }
                            }
                        }
                        iVar6 = iVar6 + 1;
                    } while (iVar6 < local_96c);
                    if (0 < iVar5) {
                        do {
                            dVar2 = adStack_960[local_968];
                            local_968 = local_968 + 1;
                            iVar6 = 0;
                            do {
                                if ((aiStack_640[iVar6 * 2 + 1] != 1)
                                    && (iVar1 = aiStack_640[iVar6 * 2], this->climbData[iVar1].type != 1)) {
                                    /*
                                      not a ladder
                                     */
                                    dVar3 = this->climbData[iVar1].area;
                                    if (dVar3 == dVar2) {
                                        dVar3 = this->climbData[iVar1].wallGroupAreaID;
                                        if (dVar3 == fromArea) {
                                            return (int)(dVar2);
                                        }
                                        dVar4 = this->climbData[iVar1].buildingArea;
                                        if (dVar4 == fromArea) {
                                            return (int)(dVar2);
                                        }
                                        adStack_960[iVar5] = dVar3;
                                        iVar5 = iVar5 + 1;
                                        aiStack_640[iVar6 * 2 + 1] = 1;
                                        if (0 < (int)dVar4) {
                                            adStack_960[iVar5] = dVar4;
                                            iVar5 = iVar5 + 1;
                                        }
                                    } else {
                                        dVar4 = this->climbData[iVar1].wallGroupAreaID;
                                        if (dVar4 == dVar2) {
                                            if (dVar3 == fromArea) {
                                                return (int)(dVar2);
                                            }
                                            dVar4 = this->climbData[iVar1].buildingArea;
                                            if (dVar4 == fromArea) {
                                                return (int)(dVar2);
                                            }
                                            adStack_960[iVar5] = dVar3;
                                            aiStack_640[iVar6 * 2 + 1] = 1;
                                            iVar5 = iVar5 + 1;
                                            if (0 < (int)dVar4) {
                                                adStack_960[iVar5] = dVar4;
                                                iVar5 = iVar5 + 1;
                                            }
                                        } else if (this->climbData[iVar1].buildingArea == dVar2) {
                                            if (dVar3 == fromArea) {
                                                return (int)(dVar2);
                                            }
                                            if (dVar4 == fromArea) {
                                                return (int)(dVar2);
                                            }
                                            adStack_960[iVar5] = dVar3;
                                            iVar5 = iVar5 + 1;
                                            aiStack_640[iVar6 * 2 + 1] = 1;
                                            adStack_960[iVar5] = dVar4;
                                            iVar5 = iVar5 + 1;
                                        }
                                    }
                                }
                                iVar6 = iVar6 + 1;
                            } while (iVar6 < local_96c);
                        } while (local_968 < iVar5);
                    }
                }
                iVar6 = 0;
                this->field63_0xc0 = 1;
                DAT_PathFindingState::instance.field50_0x98 = 1;
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
                            adStack_960[iVar5] = dVar2;
                            iVar5 = iVar5 + 1;
                            aiStack_640[iVar6 * 2 + 1] = 1;
                            if (0 < (int)dVar3) {
                                adStack_960[iVar5] = dVar3;
                                iVar5 = iVar5 + 1;
                            }
                        } else {
                            dVar3 = this->climbData[iVar1].wallGroupAreaID;
                            if (dVar3 == toArea) {
                                if (dVar2 == fromArea) {
                                    return (int)(toArea);
                                }
                                dVar3 = this->climbData[iVar1].buildingArea;
                                if (dVar3 == fromArea) {
                                    return (int)(toArea);
                                }
                                adStack_960[iVar5] = dVar2;
                                aiStack_640[iVar6 * 2 + 1] = 1;
                                iVar5 = iVar5 + 1;
                                if (0 < (int)dVar3) {
                                    adStack_960[iVar5] = dVar3;
                                    iVar5 = iVar5 + 1;
                                }
                            } else if (this->climbData[iVar1].buildingArea == toArea) {
                                if ((dVar2 == fromArea) || (dVar3 == fromArea)) {
                                    return (int)(toArea);
                                }
                                adStack_960[iVar5] = dVar2;
                                iVar5 = iVar5 + 1;
                                adStack_960[iVar5] = dVar3;
                                iVar5 = iVar5 + 1;
                                aiStack_640[iVar6 * 2 + 1] = 1;
                            }
                        }
                        iVar6 = iVar6 + 1;
                    } while (iVar6 < local_96c);
                }
                if (local_968 < iVar5) {
                    do {
                        dVar2 = adStack_960[local_968];
                        local_968 = local_968 + 1;
                        iVar6 = 0;
                        if (0 < local_96c) {
                            do {
                                if (aiStack_640[iVar6 * 2 + 1] != 1) {
                                    iVar1 = aiStack_640[iVar6 * 2];
                                    dVar3 = this->climbData[iVar1].area;
                                    if (dVar3 == dVar2) {
                                        dVar3 = this->climbData[iVar1].wallGroupAreaID;
                                        if (dVar3 == fromArea) {
                                            return (int)(dVar2);
                                        }
                                        dVar4 = this->climbData[iVar1].buildingArea;
                                        if (dVar4 == fromArea) {
                                            return (int)(dVar2);
                                        }
                                        adStack_960[iVar5] = dVar3;
                                        iVar5 = iVar5 + 1;
                                        aiStack_640[iVar6 * 2 + 1] = 1;
                                        if (0 < (int)dVar4) {
                                            adStack_960[iVar5] = dVar4;
                                            iVar5 = iVar5 + 1;
                                        }
                                    } else {
                                        dVar4 = this->climbData[iVar1].wallGroupAreaID;
                                        if (dVar4 == dVar2) {
                                            if (dVar3 == fromArea) {
                                                return (int)(dVar2);
                                            }
                                            dVar4 = this->climbData[iVar1].buildingArea;
                                            if (dVar4 == fromArea) {
                                                return (int)(dVar2);
                                            }
                                            adStack_960[iVar5] = dVar3;
                                            aiStack_640[iVar6 * 2 + 1] = 1;
                                            iVar5 = iVar5 + 1;
                                            if (0 < (int)dVar4) {
                                                adStack_960[iVar5] = dVar4;
                                                iVar5 = iVar5 + 1;
                                            }
                                        } else if (this->climbData[iVar1].buildingArea == dVar2) {
                                            if (dVar3 == fromArea) {
                                                return (int)(dVar2);
                                            }
                                            if (dVar4 == fromArea) {
                                                return (int)(dVar2);
                                            }
                                            adStack_960[iVar5] = dVar3;
                                            iVar5 = iVar5 + 1;
                                            aiStack_640[iVar6 * 2 + 1] = 1;
                                            adStack_960[iVar5] = dVar4;
                                            iVar5 = iVar5 + 1;
                                        }
                                    }
                                }
                                iVar6 = iVar6 + 1;
                            } while (iVar6 < local_96c);
                        }
                    } while (local_968 < iVar5);
                }
                DAT_PathFindingState::instance.field50_0x98 = 0;
                fromArea = 0;
            }
        LAB_ret:
            return (int)(fromArea);
        }

    }
}
}
