/*********************************************************
*
* Description: as socket raw , recvive all packets data 
* 				which through network card(MAC), parse protocol-packet and Combined protoclo-packet
*				such as tcp/ip udp icmp arp and so on
*
* Datetime: Tuesday April 19 2022
*
* Author: jiangxiaoyu
*
* Email: 1725087341@qq.com
*
****************************************************************/


#include <iostream>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/ether.h>
#include <netdb.h>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <linux/if_link.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/ip.h>
#include <netinet/if_ether.h>

using namespace std;





/* MAC header */

/* byte
|----- 6 -------|------ 6 ------|-- 2 --|

----------------|---------------|-------|
|des addr	| src addr	| type	|
|---------------|---------------|-------|

*/

struct{
	unsigned char DesMacAddr[6];  // 6 byte desmac address
	unsigned char SrcMacAddr[6];  //6 byte src mac address
	unsigned short NetworkType; // 2 byte network type
}mac_header, *pmac_header;


/* ip packet */

/*

---------------------------------------------32 bits--------------------------------------------|
|--------- 8 ------------|--------- 8 ----------|--------- 8 ----------|----------- 8 ----------|
|------------------------|----------------------|----------------------|------------------------|
| version   | header len | 	server type 	|		total len			|
|-----------|------------|----------------------|-------------|---------------------------------|
|		   identifier	   	 	|	flag  |    	offest	    		|
|-----------------------------------------------------------------------------------------------|
|      TTL |			protocol	|		checksum|
|------------------------|----------------------|-----------------------------------------------|
|					source IP						|
|-----------------------------------------------------------------------------------------------|
|					destination IP						|
|-----------------------------------------------------------------------------------------------|
|				optional				|	fill		|
|-----------------------------------------------------------------------|-----------------------|

*/

/*

- 1| - 2| --4| --6| --8| -9| -10| --12| ----16| ----20|
2 + 2 + 2 + 2 + 2  + 2 + 4 + 4 = 20(bytes)

*/

#pragma pack(4)
struct{
#if defined (__BIG_ENDIAN_BITFIELD)
	unsigned short version : 4;	/* 0 - 3  */ 
	unsigned short header_len : 4;	/* 4 - 7  */
#elif defined(__LITTLE_ENDIAN_BITFIELD)
	unsigned short header_len : 4;	/* 0 - 3 */
	unsigned short version : 4;	/* 4 - 7 */
#endif
	unsigned short server_type : 8; /* 8 - 15 */
	unsigned short total_len ;
	unsigned short identidier;
#if defined (__BIG_ENDIAN_BITFIELD)
	unsigned short flag : 4;	/* 0 - 3  */
	unsigned short offest : 12;	/* 4 - 15 */
#elif defined(__LITTLE_ENDIAN_BITFIELD)
	unsigned short offest :4;
	unsigned short flag : 12;
#endif
	unsigned char ttl;			
	unsigned char protocol;
	unsigned short checksum;
	unsigned int src_addr;
	unsigned int des_addr;
}*p_ipheader, ip_header;
#pragma pack() // cancel 



/* ICMP  

----------- 32 bits -------------
|-- 8 --|-- 8 --|----- 16 ------|
|-------|-----------------------|
| type	| code	| checksum	|
|-------------------------------|
|identifier	| serial number	|
|---------------|---------------|
|date				|
|-------------------------------|

*/


struct{
	unsigned char type;
	unsigned char code;
	unsigned char checksum;
	unsigned short identifier;
	unsigned short serNum;
}*p_icmpHeader, icmpHeader;






/* TCP 

|---------------------------- 32 bits --------------------------|
|------ 8 ------|----- 8 -------|----- 8 ------|-------	8 ------|

|---------------------------------------------------------------|
|	source port		|	destination port	|
|-------------------------------|-------------------------------|
|			serial number				|
|---------------------------------------------------------------|
|			ack number				|
|---------------------------------------------------------------|
| hd_len|  res	|	flag	|	windows size		|
|---------------------------------------------------------------|
|	  	checksum	|	urgent point		|
|---------------------------------------------------------------|
|	... optional fill......					|
-----------------------------------------------------------------
*/


