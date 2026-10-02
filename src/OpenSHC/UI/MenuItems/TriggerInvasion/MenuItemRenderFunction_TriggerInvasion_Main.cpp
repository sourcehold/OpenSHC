#include "../TriggerInvasion.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_Unknown_UnitGMHeights.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004BBF40
        void TriggerInvasion::MenuItemRenderFunction_TriggerInvasion_Main(int param_1, ...)
        {
            int number;
            int imageID;
            uint color;
            imageID = 0;
            switch (param_1) {
            case 0:
                imageID = 1;
                break;
            case 1:
                imageID = 2;
                break;
            case 2:
                imageID = 3;
                break;
            case 3:
                imageID = 4;
                break;
            case 4:
                imageID = 5;
                break;
            case 5:
                imageID = 6;
                break;
            case 6:
                imageID = 7;
                break;
            case 7:
                imageID = 8;
                break;
            case 8:
                imageID = 9;
                break;
            case 9:
                imageID = 0xc;
                break;
            case 10:
                imageID = 0xd;
                break;
            case 0xb:
                imageID = 0xf;
                break;
            case 0xc:
                imageID = 0xe;
                break;
            case 0xd:
                imageID = 0x10;
                break;
            case 0xe:
                imageID = 0xb;
                break;
            case 0xf:
                imageID = 10;
                break;
            case 0x10:
                imageID = 0x11;
                break;
            case 0x11:
                imageID = 0x12;
                break;
            case 0x12:
                imageID = 0x13;
                break;
            case 0x13:
                imageID = 0x14;
                break;
            case 0x14:
                imageID = 0x15;
                break;
            case 0x15:
                imageID = 0x16;
                break;
            case 0x16:
                imageID = 0x17;
                break;
            case 0x17:
                imageID = 0x18;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            number = DAT_MapPropertiesState::instance.invasionEventContent.unitCountsPerUnitType[param_1];
            if (number != 0) {
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    color = 0xc2f0eb;
                } else {
                    color = 0xccfaff;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    number, (int)((int)(DAT_ButtonW::instance + -10 + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, color, 0x12, FALSE, 0);
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ARMY_UNITS, imageID,
                (int)((int)(DAT_ButtonX::instance)),
                (DAT_ButtonY::instance
                    - (int)*(short*)((int)PTR_ARRAY_Unknown_UnitGMHeights::instance
                          + (GMTotalPicturesProcessed::instance[0xae] + imageID) * 0x10 + 0x72)
                        / 2)
                    + 0xf);
            return;
        }

    }
}
}
