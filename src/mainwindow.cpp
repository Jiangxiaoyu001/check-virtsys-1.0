#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindowInit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MainWindowInit()
{
    QPalette m_pal;
//    this->setCentralWidget(m_staWidget);
    this->setWindowTitle("check virtsys");
    this->setFixedSize(900,600);
//setAttribute(Qt::WA_TransparentForMouseEvents,false);
//    this->resize(900,600);
    m_pal.setColor(QPalette::Background,QColor(100,100,105));
    this->setAutoFillBackground(m_staWidget);
    this->setPalette(m_pal);
    m_staWidget=new QStackedWidget(this);

    m_staWidget->setGeometry(0,0,900,600);
    window=new Check_Virtsys_Window(m_staWidget);
//    window->setGeometry(this->x(),this->y(),this->width(),this->height());
    m_staWidget->addWidget(window);
    m_staWidget->setCurrentWidget(window);
}

