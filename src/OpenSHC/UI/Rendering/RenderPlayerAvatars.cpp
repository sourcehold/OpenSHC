#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eGM;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D8AE0
    void Rendering::RenderPlayerAvatars(int imageID, int x, int y)
    {
        int aiCharacter = 0;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[imageID] == -1) {
            aiCharacter = DAT_GameSynchronyState::instance.currentAIArray[imageID];
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, imageID + 546, x, y);
        if (aiCharacter == 0) {
            if (DAT_GameCore::instance.lordIcons[imageID] == 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 539, x, y);
            } else if (DAT_GameCore::instance.lordIcons[imageID] == 1) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 540, x, y);
            } else if (DAT_TextureRenderCoreObject::instance.bitmapFaceSizes[imageID + 19] > 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 541, x, y);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFace,
                    DAT_TextureRenderCoreObject::ptr)(imageID + 19, x + 4, y + 4);
            }
        } else {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, aiCharacter + 522, x, y);
        }
    }

}
}
