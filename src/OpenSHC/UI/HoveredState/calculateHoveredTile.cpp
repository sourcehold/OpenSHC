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

    using namespace OpenSHC::Commands;
    using namespace OpenSHC::IO::Graphics;

    // FUNCTION: STRONGHOLDCRUSADER 0x005119D0
    void HoveredState::calculateHoveredTile()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            return;
        }
        int imageID = 0;
        int flagX = 0;
        int flagY = 0;
        int const rotation = DAT_TileMapState::instance.uiBuildingRotation;
        for (int i = 0; i < countof(this->elements); ++i) {
            if (this->elements[i].type == M_MAPPER_NULL) {
                continue;
            }
            switch (this->elements[i].type) {
            case M_MAPPER_MANGONEL:
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(GID_BODY_MANGONEL, 1, 0, 0,
                    DAT_ViewportRenderState::instance.translationMatrix[this->elements[i].y].addXgetTile
                        + this->elements[i].x,
                    5);
                break;
            case M_MAPPER_BALLISTA:
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(GID_BODY_BALLISTA, 1, 0, 0,
                    DAT_ViewportRenderState::instance.translationMatrix[this->elements[i].y].addXgetTile
                        + this->elements[i].x,
                    5);
                break;
            case M_MAPPER_BRAZIER:
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(GID_BODY_BRAZIER, 1, 15, 7,
                    DAT_ViewportRenderState::instance.translationMatrix[this->elements[i].y].addXgetTile
                        + this->elements[i].x,
                    29);
                break;
            case M_MAPPER_FLAG_TYPE0:
            case M_MAPPER_FLAG_TYPE1:
            case M_MAPPER_FLAG_TYPE2:
            case M_MAPPER_FLAG_TYPE3: {
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->elements[i].y].addXgetTile
                    + this->elements[i].x;
                switch (this->elements[i].type) {
                case M_MAPPER_FLAG_TYPE0:
                    imageID = 9;
                    flagX = 15;
                    flagY = 7;
                    break;
                case M_MAPPER_FLAG_TYPE1:
                    imageID = 41;
                    flagX = 15;
                    flagY = -2;
                    break;
                case M_MAPPER_FLAG_TYPE2:
                    imageID = 73;
                    flagX = 6;
                    flagY = 6;
                    break;
                case M_MAPPER_FLAG_TYPE3:
                    imageID = 105;
                    flagX = 6;
                    flagY = 7;
                    break;
                }
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(GID_ANIM_FLAGS, imageID, flagX, flagY, tile, 13);
                break;
            }
            case M_MAPPER_HEADS:
                imageID = this->elements[i].size + 1;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(GID_ANIM_HEADS, imageID, 15, 7,
                    DAT_ViewportRenderState::instance.translationMatrix[this->elements[i].y].addXgetTile
                        + this->elements[i].x,
                    29);
                break;
            case M_MAPPER_CATAPULT:
            case M_MAPPER_TREBUCHET:
            case M_MAPPER_SIEGE_TOWER:
            case M_MAPPER_BATTERING_RAM:
            case M_MAPPER_PORTABLE_SHIELD:
            case M_MAPPER_ARAB_BALLISTA: {
                // siege equipment shows its tent on the tile in front, by the map's orientation
                int x = this->elements[i].x;
                int y = this->elements[i].y;
                int imageX = 0;
                int imageY = 0;
                switch (DAT_TileMapState::instance.mapOrientation) {
                case 0:
                    ++x;
                    imageX = 13;
                    ++y;
                    imageY = 2;
                    break;
                case 4:
                    --x;
                    imageX = 13;
                    imageY = -30;
                    --y;
                    break;
                case 2:
                    --x;
                    imageX = 45;
                    ++y;
                    imageY = -14;
                    break;
                case 6:
                    ++x;
                    imageX = -19;
                    imageY = -12;
                    --y;
                    break;
                }
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(GID_BODY_TENT, 1, imageX, imageY,
                    DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x, 5);
                break;
            }
            default:
                // any other mapper is a building placement preview, in the element's rotation
                DAT_TileMapState::instance.skipPlacementFailChecks = 1;
                DAT_TileMapState::instance.uiBuildingRotation = this->elements[i].rotationOrExtraInfo;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setConstructionGFXLayerBasedOnPlacementChecks,
                    DAT_TileMapState::ptr)(this->elements[i].x, this->elements[i].y,
                    (MappersEnum)(ushort)this->elements[i].type, this->elements[i].size);
                break;
            }
        }
        DAT_TileMapState::instance.uiBuildingRotation = rotation;
    }

}
}
