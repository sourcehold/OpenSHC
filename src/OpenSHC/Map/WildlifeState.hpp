/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/WildlifeState.hpp'
*/

#pragma once

#include "OpenSHC/Map/Wildlife/WildlifeGridElement.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Wildlife::WildlifeGridElement;

#pragma pack(push, 1)

    // SIZE: 0x00040110
    class WildlifeState {
    public:
        WildlifeGridElement grid[40][40]; // 0x00000000 length: 256000
        int DAT_DebugDataMapDataDisplayType; // 0x0003E800 length: 4
        undefined4 casDisRelated; // 0x0003E804 length: 4
        undefined4 candidateIndex; // 0x0003E808 length: 4
        undefined4 candidateIndex2; // 0x0003E80C length: 4
        short DAT_Y10_Array_Section1034[1600]; // 0x0003E810 length: 3200
        short DAT_X10_Array_Section1034[1600]; // 0x0003F490 length: 3200

    private:
        WildlifeState(WildlifeState const&);
        void operator=(WildlifeState const&);

    public:
        WildlifeState() {};
        ~WildlifeState() {};

        // Constructor
        WildlifeState* Constructor_WildlifeState();

        void clearWildlifeState();

        void updateWildlifeGrid(int _y10);

        void renderDebugDataMapData(int x, int y, int width, int height);

        undefined floodFillWildlifeDangerField();

        undefined floodFillWildlifeGrazingField();

        void findAndSetNewRallyPointForDeerAndLions(int tribeID, int always2or3or5, int always0or1);

        undefined4 buildWildlifeGrazingPath(int param_1);

        undefined4 hasAdjacentWildlifeMarker(int param_1, int param_2);

        undefined4 isGoodGrazingCell(int param_1, int param_2);

        void floodFillWildlifeClaimField(int param_1, int param_2, int param_3);

        undefined mapWildlifeFromAttackSignpost();

        int distanceFromSignpostToClaimedCell();

        void updateWildlife();

        void updateSection1034Info();

        void updateNofFpoints();
    };

    static_assert_cpp98_obj(sizeof(WildlifeState) == 262416, WildlifeState);

#pragma pack(pop)

} // namespace Map
} // namespace OpenSHC
