#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DA570
    void Rendering::RenderGfxHelperUnk(int loadedGfxIndex, int xPosInMenuRect, int yPosInMenuRect)
    {
        int const width = DAT_TextureRenderCoreObject::instance.loadedGfxArray[loadedGfxIndex].width;
        int const height = DAT_TextureRenderCoreObject::instance.loadedGfxArray[loadedGfxIndex].height;
        int const maxX
            = DAT_WindowAndDirectDraw::instance.resolutionX - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
        int const maxY
            = DAT_WindowAndDirectDraw::instance.resolutionY - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
        int const xPos = xPosInMenuRect + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
        int const yPos = yPosInMenuRect + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
        if (width == 1024 && height == 768) {
            // a full-screen picture is centred on the screen
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(loadedGfxIndex,
                (DAT_WindowAndDirectDraw::instance.resolutionX - 1024) >> 1,
                (DAT_WindowAndDirectDraw::instance.resolutionY - 768) >> 1);
            return;
        }
        if (xPos >= DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth && width + xPos <= maxX
            && yPos >= DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight && height + yPos <= maxY) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                DAT_TextureRenderCoreObject::ptr)(loadedGfxIndex, xPos, yPos);
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
            DAT_TextureRenderCoreObject::ptr)(loadedGfxIndex, xPos, yPos);
    }

}
}
