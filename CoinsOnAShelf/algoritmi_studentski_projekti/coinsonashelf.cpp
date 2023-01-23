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
        radiuses = generateRandomRadiuses(brojTacaka);
        qDebug() << "First disk radius " << radiuses.at(0);

    }

    for (float r : radiuses) {
        _disks.push_back(Disk(r));
        _disksNaive.push_back(Disk(r));
    }

    calculatePositions();

    qDebug() << "First disk size " << _disks.at(0).getSize();

}

void CoinsOnAShelf::pokreniAlgoritam()
{
    std::sort(std::begin(_disks), std::end(_disks), std::greater_equal<Disk>());
    calculatePositions();
    updateCanvasAndBlock();
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

void CoinsOnAShelf::crtajAlgoritam(QPainter *painter) const
{
    if(!painter)
        return;

    auto pen = painter->pen();
    pen.setColor(Qt::blue);
    painter->setPen(pen);

    painter->fillRect(10, 50, _pCrtanje->width()-20, 10, Qt::blue);



    for(const auto &disk : _disks) {
        painter->drawEllipse(QPointF(disk.getPosX(), disk.getPosY()), disk.getRadius(), disk.getRadius());
    }



}

void CoinsOnAShelf::crtajNaivniAlgoritam(QPainter*) const {}


std::deque<float> CoinsOnAShelf::generateRandomRadiuses(int numDisks) const
{
    std::deque<float> radiuses;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(MIN_RADIUS, MAX_RADIUS);

    for (int i=0; i<numDisks; ++i) {
        float r = dis(gen);
        qDebug() << "Random no" << i << ": " << r;
        radiuses.push_back(r);
    }

    return radiuses;
}

void CoinsOnAShelf::calculatePositions()
{
    int canvasWidth = _pCrtanje->width();
    int canvasHeight = _pCrtanje->height();

    qDebug() << "Width: " << canvasWidth << " Height: " << canvasHeight;

    float currentX = 10.0;
    float currentY = canvasHeight - 10.0;
    float currentMaxRadius = 0.0;

    for(auto &disk : _disks)
    {
        if (currentX + 2*disk.getRadius() > canvasWidth) {
            currentY -= 2*currentMaxRadius + 10.0;
            currentX = 10.0;
        }

        currentX += disk.getRadius();
        disk.setPosX(currentX);
        disk.setPosY(currentY - disk.getRadius());

        qDebug() << "Radius: " << disk.getRadius() << " x: " << disk.getPosX() << " y: " << disk.getPosY();

        if (disk.getRadius() > currentMaxRadius)
            currentMaxRadius = disk.getRadius();

        currentX += disk.getRadius();
    }
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
