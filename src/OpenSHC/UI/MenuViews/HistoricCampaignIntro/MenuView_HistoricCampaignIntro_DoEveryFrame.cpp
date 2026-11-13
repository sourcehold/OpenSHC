#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuViews/HistoricCampaignIntro.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_00eb0b20.hpp"
#include "OpenSHC/Globals/DAT_00ed2780.hpp"
#include "OpenSHC/Globals/DAT_ArrayOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/FLOAT_00ec0834.hpp"
#include "OpenSHC/Globals/FLOAT_Between1And5.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace HistoricCampaignIntro {

            // FUNCTION: STRONGHOLDCRUSADER 0x004DBBC0
            void MenuView_HistoricCampaignIntro_DoEveryFrame()
            {
                if (!MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                        DAT_SoundSystemState::ptr)(Audio::MSS::enums::SND_STR_SFX_1Unk)) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playAmbientSoundStreamUnk, DAT_SFXState::ptr)(
                        Audio::SFX::ASFXT_WIND_0);
                }
                if (DAT_MouseState::instance.leftClickStart != 0) {
                    if (DAT_00ed2780::instance == 0) {
                        FLOAT_00ec0834::instance = 0.0f;
                        DAT_00ed2780::instance = 2;
                    } else if (DAT_00ed2780::instance == 1) {
                        FLOAT_00ec0834::instance = 31.0 - FLOAT_00ec0834::instance;
                        DAT_00ed2780::instance = 2;
                    }
                }
                if (MACRO_CALL(UI::Helpers_Func::TicksSinceCounterStart)() == 0) {
                    return;
                }
                MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(0, 0, 0);
                MACRO_CALL(UI::Rendering_Func::RenderHistoryBookEdgeUnk)();
                int blendStrength = 0;
                if (DAT_00ed2780::instance == 1) {
                    blendStrength = 31 - (int)FLOAT_00ec0834::instance;
                } else if (DAT_00ed2780::instance == 2) {
                    blendStrength = (int)FLOAT_00ec0834::instance;
                }
                MACRO_CALL(UI::Rendering_Func::DrawLoadedMenuStringHelperWithBlending)(
                    0, 280, 150, 600, 0, 17, FALSE, blendStrength);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                    DAT_ArrayOfStoredMenuStrings::instance[1],
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 30,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 280, 740, 0, 17, blendStrength);
                if (DAT_00ed2780::instance == 0) {
                    MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(DAT_00eb0b20::instance, 43, 63);
                }
                if (DAT_00ed2780::instance != 0) {
                    MACRO_CALL(UI::Rendering_Func::RenderMenuGfxHelper)(DAT_00eb0b20::instance, 43, 63, blendStrength);
                }
                if (DAT_00ed2780::instance == 0 && FLOAT_00ec0834::instance > 0.0f) {
                    FLOAT_00ec0834::instance -= FLOAT_Between1And5::instance;
                    if (FLOAT_00ec0834::instance <= 0.0f) {
                        switch (DAT_GameCore::instance.historicCampaignNumber) {
                        case 1:
                            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk,
                                DAT_SoundSystemState::ptr)("fx\\speech\\intro_01.wav", 1);
                            break;
                        case 2:
                            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk,
                                DAT_SoundSystemState::ptr)("fx\\speech\\intro_02.wav", 1);
                            break;
                        case 3:
                            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk,
                                DAT_SoundSystemState::ptr)("fx\\speech\\intro_03.wav", 1);
                            break;
                        case 4:
                            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk,
                                DAT_SoundSystemState::ptr)("fx\\speech\\intro_04.wav", 1);
                            break;
                        }
                    }
                }
                if (DAT_00ed2780::instance == 0) {
                    return;
                }
                FLOAT_00ec0834::instance += FLOAT_Between1And5::instance;
                if (FLOAT_00ec0834::instance >= 32.0f) {
                    if (DAT_00ed2780::instance == 2) {
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            UI::Enums::MVT_HISTORIC_MISSION_PICTURE, 0);
                        FLOAT_00ec0834::instance = 31.0f;
                        DAT_SoundSystemState::instance
                            .streamFlagsUnkAndLoopCount_0x34[Audio::MSS::enums::SND_STR_SPEECH_2] = 0;
                        DAT_SoundSystemState::instance
                            .streamFlagsUnkAndLoopCount_0x34[Audio::MSS::enums::SND_STR_SPEECH_1] = 0;
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                            Audio::MSS::enums::SND_STR_SPEECH_1);
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                            Audio::MSS::enums::SND_STR_SPEECH_2);
                        return;
                    }
                    DAT_00ed2780::instance = 0;
                    FLOAT_00ec0834::instance = 60.0f;
                }
            }

        }
    }
}
}
