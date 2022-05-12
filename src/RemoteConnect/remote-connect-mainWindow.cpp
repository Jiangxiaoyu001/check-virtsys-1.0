/************************************************
*Description:
*   as remote connect start base-window design it with custom,
*   allow to input server ip and port       
*
*DateTime:
*   Fir Apr 1 2020-12:30
*
*Author: 
*   jiangxiaoyu
*
*Email: 
*   1725087341@qq.com (qq emial,hahah)
********************************************/

#include <QDebug>
#include <protocols/tcp-client.h>
#include "remote-connect-mainWindow.h"

remoteConnectMainWindow::remoteConnectMainWindow():
	serverIp(new QLineEdit(this)),
	serverPort(new QLineEdit(this)),
	connectBtn(new QPushButton(this)),
	cancelBtn(new QPushButton(this))
{
    createlayout();
	mainwindowInit();
}

remoteConnectMainWindow::~remoteConnectMainWindow()
{

}


void remoteConnectMainWindow::createlayout()
{
    QVBoxLayout * vBox = new QVBoxLayout();
    //QGridLayout *Glayout  = new QGridLayout();
    this->setLayout(vBox);
}



void remoteConnectMainWindow::signal_Solt_init()
{
	connect(connectBtn, &QPushButton::clicked,
			[&](){
				qDebug() << "serverIp:" << serverIp->text();
				qDebug() << "serverPort:" << serverPort->text();
			});
}




void remoteConnectMainWindow::mainwindowInit()
{
    resize(600,600);
	
	QPushButton * connectBtn, *cancelBtn = new QPushButton(this);
	
    QLabel * server_ip_lab = new QLabel(this);
    QLabel * server_port_lab = new QLabel(this);
    QLineEdit  * server_ip_edit = new QLineEdit(this);
    QLineEdit  * server_port_edit = new QLineEdit(this);
    QHBoxLayout * hbox = new QHBoxLayout();
    QHBoxLayout * hbox1 = new QHBoxLayout();
    //QHBoxLayout * hbox2 = new QHBoxLayout();
	
	


    hbox->addStretch();
//    hbox->addSpacing(1);
    hbox->addWidget(server_ip_lab);
    hbox->addWidget(server_ip_edit);
    hbox->addStretch();
//    hbox->addSpacing(1);

//    hbox->setStretchFactor(server_ip_lab,1);
//    hbox->setStretchFactor(server_ip_edit,3);

    hbox1->addStretch();
    hbox1->addWidget(server_port_lab);
    hbox1->addWidget(server_port_edit);
    hbox1->addStretch();

    server_ip_lab->setText("serverIP: ");
    server_port_lab->setText("serverPort:");


    QVBoxLayout * vBox = static_cast<QVBoxLayout *>(layout());

    /*
    Glayout->setRowStretch(0,1);
    Glayout->setRowStretch(1,1);
    Glayout->addWidget(server_ip_lab,0,0,1,1);
    Glayout->addWidget(server_ip_edit,0,1,1,1);


    Glayout->addWidget(server_port_lab,1,0,1,1);
    Glayout->addWidget(server_port_edit,1,1,1,1);
    std::cout<<"Glayout:"<<layout()<<std::endl;
    */
    //vBox->addStretch();
    vBox->addStretch(10);
    vBox->addLayout(hbox);
    vBox->addStretch(10);
    vBox->addLayout(hbox1);
    vBox->addStretch(10);
//    vBox->addStretch();
}



