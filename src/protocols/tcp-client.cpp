#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <thread>
#include <string.h>
#include <linux/if_link.h>
#include <condition_variable>
#include <mutex>
#include <protocols/tcp-client.h>


using namespace std;


hostPriHandler hostP = {
	.serverPort = 0,
	.serverIp = "",
	.localIpv4 = "",
    .local_ipv4 = {""},
    .local_ipv6 = {""},
	.serverName = ""
};
hostPriHandler * hostPri = &hostP;


/* single mode */
tcpClient * tcpClient::tcpCtrl = nullptr;
tcpClient * tcpClient::tcpClientHandler()
{
	if (tcpCtrl == nullptr)
		tcpCtrl = new tcpClient;
	return tcpCtrl;
}




tcpClient::tcpClient()
{
    //get_local_ip(AF_INET, hostPri->local_ipv4);
    ipvlistRemove();
    get_local_ipv4();
    local_ipv4_6_list();
}

tcpClient::~tcpClient()
{

}


void tcpClient::ipvlistRemove()
{
    for(auto iter = hostPri->local_ipv4.begin(); iter != hostPri->local_ipv4.end();)
        hostPri->local_ipv4.erase(iter++);
    for(auto iter = hostPri->local_ipv6.begin(); iter != hostPri->local_ipv6.end();)
        hostPri->local_ipv6.erase(iter++);
}



void tcpClient::setServerPort(uint port)
{
	hostPri->serverPort = port;
}


void tcpClient::setHostName(std::string &name)
{
	hostPri->serverName.clear();
	hostPri->serverName.assign(name);
}

void tcpClient::setServerIp(std::string &ip)
{
	hostPri->serverIp.clear();
	hostPri->serverIp = ip;
}



std::string tcpClient::getHostName()
{
	return hostPri->serverName;
}

std::string tcpClient::getServerIp()
{
	return hostPri->serverIp;
}

std::string tcpClient::getLocalIp()
{
	return hostPri->serverIp;
}



unsigned int tcpClient::getServerPort()
{
	return hostPri->serverPort;
}


int tcpClient::get_local_ipv4()
{
    return get_local_ip(AF_INET, hostPri->local_ipv4);
}

int tcpClient::get_local_ipv6()
{
    return get_local_ip(AF_INET6, hostPri->local_ipv6);
}


void tcpClient::local_ipv4_6_list()
{
    for(auto &iter : hostPri->local_ipv4) {
        hostPri->localIpv4 = iter;
        cout<<"ipv4:"<<iter<<endl;
    }
        
    for(auto &iter : hostPri->local_ipv6)
        cout<<"ipv6:"<<iter<<endl;

}


int tcpClient::get_local_ip(int ipv4_6, std::list<std::string>& out_list_ip)
{
    //typedef struct ifaddrs IFADR;
    // IFADR *ifaddr = new  IFADR;
    // IFADR *ifa = new  IFADR;

    struct ifaddrs *ifa = nullptr;
    int family, s, n = 0;
    char host[NI_MAXHOST] = {0};

    if (getifaddrs(&ifa) == -1) {
        perror("getifaddrs");
        return -1;
    }
    /* Walk through linked list, maintaining head pointer so we
    can free list later */
    
    for (; ifa != NULL; ifa = ifa->ifa_next, n++) {
        if (ifa->ifa_addr == NULL)
            continue;

        family = ifa->ifa_addr->sa_family;

        /* Display interface name and family (including symbolic
                    form of the latter for the common families) */
      

        printf("%-8s %s (%d)\n",
                ifa->ifa_name,
                (family == AF_PACKET) ? "AF_PACKET" :
                (family == AF_INET) ? "AF_INET" :
                (family == AF_INET6) ? "AF_INET6" : "???",
                family);


        
    /* For an AF_INET* interface address, display the address */


        if (family == AF_INET || family == AF_INET6) {
            s = getnameinfo(ifa->ifa_addr,
                            (family == AF_INET) ? sizeof(struct sockaddr_in) :
                                    sizeof(struct sockaddr_in6), 
                                    host, NI_MAXHOST,
                            NULL, 0, NI_NUMERICHOST);
            if (s != 0) {
                printf("getnameinfo() failed: %s\n", gai_strerror(s));
                return -1;
            }
            if(atoi(host) != atoi("127.0.0.1")) {
                (family == AF_INET) ? hostPri->local_ipv4.push_back(host) : 
                (family == AF_INET6) ? hostPri->local_ipv6.push_back(host) :
                hostPri->local_ipv6.push_back("???");
            }
           

            printf("\t\taddress: <%s>\n", host);
        } else if (family == AF_PACKET && ifa->ifa_data != nullptr) {
            struct rtnl_link_stats *stats = reinterpret_cast<struct rtnl_link_stats *>(ifa->ifa_data);
            printf("\t\ttx_packets = %10u; rx_packets = %10u\n"
                    "\t\ttx_bytes   = %10u; rx_bytes   = %10u\n",
                    stats->tx_packets, stats->rx_packets,
                    stats->tx_bytes, stats->rx_bytes);
        }
    }
    freeifaddrs(ifa);
    return 0;
}

