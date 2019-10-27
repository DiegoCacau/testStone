#include <QtTest>
#include "../../musiclists.h"

class MusicListsTest : public QObject
{
    Q_OBJECT

private:
    MusicLists* list;

public:
    MusicListsTest();
    ~MusicListsTest();

private slots:
    // test addList and count
    void test_case1();

    // test listExist
    void test_case2();

    // test addMusicToList
    void test_case3();

    //test removeMusic
    void test_case4();

};

MusicListsTest::MusicListsTest()
{
    this->list = new MusicLists();
}

MusicListsTest::~MusicListsTest()
{
    delete this->list;
}

void MusicListsTest::test_case1()
{
    QCOMPARE(this->list->count(), 0);
    this->list->addList("Lista Teste");
    QCOMPARE(this->list->count(), 1);
}

void MusicListsTest::test_case2()
{
    QCOMPARE(this->list->listExist("Lista Teste"), true);
    QCOMPARE(this->list->listExist("Lista Falsa"), false);
}

void MusicListsTest::test_case3()
{
   this->list->addMusicToList("Lista Teste", "Id Fake", "Musica Teste");
   QStringList music = this->list->getMusicsFromList("Lista Teste");
   QCOMPARE(music.contains("Musica Teste"), true);
}

void MusicListsTest::test_case4()
{
   this->list->removeMusic("Lista Teste", "Musica Teste");
   QStringList music = this->list->getMusicsFromList("Lista Teste");
   QCOMPARE(music.contains("Musica Teste"), false);
}

QTEST_APPLESS_MAIN(MusicListsTest)

#include "tst_musicliststest.moc"
