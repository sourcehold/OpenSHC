#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040DC70
        void BuildingsState::createEntityForAssemblyPointsForActiveTabType()
        {
            // Shows the rally point flags and unit previews of the building whose menu is open
            if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM) {
                for (int i = 0; i < 7; ++i) {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .barracksAssemblyPoints[i]
                            .x
                        == 0) {
                        continue;
                    }
                    int tile
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .barracksAssemblyPoints[i]
                              .x
                        + DAT_ViewportRenderState::instance
                              .translationMatrix[DAT_GameState::instance
                                      .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                      .barracksAssemblyPoints[i]
                                      .y]
                              .addXgetTile;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                        (int)DAT_TileMapState::instance.field165_0x5549d0 % 10 + 97, 18, -1, tile, 0xa0022);
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)((GmID)DAT_BuildingDefinedData::instance.field382_0x9e1c[i][0],
                        DAT_BuildingDefinedData::instance.field382_0x9e1c[i][1],
                        DAT_BuildingDefinedData::instance.field382_0x9e1c[i][2] + 41,
                        DAT_BuildingDefinedData::instance.field382_0x9e1c[i][3] - 40, tile, 0xc0006);
                    if (i == 6) {
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((GmID)DAT_BuildingDefinedData::instance.field383_0x9e8c[0],
                            DAT_BuildingDefinedData::instance.field383_0x9e8c[1],
                            DAT_BuildingDefinedData::instance.field383_0x9e8c[2] + 41,
                            DAT_BuildingDefinedData::instance.field383_0x9e8c[3] - 40, tile, 0xc0006);
                    }
                }
                return;
            }
            if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                for (int i = 0; i < 7; ++i) {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .mercenaryAssemblyPoints[i][0]
                        == 0) {
                        continue;
                    }
                    int tile
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .mercenaryAssemblyPoints[i][0]
                        + DAT_ViewportRenderState::instance
                              .translationMatrix[DAT_GameState::instance
                                      .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                      .mercenaryAssemblyPoints[i][1]]
                              .addXgetTile;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                        (int)DAT_TileMapState::instance.field165_0x5549d0 % 10 + 97, 18, -1, tile, 0xa0022);
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)((GmID)DAT_BuildingDefinedData::instance.field384_0x9e9c[i][0],
                        DAT_BuildingDefinedData::instance.field384_0x9e9c[i][1],
                        DAT_BuildingDefinedData::instance.field384_0x9e9c[i][2] + 41,
                        DAT_BuildingDefinedData::instance.field384_0x9e9c[i][3] - 40, tile, 0xc0006);
                    if (i == 1) {
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)((GmID)DAT_BuildingDefinedData::instance.field383_0x9e8c[0],
                            DAT_BuildingDefinedData::instance.field383_0x9e8c[1],
                            DAT_BuildingDefinedData::instance.field383_0x9e8c[2] + 41,
                            DAT_BuildingDefinedData::instance.field383_0x9e8c[3] - 40, tile, 0xc0006);
                    }
                }
                return;
            }
            if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_ENGINEERSGUILD) {
                for (int i = 0; i < 2; ++i) {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .engineersAssemblyPoints[i]
                            .x
                        == 0) {
                        continue;
                    }
                    int tile
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .engineersAssemblyPoints[i]
                              .x
                        + DAT_ViewportRenderState::instance
                              .translationMatrix[DAT_GameState::instance
                                      .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                      .engineersAssemblyPoints[i]
                                      .y]
                              .addXgetTile;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                        (int)DAT_TileMapState::instance.field165_0x5549d0 % 10 + 97, 18, -1, tile, 0xa0022);
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)((GmID)DAT_BuildingDefinedData::instance.field401_0x9f1c[i][0],
                        DAT_BuildingDefinedData::instance.field401_0x9f1c[i][1],
                        DAT_BuildingDefinedData::instance.field401_0x9f1c[i][2] + 41,
                        DAT_BuildingDefinedData::instance.field401_0x9f1c[i][3] - 40, tile, 0xc0006);
                }
                return;
            }
            if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_TUNNELERSGUILD) {
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .tunnelersGuildAssemblyPointX
                    == 0) {
                    return;
                }
                int tile = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                               .tunnelersGuildAssemblyPointX
                    + DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_GameState::instance
                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                  .tunnelersGuildAssemblyPointY]
                          .addXgetTile;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                    (int)DAT_TileMapState::instance.field165_0x5549d0 % 10 + 97, 18, -1, tile, 0xa0022);
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_BODY_TUNNELOR, 3, 14, -40, tile, 0xc0006);
                return;
            }
            if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_CATHEDRAL) {
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .cathedralAssemblyPointX
                    == 0) {
                    return;
                }
                int tile = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                               .cathedralAssemblyPointX
                    + DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_GameState::instance
                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                  .cathedralAssemblyPointY]
                          .addXgetTile;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                    (int)DAT_TileMapState::instance.field165_0x5549d0 % 10 + 97, 18, -1, tile, 0xa0022);
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(
                    OpenSHC::IO::Graphics::GID_BODY_FIGHTING_MONK, 3, 14, -40, tile, 0xc0006);
            }
        }

    }
}
}
