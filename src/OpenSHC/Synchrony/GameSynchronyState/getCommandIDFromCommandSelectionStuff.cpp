#include "../../Synchrony.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandState.hpp"
#include "OpenSHC/Commands/GameCommandStateByte.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandState;
    using Commands::GameCommandStateByte;

    // FUNCTION: STRONGHOLDCRUSADER 0x00480440
    int GameSynchronyState::getCommandIDFromCommandSelectionStuff()
    {
        int* _selectedPlayerIDAddress;
        GameCommandStateByte* _stateAddress;
        int _currentIndexCounter;
        int _commandID;
        int _nextPlayerID;
        int _playerID;
        bool _reorderedAnyoneUnk;
        this->MBR_someIndex = 0;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            800, '\0', (void*)((int)(this->MBR_SelectedGameCommands)));
        if (this->MBR_GameCommandID < 200) {
            _stateAddress = &this->DAT_GameCommandArray[this->MBR_GameCommandID].stateUnk;
            _currentIndexCounter = this->MBR_GameCommandID;
            do {
                /*
                  stateAddress - 9 = time address
                 */
                if (*_stateAddress != (GameCommandState)0 && (char)*_stateAddress < '\n'
                    && (int)((GameCommand*)(_stateAddress + -9))->time <= (int)DAT_GameCore::instance.mapTimeInTicks) {
                    /*
                      if this command has not been processed, but should be processed, and it has   been its time state
                      address - 5 = player
                     */
                    this->protocolInvokerPlayerID
                        = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs,
                            this)(*(int*)(_stateAddress + -5));
                    this->MBR_SelectedGameCommands[this->MBR_someIndex][0] = _currentIndexCounter;
                    this->MBR_SelectedGameCommands[this->MBR_someIndex][1] = this->protocolInvokerPlayerID;
                    this->MBR_someIndex = this->MBR_someIndex + 1;
                    if (99 < this->MBR_someIndex)
                        break;
                }
                _currentIndexCounter = _currentIndexCounter + 1;
                /*
                  move to next command
                 */
                _stateAddress = _stateAddress + 0x4f8;
            } while (_currentIndexCounter < 200);
        }
        /*
          reorder the selected commands list so that player ids with a lower number are   processed first.
         */
        int _counter2 = 0;
        if (0 < this->MBR_someIndex) {
            _reorderedAnyoneUnk = true;
            do {
                if (!_reorderedAnyoneUnk)
                    break;
                _currentIndexCounter = 1;
                _counter2 = _counter2 + 1;
                _reorderedAnyoneUnk = false;
                if (1 < this->MBR_someIndex) {
                    _selectedPlayerIDAddress = this->MBR_SelectedGameCommands[0] + 1;
                    do {
                        _nextPlayerID = _selectedPlayerIDAddress[2];
                        _commandID = (*(int (*)[2])(_selectedPlayerIDAddress + -1))[0];
                        _playerID = *_selectedPlayerIDAddress;
                        if (!_nextPlayerID) {
                            return 0;
                        }
                        if (_nextPlayerID < _playerID) {
                            (*(int (*)[2])(_selectedPlayerIDAddress + -1))[0] = _selectedPlayerIDAddress[1];
                            *_selectedPlayerIDAddress = _nextPlayerID;
                            _selectedPlayerIDAddress[1] = _commandID;
                            _selectedPlayerIDAddress[2] = _playerID;
                            _reorderedAnyoneUnk = true;
                        }
                        _currentIndexCounter = _currentIndexCounter + 1;
                        _selectedPlayerIDAddress = _selectedPlayerIDAddress + 2;
                    } while (_currentIndexCounter < this->MBR_someIndex);
                }
            } while (_counter2 < 100);
            _counter2 = 1;
        }
        return _counter2;
    }

}
}
