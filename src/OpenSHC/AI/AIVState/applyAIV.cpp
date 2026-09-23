#include "../AIVState.func.hpp"

#include "OpenSHC/AI/AIVUnitType.hpp"
#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_AIVDefinedData.hpp"
#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004EF0D0
    void AIVState::applyAIV(int aivID, int playerID)
    {
        BOOLEnum keepDefined = FALSE;
        MACRO_CALL_MEMBER(IO::FilePackager_Func::unpackAIVFile, FilePackagerObj::ptr)(
            DAT_AIVDefinedData::instance.AIVSectionAddressArray,
            DAT_AIVDefinedData::instance.AIVFileNames[this->aivs[aivID].aiType - 2][this->aivs[aivID].castleID]);
        MACRO_CALL_MEMBER(AIVState_Func::rotateAIV, this)(this->aivs[aivID].keepOrientation);

        // single buildings and the keep, steps is accessed as a flat 100 * 100 array
        int index = 0;
        for (int y = 0; y < 100; ++y) {
            for (int x = 0; x < 100; ++x, ++index) {
                if (this->isHandled[index]) {
                    continue;
                }
                int const type = this->constructions[index];
                if (type == 0) {
                    this->isHandled[index] = 1;
                } else if (type == 2) {
                    this->isHandled[index] = 1;
                } else if (type == AIV::AIVBT_KEEP2) {
                    if (!keepDefined) {
                        this->keepX = this->aivs[aivID].keepXOffset + x;
                        this->keepY = this->aivs[aivID].keepYOffset + y;
                        keepDefined = TRUE;
                    }
                    this->isHandled[index] = 1;
                } else {
                    MappersEnum const mapper = MACRO_CALL_MEMBER(AIVState_Func::convertAIVBuildingTypeToCommandBuildingType,
                        this)((AIV::AIVBuildingType2)type);
                    int const step = this->steps[0][index];
                    // walls, moats and pitch ditches are collected below
                    if (mapper == Commands::M_MAPPER_WALL || mapper == Commands::M_MAPPER_WOODWALL
                        || mapper == Commands::M_MAPPER_CRENAL || mapper == Commands::M_MAPPER_CRENAL2
                        || mapper == Commands::M_MAPPER_MOAT || mapper == Commands::M_MAPPER_PITCH_DITCH) {
                        continue;
                    }
                    this->isHandled[index] = 1;
                    if (this->aivs[aivID].aivBuildingSteps[step].quantity > 0) {
                        continue;
                    }
                    int const realY = this->aivs[aivID].keepYOffset + y;
                    if (!MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::xyAreValid, DAT_ViewportRenderState::ptr)(
                            this->aivs[aivID].keepXOffset + x, realY)) {
                        continue;
                    }
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = mapper;
                    this->aivs[aivID].aivBuildingSteps[step].buildStatus = AIVBSS_unbuilt;
                    this->aivs[aivID].aivBuildingSteps[step].quantity = 1;
                    this->aivs[aivID].aivBuildingSteps[step].location.tile.tile
                        = DAT_ViewportRenderState::instance.translationMatrix[realY].addXgetTile
                        + this->aivs[aivID].keepXOffset + x;
                    if (step > this->aivs[aivID].totalSteps) {
                        this->aivs[aivID].totalSteps = step;
                    }
                }
            }
        }

        // collect the tiles of each wall, moat and pitch ditch step, one step per pass
        int startY = 0;
        BOOLEnum selected;
        do {
            selected = FALSE;
            if (startY >= 100) {
                break;
            }
            int step;
            MappersEnum mapper;
            int index = startY * 100;
            for (int y = startY; y < 100; ++y) {
                for (int x = 0; x < 100; ++x, ++index) {
                    if (this->isHandled[index]) {
                        continue;
                    }
                    if (selected) {
                        if (this->steps[0][index] != step) {
                            continue;
                        }
                    } else {
                        mapper = MACRO_CALL_MEMBER(AIVState_Func::convertAIVBuildingTypeToCommandBuildingType, this)(
                            (AIV::AIVBuildingType2)this->constructions[index]);
                        step = this->steps[0][index];
                        this->aivs[aivID].aivBuildingSteps[step].location.tile.tile
                            = this->aivs[aivID].wallLocationsArrayIndex;
                        selected = TRUE;
                        if (y > startY) {
                            startY = y;
                        }
                    }
                    uint const realX = this->aivs[aivID].keepXOffset + x;
                    uint const realY = this->aivs[aivID].keepYOffset + y;
                    if (realX <= 399 && realY <= 399
                        && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[realY * 400 + realX]) {
                        this->aivs[aivID].aivBuildingSteps[step].buildStatus = AIVBSS_unbuilt;
                        this->aivs[aivID].aivBuildingSteps[step].buildingType = mapper;
                        ++this->aivs[aivID].aivBuildingSteps[step].quantity;
                        this->aivs[aivID].locationsArray[this->aivs[aivID].wallLocationsArrayIndex]
                            = DAT_ViewportRenderState::instance.translationMatrix[realY].addXgetTile
                            + this->aivs[aivID].keepXOffset + x;
                        ++this->aivs[aivID].wallLocationsArrayIndex;
                        if (step > this->aivs[aivID].totalSteps) {
                            this->aivs[aivID].totalSteps = step;
                        }
                    }
                    this->isHandled[index] = 1;
                }
            }
        } while (selected);

        // rotate the unit locations and copy them to the player
        int y;
        int x;
        for (int unitType = 0; unitType < 22; ++unitType) {
            DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[unitType] = 0;
            if (unitType == AIVUT_PIKEMAN || unitType == AIVUT_SWORDSMAN || unitType == AIVUT_ARABIAN_SWORDSMAN) {
                continue;
            }
            for (int i = 0; i < 10; ++i) {
                int const location = DAT_AIVState::instance.unitLocations[unitType][i];
                if (location <= 0) {
                    continue;
                }
                int const relativeY = location / 100;
                int const relativeX = location % 100;
                if (this->aivs[aivID].keepOrientation == 0) {
                    x = relativeX;
                    y = relativeY;
                } else if (this->aivs[aivID].keepOrientation == 4) {
                    x = 99 - relativeX;
                    y = 99 - relativeY;
                } else if (this->aivs[aivID].keepOrientation == 6) {
                    x = 99 - relativeY;
                    y = relativeX;
                } else if (this->aivs[aivID].keepOrientation == 2) {
                    y = 99 - relativeX;
                    x = relativeY;
                }
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->aivs[aivID].keepYOffset + y]
                                     .addXgetTile
                    + this->aivs[aivID].keepXOffset + x;
                DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlots[unitType][i] = tile;
                if (tile > 0) {
                    ++DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[unitType];
                }
            }
        }

        for (int i = 0; i < 20; ++i) {
            DAT_GameState::instance.playerDataArray[playerID].aivPauses[i] = (short)DAT_AIVState::instance.pauses[i];
        }
        DAT_GameState::instance.playerDataArray[playerID].aivCurrentPauseIndex = 1;
        if (DAT_AIVState::instance.pauseDelay <= 0) {
            DAT_AIVState::instance.pauseDelay = 100;
        }
        DAT_GameState::instance.playerDataArray[playerID].aivPauseDelay = DAT_AIVState::instance.pauseDelay;

        // steps that can not be built
        for (int step = 1; step <= this->aivs[aivID].totalSteps; ++step) {
            int const buildingType = this->aivs[aivID].aivBuildingSteps[step].buildingType;
            if (buildingType == Commands::M_MAPPER_NULL || buildingType == Commands::M_MAPPER_KEEP3
                || buildingType == Commands::M_MAPPER_POND1 || buildingType == Commands::M_MAPPER_POND2_SMALL
                || buildingType == Commands::M_MAPPER_POND3_LARGE1 || buildingType == Commands::M_MAPPER_POND4_LARGE2) {
                this->aivs[aivID].aivBuildingSteps[step].buildStatus = AIVBSS_disabled;
            }
        }
    }

}
}
