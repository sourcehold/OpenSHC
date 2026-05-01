/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Audio/SFX/MusicSfx.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)
        // SIZE: 0x00000008
        typedef struct MusicSfx {

            char* musicFile; // 0x00000000 length: 4
            BOOLEnum unknownFlag_0x4; // 0x00000004 length: 4

        } MusicSfx;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(MusicSfx) == 8, MusicSfx);
    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
