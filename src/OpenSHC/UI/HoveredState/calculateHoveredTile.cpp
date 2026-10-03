#include "../HoveredState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::GameMode;
    using OpenSHC::IO::Graphics::GmID;

    /*
      WARNING: Enum "MappersEnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005119D0
    void HoveredState::calculateHoveredTile()
    {
        int iVar1;
        int iVar2;
        int iVar3;
        int imageX;
        int imageID;
        HoveredStateElement* piVar6;
        int imageY;
        int local_10;
        int local_c;
        int local_8;
        iVar1 = DAT_TileMapState::instance.uiBuildingRotation;
        imageID = 0;
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            local_c = 0;
            local_10 = 0;
            piVar6 = &this->elements[0];
            local_8 = 0x14;
            do {
                if (piVar6->type == OpenSHC::Commands::M_MAPPER_NULL)
                    goto LAB_00511c12;
                switch (piVar6->type) {
                case OpenSHC::Commands::M_MAPPER_FLAG_TYPE0:
                case OpenSHC::Commands::M_MAPPER_FLAG_TYPE1:
                case OpenSHC::Commands::M_MAPPER_FLAG_TYPE2:
                case OpenSHC::Commands::M_MAPPER_FLAG_TYPE3:
                    switch (piVar6->type) {
                    case OpenSHC::Commands::M_MAPPER_FLAG_TYPE0:
                        imageID = 9;
                        local_c = 0xf;
                        goto LAB_00511b19;
                    case OpenSHC::Commands::M_MAPPER_FLAG_TYPE1:
                        imageID = 0x29;
                        local_c = 0xf;
                        local_10 = -2;
                        break;
                    case OpenSHC::Commands::M_MAPPER_FLAG_TYPE2:
                        imageID = 0x49;
                        local_c = 6;
                        local_10 = 6;
                        break;
                    case OpenSHC::Commands::M_MAPPER_FLAG_TYPE3:
                        imageID = 0x69;
                        local_c = 6;
                    LAB_00511b19:
                        local_10 = 7;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_ANIM_FLAGS, imageID, local_c, local_10,
                        DAT_ViewportRenderState::instance.translationMatrix[piVar6->y].addXgetTile + piVar6->x, 0xd);
                    break;
                    default:
                        DAT_TileMapState::instance.field188_0x554a14 = 1;
                    DAT_TileMapState::instance.uiBuildingRotation = piVar6->rotationOrExtraInfo;
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setConstructionGFXLayerBasedOnPlacementChecks,
                        DAT_TileMapState::ptr)(
                        piVar6->x, piVar6->y, (MappersEnum)((int)((uint)(ushort)(short)piVar6->type)), piVar6->size);
                    break;
                case OpenSHC::Commands::M_MAPPER_HEADS:
                    imageID = piVar6->size + 1;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_ANIM_HEADS, imageID, 0xf, 7,
                        DAT_ViewportRenderState::instance.translationMatrix[piVar6->y].addXgetTile + piVar6->x, 0x1d);
                    break;
                case OpenSHC::Commands::M_MAPPER_BRAZIER:
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_BODY_BRAZIER, 1, 0xf, 7,
                        DAT_ViewportRenderState::instance.translationMatrix[piVar6->y].addXgetTile + piVar6->x, 0x1d);
                    break;
                case OpenSHC::Commands::M_MAPPER_CATAPULT:
                case OpenSHC::Commands::M_MAPPER_TREBUCHET:
                case OpenSHC::Commands::M_MAPPER_SIEGE_TOWER:
                case OpenSHC::Commands::M_MAPPER_BATTERING_RAM:
                case OpenSHC::Commands::M_MAPPER_PORTABLE_SHIELD:
                case OpenSHC::Commands::M_MAPPER_ARAB_BALLISTA:
                    iVar3 = piVar6->x;
                    iVar2 = piVar6->y;
                    imageX = 0;
                    imageY = 0;
                    switch (DAT_TileMapState::instance.mapOrientation) {
                    case 0:
                        imageX = 0xd;
                        iVar3 = iVar3 + 1;
                        iVar2 = iVar2 + 1;
                        imageY = 2;
                        break;
                    case 2:
                        imageX = 0x2d;
                        iVar3 = iVar3 + -1;
                        iVar2 = iVar2 + 1;
                        imageY = -0xe;
                        break;
                    case 4:
                        imageX = 0xd;
                        iVar3 = iVar3 + -1;
                        imageY = -0x1e;
                        goto LAB_00511bbe;
                    case 6:
                        imageX = -0x13;
                        iVar3 = iVar3 + 1;
                        imageY = -0xc;
                    LAB_00511bbe:
                        iVar2 = iVar2 + -1;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_BODY_TENT, 1, imageX, imageY,
                        DAT_ViewportRenderState::instance.translationMatrix[iVar2].addXgetTile + iVar3, 5);
                    break;
                case OpenSHC::Commands::M_MAPPER_MANGONEL:
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_BODY_MANGONEL, 1, 0, 0,
                        DAT_ViewportRenderState::instance.translationMatrix[piVar6->y].addXgetTile + piVar6->x, 5);
                    break;
                case OpenSHC::Commands::M_MAPPER_BALLISTA:
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_BODY_BALLISTA, 1, 0, 0,
                        DAT_ViewportRenderState::instance.translationMatrix[piVar6->y].addXgetTile + piVar6->x, 5);
                }
            LAB_00511c12:
                piVar6 = piVar6 + 6;
                local_8 = local_8 + -1;
            } while (local_8 != 0);
        }
        DAT_TileMapState::instance.uiBuildingRotation = iVar1;
    }

}
}
