#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h> // 套接字结构

int main(){
	// 客户端创建socket套接字
	printf("客户端创建套接字\n");
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		perror("socket error");
		return -1;
	}
		
	// 创建服务器地址结构
	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(8080);
	ser.sin_addr.s_addr = inet_addr("127.0.0.1");
		
	// 客户端发送连接
	int rc = connect(sockfd,(struct sockaddr*)&ser,sizeof(ser));
	if(rc==-1){
		perror("connect error");
		return -1;
	}	
	
	// 业务处理
	char buf[128]="apple come on";
	int rs = send(sockfd,buf,strlen(buf),0);
	if(rs == -1){
		perror("send error");
		return -1;
	}

	ssize_t size = recv(sockfd,buf,sizeof(buf)-sizeof(buf[0]),0);
	if(size == -1){
		perror("recv error");
		return -1;
	}
	printf("客户端接收到 %s\n",buf);

	// 关闭套接字
	printf("客户端关闭套接字\n");
	close(sockfd);	
	return 0;
}
