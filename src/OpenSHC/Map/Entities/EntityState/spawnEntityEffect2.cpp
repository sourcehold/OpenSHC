#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004082A0
        uint EntityState::spawnEntityEffect2(
            undefined4 microX, undefined4 microY, undefined4 height, undefined4 entityType, int gmLookupValue)
        {
            int entityID;
            for (entityID = this->everyTenTicks; entityID < countof(this->entityArray); entityID++) {
                if (this->entityArray[entityID].logicalState == 0) {
                    break;
                }
                if (entityID >= countof(this->entityArray) - 1) {
                    return 0;
                }
            }
            if (entityID >= (int)this->maxEntityCount) {
                this->maxEntityCount = entityID + 1;
            }
            this->everyTenTicks = entityID;
            this->entityArray[entityID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
            DAT_GameCore::instance.uniqueGameObjectTracker++;
            this->entityArray[entityID].field_0x34 = DAT_GameCore::instance.mapTimeInTicks;
            this->entityArray[entityID].microX = (short)microX;
            this->entityArray[entityID].microY = (short)microY;
            this->entityArray[entityID].height = (short)height;
            this->entityArray[entityID].logicalState = 5;
            this->entityArray[entityID].colorUnk = 0;
            MACRO_CALL_MEMBER(EntityState_Func::setEntityParameters, this)(entityID, entityType, gmLookupValue);
            this->entityArray[entityID].field_0x12 = 0;
            this->entityArray[entityID].unknownAnimationFrameRelated = 0;
            this->entityArray[entityID].unkMinusOne = 0;
            MACRO_CALL_MEMBER(EntityState_Func::processEntityHitBuildingOrUnit, this)(entityID);
            MACRO_CALL_MEMBER(EntityState_Func::calculateEntityDrawOffset, this)(entityID);
            uint const savedCurrentEntityID = DAT_CurrentEntityID::instance;
            DAT_CurrentEntityID::instance = entityID;
            ((void(
                __cdecl*)())DAT_EntityDefinedData::instance.EntityCallbacks[this->entityArray[entityID].entityType])();
            DAT_CurrentEntityID::instance = savedCurrentEntityID;
            return entityID;
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
