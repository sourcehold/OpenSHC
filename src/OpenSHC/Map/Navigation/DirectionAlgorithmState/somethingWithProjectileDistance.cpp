#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046CAA0
        void DirectionAlgorithmState::somethingWithProjectileDistance(int x, int y, int targetX, int targetY)
        {
            if (x > targetX) {
                this->distanceX = x - targetX;
            } else {
                this->distanceX = targetX - x;
            }
            if (y > targetY) {
                this->distanceY = y - targetY;
            } else {
                this->distanceY = targetY - y;
            }

            /* minor axis in percent of the major axis (an inlined percentage helper like computeHealthPercentage:
               100 when the major axis is 0) */
            int axisRatioPercent;
            if (this->distanceX >= this->distanceY) {
                int part = this->distanceY;
                int whole = this->distanceX;
                if (whole == 0) {
                    axisRatioPercent = 100;
                } else {
                    axisRatioPercent = part * 100 / whole;
                }
            } else {
                int part = this->distanceX;
                int whole = this->distanceY;
                if (whole == 0) {
                    axisRatioPercent = 100;
                } else {
                    axisRatioPercent = part * 100 / whole;
                }
            }
            if (this->distanceX >= this->distanceY) {
                if (x > targetX) {
                    if (y > targetY) {
                        if (axisRatioPercent <= 25) {
                            this->orientation = 0x48;
                        } else if (axisRatioPercent < 75) {
                            this->orientation = 0x49;
                        } else {
                            this->orientation = 0x4a;
                        }
                    } else {
                        if (axisRatioPercent <= 25) {
                            this->orientation = 0x48;
                        } else if (axisRatioPercent < 75) {
                            this->orientation = 0x47;
                        } else {
                            this->orientation = 0x46;
                        }
                    }
                } else {
                    if (y > targetY) {
                        if (axisRatioPercent <= 25) {
                            this->orientation = 0x40;
                        } else if (axisRatioPercent < 75) {
                            this->orientation = 0x3f;
                        } else {
                            this->orientation = 0x3e;
                        }
                    } else {
                        if (axisRatioPercent <= 25) {
                            this->orientation = 0x40;
                        } else if (axisRatioPercent < 75) {
                            this->orientation = 0x41;
                        } else {
                            this->orientation = 0x42;
                        }
                    }
                }
            } else {
                if (y > targetY) {
                    if (x > targetX) {
                        if (axisRatioPercent <= 25) {
                            this->orientation = 0x3c;
                        } else if (axisRatioPercent < 75) {
                            this->orientation = 0x4b;
                        } else {
                            this->orientation = 0x4a;
                        }
                    } else {
                        if (axisRatioPercent <= 25) {
                            this->orientation = 0x3c;
                        } else if (axisRatioPercent < 75) {
                            this->orientation = 0x3d;
                        } else {
                            this->orientation = 0x3e;
                        }
                    }
                } else {
                    if (x > targetX) {
                        if (axisRatioPercent <= 25) {
                            this->orientation = 0x44;
                        } else if (axisRatioPercent < 75) {
                            this->orientation = 0x45;
                        } else {
                            this->orientation = 0x46;
                        }
                    } else {
                        if (axisRatioPercent <= 25) {
                            this->orientation = 0x44;
                        } else if (axisRatioPercent < 75) {
                            this->orientation = 0x43;
                        } else {
                            this->orientation = 0x42;
                        }
                    }
                }
            }

            if (this->distanceY + this->distanceX <= 0) {
                this->orientation = 0x4c;
            }
        }

    }
}
}
