/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
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

        WildlifeState();
        ~WildlifeState();

    public:
        // Constructor
        WildlifeState* Constructor_WildlifeState();

        void clearWildlifeState();

        void updateWildlifeGrid(int _y10);

        void renderDebugDataMapData(int x, int y, int width, int height);

        void meth_0x52c570(int param_1, int param_2, int param_3);

        void meth_0x52c810(int param_1, int param_2, int param_3);

        void findAndSetNewRallyPointForDeerAndLions(int tribeID, int always2or3or5, int always0or1);

        undefined4 meth_0x52cfe0(int param_1);

        undefined4 meth_0x52d620(int param_1, int param_2);

        undefined4 meth_0x52d690(int param_1, int param_2);

        void meth_0x52d720(int param_1, int param_2, int param_3);

        void meth_0x52d9d0();

        int meth_0x52dd20();

        void updateWildlife();

        void updateSection1034Info();

        void updateNofFpoints();
    };

    static_assert_cpp98_obj(sizeof(WildlifeState) == 262416, WildlifeState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(WildlifeState, false, Address::SHC_3BB0A8C1_0x00EE23D8) pDAT_WildlifeState;

} // namespace Map
} // namespace OpenSHC
