#include "../Helpers.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00ec0840.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00ed26d0.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/INT_00ed3110.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D6F60
    void Helpers::ParseCampaignMapHotspotBitmap()
    {
        // "gfx8\\campaign_map_england_hotspots.bmp", "rb"
        FILE* const file = MACRO_CALL(OS_Func::_fopen)(s_gfx8_campaign_map_england_hotspo_005aaf4c, s_rb_005a4e18);
        BOOLEnum topDown = FALSE;
        INT_00ed3110::instance = 1;
        for (int line = 0; line < 600; ++line) {
            DAT_ARRAY_00ec0840::instance[line].count = 0;
        }
        for (int marker = 1; marker < 21; ++marker) {
            DAT_ARRAY_00ed26d0::instance[marker].x = 64;
            DAT_ARRAY_00ed26d0::instance[marker].y = 64;
        }
        if (file == NULL) {
            return;
        }
        BITMAPINFOHEADER* const info
            = (BITMAPINFOHEADER*)MACRO_CALL(OS_Func::_malloc)(sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));
        if (info == NULL) {
            MACRO_CALL(OS_Func::_fclose)(file);
            return;
        }
        MACRO_CALL(OS_Func::_fseek)(file, sizeof(BITMAPFILEHEADER), FILE_BEGIN);
        if (MACRO_CALL(OS_Func::_fread)(info, 1, sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD), file)
            != sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)) {
            MACRO_CALL(OS_Func::_fclose)(file);
            MACRO_CALL(OS_Func::_free_base)(info);
            return;
        }
        int height = info->biHeight;
        int const width = info->biWidth;
        if (height < 0) {
            height = -height;
            topDown = TRUE;
        }
        if (width == 800 && height == 600) {
            long pixelOffset;
            MACRO_CALL(OS_Func::_fseek)(file, offsetof(BITMAPFILEHEADER, bfOffBits), FILE_BEGIN);
            MACRO_CALL(OS_Func::_fread)(&pixelOffset, sizeof(pixelOffset), 1, file);
            MACRO_CALL(OS_Func::_fseek)(file, pixelOffset, FILE_BEGIN);
            // The rows go into the image buffer top row first.
            if (!topDown) {
                for (int line = 0; line < 600; ++line) {
                    MACRO_CALL(OS_Func::_fseek)(file, pixelOffset + (599 - line) * 800, FILE_BEGIN);
                    MACRO_CALL(OS_Func::_fread)(
                        (byte*)DAT_TextureRenderCoreObject::instance.gmAndGfxImageDataBuffer + line * 800, 800, 1,
                        file);
                }
            } else {
                for (int line = 0; line < 600; ++line) {
                    MACRO_CALL(OS_Func::_fseek)(file, pixelOffset + line * 800, FILE_BEGIN);
                    MACRO_CALL(OS_Func::_fread)(
                        (byte*)DAT_TextureRenderCoreObject::instance.gmAndGfxImageDataBuffer + line * 800, 800, 1,
                        file);
                }
            }
            // Colors 21 to 40 are hotspot runs (type 40 - color), colors 1 to 20 mark a point.
            byte const* pixels = (byte const*)DAT_TextureRenderCoreObject::instance.gmAndGfxImageDataBuffer;
            for (int row = 0; row < 600; ++row) {
                int count = 0;
                // The bounds are tested after each pass: with them in the for header the count test moves first.
                for (int x = 0;;) {
                    byte const color = pixels[x];
                    if (color != 0 && color >= 21 && color <= 40) {
                        int const start = x;
                        int runWidth = 1;
                        for (; x < 800; ++x, ++runWidth) {
                            byte const pixel = pixels[x];
                            if (pixel == 0) {
                                break;
                            }
                            if (pixel > 20) {
                                if (pixel != color) {
                                    break;
                                }
                            } else {
                                DAT_ARRAY_00ed26d0::instance[pixel].y = row;
                                DAT_ARRAY_00ed26d0::instance[pixel].x = x;
                            }
                        }
                        DAT_ARRAY_00ec0840::instance[row].type[count] = 40 - color;
                        DAT_ARRAY_00ec0840::instance[row].x[count] = start;
                        DAT_ARRAY_00ec0840::instance[row].width[count] = runWidth;
                        ++count;
                    }
                    ++x;
                    if (x >= 800 || count >= 12) {
                        break;
                    }
                }
                DAT_ARRAY_00ec0840::instance[row].count = count;
                pixels += 800;
            }
        }
        MACRO_CALL(OS_Func::_free_base)(info);
        MACRO_CALL(OS_Func::_fclose)(file);
    }

}
}
