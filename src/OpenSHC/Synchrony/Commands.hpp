/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony/Commands.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Synchrony {
    namespace Commands {

        void __cdecl QueueChangeGameIntensityOrBalance();

        void __cdecl QueueChangeTaxes();

        void __cdecl InitialAnnounceReply();

        void __cdecl AnnounceGameVersion();

        void __cdecl AnnouncePlayerInformationSuchAsNameLordTypeAndAvailableAIVS();

        void __cdecl ShareGameSeedAndMultiplayerSettingsAndStartGame();

        void __cdecl CommandCheckSync();

        void __cdecl AnnounceTeamsAndPositions();

        void __cdecl ClickNavigateMenuOrEscape();

        void __cdecl MakeUnitSelection();

        void __cdecl ClickMoveUnit();

        void __cdecl ClickErase();

        void __cdecl ClickSetLand();

        void __cdecl ClickRaiseLand();

        void __cdecl ClickSetTerrain();

        void __cdecl ClickHeightEqualize();

        void __cdecl ClickTerrainHeightMinOrMax();

        void __cdecl ClickCreatePlateau();

        void __cdecl ClickPlaceWall();

        void __cdecl ClickPlaceRockOrTree();

        void __cdecl ClickRaiseLand2Unk();

        void __cdecl ClickPlaceBuilding();

        void __cdecl ClickDestroyBuilding();

        void __cdecl ClickRecruitUnit();

        void __cdecl _REMOVED_COMMAND1_();

        void __cdecl ClickSetBuildingProductionType();

        void __cdecl ClickChangeTaxes();

        void __cdecl ClickChangeRations();

        void __cdecl ClickGiveUnitsInstruction();

        void __cdecl ClickSomethingWithDrawBridgeUnk();

        void __cdecl ClickBuyOrSell();

        void __cdecl ClickDestroy();

        void __cdecl ClickPlaceSiegeTent();

        void __cdecl ClickBuildingSleep();

        void __cdecl ClickCreateAnimal();

        void __cdecl ClickOpenOrCloseGate();

        void __cdecl ShareDesyncedHashes();

        void __cdecl CommandChangeMapSelection();

        void __cdecl AcknowledgeMapExistence();

        void __cdecl ShareMSVMapIndex();

        void __cdecl ClickInitOrChangeGameIntensityAndBalance();

        void __cdecl SharePlayerName();

        void __cdecl SendResyncCharLayer();

        void __cdecl ResyncShortLayer();

        void __cdecl ResyncStatus2();

        void __cdecl ResetSyncStatusUnk();

        void __cdecl ClickRepairTower();

        void __cdecl CommandSpawnEntity();

        void __cdecl ClickUnitStance();

        void __cdecl ClickExtendRallyPoint();

        void __cdecl SiegeEngineRelated();

        void __cdecl TribeRelated1();

        void __cdecl ReleaseDogs();

        void __cdecl RemoveTowerSiegeEngine();

        void __cdecl DestroyWallOrPitch();

        void __cdecl DeselectUnit();

        void __cdecl TriggerRecalculationOfUnitSameTileLinkage();

        void __cdecl ResyncZone();

        void __cdecl KickPlayerUnk();

        void __cdecl CommandSelectionReplenishAmmo();

        void __cdecl BroadCastSyncRelatedStatus();

        void __cdecl VoteKick_K_D_B_G_J();

        void __cdecl SyncPacketSizeAnnouncement();

        void __cdecl ShareAnnouncementWithHost();

        void __cdecl CloseModalDialogForEveryone();

        void __cdecl SomePlayerNameUpdateCommand();

        void __cdecl FlagsAndBraziersCommandUnk();

        void __cdecl NotifyLaggingPlayer();

        void __cdecl SomeKindOfMultiplayerPingUnk();

        void __cdecl ShareGameStatePartialHashes();

        void __cdecl ResyncStatusStart();

        void __cdecl SetUnitAssemblyPoint();

        void __cdecl StartSendingMapFile();

        void __cdecl StartReceivingMapFile();

        void __cdecl MapSendingRelated();

        void __cdecl HostAnnounceRoundTable();

        void __cdecl AddAIPlayer();

        void __cdecl SendPlayerToPlayerRequestOrResponse();

        void __cdecl ShareAIVHash();

        void __cdecl UpdateSkirmishGameMenuFaceBitmap();

        void __cdecl ActiveTacticalPowers();

        void __cdecl InitialAnnounceToHost();

        void __cdecl AssignPlayerIDToPlayerSlot();

        void __cdecl TriggerLobbyPlayerInformationRefresh();

        void __cdecl ClickTauntOrChat();

        void __cdecl AutoSaveTriggered();

        void __cdecl SetPlayerNameUnk();

        void __cdecl CommandLoadMapHeader();

        void __cdecl SubmitMSVMapIndexAndProperties();

        void __cdecl ResyncChimp();

        void __cdecl SendResyncBuilding();

        void __cdecl SendResyncVeg();

        void __cdecl SendResyncTribe();

        void __cdecl SendResyncPlayerData();

        void __cdecl SendResyncUnknown();

        void __cdecl SendResyncEntity();

        void __cdecl SendResyncIntLayer();

        void __cdecl DestroyPlayer();

        void __cdecl ResyncMoat();

        void __cdecl ResyncTeleClimb();

        void __cdecl ResyncPitch();

        void __cdecl CommandSwitchTeams();

        void __cdecl SyncRelatedSomething();

        void __cdecl SendQuitGameQuestion();

        void __cdecl ShareQuitGameVote();

        void __cdecl VoteKick_SEND_L_E_C_A_F_H_ZAP();

        void __cdecl ShareMapHashForMapName();

        void __cdecl ShareMapPart();

        void __cdecl ResyncVillage();

        void __cdecl ResyncAIZone();

        void __cdecl AskForPlayerSlotAssignment();

        void __cdecl HostShareLobbyState();

        void __cdecl ResyncStartCS_CS_Sub();

        void __cdecl ResyncResumeCS();

        void __cdecl HostRemoveAIPlayerBySlotID();

    } // namespace Commands
} // namespace Synchrony
} // namespace OpenSHC
