#include "../HistoricCampaignSelect.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
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

        using OpenSHC::Audio::SFX::SoundEffectID;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004255D0
        void HistoricCampaignSelect::MenuItemRenderFunction_HistoricCampaignSelect_Main(int param_1, ...)
        {
            int yParam;
            char* textAddress;
            int xParam;
            TextAlignment alignment;
            uint foregroundColor;
            uint backgroundColor;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            if (DAT_UnknownGFXIndex::instance != 1) {
                if ((param_1 == 5) || (DAT_ButtonCurrentlyInteracting::instance != FALSE)) {
                    if ((DAT_TextureRenderCoreObject::instance.unknownSfxAndGmRelatedFlag != FALSE) && (param_1 < 5)) {
                        DAT_CurrentButtonGmDataIndex::instance = 0x161;
                    }
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    DAT_CurrentButtonPictureInGm::instance
                        = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                              .pictureInGm_0x4;
                    if (4 < param_1) {}
                    if (INT_00b95abc::instance != param_1) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                            (OpenSHC::Audio::SFX::SoundEffectID)(OpenSHC::Audio::SFX::SEID_CHILDREN_PLAY_MAYPOLE
                                | OpenSHC::Audio::SFX::SEID_WOOD_CHOP));
                    }
                    INT_00b95abc::instance = param_1;
                } else {
                    if (param_1 == INT_00b95abc::instance) {
                        INT_00b95abc::instance = -1;
                    }
                    if ((DAT_TextureRenderCoreObject::instance.unknownSfxAndGmRelatedFlag != FALSE) && (param_1 < 5)) {
                        DAT_CurrentButtonGmDataIndex::instance = 0x161;
                    }
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                }
                if (param_1 < 5) {
                    blendStrength = 0;
                    keepOffsetX = FALSE;
                    fontSize = 0x10;
                    backgroundColor = 0;
                    foregroundColor = 0xc2f0eb;
                    alignment = OpenSHC::Text::TTA_LEFT;
                    yParam = DAT_ButtonY::instance + 0xf;
                    xParam = DAT_ButtonX::instance + 0x1e;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_BUBBLE_HELP_TEXT, param_1 + 0x135), xParam, yParam, alignment, foregroundColor, backgroundColor, fontSize, keepOffsetX, blendStrength);
                    if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ICONS_FRONT_END, 1,
                            (int)((int)(DAT_ButtonX::instance + -0x55)), (int)((int)(DAT_ButtonY::instance + -0x1c)),
                            OpenSHC::IO::Graphics::GID_ICONS_FRONT_END, 2, 0);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                }
            }
        }

    }
}
}
