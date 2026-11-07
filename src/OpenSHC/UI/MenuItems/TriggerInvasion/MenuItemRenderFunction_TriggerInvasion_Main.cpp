#include "../TriggerInvasion.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BBF40
        void TriggerInvasion::MenuItemRenderFunction_TriggerInvasion_Main(int unitType, ...)
        {
            // the unit's picture in army_units.gm1, counted from 1
            int imageID = 0;
            switch (unitType) {
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
                imageID = 12;
                break;
            case 10:
                imageID = 13;
                break;
            case 11:
                imageID = 15;
                break;
            case 12:
                imageID = 14;
                break;
            case 13:
                imageID = 16;
                break;
            case 14:
                imageID = 11;
                break;
            case 15:
                imageID = 10;
                break;
            case 16:
                imageID = 17;
                break;
            case 17:
                imageID = 18;
                break;
            case 18:
                imageID = 19;
                break;
            case 19:
                imageID = 20;
                break;
            case 20:
                imageID = 21;
                break;
            case 21:
                imageID = 22;
                break;
            case 22:
                imageID = 23;
                break;
            case 23:
                imageID = 24;
                break;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            int const unitCount = DAT_MapPropertiesState::instance.invasionEventContent.unitCountsPerUnitType[unitType];
            if (unitCount != 0) {
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(unitCount,
                        DAT_ButtonX::instance + DAT_ButtonW::instance - 10, DAT_ButtonY::instance + 7,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                } else {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(unitCount,
                        DAT_ButtonX::instance + DAT_ButtonW::instance - 10, DAT_ButtonY::instance + 7,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                }
            }
            // the unit's picture, its middle at y + 15
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ARMY_UNITS, imageID, DAT_ButtonX::instance,
                DAT_ButtonY::instance
                    - DAT_GMImageHeaders::instance
                            .imh[GMFirstPictureIndex::instance[OpenSHC::DE::SHCDE::GM_ARMY_UNITS] + imageID - 1]
                            .height
                        / 2
                    + 15);
        }

    }
}
}
