#ifndef COINSONASHELF_H
#define COINSONASHELF_H

#include <vector>
#include <queue>
#include <tuple>

#include "algoritambaza.h"
#include "disk.h"
#include "gap.h"

class CoinsOnAShelf : public AlgoritamBaza
{
public:
    CoinsOnAShelf(QWidget *pCrtanje,
                  int pauzaKoraka,
                  const bool &naivni = false,
                  std::string imeDatoteke = "",
                  int brojTacaka = BROJ_SLUCAJNIH_OBJEKATA);

    // define the maximimum and minimum value for disk radius
    constexpr static float MAX_RADIUS = 81.0;
    constexpr static float MIN_RADIUS = 1;

    void pokreniAlgoritam();
    void crtajAlgoritam(QPainter *painter) const;
    void pokreniNaivniAlgoritam();
    void crtajNaivniAlgoritam(QPainter *painter) const;

    std::vector<Disk>& getOrdering() const;
    int getOrderingSize() const;
    float getSpanLength() const;

private:
    enum NeighbourSide
    {
        LEFT,
        RIGHT
    };

    std::deque<float> generateRandomRadiuses(int numDisks) const;
    std::deque<Disk> _disks;
    std::deque<Disk> _disksNaive;

    std::deque<Disk> _ordering;
    int _orderingSize;
    float _spanLength;
    float _spanLengthNaive;

    float footpointDistance(const Disk &disk1, const Disk &disk2);
    float gapSize(const Disk &disk1, const Disk &disk2);
    bool canDiskFitInGap(Disk &disk, float gapSize);
    void reasignIds();
    void calculatePositions();
    void placeOnShelf(Disk &disk, Disk &neighbour, NeighbourSide n);

    std::priority_queue<Gap> _gapSizes;

    constexpr static int SHELF_X = 10;
    constexpr static int SHELF_Y = 50;
    constexpr static int SHELF_HEIGHT = 10;
};

#endif // COINSONASHELF_H
