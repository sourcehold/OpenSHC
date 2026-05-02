/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/PackagedFileMagicNum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace IO {
    typedef enum PackagedFileMagicNum {

        PFMN_AIV = 200 // 0x000000C8

    } PackagedFileMagicNum;

    static_assert_cpp98_obj(sizeof(PackagedFileMagicNum) == 4, PackagedFileMagicNum);
} // namespace IO
} // namespace OpenSHC
