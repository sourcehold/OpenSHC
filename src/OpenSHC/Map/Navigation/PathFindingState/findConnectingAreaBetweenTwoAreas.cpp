#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          Breadth-first search over the usable climb data, joining the areas each one connects (its own area, its wall
          group and its building's area). Returns the area through which toArea is reached from fromArea, fromArea
          itself when both are the same area, or 0 when no chain of climb data joins them. With a playerID only the
          climb data of that player's team, or on buildings with field_0x2c6 set, take part.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A58A0
        dword PathFindingState::findConnectingAreaBetweenTwoAreas(int param_1, dword param_2, dword param_3)
        {
            if (param_2 == param_3) {
                return param_2;
            }
            dword const fromArea = param_2;
            dword const toArea = param_3;
            this->DAT_Test_gatehouse = this->DAT_Test_gatehouse + 1;
            int candidateCount = 0;
            int readIndex = 0;
            dword reachedAreas[200];
            struct {
                int climbIndex;
                int visited;
            } candidates[200];
            for (int i = 1; i < this->maxClimbDataCount; ++i) {
                if (this->climbData[i].canBeUsed != 1 || this->climbData[i].isRecognizedByPathfinding == 0
                    || this->climbData[i].type == 1) {
                    continue;
                }
                if (param_1 != 0
                    && DAT_GameState::instance.mapAndTime.playerTeams[this->climbData[i].owner]
                        != DAT_GameState::instance.mapAndTime.playerTeams[param_1]
                    && DAT_BuildingsState::instance.buildings[this->climbData[i].buildingID].field_0x2c6 == 0) {
                    continue;
                }
                candidates[candidateCount].visited = 0;
                candidates[candidateCount].climbIndex = i;
                candidateCount = candidateCount + 1;
            }
            int reachedCount = 0;
            for (int candidate = 0; candidate < candidateCount; ++candidate) {
                int const climbIndex = candidates[candidate].climbIndex;
                dword other = this->climbData[climbIndex].area;
                if (other == toArea) {
                    other = this->climbData[climbIndex].wallGroupAreaID;
                    if (other == fromArea) {
                        return toArea;
                    }
                    int const buildingArea = this->climbData[climbIndex].buildingArea;
                    if (buildingArea == fromArea) {
                        return toArea;
                    }
                    reachedAreas[reachedCount] = other;
                    reachedCount = reachedCount + 1;
                    candidates[candidate].visited = 1;
                    if (buildingArea > 0) {
                        reachedAreas[reachedCount] = buildingArea;
                        reachedCount = reachedCount + 1;
                    }
                } else if (this->climbData[climbIndex].wallGroupAreaID == toArea) {
                    if (other == fromArea) {
                        return toArea;
                    }
                    int const buildingArea = this->climbData[climbIndex].buildingArea;
                    if (buildingArea == fromArea) {
                        return toArea;
                    }
                    reachedAreas[reachedCount] = other;
                    reachedCount = reachedCount + 1;
                    candidates[candidate].visited = 1;
                    if (buildingArea > 0) {
                        reachedAreas[reachedCount] = buildingArea;
                        reachedCount = reachedCount + 1;
                    }
                } else if (this->climbData[climbIndex].buildingArea == toArea) {
                    int const wallGroupAreaID = this->climbData[climbIndex].wallGroupAreaID;
                    if (other == fromArea) {
                        return toArea;
                    }
                    if (wallGroupAreaID == fromArea) {
                        return toArea;
                    }
                    reachedAreas[reachedCount] = other;
                    reachedCount = reachedCount + 1;
                    candidates[candidate].visited = 1;
                    reachedAreas[reachedCount] = wallGroupAreaID;
                    reachedCount = reachedCount + 1;
                }
            }
            if (reachedCount <= 0) {
                return 0;
            }
            do {
                dword const area = reachedAreas[readIndex];
                readIndex = readIndex + 1;
                for (int candidate = 0; candidate < candidateCount; ++candidate) {
                    if (candidates[candidate].visited == 1) {
                        continue;
                    }
                    int const climbIndex = candidates[candidate].climbIndex;
                    dword other = this->climbData[climbIndex].area;
                    if (other == area) {
                        other = this->climbData[climbIndex].wallGroupAreaID;
                        if (other == fromArea) {
                            return area;
                        }
                        int const buildingArea = this->climbData[climbIndex].buildingArea;
                        if (buildingArea == fromArea) {
                            return area;
                        }
                        reachedAreas[reachedCount] = other;
                        reachedCount = reachedCount + 1;
                        candidates[candidate].visited = 1;
                        if (buildingArea > 0) {
                            reachedAreas[reachedCount] = buildingArea;
                            reachedCount = reachedCount + 1;
                        }
                    } else if (this->climbData[climbIndex].wallGroupAreaID == area) {
                        if (other == fromArea) {
                            return area;
                        }
                        int const buildingArea = this->climbData[climbIndex].buildingArea;
                        if (buildingArea == fromArea) {
                            return area;
                        }
                        reachedAreas[reachedCount] = other;
                        reachedCount = reachedCount + 1;
                        candidates[candidate].visited = 1;
                        if (buildingArea > 0) {
                            reachedAreas[reachedCount] = buildingArea;
                            reachedCount = reachedCount + 1;
                        }
                    } else if (this->climbData[climbIndex].buildingArea == area) {
                        int const wallGroupAreaID = this->climbData[climbIndex].wallGroupAreaID;
                        if (other == fromArea) {
                            return area;
                        }
                        if (wallGroupAreaID == fromArea) {
                            return area;
                        }
                        reachedAreas[reachedCount] = other;
                        reachedCount = reachedCount + 1;
                        candidates[candidate].visited = 1;
                        reachedAreas[reachedCount] = wallGroupAreaID;
                        reachedCount = reachedCount + 1;
                    }
                }
            } while (readIndex < reachedCount);
            return 0;
        }

    }
}
}
