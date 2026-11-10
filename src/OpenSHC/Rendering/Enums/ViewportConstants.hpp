#pragma once

namespace OpenSHC {
namespace Rendering {
    namespace Enums {
        typedef enum ViewportConstants {

            // the unit render batches unitBatch1 to unitBatch5
            VC_UNIT_BATCH_COUNT = 5, // 0x00000005
            // viewportY steps 8 pixels per tile row: rows are staggered, so a 16 pixel tile spans two rows
            VC_TILE_ROW_PIXEL_HEIGHT = 8, // 0x00000008
            // the orientation 0 table starts 8 entries into screenPointToTileNumber
            VC_SCREEN_POINT_TABLE_START = 8, // 0x00000008
            // a sea white cap animation runs this many frames before its tile is released
            VC_SEA_WHITE_CAP_FRAME_COUNT = 8, // 0x00000008
            // viewportX steps 32 pixels per tile column
            VC_TILE_PIXEL_WIDTH = 32, // 0x00000020
            // the screen point rows alternate between 201 and 200 tiles
            VC_SCREEN_POINT_SHORT_ROW = 200, // 0x000000C8
            VC_SCREEN_POINT_LONG_ROW = 201, // 0x000000C9
            // height of the map surface (initializeDirectDraw), the end of a setMapSurfaceHeightRange range
            VC_MAP_SURFACE_HEIGHT = 2076, // 0x0000081C
            // entries per orientation in screenPointToTileNumber, one per map tile
            VC_SCREEN_POINT_TABLE_SIZE = 80400 // 0x00013A10

        } ViewportConstants;

        static_assert_cpp98_obj(sizeof(ViewportConstants) == 4, ViewportConstants);
    } // namespace Enums
} // namespace Rendering
} // namespace OpenSHC
