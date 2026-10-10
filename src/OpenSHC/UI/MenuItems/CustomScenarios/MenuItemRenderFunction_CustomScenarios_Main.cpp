#include "../CustomScenarios.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using Audio::SFX::SoundEffectID;
        using DE::SHCDE::eTextSections;
        using Text::TextAlignment;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00426060
        void CustomScenarios::MenuItemRenderFunction_CustomScenarios_Main(int param_1, ...)
        {
            char* textAddress;
            int numInGroup;
            int xParam;
            int yParam;
            TextAlignment alignment;
            uint foregroundColor;
            uint backgroundColor;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            if (DAT_UnknownGFXIndex::instance == 1) {}
            if ((param_1 == 5) || (DAT_ButtonCurrentlyInteracting::instance)) {
                if ((DAT_TextureRenderCoreObject::instance.unknownSfxAndGmRelatedFlag) && (param_1 < 5)) {
                    DAT_CurrentButtonGmDataIndex::instance = 0x161;
                }
                MACRO_CALL(UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                DAT_CurrentButtonPictureInGm::instance
                    = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                          .pictureInGm_0x4;
                if (param_1 < 5) {
                    if (INT_00b95abc::instance != param_1) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                            (Audio::SFX::SoundEffectID)(Audio::SFX::SEID_CHILDREN_PLAY_MAYPOLE
                                | Audio::SFX::SEID_WOOD_CHOP));
                    }
                    INT_00b95abc::instance = param_1;
                }
            } else {
                if (param_1 == INT_00b95abc::instance) {
                    INT_00b95abc::instance = -1;
                }
                if ((DAT_TextureRenderCoreObject::instance.unknownSfxAndGmRelatedFlag) && (param_1 < 5)) {
                    DAT_CurrentButtonGmDataIndex::instance = 0x161;
                }
                MACRO_CALL(UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            }
            if (param_1 == 4) {
                numInGroup = 0;
            } else {
                if (param_1 != 2) {
                    if (4 < param_1) {}
                    if (DAT_ButtonCurrentlyInteracting::instance) {
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                            DE::SHCDE::TEXT_MAP_TITLES, param_1 + -1, (int)(DAT_ButtonX::instance + 0x1a),
                            (int)(DAT_ButtonY::instance + 0x13), Text::TTA_LEFT, 0xc2f0eb, 0, 0x11, FALSE);
                    }
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_MAP_TITLES, param_1 + -1, (int)(DAT_ButtonX::instance + 0x1a),
                        (int)(DAT_ButtonY::instance + 0x13), Text::TTA_LEFT, 0xc2f0eb, 0, 0x11, FALSE);
                }
                numInGroup = 1;
            }
            yParam = DAT_ButtonY::instance + 0x13;
            xParam = DAT_ButtonX::instance + 0x1a;
            blendStrength = 0;
            keepOffsetX = FALSE;
            fontSize = 0x11;
            backgroundColor = 0;
            foregroundColor = 0xc2f0eb;
            alignment = Text::TTA_LEFT;
            /*
              added by script: "New Map"
             */
            textAddress = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SHC_STANDALONE, numInGroup);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                textAddress, xParam, yParam, alignment, foregroundColor, backgroundColor, fontSize, keepOffsetX,
                blendStrength);
        }

    }
}
}
