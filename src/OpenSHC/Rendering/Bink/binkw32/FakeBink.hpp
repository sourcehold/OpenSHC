/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/Bink/binkw32/FakeBink.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {
    namespace Bink {
        namespace binkw32 {

#pragma pack(push, 1)
            // SIZE: 0x00000010
            typedef struct FakeBink {

                ulong width; // 0x00000000 length: 4
                ulong height; // 0x00000004 length: 4
                ulong frames; // 0x00000008 length: 4
                ulong frameNum; // 0x0000000C length: 4

            } FakeBink;
#pragma pack(pop)

            static_assert_cpp98_obj(sizeof(FakeBink) == 16, FakeBink);
        } // namespace binkw32
    } // namespace Bink
} // namespace Rendering
} // namespace OpenSHC
