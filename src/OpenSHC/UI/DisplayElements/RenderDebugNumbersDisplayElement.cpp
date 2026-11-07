#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_CurrentFramerate.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameLoopDurationBuffer.hpp"
#include "OpenSHC/Globals/DAT_GameLoopStopwatch.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TickRateBuffer.hpp"
#include "OpenSHC/Globals/INT_GameLoopTimeDataIndex.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004AF860
    void DisplayElements::RenderDebugNumbersDisplayElement(int posX, int posY, DWORD elementState)
    {
        int* _millisecLoopPointer;
        int _tickRateSum;
        int _averageMillisecLoopMain;
        dword _lastGameLoopDuration;
        dword _lastGameTickRate;
        int _loopAddressByteCounter;
        _lastGameTickRate = DAT_GameCore::instance.gameTicksThisLoop;
        _lastGameLoopDuration = DAT_GameLoopStopwatch::instance.duration_0x0;
        DAT_GameLoopDurationBuffer::instance[INT_GameLoopTimeDataIndex::instance] = _lastGameLoopDuration;
        DAT_TickRateBuffer::instance[INT_GameLoopTimeDataIndex::instance] = _lastGameTickRate;
        ++INT_GameLoopTimeDataIndex::instance;
        _tickRateSum = 0;
        int _gameLoopDurationBufferSum = 0;
        if (INT_GameLoopTimeDataIndex::instance == 100) {
            INT_GameLoopTimeDataIndex::instance = 0;
        }
        // Maybe this is an enrolled loop? -TheRedDaemon
        int _loopIndex = 0;
        do {
            _gameLoopDurationBufferSum = _gameLoopDurationBufferSum + DAT_GameLoopDurationBuffer::instance[_loopIndex]
                + DAT_GameLoopDurationBuffer::instance[_loopIndex + 1]
                + DAT_GameLoopDurationBuffer::instance[_loopIndex + 2]
                + DAT_GameLoopDurationBuffer::instance[_loopIndex + 4]
                + DAT_GameLoopDurationBuffer::instance[_loopIndex + 3];
            _tickRateSum = _tickRateSum + DAT_TickRateBuffer::instance[_loopIndex + 4]
                + DAT_TickRateBuffer::instance[_loopIndex + 3] + DAT_TickRateBuffer::instance[_loopIndex + 2]
                + DAT_TickRateBuffer::instance[_loopIndex + 1] + DAT_TickRateBuffer::instance[_loopIndex];
            _loopIndex += 5;
        } while (_loopIndex < 100);
        _averageMillisecLoopMain = _gameLoopDurationBufferSum / 100;
        if ((int)elementState != -1000) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                _lastGameLoopDuration, posX, posY + 5, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_0080FF,
                0, 15, FALSE, 0);
        }
        int _maxLoopDurationOfTheLast100 = -1;
        _millisecLoopPointer = DAT_GameLoopDurationBuffer::instance;
        do {
            if (_millisecLoopPointer[0] > _maxLoopDurationOfTheLast100) {
                _maxLoopDurationOfTheLast100 = _millisecLoopPointer[0];
            }
            if (_millisecLoopPointer[1] > _maxLoopDurationOfTheLast100) {
                _maxLoopDurationOfTheLast100 = _millisecLoopPointer[1];
            }
            if (_millisecLoopPointer[2] > _maxLoopDurationOfTheLast100) {
                _maxLoopDurationOfTheLast100
                    = _millisecLoopPointer[2]; // written out as in the draft; not tried as a loop
            }
            if (_millisecLoopPointer[3] > _maxLoopDurationOfTheLast100) {
                _maxLoopDurationOfTheLast100 = _millisecLoopPointer[3];
            }
            if (_millisecLoopPointer[4] > _maxLoopDurationOfTheLast100) {
                _maxLoopDurationOfTheLast100 = _millisecLoopPointer[4];
            }
            _millisecLoopPointer += 5;
        } while (_millisecLoopPointer < DAT_GameLoopDurationBuffer::instance + 100);
        if ((int)elementState != -1000) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                _averageMillisecLoopMain, posX + 48, posY, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 0, 17, FALSE, 0);
        }
        if (_averageMillisecLoopMain == 0) {
            _averageMillisecLoopMain = 1;
        }
        if ((int)elementState != -1000) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                1000 / _averageMillisecLoopMain, posX + 48, posY + 20, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 0, 17, FALSE, 0);
        }
        DAT_CurrentFramerate::instance = 1000 / _averageMillisecLoopMain;
        if (_tickRateSum == 0) {
            _tickRateSum = 1;
        }
        int _someRelationBetweenLoopDurationAndTickrate = _gameLoopDurationBufferSum / _tickRateSum;
        if (_someRelationBetweenLoopDurationAndTickrate == 0) {
            _someRelationBetweenLoopDurationAndTickrate = 1;
        }
        if ((int)elementState != -1000) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                1000 / _someRelationBetweenLoopDurationAndTickrate, posX + 48, posY + 40, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 0, 17, FALSE, 0);
        }
    }

}
}
