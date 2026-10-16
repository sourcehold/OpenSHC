#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519310
        void TroopValueState::computeAttackWaveTroopComposition()
        {
            this->attackInfo.field_0x20f4c = 6;
            if (this->attackInfo.field86974_0x20f74 < 6) {
                this->attackInfo.field_0x20f44 = this->attackInfo.spearmenAndMacemen;
                this->attackInfo.field_0x20f48 = 1;
                this->attackInfo.field_0x20f4c = 1;
                this->attackInfo.field_0x20f54 = 1;
                this->attackInfo.field_0x20f58 = 1;
                this->attackInfo.field_0x20f5c = 0;
                this->attackInfo.field_0x20f40 = 0;
                goto LAB_00519672;
            }
            if (9 < this->attackInfo.field86974_0x20f74) {
                if (this->attackInfo.field86974_0x20f74 < 0x14) {
                    if (this->attackInfo.spearmenAndMacemen < 1) {
                        this->attackInfo.field_0x20f44 = 0;
                    } else if (this->attackInfo.spearmenAndMacemen < 2) {
                        this->attackInfo.field_0x20f44 = 1;
                    } else if (this->attackInfo.spearmenAndMacemen < 4) {
                        this->attackInfo.field_0x20f44 = this->attackInfo.spearmenAndMacemen + -1;
                    } else {
                        this->attackInfo.field_0x20f44 = 3;
                    }
                    this->attackInfo.field_0x20f5c = 4;
                    this->attackInfo.field_0x20f48 = (1 < this->attackInfo.pikemenSwordsmenAndMore) + 2;
                    this->attackInfo.field_0x20f4c = (6 < this->attackInfo.spearmenAndMacemen) + 3;
                    this->attackInfo.field_0x20f54 = (4 < this->attackInfo.pikemenSwordsmenAndMore) + 2;
                    this->attackInfo.field_0x20f58 = (0 < this->attackInfo.pikemenSwordsmenAndMore) + 1;
                    if (this->attackInfo.laddermen < 5) {
                        this->attackInfo.field_0x20f5c = this->attackInfo.laddermen;
                    }
                    this->attackInfo.field_0x20f40 = 1;
                } else if (this->attackInfo.field86974_0x20f74 < 0x1e) {
                    if (this->attackInfo.spearmenAndMacemen < 1) {
                        this->attackInfo.field_0x20f44 = 0;
                    } else if (this->attackInfo.spearmenAndMacemen < 2) {
                        this->attackInfo.field_0x20f44 = 1;
                    } else if (this->attackInfo.spearmenAndMacemen < 4) {
                        this->attackInfo.field_0x20f44 = this->attackInfo.spearmenAndMacemen + -1;
                    } else {
                        this->attackInfo.field_0x20f44 = 3;
                    }
                    this->attackInfo.field_0x20f48 = (uint)(4 < this->attackInfo.pikemenSwordsmenAndMore) * 2 + 2;
                    if (this->attackInfo.spearmenAndMacemen < 0xb) {
                        this->attackInfo.field_0x20f4c = (uint)(5 < this->attackInfo.spearmenAndMacemen) * 2 + 2;
                    }
                    if (this->attackInfo.pikemenSwordsmenAndMore < 9) {
                        this->attackInfo.field_0x20f54 = (uint)(4 < this->attackInfo.pikemenSwordsmenAndMore) * 2 + 2;
                    } else {
                        this->attackInfo.field_0x20f54 = 5;
                    }
                    this->attackInfo.field_0x20f58 = 2;
                    this->attackInfo.field_0x20f5c = 5;
                    if (this->attackInfo.laddermen < 6) {
                        this->attackInfo.field_0x20f5c = this->attackInfo.laddermen;
                    }
                    this->attackInfo.field_0x20f40 = (4 < this->attackInfo.pikemenSwordsmenAndMore) + 1;
                } else {
                    if (this->attackInfo.spearmenAndMacemen < 1) {
                        this->attackInfo.field_0x20f44 = 0;
                    } else if (this->attackInfo.spearmenAndMacemen < 2) {
                        this->attackInfo.field_0x20f44 = 1;
                    } else if (this->attackInfo.spearmenAndMacemen < 5) {
                        this->attackInfo.field_0x20f44 = this->attackInfo.spearmenAndMacemen + -1;
                    } else {
                        this->attackInfo.field_0x20f44 = 4;
                    }
                    this->attackInfo.field_0x20f48 = ((this->attackInfo.pikemenSwordsmenAndMore < 6) - 1 & 3) + 2;
                    if (this->attackInfo.spearmenAndMacemen < 0xd) {
                        this->attackInfo.field_0x20f4c = (uint)(6 < this->attackInfo.spearmenAndMacemen) * 2 + 3;
                    } else {
                        this->attackInfo.field_0x20f4c = 8;
                    }
                    if (this->attackInfo.pikemenSwordsmenAndMore < 0xb) {
                        this->attackInfo.field_0x20f54 = (uint)(8 < this->attackInfo.pikemenSwordsmenAndMore) * 2 + 3;
                    } else {
                        this->attackInfo.field_0x20f54 = 6;
                    }
                    this->attackInfo.field_0x20f5c = 6;
                    this->attackInfo.field_0x20f58 = (0 < this->attackInfo.pikemenSwordsmenAndMore) + 2;
                    if (this->attackInfo.laddermen < 7) {
                        this->attackInfo.field_0x20f5c = this->attackInfo.laddermen;
                    }
                    this->attackInfo.field_0x20f40 = 2;
                }
                goto LAB_00519672;
            }
            if (this->attackInfo.spearmenAndMacemen < 1) {
                this->attackInfo.field_0x20f44 = 0;
            } else if (this->attackInfo.spearmenAndMacemen < 2) {
                this->attackInfo.field_0x20f44 = 1;
            } else if (this->attackInfo.spearmenAndMacemen < 3) {
                this->attackInfo.field_0x20f44 = this->attackInfo.spearmenAndMacemen + -1;
            } else {
                this->attackInfo.field_0x20f44 = 2;
            }
            this->attackInfo.field_0x20f48 = (this->attackInfo.pikemenSwordsmenAndMore) + 1;
            this->attackInfo.field_0x20f4c = (4 < this->attackInfo.spearmenAndMacemen) + 2;
            if (!this->attackInfo.pikemenSwordsmenAndMore) {
                this->attackInfo.field_0x20f54 = 0;
            LAB_005193ed:
                this->attackInfo.field_0x20f58 = 0;
            } else {
                this->attackInfo.field_0x20f54 = 1;
                this->attackInfo.field_0x20f58 = 1;
                if (this->attackInfo.pikemenSwordsmenAndMore < 1)
                    goto LAB_005193ed;
            }
            this->attackInfo.field_0x20f5c = 2;
            if (this->attackInfo.laddermen < 3) {
                this->attackInfo.field_0x20f5c = this->attackInfo.laddermen;
            }
            this->attackInfo.field_0x20f40 = (this->attackInfo.pikemenSwordsmenAndMore);
        LAB_00519672:
            this->attackInfo.field_0x20f50 = this->attackInfo.engineers;
            this->attackInfo.field_0x20f3c = 3;
            if ((int)this->attackInfo.field_0x20f48 < this->attackInfo.field86627_0x20e04) {
                this->attackInfo.field_0x20f48 = this->attackInfo.field86627_0x20e04;
            }
        }

    }
}
}
