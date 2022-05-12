/************************************************
*Description:
*	as tcp server provide some API for use,
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




#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <thread>
#include<pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/sendfile.h>

using namespace std;

typedef struct serverNet{
    unsigned int port;
    std::string ip;
};


class tcpServer{
public:
    explicit tcpServer();
    ~tcpServer();
private:
    void serverInit();
	static void recvSockMsg(int sockfd);
	static void sendSockMsg(int sockfd);
public:
    int sockedConnect();
};



tcpServer::tcpServer()
{


}


tcpServer::~tcpServer()
{
    /* todo */

}


void tcpServer::serverInit()
{
    
}


void tcpServer::recvSockMsg(int sockfd)
{
	char recvBuff[1024] = {0};
	ssize_t recvByte = 0;
	//struct sockaddr sockAdr;
	struct sockaddr_in sockAdr;
	socklen_t len = sizeof(struct sockaddr_in);
	memset(&sockAdr, 0, sizeof(sockAdr));
	/*
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen);	
*/
	while (true) {
		cout << "waitting receive ..." << endl;
		
		socklen_t len = sizeof(struct sockaddr_in);
		recvByte = recvfrom(sockfd, recvBuff, sizeof(recvBuff), 0,
							(struct sockaddr *)(&sockAdr), &len);
		/*  */
		switch (errno) {
		case  ECONNREFUSED:
			cout << "recv error: A remote host refused to allow the network connection \
					(typically because it is not running the requested service)." << endl;
		case ENOTCONN:
			cout << "The socket is associated with a connection-oriented protocol and has not been connected" << endl;
		case ENOTSOCK:
			cout << "The file descriptor sockfd does not refer to a socket." << endl;

		}
		if (recvByte == -1)
			cout << "receive messages failed" << endl;

		/* sure received whole packets  simply verify */
		if (recvBuff[recvByte-1] != 0x0a)
			continue;
		else {
			cout << "recv:" << recvBuff << " :from:" << inet_ntoa(sockAdr.sin_addr) << ntohs(sockAdr.sin_port) << endl;
			printf("\t\trecvBuff[%ld]=0x%02x\n", recvByte-1, recvBuff[recvByte-1]);
			memset(recvBuff, 0, sizeof(recvBuff));
		}
		recvByte = -1;
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); /* thread sleep 500ms */
	}
}

void tcpServer::sendSockMsg(int sockfd)
{
/*
ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
*/
	ssize_t sendByte = 0;
	char sendBuff[1024] = {0};
	while (true) {
		cout << "send:";
		char s = 0x0a;
		cin.getline((char *)sendBuff, 1024); /* input msg to send */
		strncat(sendBuff, &s, 1);
		sendByte = send(sockfd, sendBuff, strlen(sendBuff), 0);
		//sendfile();
		if (sendByte == -1 || sendByte == 0) 
			cout << "[info] send messages to server failed" << endl;
		else
			cout << "[info] send successed wait reply" << endl;
		/* show send tip */
		cout << "send:" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); /* thread sleep 500ms */
	}
}

int tcpServer::sockedConnect()
{
    int sockfd;
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		return -1;
	}
    struct sockaddr_in serverAdr;
    struct sockaddr_in sinAccept;
    memset(&serverAdr, 0, sizeof(serverAdr));
    memset(&sinAccept, 0, sizeof(sinAccept));

    serverAdr.sin_family = AF_INET;
    serverAdr.sin_port = htons(8000); /* port */
    serverAdr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* test code  */
    //cout <<"hostAdr:" <<serverAdr.sin_addr.s_addr <<"\nhostPort:" <<serverAdr.sin_port <<endl;

    /* bind socked */
    int bindStatus = bind(sockfd, (struct sockaddr*)&serverAdr, sizeof(serverAdr));
    if(bindStatus == -1){
        cout << "bind sock failed " << endl;
		return -1;
    }else{
        cout << "bind sock succeed" << endl;
    }
    /* listening mode wait for client connect */
    int listenStatus = listen(sockfd, 128); /* 128: max sock queue */
    if(listenStatus == -1){
        cout << "lestening failure" << endl;
        return -1;
    }else
        cout << "listening..." << endl;

    /* accept client to connect */
    socklen_t len = sizeof(serverAdr);

    /* accept multiple client connecting */
	int newSockfd = -1;
    while (true) {
        newSockfd = accept4(sockfd, (struct sockaddr*)&sinAccept, &len, SOCK_CLOEXEC);
        if (newSockfd == -1) {
            cout << "tcp sock:%d connect failed" << sockfd << endl;
            return -1;
        } else 
            cout << "tcp connect succeed" << endl;

		std::thread recvthread(recvSockMsg, (newSockfd));
		std::thread sendthread(sendSockMsg, (newSockfd));
		/* detach sock thread */
		recvthread.detach();
		sendthread.detach();	
    }
    close(sockfd);
	close(newSockfd);
}

int main(int argc , char * argv[])
{
    tcpServer tcpServer;
    tcpServer.sockedConnect();
}
