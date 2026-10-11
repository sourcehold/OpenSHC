/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/AttackInfoSubElement.hpp'
*/

#pragma once

#include "OpenSHC/AI/Siege/EngineerBuildingAndCountPair.hpp"
#include "OpenSHC/Map/AttackInfoSubArrayElement1.hpp"
#include "OpenSHC/Map/AttackInfoSubArrayElement2.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::AI::Siege::EngineerBuildingAndCountPair;
    using OpenSHC::Map::AttackInfoSubArrayElement1;
    using OpenSHC::Map::AttackInfoSubArrayElement2;

#pragma pack(push, 1)
    // SIZE: 0x000177BC
    typedef struct AttackInfoSubElement {

        int currentPlayerID_OR_attackedPlayerID_OR_one; // 0x00000000 length: 4
        int hack1; // 0x00000004 length: 4
        int hack2; // 0x00000008 length: 4
        int hack3; // 0x0000000C length: 4
        int hackValuesArray[4000]; // 0x00000010 length: 16000
        int minPathCostToKeep; // 0x00003E90 length: 4
        int minPathCostToGate; // 0x00003E94 length: 4
        undefined1 padding_0x3e98[8]; // 0x00003E98 length: 8
        int someMinimumDistance; // 0x00003EA0 length: 4
        int field22_0x3ea4; // 0x00003EA4 length: 4
        int field_0x3ea8; // 0x00003EA8 length: 4
        int stone1; // 0x00003EAC length: 4
        int scale1; // 0x00003EB0 length: 4
        int scale2; // 0x00003EB4 length: 4
        int scale3; // 0x00003EB8 length: 4
        AttackInfoSubArrayElement1 scaleValuesArray[1001]; // 0x00003EBC length: 16016
        int town1; // 0x00007D4C length: 4
        int town2; // 0x00007D50 length: 4
        int town3; // 0x00007D54 length: 4
        AttackInfoSubArrayElement2 townValuesArray[1001]; // 0x00007D58 length: 16016
        int gate1; // 0x0000BBE8 length: 4
        int some1000ArrayIndex_2; // 0x0000BBEC length: 4
        int gate2; // 0x0000BBF0 length: 4
        AttackInfoSubArrayElement1 gateValuesArray[1001]; // 0x0000BBF4 length: 16016
        int moat1; // 0x0000FA84 length: 4
        int moat2; // 0x0000FA88 length: 4
        int moat3; // 0x0000FA8C length: 4
        AttackInfoSubArrayElement1 moatValuesArray[562]; // 0x0000FA90 length: 8992
        int createTribeAmount; // 0x00011DB0 length: 4
        EngineerBuildingAndCountPair engineerBuildingAssignments[250]; // 0x00011DB4 length: 2000
        int field37_0x12584; // 0x00012584 length: 4
        int people1; // 0x00012588 length: 4
        int people2; // 0x0001258C length: 4
        int people3; // 0x00012590 length: 4
        AttackInfoSubArrayElement1 peopleValuesArray[312]; // 0x00012594 length: 4992
        undefined1 padding_0x13914[12]; // 0x00013914 length: 12
        int wide1; // 0x00013920 length: 4
        int wide2; // 0x00013924 length: 4
        int wide3; // 0x00013928 length: 4
        AttackInfoSubArrayElement1 wideValuesArray[687]; // 0x0001392C length: 10992
        undefined1 padding_0x1641c[8]; // 0x0001641C length: 8
        int tribeIDArraySize; // 0x00016424 length: 4
        int unknownTribeCounterRelated; // 0x00016428 length: 4
        int tribeIDArray[50]; // 0x0001642C length: 200
        int unknownIntArray_0x164f4[50]; // 0x000164F4 length: 200
        int tribeRelatedArrayValue0UpTo12[50]; // 0x000165BC length: 200
        int field71_0x16684[50]; // 0x00016684 length: 200
        int unknownSignpostRelatedArray[50]; // 0x0001674C length: 200
        int field73_0x16814; // 0x00016814 length: 4
        int delayedWaveAssignmentCount; // 0x00016818 length: 4
        int field75_0x1681c; // 0x0001681C length: 4
        int field76_0x16820; // 0x00016820 length: 4
        int knights; // 0x00016824 length: 4
        int ranged; // 0x00016828 length: 4
        undefined1 padding_0x1682c[8]; // 0x0001682C length: 8
        int tilemapOffset; // 0x00016834 length: 4
        undefined1 padding_0x16838[3972]; // 0x00016838 length: 3972

    } AttackInfoSubElement;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(AttackInfoSubElement) == 96188, AttackInfoSubElement);
} // namespace Map
} // namespace OpenSHC
