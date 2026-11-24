#include "../MainMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/DirectDrawStatus.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x00424F50
        void MainMenu::MenuItemRenderFunction_MainMenu_Main(int button, ...)
        {
            if (DAT_UnknownGFXIndex::instance == 1) {
                return;
            }
            if (button != 5 && !DAT_ButtonCurrentlyInteracting::instance && button != 6 && button != 7 && button != 8
                && button != 9) {
                // a button that is no longer hovered stops being the last one hovered
                if (button == INT_00b95abc::instance) {
                    INT_00b95abc::instance = -1;
                }
                if (DAT_TextureRenderCoreObject::instance.unknownSfxAndGmRelatedFlag
                    && (button == 1 || button == 2 || button == 3)) {
                    DAT_CurrentButtonGmDataIndex::instance = 353;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            } else {
                if (button == 5) {
                    if (DAT_ButtonCurrentlyInteracting::instance && !BOOL_WasInteracting::instance) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                            OpenSHC::Audio::SFX::SEID_UNKNOWN_0xFB);
                    }
                    BOOL_WasInteracting::instance = DAT_ButtonCurrentlyInteracting::instance;
                }
                if (DAT_TextureRenderCoreObject::instance.unknownSfxAndGmRelatedFlag
                    && (button == 1 || button == 2 || button == 3 || button == 9)) {
                    DAT_CurrentButtonGmDataIndex::instance = 353;
                }
                if (button < 10) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                } else {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonOnScreenMenu)();
                }
                DAT_CurrentButtonPictureInGm::instance
                    = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                          .pictureInGm_0x4;
                // the hover sound plays once, when the pointer moves onto another button
                if ((button < 5 || button == 9) && DAT_ButtonCurrentlyInteracting::instance) {
                    if (INT_00b95abc::instance != button) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                            OpenSHC::Audio::SFX::SEID_UNKNOWN_0x92);
                    }
                    INT_00b95abc::instance = button;
                }
            }
            if (button < 5) {
                if (button == 4 && DAT_GameCore::instance.directDrawStatus < OpenSHC::Rendering::Enums::DD7_LOADED) {
                    // "Multiplayer", greyed out
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 29, DAT_ButtonX::instance + 30,
                        DAT_ButtonY::instance + 15, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_7F7F7F, 0,
                        16, FALSE);
                } else if (!DAT_ButtonCurrentlyInteracting::instance) {
                    // one call per hover state, the two the same, each reading y before x, for the match
                    int const textY = DAT_ButtonY::instance + 15;
                    int const textX = DAT_ButtonX::instance + 30;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, button + 25),
                        textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 16, FALSE, 0);
                } else {
                    int const textY = DAT_ButtonY::instance + 15;
                    int const textX = DAT_ButtonX::instance + 30;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, button + 25),
                        textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 16, FALSE, 0);
                }
            }
            if (button == 9) {
                // two calls that are the same, one per hover state: the split is only for the match
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    int const textY = DAT_ButtonY::instance + 15;
                    int const textX = DAT_ButtonX::instance + 30;
                    // "Custom Scenarios"
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 30),
                        textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 16, FALSE, 0);
                } else {
                    int const textY = DAT_ButtonY::instance + 15;
                    int const textX = DAT_ButtonX::instance + 30;
                    // "Custom Scenarios"
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 30),
                        textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 16, FALSE, 0);
                }
            } else if (button >= 5) {
                return;
            }
            if (DAT_ButtonCurrentlyInteracting::instance) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ICONS_FRONT_END, 1,
                    DAT_ButtonX::instance - 85, DAT_ButtonY::instance - 28, OpenSHC::IO::Graphics::GID_ICONS_FRONT_END,
                    2, 0);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
        }

    }
}
}
