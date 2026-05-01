/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/Skirmish/SkirmishStatistics.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

#pragma pack(push, 1)
        // SIZE: 0x00000778
        typedef struct SkirmishStatistics {

            char names[9][90]; // 0x00000000 length: 810
            byte active[9]; // 0x0000032A length: 9
            byte padding0; // 0x00000333 length: 1
            int finalGold[9]; // 0x00000334 length: 36
            short finalMaxPopulation[9]; // 0x00000358 length: 18
            byte finalMaxGoodThings[9]; // 0x0000036A length: 9
            byte padding1; // 0x00000373 length: 1
            int finalTimeAlive[9]; // 0x00000374 length: 36
            int finalKillMatrix[9][9]; // 0x00000398 length: 324
            int finalBuildingsBurned[9]; // 0x000004DC length: 36
            int finalFoodProduced[9]; // 0x00000500 length: 36
            int finalIronProduced[9]; // 0x00000524 length: 36
            int finalStoneProduced[9]; // 0x00000548 length: 36
            int finalWoodProduced[9]; // 0x0000056C length: 36
            int finalPitchProduced[9]; // 0x00000590 length: 36
            byte finalMaxBadThings[9]; // 0x000005B4 length: 9
            byte finalKilledLords[9]; // 0x000005BD length: 9
            byte padding2[2]; // 0x000005C6 length: 2
            int finalWeaponsProduced[9]; // 0x000005C8 length: 36
            int finalBuidingsDestroyed[9]; // 0x000005EC length: 36
            int finalTroopsKilledWeighted[9]; // 0x00000610 length: 36
            int finalBuildingsDestroyedWeighted[9]; // 0x00000634 length: 36
            int finalTroopsProduced[9]; // 0x00000658 length: 36
            int finalGoodsRecieved[9]; // 0x0000067C length: 36
            int finalGoodsSent[9]; // 0x000006A0 length: 36
            int unusedUnk[9]; // 0x000006C4 length: 36
            int finalDateOfDeathInMonths[9]; // 0x000006E8 length: 36
            int yearStart; // 0x0000070C length: 4
            int monthStart; // 0x00000710 length: 4
            int yearEnd; // 0x00000714 length: 4
            int monthEnd; // 0x00000718 length: 4
            byte padding3[92]; // 0x0000071C length: 92

        } SkirmishStatistics;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SkirmishStatistics) == 1912, SkirmishStatistics);
    } // namespace Skirmish
} // namespace Game
} // namespace OpenSHC
