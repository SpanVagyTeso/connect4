#include <QtTest>
#include <QObject>
#include "gamemanager.h"

class idk : public QObject
{
    Q_OBJECT
public:
    idk();
    ~idk();
private:
    GameManager* gm;
private slots:
    void test_case1();
    void test_case2();
    void test_case3();
    void initTestCase();
    void test_place();
};
void idk::initTestCase(){
    gm=new GameManager();
}
idk::idk()
{

}

idk::~idk()
{

}

void idk::test_case1()
{
    gm->newGame(1);
    QCOMPARE(gm->getRow(),5);
}
void idk::test_case2()
{
    gm->newGame(2);
    QCOMPARE(gm->getRow(),6);
}
void idk::test_case3()
{
    gm->newGame(3);
    QCOMPARE(gm->getRow(),7);
}

void idk::test_place()
{
    gm->newGame(1);
    gm->place(90);
    QCOMPARE(gm->getField(0,0),1);
    QCOMPARE(gm->getCP(), 2);
    gm->place(90);
    QCOMPARE(gm->getField(0,1),2);
    QCOMPARE(gm->getCP(),1);
}
QTEST_APPLESS_MAIN(idk)
#include "tst_idk.moc"

