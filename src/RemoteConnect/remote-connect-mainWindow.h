/************************************************
*Description:
*	as remote connect start base-window design it with custom,
*	allow to input server ip and port		
*
*DateTime:
*	Fir Apr 1 2020-12:30
*
*Author: 
*	jiangxiaoyu
*
*Email: 
*	1725087341@qq.com (qq emial,hahah)
********************************************/

#ifndef _REMOTECONNECTMAINWINDOW_H_
#define _REMOTECONNECTMAINWINDOW_H_

#include <iostream>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>

class remoteConnectMainWindow:public QWidget{
public:
	explicit remoteConnectMainWindow();
	~remoteConnectMainWindow();
private:
	
	QLineEdit *serverIp,
			  *serverPort;

	QPushButton *connectBtn,
				*cancelBtn;
	
    void createlayout();
	void mainwindowInit();
	void signal_Solt_init();
	void signalHandler();
};

#endif /* remote-connect-mainwindow.h*/
