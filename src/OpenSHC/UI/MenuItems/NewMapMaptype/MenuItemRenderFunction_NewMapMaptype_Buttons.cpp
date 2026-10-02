#include "../NewMapMaptype.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
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

        using OpenSHC::Audio::SFX::SoundEffectID;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Text::GameLanguage;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042F140
        void NewMapMaptype::MenuItemRenderFunction_NewMapMaptype_Buttons(int param_1, ...)
        {
            int fontSize;
            int iVar1;
            if ((DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE)) {
                if (param_1 == 7) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
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
                iVar1 = 0x13;
                fontSize = 0x11;
                if (DAT_TextManagerObject::instance.gameLanguage - OpenSHC::Text::GL_FRENCH < 3) {
                    fontSize = 0x12;
                    iVar1 = 0x14;
                }
                if (param_1 == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MAP_TITLES, 1, (int)((int)(DAT_ButtonX::instance + 0x1a)),
                        DAT_ButtonY::instance + iVar1, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0, fontSize, FALSE);
                }
                if (param_1 == 2) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SHC_STANDALONE, 2, (int)((int)(DAT_ButtonX::instance + 0x1a)),
                        DAT_ButtonY::instance + iVar1, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0, fontSize, FALSE);
                }
                if (param_1 == 3) {
                    /*
                      added by script: "New Crusader Map"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MAP_TITLES, 2, (int)((int)(DAT_ButtonX::instance + 0x1a)),
                        DAT_ButtonY::instance + iVar1, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0, fontSize, FALSE);
                }
            }
        }

    }
}
}
