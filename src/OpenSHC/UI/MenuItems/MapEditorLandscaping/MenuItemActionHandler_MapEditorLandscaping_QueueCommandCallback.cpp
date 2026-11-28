#include "../MapEditorLandscaping.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Enums/LoweredViewTransition.hpp"
#include "OpenSHC/Map/Enums/MapOrientation.hpp"
#include "OpenSHC/Map/Enums/MapOrientationInt.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_ModifierKeyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00b9844c.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00443A30
        void MapEditorLandscaping::MenuItemActionHandler_MapEditorLandscaping_QueueCommandCallback()
        {
            // the mouse's event: 1, 3, 4 and 5 are handled here and set the flag that a right click's end then clears
            if (DAT_MouseState::instance.mouseBasedEvent == 1) {
                MACRO_CALL_MEMBER(Map::TileMapState_Func::triggerLoweredView, DAT_TileMapState::ptr)(
                    Map::Enums::LVT_LOWER);
                INT_00b9844c::instance = 1;
            } else if ((!DAT_MouseState::instance.rightClickState || DAT_MouseState::instance.mouseBasedEvent == 2)
                && (DAT_ModifierKeyState::instance.ctrl == 0 || DAT_ModifierKeyState::instance.downArrow == 0)
                && DAT_ModifierKeyState::instance.v == 0) {
                MACRO_CALL_MEMBER(Map::TileMapState_Func::triggerLoweredView, DAT_TileMapState::ptr)(
                    Map::Enums::LVT_RAISE);
            } else if (DAT_MouseState::instance.mouseBasedEvent == 3) {
                MACRO_CALL_MEMBER(Map::TileMapState_Func::setMapRotation, DAT_TileMapState::ptr)(
                    DAT_MouseState::instance.mapOrientationCopy3);
                INT_00b9844c::instance = 1;
            } else if (DAT_MouseState::instance.mouseBasedEvent == 4) {
                DAT_MouseState::instance.field_0x198 = 2;
                // a call in each arm (as one call with `zoomed ? 0 : 1` the match is lost)
                if (DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Rendering::ViewportRenderState_Func::resetupViewport, DAT_ViewportRenderState::ptr)(0);
                } else {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Rendering::ViewportRenderState_Func::resetupViewport, DAT_ViewportRenderState::ptr)(1);
                }
                DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                INT_00b9844c::instance = 1;
            } else if (DAT_MouseState::instance.mouseBasedEvent == 5) {
                DAT_MouseState::instance.field_0x19c = 2;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::toggleFlatView, DAT_TileMapState::ptr)(
                    DAT_TileMapState::instance.flatViewToggleValue1 ^ 1);
                INT_00b9844c::instance = 1;
            }
            // a call in each arm, as above
            if (DAT_UnitsState::instance.unitCount >= 2300) {
                MACRO_CALL(DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    Enums::DEID_PEOPLE_LEFT_TO_PLACE, 1);
            } else {
                MACRO_CALL(DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    Enums::DEID_PEOPLE_LEFT_TO_PLACE, 0);
            }
            if (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_RIPPLE) {
                MACRO_CALL(Helpers_Func::HandleWallTerrainMouseDrag)();
                return;
            }
            if (DAT_ViewportRenderState::instance.viewportState.field_0x0 == 0) {
                MACRO_CALL_MEMBER(Input::MouseState_Func::storeXYAndResetMouseState, DAT_MouseState::ptr)();
                return;
            }
            // a right click ends: the mapper command goes, unless the click was one of the events handled above
            if (DAT_MouseState::instance.rightClickStop) {
                if (INT_00b9844c::instance == 0) {
                    DAT_TileMapState::instance.currentMapperCommand = Commands::M_MAPPER_NULL;
                    return;
                }
                INT_00b9844c::instance = 0;
            }
            // no left button: only the preview under the mouse
            if (!DAT_MouseState::instance.leftClickState) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::ViewportRenderState_Func::setupMouseTileXY, DAT_ViewportRenderState::ptr)();
                MACRO_CALL_MEMBER(Map::TileMapState_Func::noop1, DAT_TileMapState::ptr)(
                    DAT_ViewportRenderState::instance.viewportState.mouseFlatTile);
                if (DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_BIGROCK1
                    && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_BIGROCK2
                    && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_BIGROCK3
                    && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_BIGROCK4
                    && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_BIGROCK5) {
                    if (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_NULL) {
                        return;
                    }
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::renderPreviewMapperWithBrush, DAT_TileMapState::ptr)(
                        DAT_ViewportRenderState::instance.viewportState.mouseTileX,
                        DAT_ViewportRenderState::instance.viewportState.mouseTileY,
                        DAT_TileMapState::instance.currentMapperCommand);
                    return;
                }
                MACRO_CALL_MEMBER(Map::TileMapState_Func::renderWallPlacementPreview, DAT_TileMapState::ptr)(
                    DAT_ViewportRenderState::instance.viewportState.mouseTileX,
                    DAT_ViewportRenderState::instance.viewportState.mouseTileY,
                    DAT_TileMapState::instance.rockFlagStartNumber
                        + DAT_TileMapState::instance.unknownBrushRelated * 4);
                return;
            }
            // the left button is down: go on when the click starts or the mouse has reached another tile
            if (!DAT_MouseState::instance.leftClickStart
                && DAT_ViewportRenderState::instance.viewportState.previousMouseTile
                    == DAT_ViewportRenderState::instance.viewportState.mouseFlatTile) {
                return;
            }
            DAT_ViewportRenderState::instance.viewportState.previousMouseTile
                = DAT_ViewportRenderState::instance.viewportState.mouseFlatTile;
            MACRO_CALL_MEMBER(
                OpenSHC::Rendering::ViewportRenderState_Func::setupMouseTileXY, DAT_ViewportRenderState::ptr)();
            // read in this order (another order loses the match); x and y below are the snapped tile
            int const snap = DAT_TileMapState::instance.editorSnapToMode;
            // read in each arm of the click test (read in front of it, the match drops)
            Map::Enums::MapOrientationInt orientation;
            int const tileY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
            int const tileX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
            // the click starts: its tile is kept, and whether it is on sea or on the unnamed 0x40 kind
            if (DAT_MouseState::instance.leftClickStart) {
                orientation = DAT_TileMapState::instance.mapOrientation;
                DAT_TileMapState::instance.DAT_ClickedTileX = tileX;
                DAT_TileMapState::instance.DAT_ClickedTileY = tileY;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(tileX, tileY)) {
                    DAT_TileMapState::instance.editorAffectType = 0;
                    if (DAT_TileMapState::instance
                            .LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + tileX]
                        & (Map::LogicHelpers::L_SEA | Map::LogicHelpers::L_UNNAMED_0x40)) {
                        DAT_TileMapState::instance.editorAffectType = 1;
                    }
                }
            } else {
                orientation = DAT_TileMapState::instance.mapOrientation;
            }
            // copies: with one pair of variables every case below is merged into the last one
            int x = tileX;
            int y = tileY;
            // snapping keeps the clicked tile's y or x; the two modes change places with the map's orientation
            if (orientation != Map::Enums::MO_NORTH && orientation != Map::Enums::MO_SOUTH) {
                if (snap == 2) {
                    y = DAT_TileMapState::instance.DAT_ClickedTileY;
                } else if (snap == 1) {
                    x = DAT_TileMapState::instance.DAT_ClickedTileX;
                }
            } else {
                if (snap == 1) {
                    y = DAT_TileMapState::instance.DAT_ClickedTileY;
                } else if (snap == 2) {
                    x = DAT_TileMapState::instance.DAT_ClickedTileX;
                }
            }
            // the field, not a local (a local loses the match)
            switch (DAT_TileMapState::instance.currentMapperCommand) {
            // every case in full; the compiler shares the tails by itself
            case Commands::M_MAPPER_DELETE:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_UNIT_ERASE);
                return;
            case Commands::M_MAPPER_RAISE:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 1;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_RAISE_LAND);
                return;
            case Commands::M_MAPPER_MOUNTAIN:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = 5;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_RAISE_LAND2Unk);
                return;
            case Commands::M_MAPPER_HILL:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = 3;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_RAISE_LAND2Unk);
                return;
            case Commands::M_MAPPER_LOWER:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = -1;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_RAISE_LAND);
                return;
            case Commands::M_MAPPER_LAND:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_LAND);
                return;
            case Commands::M_MAPPER_SEA:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_SEA;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = Map::LogicHelpers::L2_NONE;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            case Commands::M_MAPPER_BEACH:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_NONE;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = Map::LogicHelpers::L2_BEACH;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            case Commands::M_MAPPER_EQUALISE:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 1;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_TERRAIN_EQUALIZE);
                return;
            case Commands::M_MAPPER_PLAIN1:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L2_PLATEAU_MEDIUM;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_CREATE_PLATEAU);
                return;
            case Commands::M_MAPPER_PLAIN2:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L2_PLATEAU_HIGH;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_CREATE_PLATEAU);
                return;
            case Commands::M_MAPPER_MIN:
            case Commands::M_MAPPER_MAX:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = DAT_TileMapState::instance.mapperMax;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_TERRAIN_MIN_MAX);
                return;
            // rockFlagStartNumber counts on with every rock placed and starts again after 3
            case Commands::M_MAPPER_BIGROCK1:
            case Commands::M_MAPPER_BIGROCK2:
            case Commands::M_MAPPER_BIGROCK3:
            case Commands::M_MAPPER_BIGROCK4:
            case Commands::M_MAPPER_BIGROCK5:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = Commands::M_MAPPER_BIGROCKS;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = DAT_TileMapState::instance.rockFlagStartNumber
                    + DAT_TileMapState::instance.unknownBrushRelated * 4;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_PLACE_TREE_OR_ROCKUnk);
                ++DAT_TileMapState::instance.rockFlagStartNumber;
                if ((int)DAT_TileMapState::instance.rockFlagStartNumber >= 4) {
                    DAT_TileMapState::instance.rockFlagStartNumber = 0;
                }
                return;
            case Commands::M_MAPPER_ROCKY:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_ROCKY;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = Map::LogicHelpers::L2_NONE;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            case Commands::M_MAPPER_STONES:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_NONE;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = Map::LogicHelpers::L2_STONES_OR_DRIVEN_SANDUnk;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            // param 4 is the river's kind: 0 river, 16 foam, 32 ripple; a ripple takes the brush size 1
            case Commands::M_MAPPER_RIVER:
            case Commands::M_MAPPER_FOAM:
            case Commands::M_MAPPER_RIPPLE:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_RIVER;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0;
                if (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_FOAM) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 16;
                }
                if (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_RIPPLE) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 32;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = 1;
                }
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            case Commands::M_MAPPER_FORD:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_FORD;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = Map::LogicHelpers::L2_NONE;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            case Commands::M_MAPPER_BOULDERS:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_BOULDERS;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = Map::LogicHelpers::L2_NONE;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            case Commands::M_MAPPER_PEBBLES:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_PEBBLES;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = Map::LogicHelpers::L2_NONE;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            case Commands::M_MAPPER_IRON:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_IRON;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = Map::LogicHelpers::L2_NONE;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            case Commands::M_MAPPER_OIL:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_OIL;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = Map::LogicHelpers::L2_NONE;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            case Commands::M_MAPPER_MARSH:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_MARSH;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = Map::LogicHelpers::L2_NONE;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            case Commands::M_MAPPER_DUGMOAT:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_MOAT;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = Map::LogicHelpers::L2_EARTH_AND_STONES;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            case Commands::M_MAPPER_UNDUGMOAT:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_MOAT;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = Map::LogicHelpers::L2_MOAT_UNDUG;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            case Commands::M_MAPPER_DIRT:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_NONE;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = Map::LogicHelpers::L2_EARTH_AND_STONES;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            case Commands::M_MAPPER_GRASS:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_NONE;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = Map::LogicHelpers::L2_OASIS_GRASS;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            case Commands::M_MAPPER_SCRUB:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_NONE;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = Map::LogicHelpers::L2_SCRUB;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            // a tree's, a shrub's and an animal's kind is its mapper value
            case Commands::M_MAPPER_CHESTNUT:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = Commands::M_MAPPER_CHESTNUT;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_PLACE_TREE_OR_ROCKUnk);
                return;
            case Commands::M_MAPPER_OAK:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = Commands::M_MAPPER_OAK;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_PLACE_TREE_OR_ROCKUnk);
                return;
            case Commands::M_MAPPER_SHRUB1A:
            case Commands::M_MAPPER_SHRUB1B:
            case Commands::M_MAPPER_SHRUB1C:
            case Commands::M_MAPPER_SHRUB1D:
            case Commands::M_MAPPER_SHRUB1E:
            case Commands::M_MAPPER_SHRUB2A:
            case Commands::M_MAPPER_SHRUB2B:
            case Commands::M_MAPPER_SHRUB2C:
            case Commands::M_MAPPER_SHRUB2D:
            case Commands::M_MAPPER_SHRUB2E:
            case Commands::M_MAPPER_SHRUB3A:
            case Commands::M_MAPPER_SHRUB3B:
            case Commands::M_MAPPER_SHRUB3C:
            case Commands::M_MAPPER_SHRUB3D:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                    = DAT_TileMapState::instance.currentMapperCommand;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_PLACE_TREE_OR_ROCKUnk);
                return;
            case Commands::M_MAPPER_PINE:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = Commands::M_MAPPER_PINE;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_PLACE_TREE_OR_ROCKUnk);
                return;
            case Commands::M_MAPPER_BIRCH:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = Commands::M_MAPPER_BIRCH;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_PLACE_TREE_OR_ROCKUnk);
                return;
            case Commands::M_MAPPER_DEER:
            case Commands::M_MAPPER_LION:
            case Commands::M_MAPPER_RABBIT:
            case Commands::M_MAPPER_CAMEL:
            case Commands::M_MAPPER_CROW_SEAGULL:
            case Commands::M_MAPPER_SEAGULL:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                    = DAT_TileMapState::instance.currentMapperCommand;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_CREATE_ANIMAL);
                return;
            case Commands::M_MAPPER_DUNES:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_NONE;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = Map::LogicHelpers::L2_STONES_OR_DRIVEN_SANDUnk;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            // stored as -128: the thick scrub's 128 as a signed char
            case Commands::M_MAPPER_SCRUBGRASS:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = x;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = y;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_NONE;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = (char)Map::LogicHelpers::L2_THICK_SCRUB;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SET_TERRAIN);
                return;
            }
        }

    }
}
}
