#include "../HistoricMissionPicture.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/Audio/SFX/AmbientSFXType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00eb0b20.hpp"
#include "OpenSHC/Globals/DAT_00ed2780.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/FLOAT_00ec0834.hpp"
#include "OpenSHC/Globals/FLOAT_Between1And5.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using Audio::MSS::enums::SHC_SoundStream;
        using Audio::SFX::AmbientSFXType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004DB600
        void HistoricMissionPicture::MenuView_HistoricMissionPicture_DoEveryFrame()
        {
            BOOLEnum BVar1;
            int _blendStrength;
            BVar1 = MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                Audio::MSS::enums::SND_STR_SFX_1Unk);
            if (!BVar1) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playAmbientSoundStreamUnk, DAT_SFXState::ptr)(
                    Audio::SFX::ASFXT_WIND_0);
            }
            if (DAT_MouseState::instance.leftClickStart) {
                if (!DAT_00ed2780::instance) {
                    FLOAT_00ec0834::instance = 0.0;
                } else {
                    if (DAT_00ed2780::instance != 1)
                        goto LAB_004db652;
                    FLOAT_00ec0834::instance = 31.0 - FLOAT_00ec0834::instance;
                }
                DAT_00ed2780::instance = 2;
            }
        LAB_004db652:
            _blendStrength = MACRO_CALL(UI::Helpers_Func::TicksSinceCounterStart)();
            if (_blendStrength) {
                MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(0, 0, 0);
                MACRO_CALL(UI::Rendering_Func::RenderHistoryBookEdgeUnk)();
                if (!DAT_00ed2780::instance) {
                    MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(DAT_00eb0b20::instance, 0x3e, 0x67);
                }
                if (DAT_00ed2780::instance == 1) {
                    _blendStrength = (long)((double)FLOAT_00ec0834::instance);
                    MACRO_CALL(UI::Rendering_Func::RenderMenuGfxHelper)(
                        DAT_00eb0b20::instance, 0x3e, 0x67, 0x1f - _blendStrength);
                }
                if (DAT_00ed2780::instance == 2) {
                    _blendStrength = (long)((double)FLOAT_00ec0834::instance);
                    MACRO_CALL(UI::Rendering_Func::RenderMenuGfxHelper)(
                        DAT_00eb0b20::instance, 0x3e, 0x67, _blendStrength);
                }
                _blendStrength = 0;
                if (DAT_00ed2780::instance == 1) {
                    _blendStrength = (long)((double)FLOAT_00ec0834::instance);
                    _blendStrength = 0x1f - _blendStrength;
                } else if (DAT_00ed2780::instance == 2) {
                    _blendStrength = (long)((double)FLOAT_00ec0834::instance);
                }
                MACRO_CALL(UI::Rendering_Func::DrawLoadedMenuStringHelperWithBlending)(
                    0, 400, 0x46, 0, 0, 0x10, TRUE, _blendStrength);
                MACRO_CALL(UI::Rendering_Func::DrawLoadedMenuStringHelperWithBlending)(
                    1, 400, 0x6e, 0, 0, 0x10, TRUE, _blendStrength);
                if (DAT_00ed2780::instance
                    && (FLOAT_00ec0834::instance = FLOAT_Between1And5::instance + FLOAT_00ec0834::instance,
                        32.0 < FLOAT_00ec0834::instance != (FLOAT_00ec0834::instance == 32.0))) {
                    if (DAT_00ed2780::instance == 2) {
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            UI::Enums::MVT_HISTORIC_MISSION_INTRO, 0);
                        FLOAT_00ec0834::instance = 31.0;
                        return;
                    }
                    DAT_00ed2780::instance = 0;
                }
            }
            return;
        }

    }
}
}
