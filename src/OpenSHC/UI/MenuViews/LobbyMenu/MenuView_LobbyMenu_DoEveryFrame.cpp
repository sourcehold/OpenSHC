#include "../LobbyMenu.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/LobbyMenu.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_00b95b74.hpp"
#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_00b960f4.hpp"
#include "OpenSHC/Globals/DAT_00b960f8.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapNameCache.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DWORD_00b95b1c.hpp"
#include "OpenSHC/Globals/INT_00b95958.hpp"
#include "OpenSHC/Globals/INT_00b95f6c.hpp"
#include "OpenSHC/Globals/INT_00b960f0.hpp"
#include "OpenSHC/Globals/INT_00b960fc.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::IO::FileResourceType;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004482F0
        void LobbyMenu::MenuView_LobbyMenu_DoEveryFrame()
        {
            char cVar1;
            MenuModalTypeInt MVar2;
            BOOLEnum BVar3;
            int iVar4;
            int* piVar5;
            char* pcVar6;
            int iVar7;
            uint uVar8;
            short* psVar9;
            int iVar10;
            char* pcVar11;
            int iVar12;
            undefined1* x2;
            dword _mapID;
            int bottom;
            int iVar13;
            bool bVar14;
            int* local_400;
            MenuModalTypeInt local_3fc;
            undefined4 local_3f8;
            char local_3f4[4];
            char local_3f0[1004];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_400;
            MVar2 = timeGetTime();
            local_3fc = MVar2;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
            if ((DAT_00b960dc::instance != 0) && (DAT_GameSynchronyState::instance.reparseMaps == FALSE)) {
                DAT_GameCore::instance.hasMenuRenderedUnk = 1;
                if (DAT_00b960dc::instance < 0) {
                    iVar10
                        = (int)((ulonglong)((longlong)(int)(MVar2 - DWORD_00b95b1c::instance) * -0x66666667) >> 0x20);
                    DAT_ButtonBackgroundBlendStrength::instance
                        = DAT_ButtonBackgroundBlendStrength::instance + ((iVar10 >> 4) - (iVar10 >> 0x1f));
                    if (DAT_ButtonBackgroundBlendStrength::instance < 1) {
                        DAT_ButtonBackgroundBlendStrength::instance = 0;
                        DAT_00b960dc::instance = 0;
                    }
                } else {
                    DAT_ButtonBackgroundBlendStrength::instance
                        = DAT_ButtonBackgroundBlendStrength::instance + (int)(MVar2 - DWORD_00b95b1c::instance) / 0x28;
                    if (0x1f < DAT_ButtonBackgroundBlendStrength::instance) {
                        DAT_ButtonBackgroundBlendStrength::instance = 0x20;
                        DAT_GameCore::instance.menuSwitchDelay = 0;
                    }
                }
            }
            BVar3 = MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)();
            if (BVar3 == FALSE) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithCustomBlendedBackground,
                    DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 10,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 5, 0x228, 0xd8,
                    (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
                iVar10 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x10;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xf,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 10,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x22d,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xd8,
                    ((int)(iVar10 + (iVar10 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                iVar10 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x10;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 10,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xe3,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x172,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x193,
                    ((int)(iVar10 + (iVar10 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                if (DAT_ButtonBackgroundBlendStrength::instance == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                        DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 10,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xe3,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x172,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x193,
                        (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                }
                iVar7 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
                iVar12 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                local_400 = (int*)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x310);
                iVar4 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x10;
                iVar10 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x15f;
                iVar13 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x214;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x234, iVar10,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x2fc, iVar13,
                    ((int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                if (DAT_00b960dc::instance == 0) {
                    x2 = (undefined1*)((int)local_400 + 1);
                    iVar12 = iVar12 + 0x233;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine,
                        DAT_PencilRenderCore::ptr)(iVar12, iVar7 + 0x15e, (int)((int)(x2)), iVar7 + 0x15e,
                        (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine,
                        DAT_PencilRenderCore::ptr)(iVar12, iVar7 + 0x215, (int)((int)(x2)), iVar7 + 0x215,
                        (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine,
                        DAT_PencilRenderCore::ptr)(iVar12, iVar7 + 0x173, (int)((int)(x2)), iVar7 + 0x173,
                        (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        iVar12, iVar10, iVar12, iVar13, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)((int)x2,
                        iVar10, (int)((int)(x2)), iVar13, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine,
                        DAT_PencilRenderCore::ptr)((int)(local_400 + -5), iVar10, (int)((int)((local_400 + -5))),
                        iVar13, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine,
                        DAT_PencilRenderCore::ptr)((int)((int)local_400 + -0x13), iVar7 + 0x200,
                        (int)((int)(local_400)), iVar7 + 0x200,
                        (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                }
            }
            iVar12 = 1;
            iVar10 = iVar12;
            if (DAT_GameSynchronyState::instance.DAT_MapFileReceivingState == 1) {
                do {
                    if ((((DAT_GameSynchronyState::instance.mapSendingFileHandles[iVar12] != (FILE*)0x0)
                             && (iVar10 = 0, DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar12] != -1))
                            && (DAT_GameSynchronyState::instance.field282_0x109d98[iVar12] == 1))
                        && (DAT_GameSynchronyState::instance.field290_0x109e20[iVar12] != 1)) {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                            = DAT_GameSynchronyState::instance.field289_0x109dfc[iVar12];
                        DAT_GameSynchronyState::instance.field289_0x109dfc[iVar12]
                            = DAT_GameSynchronyState::instance.field289_0x109dfc[iVar12] + 1;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = iVar12;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                            (OpenSHC::Commands::GameCommandType)(OpenSHC::Commands::GCT_START_OR_STOP_SEND_MAP_FILEUnk
                                | OpenSHC::Commands::GCT_MULTIPLAYER_INITIATE_ANNOUNCE_HOST));
                    }
                    iVar12 = iVar12 + 1;
                } while (iVar12 < 9);
                if (iVar10 != 0) {
                    psVar9 = DAT_GameSynchronyState::instance.field282_0x109d98 + 2;
                    piVar5 = DAT_GameSynchronyState::instance.field290_0x109e20 + 1;
                    do {
                        if (((piVar5[-0x425de] != -1) && (psVar9[-1] == 1)) && (*piVar5 == 1)) {
                            iVar10 = 0;
                        }
                        if (((piVar5[-0x425dd] != -1) && (*psVar9 == 1)) && (piVar5[1] == 1)) {
                            iVar10 = 0;
                        }
                        if (((piVar5[-0x425dc] != -1) && (psVar9[1] == 1)) && (piVar5[2] == 1)) {
                            iVar10 = 0;
                        }
                        if (((piVar5[-0x425db] != -1) && (psVar9[2] == 1)) && (piVar5[3] == 1)) {
                            iVar10 = 0;
                        }
                        psVar9 = psVar9 + 4;
                        piVar5 = piVar5 + 4;
                    } while ((int)psVar9 < 0x1a27514);
                    if (iVar10 != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                        DAT_GameSynchronyState::instance.DAT_MapFileReceivingState = 0;
                        DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                    }
                }
            }
            iVar12 = 0xfa;
            iVar10 = MACRO_CALL_MEMBER(
                OpenSHC::Synchrony::GameSynchronyState_Func::countActiveHumanPlayers, DAT_GameSynchronyState::ptr)();
            MVar2 = local_3fc;
            if (4 < iVar10) {
                iVar12 = 0x177;
            }
            if (iVar12 < (int)(local_3fc - INT_00b960f0::instance)) {
                INT_00b960f0::instance = local_3fc;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = DAT_00b960f8::instance;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                    = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_UPDATE_LOBBY_FACE_BITMAPSPECIALTRANSMITLOGIC);
                DAT_00b960f8::instance = DAT_00b960f8::instance + 1;
                if (0x41 < (int)DAT_00b960f8::instance) {
                    DAT_00b960f8::instance = 0;
                }
            }
            if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU)
                goto LAB_00448a80;
            if (30000 < (int)(MVar2 - INT_00b960fc::instance)) {
                INT_00b960fc::instance = MVar2;
                if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                    if (INT_00b95958::instance == 0) {
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::DisplayMapDescriptionAndAllocatePlayersToSlots)();
                    }
                } else {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_TRIGGER_LOBBY_PLAYER_INFORMATION_REFRESH);
                }
            }
            if (DAT_GameSynchronyState::instance.reparseMaps != FALSE) {
                iVar10 = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::countOccupiedPlayerSlots,
                    DAT_GameSynchronyState::ptr)();
                DAT_MouseState::instance.waitCursorToggle = 1;
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetCursorDependingOnProgramState)();
                DAT_GameSynchronyState::instance.reparseMaps = FALSE;
                MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::mapNames_syncLoadedMapNames, DAT_ResourceManager::ptr)();
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected == -1) {
                    DAT_MapNameCache::instance[0] = '\0';
                } else {
                    pcVar6 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                        DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                            .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected + -1]);
                    pcVar11 = DAT_MapNameCache::instance;
                    do {
                        cVar1 = *pcVar6;
                        *pcVar11 = cVar1;
                        pcVar6 = pcVar6 + 1;
                        pcVar11 = pcVar11 + 1;
                    } while (cVar1 != '\0');
                }
                iVar12 = 0;
                _mapID = 0;
                if (0 < DAT_ResourceManager::instance.mapFileCounter) {
                    do {
                        pcVar11
                            = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                                DAT_ResourceManager::ptr)(_mapID);
                        pcVar6 = local_3f4;
                        do {
                            cVar1 = *pcVar11;
                            *pcVar6 = cVar1;
                            pcVar11 = pcVar11 + 1;
                            pcVar6 = pcVar6 + 1;
                        } while (cVar1 != '\0');
                        pcVar6 = (char*)((int)&local_3f8 + 3);
                        do {
                            pcVar11 = pcVar6;
                            pcVar6 = pcVar11 + 1;
                        } while (pcVar11[1] != '\0');
                        strcpy(pcVar11 + 1, ".map");
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                            DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_MAPS, (char const*)((int)(local_3f4)));
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::loadMapMetaByID, DAT_ResourceManager::ptr)(
                            _mapID);
                        iVar4 = DAT_GameCore::instance.mapPlayerCount;
                        iVar7 = DAT_GameCore::instance.mapU4Int0_2;
                        DAT_00b95b74::instance = 0;
                        DAT_00b960f4::instance = 0;
                        if ((DAT_GameCore::instance.mapType == 1) && (1 < DAT_GameCore::instance.mapPlayerCount)) {
                            bVar14 = DAT_GameCore::instance.mapU4Int0_2 != 0;
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar12 + -1] = _mapID;
                            iVar13 = DAT_GameCore::instance.savedMapBalance;
                            if (bVar14) {
                                iVar4 = iVar4 + -1;
                                DAT_GameCore::instance.mapPlayerCount = iVar4;
                            }
                            DAT_GameSynchronyState::instance.mapPlayerCountArray[_mapID] = iVar4;
                            DAT_GameSynchronyState::instance.mapBalanceArray[_mapID] = iVar13;
                            DAT_GameSynchronyState::instance.mapU4Int0_2Array[_mapID] = iVar7;
                            DAT_GameSynchronyState::instance.unknownMapRelatedReceivedDataArray[_mapID]
                                = (uint)(iVar10 <= iVar4) * 2 + -1;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _mapID;
                            if (DAT_GameSynchronyState::instance.isHost != FALSE) {
                                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_LOAD_MAP_HEADER);
                            }
                            iVar12 = iVar12 + 1;
                        }
                        _mapID = _mapID + 1;
                    } while ((int)_mapID < DAT_ResourceManager::instance.mapFileCounter);
                }
                DAT_GameCore::instance.descriptionUseStringTable = 1;
                DAT_GameCore::instance.mapDescUseStringTable = 1;
                DAT_GameCore::instance.descriptionStringTableIndex = 0;
                DAT_GameCore::instance.mapDescUseStringTableIndex = 0;
                DAT_MouseState::instance.waitCursorToggle = 0;
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected == -1) {
                    DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = 0;
                }
                DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber = iVar12;
                if (iVar12 != 0) {
                    if (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected == -1) {
                        DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = 0;
                    }
                    local_3fc = DAT_MenuModalComposition1::instance.activeModalDialogID;
                    DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
                    MACRO_CALL(OpenSHC::UI::MenuItems::LobbyMenu_Func::MenuItemActionHandler_LobbyMenu_MapSelectHeader)(
                        -DAT_GameSynchronyState::instance.field248_0x109250);
                    iVar12 = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected;
                    iVar7 = iVar12;
                    if (DAT_GameSynchronyState::instance
                            .mapPlayerCountArray[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar12 + -1]]
                        < iVar10) {
                        for (; iVar7 < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber;
                            iVar7 = iVar7 + 1) {
                            if (iVar10
                                <= DAT_GameSynchronyState::instance.mapPlayerCountArray[DAT_MenuTextInputState::instance
                                        .DAT_ArrayOfMapIndices[iVar7 + -1]])
                                goto LAB_00448a08;
                        }
                        iVar7 = 0;
                        if (0 < iVar12) {
                            do {
                                if (iVar10 <= DAT_GameSynchronyState::instance.mapPlayerCountArray
                                        [DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar7 + -1]])
                                    goto LAB_00448a08;
                                iVar7 = iVar7 + 1;
                            } while (iVar7 < iVar12);
                        }
                    }
                    goto LAB_00448a3a;
                }
                goto LAB_00448a5b;
            }
        LAB_00448a72:
            if (DAT_GameSynchronyState::instance.field239_0x1072f8 != 0) {
                DAT_GameSynchronyState::instance.field239_0x1072f8
                    = DAT_GameSynchronyState::instance.field239_0x1072f8 + -1;
            }
        LAB_00448a80:
            MACRO_CALL_MEMBER(
                OpenSHC::Synchrony::GameSynchronyState_Func::compareGameVersions, DAT_GameSynchronyState::ptr)();
            iVar12 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            iVar10 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE) {
                piVar5 = (int*)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x224);
                iVar7 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x17f;
                iVar13 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x10;
                iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x15e;
                bottom = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1a9;
                INT_00b95f6c::instance = 0;
                local_400 = piVar5;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                    iVar7, iVar4, (int)((int)(piVar5)), bottom, ((int)(iVar13 + (iVar13 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                if (DAT_00b960dc::instance == 0) {
                    iVar13 = iVar10 + 0x225;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine,
                        DAT_PencilRenderCore::ptr)(iVar10 + 0x17e, iVar12 + 0x15d, iVar13, iVar12 + 0x15d,
                        (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine,
                        DAT_PencilRenderCore::ptr)(iVar10 + 0x17e, iVar12 + 0x1aa, iVar13, iVar12 + 0x1aa,
                        (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine,
                        DAT_PencilRenderCore::ptr)(iVar10 + 0x17e, iVar4, iVar10 + 0x17e, bottom,
                        (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        iVar13, iVar4, iVar13, bottom, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                    piVar5 = local_400;
                }
                BVar3 = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                    iVar7, iVar4, (int)piVar5 - iVar7, bottom - iVar4);
                if (BVar3 != FALSE) {
                    INT_00b95f6c::instance = 1;
                }
                if (DAT_00b960dc::instance == 0) {
                    iVar10 = iVar10 + 0x184;
                    iVar7 = iVar12 + 0x15f;
                    uVar8 = 0;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] != -1)
                        || (DAT_GameSynchronyState::instance.currentAIArray[1] != 0)) {
                        uVar8 = 1;
                    }
                    if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] != -1)
                        || (DAT_GameSynchronyState::instance.currentAIArray[2] != 0)) {
                        uVar8 = uVar8 + 1;
                    }
                    if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] != -1)
                        || (DAT_GameSynchronyState::instance.currentAIArray[3] != 0)) {
                        uVar8 = uVar8 + 1;
                    }
                    if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] != -1)
                        || (DAT_GameSynchronyState::instance.currentAIArray[4] != 0)) {
                        uVar8 = uVar8 + 1;
                    }
                    if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] != -1)
                        || (DAT_GameSynchronyState::instance.currentAIArray[5] != 0)) {
                        uVar8 = uVar8 + 1;
                    }
                    if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] != -1)
                        || (DAT_GameSynchronyState::instance.currentAIArray[6] != 0)) {
                        uVar8 = uVar8 + 1;
                    }
                    if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] != -1)
                        || (DAT_GameSynchronyState::instance.currentAIArray[7] != 0)) {
                        uVar8 = uVar8 + 1;
                    }
                    if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] != -1)
                        || (DAT_GameSynchronyState::instance.currentAIArray[8] != 0)) {
                        uVar8 = uVar8 + 1;
                    }
                    if (uVar8 < 5) {
                        iVar7 = iVar12 + 0x172;
                    }
                    iVar12 = 0;
                    iVar4 = 0x2cf;
                    local_400 = DAT_GameSynchronyState::instance.currentAIArray + 1;
                    local_3fc = 8;
                    local_3f8 = iVar10;
                    do {
                        if (local_400[-0x1b] == -1) {
                            if (*local_400 != 0) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar4, iVar10, iVar7);
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                                    (int)((int)(*local_400 + 700)), iVar10, iVar7);
                                goto LAB_00448ced;
                            }
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar4, iVar10, iVar7);
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderFacesSmallUnk,
                                DAT_TextureRenderCoreObject::ptr)(iVar4 + -699, iVar10 + 2, iVar7 + 2);
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                                DAT_PencilRenderCore::ptr)(iVar10, iVar7, iVar10 + 0x23, iVar7 + 0x23,
                                (ushort)((int)(COL_BLACK::instance.shortValue)));
                        LAB_00448ced:
                            iVar12 = iVar12 + 1;
                            iVar10 = iVar10 + 0x28;
                            if (iVar12 == 4) {
                                iVar7 = iVar7 + 0x26;
                                iVar10 = local_3f8;
                            }
                        }
                        local_400 = local_400 + 1;
                        iVar4 = iVar4 + 1;
                        local_3fc = local_3fc + -1;
                    } while (local_3fc != 0);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    local_3fc = OpenSHC::UI::Enums::MMT_NO_MENU;
                }
            };
            return;
        LAB_00448a08:
            DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                = iVar7 - DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
            if (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected < 0) {
                iVar10 = 0;
            LAB_00448a34:
                DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected;
                DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = iVar10;
            } else if (7 < DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected) {
                DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + -7;
                iVar10 = 7;
                goto LAB_00448a34;
            }
        LAB_00448a3a:
            MACRO_CALL(OpenSHC::UI::MenuItems::LobbyMenu_Func::MenuItemActionHandler_LobbyMenu_MapSelectTable)(
                DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
            if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::DisplayMapDescriptionAndAllocatePlayersToSlots)();
            }
            DAT_MenuModalComposition1::instance.activeModalDialogID = local_3fc;
        LAB_00448a5b:
            DAT_GameSynchronyState::instance.skirmishRelated1 = -1;
            DWORD_00b95b1c::instance = timeGetTime();
            goto LAB_00448a72;
        }

    }
}
}
