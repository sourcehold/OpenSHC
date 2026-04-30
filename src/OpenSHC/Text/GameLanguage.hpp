/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Text/GameLanguage.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Text {
    typedef enum GameLanguage {

        GL_ENGLISH = 0, // 0x00000000
        GL_AMERICAN = 1, // 0x00000001
        GL_GERMAN = 2, // 0x00000002
        GL_FRENCH = 3, // 0x00000003
        GL_ITALIAN = 4, // 0x00000004
        GL_SPANISH = 5, // 0x00000005
        GL_POLISH = 6 // 0x00000006

    } GameLanguage;

    static_assert_cpp98_obj(sizeof(GameLanguage) == 4, GameLanguage);
} // namespace Text
} // namespace OpenSHC
