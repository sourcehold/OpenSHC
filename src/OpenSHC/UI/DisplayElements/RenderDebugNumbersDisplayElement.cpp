#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
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

    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004AF860
    void DisplayElements::RenderDebugNumbersDisplayElement(int posX, int posY, DWORD elementState)
    {
        int _loopEndCondition;
        int _maxLoopDurationOfTheLast100;
        int _someRelationBetweenLoopDurationAndTickrate;
        int _gameLoopDurationBufferSum;
        int* _millisecLoopPointer;
        int _tickRateSum;
        int _averageMillisecLoopMain;
        dword _lastGameLoopDuration;
        dword _lastGameTickRate;
        int _loopAddressByteCounter;
        _lastGameTickRate = DAT_GameCore::instance.gameTicksThisLoop;
        _lastGameLoopDuration = DAT_GameLoopStopwatch::instance.duration_0x0;
        DAT_GameLoopDurationBuffer::instance[INT_GameLoopTimeDataIndex::instance]
            = DAT_GameLoopStopwatch::instance.duration_0x0;
        DAT_TickRateBuffer::instance[INT_GameLoopTimeDataIndex::instance] = _lastGameTickRate;
        INT_GameLoopTimeDataIndex::instance = INT_GameLoopTimeDataIndex::instance + 1;
        _tickRateSum = 0;
        _gameLoopDurationBufferSum = 0;
        if (INT_GameLoopTimeDataIndex::instance == 100) {
            INT_GameLoopTimeDataIndex::instance = 0;
        }
        /*
          Maybe this is an enrolled loop? -TheRedDaemon
         */
        _loopAddressByteCounter = 0;
        do {
            _loopEndCondition = _loopAddressByteCounter + 0x14;
            _gameLoopDurationBufferSum = _gameLoopDurationBufferSum
                + *(int*)((int)DAT_GameLoopDurationBuffer::instance + _loopAddressByteCounter)
                + *(int*)((int)DAT_GameLoopDurationBuffer::instance + _loopAddressByteCounter + 4)
                + *(int*)((int)DAT_GameLoopDurationBuffer::instance + _loopAddressByteCounter + 8)
                + *(int*)((int)DAT_GameLoopDurationBuffer::instance + _loopAddressByteCounter + 0x10)
                + *(int*)((int)DAT_GameLoopDurationBuffer::instance + _loopAddressByteCounter + 0xc);
            _tickRateSum = _tickRateSum + *(int*)((int)DAT_TickRateBuffer::instance + _loopAddressByteCounter + 0x10)
                + *(int*)((int)DAT_TickRateBuffer::instance + _loopAddressByteCounter + 0xc)
                + *(int*)((int)DAT_TickRateBuffer::instance + _loopAddressByteCounter + 8)
                + *(int*)((int)DAT_TickRateBuffer::instance + _loopAddressByteCounter + 4)
                + *(int*)((int)DAT_TickRateBuffer::instance + _loopAddressByteCounter);
            _loopAddressByteCounter = _loopEndCondition;
        } while (_loopEndCondition < 400);
        _averageMillisecLoopMain = _gameLoopDurationBufferSum / 100;
        if (elementState != 0xfffffc18) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                _lastGameLoopDuration, posX, posY + 5, OpenSHC::Text::TTA_LEFT, 0x80ff, 0, 0xf, FALSE, 0);
        }
        _maxLoopDurationOfTheLast100 = -1;
        _millisecLoopPointer = DAT_GameLoopDurationBuffer::instance + 1;
        do {
            if (_maxLoopDurationOfTheLast100 < _millisecLoopPointer[-1]) {
                _maxLoopDurationOfTheLast100 = _millisecLoopPointer[-1];
            }
            if (_maxLoopDurationOfTheLast100 < *_millisecLoopPointer) {
                _maxLoopDurationOfTheLast100 = *_millisecLoopPointer;
            }
            if (_maxLoopDurationOfTheLast100 < _millisecLoopPointer[1]) {
                _maxLoopDurationOfTheLast100 = _millisecLoopPointer[1];
            }
            if (_maxLoopDurationOfTheLast100 < _millisecLoopPointer[2]) {
                _maxLoopDurationOfTheLast100 = _millisecLoopPointer[2];
            }
            if (_maxLoopDurationOfTheLast100 < _millisecLoopPointer[3]) {
                _maxLoopDurationOfTheLast100 = _millisecLoopPointer[3];
            }
            _millisecLoopPointer = _millisecLoopPointer + 5;
        } while ((int)_millisecLoopPointer < 0xdf552c);
        if (elementState != 0xfffffc18) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                _averageMillisecLoopMain, posX + 0x30, posY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0, 0x11, FALSE, 0);
        }
        if (_averageMillisecLoopMain == 0) {
            _averageMillisecLoopMain = 1;
        }
        if (elementState != 0xfffffc18) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                (int)(1000 / (longlong)_averageMillisecLoopMain), posX + 0x30, posY + 0x14, OpenSHC::Text::TTA_LEFT,
                0x80ff, 0, 0x11, FALSE, 0);
        }
        DAT_CurrentFramerate::instance = (int)(1000 / (longlong)_averageMillisecLoopMain);
        if (_tickRateSum == 0) {
            _tickRateSum = 1;
        }
        _someRelationBetweenLoopDurationAndTickrate = _gameLoopDurationBufferSum / _tickRateSum;
        if (_someRelationBetweenLoopDurationAndTickrate == 0) {
            _someRelationBetweenLoopDurationAndTickrate = 1;
        }
        if (elementState != 0xfffffc18) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                (int)(1000 / (longlong)_someRelationBetweenLoopDurationAndTickrate), posX + 0x30, posY + 0x28,
                OpenSHC::Text::TTA_LEFT, 0x80ff, 0, 0x11, FALSE, 0);
        }
    }

}
}
