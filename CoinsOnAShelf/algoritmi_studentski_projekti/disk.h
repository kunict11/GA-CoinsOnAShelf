#ifndef DISK_H
#define DISK_H

#include <QPointF>

class Disk
{
public:
    Disk(float radius);

    float getRadius() const;
    float getSize() const;
    QPointF& getPosition();
    bool getIsHidden() const;

    void setPosition(QPointF&);
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
    QPointF _position;

    // indicates if the disk is fully in a gap between other disks
    bool _isHidden;

};

#endif // DISK_H
