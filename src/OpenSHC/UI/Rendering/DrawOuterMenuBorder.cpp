#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    /*
      The border needs to be loaded last.   It is also usaually called in what seems to be a draw prepare function and
      not every frame.   --TheRedDaemon   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00424BE0
    void Rendering::DrawOuterMenuBorder()
    {
        if ((1024 < DAT_WindowAndDirectDraw::instance.resolutionX)
            || (768 < DAT_WindowAndDirectDraw::instance.resolutionY)) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(DAT_TextureRenderCoreObject::instance.totalLoadedGfx + -1,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance
                        .loadedGfxArray[DAT_TextureRenderCoreObject::instance.totalLoadedGfx + -1]
                        .width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance
                        .loadedGfxArray[DAT_TextureRenderCoreObject::instance.totalLoadedGfx + -1]
                        .height)
                    / 2);
        }
    }

}
}
