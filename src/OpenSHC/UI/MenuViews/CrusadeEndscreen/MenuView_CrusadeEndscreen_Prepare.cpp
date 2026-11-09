#include "../CrusadeEndscreen.func.hpp"

#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_NumberOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using Audio::MSS::enums::SHC_SoundStream;

        // FUNCTION: STRONGHOLDCRUSADER 0x004DF2E0
        void CrusadeEndscreen::MenuView_CrusadeEndscreen_Prepare()
        {
            undefined4 uVar2;
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "sktrail_win.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "endframe1.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "endframe2.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "endframe3.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "endframe4.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "endframe5.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "endframe6.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "endframe7.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "endframe8.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "jesterlast.tgx");
            MACRO_CALL(UI::Credits_Func::ResetCredits)();
            DAT_NumberOfStoredMenuStrings::instance = 0;
            /*
              added by script: "Congratulations!"
             */
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_SKTRAIL_WIN, 0));
            /*
              added by script: "Many have set out..."
             */
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_SKTRAIL_WIN, 1));
            /*
              added by script: "...but few will have survived this journey."
             */
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_SKTRAIL_WIN, 2));
            /*
              added by script: "You have bested the Crusader Trail!"
             */
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_SKTRAIL_WIN, 3));
            /*
              added by script: "You have bested the Crusader Extreme Trail!"
             */
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_SKTRAIL_WIN, 4));
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundEntry)(1, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsShowImageCommand)(41, 0, 230, 203, 336, 168, 0, 1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(0xf, 0, 0xf, 1, 402, 234, 0, 1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(0xf, 0, 0xf, 0, 400, 232, 0, 1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 1, 106, 53, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "rt_vict1.bik", 106, 53, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                "fx\\speech\\rt_anger_04.wav", 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 2, 331, 24, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "sn_vict2.bik", 331, 24, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                "fx\\speech\\sn_add_player.wav", 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 3, 557, 53, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "pg_taunt2.bik", 557, 53, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                "fx\\speech\\pg_add_player.wav", 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 4, 640, 223, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "wf_anger1.bik", 640, 223, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                "fx\\speech\\wf_anger_04.wav", 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 5, 557, 394, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "saladin_angry.bik", 557, 394, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                "fx\\speech\\sa_extra_01.wav", 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 6, 332, 436, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "sultan_natural.bik", 332, 436, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                "fx\\speech\\su_congrats_01.wav", 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 7, 106, 394, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "richard_taunting.bik", 106, 394, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                "fx\\speech\\ri_congrats_01.wav", 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 8, 35, 223, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "bad_arab_taunt.bik", 35, 223, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                "fx\\speech\\ca_add_player_01.wav", 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, Audio::MSS::enums::SND_STR_SPEECH_1);
            uVar2 = 16;
            if (DAT_TextManagerObject::instance.gameLanguage == Text::GL_ITALIAN) {
                uVar2 = 17;
            }
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextEndCommand)(16, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(
                0xf, 1, (undefined4)((int)(uVar2)), 1, 262, 238, 282, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(
                0xf, 1, (undefined4)((int)(uVar2)), 0, 260, 236, 282, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, Audio::MSS::enums::SND_STR_SFX_1Unk);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, ((SHC_SoundStream)90));
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextEndCommand)(16, 1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, Audio::MSS::enums::SND_STR_SFX_1Unk);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(
                0xf, 2, (undefined4)((int)(uVar2)), 1, 262, 238, 282, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(
                0xf, 2, (undefined4)((int)(uVar2)), 0, 260, 236, 282, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, Audio::MSS::enums::SND_STR_SFX_2Unk);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, ((SHC_SoundStream)90));
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextEndCommand)(16, 2);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, Audio::MSS::enums::SND_STR_SFX_2Unk);
            if (DAT_GameCore::instance.currentTrailType == Game::TT_EXTREME) {
                MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(
                    0xf, 4, (undefined4)((int)(uVar2)), 1, 262, 238, 282, 0);
                MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(
                    0xf, 4, (undefined4)((int)(uVar2)), 0, 260, 236, 282, 0);
                MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, Audio::MSS::enums::SND_STR_SPEECH_2);
            } else {
                MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(
                    0xf, 3, (undefined4)((int)(uVar2)), 1, 262, 238, 282, 0);
                MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(
                    0xf, 3, (undefined4)((int)(uVar2)), 0, 260, 236, 282, 0);
                MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, Audio::MSS::enums::SND_STR_SPEECH_1);
            }
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, Audio::MSS::enums::SND_STR_SFX_1Unk);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 106, 53, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "action_jester.bik", 106, 53, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, Audio::MSS::enums::SND_STR_SFX_2Unk);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 331, 24, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "action_jester.bik", 331, 24, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 557, 53, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "action_jester.bik", 557, 53, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, Audio::MSS::enums::SND_STR_SPEECH_2);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 640, 223, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "action_jester.bik", 640, 223, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8,
                (Audio::MSS::enums::SHC_SoundStream)(Audio::MSS::enums::SND_STR_SPEECH_2
                    | Audio::MSS::enums::SND_STR_SFX_1Unk));
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 557, 394, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "action_jester.bik", 557, 394, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8,
                (Audio::MSS::enums::SHC_SoundStream)(Audio::MSS::enums::SND_STR_SPEECH_2
                    | Audio::MSS::enums::SND_STR_SFX_2Unk));
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 332, 436, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "action_jester.bik", 332, 436, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8,
                (Audio::MSS::enums::SHC_SoundStream)(Audio::MSS::enums::SND_STR_SPEECH_2
                    | Audio::MSS::enums::SND_STR_SPEECH_1));
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 106, 394, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "action_jester.bik", 106, 394, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, ((SHC_SoundStream)8));
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 35, 223, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "action_jester.bik", 35, 223, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageEndCommand)(42, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextEndCommand)(16, 3);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSegmentEndCommand)();
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "action_jester.bik", 106, 53, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "action_jester.bik", 331, 24, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "action_jester.bik", 557, 53, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "action_jester.bik", 640, 223, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "action_jester.bik", 557, 394, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "action_jester.bik", 332, 436, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "action_jester.bik", 106, 394, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(12, "action_jester.bik", 35, 223, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(UI::Credits_Func::AppendCreditsClearImageCommand)();
            MACRO_CALL(Rendering_Func::TicksStartCounter)();
            MACRO_CALL(UI::Helpers_Func::LoadTGX_shc_back)();
        }

    }
}
}
