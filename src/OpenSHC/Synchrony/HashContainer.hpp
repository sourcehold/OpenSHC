/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony/HashContainer.hpp'
*/

#pragma once

#include "OpenSHC/Synchrony/HashContainerElement.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Synchrony::HashContainerElement;

#pragma pack(push, 1)
    // SIZE: 0x000001B0
    typedef struct HashContainer {

        HashContainerElement player0; // 0x00000000 length: 48
        HashContainerElement player1; // 0x00000030 length: 48
        HashContainerElement player2; // 0x00000060 length: 48
        HashContainerElement player3; // 0x00000090 length: 48
        HashContainerElement player4; // 0x000000C0 length: 48
        HashContainerElement player5; // 0x000000F0 length: 48
        HashContainerElement player6; // 0x00000120 length: 48
        HashContainerElement player7; // 0x00000150 length: 48
        HashContainerElement player8; // 0x00000180 length: 48

    } HashContainer;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(HashContainer) == 432, HashContainer);
} // namespace Synchrony
} // namespace OpenSHC
