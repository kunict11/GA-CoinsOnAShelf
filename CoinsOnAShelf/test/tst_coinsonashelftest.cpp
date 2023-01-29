#include <QtTest>
#include <QObject>
#include <QDir>
#include <QDebug>

// add necessary includes here
#include "../app/algoritmi_studentski_projekti/coinsonashelf.h"


// NOTE: Tests will not execute unless #define COINS_ON_A_SHELF_BENCHMARK is enabled
class CoinsOnAShelfTest : public QObject
{
    Q_OBJECT

public:
    CoinsOnAShelfTest();
    ~CoinsOnAShelfTest();

private slots:
    void pokreniAlgoritamTest_WhenFileNameGiven();
    void pokreniAlgoritamTest_WhenFileNameGivenAndResultIsNotOptimal();
    void pokreniAlgoritamTest_WhenRandomDisksAreGenerated();
    void pokreniNaivniAlgoritamTest_WhenFileNameGiven();
    void pokreniNaivniAlgoritamTest_WhenRandomDisksAreGenerated();


};

CoinsOnAShelfTest::CoinsOnAShelfTest()
{

}

CoinsOnAShelfTest::~CoinsOnAShelfTest()
{

}

void CoinsOnAShelfTest::pokreniAlgoritamTest_WhenFileNameGiven()
{
    float expected = 324.0;
    QDir buildDir = QDir::current();
    buildDir.cdUp();
    buildDir.cdUp();
    QString filePath = buildDir.path().append("/GA-CoinsOnAShelf/CoinsOnAShelf/app/input_files/radiuses2.txt");

    CoinsOnAShelf* coinsOnAShelf = new CoinsOnAShelf(nullptr, 0, false, filePath.toStdString(), 0);
    coinsOnAShelf->pokreniAlgoritam();
    float result = coinsOnAShelf->getSpanLength();

    QVERIFY(result == expected);
}

void CoinsOnAShelfTest::pokreniAlgoritamTest_WhenFileNameGivenAndResultIsNotOptimal()
{
    float expected = 801.0;
    QDir buildDir = QDir::current();
    buildDir.cdUp();
    buildDir.cdUp();
    QString filePath = buildDir.path().append("/GA-CoinsOnAShelf/CoinsOnAShelf/app/input_files/radiuses3.txt");

    CoinsOnAShelf* coinsOnAShelf = new CoinsOnAShelf(nullptr, 0, false, filePath.toStdString(), 0);
    coinsOnAShelf->pokreniAlgoritam();
    float result = coinsOnAShelf->getSpanLength();

    QVERIFY(result == expected);
}

void CoinsOnAShelfTest::pokreniAlgoritamTest_WhenRandomDisksAreGenerated()
{
    CoinsOnAShelf* coinsOnAShelf = new CoinsOnAShelf(nullptr, 0, false, "", 10);
    coinsOnAShelf->pokreniAlgoritam();
    float result = coinsOnAShelf->getSpanLength();
    int size = coinsOnAShelf->getNumberOfDisks();

    QVERIFY(result > 0);
    QVERIFY(size == 10);
}

void CoinsOnAShelfTest::pokreniNaivniAlgoritamTest_WhenFileNameGiven()
{
    float expected = 798.0;
    QDir buildDir = QDir::current();
    buildDir.cdUp();
    buildDir.cdUp();
    QString filePath = buildDir.path().append("/GA-CoinsOnAShelf/CoinsOnAShelf/app/input_files/radiuses3.txt");

    CoinsOnAShelf* coinsOnAShelf = new CoinsOnAShelf(nullptr, 0, true, filePath.toStdString(), 0);
    coinsOnAShelf->pokreniNaivniAlgoritam();
    float result = coinsOnAShelf->getSpanLengthNaive();

    QVERIFY(result == expected);
}

void CoinsOnAShelfTest::pokreniNaivniAlgoritamTest_WhenRandomDisksAreGenerated()
{
    CoinsOnAShelf* coinsOnAShelf = new CoinsOnAShelf(nullptr, 0, true, "", 5);
    coinsOnAShelf->pokreniNaivniAlgoritam();
    float result = coinsOnAShelf->getSpanLengthNaive();
    int size = coinsOnAShelf->getNumberOfDisksNaive();

    QVERIFY(result > 0);
    QVERIFY(size == 5);
}

QTEST_APPLESS_MAIN(CoinsOnAShelfTest)

#include "tst_coinsonashelftest.moc"
