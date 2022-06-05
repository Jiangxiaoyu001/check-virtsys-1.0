//#include <remoteConnect/remote-connect-vnc.h>

#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <protocols/tcp-client.h>
#include "remote-connect-vnc.h"

#include <QApplication>

remoteConnectVnc::remoteConnectVnc():
	tcpCtrl(tcpClient::tcpClientHandler())
{
	//tcpConnect();
}

remoteConnectVnc::~remoteConnectVnc()
{
	/* disconstruct */
}


void remoteConnectVnc::setServerPort(uint port)
{
	//phostPrivate->serverPort = port;
	tcpCtrl->setServerPort(port);
}


void remoteConnectVnc::setHostName(std::string name)
{
	//phostPrivate->serverName.clear();
	//phostPrivate->serverName.assign(name);
}

void remoteConnectVnc::setServerIp(std::string ip)
{
	//PhostPrivate->serverIp.clear();
	//PhostPrivate->serverIp = ip;
	tcpCtrl->setServerIp(ip);
}



std::string remoteConnectVnc::getHostName()
{
	//return hostPri->serverName;
	return nullptr;
}

std::string remoteConnectVnc::getServerIp()
{
	//return hostPri->serverIp;
	return nullptr;
}

std::string remoteConnectVnc::getLocalIp()
{
	//return hostPri->serverIp;
	return nullptr;
}



unsigned int remoteConnectVnc::getServerPort()
{
	//return hostPri->serverPort;
	return 0;
}



int remoteConnectVnc::tcpConnect()
{
	int clientsockfd;
	if((clientsockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		return -1;
	}
	
	struct hostent *host = nullptr;
	struct sockaddr_in serverAdr;
	memset(&serverAdr, 0, sizeof(serverAdr));
	serverAdr.sin_family = AF_INET;
	if(((host = gethostbyname(getHostName().data())) == nullptr))
	{
		printf("gethostbyname failed.\n");
		std::string serverip = getServerIp();
		if(!serverip.empty())
			serverAdr.sin_addr.s_addr = inet_addr(serverip.data());/* server ip */
		else{
			std::cout<<"server ip is empty , please give it!"<<std::endl;
			return -1;
		}
	}else
		memcpy(&serverAdr.sin_addr, host->h_addr, host->h_length);
	
	if(uint port = getServerPort() > 0)
		serverAdr.sin_port = htons(port);
	else{
		std::cout<<"server port is empty , please give it!"<<std::endl;
		return -1;
	}
	
	int nRet = connect(clientsockfd, (sockaddr*)&serverAdr, sizeof(serverAdr));

	close(clientsockfd);
	return 0;
}






int remoteConnectVnc::connectServer()
{
	return tcpConnect();
}

/*
int main(int argc, char *argv[])
{
	
}
*/
