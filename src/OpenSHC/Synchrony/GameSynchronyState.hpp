/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony/GameSynchronyState.hpp'
*/

#pragma once

#include "OpenSHC/Commands/GameCommand.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocationInt.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWriteInt.hpp"
#include "OpenSHC/Commands/GameCommandSchedulingInt.hpp"
#include "OpenSHC/Commands/GameCommandTypeInt.hpp"
#include "OpenSHC/DirectPlay/DPERRInt.hpp"
#include "OpenSHC/DirectPlay/DPNAME.hpp"
#include "OpenSHC/DirectPlay/IDirectPlay4A.hpp"
#include "OpenSHC/DirectPlay/lobby/IDirectPlayLobby3.hpp"
#include "OpenSHC/Game/GameModeInt.hpp"
#include "OpenSHC/Game/Skirmish/SkirmishStatistics.hpp"
#include "OpenSHC/Synchrony/HashContainer.hpp"
#include "OpenSHC/Synchrony/HashDataContainer.hpp"
#include "OpenSHC/Synchrony/Networking/ChatEvent.hpp"
#include "OpenSHC/Synchrony/Networking/ConnectionLagInfo.hpp"
#include "OpenSHC/Synchrony/Networking/PacketUnion.hpp"
#include "OpenSHC/UI/Enums/MenuModalTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"
#include "basetsd.h"
#include "crtdefs.h"
#include "guiddef.h"
#include "inaddr.h"
#include "mbstring.h"
#include "winnt.h"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommand;
    using OpenSHC::Commands::GameCommandParameterLocationInt;
    using OpenSHC::Commands::GameCommandParameterReadWriteInt;
    using OpenSHC::Commands::GameCommandSchedulingInt;
    using OpenSHC::Commands::GameCommandTypeInt;
    using OpenSHC::DirectPlay::DPERRInt;
    using OpenSHC::DirectPlay::DPNAME;
    using OpenSHC::DirectPlay::IDirectPlay4A;
    using OpenSHC::DirectPlay::lobby::IDirectPlayLobby3;
    using OpenSHC::Game::GameModeInt;
    using OpenSHC::Game::Skirmish::SkirmishStatistics;
    using OpenSHC::Synchrony::HashContainer;
    using OpenSHC::Synchrony::HashDataContainer;
    using OpenSHC::Synchrony::Networking::ChatEvent;
    using OpenSHC::Synchrony::Networking::ConnectionLagInfo;
    using OpenSHC::Synchrony::Networking::PacketUnion;
    using OpenSHC::UI::Enums::MenuModalTypeInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x0010A218
    class GameSynchronyState {
    public:
        undefined4 scrollBarItemCount; // 0x00000000 length: 4
        undefined4 scrollBarItemOffset; // 0x00000004 length: 4
        undefined4 selectedProviderIndex; // 0x00000008 length: 4
        GUID* guids[10]; // 0x0000000C length: 40
        LPCWSTR providerNames[10]; // 0x00000034 length: 40
        undefined4 modemScrollbarCount; // 0x0000005C length: 4
        undefined4 modemScrollBarOffset; // 0x00000060 length: 4
        undefined4 modemScrollbarIndex; // 0x00000064 length: 4
        char* stringPointerArray[29]; // 0x00000068 length: 116
        undefined1 padding_0xdc[4]; // 0x000000DC length: 4
        undefined4 DPLAY_SessionsCount; // 0x000000E0 length: 4
        int scrollBarIndex; // 0x000000E4 length: 4
        GUID* DPLAY_SessionGUIDs[50]; // 0x000000E8 length: 200
        WCHAR* DPLAY_SessionNames[50]; // 0x000001B0 length: 200
        bool unkEnumerationRelatedBool; // 0x00000278 length: 1
        undefined1 padding_0x279[3]; // 0x00000279 length: 3
        IDirectPlay4A** DPLAYX_4A; // 0x0000027C length: 4
        IDirectPlayLobby3** DPLAYX_LOBBY; // 0x00000280 length: 4
        MenuModalTypeInt nextModalDialog; // 0x00000284 length: 4
        int multiplayerJoinStep; // 0x00000288 length: 4
        BOOLEnum useTCPIP; // 0x0000028C length: 4
        char connectTarget[30]; // 0x00000290 length: 30
        undefined1 padding_0x2ae[2]; // 0x000002AE length: 2
        undefined4 connectPort; // 0x000002B0 length: 4
        undefined4 willHost; // 0x000002B4 length: 4
        char shellExecuteTarget[600]; // 0x000002B8 length: 600
        int field32_0x510; // 0x00000510 length: 4
        BOOLEnum openOnClose; // 0x00000514 length: 4
        byte connectName[256]; // 0x00000518 length: 256
        GameModeInt DAT_CurrentGameMode; // 0x00000618 length: 4
        GameModeInt currentGameModeCopy_SEC_Section1106; // 0x0000061C length: 4
        byte unused02[104]; // 0x00000620 length: 104
        DPNAME DPLAY_PlayerNameStructure; // 0x00000688 length: 16
        undefined4 DPLAYX_Connection; // 0x00000698 length: 4
        undefined4 DPLAYX_ReceivedPlayerID; // 0x0000069C length: 4
        dword DPLAY_ToID; // 0x000006A0 length: 4
        undefined4 DPLAYX_PlayerHandle; // 0x000006A4 length: 4
        int currentPlayerFullIDArray[9]; // 0x000006A8 length: 36
        int DAT_CurrentPlayerFullIDArray2[9]; // 0x000006CC length: 36
        int somePlayerRelatedArray[9]; // 0x000006F0 length: 36
        int currentAIArray[9]; // 0x00000714 length: 36
        int SEC_AIVariationArray[9]; // 0x00000738 length: 36
        byte field48_0x75c[9]; // 0x0000075C length: 9
        byte field49_0x765[3][9]; // 0x00000765 length: 27
        BOOLEnum displayYourIP; // 0x00000780 length: 4
        BOOLEnum lanOrWan; // 0x00000784 length: 4
        IN_ADDR lanIP; // 0x00000788 length: 4
        IN_ADDR wanIP; // 0x0000078C length: 4
        BOOLEnum isHost; // 0x00000790 length: 4
        undefined4 DAT_HostPlayerSlotID; // 0x00000794 length: 4
        undefined4 DAT_HostAnnounced; // 0x00000798 length: 4
        byte field57_0x79c[254]; // 0x0000079C length: 254
        WCHAR DPLAYX_SessionName[250]; // 0x0000089A length: 500
        WCHAR DPLAY_PlayerShortName[125]; // 0x00000A8E length: 250
        int packetsReceived; // 0x00000B88 length: 4
        undefined4 transmissionCounterUnk; // 0x00000B8C length: 4
        undefined4 field62_0xb90; // 0x00000B90 length: 4
        undefined4 DAT_GameHalted; // 0x00000B94 length: 4
        undefined4 syncStatus; // 0x00000B98 length: 4
        undefined4 field65_0xb9c; // 0x00000B9C length: 4
        undefined4 field66_0xba0; // 0x00000BA0 length: 4
        undefined4 field67_0xba4; // 0x00000BA4 length: 4
        undefined4 field68_0xba8; // 0x00000BA8 length: 4
        undefined4 somePacketSubTypeUnk; // 0x00000BAC length: 4
        undefined4 field70_0xbb0; // 0x00000BB0 length: 4
        undefined4 field71_0xbb4; // 0x00000BB4 length: 4
        int syncRelatedStatusArray[9]; // 0x00000BB8 length: 36
        undefined4 field73_0xbdc; // 0x00000BDC length: 4
        undefined4 currentPacketTotalSize; // 0x00000BE0 length: 4
        undefined4 field75_0xbe4; // 0x00000BE4 length: 4
        undefined4 field76_0xbe8; // 0x00000BE8 length: 4
        undefined4 flag_0xbec; // 0x00000BEC length: 4
        undefined4 field78_0xbf0; // 0x00000BF0 length: 4
        undefined4 splinterType; // 0x00000BF4 length: 4
        undefined4 totalSplitDataItems; // 0x00000BF8 length: 4
        undefined4 totalSplitChimps; // 0x00000BFC length: 4
        undefined4 totalSplitStructures; // 0x00000C00 length: 4
        undefined4 totalSplitVeg; // 0x00000C04 length: 4
        undefined4 totalSplitTribes; // 0x00000C08 length: 4
        undefined4 totalSplitPlayers; // 0x00000C0C length: 4
        undefined4 totalSplitElements; // 0x00000C10 length: 4
        undefined4 totalSplitLayers; // 0x00000C14 length: 4
        undefined4 totalSplitFlies; // 0x00000C18 length: 4
        undefined4 totalSplitMoats; // 0x00000C1C length: 4
        undefined4 totalSplitTeleports; // 0x00000C20 length: 4
        undefined4 totalSplitPitchDitches; // 0x00000C24 length: 4
        undefined4 totalSplitZones; // 0x00000C28 length: 4
        undefined1 padding_0xc2c[8]; // 0x00000C2C length: 8
        undefined4 firstSplitChimps; // 0x00000C34 length: 4
        undefined4 firstSplitStructures; // 0x00000C38 length: 4
        undefined4 firstSplitVeg; // 0x00000C3C length: 4
        undefined4 firstSplitTribe; // 0x00000C40 length: 4
        undefined4 firstSplitPlayer; // 0x00000C44 length: 4
        undefined4 firstSplitElement; // 0x00000C48 length: 4
        undefined4 firstSplitLayer; // 0x00000C4C length: 4
        undefined4 firstSplitFly; // 0x00000C50 length: 4
        undefined4 firstSplitMoat; // 0x00000C54 length: 4
        undefined4 firstSplitTeleports; // 0x00000C58 length: 4
        undefined4 firstSplitPitchDitch; // 0x00000C5C length: 4
        undefined4 firstSplitZone; // 0x00000C60 length: 4
        undefined1 padding_0xc64[8]; // 0x00000C64 length: 8
        undefined4 quitGameVoteRelated; // 0x00000C6C length: 4
        int field122_0xc70[9]; // 0x00000C70 length: 36
        int quitGameVoteRequestTime; // 0x00000C94 length: 4
        int announcementReceivedByArray[9]; // 0x00000C98 length: 36
        undefined4 saveRelated; // 0x00000CBC length: 4
        undefined4 shouldSendAnnouncementUnk; // 0x00000CC0 length: 4
        BOOLEnum announcementReceivedBool; // 0x00000CC4 length: 4
        undefined4 announcementReceiveTime; // 0x00000CC8 length: 4
        undefined4 laggingPlayerIDUnk; // 0x00000CCC length: 4
        undefined4 DAT_SomeTime; // 0x00000CD0 length: 4
        undefined4 field131_0xcd4; // 0x00000CD4 length: 4
        PacketUnion DPLAY_ReceiveData; // 0x00000CD8 length: 61000
        byte DAT_PacketDecodingDestination[61100]; // 0x0000FB20 length: 61100
        PacketUnion DAT_Packet; // 0x0001E9CC length: 61000
        undefined1 syncPacket2Type; // 0x0002D814 length: 1
        undefined3 mapTimeInTicksLower3Bytes; // 0x0002D815 length: 3
        undefined1 syncParamTimeDiff; // 0x0002D818 length: 1
        undefined1 padding_0x2d819[3]; // 0x0002D819 length: 3
        undefined4 DPLAY_ReceiveDataSize; // 0x0002D81C length: 4
        undefined4 DAT_CurrentTransmitCommandPacketSize; // 0x0002D820 length: 4
        undefined4 DAT_CurrentGameCommandID; // 0x0002D824 length: 4
        GameCommandSchedulingInt DAT_CommandActionPlan; // 0x0002D828 length: 4
        undefined4 DAT_PlayerIDReceiver; // 0x0002D82C length: 4
        undefined4 DAT_CommandSize; // 0x0002D830 length: 4
        byte DAT_GameCommandFixedParameterLocation[61000]; // 0x0002D834 length: 61000
        GameCommand DAT_GameCommandArray[200]; // 0x0003C67C length: 254400
        short DAT_LagIndicatorPerPlayer[9]; // 0x0007A83C length: 18
        undefined1 padding_0x7a84e[2]; // 0x0007A84E length: 2
        undefined4 DAT_GameCommandParam0; // 0x0007A850 length: 4
        undefined4 DAT_GameCommandParam1; // 0x0007A854 length: 4
        undefined4 DAT_GameCommandParam2; // 0x0007A858 length: 4
        undefined4 DAT_GameCommandParam3; // 0x0007A85C length: 4
        undefined4 DAT_GameCommandParam4; // 0x0007A860 length: 4
        undefined4 DAT_GameCommandParam5; // 0x0007A864 length: 4
        int receivedMatchTimesTrackerUnk; // 0x0007A868 length: 4
        int clTimeDiff; // 0x0007A86C length: 4
        int syncRelatedCountdown; // 0x0007A870 length: 4
        int matchTime; // 0x0007A874 length: 4
        int matchTimesArray[8]; // 0x0007A878 length: 32
        int HASH_HashTotal[9]; // 0x0007A898 length: 36
        int DAT_PlayerMatchTimes[9]; // 0x0007A8BC length: 36
        HashContainer HASH_PartialHashPerPlayer; // 0x0007A8E0 length: 432
        int DAT_MultiplayerGameVersions[9]; // 0x0007AA90 length: 36
        BOOLEnum isIncludedPlayer[9]; // 0x0007AAB4 length: 36
        BOOLEnum flag_0x7aad8; // 0x0007AAD8 length: 4
        byte sharedDesyncFlags[14]; // 0x0007AADC length: 14
        undefined1 padding_0x7aaea[2]; // 0x0007AAEA length: 2
        ConnectionLagInfo connectionLagInfoArray[9]; // 0x0007AAEC length: 324
        undefined1 syncPacketType; // 0x0007AC30 length: 1
        undefined1 syncRelatedCounter; // 0x0007AC31 length: 1
        undefined1 syncRelated2; // 0x0007AC32 length: 1
        undefined1 padding_0x7ac33[1]; // 0x0007AC33 length: 1
        int historicalLagInfoPerPlayer[9][100][2]; // 0x0007AC34 length: 7200
        undefined4 counter; // 0x0007C854 length: 4
        undefined4 limit; // 0x0007C858 length: 4
        int HASH_Units[9][2500]; // 0x0007C85C length: 90000
        int HASH_Buildings[9][2000]; // 0x000927EC length: 72000
        int HASH_Trees[9][2000]; // 0x000A412C length: 72000
        int HASH_Tribes[9][1250]; // 0x000B5A6C length: 45000
        int HASH_PlayerDatas[9][9]; // 0x000C0A34 length: 324
        int HASH_Section1023[9][20]; // 0x000C0B78 length: 720
        int HASH_Entities[9][3000]; // 0x000C0E48 length: 108000
        HashDataContainer HASH_LogicalTileMap[9]; // 0x000DB428 length: 138240
        int HASH_Moats[9][160]; // 0x000FD028 length: 5760
        int HASH_LaddermanWalledData[9][200]; // 0x000FE6A8 length: 7200
        int HASH_PitchDitches[9][40]; // 0x001002C8 length: 1440
        int HASH_Unknown2[9][40]; // 0x00100868 length: 1440
        int HASH_AIVS[9][9]; // 0x00100E08 length: 324
        int HASH_HeatMaps[9][80]; // 0x00100F4C length: 2880
        int receivedSyncStatusUnk[9]; // 0x00101A8C length: 36
        int syncStatus10Related[9]; // 0x00101AB0 length: 36
        undefined4 field196_0x101ad4; // 0x00101AD4 length: 4
        char receivedChatMessage[250]; // 0x00101AD8 length: 250
        char DAT_ChatMessageArray[20][250]; // 0x00101BD2 length: 5000
        char DAT_ChatMessageSubjectPlayerNameArray[20][250]; // 0x00102F5A length: 5000
        char DAT_ChatMessageObjectPlayerNameArray[20][250]; // 0x001042E2 length: 5000
        undefined1 padding_0x10566a[2]; // 0x0010566A length: 2
        undefined4 DAT_ChatMessageArrayIndex; // 0x0010566C length: 4
        undefined4 field204_0x105670; // 0x00105670 length: 4
        undefined4 DAT_InsultTextIndex; // 0x00105674 length: 4
        ChatEvent DAT_ChatEventArray[20]; // 0x00105678 length: 320
        char shortMapName[120]; // 0x001057B8 length: 120
        int skirmishRelated1; // 0x00105830 length: 4
        char mapName[1000]; // 0x00105834 length: 1000
        char DAT_PlayerNames[9][250]; // 0x00105C1C length: 2250
        char playerNames2[9][250]; // 0x001064E6 length: 2250
        int DAT_PlayerSlotArraySomeValue[9]; // 0x00106DB0 length: 36
        int unknownPlayerInfo_01[9]; // 0x00106DD4 length: 36
        int unknownPlayerInfo_03[9]; // 0x00106DF8 length: 36
        int field215_0x106e1c; // 0x00106E1C length: 4
        int field216_0x106e20; // 0x00106E20 length: 4
        int field217_0x106e24; // 0x00106E24 length: 4
        int field218_0x106e28; // 0x00106E28 length: 4
        int field219_0x106e2c; // 0x00106E2C length: 4
        int startGold; // 0x00106E30 length: 4
        int defaultPopularity; // 0x00106E34 length: 4
        int DAT_MultiplayerGameSpeedLevel; // 0x00106E38 length: 4
        int SEC_GameIntensityType; // 0x00106E3C length: 4
        int field224_0x106e40[20]; // 0x00106E40 length: 80
        undefined4 field225_0x106e90; // 0x00106E90 length: 4
        int unknownSkirmishBalanceRelatedArray[10]; // 0x00106E94 length: 40
        byte unused03[40]; // 0x00106EBC length: 40
        int field228_0x106ee4; // 0x00106EE4 length: 4
        undefined4 DAT_SkirmishBalanceRelated; // 0x00106EE8 length: 4
        undefined1 padding_0x106eec[4]; // 0x00106EEC length: 4
        undefined4 DAT_SkirmishSettingRelated; // 0x00106EF0 length: 4
        undefined4 SEC_Section1084; // 0x00106EF4 length: 4
        char unknownMapName_01[1004]; // 0x00106EF8 length: 1004
        undefined4 SEC_CurrentAdvantageBalance; // 0x001072E4 length: 4
        int field238_0x1072e8; // 0x001072E8 length: 4
        int field239_0x1072ec; // 0x001072EC length: 4
        undefined4 field240_0x1072f0; // 0x001072F0 length: 4
        BOOLEnum reparseMaps; // 0x001072F4 length: 4
        int field242_0x1072f8; // 0x001072F8 length: 4
        undefined4 DAT_MapSelectionScrollOffset; // 0x001072FC length: 4
        undefined4 DAT_MapSelectionTotalNumber; // 0x00107300 length: 4
        int DAT_MapSelectionRelativeSelected; // 0x00107304 length: 4
        byte unused04[8]; // 0x00107308 length: 8
        int unknownMapRelatedReceivedDataArray[500]; // 0x00107310 length: 2000
        int mapPlayerCountArray[500]; // 0x00107AE0 length: 2000
        int mapBalanceArray[500]; // 0x001082B0 length: 2000
        int mapU4Int0_2Array[500]; // 0x00108A80 length: 2000
        undefined4 field251_0x109250; // 0x00109250 length: 4
        undefined4 savedMapTimeInTicks; // 0x00109254 length: 4
        undefined4 savedUnitsCRC32Hash; // 0x00109258 length: 4
        undefined1 padding_0x10925c[4]; // 0x0010925C length: 4
        undefined4 unknownIncrementBy40_01; // 0x00109260 length: 4
        int DAT_ChatMessageReceiverArray[9]; // 0x00109264 length: 36
        undefined4 DAT_ChatTauntOrMessage; // 0x00109288 length: 4
        undefined4 SEC_Section1093; // 0x0010928C length: 4
        dword field262_0x109290; // 0x00109290 length: 4
        int kickedAtTime; // 0x00109294 length: 4
        undefined4 field264_0x109298; // 0x00109298 length: 4
        undefined4 kickDueToLagStatusUnk; // 0x0010929C length: 4
        int DAT_AutoSaveEveryMinutes; // 0x001092A0 length: 4
        undefined4 DAT_TimeRelated1; // 0x001092A4 length: 4
        int DAT_MapU4Int2_2; // 0x001092A8 length: 4
        undefined4 DAT_HashCountdown; // 0x001092AC length: 4
        undefined4 field270_0x1092b0; // 0x001092B0 length: 4
        undefined4 DAT_StrongWalls; // 0x001092B4 length: 4
        undefined4 field272_0x1092b8; // 0x001092B8 length: 4
        undefined4 DAT_NoCowThrowing; // 0x001092BC length: 4
        undefined4 DAT_NoDogs; // 0x001092C0 length: 4
        undefined4 DAT_NoRushSetting; // 0x001092C4 length: 4
        undefined4 field276_0x1092c8; // 0x001092C8 length: 4
        undefined4 field277_0x1092cc; // 0x001092CC length: 4
        int unknownPlayerInfoArray_01[9]; // 0x001092D0 length: 36
        int DAT_ReceivedAIVFileAvailabilityPerAIArray[9][20]; // 0x001092F4 length: 720
        SkirmishStatistics SEC_FinalResults; // 0x001095C4 length: 1912
        char ipRelatedArray[20]; // 0x00109D3C length: 20
        char ipRelatedArray2[20]; // 0x00109D50 length: 20
        char ipRelatedArray3[20]; // 0x00109D64 length: 20
        char ipRelatedArray4[20]; // 0x00109D78 length: 20
        int ipArrayIndex; // 0x00109D8C length: 4
        undefined4 DAT_TwoIfNotHost; // 0x00109D90 length: 4
        undefined4 DAT_MapFileReceivingState; // 0x00109D94 length: 4
        short field288_0x109d98[9]; // 0x00109D98 length: 18
        undefined1 padding_0x109daa[2]; // 0x00109DAA length: 2
        int mapSendingFileSize; // 0x00109DAC length: 4
        int mapSendingByteBufferAddress[9]; // 0x00109DB0 length: 36
        FILE* mapSendingFileHandles[9]; // 0x00109DD4 length: 36
        FILE* FILEPTR_ReceivedMapFile; // 0x00109DF8 length: 4
        int field295_0x109dfc[9]; // 0x00109DFC length: 36
        int field296_0x109e20[9]; // 0x00109E20 length: 36
        byte DAT_RoundTableOrderArray[9]; // 0x00109E44 length: 9
        byte DAT_PlayerGroupArray[9]; // 0x00109E4D length: 9
        byte playerGroupArray2Unk[9]; // 0x00109E56 length: 9
        byte field300_0x109e5f[9]; // 0x00109E5F length: 9
        byte DAT_PlayerPositionsArray[8]; // 0x00109E68 length: 8
        undefined4 protocolInvokerPlayerID; // 0x00109E70 length: 4
        undefined4 currentPlayerSlotID; // 0x00109E74 length: 4
        undefined4 DAT_SomePlayerID; // 0x00109E78 length: 4
        undefined4 field305_0x109e7c; // 0x00109E7C length: 4
        byte field306_0x109e80[9]; // 0x00109E80 length: 9
        undefined1 padding_0x109e89[3]; // 0x00109E89 length: 3
        int field310_0x109e8c; // 0x00109E8C length: 4
        undefined1 padding_0x109e90[4]; // 0x00109E90 length: 4
        undefined4 field315_0x109e94; // 0x00109E94 length: 4
        undefined4 field316_0x109e98; // 0x00109E98 length: 4
        undefined4 mapTimeInTicksSinglePlayer; // 0x00109E9C length: 4
        undefined4 field318_0x109ea0; // 0x00109EA0 length: 4
        undefined4 field319_0x109ea4; // 0x00109EA4 length: 4
        undefined4 field320_0x109ea8; // 0x00109EA8 length: 4
        undefined4 field321_0x109eac; // 0x00109EAC length: 4
        undefined4 field322_0x109eb0; // 0x00109EB0 length: 4
        undefined4 field323_0x109eb4; // 0x00109EB4 length: 4
        undefined4 field324_0x109eb8; // 0x00109EB8 length: 4
        int field325_0x109ebc; // 0x00109EBC length: 4
        int field326_0x109ec0; // 0x00109EC0 length: 4
        undefined4 receivedCommandMapTimeInTicks; // 0x00109EC4 length: 4
        undefined1 padding_0x109ec8[4]; // 0x00109EC8 length: 4
        int field332_0x109ecc; // 0x00109ECC length: 4
        undefined4 otherTime1; // 0x00109ED0 length: 4
        undefined4 now2; // 0x00109ED4 length: 4
        dword field335_0x109ed8; // 0x00109ED8 length: 4
        undefined4 MBR_GameCommandID; // 0x00109EDC length: 4
        undefined4 DAT_GameCommandArrayIndex; // 0x00109EE0 length: 4
        undefined4 DAT_CommandParameterOffset; // 0x00109EE4 length: 4
        undefined4 commandDelay; // 0x00109EE8 length: 4
        int MBR_SelectedGameCommands[100][2]; // 0x00109EEC length: 800
        undefined4 MBR_someIndex; // 0x0010A20C length: 4
        DPERRInt DPLAYX_SendAndReceiveREsult; // 0x0010A210 length: 4
        undefined4 DAT_TickCount; // 0x0010A214 length: 4

    private:
        GameSynchronyState(GameSynchronyState const&);
        void operator=(GameSynchronyState const&);

        GameSynchronyState();
        ~GameSynchronyState();

    public:
        // Constructor
        GameSynchronyState* Constructor_GameSynchronyState();

        BOOLEnum isAIPlayer(int playerID);

        int meth_0x479c20(char* fileName);

        void getGUIDForSelectedProvider(GUID* param_1);

        void setMenuTypeBasedOnDirectPlayGUID();

        DPERRInt createCompoundAddressBasedOnSelectedProvider(LPVOID* pCompoundAddress, SIZE_T* param_2);

        void setDPlaySessionNameValue();

        DPERRInt initializeDirectPlayAndCreateOrJoinSession(BOOLEnum join);

        void setSessionDescription();

        void meth_0x47dea0();

        void fetchSessionGUID(GUID* pGUID);

        void resolveEqualEntries(GUID* pGUID);

        void clearSessionsList();

        void disconnectDPlay();

        void readGameSpyConfig();

        void meth_0x47e5b0(int param_1);

        void decompressTooLongPacketData(void* source, void* destination);

        int FUN_0047e830();

        int aiPlayerCountUnk();

        int checkPlayerSetValid();

        int countPlayersInSameTeam(int playerID);

        uint translateMultiplayerIDsIntoPlayerIDs(int multiplayerID);

        int addPlayerToCurrentPlayerArray(int playerFullID);

        void handleUnexpectedDPlayXResult();

        undefined4 meth_0x47ede0();

        void renderDebugDataSplitInfo(int x, int y, int width, int height);

        void addChatMessageToDisplayList(int subjectPlayerID, int objectPlayerID);

        void clearChatEvents();

        void renderInGameChatUnk(int param_1, int param_2, int param_3);

        void FUN_0047fb50(int xPos, int yPos, int param_3);

        void resetGameCommands();

        void clearGameCommandEntry(int gameCommandID);

        int sendLongerDataSuchAsResync(GameCommandTypeInt commandCategory);

        void scheduleReceivedCommand(
            GameCommandTypeInt commandCategory, DWORD dxPlayerHandle, dword time, void* address);

        int getCommandIDFromCommandSelectionStuff();

        undefined4 getGameCommandArrayIndex();

        int getPendingGameCommandsCount();

        void serializeOrDeserializeCommandParameter(void* destination, size_t size,
            GameCommandParameterLocationInt srcSwitch, GameCommandParameterReadWriteInt destSwitch);

        void checkSkirmishGameDefeat();

        int getLordTypeForPlayer(int playerID);

        void meth_0x486f20(int param_1);

        void invokeDirectPlayEnumConnections();

        void restartDPlaySessionEnumeration(BOOLEnum respectTimeout);

        void createDirectPlayInterfaceModemUnk();

        void setupSkirmishLobby();

        int determineGameTicksToPerform(int currentPlayerSlotID);

        void transmitCommand(byte commandCategory, undefined4 time, char* addressOfFullCommandObjectOrCommandParameters,
            size_t size, undefined4 idTo);

        void sendSomeMultiplayerSyncMessageWithType(undefined4 syncPacketType2);

        void processSyncPacketUnk();

        void sendSyncPacket126();

        void computeAndSetLatencyInformation();

        void renderDebugDataNetwork(int x, int y, int width, int height);

        void queueCommand(GameCommandTypeInt commandType);

        void processWaitingCommands();

        void compareGameVersions();

        void createMultiplayerLobbyUnk();

        void queueSynchronizedAutosaveProtocol();

        void multiplayerSyncMessagesUnk();

        undefined4 reorderTeamsAndPositions();

        void checkGameSync();

        void recomputeHashesAndSendResync(int dontSendSyncCommand);

        void someMultiplayerMessageSending();

        void removePlayerFromLobby(int playerID);

        void checkMultiplayerLaggingPlayers();

        void receiveAllTransmittedCommands();

        void waitForMultiplayerHost();

        void handleCommandLineArguments(char* arguments);

        void RenderInGameChatDisplayElementUnk(int posX, int posY, DWORD elementState);
    };

    static_assert_cpp98_obj(sizeof(GameSynchronyState) == 1090072, GameSynchronyState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(GameSynchronyState, false, Address::SHC_3BB0A8C1_0x0191D768) pDAT_GameSynchronyState;

} // namespace Synchrony
} // namespace OpenSHC
