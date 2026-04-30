/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Synchrony/HashContainerElement.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Synchrony {

#pragma pack(push, 1)
    // SIZE: 0x00000030
    typedef struct HashContainerElement {

        int domain01; // 0x00000000 length: 4
        int domain02; // 0x00000004 length: 4
        int domain03; // 0x00000008 length: 4
        int domain04; // 0x0000000C length: 4
        int domain05; // 0x00000010 length: 4
        int domain06; // 0x00000014 length: 4
        int domain07; // 0x00000018 length: 4
        int domain08; // 0x0000001C length: 4
        int domain09; // 0x00000020 length: 4
        int domain10; // 0x00000024 length: 4
        int domain11; // 0x00000028 length: 4
        int domain12; // 0x0000002C length: 4

    } HashContainerElement;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(HashContainerElement) == 48, HashContainerElement);
} // namespace Synchrony
} // namespace OpenSHC
