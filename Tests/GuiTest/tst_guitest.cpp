#include <QtTest>
#include <../../mainwindow.h>
#include <../../spofity.h>
#include <../../musiclists.h>
#include <../../loggedwindow.h>


class GuiTest: public QObject
{
    Q_OBJECT

    friend class MainWindow;
    friend class Spofity;
    friend class LoggedWindow;

public:
    GuiTest();
    ~GuiTest();


private:
    LoggedWindow *loggedWindow;
    MainWindow *window;

private slots:
    void test_case1();
    void test_case2();


};

GuiTest::GuiTest()
{

}

GuiTest::~GuiTest()
{
    delete this->window;
}


// open MainWindow, click in the login button and await for the signal
void GuiTest::test_case1()
{

    window = new MainWindow();
    QApplication::setActiveWindow(window);

    QString comboBoxName = "pushButton";
    QPushButton* button = window->findChild<QPushButton*>(comboBoxName);
    QTest::mouseClick(button, Qt::LeftButton);

    QSignalSpy spy(window, SIGNAL(hidding()));
    QVERIFY(spy.wait(10000));

}


// check the title name and add a playlist
void GuiTest::test_case2()
{

    this->loggedWindow = this->window->getLoggegWindow();
    QApplication::setActiveWindow(this->loggedWindow);

    QString lineName = "lineEdit";
    QLineEdit* lineEdit = this->loggedWindow->findChild<QLineEdit*>(lineName);

    QVERIFY(this->loggedWindow->windowTitle().size() > 13);
    lineEdit->setFocus();
    QTest::keyClicks(QApplication::focusWidget(), "Lista 1");

    QString comboBoxName = "pushButton";
    QPushButton* button = this->loggedWindow->findChild<QPushButton*>(comboBoxName);
    QTest::mouseClick(button, Qt::LeftButton);

}



QTEST_MAIN(GuiTest)

#include "tst_guitest.moc"