void tcpClient::recvSockMsg(int sockfd)
{
	char recvBuff[1024] = {0};
	ssize_t recvByte = 0;
	struct sockaddr_in sockAdr;
	socklen_t len = sizeof(sockAdr);
	memset(&sockAdr, 0, sizeof(sockAdr));

	/* thread lock */
	std::mutex mtx;
	std::condition_variable cv;
	std::unique_lock<std::mutex> lck(mtx);
	std::condition_variable cvTimer;
	/*
	ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen);	
	*/
	while (true) { 
		recvByte = recvfrom(sockfd, recvBuff, sizeof(recvBuff), 0, (struct sockaddr *)&sockAdr, &len);
		if (recvByte == ENOTCONN)
			cout << "socket not connect" << endl;
		if (recvByte == -1)
			cout << "receive messages failed" << endl;
		else{
			cout << "recv:" << recvBuff << " :from:" << inet_ntoa(sockAdr.sin_addr) << ntohs(sockAdr.sin_port) << endl;
			printf("\t\trecvBuff[%ld]=0x%02x\n", recvByte-1, recvBuff[recvByte-1]);
			memset(recvBuff, 0, sizeof(recvBuff));
			recvByte = -1;
		}
		/* show send */
		cout << "send:" <<endl;
		std::cv_status res = cv.wait_for(lck, std::chrono::milliseconds(500));
		if ((res == cv_status::timeout) ? false : true)
			cout << "\t\ttimeout thread is weak" << endl;
		//std::this_thread::sleep_for(std::chrono::milliseconds(500)); /* thread sleep 500ms */
	}
}


void tcpClient::sendSockMsg(int sockfd)
{
/*
ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
*/
	ssize_t sendByte = 0;
	//std::string sendBuff;
	char sendBuff[1024] = {0};
	while (true) {
		cout << "send:";
		cin.getline((char *)sendBuff, 1024); /* input msg to send */
		char s = 0x0a;
		strncat(sendBuff, &s, 1);
		sendByte = send(sockfd, sendBuff, strlen(sendBuff), 0);
		/* refulsh sock  */
		//sendfile();
		if (sendByte == -1 || sendByte == 0) 
			cout << "[info] send messages to server failed" << endl;
		else
			cout << "[info] send successed wait reply" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); /* thread sleep 500ms */
	}
}


int tcpClient::tcpConnect()
{
	int sockfd;
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
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
		//std::string serverip = getServerIp();
        std::string serverip = hostPri->localIpv4;
        //std::string localIPV4 = hostPri->local_ipv4.begin();
        printf("\nlocalIPV4=%s\n", hostPri->localIpv4.data());
		if(!serverip.empty())
			serverAdr.sin_addr.s_addr = inet_addr(serverip.data());/* server ip */
			//serverAdr.sin_addr.s_addr = inet_addr("10.240.226.166");/* server ip */
		else{
			std::cout<<"server ip is empty , please give it!"<<std::endl;
			return -1;
		}
	}else
		memcpy(&serverAdr.sin_addr, host->h_addr, host->h_length);
	
    /* test start code */

    uint port_test = 8000;
    setServerPort(8000);
    
    int port = getServerPort();
	if ((port > 0) ? port : 0) {
        printf("port=%d\n", port);
		serverAdr.sin_port = htons(port);
    }
	else {
		std::cout<<"server port is empty , please give it!"<<std::endl;
		return -1;
	}

	//cout <<"hostAdr:" <<serverAdr.sin_addr.s_addr <<"\nhostPort:" <<serverAdr.sin_port <<endl;
	cout << "hostAdr:" << hostPri->localIpv4  << "\nhostPort:" << port <<endl;
    /* test end */

	int nRet = connect(sockfd, (sockaddr*)&serverAdr, sizeof(serverAdr));
    if(nRet == -1) {
        cout << "connect server failed" << endl;
        return -1;
    } else
        cout << "connect server succeed" << endl;

	std::thread recvthread(recvSockMsg, sockfd);
	std::thread sendthread(sendSockMsg, sockfd);
	recvthread.detach();
	sendthread.join();
	close(sockfd);
	return 0;
}

/* use for test 
int main(int argc, char * argv[])
{
    tcpClient *tcpCtrl = tcpClient::tcpClientHandler();
    tcpCtrl->tcpConnect();
    return 0;
}
*/
