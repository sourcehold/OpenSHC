#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F8BD0
    void TileMapState::renderWallDragPreview(int playerID, uint x1, uint y1, uint x2, uint y2, short command)
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
        if (command == OpenSHC::Commands::M_MAPPER_STAIR) {
            budget = this->maxWallHeightInPath;
            if (this->field_0x554920 == 0) {
                this->ConstructionGFXLayer[DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile + x1]
                    = (short)GMFirstPictureIndex::instance[6] + 19;
                return;
            }
        }

        // the drag walks one tile at a time towards (x2, y2), on whichever axis is further away
        uint x = x1;
        uint y = y1;
        int upY = y1 - y2;
        int leftX = x1 - x2;
        int downY = y2 - y1;
        int rightX = x2 - x1;
        int* translation = &DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile;
        do {
            if (command == OpenSHC::Commands::M_MAPPER_STAIR && budget < 24) {
                break;
            }
            int const tile = *translation + x;
            if (command == OpenSHC::Commands::M_MAPPER_STAIR && (this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                break;
            }
            if (this->DAT_WallTileCountCurrentDrag >= this->constructionTileCount) {
                break;
            }
            this->DAT_WallTileCountCurrentDrag += 1;

            // a crenel dragged over an existing one does not count against the tile budget
            BOOLEnum onCrenel = FALSE;
            if (command == OpenSHC::Commands::M_MAPPER_WALL && (this->LogicLayer[tile] & L_CRENEL) != 0) {
                onCrenel = TRUE;
            }
            if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0 && this->DamageLayer[tile] == 0 && !onCrenel) {
                this->DAT_WallTileCountCurrentDrag -= 1;
            } else {
                if (onCrenel) {
                    this->DAT_WallTileCountCurrentDrag -= 1;
                }
                if (this->illegalBuild != FALSE) {
                    if (command == OpenSHC::Commands::M_MAPPER_WALL) {
                        this->ConstructionGFXLayer[tile] = (ushort)GMFirstPictureIndex::instance[6] + 19;
                    } else if (command == OpenSHC::Commands::M_MAPPER_WOODWALL) {
                        this->ConstructionGFXLayer[tile] = (ushort)GMFirstPictureIndex::instance[6] + 19;
                    } else if (command == OpenSHC::Commands::M_MAPPER_CRENAL) {
                        this->ConstructionGFXLayer[tile] = (ushort)GMFirstPictureIndex::instance[6] + 20;
                    } else if (command == OpenSHC::Commands::M_MAPPER_STAIR) {
                        this->ConstructionGFXLayer[tile] = (ushort)GMFirstPictureIndex::instance[6] + 19;
                    }
                } else if (command == OpenSHC::Commands::M_MAPPER_WALL) {
                    this->ConstructionGFXLayer[tile] = (ushort)GMFirstPictureIndex::instance[6];
                } else if (command == OpenSHC::Commands::M_MAPPER_WOODWALL) {
                    this->ConstructionGFXLayer[tile] = (ushort)GMFirstPictureIndex::instance[6] + 1;
                } else if (command == OpenSHC::Commands::M_MAPPER_CRENAL) {
                    this->ConstructionGFXLayer[tile] = (ushort)GMFirstPictureIndex::instance[6] + 4;
                } else if (command == OpenSHC::Commands::M_MAPPER_STAIR) {
                    // a stair climbs one graphic per eight units of height below the wall top
                    int steps = (budget - this->HeightLayer[tile]) / 8 - 1;
                    if (steps <= 0) {
                        this->DAT_WallTileCountCurrentDrag -= 1;
                    } else {
                        if (steps > 10) {
                            steps = 10;
                        }
                        this->ConstructionGFXLayer[tile] = steps + GMFirstPictureIndex::instance[6] + 8;
                    }
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
            if (command == OpenSHC::Commands::M_MAPPER_STAIR) {
                if (stepX > stepY) {
                    if ((int)x >= (int)x2) {
                        leftX -= 1;
                        x -= 1;
                        rightX += 1;
                    } else {
                        leftX += 1;
                        x += 1;
                        rightX -= 1;
                    }
                } else if (stepY > 0) {
                    if ((int)y >= (int)y2) {
                        translation -= 3;
                        y -= 1;
                        upY -= 1;
                        downY += 1;
                    } else {
                        translation += 3;
                        y += 1;
                        upY += 1;
                        downY -= 1;
                    }
                } else {
                    overshoot -= 1;
                }
            } else {
                if (stepX != 0) {
                    if ((int)x >= (int)x2) {
                        leftX -= 1;
                        x -= 1;
                        rightX += 1;
                    } else {
                        leftX += 1;
                        x += 1;
                        rightX -= 1;
                    }
                }
                if (stepY != 0) {
                    if ((int)y >= (int)y2) {
                        translation -= 3;
                        y -= 1;
                        upY -= 1;
                        downY += 1;
                    } else {
                        translation += 3;
                        y += 1;
                        upY += 1;
                        downY -= 1;
                    }
                }
                if (x == x2 && y == y2) {
                    overshoot -= 1;
                }
            }
            if (budget > 16 && overshoot == 2) {
                budget -= 16;
            }
        } while (x != x2 || y != y2 || overshoot != 0);

        if (this->illegalBuild != FALSE) {
            this->DAT_WallTileCountCurrentDrag = 0;
        }
        if (this->wallDragButtonUp != 0) {
            return;
        }
        if (command == OpenSHC::Commands::M_MAPPER_WOODWALL) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processWallBuildingLoss,
                DAT_BuildingsState::ptr)(playerID, 0, this->DAT_WallTileCountCurrentDrag, 1);
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processWallBuildingLoss,
            DAT_BuildingsState::ptr)(playerID, this->DAT_WallTileCountCurrentDrag, 0, 1);
    }

}
}
