/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/WindowsHelper/Structs/threadmbcinfostructWINE.hpp'
*/

#pragma once

namespace OpenSHC {
namespace WindowsHelper {
    namespace Structs {

#pragma pack(push, 1)
        // SIZE: 0x00000220
        typedef struct threadmbcinfostructWINE {

            int refcount; // 0x00000000 length: 4
            int mbcodepage; // 0x00000004 length: 4
            int ismbcodepage; // 0x00000008 length: 4
            int mblcid; // 0x0000000C length: 4
            ushort mbulinfo[6]; // 0x00000010 length: 12
            uchar mbctype[257]; // 0x0000001C length: 257
            uchar mbcasemap[256]; // 0x0000011D length: 256
            undefined1 padding_0x21d[3]; // 0x0000021D length: 3

        } threadmbcinfostructWINE;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(threadmbcinfostructWINE) == 544, threadmbcinfostructWINE);
    } // namespace Structs
} // namespace WindowsHelper
} // namespace OpenSHC
