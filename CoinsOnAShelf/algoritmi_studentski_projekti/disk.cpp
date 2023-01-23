#include "disk.h"

Disk::Disk(float radius, float posX, float posY)
    : _radius(radius), _posX(posX), _posY(posY)
{
    _size = std::sqrt(radius);
    _isHidden = false;
}

Disk& Disk::operator = (const Disk& other)
{
    _radius = other._radius;
    _size = other._size;
    _isHidden = other._isHidden;
    _posX = other._posX;
    _posY = other._posY;

    return *this;
}

bool operator < (const Disk &d1, const Disk &d2)
{
    return d1._size < d2._size;
}

bool operator > (const Disk &d1, const Disk &d2)
{
    return d1._size > d2._size;
}

bool operator >= (const Disk &d1, const Disk &d2)
{
    return d1._size >= d2._size;
}

bool operator == (const Disk &d1, const Disk &d2)
{
    return d1._size == d2._size;
}

float Disk::getRadius() const
{
    return _radius;
}

float Disk::getSize() const
{
    return _size;
}

float Disk::getPosX() const
{
    return _posX;
}

float Disk::getPosY() const
{
    return _posY;
}

bool Disk::getIsHidden() const
{
    return _isHidden;
}

void Disk::setIsHidden(bool isHidden)
{
    _isHidden = isHidden;
}

void Disk::setPosX(float posX)
{
    _posX = posX;
}

void Disk::setPosY(float posY)
{
    _posY = posY;
}

bool Disk::isOvershadowedByOther(const Disk& other)
{
    float g = (std::sqrt(2) - 1) * other.getSize();

    if(_size <= g) {
        _isHidden = true;
        return true;
    }

    return false;
}
