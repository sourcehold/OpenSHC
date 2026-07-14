/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony/ProtocolDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Util/FunctionTypes/NoArgCallback.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Util::FunctionTypes::NoArgCallback;

#pragma pack(push, 1)
    // SIZE: 0x000004F8
    typedef struct ProtocolDefinedData {

        undefined1 padding_0x0[4]; // 0x00000000 length: 4
        int resetMatchTimersCfg_0x4[12][2]; // 0x00000004 length: 96
        int resetMatchTimersCfg_0x64[39][3]; // 0x00000064 length: 468
        undefined1 padding_0x238[8]; // 0x00000238 length: 8
        char** clickTauntOrChatCfg_0x240[21]; // 0x00000240 length: 84
        NoArgCallback* handleFunctions; // 0x00000294 length: 4
        NoArgCallback* field16_0x298; // 0x00000298 length: 4
        NoArgCallback* waitForMultiplayerHostCfg_0x29c; // 0x0000029C length: 4
        NoArgCallback* initialAnnounceToHostCfg_0x2a0; // 0x000002A0 length: 4
        NoArgCallback* scenarioDescription_MainCfg_0x2a4; // 0x000002A4 length: 4
        NoArgCallback* field20_0x2a8; // 0x000002A8 length: 4
        NoArgCallback* gameLost_DoEveryFrameCfg_0x2ac; // 0x000002AC length: 4
        NoArgCallback* triggerLobbyPlayerInformatCfg_0x2b0; // 0x000002B0 length: 4
        NoArgCallback* field23_0x2b4; // 0x000002B4 length: 4
        NoArgCallback* lobbyMenu_DoEveryFrameCfg_0x2b8; // 0x000002B8 length: 4
        NoArgCallback* triggerLobbyPlayerInformatCfg_0x2bc; // 0x000002BC length: 4
        NoArgCallback* lobbyMenu_LobbyscreenStartCfg_0x2c0; // 0x000002C0 length: 4
        NoArgCallback* recomputeHashesAndSendResyCfg_0x2c4; // 0x000002C4 length: 4
        NoArgCallback* reorderTeamsAndPositionsCfg_0x2c8; // 0x000002C8 length: 4
        NoArgCallback* someChatMessageSelectionCfg_0x2cc; // 0x000002CC length: 4
        NoArgCallback* queueClickNavigateMenuOrEsCfg_0x2d0; // 0x000002D0 length: 4
        NoArgCallback* createTribeFromSelectedUniCfg_0x2d4; // 0x000002D4 length: 4
        NoArgCallback* giveMoveCommandCfg_0x2d8; // 0x000002D8 length: 4
        NoArgCallback* mapEditorLandscaping_QueueCfg_0x2dc; // 0x000002DC length: 4
        NoArgCallback* mapEditorLandscaping_QueueCfg_0x2e0; // 0x000002E0 length: 4
        NoArgCallback* mapEditorLandscaping_QueueCfg_0x2e4; // 0x000002E4 length: 4
        NoArgCallback* inGameMenu_TriggerPlaceBuiCfg_0x2e8; // 0x000002E8 length: 4
        NoArgCallback* mapEditorLandscaping_QueueCfg_0x2ec; // 0x000002EC length: 4
        NoArgCallback* mapEditorLandscaping_QueueCfg_0x2f0; // 0x000002F0 length: 4
        NoArgCallback* mapEditorLandscaping_QueueCfg_0x2f4; // 0x000002F4 length: 4
        NoArgCallback* inGameMenu_TriggerPlaceWalCfg_0x2f8; // 0x000002F8 length: 4
        NoArgCallback* mapEditorLandscaping_QueueCfg_0x2fc; // 0x000002FC length: 4
        NoArgCallback* mapEditorLandscaping_QueueCfg_0x300; // 0x00000300 length: 4
        NoArgCallback* inGameMenu_TriggerPlaceBuiCfg_0x304; // 0x00000304 length: 4
        NoArgCallback* buildMenu_DeleteActionCfg_0x308; // 0x00000308 length: 4
        NoArgCallback* field45_0x30c; // 0x0000030C length: 4
        NoArgCallback* buildingAndStatusMenu_MercCfg_0x310; // 0x00000310 length: 4
        NoArgCallback* field47_0x314; // 0x00000314 length: 4
        NoArgCallback* buildingAndStatusMenu_WorkCfg_0x318; // 0x00000318 length: 4
        NoArgCallback* queueChangeTaxesCfg_0x31c; // 0x0000031C length: 4
        NoArgCallback* buildingAndStatusMenu_ChanCfg_0x320; // 0x00000320 length: 4
        NoArgCallback* queueCommand_36_variation2Cfg_0x324; // 0x00000324 length: 4
        NoArgCallback* buildingAndStatusMenu_DrawCfg_0x328; // 0x00000328 length: 4
        NoArgCallback* buildingAndStatusMenu_BuySCfg_0x32c; // 0x0000032C length: 4
        NoArgCallback* general_LaunchOrQuitMultipCfg_0x330; // 0x00000330 length: 4
        NoArgCallback* saveLoadMap_ButtonsCfg_0x334; // 0x00000334 length: 4
        NoArgCallback* buildMenu_DeleteActionCfg_0x338; // 0x00000338 length: 4
        NoArgCallback* inGameMenu_TriggerPlaceBuiCfg_0x33c; // 0x0000033C length: 4
        NoArgCallback* buildingAndStatusMenu_BuilCfg_0x340; // 0x00000340 length: 4
        NoArgCallback* field59_0x344; // 0x00000344 length: 4
        NoArgCallback* buildingAndStatusMenu_GateCfg_0x348; // 0x00000348 length: 4
        NoArgCallback* processGameTickCfg_0x34c; // 0x0000034C length: 4
        NoArgCallback* lobbyMenu_LobbyscreenStartCfg_0x350; // 0x00000350 length: 4
        NoArgCallback* lobbyMenu_DoEveryFrameCfg_0x354; // 0x00000354 length: 4
        NoArgCallback* commandLoadMapHeaderCfg_0x358; // 0x00000358 length: 4
        NoArgCallback* loadOrSaveGameCfg_0x35c; // 0x0000035C length: 4
        NoArgCallback* submitMSVMapIndexAndProperCfg_0x360; // 0x00000360 length: 4
        NoArgCallback* lobbyMenu_LobbyscreenStartCfg_0x364; // 0x00000364 length: 4
        NoArgCallback* playerNameUnkCfg_0x368; // 0x00000368 length: 4
        NoArgCallback* checkGameSyncCfg_0x36c; // 0x0000036C length: 4
        NoArgCallback* processGameTickCfg_0x370; // 0x00000370 length: 4
        NoArgCallback* processGameTickCfg_0x374; // 0x00000374 length: 4
        NoArgCallback* processGameTickCfg_0x378; // 0x00000378 length: 4
        NoArgCallback* processGameTickCfg_0x37c; // 0x0000037C length: 4
        NoArgCallback* processGameTickCfg_0x380; // 0x00000380 length: 4
        NoArgCallback* processGameTickCfg_0x384; // 0x00000384 length: 4
        NoArgCallback* processGameTickCfg_0x388; // 0x00000388 length: 4
        NoArgCallback* processGameTickCfg_0x38c; // 0x0000038C length: 4
        NoArgCallback* processGameTickCfg_0x390; // 0x00000390 length: 4
        NoArgCallback* processGameTickCfg_0x394; // 0x00000394 length: 4
        NoArgCallback* processGameTickCfg_0x398; // 0x00000398 length: 4
        NoArgCallback* processGameTickCfg_0x39c; // 0x0000039C length: 4
        NoArgCallback* processGameTickCfg_0x3a0; // 0x000003A0 length: 4
        NoArgCallback* buildingAndStatusMenu_RepaCfg_0x3a4; // 0x000003A4 length: 4
        NoArgCallback* inGameMenu_TriggerPlaceBuiCfg_0x3a8; // 0x000003A8 length: 4
        NoArgCallback* queueUnitStanceCfg_0x3ac; // 0x000003AC length: 4
        NoArgCallback* extendRallyPointCfg_0x3b0; // 0x000003B0 length: 4
        NoArgCallback* queueTribeCommandCfg_0x3b4; // 0x000003B4 length: 4
        NoArgCallback* field88_0x3b8; // 0x000003B8 length: 4
        NoArgCallback* field89_0x3bc; // 0x000003BC length: 4
        NoArgCallback* field90_0x3c0; // 0x000003C0 length: 4
        NoArgCallback* commitPlacementUndoCfg_0x3c4; // 0x000003C4 length: 4
        NoArgCallback* field92_0x3c8; // 0x000003C8 length: 4
        NoArgCallback* inGameMenu_UnitSelectionAnCfg_0x3cc; // 0x000003CC length: 4
        NoArgCallback* detectTileUnitDesyncCfg_0x3d0; // 0x000003D0 length: 4
        NoArgCallback* processGameTickCfg_0x3d4; // 0x000003D4 length: 4
        NoArgCallback* processGameTickCfg_0x3d8; // 0x000003D8 length: 4
        NoArgCallback* processGameTickCfg_0x3dc; // 0x000003DC length: 4
        NoArgCallback* field98_0x3e0; // 0x000003E0 length: 4
        NoArgCallback* processGameTickCfg_0x3e4; // 0x000003E4 length: 4
        NoArgCallback* lobbyMenu_PlayerListAndNpcCfg_0x3e8; // 0x000003E8 length: 4
        NoArgCallback* general_ToolbarButtonPressCfg_0x3ec; // 0x000003EC length: 4
        NoArgCallback* processGameTickCfg_0x3f0; // 0x000003F0 length: 4
        NoArgCallback* syncRelatedSomethingCfg_0x3f4; // 0x000003F4 length: 4
        NoArgCallback* someMultiplayerInfoUnkDispCfg_0x3f8; // 0x000003F8 length: 4
        NoArgCallback* processGameTickCfg_0x3fc; // 0x000003FC length: 4
        NoArgCallback* onlineVoteQuitAndQuitGame_Cfg_0x400; // 0x00000400 length: 4
        NoArgCallback* windowMsgProcessingFuncCfg_0x404; // 0x00000404 length: 4
        NoArgCallback* checkMultiplayerLaggingPlaCfg_0x408; // 0x00000408 length: 4
        NoArgCallback* processGameTickCfg_0x40c; // 0x0000040C length: 4
        NoArgCallback* removePlayerFromLobbyCfg_0x410; // 0x00000410 length: 4
        NoArgCallback* identityOptions_ConfirmCfg_0x414; // 0x00000414 length: 4
        NoArgCallback* buildMenu_DeleteActionCfg_0x418; // 0x00000418 length: 4
        NoArgCallback* checkMultiplayerLaggingPlaCfg_0x41c; // 0x0000041C length: 4
        NoArgCallback* someMultiplayerInfoUnkDispCfg_0x420; // 0x00000420 length: 4
        NoArgCallback* processGameTickCfg_0x424; // 0x00000424 length: 4
        NoArgCallback* processGameTickCfg_0x428; // 0x00000428 length: 4
        NoArgCallback* inGameMenu_TriggerPlaceBuiCfg_0x42c; // 0x0000042C length: 4
        NoArgCallback* lobbyMenu_LobbyscreenStartCfg_0x430; // 0x00000430 length: 4
        NoArgCallback* windowMsgProcessingFuncCfg_0x434; // 0x00000434 length: 4
        NoArgCallback* sendReceiveMap_MainCfg_0x438; // 0x00000438 length: 4
        NoArgCallback* lobbyMenu_DoEveryFrameCfg_0x43c; // 0x0000043C length: 4
        NoArgCallback* sendReceiveMap_MainCfg_0x440; // 0x00000440 length: 4
        NoArgCallback* field123_0x444; // 0x00000444 length: 4
        NoArgCallback* field124_0x448; // 0x00000448 length: 4
        NoArgCallback* reorderTeamsAndPositionsCfg_0x44c; // 0x0000044C length: 4
        NoArgCallback* field126_0x450; // 0x00000450 length: 4
        NoArgCallback* aiLordSelect_MainCfg_0x454; // 0x00000454 length: 4
        NoArgCallback* alliesSendAndRequestGoods_Cfg_0x458; // 0x00000458 length: 4
        NoArgCallback* processGameTickCfg_0x45c; // 0x0000045C length: 4
        NoArgCallback* processGameTickCfg_0x460; // 0x00000460 length: 4
        NoArgCallback* progressBarBox_LoadAndSaveCfg_0x464; // 0x00000464 length: 4
        NoArgCallback* lobbyMenu_DoEveryFrameCfg_0x468; // 0x00000468 length: 4
        NoArgCallback* hostChecksLobbyAIVAvailabiCfg_0x46c; // 0x0000046C length: 4
        NoArgCallback* tacticalPowerBar_MainCfg_0x470; // 0x00000470 length: 4
        int menuModalRenderFunction_FiCfg_0x474[32]; // 0x00000474 length: 128
        char** base64EncodeCharacterLookuCfg_0x4f4; // 0x000004F4 length: 4

    } ProtocolDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(ProtocolDefinedData) == 1272, ProtocolDefinedData);
} // namespace Synchrony
} // namespace OpenSHC
