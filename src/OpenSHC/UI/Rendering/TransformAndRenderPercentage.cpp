#include "../Rendering.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00433C20
    void Rendering::TransformAndRenderPercentage(int xPos, int yPos, int valueUnk, BOOLEnum otherImageFlagUnk)
    {
        RenderTargetInt const previousDrawBuffer = DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;
        int const displayedValue = (valueUnk * 4) / 100;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        int imageID;
        if (displayedValue > 0) {
            imageID = 128;
        } else if (displayedValue != 0) {
            imageID = 130;
        } else {
            imageID = 129;
        }
        int yOffset;
        if (!otherImageFlagUnk) {
            imageID += 3;
            yOffset = 1;
        } else {
            yOffset = -4;
        }
        int color;
        if (displayedValue > 0) {
            color = OpenSHC::Rendering::Colors::COL_00FF00;
        } else if (displayedValue != 0) {
            color = OpenSHC::Rendering::Colors::COL_0000FF;
        } else {
            color = OpenSHC::Rendering::Colors::COL_B8EEFB;
        }
        DAT_TextManagerObject::instance.field8_0x20 = 1;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
            displayedValue, xPos - 2, yPos + 1, OpenSHC::Text::TTA_RIGHT, color, 0, 18, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, imageID, xPos, yOffset + yPos);
        DAT_TextManagerObject::instance.field8_0x20 = 0;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = previousDrawBuffer;
    }

}
}
