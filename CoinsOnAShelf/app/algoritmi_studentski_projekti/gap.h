#ifndef GAP_H
#define GAP_H

#include "disk.h"
class Gap
{
public:
    Gap(Disk *leftDisk, Disk *rightDisk);
    ~Gap() = default;

    Disk* getLeftDisk() const;
    Disk* getRightDisk() const;
    float getSize() const;

    Gap& operator = (const Gap &other);
    friend bool operator < (const Gap &g1, const Gap &g2);
    friend bool operator > (const Gap &g1, const Gap &g2);
    friend bool operator == (const Gap &g1, const Gap &g2);

private:
    Disk* _leftDisk;
    Disk* _rightDisk;
    float _size;

    float calculateSize();
};

#endif // GAP_H
