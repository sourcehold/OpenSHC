/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony/HashDataContainer.hpp'
*/

#pragma once

#include "OpenSHC/Synchrony/HashData.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Synchrony::HashData;

#pragma pack(push, 1)
    // SIZE: 0x00003C00
    typedef struct HashDataContainer {

        HashData hashDataArray[30]; // 0x00000000 length: 15360

    } HashDataContainer;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(HashDataContainer) == 15360, HashDataContainer);
} // namespace Synchrony
} // namespace OpenSHC
