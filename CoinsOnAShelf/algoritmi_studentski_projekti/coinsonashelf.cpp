#include "coinsonashelf.h"

#include <algorithm>
#include <random>
#include <QDebug>
#include <fstream>

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

    }
    else {

        std::ifstream datoteka(imeDatoteke);

        float r;
        while(datoteka >> r) {
            radiuses.push_back(r);
        }
    }

    int i = 0;
    for (float r : radiuses) {
        _disks.push_back(Disk{r, i});
        _disksNaive.push_back(Disk{r, i});
        i+=1;
    }
#ifndef COINS_ON_A_SHELF_BENCHMARK
    calculatePositions(_disks);
    calculatePositions(_disksNaive);
#endif


}

void CoinsOnAShelf::pokreniAlgoritam()
{
    std::sort(std::begin(_disks), std::end(_disks), std::greater_equal<Disk>());

#ifndef COINS_ON_A_SHELF_BENCHMARK
    calculatePositions(_disks);
    reasignIds();
    updateCanvasAndBlock();
#endif
    _spanLength = 0;

    Disk &d1 = _disks.at(0);
    Disk &d2 = _disks.at(1);
#ifndef COINS_ON_A_SHELF_BENCHMARK
    d1.setPosX(_pCrtanje->width() / 2.0);
    d1.setPosY(SHELF_Y + SHELF_HEIGHT + d1.getRadius());
    updateCanvasAndBlock();

    placeOnShelf(d2, d1, NeighbourSide::LEFT);
    updateCanvasAndBlock();
#endif
    _ordering.push_back(d1);
    _ordering.push_back(d2);

    Gap g = Gap(new Disk(d1), new Disk(d2));
    _gapSizes.push(g);

    _spanLength = d1.getRadius() + footpointDistance(d1, d2) + d2.getRadius();

    for(auto& disk : _disks)
    {

        if(disk.getId() == 0 || disk.getId() == 1)
            continue;
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

#ifndef COINS_ON_A_SHELF_BENCHMARK
                placeOnShelf(disk, d1, NeighbourSide::RIGHT);
#endif
                if(placingLeftIncreasesSpanLength) {
                   _spanLength = newSpanLengthLeft;
                   _ordering.push_front(disk);
                }

                Gap g = Gap(new Disk(disk), new Disk(d1));
                _gapSizes.push(g);
#ifndef COINS_ON_A_SHELF_BENCHMARK
                updateCanvasAndBlock();
#endif
            }

            else {
#ifndef COINS_ON_A_SHELF_BENCHMARK
                placeOnShelf(disk, d2, NeighbourSide::LEFT);
#endif

                if (placingRightIncreasesSpanLength) {
                    _spanLength = newSpanLengthRight;
                    _ordering.push_back(disk);
                }

                Gap g = Gap(new Disk(d2), new Disk(disk));
                _gapSizes.push(g);
#ifndef COINS_ON_A_SHELF_BENCHMARK
                updateCanvasAndBlock();
#endif
            }
        }
        else {
            const auto &top = _gapSizes.top();
            Disk* leftDisk = top.getLeftDisk();
            Disk* rightDisk = top.getRightDisk();
            disk.setIsHidden(true);
#ifndef COINS_ON_A_SHELF_BENCHMARK
            placeOnShelf(disk, *leftDisk, NeighbourSide::LEFT);
#endif
            Gap g1 = Gap(leftDisk, new Disk(disk));
            Gap g2 = Gap(new Disk(disk), rightDisk);
            _gapSizes.push(g1);
            _gapSizes.push(g2);
            _gapSizes.pop();

            // the span won't increase because the inserted disk is fully hidden between the two disks
            disk.setIsHidden(true);

#ifndef COINS_ON_A_SHELF_BENCHMARK
            updateCanvasAndBlock();
#endif
        }
    }
#ifndef COINS_ON_A_SHELF_BENCHMARK
    emit animacijaZavrsila();
#endif
}

void CoinsOnAShelf::pokreniNaivniAlgoritam()
{

    std::sort(std::begin(_disksNaive), std::end(_disksNaive), std::less<Disk>());
#ifndef COINS_ON_A_SHELF_BENCHMARK
    calculatePositions(_disksNaive);
    updateCanvasAndBlock();
#endif

    int n = _disksNaive.size();
    _spanLengthNaive = (float)INT_MAX;

    do {
        float currentResult = _disksNaive.front().getRadius() + _disksNaive.back().getRadius();

#ifndef COINS_ON_A_SHELF_BENCHMARK
        organizeOnShelfNaive();
        updateCanvasAndBlock();
#endif

        for (int i=0; i<n-1; ++i) {
            currentResult += footpointDistance(_disksNaive.at(i), _disksNaive.at(i+1));
        }

        if(currentResult < _spanLengthNaive) {
            _spanLengthNaive = currentResult;
            _orderingNaive = _disksNaive;
        }

    } while(std::next_permutation(std::begin(_disksNaive), std::end(_disksNaive)));

    _disksNaive = _orderingNaive;

#ifndef COINS_ON_A_SHELF_BENCHMARK
    updateCanvasAndBlock();
    emit animacijaZavrsila();
#endif
}

