#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <appmanager.h>

namespace Ui {
class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

private:
    Ui::MainView *ui;
    std::unique_ptr<CAppManager> m_appManager;  //manager class
};

#endif // MAINVIEW_H
