#ifndef COINSONASHELF_H
#define COINSONASHELF_H

#include <vector>
#include <queue>
#include <tuple>

#include "algoritambaza.h"
#include "disk.h"
#include "gap.h"

#define COINS_ON_A_SHELF_BENCHMARK

class CoinsOnAShelf : public AlgoritamBaza
{
public:
    CoinsOnAShelf(QWidget *pCrtanje,
                  int pauzaKoraka,
                  const bool &naivni = false,
                  std::string imeDatoteke = "",
                  int brojTacaka = BROJ_SLUCAJNIH_OBJEKATA);

    // define the maximimum and minimum value for disk radius
    constexpr static float MAX_RADIUS = 196.0;
    constexpr static float MIN_RADIUS = 2.0;

    void pokreniAlgoritam();
    void crtajAlgoritam(QPainter *painter) const;
    void pokreniNaivniAlgoritam();
    void crtajNaivniAlgoritam(QPainter *painter) const;

    std::vector<Disk>& getOrdering() const;
    int getOrderingSize() const;
    float getSpanLength() const;
    float getSpanLengthNaive() const;

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
    std::deque<Disk> _orderingNaive;
    int _orderingSize;
    float _spanLength;
    float _spanLengthNaive;

    float footpointDistance(const Disk &disk1, const Disk &disk2);
    float gapSize(const Disk &disk1, const Disk &disk2);
    bool canDiskFitInGap(Disk &disk, float gapSize);
    void reasignIds();
    void calculatePositions(std::deque<Disk>& disks);
    void placeOnShelf(Disk &disk, Disk &neighbour, NeighbourSide n);
    void organizeOnShelfNaive();

    std::priority_queue<Gap> _gapSizes;

    constexpr static int SHELF_Y = 50;
    constexpr static int SHELF_HEIGHT = 10;
};

#endif // COINSONASHELF_H
