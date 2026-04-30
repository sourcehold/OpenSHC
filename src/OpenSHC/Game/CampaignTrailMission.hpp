/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/CampaignTrailMission.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {

#pragma pack(push, 1)
    // SIZE: 0x00000090
    typedef struct CampaignTrailMission {

        pointer* mapNameAddress; // 0x00000000 length: 4
        int fairness; // 0x00000004 length: 4
        int startLevels; // 0x00000008 length: 4
        int numberOfPlayers; // 0x0000000C length: 4
        int player1AI; // 0x00000010 length: 4
        int player2AI; // 0x00000014 length: 4
        int player3AI; // 0x00000018 length: 4
        int player4AI; // 0x0000001C length: 4
        int player5AI; // 0x00000020 length: 4
        int player6AI; // 0x00000024 length: 4
        int player7AI; // 0x00000028 length: 4
        int player8AI; // 0x0000002C length: 4
        int position1; // 0x00000030 length: 4
        int position2; // 0x00000034 length: 4
        int position3; // 0x00000038 length: 4
        int position4; // 0x0000003C length: 4
        int position5; // 0x00000040 length: 4
        int position6; // 0x00000044 length: 4
        int position7; // 0x00000048 length: 4
        int position8; // 0x0000004C length: 4
        int team1; // 0x00000050 length: 4
        int team2; // 0x00000054 length: 4
        int team3; // 0x00000058 length: 4
        int team4; // 0x0000005C length: 4
        int team5; // 0x00000060 length: 4
        int team6; // 0x00000064 length: 4
        int team7; // 0x00000068 length: 4
        int team8; // 0x0000006C length: 4
        int aiv1; // 0x00000070 length: 4
        int aiv2; // 0x00000074 length: 4
        int aiv3; // 0x00000078 length: 4
        int aiv4; // 0x0000007C length: 4
        int aiv5; // 0x00000080 length: 4
        int aiv6; // 0x00000084 length: 4
        int aiv7; // 0x00000088 length: 4
        int aiv8; // 0x0000008C length: 4

    } CampaignTrailMission;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(CampaignTrailMission) == 144, CampaignTrailMission);
} // namespace Game
} // namespace OpenSHC
