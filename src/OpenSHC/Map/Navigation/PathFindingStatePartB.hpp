/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Navigation/PathFindingStatePartB.hpp'
*/

#pragma once

#include "OpenSHC/Map/Navigation/AreaPairInt.hpp"
#include "OpenSHC/Map/Navigation/PathHelper12.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Navigation::AreaPairInt;
        using OpenSHC::Map::Navigation::PathHelper12;

#pragma pack(push, 1)
        // SIZE: 0x000B22CC
        typedef struct PathFindingStatePartB {

            PathHelper12 destinationsArray[500]; // 0x00000000 length: 6000
            undefined4 currentDistance; // 0x00001770 length: 4
            undefined4 readIndex; // 0x00001774 length: 4
            undefined4 previousReadIndex; // 0x00001778 length: 4
            undefined4 writeIndex; // 0x0000177C length: 4
            undefined4 nextWriteIndex; // 0x00001780 length: 4
            undefined1 padding_0x1784[12]; // 0x00001784 length: 12
            int depth; // 0x00001790 length: 4
            byte* ptrPathPlan; // 0x00001794 length: 4
            undefined4 pathPlanIndex; // 0x00001798 length: 4
            int tilesQueue[80400]; // 0x0000179C length: 321600
            short yQueue[80400]; // 0x0004FFDC length: 160800
            short xQueue[80400]; // 0x000773FC length: 160800
            byte unknownAlgLayer[80400]; // 0x0009E81C length: 80400
            AreaPairInt acceptAreaPairArray1[10]; // 0x000B222C length: 80
            AreaPairInt rejectionAreaPairArray[10]; // 0x000B227C length: 80

        } PathFindingStatePartB;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(PathFindingStatePartB) == 729804, PathFindingStatePartB);
    } // namespace Navigation
} // namespace Map
} // namespace OpenSHC
