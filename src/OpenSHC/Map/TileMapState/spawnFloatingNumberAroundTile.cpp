#include "../TileMapState.func.hpp"

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

    // FUNCTION: STRONGHOLDCRUSADER 0x004FB3F0
    void TileMapState::spawnFloatingNumberAroundTile(int x, int y, int type)
    {
        int const radius = type / 2;
        int index = 0;
        // x and y become the corner of the square the offset table is measured from
        x -= radius;
        y -= radius;
        for (int xOffset = DAT_TerrainDefinedData::instance.field_0x2764[radius * 60 + index].x; xOffset != -1;
            xOffset = DAT_TerrainDefinedData::instance.field_0x2764[radius * 60 + index].x) {
            int const yOffset = DAT_TerrainDefinedData::instance.field_0x2764[radius * 60 + index].y;
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[yOffset + y].addXgetTile + xOffset + x;
            if ((this->LogicLayer[tile] & (L_WALL_OR_GATEHOUSE | L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0
                && (index & 1) == 0) {
                int const frame
                    = (DAT_TileMapState::instance.cursorOverlayAnimationFrame + yOffset + xOffset + index + x + y - 1)
                    % 16;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(
                    OpenSHC::IO::Graphics::GID_FLOATS_NEW, frame + 229, 16, 14, tile, 0x100021);
            }
            index++;
        }
    }

}
}
