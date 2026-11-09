#include "../CrusadeEndscreen.func.hpp"

#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_NumberOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DF2E0
        void CrusadeEndscreen::MenuView_CrusadeEndscreen_Prepare()
        {
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            // "sktrail_win.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_sktrail_win_tgx_005ab768);
            // "endframe1.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_endframe1_tgx_005ab758);
            // "endframe2.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_endframe2_tgx_005ab748);
            // "endframe3.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_endframe3_tgx_005ab738);
            // "endframe4.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_endframe4_tgx_005ab728);
            // "endframe5.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_endframe5_tgx_005ab718);
            // "endframe6.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_endframe6_tgx_005ab708);
            // "endframe7.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_endframe7_tgx_005ab6f8);
            // "endframe8.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_endframe8_tgx_005ab6e8);
            // "jesterlast.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_jesterlast_tgx_005ab6d8);
            MACRO_CALL(UI::Credits_Func::ResetCredits)();
            DAT_NumberOfStoredMenuStrings::instance = 0;
            // the five texts are written out: a loop over them loses (quick_diff 0.9985 -> 0.9718)
            // "Congratulations!"
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_SKTRAIL_WIN, 0));
            // "Many have set out..."
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_SKTRAIL_WIN, 1));
            // "...but few will have survived this journey."
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_SKTRAIL_WIN, 2));
            // "You have bested the Crusader Trail!"
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_SKTRAIL_WIN, 3));
            // "You have bested the Crusader Extreme Trail!"
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_SKTRAIL_WIN, 4));
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundEntry)(1, 0);
            // the repeated blocks are written out: the original has no loop here
            MACRO_CALL(UI::Credits_Func::AppendCreditsShowImageCommand)(41, 0, 230, 203, 336, 168, 0, 1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(15, 0, 15, 1, 402, 234, 0, 1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(15, 0, 15, 0, 400, 232, 0, 1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 1, 106, 53, 4);
            // "rt_vict1.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_rt_vict1_bik_005a78fc, 106, 53, 0, 0);
            // "fx\\speech\\rt_anger_04.wav"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                (char*)s_fx_speech_rt_anger_04_wav_005ab6bc, 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, 3);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 2, 331, 24, 4);
            // "sn_vict2.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_sn_vict2_bik_005a78ec, 331, 24, 0, 0);
            // "fx\\speech\\sn_add_player.wav"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                (char*)s_fx_speech_sn_add_player_wav_005ab6a0, 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, 3);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 3, 557, 53, 4);
            // "pg_taunt2.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_pg_taunt2_bik_005a7c44, 557, 53, 0, 0);
            // "fx\\speech\\pg_add_player.wav"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                (char*)s_fx_speech_pg_add_player_wav_005ab684, 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, 3);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 4, 640, 223, 4);
            // "wf_anger1.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_wf_anger1_bik_005a7b20, 640, 223, 0, 0);
            // "fx\\speech\\wf_anger_04.wav"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                (char*)s_fx_speech_wf_anger_04_wav_005ab668, 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, 3);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 5, 557, 394, 4);
            // "saladin_angry.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_saladin_angry_bik_005a7b0c, 557, 394, 0, 0);
            // "fx\\speech\\sa_extra_01.wav"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                (char*)s_fx_speech_sa_extra_01_wav_005ab64c, 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, 3);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 6, 332, 436, 4);
            // "sultan_natural.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_sultan_natural_bik_005a78a4, 332, 436, 0, 0);
            // "fx\\speech\\su_congrats_01.wav"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                (char*)s_fx_speech_su_congrats_01_wav_005ab62c, 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, 3);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 7, 106, 394, 4);
            // "richard_taunting.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_richard_taunting_bik_005a7d00, 106, 394, 0, 0);
            // "fx\\speech\\ri_congrats_01.wav"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                (char*)s_fx_speech_ri_congrats_01_wav_005ab60c, 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, 3);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 8, 35, 223, 4);
            // "bad_arab_taunt.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_bad_arab_taunt_bik_005a7d2c, 35, 223, 0, 0);
            // "fx\\speech\\ca_add_player_01.wav"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoWithAudioCommand)(
                (char*)s_fx_speech_ca_add_player_01_wav_005ab5ec, 3, 0, 100);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(4, 3);
            // 17 in Italian, 16 otherwise
            int fontSizeUnk = 16;
            if (DAT_TextManagerObject::instance.gameLanguage == Text::GL_ITALIAN) {
                fontSizeUnk = 17;
            }
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextEndCommand)(16, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(15, 1, fontSizeUnk, 1, 262, 238, 282, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(15, 1, fontSizeUnk, 0, 260, 236, 282, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, 1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, 90);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextEndCommand)(16, 1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, 1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(15, 2, fontSizeUnk, 1, 262, 238, 282, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(15, 2, fontSizeUnk, 0, 260, 236, 282, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, 2);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, 90);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextEndCommand)(16, 2);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, 2);
            if (DAT_GameCore::instance.currentTrailType == Game::TT_EXTREME) {
                MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(15, 4, fontSizeUnk, 1, 262, 238, 282, 0);
                MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(15, 4, fontSizeUnk, 0, 260, 236, 282, 0);
                MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, 4);
            } else {
                MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(15, 3, fontSizeUnk, 1, 262, 238, 282, 0);
                MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(15, 3, fontSizeUnk, 0, 260, 236, 282, 0);
                MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, 3);
            }
            // Written out too: the original has no loop here.
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, 1);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 106, 53, 4);
            // "action_jester.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_action_jester_bik_005aa504, 106, 53, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, 2);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 331, 24, 4);
            // "action_jester.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_action_jester_bik_005aa504, 331, 24, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, 3);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 557, 53, 4);
            // "action_jester.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_action_jester_bik_005aa504, 557, 53, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, 4);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 640, 223, 4);
            // "action_jester.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_action_jester_bik_005aa504, 640, 223, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, 5);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 557, 394, 4);
            // "action_jester.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_action_jester_bik_005aa504, 557, 394, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, 6);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 332, 436, 4);
            // "action_jester.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_action_jester_bik_005aa504, 332, 436, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, 7);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 106, 394, 4);
            // "action_jester.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_action_jester_bik_005aa504, 106, 394, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, 8);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(5, 9, 35, 223, 4);
            // "action_jester.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_action_jester_bik_005aa504, 35, 223, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsImageEndCommand)(42, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsTextEndCommand)(16, 3);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSegmentEndCommand)();
            // Written out too: the original has no loop here.
            // "action_jester.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_action_jester_bik_005aa504, 106, 53, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            // "action_jester.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_action_jester_bik_005aa504, 331, 24, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            // "action_jester.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_action_jester_bik_005aa504, 557, 53, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            // "action_jester.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_action_jester_bik_005aa504, 640, 223, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            // "action_jester.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_action_jester_bik_005aa504, 557, 394, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            // "action_jester.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_action_jester_bik_005aa504, 332, 436, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            // "action_jester.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_action_jester_bik_005aa504, 106, 394, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            // "action_jester.bik"
            MACRO_CALL(UI::Credits_Func::AppendCreditsBinkVideoCommand)(
                12, (char*)s_action_jester_bik_005aa504, 35, 223, 0, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(24, 0);
            MACRO_CALL(UI::Credits_Func::AppendCreditsClearImageCommand)();
            MACRO_CALL(Rendering_Func::TicksStartCounter)();
            MACRO_CALL(UI::Helpers_Func::LoadTGX_shc_back)();
        }

    }
}
}
