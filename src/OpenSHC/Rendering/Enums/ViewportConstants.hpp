/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/Enums/ViewportConstants.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {
    namespace Enums {
        typedef enum ViewportConstants {

            VC_UNIT_BATCH_COUNT = 5, // 0x00000005
            VC_SCREEN_POINT_TABLE_START = 8, // 0x00000008
            VC_SEA_WHITE_CAP_FRAME_COUNT = 8, // 0x00000008
            VC_TILE_ROW_PIXEL_HEIGHT = 8, // 0x00000008
            VC_TILE_PIXEL_HEIGHT = 16, // 0x00000010
            VC_TILE_PIXEL_WIDTH = 32, // 0x00000020
            VC_MAP_SURFACE_MARGIN_X = 150, // 0x00000096
            VC_SCREEN_POINT_SHORT_ROW = 200, // 0x000000C8
            VC_SCREEN_POINT_LONG_ROW = 201, // 0x000000C9
            VC_MAP_SURFACE_HEIGHT = 2076, // 0x0000081C
            VC_SCREEN_POINT_TABLE_SIZE = 80400 // 0x00013A10

        } ViewportConstants;

        static_assert_cpp98_obj(sizeof(ViewportConstants) == 4, ViewportConstants);
    } // namespace Enums
} // namespace Rendering
} // namespace OpenSHC
