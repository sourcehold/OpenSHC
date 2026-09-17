// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../SettingsFileState.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
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

    // FUNCTION: STRONGHOLDCRUSADER 0x00495A30
    void SettingsFileState::readUserConfig()
    {
        DAT_GameCore::instance.missionDifficulty = 1;
        DAT_GameCore::instance.missionDifficulty2 = 1;
        DAT_GameCore::instance.missionDifficulty_2 = 1;
        DAT_GameCore::instance.missionDifficulty_3 = 1;
        DAT_GameCore::instance.missionDifficulty_1 = 1;
        DAT_GameCore::instance.missionDifficulty_0 = 1;

        MACRO_CALL(OS_Func::_memset)(DAT_GameSynchronyState::instance.ipRelatedArray, 0,
            sizeof(DAT_GameSynchronyState::instance.ipRelatedArray));

        DAT_GameCore::instance.furthestSkirmishTrailMission = 0;
        DAT_GameCore::instance.furthestWarchestTrailMission = 0;
        DAT_GameCore::instance.furthestExtremeTrailMission = 0;

        DAT_GameCore::instance.skirmishTrailProgress = 0;
        DAT_GameCore::instance.warchestTrailProgress = 0;
        DAT_GameCore::instance.extremeTrailProgress = 0;

        DAT_GameCore::instance.lordIconUnk = 2;
        DAT_GameCore::instance.selectedLordTypeUnk = 0;

        DAT_GameCore::instance.genieVoiceActive = TRUE;
        DAT_GameCore::instance.tacticalPowersDisplayFlag = 0;
        DAT_GameCore::instance.unusedOption1 = 0;

        DAT_GameCore::instance.skirmishTrailYearReached = 13200;
        DAT_GameCore::instance.warchestTrailYearReached = 13560;
        DAT_GameCore::instance.extremeTrailYearReached = 13920;

        for (int i = 0; i < sizeof(DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken)
                / sizeof(DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken[0]);
            ++i) {
            DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken[i] = -1;
        }

        for (int i = 0; i < 30; ++i) {
            DAT_GameCore::instance.warchestTrailMonthsTakenOrChicken[i] = -1;
        }

        for (int i = 0; i < 20; ++i) {
            DAT_GameCore::instance.extremeTrailMonthsTakenOrChicken[i] = -1;
        }

        char configPath[1000];
        // NOTE: Requires direct, non-resolved call due to copy elision.
        strcpy(configPath, DAT_ResourceManager::ptr->paths_getDocumentsFolderString(true).c_str());
        strcat(configPath, s_crusader_cfg_005a75bc);
        FILE* _File = MACRO_CALL(OS_Func::_fopen)(configPath, s_rb_005a4e18);

        unsigned int local_9cc = 0xffffffff;

        // NOTE: Weird stack sizes. No idea if this were truly the sizes or if something is missing here, but the
        // function fits.
        WCHAR wideCharBuffer[266];
        char charBuffer[512];
        if (_File) {
            MACRO_CALL(OS_Func::_fseek)(_File, 0, FILE_END);
            long _fileLength = MACRO_CALL(OS_Func::_ftell)(_File);
            MACRO_CALL(OS_Func::_fseek)(_File, 0, FILE_BEGIN);

            char multiByteBuffer[268];
            if (_fileLength < 1000) {

                memset(charBuffer, 0, 20);
                MACRO_CALL(OS_Func::_fread)(charBuffer, sizeof(char), 15, _File);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(5);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    charBuffer);

                memset(charBuffer, 0, 20);
                MACRO_CALL(OS_Func::_fread)(charBuffer, sizeof(char), 5, _File);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(6);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    charBuffer);

                memset(charBuffer, 0, 20);
                MACRO_CALL(OS_Func::_fread)(charBuffer, sizeof(char), 15, _File);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(7);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    charBuffer);

                memset(charBuffer, 0, 20);
                MACRO_CALL(OS_Func::_fread)(charBuffer, sizeof(char), 256, _File);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0);

                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    charBuffer);
            } else {

                memset(wideCharBuffer, 0, 20 * sizeof(WCHAR));
                MACRO_CALL(OS_Func::_fread)(wideCharBuffer, sizeof(WCHAR), 15, _File);
                MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                    DAT_WideCharMultiByteState::ptr)(multiByteBuffer, wideCharBuffer, 15);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(5);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    multiByteBuffer);

                memset(wideCharBuffer, 0, 20 * sizeof(WCHAR));
                MACRO_CALL(OS_Func::_fread)(wideCharBuffer, sizeof(WCHAR), 5, _File);
                MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                    DAT_WideCharMultiByteState::ptr)(multiByteBuffer, wideCharBuffer, 5);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(6);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    multiByteBuffer);

                memset(wideCharBuffer, 0, 20 * sizeof(WCHAR));
                MACRO_CALL(OS_Func::_fread)(wideCharBuffer, sizeof(WCHAR), 15, _File);
                MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                    DAT_WideCharMultiByteState::ptr)(multiByteBuffer, wideCharBuffer, 15);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(7);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    multiByteBuffer);

                memset(wideCharBuffer, 0, 20 * sizeof(WCHAR));
                MACRO_CALL(OS_Func::_fread)(wideCharBuffer, sizeof(WCHAR), 256, _File);
                MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                    DAT_WideCharMultiByteState::ptr)(multiByteBuffer, wideCharBuffer, 256);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0);

                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    multiByteBuffer);
            }

            MACRO_CALL(OS_Func::_fread)(
                &DAT_GameCore::instance.gameSpeedLevel, sizeof(DAT_GameCore::instance.gameSpeedLevel), 1, _File);

            MACRO_CALL(OS_Func::_fread)(
                &DAT_GameCore::instance.settingBubbleHelp, sizeof(DAT_GameCore::instance.settingBubbleHelp), 1, _File);
            MACRO_CALL(OS_Func::_fread)(&local_9cc, sizeof(local_9cc), 1, _File);
            MACRO_CALL(OS_Func::_fread)(&DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk,
                sizeof(DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk), 1, _File);
            MACRO_CALL(OS_Func::_fread)(&DAT_ScrollingHandler::instance.scrollSpeedSetting_0x38,
                sizeof(DAT_ScrollingHandler::instance.scrollSpeedSetting_0x38), 1, _File);

            MACRO_CALL(OS_Func::_fread)(&DAT_SoundSystemState::instance.soundActiveUnk_0x0,
                sizeof(DAT_SoundSystemState::instance.soundActiveUnk_0x0), 1, _File);
            MACRO_CALL(OS_Func::_fread)(&DAT_SoundSystemState::instance.streamVolume[0],
                sizeof(DAT_SoundSystemState::instance.streamVolume[0]), 1, _File);
            MACRO_CALL(OS_Func::_fread)(&DAT_SoundSystemState::instance.streamVolume[1],
                sizeof(DAT_SoundSystemState::instance.streamVolume[1]), 1, _File);
            MACRO_CALL(OS_Func::_fread)(&DAT_SoundSystemState::instance.streamVolume[3],
                sizeof(DAT_SoundSystemState::instance.streamVolume[3]), 1, _File);
            DAT_SoundSystemState::instance.streamVolume[4] = DAT_SoundSystemState::instance.streamVolume[3];
            DAT_SoundSystemState::instance.sampleVolume = DAT_SoundSystemState::instance.streamVolume[3];

            MACRO_CALL(OS_Func::_fread)(
                &DAT_GameCore::instance.scenarioProgress, sizeof(DAT_GameCore::instance.scenarioProgress), 1, _File);
            MACRO_CALL(OS_Func::_fread)(
                &DAT_GameCore::instance.furthestMission, sizeof(DAT_GameCore::instance.furthestMission), 1, _File);

            MACRO_CALL(OS_Func::_fread)(
                &DAT_GameCore::instance.unused1, sizeof(DAT_GameCore::instance.unused1), 1, _File);

            MACRO_CALL(OS_Func::_fread)(&DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes,
                sizeof(DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes), 1, _File);

            MACRO_CALL(OS_Func::_fread)(
                &DAT_GameCore::instance.missionDifficulty, sizeof(DAT_GameCore::instance.missionDifficulty), 1, _File);

            MACRO_CALL(OS_Func::_fread)(&DAT_GameCore::instance.missionDifficulty2,
                sizeof(DAT_GameCore::instance.missionDifficulty2), 1, _File);
            MACRO_CALL(OS_Func::_fread)(&DAT_GameCore::instance.missionDifficulty_2,
                sizeof(DAT_GameCore::instance.missionDifficulty_2), 1, _File);
            MACRO_CALL(OS_Func::_fread)(&DAT_GameCore::instance.missionDifficulty_3,
                sizeof(DAT_GameCore::instance.missionDifficulty_3), 1, _File);
            MACRO_CALL(OS_Func::_fread)(&DAT_GameCore::instance.missionDifficulty_1,
                sizeof(DAT_GameCore::instance.missionDifficulty_1), 1, _File);
            MACRO_CALL(OS_Func::_fread)(&DAT_GameCore::instance.missionDifficulty_0,
                sizeof(DAT_GameCore::instance.missionDifficulty_0), 1, _File);

            MACRO_CALL(OS_Func::_fread)(
                &DAT_MouseState::instance.cursorType, sizeof(DAT_MouseState::instance.cursorType), 1, _File);

            if (_fileLength < 1000) {
                MACRO_CALL(OS_Func::_fread)(DAT_GameSynchronyState::instance.ipRelatedArray, 1,
                    sizeof(DAT_GameSynchronyState::instance.ipRelatedArray), _File);
            } else {
                WCHAR ipRelatedArrayWideChar[4][20];

                MACRO_CALL(OS_Func::_fread)(
                    ipRelatedArrayWideChar, sizeof(WCHAR), sizeof(ipRelatedArrayWideChar) / sizeof(WCHAR), _File);
                MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                    DAT_WideCharMultiByteState::ptr)(DAT_GameSynchronyState::instance.ipRelatedArray[0],
                    ipRelatedArrayWideChar[0], sizeof(DAT_GameSynchronyState::instance.ipRelatedArray[0]));
                MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                    DAT_WideCharMultiByteState::ptr)(DAT_GameSynchronyState::instance.ipRelatedArray[1],
                    ipRelatedArrayWideChar[1], sizeof(DAT_GameSynchronyState::instance.ipRelatedArray[1]));
                MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                    DAT_WideCharMultiByteState::ptr)(DAT_GameSynchronyState::instance.ipRelatedArray[2],
                    ipRelatedArrayWideChar[2], sizeof(DAT_GameSynchronyState::instance.ipRelatedArray[2]));
                MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                    DAT_WideCharMultiByteState::ptr)(DAT_GameSynchronyState::instance.ipRelatedArray[3],
                    ipRelatedArrayWideChar[3], sizeof(DAT_GameSynchronyState::instance.ipRelatedArray[3]));
            }

            MACRO_CALL(OS_Func::_fread)(&DAT_GameCore::instance.furthestSkirmishTrailMission,
                sizeof(DAT_GameCore::instance.furthestSkirmishTrailMission), 1, _File);

            MACRO_CALL(OS_Func::_fread)(
                &DAT_GameCore::instance.lordIconUnk, sizeof(DAT_GameCore::instance.lordIconUnk), 1, _File);
            if (DAT_GameCore::instance.lordIconUnk < 2) {
                DAT_GameCore::instance.lordIconUnk = 2;
            }

            MACRO_CALL(OS_Func::_fread)(&DAT_GameCore::instance.skirmishTrailProgress,
                sizeof(DAT_GameCore::instance.skirmishTrailProgress), 1, _File);
            MACRO_CALL(OS_Func::_fread)(&DAT_GameCore::instance.selectedLordTypeUnk,
                sizeof(DAT_GameCore::instance.selectedLordTypeUnk), 1, _File);
            MACRO_CALL(OS_Func::_fread)(&DAT_GameCore::instance.skirmishTrailYearReached,
                sizeof(DAT_GameCore::instance.skirmishTrailYearReached), 1, _File);

            MACRO_CALL(OS_Func::_fread)(DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken,
                sizeof(DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken[0]),
                sizeof(DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken)
                    / sizeof(DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken[0]),
                _File);

            MACRO_CALL(OS_Func::_fread)(
                &DAT_GameCore::instance.genieVoiceActive, sizeof(DAT_GameCore::instance.genieVoiceActive), 1, _File);

            MACRO_CALL(OS_Func::_fread)(&DAT_GameCore::instance.furthestWarchestTrailMission,
                sizeof(DAT_GameCore::instance.furthestWarchestTrailMission), 1, _File);
            MACRO_CALL(OS_Func::_fread)(&DAT_GameCore::instance.warchestTrailProgress,
                sizeof(DAT_GameCore::instance.warchestTrailProgress), 1, _File);
            MACRO_CALL(OS_Func::_fread)(&DAT_GameCore::instance.warchestTrailYearReached,
                sizeof(DAT_GameCore::instance.warchestTrailYearReached), 1, _File);
            MACRO_CALL(OS_Func::_fread)(DAT_GameCore::instance.warchestTrailMonthsTakenOrChicken,
                sizeof(DAT_GameCore::instance.warchestTrailMonthsTakenOrChicken[0]), 30, _File);

            MACRO_CALL(OS_Func::_fread)(&DAT_GameCore::instance.furthestExtremeTrailMission,
                sizeof(DAT_GameCore::instance.furthestExtremeTrailMission), 1, _File);
            MACRO_CALL(OS_Func::_fread)(&DAT_GameCore::instance.extremeTrailProgress,
                sizeof(DAT_GameCore::instance.extremeTrailProgress), 1, _File);
            MACRO_CALL(OS_Func::_fread)(&DAT_GameCore::instance.extremeTrailYearReached,
                sizeof(DAT_GameCore::instance.extremeTrailYearReached), 1, _File);
            MACRO_CALL(OS_Func::_fread)(DAT_GameCore::instance.extremeTrailMonthsTakenOrChicken,
                sizeof(DAT_GameCore::instance.extremeTrailMonthsTakenOrChicken[0]), 30, _File);

            MACRO_CALL(OS_Func::_fread)(&DAT_GameCore::instance.tacticalPowersDisplayFlag,
                sizeof(DAT_GameCore::instance.tacticalPowersDisplayFlag), 1, _File);
            MACRO_CALL(OS_Func::_fread)(
                &DAT_GameCore::instance.unusedOption1, sizeof(DAT_GameCore::instance.unusedOption1), 1, _File);

            MACRO_CALL(OS_Func::_fread)(&DAT_WindowAndDirectDraw::instance.currentGameResolution,
                sizeof(DAT_WindowAndDirectDraw::instance.currentGameResolution), 1, _File);

            MACRO_CALL(OS_Func::_fclose)(_File);
            DAT_SoundSystemState::instance.streamVolume[2] = DAT_SoundSystemState::instance.streamVolume[1];
        } else {
            MACRO_CALL(OS_Func::_memset)(charBuffer, 0, 256);

            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(5);
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(charBuffer);
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(6);
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(charBuffer);
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(7);
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(charBuffer);
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0);
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(charBuffer);

            DAT_SoundSystemState::instance.streamVolume[2] = 80;
            DAT_SoundSystemState::instance.streamVolume[1] = 80;
            DAT_SoundSystemState::instance.streamVolume[0] = 90;
            DAT_SoundSystemState::instance.streamVolume[3] = 85;
            DAT_SoundSystemState::instance.streamVolume[4] = 85;
            DAT_SoundSystemState::instance.sampleVolume = 100;

            DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes = 10;
            DAT_MouseState::instance.cursorType = 0;
            DAT_SoundSystemState::instance.soundActiveUnk_0x0 = 1;
        }
        DAT_GameCore::instance.unusedOption1 = 0;
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
        DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk = 0;
        MACRO_CALL_MEMBER(Game::GameCore_Func::setStartDateUnk, DAT_GameCore::ptr)(0);
    }

}
}
