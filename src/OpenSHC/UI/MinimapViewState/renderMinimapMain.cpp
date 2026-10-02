#include "../MinimapViewState.func.hpp"

#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Rendering::Enums::RenderTarget;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B7300
    void MinimapViewState::renderMinimapMain()
    {
        int yOffset;
        int xOffset;
        int widthFactor;
        int heightFactor;
        xOffset = (DAT_ViewportRenderState::instance.viewportState.viewportHeight + -5) / 2
            + ((int)(DAT_ViewportRenderState::instance.viewportState.viewportX
                   + (DAT_ViewportRenderState::instance.viewportState.viewportX >> 0x1f & 0x1fU))
                >> 5);
        yOffset = DAT_ViewportRenderState::instance.viewportState.viewportWidth / 2
            + ((int)(DAT_ViewportRenderState::instance.viewportState.viewportY
                   + (DAT_ViewportRenderState::instance.viewportState.viewportY >> 0x1f & 7U))
                >> 3);
        if (((this->field0_0x0 != 0) || (xOffset != this->field1_0x4)) || (yOffset != this->field2_0x8)) {
            if (DAT_TileMapState::instance.mapSize < 200) {
                heightFactor = 2;
                widthFactor = 4;
            } else {
                heightFactor = 1;
                widthFactor = 2;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::drawMinimap, this)(
                DAT_MenuHandlerState::instance.x + 571, (int)((int)(DAT_MenuHandlerState::instance.y + 465)),
                (int)((int)(126)), (int)((int)(126)), 7, xOffset, yOffset, widthFactor, heightFactor, 0);
        }
        this->DAT_SomeMiniMapCounterTill4 = this->DAT_SomeMiniMapCounterTill4 + 1 & 0x80000003;
        this->field0_0x0 = 0;
        this->field3_0xc = 0;
        if ((int)this->DAT_SomeMiniMapCounterTill4 < 0) {
            this->DAT_SomeMiniMapCounterTill4 = (this->DAT_SomeMiniMapCounterTill4 - 1 | 0xfffffffc) + 1;
        }
        this->field1_0x4 = xOffset;
        this->field2_0x8 = yOffset;
        if ((DAT_TileMapState::instance.DAT_SelectionIconType != 0) && (this->field15_0x3c != 0)) {
            if ((DAT_MenuHandlerState::instance.x + 571 <= DAT_MouseState::instance.screenSpaceX)
                && (DAT_MouseState::instance.screenSpaceX < DAT_MenuHandlerState::instance.x + 697)) {
                if ((DAT_MenuHandlerState::instance.y + 465 <= DAT_MouseState::instance.screenSpaceY)
                    && (DAT_MouseState::instance.screenSpaceY < DAT_MenuHandlerState::instance.y + 591)) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)153,
                        (int)((int)(DAT_TileMapState::instance.DAT_SelectionIconType)),
                        DAT_MouseState::instance.screenSpaceX
                            - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[0x99].originX,
                        DAT_MouseState::instance.screenSpaceY
                            - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[0x99].originY);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
            }
        }
    }

}
}
