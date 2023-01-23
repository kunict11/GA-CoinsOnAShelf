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
    constexpr static float MAX_RADIUS = 64.0;
    constexpr static float MIN_RADIUS = 0.4;

    void pokreniAlgoritam();
    void crtajAlgoritam(QPainter *painter) const;
    void pokreniNaivniAlgoritam();
    void crtajNaivniAlgoritam(QPainter *painter) const;

    std::vector<Disk>& getOrdering() const;
    int getOrderingSize() const;
    float getSpanLength() const;

private:
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

    std::priority_queue<Gap> _gapSizes;
};

#endif // COINSONASHELF_H
