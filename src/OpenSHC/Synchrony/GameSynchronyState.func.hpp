/**
  path: 'OpenSHC/Synchrony/GameSynchronyState.func.hpp'
*/

#include "OpenSHC/Commands/GameCommandParameterLocationInt.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWriteInt.hpp"
#include "OpenSHC/Commands/GameCommandTypeInt.hpp"
#include "OpenSHC/DirectPlay/DPERRInt.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"
#include "basetsd.h"
#include "crtdefs.h"
#include "guiddef.h"
namespace OpenSHC {
namespace Synchrony {
    namespace GameSynchronyState_Func {

        using OpenSHC::Commands::GameCommandParameterLocationInt;
        using OpenSHC::Commands::GameCommandParameterReadWriteInt;
        using OpenSHC::Commands::GameCommandTypeInt;
        using OpenSHC::DirectPlay::DPERRInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (GameSynchronyState::*)(int), false, Address::SHC_3BB0A8C1_0x004010B0,
            &GameSynchronyState::isAIPlayer)
        isAIPlayer;

        MACRO_FUNCTION_RESOLVER(int (GameSynchronyState::*)(char*), false, Address::SHC_3BB0A8C1_0x00479C20,
            &GameSynchronyState::meth_0x479c20)
        meth_0x479c20;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(GUID*), false, Address::SHC_3BB0A8C1_0x0047D4A0,
            &GameSynchronyState::getGUIDForSelectedProvider)
        getGUIDForSelectedProvider;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0047D500,
            &GameSynchronyState::setMenuTypeBasedOnDirectPlayGUID)
        setMenuTypeBasedOnDirectPlayGUID;

        MACRO_FUNCTION_RESOLVER(DPERRInt (GameSynchronyState::*)(LPVOID*, SIZE_T*), false,
            Address::SHC_3BB0A8C1_0x0047D6A0, &GameSynchronyState::createCompoundAddressBasedOnSelectedProvider)
        createCompoundAddressBasedOnSelectedProvider;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0047DA70,
            &GameSynchronyState::setDPlaySessionNameValue)
        setDPlaySessionNameValue;

        MACRO_FUNCTION_RESOLVER(DPERRInt (GameSynchronyState::*)(BOOLEnum), false, Address::SHC_3BB0A8C1_0x0047DB10,
            &GameSynchronyState::initializeDirectPlayAndCreateOrJoinSession)
        initializeDirectPlayAndCreateOrJoinSession;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0047DE00,
            &GameSynchronyState::setSessionDescription)
        setSessionDescription;

        MACRO_FUNCTION_RESOLVER(
            void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0047DEA0, &GameSynchronyState::meth_0x47dea0)
        meth_0x47dea0;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(GUID*), false, Address::SHC_3BB0A8C1_0x0047E010,
            &GameSynchronyState::fetchSessionGUID)
        fetchSessionGUID;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(GUID*), false, Address::SHC_3BB0A8C1_0x0047E050,
            &GameSynchronyState::resolveEqualEntries)
        resolveEqualEntries;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0047E0E0,
            &GameSynchronyState::clearSessionsList)
        clearSessionsList;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0047E240,
            &GameSynchronyState::disconnectDPlay)
        disconnectDPlay;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0047E490,
            &GameSynchronyState::readGameSpyConfig)
        readGameSpyConfig;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(int), false, Address::SHC_3BB0A8C1_0x0047E5B0,
            &GameSynchronyState::meth_0x47e5b0)
        meth_0x47e5b0;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(void*, void*), false, Address::SHC_3BB0A8C1_0x0047E800,
            &GameSynchronyState::decompressTooLongPacketData)
        decompressTooLongPacketData;

        MACRO_FUNCTION_RESOLVER(
            int (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0047E830, &GameSynchronyState::FUN_0047e830)
        FUN_0047e830;

        MACRO_FUNCTION_RESOLVER(int (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0047E890,
            &GameSynchronyState::aiPlayerCountUnk)
        aiPlayerCountUnk;

        MACRO_FUNCTION_RESOLVER(int (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0047E8F0,
            &GameSynchronyState::checkPlayerSetValid)
        checkPlayerSetValid;

        MACRO_FUNCTION_RESOLVER(int (GameSynchronyState::*)(int), false, Address::SHC_3BB0A8C1_0x0047EA40,
            &GameSynchronyState::countPlayersInSameTeam)
        countPlayersInSameTeam;

        MACRO_FUNCTION_RESOLVER(uint (GameSynchronyState::*)(int), false, Address::SHC_3BB0A8C1_0x0047EAF0,
            &GameSynchronyState::translateMultiplayerIDsIntoPlayerIDs)
        translateMultiplayerIDsIntoPlayerIDs;

        MACRO_FUNCTION_RESOLVER(int (GameSynchronyState::*)(int), false, Address::SHC_3BB0A8C1_0x0047EB80,
            &GameSynchronyState::addPlayerToCurrentPlayerArray)
        addPlayerToCurrentPlayerArray;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0047EC10,
            &GameSynchronyState::handleUnexpectedDPlayXResult)
        handleUnexpectedDPlayXResult;

        MACRO_FUNCTION_RESOLVER(undefined4 (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0047EDE0,
            &GameSynchronyState::meth_0x47ede0)
        meth_0x47ede0;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(int, int, int, int), false,
            Address::SHC_3BB0A8C1_0x0047EED0, &GameSynchronyState::renderDebugDataSplitInfo)
        renderDebugDataSplitInfo;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0047F6A0,
            &GameSynchronyState::addChatMessageToDisplayList)
        addChatMessageToDisplayList;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0047F7E0,
            &GameSynchronyState::clearChatEvents)
        clearChatEvents;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0047F860,
            &GameSynchronyState::renderInGameChatUnk)
        renderInGameChatUnk;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0047FB50,
            &GameSynchronyState::FUN_0047fb50)
        FUN_0047fb50;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x00480050,
            &GameSynchronyState::resetGameCommands)
        resetGameCommands;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(int), false, Address::SHC_3BB0A8C1_0x004800B0,
            &GameSynchronyState::clearGameCommandEntry)
        clearGameCommandEntry;

        MACRO_FUNCTION_RESOLVER(int (GameSynchronyState::*)(GameCommandTypeInt), false,
            Address::SHC_3BB0A8C1_0x004800E0, &GameSynchronyState::sendLongerDataSuchAsResync)
        sendLongerDataSuchAsResync;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(GameCommandTypeInt, DWORD, dword, void*), false,
            Address::SHC_3BB0A8C1_0x00480210, &GameSynchronyState::scheduleReceivedCommand)
        scheduleReceivedCommand;

        MACRO_FUNCTION_RESOLVER(int (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x00480440,
            &GameSynchronyState::getCommandIDFromCommandSelectionStuff)
        getCommandIDFromCommandSelectionStuff;

        MACRO_FUNCTION_RESOLVER(undefined4 (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x00480570,
            &GameSynchronyState::getGameCommandArrayIndex)
        getGameCommandArrayIndex;

        MACRO_FUNCTION_RESOLVER(int (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x00480580,
            &GameSynchronyState::getPendingGameCommandsCount)
        getPendingGameCommandsCount;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(
                                    void*, size_t, GameCommandParameterLocationInt, GameCommandParameterReadWriteInt),
            false, Address::SHC_3BB0A8C1_0x004805D0, &GameSynchronyState::serializeOrDeserializeCommandParameter)
        serializeOrDeserializeCommandParameter;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x00486600,
            &GameSynchronyState::checkSkirmishGameDefeat)
        checkSkirmishGameDefeat;

        MACRO_FUNCTION_RESOLVER(int (GameSynchronyState::*)(int), false, Address::SHC_3BB0A8C1_0x00486A70,
            &GameSynchronyState::getLordTypeForPlayer)
        getLordTypeForPlayer;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(int), false, Address::SHC_3BB0A8C1_0x00486F20,
            &GameSynchronyState::meth_0x486f20)
        meth_0x486f20;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x00487250,
            &GameSynchronyState::invokeDirectPlayEnumConnections)
        invokeDirectPlayEnumConnections;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(BOOLEnum), false, Address::SHC_3BB0A8C1_0x00487390,
            &GameSynchronyState::restartDPlaySessionEnumeration)
        restartDPlaySessionEnumeration;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x004874B0,
            &GameSynchronyState::createDirectPlayInterfaceModemUnk)
        createDirectPlayInterfaceModemUnk;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x00487650,
            &GameSynchronyState::setupSkirmishLobby)
        setupSkirmishLobby;

        MACRO_FUNCTION_RESOLVER(int (GameSynchronyState::*)(int), false, Address::SHC_3BB0A8C1_0x00487A30,
            &GameSynchronyState::determineGameTicksToPerform)
        determineGameTicksToPerform;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(byte, undefined4, char*, size_t, undefined4), false,
            Address::SHC_3BB0A8C1_0x00487C50, &GameSynchronyState::transmitCommand)
        transmitCommand;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00487E30,
            &GameSynchronyState::sendSomeMultiplayerSyncMessageWithType)
        sendSomeMultiplayerSyncMessageWithType;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x00488010,
            &GameSynchronyState::processSyncPacketUnk)
        processSyncPacketUnk;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x004880E0,
            &GameSynchronyState::sendSyncPacket126)
        sendSyncPacket126;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x004882A0,
            &GameSynchronyState::computeAndSetLatencyInformation)
        computeAndSetLatencyInformation;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(int, int, int, int), false,
            Address::SHC_3BB0A8C1_0x00488540, &GameSynchronyState::renderDebugDataNetwork)
        renderDebugDataNetwork;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(GameCommandTypeInt), false,
            Address::SHC_3BB0A8C1_0x00489100, &GameSynchronyState::queueCommand)
        queueCommand;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x004892F0,
            &GameSynchronyState::processWaitingCommands)
        processWaitingCommands;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0048BD40,
            &GameSynchronyState::compareGameVersions)
        compareGameVersions;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0048BF80,
            &GameSynchronyState::createMultiplayerLobbyUnk)
        createMultiplayerLobbyUnk;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0048C660,
            &GameSynchronyState::queueSynchronizedAutosaveProtocol)
        queueSynchronizedAutosaveProtocol;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0048C750,
            &GameSynchronyState::multiplayerSyncMessagesUnk)
        multiplayerSyncMessagesUnk;

        MACRO_FUNCTION_RESOLVER(undefined4 (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0048C7B0,
            &GameSynchronyState::reorderTeamsAndPositions)
        reorderTeamsAndPositions;

        MACRO_FUNCTION_RESOLVER(
            void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x0048CB00, &GameSynchronyState::checkGameSync)
        checkGameSync;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(int), false, Address::SHC_3BB0A8C1_0x0048CC90,
            &GameSynchronyState::recomputeHashesAndSendResync)
        recomputeHashesAndSendResync;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x00490340,
            &GameSynchronyState::someMultiplayerMessageSending)
        someMultiplayerMessageSending;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(int), false, Address::SHC_3BB0A8C1_0x00490380,
            &GameSynchronyState::removePlayerFromLobby)
        removePlayerFromLobby;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x00490480,
            &GameSynchronyState::checkMultiplayerLaggingPlayers)
        checkMultiplayerLaggingPlayers;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x00490690,
            &GameSynchronyState::receiveAllTransmittedCommands)
        receiveAllTransmittedCommands;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(), false, Address::SHC_3BB0A8C1_0x00490920,
            &GameSynchronyState::waitForMultiplayerHost)
        waitForMultiplayerHost;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(char*), false, Address::SHC_3BB0A8C1_0x00491040,
            &GameSynchronyState::handleCommandLineArguments)
        handleCommandLineArguments;

        MACRO_FUNCTION_RESOLVER(void (GameSynchronyState::*)(int, int, DWORD), false, Address::SHC_3BB0A8C1_0x004AF800,
            &GameSynchronyState::RenderInGameChatDisplayElementUnk)
        RenderInGameChatDisplayElementUnk;

    } // namespace GameSynchronyState_Func
} // namespace Synchrony
} // namespace OpenSHC
