#include <QApplication>
#include "remote-connect-mainWindow.h"
#include "remote-connect-vnc.h"



int main(int argc,char **argv)
{
	QApplication a(argc,argv);
	/* start gui  */
	//remoteConnectMainWindow w;
	//w.show();
	remoteConnectVnc remoteCon;
	a.exec();
}
