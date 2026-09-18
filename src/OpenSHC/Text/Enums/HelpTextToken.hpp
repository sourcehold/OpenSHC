/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Text/Enums/HelpTextToken.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Text {
    namespace Enums {
        typedef enum HelpTextToken {

            HTT_PIC = 1, // 0x00000001
            HTT_FONT = 2, // 0x00000002
            HTT_COLOUR = 3, // 0x00000003
            HTT_LINK = 4, // 0x00000004
            HTT_ENDLINK = 5, // 0x00000005
            HTT_NEWPARAGRAPH = 6, // 0x00000006
            HTT_CENTRE = 7, // 0x00000007
            HTT_ENDCENTRE = 8, // 0x00000008
            HTT_TAB = 9, // seems unused in almost all code
            HTT_LINKCOLOUR = 10, // 0x00000009
            HTT_SOUND = 11, // 0x0000000A
            HTT_STRING = 12, // 0x0000000B
            HTT_INCLUDE = 14 // 0x0000000D

        } HelpTextToken;

        static_assert_cpp98_obj(sizeof(HelpTextToken) == 4, HelpTextToken);
    } // namespace Enums
} // namespace Text
} // namespace OpenSHC
