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

        HashContainerElement player[9]; // 0x00000000 length: 432

    } HashContainer;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(HashContainer) == 432, HashContainer);
} // namespace Synchrony
} // namespace OpenSHC
