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

    void setPosition(QPointF& position);
    void setIsHidden(bool isHidden);

    bool isOvershadowedByOther(const Disk &other);

    bool operator > (const Disk& other);
    bool operator < (const Disk& other);
    bool operator == (const Disk& other);

private:
    float _radius;
    float _size;
    QPointF _position;

    // indicates if the disk is fully in a gap between other disks
    bool _isHidden;

};

#endif // DISK_H
