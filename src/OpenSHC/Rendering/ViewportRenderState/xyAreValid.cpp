#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00401000
    BOOLEnum ViewportRenderState::xyAreValid(uint x, uint y)
    {
        return ((x <= 399) && (y <= 399)) && this->DAT_BinaryTileMap400x400[y * 400 + x] != 0;
    }

}
}