void CoinsOnAShelf::crtajAlgoritam(QPainter *painter) const
{
    if(!painter)
        return;

    auto pen = painter->pen();
    pen.setColor(Qt::black);
    painter->setPen(pen);

    painter->fillRect(0, SHELF_Y, _pCrtanje->width(), SHELF_HEIGHT, Qt::blue);



    for(const auto &disk : _disks) {
        painter->drawEllipse(QPointF(disk.getPosX(), disk.getPosY()), disk.getRadius(), disk.getRadius());
    }
}

void CoinsOnAShelf::crtajNaivniAlgoritam(QPainter *painter) const
{
    if(!painter)
        return;

    auto pen = painter->pen();
    pen.setColor(Qt::black);
    painter->setPen(pen);

    painter->fillRect(0, SHELF_Y, _pCrtanje->width(), SHELF_HEIGHT, Qt::blue);



    for(const auto &disk : _disksNaive) {
        qDebug() << "Printing disk pos x: " << disk.getPosX();
        painter->drawEllipse(QPointF(disk.getPosX(), disk.getPosY()), disk.getRadius(), disk.getRadius());
    }
}


std::deque<float> CoinsOnAShelf::generateRandomRadiuses(int numDisks) const
{
    std::deque<float> radiuses;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(MIN_RADIUS, MAX_RADIUS);

    for (int i=0; i<numDisks; ++i) {
        float r = dis(gen);
        radiuses.push_back(r);
    }

    return radiuses;
}

void CoinsOnAShelf::calculatePositions(std::deque<Disk>& disks)
{
    int canvasWidth = _pCrtanje->width();
    int canvasHeight = _pCrtanje->height();

    float currentX = 10.0;
    float currentY = canvasHeight - 10.0;
    float currentMaxRadius = 0.0;

    for(auto& disk : disks)
    {

        if (currentX + 2*disk.getRadius() > canvasWidth) {
            currentY -= 2*currentMaxRadius + 10.0;
            currentX = 10.0;
        }

        currentX += disk.getRadius();
        disk.setPosX(currentX);
        disk.setPosY(currentY - disk.getRadius());

        if (disk.getRadius() > currentMaxRadius)
            currentMaxRadius = disk.getRadius();

        currentX += disk.getRadius();
    }
}

void CoinsOnAShelf::placeOnShelf(Disk &disk, Disk &neighbour, NeighbourSide ns)
{
    if (ns == NeighbourSide::LEFT)
        disk.setPosX(neighbour.getPosX() + footpointDistance(neighbour, disk));
    else
        disk.setPosX(neighbour.getPosX() - footpointDistance(disk, neighbour));

    disk.setPosY(SHELF_Y + SHELF_HEIGHT + disk.getRadius());

}

void CoinsOnAShelf::organizeOnShelfNaive()
{
    int n = _disksNaive.size();
    int s = n / 2.0;
    auto& middleDisk = _disksNaive.at(s);
    qDebug() << "Middle disk:" << middleDisk.getId();
    float shelfPos = SHELF_Y + SHELF_HEIGHT;

    middleDisk.setPosX(_pCrtanje->width() / 2.0);
    middleDisk.setPosY(shelfPos + middleDisk.getRadius());

    float currentX = middleDisk.getPosX();
    Disk neighbourDisk = middleDisk;
    Disk previousDisk = _disksNaive.at(s - 1);

    for (int i = s+1; i < n; ++i) {
        auto& currentDisk = _disksNaive.at(i);

        if (neighbourDisk.getSize() <= gapSize(previousDisk, currentDisk))
             currentX = previousDisk.getPosX() + footpointDistance(previousDisk, currentDisk);

        else
            currentX += footpointDistance(neighbourDisk, currentDisk);

        currentDisk.setPosX(currentX);
        currentDisk.setPosY(shelfPos + currentDisk.getRadius());

        previousDisk = neighbourDisk;
        neighbourDisk = currentDisk;
    }

    currentX = middleDisk.getPosX();
    neighbourDisk = middleDisk;
    previousDisk = _disksNaive.at(s + 1);

    for (int i = s-1; i >= 0; --i) {
        auto& currentDisk = _disksNaive.at(i);

        if (neighbourDisk.getSize() <= gapSize(previousDisk, currentDisk))
            currentX = previousDisk.getPosX() - footpointDistance(previousDisk, currentDisk);
        else
            currentX -= footpointDistance(neighbourDisk, currentDisk);

        currentDisk.setPosX(currentX);
        currentDisk.setPosY(shelfPos + currentDisk.getRadius());

        previousDisk = neighbourDisk;
        neighbourDisk = currentDisk;
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

void CoinsOnAShelf::reasignIds()
{
    int i = 0;
    for(auto &disk : _disks) {
        disk.setId(i);
        ++i;
    }
}

float CoinsOnAShelf::getSpanLength() const
{
    return _spanLength;
}

float CoinsOnAShelf::getSpanLengthNaive() const
{
    return _spanLengthNaive;
}
