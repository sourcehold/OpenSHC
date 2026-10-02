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

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00433C20
    void Rendering::TransformAndRenderPercentage(int xPos, int yPos, int valueUnk, BOOLEnum otherImageFlagUnk)
    {
        int integer;
        RenderTargetInt RVar1;
        uint color;
        int imageID;
        int iVar2;
        RVar1 = DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;
        integer = (valueUnk * 4) / 100;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        if (integer < 1) {
            imageID = (integer != 0) + 0x81;
        } else {
            imageID = 0x80;
        }
        if (otherImageFlagUnk == FALSE) {
            imageID = imageID + 3;
            iVar2 = 1;
        } else {
            iVar2 = -4;
        }
        if (integer < 1) {
            color = (-(uint)(integer != 0) & 0xff471204) + 0xb8eefb;
        } else {
            color = 0xff00;
        }
        DAT_TextManagerObject::instance.field8_0x20 = 1;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
            integer, xPos + -2, yPos + 1, OpenSHC::Text::TTA_RIGHT, color, 0, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, imageID, xPos, iVar2 + yPos);
        DAT_TextManagerObject::instance.field8_0x20 = 0;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = RVar1;
    }

}
}
