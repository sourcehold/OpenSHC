/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Audio/mss/SndStreamHelper.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace mss {

#pragma pack(push, 1)
        // SIZE: 0x00000014
        typedef struct SndStreamHelper {

            int music; // 0x00000000 length: 4
            int sfx_1Unk; // 0x00000004 length: 4
            int sfx_2Unk; // 0x00000008 length: 4
            int speech_1; // 0x0000000C length: 4
            int speech_2; // 0x00000010 length: 4

        } SndStreamHelper;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SndStreamHelper) == 20, SndStreamHelper);
    } // namespace mss
} // namespace Audio
} // namespace OpenSHC
