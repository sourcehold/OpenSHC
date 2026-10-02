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

        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Game::TrailType;
        using OpenSHC::Text::GameLanguage;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004DF2E0
        void CrusadeEndscreen::MenuView_CrusadeEndscreen_Prepare()
        {
            char* pcVar1;
            undefined4 uVar2;
            SHC_SoundStream SVar3;
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("sktrail_win.tgx");
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("endframe1.tgx");
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("endframe2.tgx");
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("endframe3.tgx");
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("endframe4.tgx");
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("endframe5.tgx");
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("endframe6.tgx");
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("endframe7.tgx");
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("endframe8.tgx");
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("jesterlast.tgx");
            MACRO_CALL(OpenSHC::UI::Credits_Func::ResetCredits)();
            DAT_NumberOfStoredMenuStrings::instance = 0;
            /*
              added by script: "Congratulations!"
             */
            MACRO_CALL(OpenSHC::UI::Helpers_Func::StoreStringInMenuStringArray)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKTRAIL_WIN, 0));
            /*
              added by script: "Many have set out..."
             */
            MACRO_CALL(OpenSHC::UI::Helpers_Func::StoreStringInMenuStringArray)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKTRAIL_WIN, 1));
            /*
              added by script: "...but few will have survived this journey."
             */
            MACRO_CALL(OpenSHC::UI::Helpers_Func::StoreStringInMenuStringArray)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKTRAIL_WIN, 2));
            /*
              added by script: "You have bested the Crusader Trail!"
             */
            MACRO_CALL(OpenSHC::UI::Helpers_Func::StoreStringInMenuStringArray)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKTRAIL_WIN, 3));
            /*
              added by script: "You have bested the Crusader Extreme Trail!"
             */
            MACRO_CALL(OpenSHC::UI::Helpers_Func::StoreStringInMenuStringArray)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKTRAIL_WIN, 4));
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundEntry)(1, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsShowImageCommand)(0x29, 0, 0xe6, 0xcb, 0x150, 0xa8, 0, 1);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsTextCommand)(0xf, 0, 0xf, 1, 0x192, 0xea, 0, 1);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsTextCommand)(0xf, 0, 0xf, 0, 400, 0xe8, 0, 1);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 1, 0x6a, 0x35, 4);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "rt_vict1.bik", 0x6a, 0x35, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)("fx\\speech\\rt_anger_04.wav", 3, 0, 100);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 2, 0x14b, 0x18, 4);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "sn_vict2.bik", 0x14b, 0x18, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)("fx\\speech\\sn_add_player.wav", 3, 0, 100);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 3, 0x22d, 0x35, 4);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "pg_taunt2.bik", 0x22d, 0x35, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)("fx\\speech\\pg_add_player.wav", 3, 0, 100);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 4, 0x280, 0xdf, 4);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "wf_anger1.bik", 0x280, 0xdf, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)("fx\\speech\\wf_anger_04.wav", 3, 0, 100);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 5, 0x22d, 0x18a, 4);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "saladin_angry.bik", 0x22d, 0x18a, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)("fx\\speech\\sa_extra_01.wav", 3, 0, 100);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 6, 0x14c, 0x1b4, 4);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "sultan_natural.bik", 0x14c, 0x1b4, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)("fx\\speech\\su_congrats_01.wav", 3, 0, 100);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 7, 0x6a, 0x18a, 4);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "richard_taunting.bik", 0x6a, 0x18a, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)("fx\\speech\\ri_congrats_01.wav", 3, 0, 100);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 8, 0x23, 0xdf, 4);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "bad_arab_taunt.bik", 0x23, 0xdf, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)("fx\\speech\\ca_add_player_01.wav", 3, 0, 100);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
            uVar2 = 0x10;
            if (DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_ITALIAN) {
                uVar2 = 0x11;
            }
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsTextEndCommand)(0x10, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsTextCommand)(
                0xf, 1, (undefined4)((int)(uVar2)), 1, 0x106, 0xee, 0x11a, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsTextCommand)(
                0xf, 1, (undefined4)((int)(uVar2)), 0, 0x104, 0xec, 0x11a, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, OpenSHC::Audio::MSS::enums::SND_STR_SFX_1Unk);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, ((SHC_SoundStream)0x5a));
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsTextEndCommand)(0x10, 1);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, OpenSHC::Audio::MSS::enums::SND_STR_SFX_1Unk);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsTextCommand)(
                0xf, 2, (undefined4)((int)(uVar2)), 1, 0x106, 0xee, 0x11a, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsTextCommand)(
                0xf, 2, (undefined4)((int)(uVar2)), 0, 0x104, 0xec, 0x11a, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, OpenSHC::Audio::MSS::enums::SND_STR_SFX_2Unk);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, ((SHC_SoundStream)0x5a));
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsTextEndCommand)(0x10, 2);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, OpenSHC::Audio::MSS::enums::SND_STR_SFX_2Unk);
            if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsTextCommand)(
                    0xf, 4, (undefined4)((int)(uVar2)), 1, 0x106, 0xee, 0x11a, 0);
                MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsTextCommand)(
                    0xf, 4, (undefined4)((int)(uVar2)), 0, 0x104, 0xec, 0x11a, 0);
                SVar3 = OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2;
            } else {
                MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsTextCommand)(
                    0xf, 3, (undefined4)((int)(uVar2)), 1, 0x106, 0xee, 0x11a, 0);
                MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsTextCommand)(
                    0xf, 3, (undefined4)((int)(uVar2)), 0, 0x104, 0xec, 0x11a, 0);
                SVar3 = OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1;
            }
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, SVar3);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, OpenSHC::Audio::MSS::enums::SND_STR_SFX_1Unk);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 0x6a, 0x35, 4);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "action_jester.bik", 0x6a, 0x35, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, OpenSHC::Audio::MSS::enums::SND_STR_SFX_2Unk);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 0x14b, 0x18, 4);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "action_jester.bik", 0x14b, 0x18, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 0x22d, 0x35, 4);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "action_jester.bik", 0x22d, 0x35, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 0x280, 0xdf, 4);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "action_jester.bik", 0x280, 0xdf, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(
                8, (OpenSHC::Audio::MSS::enums::SHC_SoundStream)(OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2 | OpenSHC::Audio::MSS::enums::SND_STR_SFX_1Unk));
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 0x22d, 0x18a, 4);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "action_jester.bik", 0x22d, 0x18a, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(
                8, (OpenSHC::Audio::MSS::enums::SHC_SoundStream)(OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2 | OpenSHC::Audio::MSS::enums::SND_STR_SFX_2Unk));
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 0x14c, 0x1b4, 4);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "action_jester.bik", 0x14c, 0x1b4, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(
                8, (OpenSHC::Audio::MSS::enums::SHC_SoundStream)(OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2 | OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1));
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 0x6a, 0x18a, 4);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "action_jester.bik", 0x6a, 0x18a, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, ((SHC_SoundStream)8));
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 0x23, 0xdf, 4);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "action_jester.bik", 0x23, 0xdf, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsImageEndCommand)(0x2a, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsTextEndCommand)(0x10, 3);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSegmentEndCommand)();
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "action_jester.bik", 0x6a, 0x35, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "action_jester.bik", 0x14b, 0x18, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "action_jester.bik", 0x22d, 0x35, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "action_jester.bik", 0x280, 0xdf, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "action_jester.bik", 0x22d, 0x18a, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "action_jester.bik", 0x14c, 0x1b4, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "action_jester.bik", 0x6a, 0x18a, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsBinkVideoCommand)(0xc, "action_jester.bik", 0x23, 0xdf, 0, 0);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundStreamCommand)(0x18, OpenSHC::Audio::MSS::enums::SND_STR_MUSIC);
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsClearImageCommand)();
            MACRO_CALL(OpenSHC::Rendering_Func::TicksStartCounter)();
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
        }

    }
}
}
