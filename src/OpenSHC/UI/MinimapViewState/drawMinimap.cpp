#include "../MinimapViewState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Enums/MapOrientation.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/Rendering/Enums/ViewportConstants.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MiniMapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Rendering::Enums::VC_SCREEN_POINT_LONG_ROW;
    using OpenSHC::Rendering::Enums::VC_SCREEN_POINT_SHORT_ROW;
    using OpenSHC::Rendering::Enums::VC_SCREEN_POINT_TABLE_SIZE;
    using OpenSHC::Rendering::Enums::VC_SCREEN_POINT_TABLE_START;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // A row of the minimap picture (200 pixels) in bytes, for the assembly (it cannot name a qualified constant).
    enum { PICTURE_ROW_BYTES = Map::MC_MAP_XY_LIMIT / 2 * sizeof(ushort) };

    // Draws the minimap: the terrain picture, every unit as a dot in its player's colour, and the viewport's box.
    // FUNCTION: STRONGHOLDCRUSADER 0x004B66C0
    void MinimapViewState::drawMinimap(int xPos, int yPos, int width, int height, uint flags, int xOffset, int yOffset,
        int widthFactor, int heightFactor, int intoPreview)
    {
        // in this order (in another order the first stores move; found by a search over the orders)
        BOOLEnum isRGB565 = FALSE;
        int rowBase = VC_SCREEN_POINT_TABLE_START;
        int scale = 1;
        int blitWidth = width;
        int blitHeight = height;
        ushort* const buffer = this->field_0x44;
        int sourceColumnBase = 0;
        int sourceRowBase = 0;
        BOOLEnum showBox = TRUE;
        int mapSize = DAT_TileMapState::instance.mapSize;
        if (mapSize == 0) {
            mapSize = Map::MC_MAP_SIZE_400;
        }
        int minX;
        int minY;
        int maxY;
        int maxX;
        int quarterMargin;
        int halfMargin;
        // MC_MAP_SIZE_400 - mapSize written out each time (a local for it changes the stack slots)
        if (width < 200) {
            quarterMargin = (Map::MC_MAP_SIZE_400 - mapSize) / 4;
            minX = quarterMargin + 1;
            halfMargin = (Map::MC_MAP_SIZE_400 - mapSize) / 2;
            minY = halfMargin + 2;
            maxX = (Map::MC_MAP_SIZE_400 - halfMargin) / 2 - 2;
            maxY = Map::MC_MAP_SIZE_400 - halfMargin;
        } else {
            quarterMargin = (Map::MC_MAP_SIZE_400 - mapSize) / 4;
            halfMargin = (Map::MC_MAP_SIZE_400 - mapSize) / 2;
            minX = quarterMargin;
            minY = halfMargin;
            maxX = (Map::MC_MAP_SIZE_400 - halfMargin) / 2;
            maxY = Map::MC_MAP_SIZE_400 - halfMargin;
        }
        if (DAT_MiniMapDefinedData::instance.cachedMapOrientation != DAT_TileMapState::instance.mapOrientation) {
            MACRO_CALL_MEMBER(MinimapViewState_Func::setTileColorsDependingOnMapSize, this)(0, 100);
            MACRO_CALL_MEMBER(MinimapViewState_Func::setMapPropertyDependingOnMapSize, this)(0, 100);
            DAT_MiniMapDefinedData::instance.cachedMapOrientation = DAT_TileMapState::instance.mapOrientation;
        }
        if (this->field_0x38 != 0) {
            if (this->field_0x34 == 0) {
                MACRO_CALL_MEMBER(MinimapViewState_Func::setTileColorsDependingOnMapSize, this)(this->field_0x34, 2);
                MACRO_CALL_MEMBER(MinimapViewState_Func::setMapPropertyDependingOnMapSize, this)(this->field_0x34, 2);
                MACRO_CALL_MEMBER(Map::TileMapState_Func::collectCliffEdgeTilesForClimbData, DAT_TileMapState::ptr)();
                this->field_0x34 += 2;
            } else {
                MACRO_CALL_MEMBER(MinimapViewState_Func::setTileColorsDependingOnMapSize, this)(this->field_0x34, 2);
                MACRO_CALL_MEMBER(MinimapViewState_Func::setMapPropertyDependingOnMapSize, this)(this->field_0x34, 2);
                this->field_0x34 += 2;
                // (int): the original compares signed (the header has undefined4)
                if ((int)this->field_0x34 >= 100) {
                    --this->field_0x38;
                    if ((int)this->field_0x38 > 0) {
                        this->field_0x34 = 0;
                    } else {
                        this->field_0x38 = 0;
                    }
                }
            }
        }
        if (flags & 4) {
            scale = 2;
        }
        // a small map sits in the middle of the 400 by 400 picture
        if (DAT_TileMapState::instance.mapSize <= Map::MC_MAP_SIZE_200) {
            sourceColumnBase = (Map::MC_MAP_XY_LIMIT - Map::MC_MAP_SIZE_200) / 2;
            sourceRowBase = (Map::MC_MAP_XY_LIMIT - Map::MC_MAP_SIZE_200) / 2;
        }
        this->width = width;
        this->height = height;
        this->widthFactor = widthFactor;
        this->heightFactor = heightFactor;
        this->x = xPos;
        this->y = yPos;
        this->oneOrTwo = scale;
        int const viewWidth = DAT_ViewportRenderState::instance.viewportState.viewportHeight - 5;
        int boxWidth = viewWidth * widthFactor / scale + widthFactor / scale - 1;
        int boxHeight = DAT_ViewportRenderState::instance.viewportState.viewportWidth * heightFactor / scale - 1;
        // width and height count tiles from here on, as in the original, which keeps the counts in their stack slots
        width = width / widthFactor * scale;
        height = height / heightFactor * scale;
        if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
            isRGB565 = TRUE;
        }
        int boxX = xOffset;
        int boxY = yOffset;
        int const half = mapSize / 2;
        if (half < width) {
            xOffset = quarterMargin - (width - half) / 2;
            yOffset = halfMargin - (height - mapSize) / 2;
            boxX -= viewWidth / 2;
            boxY -= DAT_ViewportRenderState::instance.viewportState.viewportWidth / 2;
            if (boxX < minX) {
                boxWidth = half * widthFactor / scale;
                boxX = minX;
                showBox = FALSE;
            }
            if (boxY < minY) {
                boxHeight = mapSize * heightFactor / scale;
                boxY = minY;
                showBox = FALSE;
            }
        } else {
            if (flags & 1) {
                xOffset -= width / 2;
                yOffset -= height / 2;
                boxX -= viewWidth / 2;
                boxY -= DAT_ViewportRenderState::instance.viewportState.viewportWidth / 2;
            }
            if (xOffset < minX) {
                xOffset = minX;
            } else if (xOffset > maxX - width) {
                xOffset = maxX - width;
            }
            if (yOffset < minY) {
                yOffset = minY;
            } else if (yOffset > maxY - height - 1) {
                yOffset = maxY - height - 1;
            }
            if (boxX < minX) {
                boxX = minX;
            } else if (boxX > maxX - DAT_ViewportRenderState::instance.viewportState.viewportHeight + 5) {
                boxX = maxX - DAT_ViewportRenderState::instance.viewportState.viewportHeight + 5;
            }
            if (boxY < minY) {
                boxY = minY;
            } else if (boxY > maxY - DAT_ViewportRenderState::instance.viewportState.viewportWidth - 1) {
                boxY = maxY - DAT_ViewportRenderState::instance.viewportState.viewportWidth - 1;
            }
        }
        boxX = (boxX - xOffset) * widthFactor / scale + xPos;
        this->tileOffsetY = yOffset;
        this->tileOffsetX = xOffset;
        boxY = (boxY - yOffset) * heightFactor / scale + yPos;
        int const halfY = yOffset / 2;
        int const viewportHeight = DAT_ViewportRenderState::instance.viewportState.viewportHeight;
        int const otherParity = viewportHeight + 1;
        int rowParity = otherParity;
        if (DAT_TileMapState::instance.mapOrientation == Map::Enums::MO_NORTH) {
            rowBase = VC_SCREEN_POINT_TABLE_START;
        } else if (DAT_TileMapState::instance.mapOrientation == Map::Enums::MO_WEST) {
            rowBase = VC_SCREEN_POINT_TABLE_START + VC_SCREEN_POINT_TABLE_SIZE;
        } else if (DAT_TileMapState::instance.mapOrientation == Map::Enums::MO_SOUTH) {
            rowBase = VC_SCREEN_POINT_TABLE_START + 2 * VC_SCREEN_POINT_TABLE_SIZE;
        } else if (DAT_TileMapState::instance.mapOrientation == Map::Enums::MO_EAST) {
            rowBase = VC_SCREEN_POINT_TABLE_START + 3 * VC_SCREEN_POINT_TABLE_SIZE;
        }
        int sourceX = xOffset * widthFactor / scale;
        int const sourceY = halfY * heightFactor;
        rowBase += halfY * (VC_SCREEN_POINT_SHORT_ROW + VC_SCREEN_POINT_LONG_ROW) + xOffset + 1;
        // the loaded map's preview, or the screen
        if (intoPreview > 0) {
            DAT_PencilRenderCore::instance.surfacePtr = (ushort*)this->loadedMiniMap;
            DAT_PencilRenderCore::instance.horizontalByteSize = sizeof(this->loadedMiniMap[0]);
            this->someMiniMapCounterTill4 = 0;
        } else {
            MACRO_CALL_MEMBER(Rendering::PencilRenderCore_Func::setupPencilSurface, DAT_PencilRenderCore::ptr)();
        }
        if (intoPreview != 0) {
            if (DAT_TileMapState::instance.mapSize == Map::MC_MAP_SIZE_160) {
                blitWidth -= 5;
                xPos += 3;
            } else if (DAT_TileMapState::instance.mapSize == Map::MC_MAP_SIZE_200) {
                xPos += 3;
                ++sourceX;
                blitWidth -= 4;
            }
        }
        // handwritten in the original: the minimap picture copied to the surface row by row
        __asm {
            mov edi, DAT_PencilRenderCore::instance.surfacePtr
            mov eax, xPos
            add eax, eax
            add edi, eax
            mov eax, yPos
            mov edx, DAT_PencilRenderCore::instance.horizontalByteSize
            mul edx
            add edi, eax
            mov esi, buffer
            mov eax, sourceX
            sub eax, sourceColumnBase
            add eax, eax
            add esi, eax
            mov eax, sourceY
            sub eax, sourceRowBase
            mov edx, PICTURE_ROW_BYTES
            mul edx
            add esi, eax
            mov edx, blitHeight
        next_row:
            mov ecx, blitWidth
            mov ebx, 0
        next_pixel:
            mov ax, word ptr [esi + ebx]
            mov word ptr [edi + ebx], ax
            add ebx, 2
            dec ecx
            jne next_pixel
            add esi, PICTURE_ROW_BYTES
            add edi, DAT_PencilRenderCore::instance.horizontalByteSize
            dec edx
            jne next_row
        }
        // 160 keeps its shift and 200 keeps one of its three pixels (the original tests 160 first)
        if (intoPreview != 0)
        {
            if (DAT_TileMapState::instance.mapSize == Map::MC_MAP_SIZE_160) {
            } else if (DAT_TileMapState::instance.mapSize == Map::MC_MAP_SIZE_200) {
                xPos -= 2;
            }
        }
        // per player four animation frames in the two colour modes
        typedef ushort PlayerUnitColors[4][2];
        PlayerUnitColors const* const playerColors
            = (PlayerUnitColors const*)DAT_MiniMapDefinedData::instance.PlayerColorColors;
        uint color;
        // declared once for both unit loops (declared in each loop they take other stack slots)
        int row;
        int column;
        int rowLength;
        int start;
        int pixelX;
        int pixelY;
        int unit;
        int baseX;
        int baseY;
        int offsetX;
        int offsetY;
        int x;
        int y;
        int px;
        if (!DAT_GameCore::instance.altRToggleMinimapHideWildlife) {
            for (row = 0; row < height; ++row, rowBase += rowLength) {
                pixelY = row * heightFactor;
                if (rowParity == otherParity) {
                    rowParity = viewportHeight;
                    start = widthFactor / 2;
                    rowLength = VC_SCREEN_POINT_SHORT_ROW;
                } else {
                    rowParity = otherParity;
                    start = 0;
                    rowLength = VC_SCREEN_POINT_LONG_ROW;
                }
                if (scale != 2 || !(pixelY & 1)) {
                    for (column = -2; column < width; ++column) {
                        pixelX = column * widthFactor + start;
                        unit = DAT_TileMapState::instance.UnitLayer[DAT_ViewportRenderState::instance
                                .screenPointToTileNumber[rowBase + column]];
                        if (unit == 0) {
                            if (scale != 2) {
                                continue;
                            }
                            unit = DAT_TileMapState::instance.UnitLayer[DAT_ViewportRenderState::instance
                                    .screenPointToTileNumber[column + rowLength + rowBase]];
                            if (unit == 0) {
                                continue;
                            }
                        }
                        short const owner = DAT_UnitsState::instance.units[unit].owner;
                        if (owner == 0) {
                            color = playerColors[0][2][isRGB565];
                        } else {
                            int colorPlayer;
                            if (DAT_UnitsState::instance.units[unit].isSelectable_OR_matchTime != 0) {
                                switch (DAT_UnitsState::instance.units[unit].unitType) {
                                case Map::Units::UT_E_KNIGHT:
                                case Map::Units::UT_A_HARCHER:
                                    colorPlayer = DAT_UnitsState::instance.units[unit].displayColorPlayerID;
                                    break;
                                case Map::Units::UT_S_TOWER:
                                    colorPlayer = owner;
                                    break;
                                default:
                                    colorPlayer = DAT_UnitsState::instance.units[unit].calculatedOwnerPlayerIndex;
                                    break;
                                }
                            } else {
                                colorPlayer = owner;
                            }
                            if (colorPlayer <= 0) {
                                colorPlayer = 1;
                            }
                            switch (DAT_UnitsState::instance.units[unit].unitType) {
                            case Map::Units::UT_A_ASSASSIN:
                                color = playerColors[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[colorPlayer]]
                                                    [0][isRGB565];
                                if (DAT_GameState::instance.mapAndTime.playerTeams[owner]
                                        != DAT_GameState::instance.mapAndTime
                                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    && DAT_UnitsState::instance.units[unit].assassinsMicroDistanceToEnemyUnk > 160
                                    && DAT_UnitsState::instance.units[unit].state.generic
                                        != Map::Units::States::US_MELEE_ATTACK
                                    && DAT_UnitsState::instance.units[unit].state.generic
                                        != Map::Units::States::US_MELEE_ATTACK_WALL
                                    && (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                                        || DAT_UnitsState::instance.units[unit].idleCounterUnk <= 2400)) {
                                    continue;
                                }
                                break;
                            case Map::Units::UT_COW:
                            case Map::Units::UT_HUNTERDOG:
                            case Map::Units::UT_CHICKEN:
                                color = playerColors[0][2][isRGB565];
                                break;
                            case Map::Units::UT_S_CATAPULT:
                            case Map::Units::UT_S_TREBUCHET:
                            case Map::Units::UT_S_MANGONEL:
                            case Map::Units::UT_S_TOWER:
                            case Map::Units::UT_S_BATTERINGRAM:
                            case Map::Units::UT_S_SHIELD:
                            case Map::Units::UT_S_BALLISTA:
                            case Map::Units::UT_S_FBALLISTA:
                                color = playerColors[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[colorPlayer]]
                                                    [this->someMiniMapCounterTill4][isRGB565];
                                break;
                            default:
                                color = playerColors[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[colorPlayer]]
                                                    [0][isRGB565];
                                break;
                            }
                        }
                        if (scale == 1) {
                            baseX = pixelX + xPos;
                            baseY = pixelY + yPos;
                            for (offsetX = 0; offsetX < widthFactor; ++offsetX) {
                                if (baseX + offsetX >= xPos && baseX + offsetX < width * widthFactor + xPos) {
                                    for (offsetY = 0; offsetY < heightFactor; ++offsetY) {
                                        // handwritten in the original: one pixel
                                        __asm {
                                            mov edi, DAT_PencilRenderCore::instance.surfacePtr
                                            mov eax, baseX
                                            add eax, offsetX
                                            add eax, eax
                                            add edi, eax
                                            mov eax, baseY
                                            add eax, offsetY
                                            mov edx, DAT_PencilRenderCore::instance.horizontalByteSize
                                            mul edx
                                            add edi, eax
                                            mov ax, word ptr color
                                            mov word ptr [edi], ax
                                        }
                                    }
                                }
                            }
                        } else {
                            // Every other pixel at half the position (a plain loop skipping odd ones loses the match).
                            for (offsetX = pixelX & 1; offsetX < widthFactor; offsetX += 2) {
                                px = pixelX + offsetX;
                                if (px >= 0 && px < width * widthFactor) {
                                    x = px / scale + xPos;
                                    for (offsetY = 0; offsetY < heightFactor; ++offsetY) {
                                        y = (pixelY + offsetY) / scale + yPos;
                                        // handwritten in the original: one pixel
                                        __asm {
                                            mov edi, DAT_PencilRenderCore::instance.surfacePtr
                                            mov eax, x
                                            add eax, eax
                                            add edi, eax
                                            mov eax, y
                                            mov edx, DAT_PencilRenderCore::instance.horizontalByteSize
                                            mul edx
                                            add edi, eax
                                            mov ax, word ptr color
                                            mov word ptr [edi], ax
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            // with the wildlife hidden: own team and enemies in two colours
            uint const ownColor = playerColors[DAT_BlendingDefinedData::instance
                    .PlayerSlotUnitColor[DAT_GameSynchronyState::instance.currentPlayerSlotID]][0][isRGB565];
            uint enemyColor = 0;
            for (int player = 1; player < countof(DAT_GameState::instance.mapAndTime.playerTeams); ++player) {
                if (DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    != DAT_GameState::instance.mapAndTime.playerTeams[player]) {
                    enemyColor
                        = playerColors[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[player]][0][isRGB565];
                    break;
                }
            }
            for (row = 0; row < height; ++row, rowBase += rowLength) {
                pixelY = row * heightFactor;
                if (rowParity == otherParity) {
                    rowParity = viewportHeight;
                    start = widthFactor / 2;
                    rowLength = VC_SCREEN_POINT_SHORT_ROW;
                } else {
                    rowParity = otherParity;
                    start = 0;
                    rowLength = VC_SCREEN_POINT_LONG_ROW;
                }
                if (scale != 2 || !(pixelY & 1)) {
                    for (column = -2; column < width; ++column) {
                        pixelX = column * widthFactor + start;
                        unit = DAT_TileMapState::instance.UnitLayer[DAT_ViewportRenderState::instance
                                .screenPointToTileNumber[rowBase + column]];
                        if (unit == 0) {
                            if (scale != 2) {
                                continue;
                            }
                            unit = DAT_TileMapState::instance.UnitLayer[DAT_ViewportRenderState::instance
                                    .screenPointToTileNumber[column + rowLength + rowBase]];
                            if (unit == 0) {
                                continue;
                            }
                        }
                        short const owner = DAT_UnitsState::instance.units[unit].owner;
                        if (owner == 0) {
                            continue;
                        }
                        switch (DAT_UnitsState::instance.units[unit].unitType) {
                        case Map::Units::UT_COW:
                        case Map::Units::UT_HUNTERDOG:
                        case Map::Units::UT_CHICKEN:
                            continue;
                        case Map::Units::UT_A_ASSASSIN:
                            if (DAT_GameState::instance.mapAndTime.playerTeams[owner]
                                    != DAT_GameState::instance.mapAndTime
                                        .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                && DAT_UnitsState::instance.units[unit].assassinsMicroDistanceToEnemyUnk > 160
                                && DAT_UnitsState::instance.units[unit].state.generic
                                    != Map::Units::States::US_MELEE_ATTACK
                                && DAT_UnitsState::instance.units[unit].state.generic
                                    != Map::Units::States::US_MELEE_ATTACK_WALL
                                && (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                                    || DAT_UnitsState::instance.units[unit].idleCounterUnk <= 2400)) {
                                continue;
                            }
                            break;
                        default:
                            break;
                        }
                        if (DAT_GameState::instance.mapAndTime
                                .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            == DAT_GameState::instance.mapAndTime.playerTeams[owner]) {
                            color = (ushort)ownColor;
                        } else {
                            color = (ushort)enemyColor;
                        }
                        if (scale == 1) {
                            baseX = pixelX + xPos;
                            baseY = pixelY + yPos;
                            for (offsetX = 0; offsetX < widthFactor; ++offsetX) {
                                if (baseX + offsetX >= xPos && baseX + offsetX < width * widthFactor + xPos) {
                                    for (offsetY = 0; offsetY < heightFactor; ++offsetY) {
                                        // handwritten in the original: one pixel
                                        __asm {
                                            mov edi, DAT_PencilRenderCore::instance.surfacePtr
                                            mov eax, baseX
                                            add eax, offsetX
                                            add eax, eax
                                            add edi, eax
                                            mov eax, baseY
                                            add eax, offsetY
                                            mov edx, DAT_PencilRenderCore::instance.horizontalByteSize
                                            mul edx
                                            add edi, eax
                                            mov ax, word ptr color
                                            mov word ptr [edi], ax
                                        }
                                    }
                                }
                            }
                        } else {
                            // Every other pixel at half the position (a plain loop skipping odd ones loses the match).
                            for (offsetX = pixelX & 1; offsetX < widthFactor; offsetX += 2) {
                                px = pixelX + offsetX;
                                if (px >= 0 && px < width * widthFactor) {
                                    x = px / scale + xPos;
                                    for (offsetY = 0; offsetY < heightFactor; ++offsetY) {
                                        y = (pixelY + offsetY) / scale + yPos;
                                        // handwritten in the original: one pixel
                                        __asm {
                                            mov edi, DAT_PencilRenderCore::instance.surfacePtr
                                            mov eax, x
                                            add eax, eax
                                            add edi, eax
                                            mov eax, y
                                            mov edx, DAT_PencilRenderCore::instance.horizontalByteSize
                                            mul edx
                                            add edi, eax
                                            mov ax, word ptr color
                                            mov word ptr [edi], ax
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if ((flags & 2) && showBox) {
            if (boxX < xPos) {
                if (boxX + boxWidth >= blitWidth + xPos) {
                    return;
                }
                boxWidth += boxX - xPos;
                boxX = xPos;
            } else if (boxX + boxWidth >= blitWidth + xPos) {
                boxWidth = blitWidth - boxX + xPos - 1;
            }
            if (boxY < yPos) {
                if (boxY + boxHeight >= blitHeight + yPos) {
                    return;
                }
                boxHeight += boxY - yPos;
                boxY = yPos;
            } else if (boxY + boxHeight >= yPos + blitHeight) {
                boxHeight = blitHeight - boxY + yPos;
            }
            MACRO_CALL_MEMBER(Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                boxX, boxY, boxX + boxWidth, boxY + boxHeight, -1);
        }
    }

}
}
