#include "gap.h"

Gap::Gap(Disk *d1, Disk *d2)
    : _leftDisk(d1), _rightDisk(d2)
{
    _size = calculateSize();
}

Disk* Gap::getLeftDisk() const
{
    return _leftDisk;
}

Disk* Gap::getRightDisk() const
{
    return _rightDisk;
}

Gap& Gap::operator = (const Gap &other)
{
    _leftDisk = other._leftDisk;
    _rightDisk = other._rightDisk;
    _size = other._size;

    return *this;
}

bool operator < (const Gap &g1, const Gap &g2)
{
    return g1._size < g2._size;
}

bool operator > (const Gap &g1, const Gap &g2)
{
    return g1._size > g2._size;
}

bool operator == (const Gap &g1, const Gap &g2)
{
    return g1._size == g2._size;
}

float Gap::getSize() const
{
    return _size;
}

float Gap::calculateSize()
{
    float tmp = 1/_leftDisk->getSize() + 1/_rightDisk->getSize();

    return 1/tmp;
}
