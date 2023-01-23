#include "coinsonashelf.h"

#include <algorithm>
#include <random>
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
        radiuses = generateRandomRadiuses(12);
        qDebug() << "First disk radius " << radiuses.at(0);

    }

    for (float r : radiuses) {
        _disks.push_back(Disk(r));
        _disksNaive.push_back(Disk(r));
    }

    qDebug() << "First disk size " << _disks.at(0).getSize();

}

void CoinsOnAShelf::pokreniAlgoritam()
{
    std::sort(std::begin(_disks), std::end(_disks), std::greater_equal<Disk>());
    _spanLength = 0;

    qDebug() << "Largest disk size " << _disks.front().getSize();
    qDebug() << "Num disks " << _disks.size();

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

    std::sort(std::begin(_disksNaive), std::end(_disksNaive), std::less<Disk>());

    qDebug() << "Largest disk size " << _disksNaive.front().getSize();
    qDebug() << "Num disks " << _disksNaive.size();

    int n = _disksNaive.size();
    float currentMin = (float)INT_MAX;

    do {
        float currentResult = _disksNaive.front().getRadius() + _disksNaive.back().getRadius();

        for (int i=0; i<n-1; ++i) {
            currentResult += footpointDistance(_disksNaive.at(i), _disksNaive.at(i+1));
        }

        if(currentResult < currentMin)
            currentMin = currentResult;

    } while(std::next_permutation(std::begin(_disksNaive), std::end(_disksNaive)));

    _spanLengthNaive = currentMin;
    qDebug() << "Min result: " << _spanLengthNaive;
}

void CoinsOnAShelf::crtajAlgoritam(QPainter*) const {}

void CoinsOnAShelf::crtajNaivniAlgoritam(QPainter*) const {}


std::deque<float> CoinsOnAShelf::generateRandomRadiuses(int numDisks) const
{
    std::deque<float> radiuses;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(MIN_RADIUS, MAX_RADIUS);

    for (int i=0; i<numDisks; ++i) {
//        float r = (float)rand() * (MAX_RADIUS - MIN_RADIUS) / (float)RAND_MAX + MIN_RADIUS;
        float r = dis(gen);
        qDebug() << "Random no" << i << ": " << r;
        radiuses.push_back(r);
    }

    return radiuses;
}

float CoinsOnAShelf::gapSize(const Disk &d1, const Disk &d2)
{
    float tmp = 1/d1.getSize() + 1/d2.getSize();

    return 1/tmp;
}

float CoinsOnAShelf::footpointDistance(const Disk &d1, const Disk &d2)
{
    return 2*d1.getSize()*d2.getSize();
}
