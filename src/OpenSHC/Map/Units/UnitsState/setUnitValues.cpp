#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053B8E0
        void UnitsState::setUnitValues(int unitID, UnitType unitType)
        {
            this->units[unitID].unitType = (UnitTypeShort)unitType;
            this->units[unitID].field64_0x90 = (short)DAT_UnitPropertiesDefinedData::instance.field65_0x7634[unitType];
            this->units[unitID].isStalked = (byte)DAT_UnitPropertiesDefinedData::instance.field66_0x7774[unitType];
            this->units[unitID].gmIDUnk = (short)DAT_UnitPropertiesDefinedData::instance.SPRITE_ID[unitType];
            this->units[unitID].spriteID = (short)DAT_UnitPropertiesDefinedData::instance.SPRITE_ID[unitType];
            this->units[unitID].gfxNumber = 1;
            this->units[unitID].field22_0x2a = (short)DAT_TextureRenderCoreObject::instance
                                                   .gmFileHeaderColorpaletteArray[this->units[unitID].spriteID]
                                                   .originX;
            *(short*)&this->units[unitID].unknownV = (short)DAT_TextureRenderCoreObject::instance
                                                         .gmFileHeaderColorpaletteArray[this->units[unitID].spriteID]
                                                         .originY;
            this->units[unitID].spriteWidthUnk
                = (short)DAT_UnitPropertiesDefinedData::instance.UNIT_SPRITE_DIMENSIONS[unitType][0];
            this->units[unitID].spriteHeightUnk
                = (short)DAT_UnitPropertiesDefinedData::instance.UNIT_SPRITE_DIMENSIONS[unitType][1];
            this->units[unitID].drawXOffset = this->units[unitID].field22_0x2a - this->units[unitID].spriteWidthUnk / 2;
            this->units[unitID].someDrawYOffset
                = ((short)this->units[unitID].unknownV - this->units[unitID].spriteHeightUnk) + 3;
            this->units[unitID].movementSpeed
                = (short)DAT_UnitPropertiesDefinedData::instance.UNIT_MOVEMENT_SPEED_ARRAY[unitType];
            this->units[unitID].calculatedMovementSpeed = this->units[unitID].movementSpeed;
            this->units[unitID].field200_0x354 = 0;
            this->units[unitID].field199_0x350 = 0;
            this->units[unitID].maxHealth = DAT_UnitPropertiesDefinedData::instance.BASE_HP[unitType];
            this->units[unitID].health = this->units[unitID].maxHealth;
            if (this->units[unitID].maxHealth == 0) {
                this->units[unitID].healthPercentage = 100;
            } else {
                this->units[unitID].healthPercentage
                    = (short)((this->units[unitID].health * 100) / this->units[unitID].maxHealth);
            }
            byte _firstNameIndex = this->units[unitID].firstNameIndex;
            this->units[unitID].healthbar = this->units[unitID].healthPercentage / 10;
            this->units[unitID].unitCanClimb = (short)DAT_UnitPropertiesDefinedData::instance.UNIT_CLIMB[unitType];
            this->units[unitID].someUnitStat4
                = (short)DAT_UnitPropertiesDefinedData::instance.SomeUnitStatMatrix4[unitType];
            this->units[unitID].graphicSize = (short)DAT_UnitPropertiesDefinedData::instance.GRAPHIC_SIZE[unitType];
            this->units[unitID].someUnitStat2_meleeDamageUnk
                = (short)DAT_UnitPropertiesDefinedData::instance.UNIT_CAN_MELEE[unitType];
            this->units[unitID].enemyNoticeFrequencyUnk
                = DAT_UnitPropertiesDefinedData::instance.UNIT_ENEMY_NOTICE_RANGE[unitType];
            this->units[unitID].moveableUnk = (short)DAT_UnitPropertiesDefinedData::instance.UNIT_MOVABLE[unitType];
            if ((char)_firstNameIndex < '\x01' || unitType == OpenSHC::Map::Units::UT_BREWER
                || unitType == OpenSHC::Map::Units::UT_TANNER || unitType == OpenSHC::Map::Units::UT_LADY
                || unitType == OpenSHC::Map::Units::UT_MOTHER || unitType == OpenSHC::Map::Units::UT_JUGGLER
                || unitType == OpenSHC::Map::Units::UT_FIREEATER || unitType == OpenSHC::Map::Units::UT_PRIEST) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignNameToUnit, this)(unitID);
            }
            if (this->units[unitID].owner <= 0) {
                this->units[unitID].occupancyOrFlag = 0xff;
                this->units[unitID].field258_0x3d1 = 0xff;
            } else {
                this->units[unitID].occupancyOrFlag = '\x01' << ((char)this->units[unitID].owner - 1U & 0x1f);
                this->units[unitID].field258_0x3d1 = ~this->units[unitID].occupancyOrFlag;
            }
            this->units[unitID].isSelectable_OR_matchTime = 0;
            this->units[unitID].field316_0x430 = 0;
            if (unitType != OpenSHC::Map::Units::UT_CAGEDOG) {
                this->units[unitID].unknownBool01 = 500;
            }
            if (unitType == OpenSHC::Map::Units::UT_A_ASSASSIN) {
                this->units[unitID].assassinsMicroDistanceToEnemyUnk = 32000;
            }
        }

    }
}
}
