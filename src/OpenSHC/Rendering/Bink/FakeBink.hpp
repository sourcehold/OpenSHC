/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Rendering/Bink/FakeBink.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

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
    } // namespace Bink
} // namespace Rendering
} // namespace OpenSHC
