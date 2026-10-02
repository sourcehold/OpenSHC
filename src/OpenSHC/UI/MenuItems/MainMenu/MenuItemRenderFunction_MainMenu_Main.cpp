#include "../MainMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/BOOL_WasInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnknownGFXIndex.hpp"
#include "OpenSHC/Globals/INT_00b95abc.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Audio::SFX::SoundEffectID;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00424F50
        void MainMenu::MenuItemRenderFunction_MainMenu_Main(int param_1, ...)
        {
            char* _textAddress;
            int _y;
            int _x;
            uint uVar1;
            int iVar2;
            BOOLEnum BVar3;
            int iVar4;
            TextAlignment _aligntment;
            uint _color;
            if (DAT_UnknownGFXIndex::instance == 1) {}
            if (param_1 == 5) {
                if ((DAT_ButtonCurrentlyInteracting::instance != FALSE) && (BOOL_WasInteracting::instance == FALSE)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)((OpenSHC::Audio::SFX::SoundEffectID)(OpenSHC::Audio::SFX::SEID_UNIT_DAMAGE3 | OpenSHC::Audio::SFX::SEID_WOOD_SAW));
                }
                BOOL_WasInteracting::instance = DAT_ButtonCurrentlyInteracting::instance;
            LAB_00424fed:
                if ((DAT_TextureRenderCoreObject::instance.unknownSfxAndGmRelatedFlag != FALSE)
                    && (((param_1 == 1 || (param_1 == 2)) || ((param_1 == 3 || (param_1 == 9)))))) {
                    DAT_CurrentButtonGmDataIndex::instance = 0x161;
                }
                if (param_1 < 10) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                } else {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonOnScreenMenu)();
                }
                DAT_CurrentButtonPictureInGm::instance
                    = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                          .pictureInGm_0x4;
                if (((param_1 < 5) || (param_1 == 9)) && (DAT_ButtonCurrentlyInteracting::instance != FALSE)) {
                    if (INT_00b95abc::instance != param_1) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)((OpenSHC::Audio::SFX::SoundEffectID)(OpenSHC::Audio::SFX::SEID_CHILDREN_PLAY_MAYPOLE | OpenSHC::Audio::SFX::SEID_WOOD_CHOP));
                    }
                    INT_00b95abc::instance = param_1;
                }
            } else {
                if ((((DAT_ButtonCurrentlyInteracting::instance != FALSE) || (param_1 == 6)) || (param_1 == 7))
                    || ((param_1 == 8 || (param_1 == 9))))
                    goto LAB_00424fed;
                if (param_1 == INT_00b95abc::instance) {
                    INT_00b95abc::instance = -1;
                }
                if ((DAT_TextureRenderCoreObject::instance.unknownSfxAndGmRelatedFlag != FALSE)
                    && (((param_1 == 1 || (param_1 == 2)) || (param_1 == 3)))) {
                    DAT_CurrentButtonGmDataIndex::instance = 0x161;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            }
            if (param_1 < 5) {
                if ((param_1 == 4) && ((int)DAT_GameCore::instance.directDrawStatus < 0x700)) {
                    /*
                      added by script: "Multiplayer"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 0x1d, (int)((int)(DAT_ButtonX::instance + 0x1e)),
                        (int)((int)(DAT_ButtonY::instance + 0xf)), OpenSHC::Text::TTA_LEFT, 0x7f7f7f, 0, 0x10, FALSE);
                    goto LAB_00425150;
                }
                iVar4 = 0;
                BVar3 = FALSE;
                iVar2 = 0x10;
                uVar1 = 0;
                _color = 0xc2f0eb;
                _y = DAT_ButtonY::instance + 0xf;
                _aligntment = OpenSHC::Text::TTA_LEFT;
                _x = DAT_ButtonX::instance + 0x1e;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, param_1 + 0x19), _x, _y, _aligntment, _color, uVar1, iVar2, BVar3, iVar4);
            }
            if (param_1 == 9) {
                iVar4 = 0;
                BVar3 = FALSE;
                iVar2 = 0x10;
                uVar1 = 0;
                _color = 0xc2f0eb;
                _aligntment = OpenSHC::Text::TTA_LEFT;
                _y = DAT_ButtonY::instance + 0xf;
                _x = DAT_ButtonX::instance + 0x1e;
                /*
                  added by script: "Custom Scenarios"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 0x1e), _x, _y, _aligntment, _color, uVar1, iVar2, BVar3, iVar4);
            } else if (4 < param_1) {
            }
        LAB_00425150:
            if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ICONS_FRONT_END, 1,
                    (int)((int)(DAT_ButtonX::instance + -0x55)), (int)((int)(DAT_ButtonY::instance + -0x1c)),
                    OpenSHC::IO::Graphics::GID_ICONS_FRONT_END, 2, 0);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
        }

    }
}
}
