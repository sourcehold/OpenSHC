#include "../Rendering.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00433C20
    void Rendering::TransformAndRenderPercentage(int xPos, int yPos, int valueUnk, BOOLEnum otherImageFlagUnk)
    {
        RenderTargetInt const previousDrawBuffer = DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;
        int const integer = (valueUnk * 4) / 100;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        int imageID;
        if (integer > 0) {
            imageID = 128;
        } else {
            imageID = (integer != 0) + 129;
        }
        int yOffset;
        if (otherImageFlagUnk == FALSE) {
            imageID = imageID + 3;
            yOffset = 1;
        } else {
            yOffset = -4;
        }
        int color;
        if (integer > 0) {
            color = 0xff00;
        } else if (integer != 0) {
            color = 0xff;
        } else {
            color = 0xb8eefb;
        }
        DAT_TextManagerObject::instance.field8_0x20 = 1;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
            integer, xPos - 2, yPos + 1, OpenSHC::Text::TTA_RIGHT, color, 0, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, imageID, xPos, yOffset + yPos);
        DAT_TextManagerObject::instance.field8_0x20 = 0;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = previousDrawBuffer;
    }

}
}
