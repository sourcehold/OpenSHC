#include "../MapEditorLandscaping.func.hpp"

#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_ButtonBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace MapEditorLandscaping {

            // FUNCTION: STRONGHOLDCRUSADER 0x00464860
            void MenuItemRenderFunction_MapEditorLandscaping_GeneralButtons(int mapper, ...)
            {
                // The picture is the button's first one plus this frame.
                int frame = 0;
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    frame = 1;
                }
                if (mapper >= Commands::M_MAPPER_SUB_MODE_HEIGHT && mapper <= Commands::M_MAPPER_SUB_MODE_FEATURE) {
                    // The sub-mode tabs: the open one shows its third picture.
                    if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == mapper) {
                        frame = 2;
                    }
                } else {
                    frame = 0;
                    switch (mapper) {
                    case Commands::M_MAPPER_AREA:
                        // The brush size, 1 to 7, three pictures each.
                        if (DAT_TileMapState::instance.editorActiveBrush > 7
                            || DAT_TileMapState::instance.editorActiveBrush < 1) {
                            DAT_TileMapState::instance.editorActiveBrush = 1;
                        }
                        frame = DAT_TileMapState::instance.editorActiveBrush * 3 - 3;
                        break;
                    case Commands::M_MAPPER_TOMAIN:
                        // back to the main menu: never the current tool, so only hovering changes its picture
                        break;
                    case Commands::M_MAPPER_SNAP_TO:
                        // each snap mode has its own three pictures: mode 1 first, then the others, then mode 0
                        if (DAT_TileMapState::instance.editorSnapToMode == 0) {
                            frame = 6;
                        } else if (DAT_TileMapState::instance.editorSnapToMode != 1) {
                            frame = 3;
                        }
                        break;
                    case Commands::M_MAPPER_AREA_BACK:
                        // the area tool's back button draws nothing here
                        return;
                    default:
                        // A mapper tool shows its third picture while it is the current one.
                        if (DAT_TileMapState::instance.currentMapperCommand == mapper) {
                            // 1 when hovered: the ++ below makes it 2 as well
                            frame = 2;
                            if (DAT_ButtonCurrentlyInteracting::instance) {
                                frame = 1;
                            }
                        }
                        break;
                    }
                    if (DAT_ButtonCurrentlyInteracting::instance) {
                        ++frame;
                    }
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if (DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                        .alphaGmIdUnk_0xc
                    != 0) {
                    ButtonGmData* const buttonGmData
                        = &DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance];
                    // the call in each arm: one call shared by both arms measures 82.5
                    int const picture
                        = MACRO_CALL_MEMBER(
                              OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(FALSE)
                        + frame;
                    if (DAT_ButtonBlendStrength::instance != 32) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)((OpenSHC::IO::Graphics::GmID)buttonGmData->gmId_0x0,
                            picture, DAT_ButtonX::instance, DAT_ButtonY::instance, DAT_ButtonBlendStrength::instance);
                    }
                    DAT_CurrentButtonPictureInGm::instance = picture;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
                ButtonGmData* const buttonGmData
                    = &DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance];
                int const picture = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm,
                                        buttonGmData)(FALSE)
                    + frame;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)buttonGmData->gmId_0x0, picture,
                    DAT_ButtonX::instance, DAT_ButtonY::instance);
                // the render target first: the picture first loses the match
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                DAT_CurrentButtonPictureInGm::instance = picture;
            }

        }
    }
}
}
