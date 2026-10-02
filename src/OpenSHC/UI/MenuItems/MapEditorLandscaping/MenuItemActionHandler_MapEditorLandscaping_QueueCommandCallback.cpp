#include "../MapEditorLandscaping.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Commands/MappersEnumInt.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::Commands::MappersEnumInt;
        using OpenSHC::UI::Enums::DisplayElementID;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00443A30
        void MapEditorLandscaping::MenuItemActionHandler_MapEditorLandscaping_QueueCommandCallback()
        {
            int iVar1;
            int iVar2;
            BOOLEnum BVar3;
            int _clickedX;
            bool bVar4;
            GameCommandType commandType;
            MappersEnumInt unionfacet4_443ced;
            int _orientation;
            int _clickedY;
            MappersEnumInt unionfacet2_443cc0;
            if (DAT_MouseState::instance.mouseBasedEvent == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::triggerLoweredView, DAT_TileMapState::ptr)(3);
            LAB_00443aed:
                INT_00b9844c::instance = 1;
            } else {
                if ((((DAT_MouseState::instance.rightClickState != FALSE)
                         && (DAT_MouseState::instance.mouseBasedEvent != 2))
                        || ((DAT_ModifierKeyState::instance.ctrl != 0
                            && (DAT_ModifierKeyState::instance.downArrow != 0))))
                    || (DAT_ModifierKeyState::instance.v != 0)) {
                    if (DAT_MouseState::instance.mouseBasedEvent == 3) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMapRotation, DAT_TileMapState::ptr)(
                            DAT_MouseState::instance.mapOrientationCopy3);
                    } else if (DAT_MouseState::instance.mouseBasedEvent == 4) {
                        DAT_MouseState::instance.field51_0x198 = 2;
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::resetupViewport,
                            DAT_ViewportRenderState::ptr)(
                            (uint)(DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk == 0));
                        DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
                        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                    } else {
                        if (DAT_MouseState::instance.mouseBasedEvent != 5)
                            goto LAB_00443af3;
                        DAT_MouseState::instance.field52_0x19c = 2;
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::toggleFlatView, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance.flatViewToggleValue1 ^ 1);
                    }
                    goto LAB_00443aed;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::triggerLoweredView, DAT_TileMapState::ptr)(4);
            }
        LAB_00443af3:
            MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                OpenSHC::UI::Enums::DEID_PEOPLE_LEFT_TO_PLACE,
                (dword)((int)((uint)(2300 < (int)DAT_UnitsState::instance.unitCount))));
            if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_RIPPLE) {
                MACRO_CALL(OpenSHC::UI::Helpers_Func::HandleWallTerrainMouseDrag)();
            }
            if (DAT_ViewportRenderState::instance.viewportState.field0_0x0 == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::storeXYAndResetMouseState, DAT_MouseState::ptr)();
            }
            if (DAT_MouseState::instance.rightClickStop != 0) {
                if (INT_00b9844c::instance == 0) {
                    DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                }
                INT_00b9844c::instance = 0;
            }
            if (DAT_MouseState::instance.leftClickState == FALSE) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::ViewportRenderState_Func::setupMouseTileXY, DAT_ViewportRenderState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::noop1, DAT_TileMapState::ptr)(
                    DAT_ViewportRenderState::instance.viewportState.mouseTile);
                if ((((DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_BIGROCK1)
                         && (DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_BIGROCK2))
                        && (DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_BIGROCK3))
                    && ((DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_BIGROCK4
                        && (DAT_TileMapState::instance.currentMapperCommand
                            != OpenSHC::Commands::M_MAPPER_BIGROCK5)))) {
                    if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_NULL) {}
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::renderPreviewMapperWithBrush,
                        DAT_TileMapState::ptr)(DAT_ViewportRenderState::instance.viewportState.mouseTileX,
                        (uint)((int)(DAT_ViewportRenderState::instance.viewportState.mouseTileY)),
                        DAT_TileMapState::instance.currentMapperCommand);
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::renderWallPlacementPreview, DAT_TileMapState::ptr)(
                    DAT_ViewportRenderState::instance.viewportState.mouseTileX,
                    (uint)((int)(DAT_ViewportRenderState::instance.viewportState.mouseTileY)),
                    (short)((int)(DAT_TileMapState::instance.rockFlagStartNumber
                        + DAT_TileMapState::instance.unknownBrushRelated * 4)));
            }
            if ((DAT_MouseState::instance.leftClickStart == 0)
                && (DAT_ViewportRenderState::instance.viewportState.field4_0x10
                    == DAT_ViewportRenderState::instance.viewportState.mouseTile)) {}
            DAT_ViewportRenderState::instance.viewportState.field4_0x10
                = DAT_ViewportRenderState::instance.viewportState.mouseTile;
            MACRO_CALL_MEMBER(
                OpenSHC::Rendering::ViewportRenderState_Func::setupMouseTileXY, DAT_ViewportRenderState::ptr)();
            iVar2 = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
            _clickedX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
            iVar1 = DAT_TileMapState::instance.unknownZero_0x5548fc;
            _orientation = DAT_TileMapState::instance.mapOrientation;
            if (DAT_MouseState::instance.leftClickStart != 0) {
                DAT_TileMapState::instance.DAT_ClickedTileX
                    = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                DAT_TileMapState::instance.DAT_ClickedTileY
                    = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
                BVar3 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                    DAT_ViewportRenderState::ptr)(DAT_ViewportRenderState::instance.viewportState.mouseTileX,
                    (uint)((int)(DAT_ViewportRenderState::instance.viewportState.mouseTileY)));
                if ((BVar3 != FALSE)
                    && (DAT_TileMapState::instance.unknownZero_0x554904 = 0,
                        (DAT_TileMapState::instance
                                .LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[iVar2].addXgetTile
                                    + _clickedX]
                            & 0x41)
                            != 0)) {
                    DAT_TileMapState::instance.unknownZero_0x554904 = 1;
                }
            }
            _clickedY = DAT_TileMapState::instance.DAT_ClickedTileY;
            if ((_orientation == 0) || (_orientation == 4)) {
                if (iVar1 != 1) {
                    bVar4 = iVar1 == 2;
                    goto LAB_00443cb1;
                }
            } else if (iVar1 != 2) {
                bVar4 = iVar1 == 1;
            LAB_00443cb1:
                _clickedY = iVar2;
                if (bVar4) {
                    _clickedX = DAT_TileMapState::instance.DAT_ClickedTileX;
                }
            }
            if (0x154 < (int)DAT_TileMapState::instance.currentMapperCommand) {
                if (DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_SCRUBGRASS) {}
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0xffffff80;
                goto LAB_00444270;
            }
            if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_DUNES) {
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0x40;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SET_TERRAIN);
            }
            switch (DAT_TileMapState::instance.currentMapperCommand) {
            case OpenSHC::Commands::M_MAPPER_RAISE:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 1;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_RAISE_LAND);
                return;
            case OpenSHC::Commands::M_MAPPER_LOWER:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0xffffffff;
                commandType = OpenSHC::Commands::GCT_RAISE_LAND;
                goto LAB_0044427c;
            case OpenSHC::Commands::M_MAPPER_SEA:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 1;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SET_TERRAIN);
                return;
            case OpenSHC::Commands::M_MAPPER_LAND:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SET_LAND);
                return;
            default:
                break;
            case OpenSHC::Commands::M_MAPPER_SCRUB:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 1;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SET_TERRAIN);
                return;
            case OpenSHC::Commands::M_MAPPER_BEACH:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0x20;
                goto LAB_00444270;
            case OpenSHC::Commands::M_MAPPER_ROCKY:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0x80;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0;
                goto LAB_0044427a;
            case OpenSHC::Commands::M_MAPPER_STONES:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0x40;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SET_TERRAIN);
                return;
            case OpenSHC::Commands::M_MAPPER_BOULDERS:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 131072;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SET_TERRAIN);
                return;
            case OpenSHC::Commands::M_MAPPER_PEBBLES:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0x40000;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SET_TERRAIN);
                return;
            case OpenSHC::Commands::M_MAPPER_RIVER:
            case OpenSHC::Commands::M_MAPPER_FOAM:
            case OpenSHC::Commands::M_MAPPER_RIPPLE:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0x100000;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0;
                if (DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_FOAM) {
                    if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_RIPPLE) {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0x20;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = OpenSHC::Commands::M_MAPPER_AREA;
                    }
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SET_TERRAIN);
                }
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0x10;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SET_TERRAIN);
                return;
            case OpenSHC::Commands::M_MAPPER_FORD:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0x200000;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0;
                goto LAB_0044427a;
            case OpenSHC::Commands::M_MAPPER_IRON:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0x80000;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0;
                goto LAB_0044427a;
            case OpenSHC::Commands::M_MAPPER_MARSH:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0x20000000;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SET_TERRAIN);
                return;
            case OpenSHC::Commands::M_MAPPER_DIRT:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 2;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SET_TERRAIN);
                return;
            case OpenSHC::Commands::M_MAPPER_GRASS:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0x10;
            LAB_00444270:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0;
                goto LAB_0044427a;
            case OpenSHC::Commands::M_MAPPER_MIN:
            case OpenSHC::Commands::M_MAPPER_MAX:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = DAT_TileMapState::instance.mapperMax;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_TERRAIN_MIN_MAX);
                return;
            case OpenSHC::Commands::M_MAPPER_EQUALISE:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 1;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_TERRAIN_EQUALIZE);
                return;
            case OpenSHC::Commands::M_MAPPER_MOUNTAIN:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = OpenSHC::Commands::M_MAPPER_LAND;
                commandType = OpenSHC::Commands::GCT_RAISE_LAND2Unk;
                break;
            case OpenSHC::Commands::M_MAPPER_HILL:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = OpenSHC::Commands::M_MAPPER_LOWER;
                commandType = OpenSHC::Commands::GCT_RAISE_LAND2Unk;
                break;
            case OpenSHC::Commands::M_MAPPER_DELETE:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_UNIT_ERASE);
                return;
            case OpenSHC::Commands::M_MAPPER_CHESTNUT:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = OpenSHC::Commands::M_MAPPER_CHESTNUT;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0;
                commandType = OpenSHC::Commands::GCT_PLACE_TREE_OR_ROCKUnk;
                break;
            case OpenSHC::Commands::M_MAPPER_OAK:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = OpenSHC::Commands::M_MAPPER_OAK;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0;
                commandType = OpenSHC::Commands::GCT_PLACE_TREE_OR_ROCKUnk;
                break;
            case OpenSHC::Commands::M_MAPPER_PINE:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = OpenSHC::Commands::M_MAPPER_PINE;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0;
                commandType = OpenSHC::Commands::GCT_PLACE_TREE_OR_ROCKUnk;
                break;
            case OpenSHC::Commands::M_MAPPER_BIRCH:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = OpenSHC::Commands::M_MAPPER_BIRCH;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0;
                commandType = OpenSHC::Commands::GCT_PLACE_TREE_OR_ROCKUnk;
                break;
            case OpenSHC::Commands::M_MAPPER_UNDUGMOAT:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0x40000000;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 3;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SET_TERRAIN);
                return;
            case OpenSHC::Commands::M_MAPPER_DUGMOAT:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0x40000000;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 2;
            LAB_0044427a:
                commandType = OpenSHC::Commands::GCT_SET_TERRAIN;
            LAB_0044427c:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                break;
            case OpenSHC::Commands::M_MAPPER_PLAIN1:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 4;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_CREATE_PLATEAU);
                return;
            case OpenSHC::Commands::M_MAPPER_PLAIN2:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 8;
                commandType = OpenSHC::Commands::GCT_CREATE_PLATEAU;
                goto LAB_0044427c;
            case OpenSHC::Commands::M_MAPPER_OIL:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.editorActiveBrush;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0x80000000;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 0;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SET_TERRAIN);
                return;
            case OpenSHC::Commands::M_MAPPER_SHRUB1A:
            case OpenSHC::Commands::M_MAPPER_SHRUB1B:
            case OpenSHC::Commands::M_MAPPER_SHRUB1C:
            case OpenSHC::Commands::M_MAPPER_SHRUB1D:
            case OpenSHC::Commands::M_MAPPER_SHRUB1E:
            case OpenSHC::Commands::M_MAPPER_SHRUB2A:
            case OpenSHC::Commands::M_MAPPER_SHRUB2B:
            case OpenSHC::Commands::M_MAPPER_SHRUB2C:
            case OpenSHC::Commands::M_MAPPER_SHRUB2D:
            case OpenSHC::Commands::M_MAPPER_SHRUB2E:
            case OpenSHC::Commands::M_MAPPER_SHRUB3A:
            case OpenSHC::Commands::M_MAPPER_SHRUB3B:
            case OpenSHC::Commands::M_MAPPER_SHRUB3C:
            case OpenSHC::Commands::M_MAPPER_SHRUB3D:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                    = DAT_TileMapState::instance.currentMapperCommand;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 0;
                commandType = OpenSHC::Commands::GCT_PLACE_TREE_OR_ROCKUnk;
                break;
            case OpenSHC::Commands::M_MAPPER_BIGROCK1:
            case OpenSHC::Commands::M_MAPPER_BIGROCK2:
            case OpenSHC::Commands::M_MAPPER_BIGROCK3:
            case OpenSHC::Commands::M_MAPPER_BIGROCK4:
            case OpenSHC::Commands::M_MAPPER_BIGROCK5:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = DAT_TileMapState::instance.rockFlagStartNumber
                    + DAT_TileMapState::instance.unknownBrushRelated * 4;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = 0x14;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_PLACE_TREE_OR_ROCKUnk);
                if (DAT_TileMapState::instance.rockFlagStartNumber + 1 < 4) {
                    DAT_TileMapState::instance.rockFlagStartNumber = DAT_TileMapState::instance.rockFlagStartNumber + 1;
                }
                DAT_TileMapState::instance.rockFlagStartNumber = 0;
                return;
            case OpenSHC::Commands::M_MAPPER_DEER:
            case OpenSHC::Commands::M_MAPPER_LION:
            case OpenSHC::Commands::M_MAPPER_RABBIT:
            case OpenSHC::Commands::M_MAPPER_CAMEL:
            case OpenSHC::Commands::M_MAPPER_CROW_SEAGULL:
            case OpenSHC::Commands::M_MAPPER_SEAGULL:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                    = DAT_TileMapState::instance.currentMapperCommand;
                commandType = OpenSHC::Commands::GCT_CREATE_ANIMAL;
            }
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickedX;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = _clickedY;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                commandType);
        }

    }
}
}
