#include "../HistoricCampaignSelect.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
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

        // FUNCTION: STRONGHOLDCRUSADER 0x004255D0
        void HistoricCampaignSelect::MenuItemRenderFunction_HistoricCampaignSelect_Main(int param_1, ...)
        {
            if (DAT_UnknownGFXIndex::instance == 1) {
                return;
            }
            if (param_1 != 5 && !DAT_ButtonCurrentlyInteracting::instance) {
                if (param_1 == INT_00b95abc::instance) {
                    INT_00b95abc::instance = -1;
                }
                if (DAT_TextureRenderCoreObject::instance.unknownSfxAndGmRelatedFlag && param_1 < 5) {
                    DAT_CurrentButtonGmDataIndex::instance = 353;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            } else {
                if (DAT_TextureRenderCoreObject::instance.unknownSfxAndGmRelatedFlag && param_1 < 5) {
                    DAT_CurrentButtonGmDataIndex::instance = 353;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                DAT_CurrentButtonPictureInGm::instance
                    = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                          .pictureInGm_0x4;
                if (param_1 >= 5) {
                    return;
                }
                if (INT_00b95abc::instance != param_1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_UNKNOWN_0x92);
                }
                INT_00b95abc::instance = param_1;
            }
            if (param_1 >= 5) {
                return;
            }
            // the campaign's name: "Heads on Spikes", "The Call to Arms", "Saladin's Conquest", "The Kings Crusade" or
            // "Crusader States"
            int const textY = DAT_ButtonY::instance + 15;
            int const textX = DAT_ButtonX::instance + 30;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_BUBBLE_HELP_TEXT, param_1 + 309),
                textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 16, FALSE, 0);
            if (!DAT_ButtonCurrentlyInteracting::instance) {
                return;
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ICONS_FRONT_END, 1,
                DAT_ButtonX::instance - 85, DAT_ButtonY::instance - 28, OpenSHC::IO::Graphics::GID_ICONS_FRONT_END, 2,
                0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
