#include "../MinimapViewState.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B7300
    void MinimapViewState::renderMinimapMain()
    {
        int const xOffset = (DAT_ViewportRenderState::instance.viewportState.viewportHeight - 5) / 2
            + DAT_ViewportRenderState::instance.viewportState.viewportX / 32;
        int const yOffset = DAT_ViewportRenderState::instance.viewportState.viewportY / 8
            + DAT_ViewportRenderState::instance.viewportState.viewportWidth / 2;
        if (this->needsRedraw || xOffset != this->lastRenderedXOffset || yOffset != this->lastRenderedYOffset) {
            if (DAT_TileMapState::instance.mapSize > OpenSHC::Map::MC_MAP_SIZE_200) {
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::drawMinimap, this)(
                    DAT_MenuHandlerState::instance.x + 571, DAT_MenuHandlerState::instance.y + 465, 126, 126, 7,
                    xOffset, yOffset, 2, 1, 0);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::drawMinimap, this)(
                    DAT_MenuHandlerState::instance.x + 571, DAT_MenuHandlerState::instance.y + 465, 126, 126, 7,
                    xOffset, yOffset, 4, 2, 0);
            }
        }
        this->lastRenderedXOffset = xOffset;
        this->lastRenderedYOffset = yOffset;
        this->needsRedraw = FALSE;
        this->field_0xc = 0;
        this->someMiniMapCounterTill4 = (this->someMiniMapCounterTill4 + 1) % 4;
        if (DAT_TileMapState::instance.DAT_SelectionIconType != 0 && this->minimapClickEnabled
            && DAT_MouseState::instance.screenSpaceX >= DAT_MenuHandlerState::instance.x + 571
            && DAT_MouseState::instance.screenSpaceX < DAT_MenuHandlerState::instance.x + 697
            && DAT_MouseState::instance.screenSpaceY >= DAT_MenuHandlerState::instance.y + 465
            && DAT_MouseState::instance.screenSpaceY < DAT_MenuHandlerState::instance.y + 591) {
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_MINI_CURSORS,
                DAT_TileMapState::instance.DAT_SelectionIconType,
                DAT_MouseState::instance.screenSpaceX
                    - DAT_TextureRenderCoreObject::instance
                        .gmFileHeaderColorpaletteArray[OpenSHC::DE::SHCDE::GM_MINI_CURSORS]
                        .originX,
                DAT_MouseState::instance.screenSpaceY
                    - DAT_TextureRenderCoreObject::instance
                        .gmFileHeaderColorpaletteArray[OpenSHC::DE::SHCDE::GM_MINI_CURSORS]
                        .originY);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }
    }

}
}
