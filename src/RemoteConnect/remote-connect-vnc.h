#ifndef _REMOTECONNECT_VNC_H
#define _REMOTECONNECT_VNC_H

#include <iostream>
#include <string>

struct{
	int serverPort;
	std::string serverIp;
	std::string localIp;
	std::string serverName;
}*phostPrivate, hostPrivate = {
				.serverPort = 0,
				.serverIp = "",
				.localIp = "",
				.serverName = ""
				};

/* before define */
class tcpClient;
class remoteConnectVnc{
public:
	explicit remoteConnectVnc();
	~remoteConnectVnc();
public:
	int connectServer();
	int tcpConnect();
	int hdpConnect();
private:
	tcpClient *tcpCtrl;
	void setServerPort(uint port);
	void setServerIp(std::string ip);
	void setHostName(std::string doname);
	std::string getHostName();
	std::string getServerIp();
	std::string getLocalIp();
	unsigned int getServerPort();
	//
};




#endif /* remote-connect-vnc.h*/
