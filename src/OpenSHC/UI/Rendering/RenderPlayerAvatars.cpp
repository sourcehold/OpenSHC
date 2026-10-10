#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    using DE::SHCDE::eGM;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D8AE0
    void Rendering::RenderPlayerAvatars(int imageID, int x, int y)
    {
        int iVar1 = 0;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[imageID] == -1) {
            iVar1 = DAT_GameSynchronyState::instance.currentAIArray[imageID];
        }
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            DE::SHCDE::GM_INTERFACE_ICONS2, imageID + 0x222, x, y);
        if (!iVar1) {
            if (DAT_GameCore::instance.lordIcons[imageID] == 0) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    DE::SHCDE::GM_INTERFACE_ICONS2, 0x21b, x, y);
            }
            if (DAT_GameCore::instance.lordIcons[imageID] == 1) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    DE::SHCDE::GM_INTERFACE_ICONS2, 0x21c, x, y);
            }
            if (0 < DAT_TextureRenderCoreObject::instance.bitmapFaceSizes[imageID + 0x13]) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    DE::SHCDE::GM_INTERFACE_ICONS2, 0x21d, x, y);
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::drawBitmapFace,
                    DAT_TextureRenderCoreObject::ptr)(imageID + 0x13, x + 4, y + 4);
            }
        } else {
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_INTERFACE_ICONS2, iVar1 + 0x20a, x, y);
        }
    }

}
}
