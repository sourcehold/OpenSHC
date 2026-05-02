/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony/HashData.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Synchrony {

#pragma pack(push, 1)
    // SIZE: 0x00000200
    typedef struct HashData {

        int componentArray[128]; // 0x00000000 length: 512

    } HashData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(HashData) == 512, HashData);
} // namespace Synchrony
} // namespace OpenSHC
