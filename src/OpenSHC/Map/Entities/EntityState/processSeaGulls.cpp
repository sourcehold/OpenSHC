#include "../../../Map.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using DE::SHCDE::eSFX;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00406900
        void EntityState::processSeaGulls(int seagullID)
        {
            short* psVar1;
            short sVar2;
            double dVar3;
            short _newAngle;
            short sVar5;
            short _targetYPart1;
            short sVar4;
            uint _targetX;
            uint _yDiff;
            uint _newX;
            BOOLEnum _newBounds;
            int _oldMicroY;
            int _oldMicroX;
            uint _oldX;
            BOOLEnum _oldBounds;
            int _targetXPart2;
            int _targetYPart2;
            int iVar6;
            uint uVar7;
            int _microX;
            uint _newY;
            uint _oldY;
            int iVar8;
            uint uVar9;
            int _newMicroY;
            short _targetXPart1;
            int _newMicroX;
            int _entityID;
            double fVar10;
            double fVar11;
            short _y;
            short _yPosition;
            sVar4 = this->seagullArray[seagullID].someCountDown;
            _entityID = (int)this->seagullArray[seagullID].entityID;
            if (sVar4) {
                sVar4 = sVar4 + -1;
                this->seagullArray[seagullID].someCountDown = sVar4;
                if (sVar4) {
                    return;
                }
                _y = this->entityArray[_entityID].microY;
                this->entityArray[_entityID].targetX = this->entityArray[_entityID].microX;
                _yPosition = this->entityArray[_entityID].yPosition;
                this->entityArray[_entityID].targetY = _y;
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)this->entityArray[_entityID].xPosition, (int)((int)(_yPosition)),
                    DE::SHCDE::FX_GULL_SURFACE);
            }
            _microX = (int)this->entityArray[_entityID].microX;
            _targetX = _microX - this->entityArray[_entityID].targetX;
            if (((int)((_targetX ^ (int)_targetX >> 0x1f) - ((int)_targetX >> 0x1f)) < 3)
                && (_yDiff = (int)this->entityArray[_entityID].microY - (int)this->entityArray[_entityID].targetY,
                    (int)((_yDiff ^ (int)_yDiff >> 0x1f) - ((int)_yDiff >> 0x1f)) < 3)) {
                if (((int)this->seagullArray[seagullID].randomNumber ^ this->entityArray[_entityID].rng_1
                        ^ (int)SEC_RNG::instance.currentNumber2)
                        % 500
                    == 123) {
                    _newMicroY
                        = (int)this->entityArray[_entityID].someMicroY + (int)this->entityArray[_entityID].microY;
                    _newMicroX = this->entityArray[_entityID].someMicroX + _microX;
                    _newY = _newMicroY / 8;
                    _newX = _newMicroX / 8;
                    _newBounds = MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(_newX, _newY);
                    if (_newBounds) {
                        _oldMicroY = (int)this->entityArray[_entityID].microY;
                        _oldMicroX = (int)this->entityArray[_entityID].microX;
                        _oldY = _oldMicroY / 8;
                        _oldX = _oldMicroX / 8;
                        _oldBounds = MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::xyAreValid,
                            DAT_ViewportRenderState::ptr)(_oldX, _oldY);
                        if (((_oldBounds)
                                && ((
                                    DAT_TileMapState::instance.LogicLayer
                                        [DAT_ViewportRenderState::instance.translationMatrix[_newY].addXgetTile + _newX]
                                    & 1)))
                            && ((DAT_TileMapState::instance
                                     .LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[_oldY].addXgetTile
                                         + _oldX]
                                & 1))) {
                            this->seagullArray[seagullID].someCountDown = 160;
                            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::setProjectileTargetPosition,
                                this)(_entityID, (int)((int)(this->entityArray[_entityID].microX)),
                                (int)((int)(this->entityArray[_entityID].microY)), 0xfa, _newMicroX, _newMicroY, 0);
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                (int)this->entityArray[_entityID].xPosition,
                                (int)((int)(this->entityArray[_entityID].yPosition)), DE::SHCDE::FX_GULL);
                            return;
                        }
                    }
                }
                sVar4 = this->seagullArray[seagullID].angle;
                dVar3 = ((double)(sVar4 + -0xb4) * 3.1415926535) / 180.0;
                _newAngle = this->seagullArray[seagullID].someAngle * 20 + sVar4;
                this->seagullArray[seagullID].angle = _newAngle;
                if (360 < _newAngle) {
                    MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                    if ((int)SEC_RNG::instance.currentNumber1 % 5 == 1) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)this->entityArray[_entityID].xPosition,
                            (int)((int)(this->entityArray[_entityID].yPosition)), DE::SHCDE::FX_GULL);
                    }
                    sVar4 = this->seagullArray[seagullID].field12_0x1a;
                    this->seagullArray[seagullID].angle = this->seagullArray[seagullID].angle + -360;
                    if (sVar4 < 0) {
                        this->seagullArray[seagullID].unknownCounter_0x16
                            = this->seagullArray[seagullID].unknownCounter_0x16 + 1;
                    } else if (0 < sVar4) {
                        this->seagullArray[seagullID].unknownCounter_0x16
                            = this->seagullArray[seagullID].unknownCounter_0x16 + -1;
                    }
                    if (this->seagullArray[seagullID].unknownCounter_0x16 < 24) {
                        this->seagullArray[seagullID].unknownCounter_0x16 = 24;
                    }
                    if (80 < this->seagullArray[seagullID].unknownCounter_0x16) {
                        this->seagullArray[seagullID].unknownCounter_0x16 = 80;
                    }
                    this->seagullArray[seagullID].field12_0x1a = sVar4 + 1;
                    if ((short)(sVar4 + 1) >= 0x14) {
                        this->seagullArray[seagullID].field12_0x1a = -0x14;
                    }
                }
                sVar4 = this->seagullArray[seagullID].angle;
                if (sVar4 < 0) {
                    this->seagullArray[seagullID].angle = sVar4 + 0x168;
                    sVar4 = this->seagullArray[seagullID].field12_0x1a;
                    if (sVar4 < 0) {
                        this->seagullArray[seagullID].unknownCounter_0x16
                            = this->seagullArray[seagullID].unknownCounter_0x16 + 1;
                    } else if (0 < sVar4) {
                        this->seagullArray[seagullID].unknownCounter_0x16
                            = this->seagullArray[seagullID].unknownCounter_0x16 + -1;
                    }
                    if (this->seagullArray[seagullID].unknownCounter_0x16 < 0x18) {
                        this->seagullArray[seagullID].unknownCounter_0x16 = 0x18;
                    }
                    if (0x50 < this->seagullArray[seagullID].unknownCounter_0x16) {
                        this->seagullArray[seagullID].unknownCounter_0x16 = 0x50;
                    }
                    this->seagullArray[seagullID].field12_0x1a = sVar4 + 1;
                    if ((short)(sVar4 + 1) >= 0x14) {
                        this->seagullArray[seagullID].field12_0x1a = -0x14;
                    }
                }
                iVar8 = (int)this->seagullArray[seagullID].unknownCounter_0x16;
                fVar10 = sin((double)dVar3);
                _targetXPart2 = (long)(fVar10 * (double)iVar8);
                fVar10 = cos((double)dVar3);
                _targetYPart2 = (long)(fVar10 * (double)iVar8);
                sVar4 = this->seagullArray[seagullID].angle_2;
                sVar5 = this->seagullArray[seagullID].angleStep + sVar4;
                this->seagullArray[seagullID].angle_2 = sVar5;
                fVar10 = ((double)(sVar4 + -0xb4) * (double)3.1415926535) / (double)180.0;
                if (sVar5 >= 0x168) {
                    this->seagullArray[seagullID].angle_2 = sVar5 + -0x168;
                }
                sVar4 = this->seagullArray[seagullID].angle_2;
                if (sVar4 < 0) {
                    this->seagullArray[seagullID].angle_2 = sVar4 + 0x168;
                }
                iVar8 = (int)this->seagullArray[seagullID].numberBetween60And100;
                fVar11 = sin(fVar10);
                iVar6 = (long)(fVar11 * (double)iVar8);
                _targetXPart1 = (short)iVar6 + this->seagullArray[seagullID].x;
                this->seagullArray[seagullID].x_2 = _targetXPart1;
                fVar10 = cos((double)fVar10);
                iVar8 = (long)(fVar10 * (double)iVar8);
                _targetYPart1 = (short)iVar8;
                _targetYPart1 = _targetYPart1 + this->seagullArray[seagullID].y;
                this->seagullArray[seagullID].y_2 = _targetYPart1;
                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::setProjectileTargetPosition, this)(
                    _entityID, (int)((int)(this->entityArray[_entityID].microX)),
                    (int)((int)(this->entityArray[_entityID].microY)),
                    (int)((int)(this->entityArray[_entityID].height)), _targetXPart1 + _targetXPart2,
                    _targetYPart1 + _targetYPart2, (int)((int)(250)));
            }
            sVar4 = this->seagullArray[seagullID].x;
            iVar8 = (int)sVar4;
            uVar7 = iVar8 - this->seagullArray[seagullID].x_3;
            uVar9 = (int)uVar7 >> 0x1f;
            if (((1 < (int)((uVar7 ^ uVar9) - uVar9))
                    || (uVar7 = (int)this->seagullArray[seagullID].y - (int)this->seagullArray[seagullID].y_3,
                        uVar9 = (int)uVar7 >> 0x1f, 1 < (int)((uVar7 ^ uVar9) - uVar9)))
                && (sVar5 = this->seagullArray[seagullID].pathMajorLength, 0 < sVar5)) {
                this->seagullArray[seagullID].pathStepDelay = this->seagullArray[seagullID].pathStepDelay + -1;
                if (this->seagullArray[seagullID].pathStepDelay < 1) {
                    sVar2 = this->seagullArray[seagullID].pathAxisCase;
                    this->seagullArray[seagullID].pathStepDelay = 10;
                    this->seagullArray[seagullID].pathMajorLength = sVar5 + -1;
                    if (sVar2) {
                        if (sVar2 == 2) {
                            this->seagullArray[seagullID].x = this->seagullArray[seagullID].pathStepX + sVar4;
                            return;
                        }
                        if (sVar2 == 1) {
                            this->seagullArray[seagullID].y
                                = this->seagullArray[seagullID].y + this->seagullArray[seagullID].pathStepY;
                            return;
                        }
                        if (sVar2 == 4) {
                            sVar5 = this->seagullArray[seagullID].pathError;
                            if (0 < sVar5) {
                                sVar2 = this->seagullArray[seagullID].pathStepX;
                                this->seagullArray[seagullID].y
                                    = this->seagullArray[seagullID].y + this->seagullArray[seagullID].pathStepY;
                                this->seagullArray[seagullID].x = sVar2 + sVar4;
                                this->seagullArray[seagullID].pathError
                                    = this->seagullArray[seagullID].pathErrorStepDiagonal + sVar5;
                                return;
                            }
                            sVar2 = this->seagullArray[seagullID].pathErrorStepStraight;
                            this->seagullArray[seagullID].x = this->entityArray[_entityID].someMicroX + sVar4;
                            this->seagullArray[seagullID].pathError = sVar2 + sVar5;
                            return;
                        }
                        if (sVar2 == 3) {
                            sVar5 = this->seagullArray[seagullID].pathError;
                            this->seagullArray[seagullID].y
                                = this->seagullArray[seagullID].y + this->seagullArray[seagullID].pathStepY;
                            if (0 < sVar5) {
                                this->seagullArray[seagullID].x = this->seagullArray[seagullID].pathStepX + sVar4;
                                this->seagullArray[seagullID].pathError
                                    = this->seagullArray[seagullID].pathErrorStepDiagonal + sVar5;
                                return;
                            }
                            this->seagullArray[seagullID].pathError
                                = this->seagullArray[seagullID].pathErrorStepStraight + sVar5;
                        }
                    }
                }
                return;
            }
            sVar4 = this->seagullArray[seagullID].rngMax799_countdown;
            if (0 < sVar4) {
                this->seagullArray[seagullID].rngMax799_countdown = sVar4 + -1;
                return;
            }
            _entityID = (int)this->seagullArray[seagullID].y;
            this->seagullArray[seagullID].rngMax799_countdown = SEC_RNG::instance.currentNumber2 % 400 + 400;
            MACRO_CALL_MEMBER(
                Map::Navigation::PathFindingState_Func::findFurthestSeaTile, DAT_PathFindingState::ptr)(
                (int)((((ulonglong)((int)SEC_RNG::instance.currentNumber2 >> 0x1f) << 0x20)
                    | (uint)((uint)((int)((int)SEC_RNG::instance.currentNumber2 >> 4) % 200) + 400))),
                (uint)((int)(iVar8 / 8)), _entityID / 8);
            this->seagullArray[seagullID].x_3 = (short)DAT_PathFindingState::instance.ALG_ResultX * 8;
            sVar4 = this->seagullArray[seagullID].x_3;
            sVar2 = (short)DAT_PathFindingState::instance.ALG_ResultY * 8;
            sVar5 = this->seagullArray[seagullID].x;
            this->seagullArray[seagullID].y_3 = sVar2;
            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::initializeSeagullMovementVector, this)(
                seagullID, (int)((int)(sVar5)), (int)((int)(this->seagullArray[seagullID].y)), (int)((int)(sVar4)),
                (int)((int)(sVar2)));
            this->seagullArray[seagullID].pathStepDelay = 10;
            return;
        }

    }
}
}
