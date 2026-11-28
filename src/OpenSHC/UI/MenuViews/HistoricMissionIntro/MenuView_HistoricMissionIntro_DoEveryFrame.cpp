#include "../HistoricMissionIntro.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/Audio/SFX/AmbientSFXType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00eb0b20.hpp"
#include "OpenSHC/Globals/DAT_00eb9b28.hpp"
#include "OpenSHC/Globals/DAT_00eb9b2c.hpp"
#include "OpenSHC/Globals/DAT_00eb9b30.hpp"
#include "OpenSHC/Globals/DAT_00eb9b34.hpp"
#include "OpenSHC/Globals/DAT_00eb9b38.hpp"
#include "OpenSHC/Globals/DAT_00eb9b3c.hpp"
#include "OpenSHC/Globals/DAT_00eb9b40.hpp"
#include "OpenSHC/Globals/DAT_00ed2780.hpp"
#include "OpenSHC/Globals/DAT_ArrayOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
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

        using Audio::MSS::enums::SHC_SoundStream;
        using Audio::SFX::AmbientSFXType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004DB8B0
        void HistoricMissionIntro::MenuView_HistoricMissionIntro_DoEveryFrame()
        {
            BOOLEnum BVar1;
            int iVar2;
            BVar1 = MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                DAT_SoundSystemState::ptr)(Audio::MSS::enums::SND_STR_SFX_1Unk);
            if (!BVar1) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playAmbientSoundStreamUnk, DAT_SFXState::ptr)(
                    Audio::SFX::ASFXT_WIND_0);
            }
            if (DAT_MouseState::instance.leftClickStart) {
                if (!DAT_00eb9b28::instance) {
                    DAT_00eb9b28::instance = 1;
                } else {
                    if (!DAT_00ed2780::instance) {
                        FLOAT_00ec0834::instance = 0.0;
                    } else {
                        if (DAT_00ed2780::instance != 1)
                            goto LAB_004db917;
                        FLOAT_00ec0834::instance = 31.0 - FLOAT_00ec0834::instance;
                    }
                    DAT_00ed2780::instance = 2;
                }
            }
        LAB_004db917:
            iVar2 = MACRO_CALL(UI::Helpers_Func::TicksSinceCounterStart)();
            if (!iVar2) {
                return;
            }
            MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(0, 0, 0);
            MACRO_CALL(UI::Rendering_Func::RenderHistoryBookEdgeUnk)();
            iVar2 = 0;
            if (DAT_00ed2780::instance == 1) {
                iVar2 = (long)((double)FLOAT_00ec0834::instance);
                iVar2 = 0x1f - iVar2;
            } else if (DAT_00ed2780::instance == 2) {
                iVar2 = (long)((double)FLOAT_00ec0834::instance);
            }
            if (!DAT_00ed2780::instance) {
                MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(DAT_00eb0b20::instance, 0x24, 0x56);
            } else {
                MACRO_CALL(UI::Rendering_Func::RenderMenuGfxHelper)(
                    DAT_00eb0b20::instance, 0x24, 0x56, iVar2);
            }
            if (DAT_00ed2780::instance == 2) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                    DAT_ArrayOfStoredMenuStrings::instance[DAT_00eb9b2c::instance],
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + DAT_00eb9b30::instance,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + DAT_00eb9b34::instance,
                    DAT_00eb9b38::instance, DAT_00eb9b3c::instance, DAT_00eb9b40::instance, iVar2);
            } else if (!DAT_00ed2780::instance) {
                MACRO_CALL(UI::Credits_Func::RenderScrollingCreditsTextFrame)(30.0);
            }
            MACRO_CALL(UI::Rendering_Func::DrawLoadedMenuStringHelperWithBlending)(0, 0x15e, 0xaa, 400, 0, 0x11, FALSE, iVar2);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                DAT_ArrayOfStoredMenuStrings::instance[1],
                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x15e,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xd2, 400, 0, 0x11, iVar2);
            if ((DAT_00ed2780::instance)
                && (FLOAT_00ec0834::instance = FLOAT_Between1And5::instance + FLOAT_00ec0834::instance,
                    32.0 <= FLOAT_00ec0834::instance)) {
                if (DAT_00ed2780::instance == 2) {
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
                    FLOAT_00ec0834::instance = 31.0;
                    MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                        Audio::MSS::enums::SND_STR_SFX_1Unk);
                    return;
                }
                DAT_00ed2780::instance = 0;
                if (DAT_GameCore::instance.missionNumber1to20 + -1 < 0x14) {
                    MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk, DAT_SoundSystemState::ptr)(
                        DAT_MissionDefinedData::instance
                            .HistoricMissionIntroSoundNames[DAT_GameCore::instance.missionNumber1to20 + -1],
                        1);
                }
            }
            return;
        }

    }
}
}
