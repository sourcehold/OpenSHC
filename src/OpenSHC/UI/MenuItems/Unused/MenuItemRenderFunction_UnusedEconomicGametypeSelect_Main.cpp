#include "../Unused.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using OpenSHC::Audio::SFX::SoundEffectID;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00425AD0
        void Unused::MenuItemRenderFunction_UnusedEconomicGametypeSelect_Main(int param_1, ...)
        {
            int iVar1;
            DWORD _currentTime;
            uint uVar2;
            iVar1 = DAT_CurrentButtonGmDataIndex::instance;
            if ((param_1 != 5) && (DAT_ButtonCurrentlyInteracting::instance == FALSE)) {
                if (param_1 == INT_00b95abc::instance) {
                    INT_00b95abc::instance = -1;
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                _currentTime = timeGetTime();
                uVar2
                    = (_currentTime
                          - DAT_UIButtonDefinedData::instance.ButtonGmDataArray[iVar1].stateTransitionTimeBaseUnk_0x18)
                        / 100
                    & 0x3f;
                if (0xf < uVar2) {
                    uVar2 = 0;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    (OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance.ButtonGmDataArray[iVar1].gmId_0x0,
                    (int)((int)(DAT_UIButtonDefinedData::instance.ButtonGmDataArray[iVar1].pictureInGm_0x4 + uVar2)),
                    (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                DAT_CurrentButtonPictureInGm::instance
                    = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                          .pictureInGm_0x4;
            }
            switch (param_1) {
            case 1:
                DAT_ButtonX::instance = DAT_ButtonX::instance + 1;
                DAT_ButtonY::instance = DAT_ButtonY::instance + -1;
                break;
            case 2:
                DAT_ButtonX::instance = DAT_ButtonX::instance + -1;
                break;
            case 4:
                DAT_ButtonY::instance = DAT_ButtonY::instance + 2;
            }
            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            DAT_CurrentButtonPictureInGm::instance
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                      .pictureInGm_0x4;
            if (param_1 < 5) {
                if (INT_00b95abc::instance != param_1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        (OpenSHC::Audio::SFX::SoundEffectID)(OpenSHC::Audio::SFX::SEID_CHILDREN_PLAY_MAYPOLE
                            | OpenSHC::Audio::SFX::SEID_WOOD_CHOP));
                }
                INT_00b95abc::instance = param_1;
            }
        }

    }
}
}