/* TCP struct */
struct{
	unsigned short srcPort;
	unsigned short desPort;
	unsigned int serialNum;
	unsigned int acknowledgeNum;
#if defined (__BIG_ENDIAN_BITFIELD)
	unsigned short headerLen : 4;	/* 0 - 3 */
	unsigned short reserve : 4;	/* 4 - 7 */
#elif defined(__LITTLE_ENDIAN_BITFIELD)
	unsigned short reserve : 4;	/* 0 - 3 */
	unsigned short headerLen : 4;	/* 4 - 7 */
#endif
	unsigned short flag : 8;	/* 8 - 15 */
	unsigned short windowSize;
	unsigned short checksum;
	unsigned short urgPoint;
}*p_tcpHeader, tcpHeader;


/* header len */

struct{
	unsigned short macHeader_len;
	unsigned short ipHeader_len;
	unsigned short ipSrcAdrLen;
	unsigned short ipDesAdrLen;
	unsigned short icmpHeaderLen;
	unsigned short tcpHeaderLen;
}*p_headerLen, headerLen={
			.macHeader_len = sizeof(mac_header),
			.ipHeader_len = sizeof(ip_header),
			.ipSrcAdrLen = sizeof(ip_header.src_addr),
			.ipDesAdrLen = sizeof(ip_header.des_addr),
			.icmpHeaderLen = sizeof(icmpHeader),
			.tcpHeaderLen = sizeof(tcpHeader)
			};

class sockManage{

public:
	explicit sockManage();
	~sockManage();
public:
	int recvByte;
	int sock_protocol_parse(const char *msg);
private:
	int macHeader();
	int ipHeader();
	
	/* sock packge  */
	int arp_package();
	int icmp_package();

	/* sock packet paser */
	int rarp_packet_pasre(const char *msg);
	int icmp_packet_pasre(const char *msg);
	int arp_packet_pasre(const char *msg);
	int ip_packet_pasre(const char * msg);
	int tcp_packet_pasre(const char * msg);
	int udp_packet_pasre(const char * msg);

};



sockManage::sockManage():recvByte(0)
{

}


sockManage::~sockManage()
{

}



int sockManage::arp_packet_pasre(const char *msg)
{
	cout << "\n arp packet" << endl;
	return 0;
	struct in_addr src_adr, des_adr;
	p_headerLen = &headerLen;

	memset(pmac_header, 0, sizeof(*pmac_header));
	memset(p_ipheader, 0, sizeof(*p_ipheader));

	cout << "\nDES_MAC: ";
	memcpy(pmac_header, msg, p_headerLen->macHeader_len);
	for (int i = 0; i < 6; i++) {
		printf("%02x:", (unsigned char)pmac_header->DesMacAddr[i]);
	}
	cout << "\nSRC_MAC: ";
	for (int i = 0; i < 6; i++) {
        	printf("%02x:", (unsigned char)pmac_header->SrcMacAddr[i]);
	}
	memcpy(p_ipheader, &msg[p_headerLen->macHeader_len-1], p_headerLen->ipHeader_len);
	

}


