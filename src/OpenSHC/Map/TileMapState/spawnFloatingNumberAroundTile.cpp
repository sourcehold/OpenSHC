#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FB3F0
    void TileMapState::spawnFloatingNumberAroundTile(int x, int y, int type)
    {
        int radius = type / 2;
        int xOffset = DAT_TerrainDefinedData::instance.field2474_0x2764[radius * 60].x;
        if (xOffset == -1) {
            return;
        }

        uint index = 0;
        do {
            int yOffset = DAT_TerrainDefinedData::instance.field2474_0x2764[radius * 60 + index].y;
            int tile = DAT_ViewportRenderState::instance.translationMatrix[yOffset + (y - radius)].addXgetTile + xOffset
                + (x - radius);
            if ((this->LogicLayer[tile] & (L_WALL_OR_GATEHOUSE | L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0
                && (index & 1) == 0) {
                uint frame
                    = (this->field161_0x5549c0 + yOffset + xOffset + index + (x - radius) - 1 + (y - radius)) % 16;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(
                    OpenSHC::IO::Graphics::GID_FLOATS_NEW, frame + 0xe5, 16, 14, tile, 0x100021);
            }
            index++;
            xOffset = DAT_TerrainDefinedData::instance.field2474_0x2764[radius * 60 + index].x;
        } while (xOffset != -1);
    }

}
}
