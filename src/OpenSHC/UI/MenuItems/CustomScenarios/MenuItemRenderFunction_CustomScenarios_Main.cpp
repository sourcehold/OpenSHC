#include "../CustomScenarios.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnknownGFXIndex.hpp"
#include "OpenSHC/Globals/INT_00b95abc.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace CustomScenarios {

            // FUNCTION: STRONGHOLDCRUSADER 0x00426060
            void MenuItemRenderFunction_CustomScenarios_Main(int button, ...)
            {
                // 1 while a dialog is open over the menu
                if (DAT_UnknownGFXIndex::instance == 1) {
                    return;
                }
                // Buttons 1 to 4 play a sound when the mouse comes onto them; 5 is Back.
                if (button != 5 && !DAT_ButtonCurrentlyInteracting::instance) {
                    if (button == INT_00b95abc::instance) {
                        INT_00b95abc::instance = -1;
                    }
                    // under this flag buttons 1 to 4 use button picture 353, as MainMenu_Main does
                    if (DAT_TextureRenderCoreObject::instance.unknownSfxAndGmRelatedFlag && button < 5) {
                        DAT_CurrentButtonGmDataIndex::instance = 353;
                    }
                    MACRO_CALL(General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                } else {
                    // under this flag buttons 1 to 4 use button picture 353, as MainMenu_Main does
                    if (DAT_TextureRenderCoreObject::instance.unknownSfxAndGmRelatedFlag && button < 5) {
                        DAT_CurrentButtonGmDataIndex::instance = 353;
                    }
                    MACRO_CALL(General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    DAT_CurrentButtonPictureInGm::instance
                        = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                              .pictureInGm_0x4;
                    if (button < 5) {
                        if (INT_00b95abc::instance != button) {
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                                Audio::SFX::SEID_UNKNOWN_0x92);
                        }
                        INT_00b95abc::instance = button;
                    }
                }
                if (button == 4) {
                    // y before x: x first, or both written in the call, loses the match
                    int const textY = DAT_ButtonY::instance + 19;
                    int const textX = DAT_ButtonX::instance + 26;
                    // "Play a Map"
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SHC_STANDALONE, 0),
                        textX, textY, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 17, FALSE, 0);
                    return;
                }
                if (button == 2) {
                    // y before x: x first, or both written in the call, loses the match
                    int const textY = DAT_ButtonY::instance + 19;
                    int const textX = DAT_ButtonX::instance + 26;
                    // "New Map"
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SHC_STANDALONE, 1),
                        textX, textY, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 17, FALSE, 0);
                    return;
                }
                if (button < 5) {
                    // "Load a Map" (button 1) or "New Crusader Map" (3)
                    // the same call twice, as the original has it: one call loses the match
                    if (!DAT_ButtonCurrentlyInteracting::instance) {
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                            DE::SHCDE::TEXT_MAP_TITLES, button - 1, DAT_ButtonX::instance + 26,
                            DAT_ButtonY::instance + 19, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 17,
                            FALSE);
                        return;
                    }
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_MAP_TITLES, button - 1, DAT_ButtonX::instance + 26, DAT_ButtonY::instance + 19,
                        Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 17, FALSE);
                }
            }

        }
    }
}
}
