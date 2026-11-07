#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // magenta as RGB555 with the top bit set, and as RGB565
        enum { MAGENTA_555 = 1 << 15 | 31 << 10 | 31, MAGENTA_565 = 31 << 11 | 31 };

        // FUNCTION: STRONGHOLDCRUSADER 0x00454CB0
        void TextureRenderCore::loadCampaignMapGfxUnk()
        {
            // the campaign map's six palettes (.act files, 256 RGB triples each), as screen colours
            for (int map = 0; map < countof(DAT_BlendingDefinedData::instance.campaign_map_england); ++map) {
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    OpenSHC::IO::FRT_GFX8, (char const*)DAT_BlendingDefinedData::instance.campaign_map_england[map]);
                byte palette[256][3];
                // "act"
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::readFirstPartOfCurrentResourceIntoMemory,
                    DAT_ResourceManager::ptr)(palette, sizeof(palette), (char*)s_act_005a5064);
                for (int i = 0; i < countof(palette); ++i) {
                    // green read first (red first: quick_diff 0.9797 -> 0.8716)
                    ushort const green = palette[i][1];
                    ushort const red = palette[i][0];
                    ushort const blue = palette[i][2] >> 3;
                    ushort colour;
                    if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                        colour = ((red & ~7) * 32 + (green & ~3)) * 8 + blue;
                    } else {
                        colour = (((red & ~7) * 32 + (green & ~7)) * 4 + blue) | 1 << 15;
                    }
                    // RGB555 magenta (top bit set) becomes the RGB565 marker; the test runs in both modes
                    if (colour == MAGENTA_555) {
                        colour = MAGENTA_565;
                    }
                    this->campaignMapColorMapsUnk_0x16c886[map][i] = colour;
                }
            }
        }

    }
}
}
