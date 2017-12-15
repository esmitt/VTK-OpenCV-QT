#include "mainview.h"
#include "ui_mainview.h"

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
    cv::Mat image = cv::imread("small.png");
    ui->m_openCVWidget->showImage(image);
    //m_appManager = new CAppManager(ui->m_qvtkWidget, ui->m_openCVWidget);
    m_appManager = nullptr;
}

MainView::~MainView()
{
    delete ui;
    if (m_appManager)
      delete m_appManager;
}
