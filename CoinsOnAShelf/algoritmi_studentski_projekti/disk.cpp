#include "disk.h"

Disk::Disk(float radius) : _radius(radius)
{
    _size = std::sqrt(radius);
    _isHidden = false;
}

bool Disk::operator < (const Disk& other)
{
    return _size < other.getSize();
}

bool Disk::operator > (const Disk& other)
{
    return _size > other.getSize();
}

bool Disk::operator == (const Disk& other)
{
    return _size == other.getSize();
}

float Disk::getRadius() const
{
    return _radius;
}

float Disk::getSize() const
{
    return _size;
}

QPointF& Disk::getPosition()
{
    return _position;
}

bool Disk::getIsHidden() const
{
    return _isHidden;
}

void Disk::setIsHidden(bool isHidden)
{
    _isHidden = isHidden;
}

void Disk::setPosition(QPointF& position)
{
    _position = position;
}

bool Disk::isOvershadowedByOther(const Disk &other)
{
    float g = (std::sqrt(2) - 1) * other.getSize();

    if(_size <= g) {
        _isHidden = true;
        return true;
    }

    return false;
}
