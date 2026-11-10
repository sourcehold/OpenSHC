#include "../NewMapMapsize.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/GmDataIndex.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/INT_00b95abc.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042F7F0
        void NewMapMapsize::MenuItemRenderFunction_NewMapMapsize_Buttons(int buttonID, ...)
        {
            if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU
                || DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                return;
            }
            if (buttonID == 7) {
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                return;
            }
            if (DAT_ButtonCurrentlyInteracting::instance) {
                if (DAT_TextureRenderCoreObject::instance.unknownSfxAndGmRelatedFlag) {
                    DAT_CurrentButtonGmDataIndex::instance = OpenSHC::Rendering::Enums::GDI_ICONS_FRONT_END_353_PIC_17;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                DAT_CurrentButtonPictureInGm::instance
                    = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                          .pictureInGm_0x4;
                if (INT_00b95abc::instance != buttonID) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_UNKNOWN_0x92);
                }
                INT_00b95abc::instance = buttonID;
            } else {
                if (buttonID == INT_00b95abc::instance) {
                    INT_00b95abc::instance = -1;
                }
                if (DAT_TextureRenderCoreObject::instance.unknownSfxAndGmRelatedFlag) {
                    DAT_CurrentButtonGmDataIndex::instance = OpenSHC::Rendering::Enums::GDI_ICONS_FRONT_END_353_PIC_17;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            }
            int mapSize;
            switch (buttonID) {
            default:
                mapSize = OpenSHC::Map::MC_MAP_SIZE_400;
                break;
            case 3:
                mapSize = OpenSHC::Map::MC_MAP_SIZE_300;
                break;
            case 2:
                mapSize = OpenSHC::Map::MC_MAP_SIZE_200;
                break;
            case 1:
                mapSize = OpenSHC::Map::MC_MAP_SIZE_160;
                break;
            }
            char sizeText[20];
            // "%dx%d"
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(sizeText, s__dx_d_005a22fc, mapSize, mapSize);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                sizeText, DAT_ButtonX::instance, DAT_ButtonY::instance + 19,
                (OpenSHC::Text::TextAlignment)DAT_ButtonW::instance, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 17,
                FALSE, 0);
        }

    }
}
}
