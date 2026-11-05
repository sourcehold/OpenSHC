#include "../MouseState.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x004685C0
    void MouseState::renderPreviewAtMouseLocation()
    {
        int orientationVariant = 0;
        if (!this->previewEnabled || !this->rightClickState
            || !DAT_ViewportRenderState::instance.viewportState.field_0x0
            || (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_BUILD_MENU
                && DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)) {
            return;
        }

        if (DAT_TileMapState::instance.mapOrientation == 0) {
            orientationVariant = 0;
        } else if (DAT_TileMapState::instance.mapOrientation == 2) {
            orientationVariant = 3;
        } else if (DAT_TileMapState::instance.mapOrientation == 4) {
            orientationVariant = 2;
        } else if (DAT_TileMapState::instance.mapOrientation == 6) {
            orientationVariant = 1;
        }

        if (!this->field_0x1bc) {
            int imageIndex = GMFirstPictureIndex::instance[16] + 37 + orientationVariant;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_FLOATS, 38 + orientationVariant,
                (this->storedScreenSpaceX - DAT_GMImageHeaders::instance.imh[imageIndex].width / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX,
                (this->storedScreenSpaceY - DAT_GMImageHeaders::instance.imh[imageIndex].height / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY - 50);
        }

        if (!this->field_0x1c0) {
            int iconVariant = this->mouseBasedEvent == 1;

            int imageIndex = GMFirstPictureIndex::instance[16] + 35 + iconVariant;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_FLOATS, 36 + iconVariant,
                (this->storedScreenSpaceX - DAT_GMImageHeaders::instance.imh[imageIndex].width / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX,
                (this->storedScreenSpaceY - DAT_GMImageHeaders::instance.imh[imageIndex].height / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY + 50);
        }

        if (!this->field_0x1c8) {
            int iconVariant = !DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk;
            if (this->field_0x1b8 == 3) {
                iconVariant += 2;
            }

            int imageIndex = GMFirstPictureIndex::instance[16] + 45 + iconVariant;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_FLOATS, 46 + iconVariant,
                (this->storedScreenSpaceX - DAT_GMImageHeaders::instance.imh[imageIndex].width / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX + 80,
                (this->storedScreenSpaceY - DAT_GMImageHeaders::instance.imh[imageIndex].height / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY);
        }

        if (!this->field_0x1c4) {
            int iconVariant = !!DAT_TileMapState::instance.flatViewToggleValue1;
            if (this->field_0x1b8 == 4) {
                iconVariant += 2;
            }

            int imageIndex = GMFirstPictureIndex::instance[16] + 124 + iconVariant;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_FLOATS, 125 + iconVariant,
                (this->storedScreenSpaceX - DAT_GMImageHeaders::instance.imh[imageIndex].width / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX - 80,
                (this->storedScreenSpaceY - DAT_GMImageHeaders::instance.imh[imageIndex].height / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY);
        }
    }

}
}
