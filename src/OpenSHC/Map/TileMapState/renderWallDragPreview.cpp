#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F8BD0
    void TileMapState::renderWallDragPreview(
        int playerID, uint x1, uint y1, uint x2, uint y2, undefined4 command)
    {
        int budget = 0;
        if (x1 > 399 || y1 > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y1 * 400 + x1] == 0) {
            return;
        }
        if (x2 > 399 || y2 > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y2 * 400 + x2] == 0) {
            return;
        }

        this->DAT_WallTileCountCurrentDrag = 0;
        int overshoot = 2;
        if ((short)command == 0x1b) {
            budget = this->field119_0x554924;
            if (this->field118_0x554920 == 0) {
                this->ConstructionGFXLayer[DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile + x1]
                    = (short)GMTotalPicturesProcessed::instance[6] + 0x13;
                return;
            }
        }

        /* the drag walks one tile at a time towards (x2, y2), on whichever axis is further away */
        int upY = y1 - y2;
        int downY = y2 - y1;
        uint x = x1;
        uint y = y1;
        int leftX = x1 - x2;
        int rightX = x2 - x1;
        int* translation = &DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile;
        int tile;
        do {
            if ((short)command == 0x1b && budget < 0x18) {
                break;
            }
            tile = *translation + x;
            if ((short)command == 0x1b && (this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                break;
            }
            if (this->constructionTileCount <= this->DAT_WallTileCountCurrentDrag) {
                break;
            }

            /* a crenel dragged over an existing one does not count against the tile budget */
            bool onCrenel = false;
            if ((short)command == 0x19 && (this->LogicLayer[tile] & L_CRENEL) != 0) {
                onCrenel = true;
            }
            if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) == 0 || this->DamageLayer[tile] != 0 || onCrenel) {
                if (!onCrenel) {
                    this->DAT_WallTileCountCurrentDrag = this->DAT_WallTileCountCurrentDrag + 1;
                }
                if (this->illegalBuild == FALSE) {
                    if ((short)command == 0x19) {
                        this->ConstructionGFXLayer[tile] = (ushort)GMTotalPicturesProcessed::instance[6];
                    } else if ((short)command == 0x2e) {
                        this->ConstructionGFXLayer[tile] = (ushort)GMTotalPicturesProcessed::instance[6] + 1;
                    } else if ((short)command == 0x1a) {
                        this->ConstructionGFXLayer[tile] = (ushort)GMTotalPicturesProcessed::instance[6] + 4;
                    } else if ((short)command == 0x1b) {
                        /* a stair climbs one graphic per eight units of height below the wall top */
                        int steps = (budget - (int)(uint)this->HeightLayer[tile]) / 8 - 1;
                        if (steps > 0) {
                            if (steps > 10) {
                                steps = 10;
                            }
                            this->ConstructionGFXLayer[tile] = (short)steps + 8 + (ushort)GMTotalPicturesProcessed::instance[6];
                        } else {
                            this->DAT_WallTileCountCurrentDrag = this->DAT_WallTileCountCurrentDrag - 1;
                        }
                    }
                } else if ((short)command == 0x19) {
                    this->ConstructionGFXLayer[tile] = (ushort)GMTotalPicturesProcessed::instance[6] + 0x13;
                } else if ((short)command == 0x2e) {
                    this->ConstructionGFXLayer[tile] = (ushort)GMTotalPicturesProcessed::instance[6] + 0x13;
                } else if ((short)command == 0x1a) {
                    this->ConstructionGFXLayer[tile] = (ushort)GMTotalPicturesProcessed::instance[6] + 0x14;
                } else if ((short)command == 0x1b) {
                    this->ConstructionGFXLayer[tile] = (ushort)GMTotalPicturesProcessed::instance[6] + 0x13;
                }
            }

            int stepX = leftX;
            if ((int)x < (int)x2) {
                stepX = rightX;
            }
            int stepY = upY;
            if ((int)y < (int)y2) {
                stepY = downY;
            }
            if ((short)command == 0x1b) {
                if (stepY < stepX) {
                    if ((int)x < (int)x2) {
                        leftX = leftX + 1;
                        x = x + 1;
                        rightX = rightX - 1;
                    } else {
                        leftX = leftX - 1;
                        x = x - 1;
                        rightX = rightX + 1;
                    }
                } else if (stepY > 0) {
                    if ((int)y < (int)y2) {
                        translation = translation + 3;
                        y = y + 1;
                        upY = upY + 1;
                        downY = downY - 1;
                    } else {
                        translation = translation - 3;
                        y = y - 1;
                        upY = upY - 1;
                        downY = downY + 1;
                    }
                } else {
                    overshoot = overshoot - 1;
                }
            } else {
                if (stepX != 0) {
                    if ((int)x < (int)x2) {
                        leftX = leftX + 1;
                        x = x + 1;
                        rightX = rightX - 1;
                    } else {
                        leftX = leftX - 1;
                        x = x - 1;
                        rightX = rightX + 1;
                    }
                }
                if (stepY != 0) {
                    if ((int)y < (int)y2) {
                        translation = translation + 3;
                        y = y + 1;
                        upY = upY + 1;
                        downY = downY - 1;
                    } else {
                        translation = translation - 3;
                        y = y - 1;
                        upY = upY - 1;
                        downY = downY + 1;
                    }
                }
                if (x == x2 && y == y2) {
                    overshoot = overshoot - 1;
                }
            }
            if (budget > 0x10 && overshoot == 2) {
                budget = budget - 0x10;
            }
        } while (x != x2 || y != y2 || overshoot != 0);

        if (this->illegalBuild != FALSE) {
            this->DAT_WallTileCountCurrentDrag = 0;
        }
        if (this->field145_0x554980 != 0) {
            return;
        }
        if ((short)command == 0x2e) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processWallBuildingLoss, DAT_BuildingsState::ptr)(
                playerID, 0, this->DAT_WallTileCountCurrentDrag, 1);
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processWallBuildingLoss, DAT_BuildingsState::ptr)(
            playerID, this->DAT_WallTileCountCurrentDrag, 0, 1);
    }

}
}
