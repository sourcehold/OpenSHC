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
        int iVar1 = 0;
        if (!this->previewEnabled || !this->rightClickState
            || !DAT_ViewportRenderState::instance.viewportState.field0_0x0
            || (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_BUILD_MENU
                && DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)) {
            return;
        }

        if (DAT_TileMapState::instance.mapOrientation == 0) {
            iVar1 = 0;
        } else if (DAT_TileMapState::instance.mapOrientation == 2) {
            iVar1 = 3;
        } else if (DAT_TileMapState::instance.mapOrientation == 4) {
            iVar1 = 2;
        } else if (DAT_TileMapState::instance.mapOrientation == 6) {
            iVar1 = 1;
        }

        if (!this->field60_0x1bc) {
            int imageIndex = GMTotalPicturesProcessed::instance[16] + 37 + iVar1;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_FLOATS, 38 + iVar1,
                (this->storedScreenSpaceX - DAT_GMImageHeaders::instance.imh[imageIndex].width / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX,
                (this->storedScreenSpaceY - DAT_GMImageHeaders::instance.imh[imageIndex].height / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY - 50);
        }

        if (!this->field61_0x1c0) {
            int uVar2 = this->mouseBasedEvent == 1;

            int imageIndex = GMTotalPicturesProcessed::instance[16] + 35 + uVar2;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_FLOATS, 36 + uVar2,
                (this->storedScreenSpaceX - DAT_GMImageHeaders::instance.imh[imageIndex].width / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX,
                (this->storedScreenSpaceY - DAT_GMImageHeaders::instance.imh[imageIndex].height / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY + 50);
        }

        if (!this->field63_0x1c8) {
            int uVar2 = !DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk;
            if (this->field59_0x1b8 == 3) {
                uVar2 += 2;
            }

            int imageIndex = GMTotalPicturesProcessed::instance[16] + 45 + uVar2;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_FLOATS, 46 + uVar2,
                (this->storedScreenSpaceX - DAT_GMImageHeaders::instance.imh[imageIndex].width / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX + 80,
                (this->storedScreenSpaceY - DAT_GMImageHeaders::instance.imh[imageIndex].height / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY);
        }

        if (!this->field62_0x1c4) {
            int uVar2 = !!DAT_TileMapState::instance.flatViewToggleValue1;
            if (this->field59_0x1b8 == 4) {
                uVar2 += 2;
            }

            int imageIndex = GMTotalPicturesProcessed::instance[16] + 124 + uVar2;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_FLOATS, 125 + uVar2,
                (this->storedScreenSpaceX - DAT_GMImageHeaders::instance.imh[imageIndex].width / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX - 80,
                (this->storedScreenSpaceY - DAT_GMImageHeaders::instance.imh[imageIndex].height / 2)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY);
        }
    }

}
}
