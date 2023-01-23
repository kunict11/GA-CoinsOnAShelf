#ifndef DISK_H
#define DISK_H

#include <QPointF>

class Disk
{
public:
    Disk(float radius, float posX = 0.0, float posY = 0.0);

    float getRadius() const;
    float getSize() const;
    float getPosX() const;
    float getPosY() const;
    bool getIsHidden() const;

    void setPosX(float x);
    void setPosY(float y);
    void setIsHidden(bool);

    bool isOvershadowedByOther(const Disk&);

    Disk& operator = (const Disk&);
    friend bool operator > (const Disk &d1, const Disk &d2);
    friend bool operator >= (const Disk &d1, const Disk &d2);
    friend bool operator < (const Disk &d1, const Disk &d2);
    friend bool operator == (const Disk &d1, const Disk &d2);

private:
    float _radius;
    float _size;
    float _posX;
    float _posY;

    // indicates if the disk is fully in a gap between other disks
    bool _isHidden;

};

#endif // DISK_H
