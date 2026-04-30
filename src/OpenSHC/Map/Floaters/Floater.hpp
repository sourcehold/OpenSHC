/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Floaters/Floater.hpp'
*/

#pragma once

#include "OpenSHC/IO/Graphics/GmIDInt.hpp"

namespace OpenSHC {
namespace Map {
    namespace Floaters {

        using OpenSHC::IO::Graphics::GmIDInt;

#pragma pack(push, 1)
        // SIZE: 0x0000001C
        typedef struct Floater {

            int imageID; // 0x00000000 length: 4
            GmIDInt gmID; // 0x00000004 length: 4
            int originX; // 0x00000008 length: 4
            int originY; // 0x0000000C length: 4
            int tile; // 0x00000010 length: 4
            int variation; // 0x00000014 length: 4
            int id; // 0x00000018 length: 4

        } Floater;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(Floater) == 28, Floater);
    } // namespace Floaters
} // namespace Map
} // namespace OpenSHC
