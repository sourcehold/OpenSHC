#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004DA570
    void Rendering::RenderGfxHelperUnk(int loadedGfxIndex, int xPosInMenuRect, int yPosInMenuRect)
    {
        int xPos;
        int yPos;
        int _height;
        int _width;
        _width = DAT_TextureRenderCoreObject::instance.loadedGfxArray[loadedGfxIndex].width;
        _height = DAT_TextureRenderCoreObject::instance.loadedGfxArray[loadedGfxIndex].height;
        xPos = xPosInMenuRect + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
        yPos = yPosInMenuRect + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
        if ((_width == 0x400) && (_height == 0x300)) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(loadedGfxIndex,
                DAT_WindowAndDirectDraw::instance.resolutionX + -0x400 >> 1,
                DAT_WindowAndDirectDraw::instance.resolutionY + -0x300 >> 1);
        }
        if ((DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth <= xPos)
            && (((_width + xPos <= DAT_WindowAndDirectDraw::instance.resolutionX
                             - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                     && (DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight <= yPos))
                && (_height + yPos <= DAT_WindowAndDirectDraw::instance.resolutionY
                        - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight)))) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                DAT_TextureRenderCoreObject::ptr)(loadedGfxIndex, xPos, yPos);
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
            DAT_TextureRenderCoreObject::ptr)(loadedGfxIndex, xPos, yPos);
    }

}
}
