/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Input/Mouse/MouseXYUUStruct.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Input {
    namespace Mouse {

#pragma pack(push, 1)
        // SIZE: 0x00000010
        typedef struct MouseXYUUStruct {

            int x; // 0x00000000 length: 4
            int y; // 0x00000004 length: 4
            int unknownZero01; // 0x00000008 length: 4
            int unknownOne02; // 0x0000000C length: 4

        } MouseXYUUStruct;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(MouseXYUUStruct) == 16, MouseXYUUStruct);
    } // namespace Mouse
} // namespace Input
} // namespace OpenSHC
