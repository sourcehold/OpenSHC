#include "../Unused.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/INT_00b95abc.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00425AD0
        void Unused::MenuItemRenderFunction_UnusedEconomicGametypeSelect_Main(int button, ...)
        {
            if (button != 5 && !DAT_ButtonCurrentlyInteracting::instance) {
                // not hovered: the button's 16-frame animation, one frame every 100 ms; & 63 holds frame 0 for the
                // rest of a 6.4 s cycle
                if (button == INT_00b95abc::instance) {
                    // the hover ended, so the next hover plays the sound again
                    INT_00b95abc::instance = -1;
                }
                int const buttonIndex = DAT_CurrentButtonGmDataIndex::instance;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                int frame = ((timeGetTime()
                                 - DAT_UIButtonDefinedData::instance.ButtonGmDataArray[buttonIndex]
                                     .stateTransitionTimeBaseUnk_0x18)
                                / 100)
                    & 63;
                if (frame >= 16) {
                    frame = 0;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    (OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance.ButtonGmDataArray[buttonIndex].gmId_0x0,
                    DAT_UIButtonDefinedData::instance.ButtonGmDataArray[buttonIndex].pictureInGm_0x4 + frame,
                    DAT_ButtonX::instance, DAT_ButtonY::instance);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                DAT_CurrentButtonPictureInGm::instance
                    = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                          .pictureInGm_0x4;
                return;
            }
            // hovered, and button 5 always: the still picture, 1, 2 and 4 shifted; 1 to 4 play a sound when the hover
            // starts
            switch (button) {
            case 1:
                DAT_ButtonX::instance += 1;
                DAT_ButtonY::instance -= 1;
                break;
            case 2:
                DAT_ButtonX::instance -= 1;
                break;
            case 3:
                // written out: an empty case leaves the binary's jump table (quick_diff 0.9444 -> 0.8163)
                DAT_ButtonX::instance += 0;
                break;
            case 4:
                DAT_ButtonY::instance += 2;
                break;
            }
            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            DAT_CurrentButtonPictureInGm::instance
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                      .pictureInGm_0x4;
            if (button < 5) {
                if (INT_00b95abc::instance != button) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_UNKNOWN_0x92);
                }
                INT_00b95abc::instance = button;
            }
        }

    }
}
}
