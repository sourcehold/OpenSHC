#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519310
        void TroopValueState::computeAttackWaveTroopComposition()
        {
            this->attackInfo.maxMoatAttackTribes = 6;
            if (this->attackInfo.attackTribeCount < 6) {
                this->attackInfo.maxWallScaleTribes = this->attackInfo.spearmenAndMacemen;
                this->attackInfo.maxTownAttackTribes = 1;
                this->attackInfo.maxMoatAttackTribes = 1;
                this->attackInfo.maxPeopleAttackTribes = 1;
                this->attackInfo.maxGateAttackTribes = 1;
                this->attackInfo.maxLadderTribes = 0;
                this->attackInfo.maxTunnelerTribes = 0;
                goto LAB_00519672;
            }
            if (9 < this->attackInfo.attackTribeCount) {
                if (this->attackInfo.attackTribeCount < 0x14) {
                    if (this->attackInfo.spearmenAndMacemen < 1) {
                        this->attackInfo.maxWallScaleTribes = 0;
                    } else if (this->attackInfo.spearmenAndMacemen < 2) {
                        this->attackInfo.maxWallScaleTribes = 1;
                    } else if (this->attackInfo.spearmenAndMacemen < 4) {
                        this->attackInfo.maxWallScaleTribes = this->attackInfo.spearmenAndMacemen + -1;
                    } else {
                        this->attackInfo.maxWallScaleTribes = 3;
                    }
                    this->attackInfo.maxLadderTribes = 4;
                    this->attackInfo.maxTownAttackTribes = (1 < this->attackInfo.pikemenSwordsmenAndMore) + 2;
                    this->attackInfo.maxMoatAttackTribes = (6 < this->attackInfo.spearmenAndMacemen) + 3;
                    this->attackInfo.maxPeopleAttackTribes = (4 < this->attackInfo.pikemenSwordsmenAndMore) + 2;
                    this->attackInfo.maxGateAttackTribes = (0 < this->attackInfo.pikemenSwordsmenAndMore) + 1;
                    if (this->attackInfo.laddermen < 5) {
                        this->attackInfo.maxLadderTribes = this->attackInfo.laddermen;
                    }
                    this->attackInfo.maxTunnelerTribes = 1;
                } else if (this->attackInfo.attackTribeCount < 0x1e) {
                    if (this->attackInfo.spearmenAndMacemen < 1) {
                        this->attackInfo.maxWallScaleTribes = 0;
                    } else if (this->attackInfo.spearmenAndMacemen < 2) {
                        this->attackInfo.maxWallScaleTribes = 1;
                    } else if (this->attackInfo.spearmenAndMacemen < 4) {
                        this->attackInfo.maxWallScaleTribes = this->attackInfo.spearmenAndMacemen + -1;
                    } else {
                        this->attackInfo.maxWallScaleTribes = 3;
                    }
                    this->attackInfo.maxTownAttackTribes = (uint)(4 < this->attackInfo.pikemenSwordsmenAndMore) * 2 + 2;
                    if (this->attackInfo.spearmenAndMacemen < 0xb) {
                        this->attackInfo.maxMoatAttackTribes = (uint)(5 < this->attackInfo.spearmenAndMacemen) * 2 + 2;
                    }
                    if (this->attackInfo.pikemenSwordsmenAndMore < 9) {
                        this->attackInfo.maxPeopleAttackTribes = (uint)(4 < this->attackInfo.pikemenSwordsmenAndMore) * 2 + 2;
                    } else {
                        this->attackInfo.maxPeopleAttackTribes = 5;
                    }
                    this->attackInfo.maxGateAttackTribes = 2;
                    this->attackInfo.maxLadderTribes = 5;
                    if (this->attackInfo.laddermen < 6) {
                        this->attackInfo.maxLadderTribes = this->attackInfo.laddermen;
                    }
                    this->attackInfo.maxTunnelerTribes = (4 < this->attackInfo.pikemenSwordsmenAndMore) + 1;
                } else {
                    if (this->attackInfo.spearmenAndMacemen < 1) {
                        this->attackInfo.maxWallScaleTribes = 0;
                    } else if (this->attackInfo.spearmenAndMacemen < 2) {
                        this->attackInfo.maxWallScaleTribes = 1;
                    } else if (this->attackInfo.spearmenAndMacemen < 5) {
                        this->attackInfo.maxWallScaleTribes = this->attackInfo.spearmenAndMacemen + -1;
                    } else {
                        this->attackInfo.maxWallScaleTribes = 4;
                    }
                    this->attackInfo.maxTownAttackTribes = ((this->attackInfo.pikemenSwordsmenAndMore < 6) - 1 & 3) + 2;
                    if (this->attackInfo.spearmenAndMacemen < 0xd) {
                        this->attackInfo.maxMoatAttackTribes = (uint)(6 < this->attackInfo.spearmenAndMacemen) * 2 + 3;
                    } else {
                        this->attackInfo.maxMoatAttackTribes = 8;
                    }
                    if (this->attackInfo.pikemenSwordsmenAndMore < 0xb) {
                        this->attackInfo.maxPeopleAttackTribes = (uint)(8 < this->attackInfo.pikemenSwordsmenAndMore) * 2 + 3;
                    } else {
                        this->attackInfo.maxPeopleAttackTribes = 6;
                    }
                    this->attackInfo.maxLadderTribes = 6;
                    this->attackInfo.maxGateAttackTribes = (0 < this->attackInfo.pikemenSwordsmenAndMore) + 2;
                    if (this->attackInfo.laddermen < 7) {
                        this->attackInfo.maxLadderTribes = this->attackInfo.laddermen;
                    }
                    this->attackInfo.maxTunnelerTribes = 2;
                }
                goto LAB_00519672;
            }
            if (this->attackInfo.spearmenAndMacemen < 1) {
                this->attackInfo.maxWallScaleTribes = 0;
            } else if (this->attackInfo.spearmenAndMacemen < 2) {
                this->attackInfo.maxWallScaleTribes = 1;
            } else if (this->attackInfo.spearmenAndMacemen < 3) {
                this->attackInfo.maxWallScaleTribes = this->attackInfo.spearmenAndMacemen + -1;
            } else {
                this->attackInfo.maxWallScaleTribes = 2;
            }
            this->attackInfo.maxTownAttackTribes = (this->attackInfo.pikemenSwordsmenAndMore) + 1;
            this->attackInfo.maxMoatAttackTribes = (4 < this->attackInfo.spearmenAndMacemen) + 2;
            if (!this->attackInfo.pikemenSwordsmenAndMore) {
                this->attackInfo.maxPeopleAttackTribes = 0;
            LAB_005193ed:
                this->attackInfo.maxGateAttackTribes = 0;
            } else {
                this->attackInfo.maxPeopleAttackTribes = 1;
                this->attackInfo.maxGateAttackTribes = 1;
                if (this->attackInfo.pikemenSwordsmenAndMore < 1)
                    goto LAB_005193ed;
            }
            this->attackInfo.maxLadderTribes = 2;
            if (this->attackInfo.laddermen < 3) {
                this->attackInfo.maxLadderTribes = this->attackInfo.laddermen;
            }
            this->attackInfo.maxTunnelerTribes = (this->attackInfo.pikemenSwordsmenAndMore);
        LAB_00519672:
            this->attackInfo.maxEngineerTribes = this->attackInfo.engineers;
            this->attackInfo.maxLordAttackTribes = 3;
            if ((int)this->attackInfo.maxTownAttackTribes < this->attackInfo.assassinTribeCount) {
                this->attackInfo.maxTownAttackTribes = this->attackInfo.assassinTribeCount;
            }
        }

    }
}
}
