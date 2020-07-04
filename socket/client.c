//
//  client.c
//  socket
//
//  Created by 이다연 on 13/06/2020.
//  Copyright © 2020 이다연. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
/*버퍼 사이즈 1024*/
#define BUFSIZE 1024
int main(int argc,char* argv[]){
    /*클라이언트 소켓 선언*/
    int clientSocket;
    /*서버 소켓의 IP,port등의 정보를 저장할 구조체 선언*/
    struct sockaddr_in server_address;
    /*서버로 보낼 메세지 저장 배열*/
    char toServer[BUFSIZE];
    /*서버에서 받아온 메세지 저장 배열*/
    char fromServer[BUFSIZE];
    /*서버 ip 옵션으로 받기*/
    char* serverIP=argv[1];
    /*port 옵션으로 받기*/
    in_port_t Port=atoi(argv[2]);
    /*서버에 접속해서 데이터를 입출력 하는 클라이언트 소켓생성*/
    clientSocket=socket(PF_INET, SOCK_STREAM, 0);
    printf("Create Client Socket!!\n");
    
    /*서버의 주소 정보가 저장될 server_adress 를 0으로 초기화*/
    memset(&server_address, 0, sizeof(server_address));
    
    /*server_address 에 서버의 주소 정보 대입*/
    server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=inet_addr(serverIP);
    server_address.sin_port=htons(Port);
    
    /*서버에 접속 실패하면 실패메세지 출력 후 exit*/
    if(connect(clientSocket, (struct sockaddr*)&server_address, sizeof(server_address))==-1){
        printf("Connect Failed!!!\n");
        exit(1);
    }
    /*서버와 연결 성공하면 출력되는 메세지*/
    printf("Connect Server!!\n");
    /*Bye 문자열 보내기까지 반복문*/
    while(1){
    
    printf("To Server Message: %s",toServer);
    /*서버로 보낼 문자열 입력받고 toServer에 저장*/
    fgets(toServer, BUFSIZE, stdin);
    /*toServer 에 저장된 메시지를 서버로 전송*/
    write(clientSocket,toServer,sizeof(toServer));
    /*서버로 Bye 를 보낸 경우 종료*/
    if(strcmp(toServer, "Bye\n")==0){
            break;}
    /*toServer 초기화*/
    memset(toServer, 0, sizeof(toServer));
    /*서버에서 보내온 메시지를 fromServer 에 저장 후 출력*/
    read(clientSocket, fromServer, sizeof(fromServer));
    printf("\nFrom Server Message: %s\n",fromServer);
    /*fromServer 초기화*/
    memset(fromServer, 0, sizeof(fromServer));
    }
    /*소켓 닫기*/
    close(clientSocket);
    
    return 0;
}
