#include "disk.h"

Disk::Disk(float radius, int id, float posX, float posY)
    : _radius(radius), _id(id), _posX(posX), _posY(posY)
{
    _size = std::sqrt(radius);
    _isHidden = false;
}

Disk::Disk(const Disk& d)
    : _radius(d._radius), _id(d._id), _size(d._size), _posX(d._posX), _posY(d._posY), _isHidden(d._isHidden)
{ }

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

int Disk::getId() const
{
    return _id;
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

void Disk::setId(int id)
{
    _id = id;
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
