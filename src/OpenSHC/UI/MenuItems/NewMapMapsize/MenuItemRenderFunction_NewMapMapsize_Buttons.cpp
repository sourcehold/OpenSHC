#include "../NewMapMapsize.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Audio::SFX::SoundEffectID;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042F7F0
        void NewMapMapsize::MenuItemRenderFunction_NewMapMapsize_Buttons(int param_1, ...)
        {
            undefined4 uVar1;
            char local_18[20];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)local_18;
            if ((DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE)) {
                if (param_1 == 7) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    ;
                }
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    if (param_1 == INT_00b95abc::instance) {
                        INT_00b95abc::instance = -1;
                    }
                    if (DAT_TextureRenderCoreObject::instance.unknownSfxAndGmRelatedFlag != FALSE) {
                        DAT_CurrentButtonGmDataIndex::instance = 0x161;
                    }
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                } else {
                    if (DAT_TextureRenderCoreObject::instance.unknownSfxAndGmRelatedFlag != FALSE) {
                        DAT_CurrentButtonGmDataIndex::instance = 0x161;
                    }
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    DAT_CurrentButtonPictureInGm::instance
                        = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                              .pictureInGm_0x4;
                    if (INT_00b95abc::instance != param_1) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                            (OpenSHC::Audio::SFX::SoundEffectID)(OpenSHC::Audio::SFX::SEID_CHILDREN_PLAY_MAYPOLE
                                | OpenSHC::Audio::SFX::SEID_WOOD_CHOP));
                    }
                    INT_00b95abc::instance = param_1;
                }
                if (param_1 == 1) {
                    uVar1 = 0xa0;
                } else if (param_1 == 2) {
                    uVar1 = 200;
                } else if (param_1 == 3) {
                    uVar1 = 300;
                } else {
                    uVar1 = 400;
                }
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_18, "%dx%d", uVar1, uVar1);
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(local_18,
                    (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance + 0x13)),
                    (TextAlignment)((int)(DAT_ButtonW::instance)), 0xc2f0eb, 0, 0x11, FALSE, 0);
            };
        }

    }
}
}
