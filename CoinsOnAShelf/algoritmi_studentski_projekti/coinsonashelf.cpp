#include "coinsonashelf.h"

#include <algorithm>
#include <QDebug>

CoinsOnAShelf::CoinsOnAShelf(QWidget *pCrtanje,
                             int pauzaKoraka,
                             const bool &naivni,
                             std::string imeDatoteke,
                             int brojTacaka)
    :AlgoritamBaza(pCrtanje, pauzaKoraka, naivni)
{
    std::deque<float> radiuses;

    if (imeDatoteke == "") {
        radiuses = generateRandomRadiuses(brojTacaka);
        qDebug() << "First disk radius " << radiuses.at(0);
    }

    for (float r : radiuses) {
        _disks.push_back(Disk(r));
    }

    qDebug() << "First disk size " << _disks.at(0).getSize();

}

std::deque<float> CoinsOnAShelf::generateRandomRadiuses(int numDisks) const
{
    std::deque<float> radiuses;
    for (int i=0; i<numDisks; ++i) {
        float r = (rand() / (float)RAND_MAX) * (MAX_RADIUS - MIN_RADIUS) + MIN_RADIUS;
        radiuses.push_back(r);
    }

    return radiuses;
}

void CoinsOnAShelf::pokreniAlgoritam()
{
    std::sort(_disks.begin(), _disks.end(), std::greater<Disk&>());

    Disk &d1 = _disks.at(0);
    Disk &d2 = _disks.at(1);
    _ordering.push_back(d1);
    _ordering.push_back(d2);
    _gapSizes.push(Gap(d1, d2));
    _disks.pop_front();
    _disks.pop_front();

    _spanLength = d1.getRadius() + footpointDistance(d1, d2) + d2.getRadius();

    for(auto& disk : _disks)
    {
        // the size of the current disk is larger than the largest gap
        if (_gapSizes.top().getSize() < disk.getSize()) {
            Disk &d1 = _ordering.front();
            Disk &d2 = _ordering.back();

            float newSpanLengthLeft = _spanLength;
            bool placingLeftIncreasesSpanLength = false;

            float newSpanLengthRight = _spanLength;
            bool placingRightIncreasesSpanLength = false;

            if(!disk.isOvershadowedByOther(d1)) {
                newSpanLengthLeft = _spanLength - d1.getRadius() + footpointDistance(d1, disk) + disk.getRadius();
                placingLeftIncreasesSpanLength = true;
            }
            if(!disk.isOvershadowedByOther(d2)) {
                newSpanLengthRight = _spanLength - d2.getRadius() + footpointDistance(d2, disk) + disk.getRadius();
                placingRightIncreasesSpanLength = true;
            }

            if (newSpanLengthLeft < newSpanLengthRight) {
                if(placingLeftIncreasesSpanLength) {
                   _spanLength = newSpanLengthLeft;
                   _ordering.push_front(disk);
                }
                _gapSizes.push(Gap(d1, disk));
            }

            else {
                if (placingRightIncreasesSpanLength) {
                    _spanLength = newSpanLengthRight;
                    _ordering.push_back(disk);
                }
                _gapSizes.push(Gap(disk, d2));
            }
        }
        else {
            Disk& leftDisk = _gapSizes.top().getLeftDisk();
            Disk& rightDisk = _gapSizes.top().getRightDisk();
            _gapSizes.push(Gap(leftDisk, disk));
            _gapSizes.push(Gap(disk, rightDisk));
            _gapSizes.pop();
            // the span won't increase because the inserted disk is fully hidden between the two disks
            disk.setIsHidden(true);
        }

    }

    qDebug() << _spanLength;
}

void CoinsOnAShelf::pokreniNaivniAlgoritam()
{

}

void CoinsOnAShelf::crtajAlgoritam(QPainter*) const {}

void CoinsOnAShelf::crtajNaivniAlgoritam(QPainter*) const {}

float CoinsOnAShelf::gapSize(const Disk &d1, const Disk &d2)
{
    float tmp = 1/d1.getSize() + 1/d2.getSize();

    return 1/tmp;
}

float CoinsOnAShelf::footpointDistance(const Disk &d1, const Disk &d2)
{
    return 2*d1.getSize()*d2.getSize();
}
