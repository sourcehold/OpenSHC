#include "../MainMenu.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MainMenuSwingSwordBool.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnknownGFXIndex.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x00424DA0
        void MainMenu::MenuView_MainMenu_DoEveryFrame()
        {
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE) {
                DAT_UnknownGFXIndex::instance = 0;
                // fixme: a positive remainder is cleared too, so the sword swing below never starts from here
                if (DAT_BinkControlState::instance.binkObjPtrArray[0] == NULL
                    && DAT_GameCore::instance.menuViewToSwitchTo == DAT_GameCore::instance.currentMenuViewType) {
                    if (DAT_MainMenuSwingSwordBool::instance) {
                        DAT_MainMenuSwingSwordBool::instance = 0;
                    } else {
                        DAT_MainMenuSwingSwordBool::instance = SEC_RNG::instance.currentNumber1 % 3;
                        if (DAT_MainMenuSwingSwordBool::instance > 0) {
                            DAT_MainMenuSwingSwordBool::instance = 0;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                    }
                    // the idle video
                    if (!DAT_MainMenuSwingSwordBool::instance) {
                        // "richard_ambient.bik"
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK,
                            DAT_BinkControlState::ptr)(0, s_richard_ambient_bik_005a1fe4, 0, 0,
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 508,
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 22, 0);
                    }
                    if (DAT_MainMenuSwingSwordBool::instance == 1) {
                        // "richard_swordswing.bik"
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK,
                            DAT_BinkControlState::ptr)(0, s_richard_swordswing_bik_005a1fc4, 0, 0,
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 508,
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 22, 0);
                    }
                }
            } else {
                DAT_UnknownGFXIndex::instance = 1;
                if (DAT_BinkControlState::instance.binkObjPtrArray[0] != NULL) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback,
                        DAT_BinkControlState::ptr)(0);
                }
            }
            // the background, centred
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(DAT_UnknownGFXIndex::instance,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[DAT_UnknownGFXIndex::instance].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[DAT_UnknownGFXIndex::instance].height)
                    / 2);
            // the version, "V1.41", in the bottom left corner
            char version[100];
            // "V1.%d"
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(version, s_V1_d_005a1fdc, 41);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(version,
                DAT_MenuHandlerState::instance.x + 2, DAT_MenuHandlerState::instance.y + 588, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_7CAAAF, 19, FALSE, 0);
        }

    }
}
}
