/************************************************
*Description:
*	as tcp client provide some API for use,
*	still in developing		
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


#ifndef _TCPCLIENT_H_
#define _TCPCLIENT_H_

#include <list>
#include <string.h>
#include <iostream>


typedef struct HOST{
	uint serverPort;
	std::string serverIp;
	std::string localIpv4;
    std::list<std::string> local_ipv4;
    std::list<std::string> local_ipv6;
	std::string serverName;
}hostPriHandler;


class tcpClient{
public:
    ~tcpClient();
	static tcpClient * tcpClientHandler();
private:
	static tcpClient *tcpCtrl;
    explicit tcpClient();
    
	void socketInit();
    int sockConnect();
 
	std::string getHostName();
	std::string getServerIp();
	unsigned int getServerPort();
    std::string getLocalIp();
    
    /* get ipv4_6 list */
    int get_local_ipv4();
    int get_local_ipv6();
    int get_local_ip(int ipv4_6, std::list<std::string>& out_list_ip);

    void ipvlistRemove();
    void local_ipv4_6_list();
	/* thread function  */
	static void recvSockMsg(int sock);
	static void sendSockMsg(int sock);
public:
    int tcpConnect();
    void setServerPort(uint port);
	void setServerIp(std::string& ip);
	void setHostName(std::string& doname);
};
#endif /* */
