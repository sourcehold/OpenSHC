#include "../MouseState.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x004685C0
    void MouseState::renderPreviewAtMouseLocation()
    {
        int orientationOffset = 0;
        if (!this->previewEnabled || !this->rightClickState
            || !DAT_ViewportRenderState::instance.viewportState.field0_0x0
            || (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_BUILD_MENU
                && DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)) {
            return;
        }

        if (DAT_TileMapState::instance.mapOrientation == 0) {
            orientationOffset = 0;
        } else if (DAT_TileMapState::instance.mapOrientation == 2) {
            orientationOffset = 3;
        } else if (DAT_TileMapState::instance.mapOrientation == 4) {
            orientationOffset = 2;
        } else if (DAT_TileMapState::instance.mapOrientation == 6) {
            orientationOffset = 1;
        }

        if (!this->field57_0x1bc) {
            int imageIndex = GMTotalPicturesProcessed::instance[16] + 37 + orientationOffset;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_FLOATS, 38 + orientationOffset,
                (this->storedScreenSpaceX - DAT_GMImageHeaders::instance.imh[imageIndex].width / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX,
                (this->storedScreenSpaceY - DAT_GMImageHeaders::instance.imh[imageIndex].height / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY - 50);
        }

        if (!this->field58_0x1c0) {
            int imageOffset = this->mouseBasedEvent == 1;

            int imageIndex = GMTotalPicturesProcessed::instance[16] + 35 + imageOffset;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_FLOATS, 36 + imageOffset,
                (this->storedScreenSpaceX - DAT_GMImageHeaders::instance.imh[imageIndex].width / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX,
                (this->storedScreenSpaceY - DAT_GMImageHeaders::instance.imh[imageIndex].height / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY + 50);
        }

        if (!this->field60_0x1c8) {
            int imageOffset = !DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk;
            if (this->field56_0x1b8 == 3) {
                imageOffset += 2;
            }

            int imageIndex = GMTotalPicturesProcessed::instance[16] + 45 + imageOffset;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_FLOATS, 46 + imageOffset,
                (this->storedScreenSpaceX - DAT_GMImageHeaders::instance.imh[imageIndex].width / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX + 80,
                (this->storedScreenSpaceY - DAT_GMImageHeaders::instance.imh[imageIndex].height / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY);
        }

        if (!this->field59_0x1c4) {
            int imageOffset = !!DAT_TileMapState::instance.flatViewToggleValue1;
            if (this->field56_0x1b8 == 4) {
                imageOffset += 2;
            }

            int imageIndex = GMTotalPicturesProcessed::instance[16] + 124 + imageOffset;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_FLOATS, 125 + imageOffset,
                (this->storedScreenSpaceX - DAT_GMImageHeaders::instance.imh[imageIndex].width / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX - 80,
                (this->storedScreenSpaceY - DAT_GMImageHeaders::instance.imh[imageIndex].height / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY);
        }
    }

}
}
