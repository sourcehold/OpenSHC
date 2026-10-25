#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          Graph search over active, recognised climb data entries to determine whether two path-connection   areas
          (param_2 and param_3) are reachable from each other via intermediate wall or building   areas. Returns the
          connecting intermediate area ID if a path exists, param_2 if they are directly   adjacent, or 0 if no
          connection is found. Used to decide if units can navigate between   disconnected areas via climbing
          structures.      renamed by: Claude Sonnet 4.6
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A58A0
        dword PathFindingState::findConnectingAreaBetweenTwoAreas(int param_1, dword param_2, dword param_3)
        {
            undefined4 dVar2;
            int iVar1;
            int* piVar5;
            int iVar6;
            dword dVar7;
            dword dVar8;
            int local_96c;
            int local_968;
            dword adStack_960[200];
            int aiStack_640[400];
            if (param_2 == param_3) {
                return (dword)(param_2);
            }
            this->DAT_Test_gatehouse = this->DAT_Test_gatehouse + 1;
            local_96c = 0;
            local_968 = 0;
            iVar6 = 1;
            if (1 < this->maxClimbDataCount) {
                piVar5 = &this->climbData[1].isRecognizedByPathfinding;
                do {
                    if (((ClimbData*)(piVar5 + -6))->canBeUsed == 1 && *piVar5 != 0 && piVar5[-5] != 1
                        && ((param_1 == 0
                                || (DAT_GameState::instance.mapAndTime.playerTeams[piVar5[0x73]]
                                    == DAT_GameState::instance.mapAndTime.playerTeams[param_1]))
                            || (DAT_BuildingsState::instance.buildings[piVar5[-3]].field201_0x2c6 != 0))) {
                        aiStack_640[local_96c * 2 + 1] = 0;
                        aiStack_640[local_96c * 2] = iVar6;
                        local_96c = local_96c + 1;
                    }
                    iVar6 = iVar6 + 1;
                    piVar5 = piVar5 + 0x81;
                } while (iVar6 < this->maxClimbDataCount);
            }
            int iVar4 = 0;
            iVar6 = 0;
            if (0 < local_96c) {
                do {
                    iVar1 = aiStack_640[iVar4 * 2];
                    dVar7 = this->climbData[iVar1].area;
                    if (dVar7 == param_3) {
                        dVar7 = this->climbData[iVar1].wallGroupAreaID;
                        if (dVar7 == param_2) {
                            return (dword)(param_3);
                        }
                        dVar8 = this->climbData[iVar1].buildingArea;
                        if (dVar8 == param_2) {
                            return (dword)(param_3);
                        }
                        adStack_960[iVar6] = dVar7;
                        iVar6 = iVar6 + 1;
                        aiStack_640[iVar4 * 2 + 1] = 1;
                        if (0 < (int)dVar8) {
                            adStack_960[iVar6] = dVar8;
                            iVar6 = iVar6 + 1;
                        }
                    } else if (this->climbData[iVar1].wallGroupAreaID == param_3) {
                        if (dVar7 == param_2) {
                            return (dword)(param_3);
                        }
                        dVar8 = this->climbData[iVar1].buildingArea;
                        if (dVar8 == param_2) {
                            return (dword)(param_3);
                        }
                        adStack_960[iVar6] = dVar7;
                        iVar6 = iVar6 + 1;
                        aiStack_640[iVar4 * 2 + 1] = 1;
                        if (0 < (int)dVar8) {
                            adStack_960[iVar6] = dVar8;
                            iVar6 = iVar6 + 1;
                        }
                    } else if (this->climbData[iVar1].buildingArea == param_3) {
                        dVar8 = this->climbData[iVar1].wallGroupAreaID;
                        if (dVar7 == param_2) {
                            return (dword)(param_3);
                        }
                        if (dVar8 == param_2) {
                            return (dword)(param_3);
                        }
                        adStack_960[iVar6] = dVar7;
                        iVar6 = iVar6 + 1;
                        aiStack_640[iVar4 * 2 + 1] = 1;
                        adStack_960[iVar6] = dVar8;
                        iVar6 = iVar6 + 1;
                    }
                    iVar4 = iVar4 + 1;
                } while (iVar4 < local_96c);
                if (0 < iVar6) {
                    do {
                        dVar7 = adStack_960[local_968];
                        local_968 = local_968 + 1;
                        for (iVar4 = 0; iVar4 < local_96c; iVar4 = iVar4 + 1) {
                            if (aiStack_640[iVar4 * 2 + 1] == 1) {
                                continue;
                            }
                            iVar1 = aiStack_640[iVar4 * 2];
                            dVar8 = this->climbData[iVar1].area;
                            if (dVar8 == dVar7) {
                                dVar8 = this->climbData[iVar1].wallGroupAreaID;
                                if (dVar8 == param_2) {
                                    return (dword)(dVar7);
                                }
                                dVar2 = this->climbData[iVar1].buildingArea;
                                if (dVar2 == param_2) {
                                    return (dword)(dVar7);
                                }
                                adStack_960[iVar6] = dVar8;
                                iVar6 = iVar6 + 1;
                                aiStack_640[iVar4 * 2 + 1] = 1;
                                if ((int)dVar2 <= 0) {
                                    continue;
                                }
                                adStack_960[iVar6] = dVar2;
                                iVar6 = iVar6 + 1;
                            } else if (this->climbData[iVar1].wallGroupAreaID == dVar7) {
                                if (dVar8 == param_2) {
                                    return (dword)(dVar7);
                                }
                                dVar2 = this->climbData[iVar1].buildingArea;
                                if (dVar2 == param_2) {
                                    return (dword)(dVar7);
                                }
                                adStack_960[iVar6] = dVar8;
                                iVar6 = iVar6 + 1;
                                aiStack_640[iVar4 * 2 + 1] = 1;
                                if ((int)dVar2 <= 0) {
                                    continue;
                                }
                                adStack_960[iVar6] = dVar2;
                                iVar6 = iVar6 + 1;
                            } else if (this->climbData[iVar1].buildingArea == dVar7) {
                                dVar2 = this->climbData[iVar1].wallGroupAreaID;
                                if (dVar8 == param_2) {
                                    return (dword)(dVar7);
                                }
                                if (dVar2 == param_2) {
                                    return (dword)(dVar7);
                                }
                                adStack_960[iVar6] = dVar8;
                                iVar6 = iVar6 + 1;
                                aiStack_640[iVar4 * 2 + 1] = 1;
                                adStack_960[iVar6] = dVar2;
                                iVar6 = iVar6 + 1;
                            }
                        }
                    } while (local_968 < iVar6);
                }
            }
            return (dword)(0);
        }

    }
}
}
