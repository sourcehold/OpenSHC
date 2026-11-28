#include "../../../Map.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using DE::SHCDE::eSFX;
        using Map::Entities::EntityType;
        using WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000      Note that Ghidra is bad at x87 extended precision
          instructions.   This function likely does:      float dx = vCos * speed * 0.25f;   float dy = vSin * speed *
          0.25f;      float t = vSin - gravityAccum;      float slope =       (height - (4.906f * t - t * t * velocity))
          /       (distance - dx * t);      float angle = atan(slope) * 180.0f / PI;
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004084A0
        BOOLEnum EntityState::moveProjectileEntity(int entityID)
        {
            short* psVar1;
            short sVar2;
            EntityTypeShort EVar3;
            short sVar4;
            int _dx;
            int iVar5;
            int iVar6;
            int _height;
            double _vSin;
            double _dxRaw;
            double _gravityConstantDiv2;
            double _gravConstant_2;
            double extraout_ST0;
            double fVar7;
            double extraout_ST1;
            double extraout_ST1_00;
            double fVar8;
            int iVar9;
            int local_10;
            float _vCos;
            float _speed;
            float _accum_2;
            int _entityID;
            float _speed_2;
            _entityID = entityID;
            _speed = (float)this->entityArray[entityID].speedUnk;
            _vCos = this->entityArray[entityID].vCos;
            _vSin = (double)this->entityArray[entityID].vSin;
            _height = (int)this->entityArray[entityID].height - (int)this->entityArray[entityID].startingHeight;
            local_10 = 0;
            if (this->entityArray[entityID].someCounter_OR_hitGround != 0) {
                return FALSE;
            }
            if (this->entityArray[entityID].pathAxisCase == 0) {
                this->entityArray[entityID].someCounter_OR_hitGround = 0x28;
            }
            _dxRaw = (double)_vCos * (double)_speed;
            /*
              9.812 / 2 (gravity!)
             */
            _gravityConstantDiv2 = (double)4.906;
            _dx = (long)(_dxRaw * (double)0.25);
            fVar7 = extraout_ST1;
            iVar5 = (long)(_gravConstant_2 + _gravConstant_2);
            if ((double)0 == _vSin) {
                fVar7 = (double)(int)this->entityArray[entityID].startingAngle;
            } else {
                fVar8 = _vSin - (double)this->entityArray[entityID]._elapsedTimeOrGravityAccumulator;
                fVar7 = atan(((extraout_ST0 - (_gravityConstantDiv2 * fVar8 - fVar8 * fVar8 * extraout_ST1_00))
                                 / (fVar7 - _dxRaw * fVar8))
                    * (double)3.0);
                fVar7 = (fVar7 * (double)180.0) / (double)3.1415926535;
            }
            iVar6 = (long)(fVar7);
            _accum_2 = this->entityArray[entityID]._elapsedTimeOrGravityAccumulator;
            _speed_2 = (float)this->entityArray[entityID].speedUnk;
            this->entityArray[entityID].graphicRotationUnk = (word)iVar6;
            iVar6 = _dx - this->entityArray[entityID].travelledDistance;
            this->entityArray[entityID].speedUnk = (int)(_accum_2 + _speed_2);
            if (iVar6) {
                local_10 = (iVar5 - _height) / iVar6;
            }
            sVar2 = this->entityArray[entityID].travelledDistance;
            while (sVar2 < _dx) {
                psVar1 = &this->entityArray[entityID].travelledDistance;
                *psVar1 = *psVar1 + 1;
                psVar1 = &this->entityArray[entityID].clearanceStepsRemaining;
                *psVar1 = *psVar1 + -1;
                if (entityID) {
                    MACRO_CALL_MEMBER(
                        Map::Entities::EntityState_Func::doSomethingWithOtherEntitiesOnTile, this)(entityID);
                }
                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::updateEntityMicroMovement, this)(entityID);
                if ((DAT_EntityDefinedData::instance
                            .EntityArrayCurveTypeForProjectileType[(short)this->entityArray[entityID].entityType]
                        != 9)
                    && (DAT_EntityDefinedData::instance
                            .EntityArrayCurveTypeForProjectileType[(short)this->entityArray[entityID].entityType]
                        != 10)) {
                    _height = _height + local_10;
                    iVar9 = 1;
                    iVar6 = (long)((double)fVar7);
                    MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::updateProjectileHeightAndCollision,
                        this)(entityID, (undefined4)((int)(_height)), iVar6, iVar9);
                }
                iVar6 = MACRO_CALL_MEMBER(
                    Map::Entities::EntityState_Func::processEntityHitBuildingOrUnit, this)(entityID);
                if (!iVar6) {
                    MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::calculateEntityDrawOffset, this)(
                        entityID);
                    return TRUE;
                }
                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::calculateEntityDrawOffset, this)(entityID);
                if (this->entityArray[entityID].someCounter_OR_hitGround != 0)
                    break;
                sVar2 = this->entityArray[entityID].travelledDistance;
            }
            EVar3 = this->entityArray[entityID].entityType;
            (*(short*)&entityID) = (short)_dx;
            this->entityArray[_entityID].travelledDistance = (short)entityID;
            if (DAT_EntityDefinedData::instance.EntityArrayCurveTypeForProjectileType[(short)EVar3] == 9) {
                sVar2 = this->entityArray[_entityID].height;
                sVar4 = this->entityArray[_entityID].targetZ;
                if (sVar2 < sVar4) {
                    this->entityArray[_entityID].height = sVar2 + 1;
                    return TRUE;
                }
                if ((sVar4 < sVar2) && (this->entityArray[_entityID].height = sVar2 + -8, (short)(sVar2 + -8) < 1)) {
                    iVar5 = (int)this->entityArray[_entityID].microY;
                    iVar6 = (int)this->entityArray[_entityID].microX;
                    this->entityArray[_entityID].someMicroY = 0;
                    this->entityArray[_entityID].someMicroX = 0;
                    this->entityArray[_entityID].height = 0;
                    MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity, this)(
                        0, 0, 0, iVar6, iVar5, 0, iVar6, iVar5, 0, ((EntityType)0x1f), 0);
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)this->entityArray[_entityID].xPosition,
                        (int)((int)(this->entityArray[_entityID].yPosition)), DE::SHCDE::FX_GULL_DIVE);
                    return TRUE;
                }
            } else {
                if (DAT_EntityDefinedData::instance.EntityArrayCurveTypeForProjectileType[(short)EVar3] == 10) {
                    psVar1 = &this->entityArray[_entityID].height;
                    *psVar1 = *psVar1 + 1;
                    return TRUE;
                }
                iVar9 = 0;
                iVar6 = (long)((double)fVar7);
                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::updateProjectileHeightAndCollision, this)(
                    _entityID, (undefined4)((int)(iVar5)), iVar6, iVar9);
            }
            return TRUE;
        }

    }
}
}