int sockManage::ip_packet_pasre(const char *msg)
{
	

	cout << "\t\tipHeader_len:" << dec << p_headerLen->ipHeader_len << endl;
	cout << "\t\tmacHeader_len:" << dec << p_headerLen->macHeader_len << endl;

	struct in_addr src_adr, des_adr = {0};
	p_headerLen = &headerLen;
	memset(p_ipheader, 0, sizeof(ip_header));
	
	memcpy(p_ipheader, &msg[p_headerLen->macHeader_len], p_headerLen->ipHeader_len);
	memcpy(&src_adr, &p_ipheader->src_addr, p_headerLen->ipSrcAdrLen);
	memcpy(&des_adr, &p_ipheader->des_addr, p_headerLen->ipDesAdrLen);

	
	
	printf("version:%d\n", p_ipheader->version);
	printf("header_len:%d\n", p_ipheader->header_len);
	printf("server_type:%d\n", p_ipheader->server_type);
	printf("total_len:%d\n", ntohs(p_ipheader->total_len));
	printf("flag:%d\n", p_ipheader->flag);
	printf("ttl:%d\n", p_ipheader->ttl);
	printf("dataLen:%d\n", ntohs(p_ipheader->total_len) - p_ipheader->header_len * 4);
	
	cout << "src_ip:" << inet_ntoa(src_adr) << endl;
	cout << "des_ip:" << inet_ntoa(des_adr) << endl;
	
	/* ip header len = headerLen * 4  max(headerLen):1111(b)/15(d) */
	unsigned short ipHeaderLen = p_ipheader->header_len * 4;
	if ( ipHeaderLen < 20 | ipHeaderLen > 60)
		printf("ip header(%d) less 20bytes , so fill %d bytes\n", 20 - p_ipheader->header_len);

	switch (static_cast<unsigned short>(p_ipheader->protocol)) {
	case IPPROTO_ICMP:
        	printf("ICMP protocol\n");
		icmp_packet_pasre(&msg[p_headerLen->macHeader_len + p_headerLen->ipHeader_len]);
        	break;
    	case IPPROTO_IGMP:
        	printf("IGMP protocol\n");
        	break;
	case IPPROTO_IPIP:
        	printf("IPIP protocol\n");
        	break;
    	case IPPROTO_TCP :
		tcp_packet_pasre(&msg[p_headerLen->macHeader_len + p_headerLen->ipHeader_len]);
		break;
	default:
		printf("unknow protocol:0x%02x:\n", p_ipheader->protocol);
		break;
	}

	
}

int sockManage::rarp_packet_pasre(const char *msg)
{
	cout << "rarp packet" << endl;
	return 0;
	struct in_addr src_adr, des_adr;
	p_headerLen = &headerLen;

	memset(pmac_header, 0, sizeof(*pmac_header));
	memset(p_ipheader, 0, sizeof(*p_ipheader));

	cout << "\nDES_MAC: ";
	memcpy(pmac_header, msg, p_headerLen->macHeader_len);
	for (int i = 0; i < 6; i++) {
		printf("%02x:", (unsigned char)pmac_header->DesMacAddr[i]);
	}
	cout << "\nSRC_MAC: ";
	for (int i = 0; i < 6; i++) {
        	printf("%02x:", (unsigned char)pmac_header->SrcMacAddr[i]);
	}
	memcpy(p_ipheader, &msg[p_headerLen->macHeader_len-1], p_headerLen->ipHeader_len);
	
	
}


int sockManage::tcp_packet_pasre(const char *msg)
{	
	p_tcpHeader = &tcpHeader;
	memset(p_tcpHeader, 0, p_headerLen->tcpHeaderLen);
	memcpy(p_tcpHeader, msg, p_headerLen->tcpHeaderLen);
	
	char data[1024] = {0};
	memcpy(data, &msg[p_headerLen->tcpHeaderLen], 1024);
	/* big endian to little endian
	unsigned short src_port, temp = 0;
	temp = (src_port | msg[0] &0x00FF) << 8;
	src_port = (temp & 0xFF00) | msg[1];
	*/

	unsigned int dataLen = this->recvByte - (p_headerLen->tcpHeaderLen +
		       		p_headerLen->macHeader_len + p_headerLen->ipHeader_len);

	cout << "TCP portocol" << endl;
	cout << "\t\trecvByte:" << this->recvByte << endl;
	cout << "\t\tdata size:" << dataLen << endl;
	cout << "\t\tsrc_port:" << ntohs(p_tcpHeader->srcPort) << endl;
	cout << "\t\tdes_port:" << ntohs(p_tcpHeader->desPort) << endl;
	cout << "\t\theaderLen:" << p_tcpHeader->headerLen * 4 << endl;
	cout << "\t\tacknowledge number:" << ntohs(p_tcpHeader->acknowledgeNum) << endl;
	cout << "\t\tflag:" << p_tcpHeader->flag << endl;

	cout << "recvdata:";
	for (int i = 0; i < dataLen - 1; i++)
		printf(" 0x%0x2", (unsigned char)data[i]);
	cout << endl;
} 



