#ifndef COINSONASHELF_H
#define COINSONASHELF_H

#include <vector>
#include <queue>
#include <tuple>

#include "algoritambaza.h"
#include "disk.h"

// define the maximimum and minimum value for disk radius
#define MAX_RADIUS (256)
#define MIN_RADIUS (1)

class CoinsOnAShelf : public AlgoritamBaza
{
public:
    CoinsOnAShelf(QWidget *pCrtanje,
                  int pauzaKoraka,
                  const bool &naivni = false,
                  std::string imeDatoteke = "",
                  int brojTacaka = BROJ_SLUCAJNIH_OBJEKATA);

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

    std::deque<Disk> _ordering;
    int _orderingSize;
    float _spanLength;

    float footpointDistance(const Disk &disk1, const Disk &disk2);
    float gapSize(const Disk &disk1, const Disk &disk2);
    bool canDiskFitInGap(Disk &disk, float gapSize);

    std::priority_queue<std::tuple<Disk, Disk, float>> _gapSizes;
};

#endif // COINSONASHELF_H
