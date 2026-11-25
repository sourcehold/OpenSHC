// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

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
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
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
#include "OpenSHC/Globals/INT_00b95b74.hpp"
#include "OpenSHC/Globals/INT_00b95f6c.hpp"
#include "OpenSHC/Globals/INT_00b960f0.hpp"
#include "OpenSHC/Globals/INT_00b960fc.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004482F0
        void LobbyMenu::MenuView_LobbyMenu_DoEveryFrame()
        {
            int const now = timeGetTime();
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);

            // the menu fades in or out over time
            if (DAT_00b960dc::instance != 0 && !DAT_GameSynchronyState::instance.reparseMaps) {
                int const elapsed = now - DWORD_00b95b1c::instance;
                DAT_GameCore::instance.hasMenuRenderedUnk = 1;
                if ((int)DAT_00b960dc::instance < 0) {
                    DAT_ButtonBackgroundBlendStrength::instance += elapsed / -40;
                    if (DAT_ButtonBackgroundBlendStrength::instance <= 0) {
                        DAT_ButtonBackgroundBlendStrength::instance = 0;
                        DAT_00b960dc::instance = 0;
                    }
                } else {
                    DAT_ButtonBackgroundBlendStrength::instance += elapsed / 40;
                    if (DAT_ButtonBackgroundBlendStrength::instance >= 32) {
                        DAT_ButtonBackgroundBlendStrength::instance = 32;
                        DAT_GameCore::instance.menuSwitchDelay = 0;
                    }
                }
            }

            if (!MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)()) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithCustomBlendedBackground,
                    DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 10,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 5, 552, 216,
                    DAT_ButtonBackgroundBlendStrength::instance);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 15,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 10,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 557,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 216,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 16 / 32 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 10,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 227,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 370,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 403,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 16 / 32 + 32);
                if (DAT_ButtonBackgroundBlendStrength::instance == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                        DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 10,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 227,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 370,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 403,
                        COL_VERY_SOFT_YELLOW::instance.shortValue);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;

                int const left = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 564;
                int const right = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 784;
                int const top = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 351;
                int const bottom = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 532;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                    left, top, right - 20, bottom, (DAT_ButtonBackgroundBlendStrength::instance - 32) * 16 / 32 + 32);
                if (DAT_00b960dc::instance == 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        left - 1, top - 1, right + 1, top - 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        left - 1, bottom + 1, right + 1, bottom + 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        left - 1, top + 20, right + 1, top + 20, COL_VERY_SOFT_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        left - 1, top, left - 1, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        right + 1, top, right + 1, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        right - 20, top, right - 20, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        right - 19, bottom - 20, right, bottom - 20, COL_VERY_SOFT_YELLOW::instance.shortValue);
                }
            }

            // sending the map to the other players: when every file is closed and nobody still asks, reparse
            if (DAT_GameSynchronyState::instance.DAT_MapFileReceivingState == 1) {
                BOOLEnum finished = TRUE;
                for (int player = 1; player < countof(DAT_GameSynchronyState::instance.mapSendingFileHandles);
                    ++player) {
                    if (DAT_GameSynchronyState::instance.mapSendingFileHandles[player] != NULL) {
                        finished = FALSE;
                        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] != -1
                            && DAT_GameSynchronyState::instance.mapTransferStatePerPlayer[player] == 1
                            && DAT_GameSynchronyState::instance.mapSendRequestStatePerPlayer[player] != 1) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                                = DAT_GameSynchronyState::instance.mapTransferTicksPerPlayer[player];
                            DAT_GameSynchronyState::instance.mapTransferTicksPerPlayer[player]++;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = player;
                            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)((OpenSHC::Commands::GameCommandType)106);
                        }
                    }
                }
                if (finished) {
                    for (int player = 1; player < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray);
                        ++player) {
                        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] != -1
                            && DAT_GameSynchronyState::instance.mapTransferStatePerPlayer[player] == 1
                            && DAT_GameSynchronyState::instance.mapSendRequestStatePerPlayer[player] == 1) {
                            finished = FALSE;
                        }
                    }
                    if (finished) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                        DAT_GameSynchronyState::instance.DAT_MapFileReceivingState = 0;
                        DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                    }
                }
            }

            // the faces go out one part at a time, more slowly with more than four players
            int interval = 250;
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Synchrony::GameSynchronyState_Func::countActiveHumanPlayers, DAT_GameSynchronyState::ptr)()
                > 4) {
                interval = 375;
            }
            if (now - INT_00b960f0::instance > interval) {
                INT_00b960f0::instance = now;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = DAT_00b960f8::instance;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                    = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_UPDATE_LOBBY_FACE_BITMAPSPECIALTRANSMITLOGIC);
                DAT_00b960f8::instance++;
                if ((int)DAT_00b960f8::instance >= 66) {
                    DAT_00b960f8::instance = 0;
                }
            }

            if (DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU) {
                if (now - INT_00b960fc::instance > 30000) {
                    INT_00b960fc::instance = now;
                    if (DAT_GameSynchronyState::instance.isHost) {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                            OpenSHC::Commands::GCT_TRIGGER_LOBBY_PLAYER_INFORMATION_REFRESH);
                    } else if (INT_00b95958::instance == 0) {
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::DisplayMapDescriptionAndAllocatePlayersToSlots)();
                    }
                }

                if (DAT_GameSynchronyState::instance.reparseMaps) {
                    int const playerCount
                        = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::countOccupiedPlayerSlots,
                            DAT_GameSynchronyState::ptr)();
                    DAT_MouseState::instance.waitCursorToggle = 1;
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SetCursorDependingOnProgramState)();
                    DAT_GameSynchronyState::instance.reparseMaps = FALSE;
                    MACRO_CALL_MEMBER(
                        OpenSHC::IO::ResourceManager_Func::mapNames_syncLoadedMapNames, DAT_ResourceManager::ptr)();
                    if (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected != -1) {
                        strcpy(DAT_MapNameCache::instance,
                            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                                DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                                    .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                        + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected]));
                    } else {
                        DAT_MapNameCache::instance[0] = '\0';
                    }

                    // every map a skirmish can use goes into the list, and to the other players when hosting
                    int mapCount = 0;
                    for (int mapID = 0; mapID < DAT_ResourceManager::instance.mapFileCounter; ++mapID) {
                        char fileName[1008];
                        strcpy(fileName,
                            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                                DAT_ResourceManager::ptr)(mapID));
                        // ".map"
                        strcat(fileName, S__MAP_005A2294);
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                            DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_MAPS, fileName);
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::loadMapMetaByID, DAT_ResourceManager::ptr)(
                            mapID);
                        INT_00b95b74::instance = 0;
                        DAT_00b960f4::instance = 0;
                        if (DAT_GameCore::instance.mapType == 1 && DAT_GameCore::instance.mapPlayerCount >= 2) {
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[mapCount] = mapID;
                            if (DAT_GameCore::instance.mapU4Int0_2 != 0) {
                                DAT_GameCore::instance.mapPlayerCount--;
                            }
                            DAT_GameSynchronyState::instance.mapPlayerCountArray[mapID]
                                = DAT_GameCore::instance.mapPlayerCount;
                            DAT_GameSynchronyState::instance.mapBalanceArray[mapID]
                                = DAT_GameCore::instance.savedMapBalance;
                            DAT_GameSynchronyState::instance.mapU4Int0_2Array[mapID]
                                = DAT_GameCore::instance.mapU4Int0_2;
                            if (DAT_GameCore::instance.mapPlayerCount >= playerCount) {
                                DAT_GameSynchronyState::instance.unknownMapRelatedReceivedDataArray[mapID] = 1;
                            } else {
                                DAT_GameSynchronyState::instance.unknownMapRelatedReceivedDataArray[mapID] = -1;
                            }
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = mapID;
                            if (DAT_GameSynchronyState::instance.isHost) {
                                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_LOAD_MAP_HEADER);
                            }
                            ++mapCount;
                        }
                    }

                    DAT_GameCore::instance.descriptionUseStringTable = TRUE;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    DAT_GameCore::instance.descriptionStringTableIndex = 0;
                    DAT_GameCore::instance.mapDescUseStringTableIndex = 0;
                    DAT_MouseState::instance.waitCursorToggle = 0;
                    DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber = mapCount;
                    if (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected == -1) {
                        DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = 0;
                        // -1 is stored again although just compared (dropping the store loses the match)
                        DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = -1;
                    }
                    if (mapCount != 0) {
                        if (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected == -1) {
                            DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = 0;
                        }
                        MenuModalTypeInt const openDialog = DAT_MenuModalComposition1::instance.activeModalDialogID;
                        DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
                        MACRO_CALL(
                            OpenSHC::UI::MenuItems::LobbyMenu_Func::MenuItemActionHandler_LobbyMenu_MapSelectHeader)(
                            -(int)DAT_GameSynchronyState::instance.lobbyMapSortOrder);

                        // the selected map has too few places: take the next one that fits, wrapping round the list
                        if (DAT_GameSynchronyState::instance.mapPlayerCountArray[DAT_MenuTextInputState::instance
                                    .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                        + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected]]
                            < playerCount) {
                            // the searches share the block at found (a found index or helpers lose the match)
                            int index;
                            for (index = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                    + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected;
                                index < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber; ++index) {
                                if (DAT_GameSynchronyState::instance.mapPlayerCountArray
                                        [DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[index]]
                                    >= playerCount) {
                                    // to the shared block (the match needs the goto)
                                    goto found;
                                }
                            }
                            for (index = 0; index < DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                    + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected;
                                ++index) {
                                if (DAT_GameSynchronyState::instance.mapPlayerCountArray
                                        [DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[index]]
                                    >= playerCount) {
                                    // to the shared block (the match needs the goto)
                                    goto found;
                                }
                            }
                            // no map fits: past the shared block (the match needs the goto)
                            goto select;
                        found:
                            DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                                = index - DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                            if (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected < 0) {
                                DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                    += DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected;
                                DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = 0;
                            } else if (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected > 7) {
                                DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                    += DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected - 7;
                                DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = 7;
                            }
                        }
                    select:
                        MACRO_CALL(
                            OpenSHC::UI::MenuItems::LobbyMenu_Func::MenuItemActionHandler_LobbyMenu_MapSelectTable)(
                            DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                        if (!DAT_GameSynchronyState::instance.isHost) {
                            MACRO_CALL(OpenSHC::UI::Rendering_Func::DisplayMapDescriptionAndAllocatePlayersToSlots)();
                        }
                        DAT_MenuModalComposition1::instance.activeModalDialogID = openDialog;
                    }
                    DAT_GameSynchronyState::instance.skirmishRelated1 = -1;
                    DWORD_00b95b1c::instance = timeGetTime();
                }

                if (DAT_GameSynchronyState::instance.mapExistenceAckCountdown != 0) {
                    DAT_GameSynchronyState::instance.mapExistenceAckCountdown--;
                }
            }

            MACRO_CALL_MEMBER(
                OpenSHC::Synchrony::GameSynchronyState_Func::compareGameVersions, DAT_GameSynchronyState::ptr)();
            if (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                return;
            }

            // the box of the players' faces
            INT_00b95f6c::instance = 0;
            int const left = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 383;
            int const top = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 350;
            int const right = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 548;
            int const bottom = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 425;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                left, top, right, bottom, (DAT_ButtonBackgroundBlendStrength::instance - 32) * 16 / 32 + 32);
            if (DAT_00b960dc::instance == 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    left - 1, top - 1, right + 1, top - 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    left - 1, bottom + 1, right + 1, bottom + 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    left - 1, top, left - 1, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right + 1, top, right + 1, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                    left, top, right - left, bottom - top)) {
                INT_00b95f6c::instance = 1;
            }
            if (DAT_00b960dc::instance != 0) {
                return;
            }

            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            int const firstX = left + 5;
            int x = firstX;
            int y = top + 1;
            int occupied = 0;
            for (int player = 1; player < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray);
                ++player) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] != -1
                    || DAT_GameSynchronyState::instance.currentAIArray[player] != OpenSHC::AI::AITA_NULL) {
                    ++occupied;
                }
            }

            // two rows of four; a single row sits lower
            if (occupied <= 4) {
                y += 19;
            }
            // the step to the next face is written in both arms (one copy after them loses the match)
            int drawn = 0;
            for (int player = 1; player < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray);
                ++player) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] != -1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, player + 718, x, y);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderFacesSmallUnk,
                        DAT_TextureRenderCoreObject::ptr)(player + 19, x + 2, y + 2);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                        DAT_PencilRenderCore::ptr)(x, y, x + 35, y + 35, COL_BLACK::instance.shortValue);
                    ++drawn;
                    x += 40;
                    if (drawn == 4) {
                        x = firstX;
                        y += 38;
                    }
                } else if (DAT_GameSynchronyState::instance.currentAIArray[player] != OpenSHC::AI::AITA_NULL) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, player + 718, x, y);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                        DAT_GameSynchronyState::instance.currentAIArray[player] + 700, x, y);
                    ++drawn;
                    x += 40;
                    if (drawn == 4) {
                        x = firstX;
                        y += 38;
                    }
                }
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
