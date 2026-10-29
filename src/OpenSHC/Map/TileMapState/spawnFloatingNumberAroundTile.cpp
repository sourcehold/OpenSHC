#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
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
        int xBase = x - radius;
        int yBase = y - radius;
        int index = 0;
        int xOffset = DAT_TerrainDefinedData::instance.field2343_0x2764[radius * 60].x;
        if (xOffset == -1) {
            return;
        }

        do {
            int yOffset = DAT_TerrainDefinedData::instance.field2343_0x2764[radius * 60 + index].y;
            int tileUnk = DAT_ViewportRenderState::instance.translationMatrix[yOffset + yBase].addXgetTile + xOffset + xBase;
            if ((this->LogicLayer[tileUnk] & (L_WALL_OR_GATEHOUSE | L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0
                && (index & 1) == 0) {
                int frame
                    = ((int)DAT_TileMapState::instance.cursorOverlayAnimationFrame + yOffset + xOffset + index + yBase + xBase - 1)
                    % 16;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(
                    OpenSHC::IO::Graphics::GID_FLOATS_NEW, frame + 0xe5, 16, 14, tileUnk, 0x100021);
            }
            index++;
            xOffset = DAT_TerrainDefinedData::instance.field2343_0x2764[radius * 60 + index].x;
        } while (xOffset != -1);
    }

}
}
