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

    }

    int i = 0;
    for (float r : radiuses) {
        _disks.push_back(Disk{r, i});
        _disksNaive.push_back(Disk{r, i});
        i+=1;
    }

    calculatePositions();


}

void CoinsOnAShelf::pokreniAlgoritam()
{
    std::sort(std::begin(_disks), std::end(_disks), std::greater_equal<Disk>());
    calculatePositions();
    reasignIds();
    updateCanvasAndBlock();
    _spanLength = 0;

    Disk &d1 = _disks.at(0);
    Disk &d2 = _disks.at(1);

    d1.setPosX((SHELF_X + _pCrtanje->width() - 20) / 2.0);
    d1.setPosY(SHELF_Y + SHELF_HEIGHT + d1.getRadius());
    placeOnShelf(d2, d1, NeighbourSide::LEFT);

    _ordering.push_back(d1);
    _ordering.push_back(d2);

    _gapSizes.push(Gap(d1, d2));

    updateCanvasAndBlock();

    _spanLength = d1.getRadius() + footpointDistance(d1, d2) + d2.getRadius();

    for(auto& disk : _disks)
    {

        qDebug() << "Now working on disk" << disk.getId();

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

                placeOnShelf(disk, d1, NeighbourSide::RIGHT);

                if(placingLeftIncreasesSpanLength) {
                   _spanLength = newSpanLengthLeft;
                   _ordering.push_front(disk);
                }
                _gapSizes.push(Gap{disk, d1});
                updateCanvasAndBlock();
            }

            else {

                placeOnShelf(disk, d2, NeighbourSide::LEFT);

                if (placingRightIncreasesSpanLength) {
                    _spanLength = newSpanLengthRight;
                    _ordering.push_back(disk);
                }
                _gapSizes.push(Gap{d2, disk});
                updateCanvasAndBlock();
            }
        }
        else {
            Disk& leftDisk = _gapSizes.top().getLeftDisk();
            Disk& rightDisk = _gapSizes.top().getRightDisk();
            _gapSizes.push(Gap{leftDisk, disk});
            _gapSizes.push(Gap{disk, rightDisk});
            _gapSizes.pop();
            // the span won't increase because the inserted disk is fully hidden between the two disks
            disk.setIsHidden(true);
            placeOnShelf(disk, leftDisk, NeighbourSide::LEFT);
            updateCanvasAndBlock();
        }
    }

    qDebug() << _spanLength;
}

void CoinsOnAShelf::pokreniNaivniAlgoritam()
{

    std::sort(std::begin(_disksNaive), std::end(_disksNaive), std::less<Disk>());

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

    painter->fillRect(SHELF_X, SHELF_Y, _pCrtanje->width()-20, SHELF_HEIGHT, Qt::blue);



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

        if (disk.getRadius() > currentMaxRadius)
            currentMaxRadius = disk.getRadius();

        currentX += disk.getRadius();
    }
}

void CoinsOnAShelf::placeOnShelf(Disk &disk, Disk &neighbour, NeighbourSide ns)
{
    if (ns == NeighbourSide::LEFT)
        disk.setPosX(neighbour.getPosX() + footpointDistance(neighbour, disk));
    else{
        disk.setPosX(neighbour.getPosX() - footpointDistance(disk, neighbour));
        disk.setId(999);
    }

    disk.setPosY(SHELF_Y + SHELF_HEIGHT + disk.getRadius());
    qDebug() << "Disk with id " << disk.getId() << " x: " << disk.getPosX();
    qDebug() << "Neighbour " << neighbour.getId() << " " << neighbour.getPosX();

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
