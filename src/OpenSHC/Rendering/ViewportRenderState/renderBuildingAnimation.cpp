#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentlyRenderedSpriteID.hpp"
#include "OpenSHC/Globals/DAT_RenderedUnitOwner.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E3870
    void ViewportRenderState::renderBuildingAnimation(
        int buildingID, int screenX, int screenY, undefined4 param_4, int clipToBuilding)
    {
        if (DAT_BuildingsState::instance.buildings[buildingID].renderAnimation == 0) {
            return;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].animationFrame == 0) {
            return;
        }
        if (DAT_TileMapState::instance.field93_0x5548c8 != 0) {
            return;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].drawBridgeState1 != 0) {
            return;
        }

        if (clipToBuilding != 0) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::temporarySaveMapSurfaceHeightRangeUnk,
                DAT_TextureRenderCoreObject::ptr)
            ();
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMapSurfaceHeightRange,
                DAT_TextureRenderCoreObject::ptr)
            ((screenY - 0x27 < 0) ? 0 : screenY - 0x27, 0x81c);
        }

        DAT_RenderedUnitOwner::instance = DAT_BuildingsState::instance.buildings[buildingID].playerColorUnk;
        DAT_CurrentlyRenderedSpriteID::instance = DAT_BuildingsState::instance.buildings[buildingID].spriteID2;
        if (DAT_BuildingsState::instance.buildings[buildingID].field66_0xbe != 0) {
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending, DAT_TextureRenderCoreObject::ptr)
            ((OpenSHC::IO::Graphics::GmID)DAT_CurrentlyRenderedSpriteID::instance,
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame,
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX + screenX,
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY + screenY,
                DAT_BuildingsState::instance.buildings[buildingID].field66_0xbe);
        } else {
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)
            ((OpenSHC::DE::SHCDE::eGM)DAT_CurrentlyRenderedSpriteID::instance,
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame,
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX + screenX,
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY + screenY);
        }
        if (clipToBuilding != 0) {
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::restoreMapSurfaceHeightRangeFromTemporaryUnk,
                DAT_TextureRenderCoreObject::ptr)
            ();
        }
    }

}
}
