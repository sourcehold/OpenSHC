// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../SettingsFileState.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00496400
    void SettingsFileState::writeUserConfig()
    {
        char configPath[1000];
        // NOTE: Requires direct, non-resolved call due to copy elision.
        strcpy(configPath, DAT_ResourceManager::ptr->paths_getDocumentsFolderString(true).c_str());
        strcat(configPath, s_crusader_cfg_005a75bc);

        FILE* _File = MACRO_CALL(OS_Func::_fopen)(configPath, s_wb_005a5510);
        if (!_File) {
            return;
        }
        WCHAR _wideCharBuffer[265];

        MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::multiByteToWideCharThunk, DAT_WideCharMultiByteState::ptr)(
            _wideCharBuffer,
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(5), 15);
        MACRO_CALL(OS_Func::_fwrite)(_wideCharBuffer, sizeof(WCHAR), 15, _File);

        MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::multiByteToWideCharThunk, DAT_WideCharMultiByteState::ptr)(
            _wideCharBuffer,
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(6), 5);
        MACRO_CALL(OS_Func::_fwrite)(_wideCharBuffer, sizeof(WCHAR), 5, _File);

        MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::multiByteToWideCharThunk, DAT_WideCharMultiByteState::ptr)(
            _wideCharBuffer,
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(7), 15);
        MACRO_CALL(OS_Func::_fwrite)(_wideCharBuffer, sizeof(WCHAR), 15, _File);

        MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::multiByteToWideCharThunk, DAT_WideCharMultiByteState::ptr)(
            _wideCharBuffer,
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0), 256);
        MACRO_CALL(OS_Func::_fwrite)(_wideCharBuffer, sizeof(WCHAR), 256, _File);

        MACRO_CALL(OS_Func::_fwrite)(
            &DAT_GameCore::instance.gameSpeedLevel, sizeof(DAT_GameCore::instance.gameSpeedLevel), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(
            &DAT_GameCore::instance.settingBubbleHelp, sizeof(DAT_GameCore::instance.settingBubbleHelp), 1, _File);

        MACRO_CALL(OS_Func::_fwrite)(&DAT_WindowAndDirectDraw::instance.currentGameResolution,
            sizeof(DAT_WindowAndDirectDraw::instance.currentGameResolution), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(&DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk,
            sizeof(DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(&DAT_ScrollingHandler::instance.scrollSpeedSetting_0x38,
            sizeof(DAT_ScrollingHandler::instance.scrollSpeedSetting_0x38), 1, _File);

        MACRO_CALL(OS_Func::_fwrite)(&DAT_SoundSystemState::instance.soundActiveUnk_0x0,
            sizeof(DAT_SoundSystemState::instance.soundActiveUnk_0x0), 1, _File);

        MACRO_CALL(OS_Func::_fwrite)(&DAT_SoundSystemState::instance.streamVolume[0],
            sizeof(DAT_SoundSystemState::instance.streamVolume[0]), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(&DAT_SoundSystemState::instance.streamVolume[1],
            sizeof(DAT_SoundSystemState::instance.streamVolume[1]), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(&DAT_SoundSystemState::instance.streamVolume[3],
            sizeof(DAT_SoundSystemState::instance.streamVolume[3]), 1, _File);

        MACRO_CALL(OS_Func::_fwrite)(
            &DAT_GameCore::instance.scenarioProgress, sizeof(DAT_GameCore::instance.scenarioProgress), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(
            &DAT_GameCore::instance.furthestMission, sizeof(DAT_GameCore::instance.furthestMission), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(&DAT_GameCore::instance.unused1, sizeof(DAT_GameCore::instance.unused1), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(&DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes,
            sizeof(DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes), 1, _File);

        MACRO_CALL(OS_Func::_fwrite)(
            &DAT_GameCore::instance.missionDifficulty, sizeof(DAT_GameCore::instance.missionDifficulty), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(
            &DAT_GameCore::instance.missionDifficulty2, sizeof(DAT_GameCore::instance.missionDifficulty2), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(
            &DAT_GameCore::instance.missionDifficulty_2, sizeof(DAT_GameCore::instance.missionDifficulty_2), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(
            &DAT_GameCore::instance.missionDifficulty_3, sizeof(DAT_GameCore::instance.missionDifficulty_3), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(
            &DAT_GameCore::instance.missionDifficulty_1, sizeof(DAT_GameCore::instance.missionDifficulty_1), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(
            &DAT_GameCore::instance.missionDifficulty_0, sizeof(DAT_GameCore::instance.missionDifficulty_0), 1, _File);

        MACRO_CALL(OS_Func::_fwrite)(
            &DAT_MouseState::instance.cursorType, sizeof(DAT_MouseState::instance.cursorType), 1, _File);

        MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::multiByteToWideCharThunk, DAT_WideCharMultiByteState::ptr)(
            _wideCharBuffer, DAT_GameSynchronyState::instance.ipRelatedArray[0],
            sizeof(DAT_GameSynchronyState::instance.ipRelatedArray[0]));
        MACRO_CALL(OS_Func::_fwrite)(
            _wideCharBuffer, sizeof(WCHAR), sizeof(DAT_GameSynchronyState::instance.ipRelatedArray[0]), _File);

        MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::multiByteToWideCharThunk, DAT_WideCharMultiByteState::ptr)(
            _wideCharBuffer, DAT_GameSynchronyState::instance.ipRelatedArray[1],
            sizeof(DAT_GameSynchronyState::instance.ipRelatedArray[1]));
        MACRO_CALL(OS_Func::_fwrite)(
            _wideCharBuffer, sizeof(WCHAR), sizeof(DAT_GameSynchronyState::instance.ipRelatedArray[1]), _File);

        MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::multiByteToWideCharThunk, DAT_WideCharMultiByteState::ptr)(
            _wideCharBuffer, DAT_GameSynchronyState::instance.ipRelatedArray[2],
            sizeof(DAT_GameSynchronyState::instance.ipRelatedArray[2]));
        MACRO_CALL(OS_Func::_fwrite)(
            _wideCharBuffer, sizeof(WCHAR), sizeof(DAT_GameSynchronyState::instance.ipRelatedArray[2]), _File);

        MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::multiByteToWideCharThunk, DAT_WideCharMultiByteState::ptr)(
            _wideCharBuffer, DAT_GameSynchronyState::instance.ipRelatedArray[3],
            sizeof(DAT_GameSynchronyState::instance.ipRelatedArray[3]));
        MACRO_CALL(OS_Func::_fwrite)(
            _wideCharBuffer, sizeof(WCHAR), sizeof(DAT_GameSynchronyState::instance.ipRelatedArray[3]), _File);

        MACRO_CALL(OS_Func::_fwrite)(&DAT_GameCore::instance.furthestSkirmishTrailMission,
            sizeof(DAT_GameCore::instance.furthestSkirmishTrailMission), 1, _File);

        MACRO_CALL(OS_Func::_fwrite)(
            &DAT_GameCore::instance.lordIconUnk, sizeof(DAT_GameCore::instance.lordIconUnk), 1, _File);

        MACRO_CALL(OS_Func::_fwrite)(&DAT_GameCore::instance.skirmishTrailProgress,
            sizeof(DAT_GameCore::instance.skirmishTrailProgress), 1, _File);

        MACRO_CALL(OS_Func::_fwrite)(
            &DAT_GameCore::instance.selectedLordTypeUnk, sizeof(DAT_GameCore::instance.selectedLordTypeUnk), 1, _File);

        MACRO_CALL(OS_Func::_fwrite)(&DAT_GameCore::instance.skirmishTrailYearReached,
            sizeof(DAT_GameCore::instance.skirmishTrailYearReached), 1, _File);

        MACRO_CALL(OS_Func::_fwrite)(DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken,
            sizeof(DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken[0]),
            sizeof(DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken)
                / sizeof(DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken[0]),
            _File);

        MACRO_CALL(OS_Func::_fwrite)(
            &DAT_GameCore::instance.genieVoiceActive, sizeof(DAT_GameCore::instance.genieVoiceActive), 1, _File);

        MACRO_CALL(OS_Func::_fwrite)(&DAT_GameCore::instance.furthestWarchestTrailMission,
            sizeof(DAT_GameCore::instance.furthestWarchestTrailMission), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(&DAT_GameCore::instance.warchestTrailProgress,
            sizeof(DAT_GameCore::instance.warchestTrailProgress), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(&DAT_GameCore::instance.warchestTrailYearReached,
            sizeof(DAT_GameCore::instance.warchestTrailYearReached), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(DAT_GameCore::instance.warchestTrailMonthsTakenOrChicken,
            sizeof(DAT_GameCore::instance.warchestTrailMonthsTakenOrChicken[0]), 30, _File);

        MACRO_CALL(OS_Func::_fwrite)(&DAT_GameCore::instance.furthestExtremeTrailMission,
            sizeof(DAT_GameCore::instance.furthestExtremeTrailMission), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(&DAT_GameCore::instance.extremeTrailProgress,
            sizeof(DAT_GameCore::instance.extremeTrailProgress), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(&DAT_GameCore::instance.extremeTrailYearReached,
            sizeof(DAT_GameCore::instance.extremeTrailYearReached), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(DAT_GameCore::instance.extremeTrailMonthsTakenOrChicken,
            sizeof(DAT_GameCore::instance.extremeTrailMonthsTakenOrChicken[0]), 30, _File);

        MACRO_CALL(OS_Func::_fwrite)(&DAT_GameCore::instance.tacticalPowersDisplayFlag,
            sizeof(DAT_GameCore::instance.tacticalPowersDisplayFlag), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(
            &DAT_GameCore::instance.unusedOption1, sizeof(DAT_GameCore::instance.unusedOption1), 1, _File);
        MACRO_CALL(OS_Func::_fwrite)(&DAT_WindowAndDirectDraw::instance.currentGameResolution,
            sizeof(DAT_WindowAndDirectDraw::instance.currentGameResolution), 1, _File);

        MACRO_CALL(OS_Func::_fclose)(_File);
    }

}
}
