#include "mainview.h"
#include "ui_mainview.h"

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
    m_appManager = new CAppManager(ui->m_qvtkWidget, ui->m_openCVWidget);
}

MainView::~MainView()
{
    delete ui;
    if (m_appManager)
      delete m_appManager;
}
