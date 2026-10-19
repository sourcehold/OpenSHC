#include "../../Synchrony.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Commands/GameCommandState.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_ProtocolDefinedData.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandScheduling;
    using Commands::GameCommandState;

    // FUNCTION: STRONGHOLDCRUSADER 0x004800E0
    int GameSynchronyState::sendLongerDataSuchAsResync(GameCommandType commandCategory)
    {
        this->DAT_CurrentGameCommandID = this->DAT_GameCommandArrayIndex;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            1260, '\0', (void*)((int)(&this->DAT_GameCommandArray[this->DAT_GameCommandArrayIndex].parameters)));
        this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].stateUnk = Commands::GCS_UNPROCESSED;
        this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].playerUnk = this->DPLAYX_PlayerHandle;
        this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].commandType = (undefined1)commandCategory;
        this->DAT_CommandActionPlan = Commands::GCS_SCHEDULE_AND_SEND;
        this->DAT_PlayerIDReceiver = 0;
        this->DAT_CommandParameterOffset = 0;
        ((void (*)())DAT_ProtocolDefinedData::instance
                .commandFunctions[this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].commandType + 21])();
        this->DAT_CommandParameterOffset = 0;
        int _size = this->DAT_CommandSize;
        if (200 < this->DAT_CommandSize && (undefined1)commandCategory != Commands::GCT_SEND_RESYNC_LOGICALTILEMAP) {
            this->DAT_Packet.packet.commandProtocol = 125;
            this->DAT_Packet.prefixedPacket.packet.commandProtocol = (undefined1)commandCategory;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::moveLowerThreeBytesIntoParam2, DAT_LowLevelMemory::ptr)(
                this->DAT_GameCommandArray + this->DAT_CurrentGameCommandID,
                (void*)((int)(((int)&this->DAT_Packet + 2))));
            _size = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::compressOrCreateLengthPrefixedPacketUnk,
                this)(this->DAT_CommandSize, (char*)((int)(this->DAT_GameCommandFixedParameterLocation)),
                (void*)((int)(((int)&this->DAT_Packet + 5))));
            ++_size;
        }
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::clearGameCommandEntry, this)(
            this->DAT_CurrentGameCommandID);
        return _size;
    }

}
}
