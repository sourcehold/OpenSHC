/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/WallAndPitchState.hpp'
*/

#pragma once

#include "OpenSHC/Map/Walls/WallPlacementInfoElementStruct.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Walls::WallPlacementInfoElementStruct;

#pragma pack(push, 1)

    // SIZE: 0x00000980
    class WallAndPitchState {
    public:
        int countdown; // 0x00000000 length: 4
        int state; // 0x00000004 length: 4
        int id; // 0x00000008 length: 4
        int uid; // 0x0000000C length: 4
        int index; // 0x00000010 length: 4
        int counter; // 0x00000014 length: 4
        int flag; // 0x00000018 length: 4
        WallPlacementInfoElementStruct wallPlacementInfoArray[100]; // 0x0000001C length: 1200
        WallPlacementInfoElementStruct receivedWallPlacementInfoArray[100]; // 0x000004CC length: 1200
        int unused; // 0x0000097C length: 4

    private:
        WallAndPitchState(WallAndPitchState const&);
        void operator=(WallAndPitchState const&);

        WallAndPitchState();
        ~WallAndPitchState();

    public:
        void meth_0x500c20(int buildingID);

        void resetWallAndPitchState();

        void meth_0x500cb0(int entityID);

        void meth_0x500cf0(int unitID);

        void resetWallPlacementInfo();

        void addWallPlacementInfoForTile(int tile);

        void placePitchDitch(int pitchID);

        void destroyWall(int playerID, int count, int amount, int param_4);

        void destroyPitch(int playerID, int count, int amount);

        void meth_0x500f40();

        void meth_0x5118c0();
    };

    static_assert_cpp98_obj(sizeof(WallAndPitchState) == 2432, WallAndPitchState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(WallAndPitchState, false, Address::SHC_3BB0A8C1_0x00EE19D0) pDAT_WallAndPitchState;

} // namespace Map
} // namespace OpenSHC
