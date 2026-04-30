/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Navigation/DirectionAlgorithmState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Navigation {

#pragma pack(push, 1)

        // SIZE: 0x00000014
        class DirectionAlgorithmState {
        public:
            int distanceX; // 0x00000000 length: 4
            int distanceY; // 0x00000004 length: 4
            int distanceLow; // 0x00000008 length: 4
            int distanceHigh; // 0x0000000C length: 4
            int orientation; // 0x00000010 length: 4

        private:
            DirectionAlgorithmState(DirectionAlgorithmState const&);
            void operator=(DirectionAlgorithmState const&);

            DirectionAlgorithmState();
            ~DirectionAlgorithmState();

        public:
            int computeHealthPercentage(int param_1, int param_2);

            void calculateOrientation(
                int currentXPosition, int currentYPosition, int destinationXPosition, int destinationYPosition);

            void FUN_0046c9a0(int param_1, int param_2);

            void calculatePreferredRelativeOrientation(int param_1, int param_2, int param_3, int param_4);

            void somethingWithProjectileDistance(int x, int y, int targetX, int targetY);

            int setAxisBasedDistanceResult(
                int destinationXPosition, int destinationYPosition, int fromXPosition, int fromYPosition);

            int getMouseVectorLengthBasedOnDirection(
                int param_1, int param_2, int param_3, int param_4, int orientation);

            uint computeHash(int byteCount, int* address);

            uint FUN_0046cdf0(int param_1, uint* param_2, uint param_3);
        };

        static_assert_cpp98_obj(sizeof(DirectionAlgorithmState) == 20, DirectionAlgorithmState);

#pragma pack(pop)

        MACRO_STRUCT_RESOLVER(DirectionAlgorithmState, false, Address::SHC_3BB0A8C1_0x00EE23BC)
        pDAT_DirectionAlgorithmState;

    } // namespace Navigation
} // namespace Map
} // namespace OpenSHC