int sockManage::sock_protocol_parse(const char *msg)
{
	struct in_addr src_adr, des_adr;
	p_headerLen = &headerLen;

	memset(pmac_header, 0, sizeof(mac_header));

	cout << "\nDES_MAC: ";
	memcpy(pmac_header, msg, p_headerLen->macHeader_len);
	for (int i = 0; i < 6; i++) {
		printf("%02x:", (unsigned char)pmac_header->DesMacAddr[i]);
	}
	cout << "\nSRC_MAC: ";
	for (int i = 0; i < 6; i++) {
        	printf("%02x:", (unsigned char)pmac_header->SrcMacAddr[i]);
	}
	
	cout << hex << "\nnet type:" << ntohs(pmac_header->NetworkType) << endl;
	/*  byte order convert , network to host */
	switch (ntohs(pmac_header->NetworkType)) {
	case 0x0800:
		ip_packet_pasre(msg);
		break;
	case 0x0806:
		arp_packet_pasre(msg);
		break;
	case 0x0835:
		rarp_packet_pasre(msg);
		break;
	default:
		cout << "\nunknow protocol packet:" << hex << ntohs(pmac_header->NetworkType) << endl;
		break;
	}
	

	return 0;
}



int sockManage::icmp_packet_pasre(const char *msg)
{
	char bf[1024] = {0};
	p_icmpHeader = &icmpHeader;
	memset(p_icmpHeader, 0, p_headerLen->icmpHeaderLen);
	memcpy(p_icmpHeader, msg, p_headerLen->icmpHeaderLen);
	memcpy(bf, &msg[p_headerLen->icmpHeaderLen-1], sizeof(bf));

	printf("\n\t\ttype:%d\n", p_icmpHeader->type);
	for (int i = 0; i < strlen(bf); i++) 
		printf("\t\tdate:%c", bf[i]);
	
}



int main(int argc, char * argv[])
{
	sockManage sockmg;
	p_ipheader = &ip_header;
	pmac_header = &mac_header;

	char recvBuff[1024] = {0};
	ssize_t recvByte = 0;
	struct sockaddr_in sockAdr;
	socklen_t len = sizeof(sockAdr);
	memset(&sockAdr, 0, sizeof(sockAdr));
	memset(&mac_header, 0, sizeof(mac_header));
	memset(&ip_header, 0, sizeof(ip_header));

	/* int socket(int domain, int type, int protocol); */

	/* family:
		
		PF_PACKET : link layer
		AF_INET   : network layer /ipv4
		AF_INET   : network layer /ipv6 
	*/		
	
	/*type
	
	
	*/
	int sockrawfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sockrawfd == -1) {
		std::cout << "sock raw create failed" << endl;
		return -1;	
	} else
		std::cout << "sock raw created succeed" << endl;

	struct ifreq ifstruct;
	struct sockaddr_in serverAdr;
	
	memset(&serverAdr, 0, sizeof(serverAdr));
	memset(&ifstruct, 0, sizeof(ifstruct));
    	serverAdr.sin_family = AF_PACKET;
    	serverAdr.sin_port = htons(ETH_P_ALL); /* all port */
    	serverAdr.sin_addr.s_addr = htonl(INADDR_ANY);

/*
	if (setsockopt(sockrawfd, SOL_SOCKET, SO_BINDTODEVICE, &ifstruct, sizeof(ifstruct)) < 0)
	{
		cout << "socket setsockopt error" << endl;
		printf("bind interface fail, errno: %d \r\n", errno);
    	close(sockrawfd);
    	return -2;
	}

	addr_ll.sll_ifindex = ifstruct.ifr_ifindex;

*/
	while (true) {
	
		recvByte = recvfrom(sockrawfd, recvBuff, sizeof(recvBuff), 0, (struct sockaddr *)&sockAdr, &len);
		
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
		if (recvByte == -1) {}
		else {
			cout << "==========================================" << endl;
			sockmg.recvByte = recvByte;
			sockmg.sock_protocol_parse(recvBuff);
			memset(recvBuff, 0, sizeof(recvBuff));
		}
		recvByte = -1;
		std::this_thread::sleep_for(std::chrono::milliseconds(1*1000)); /* thread sleep 500ms */
	}
}
