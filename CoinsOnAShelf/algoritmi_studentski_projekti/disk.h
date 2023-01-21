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

    const Disk& operator = (const Disk&);
    bool operator > (const Disk&);
    bool operator < (const Disk&);
    bool operator == (const Disk&);

private:
    float _radius;
    float _size;
    QPointF _position;

    // indicates if the disk is fully in a gap between other disks
    bool _isHidden;

};

#endif // DISK_H
