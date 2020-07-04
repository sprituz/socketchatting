//
//  server.c
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
    /*서버 파일 기술자*/
    int s_socket_fd;
    /*클라이언트 파일 기술자*/
    int c_socket_fd;
    /*서버 소켓과 클라이언트 소켓에 대한 정보를 저장할 구조체 선언*/
    struct sockaddr_in server_address, client_address;
    /*클라이언트 주소 크기 저장 변수*/
    int client_address_size;
    /*클라이언트로 보낼 메세지 저장 배열*/
    char Msg2Client[BUFSIZE];
    /*클라이언트에서 받아온 메세지 저장 배열*/
    char Msg2Server[BUFSIZE];
    /*port 옵션으로 받기*/
    in_port_t Port=atoi(argv[1]);
    /*클라이언트의 접속을 기다리는 서버소켓 객체 생성*/
    s_socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    printf("Server Socket Create!!!\n");
    /*서버의 IP 와 PORT 를 저장할 server_address 객체를 0으로 초기화 시킴*/
    memset(&server_address, 0, sizeof(server_address));
    /*server_address 에 서버의 주소 정보 대입*/
    server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=htonl(INADDR_ANY);
    server_address.sin_port=htons(Port);
    /*bind에 실패하면 실패메세지 출력 후 exit*/
    if(bind(s_socket_fd, (struct sockaddr*) &server_address, sizeof(server_address))==-1){
        printf("Bind Failed!!!\n");
        exit(1);
    }
    /*클라이언트의 접속을 기다리는 대기 모드로 전환*/
    if(listen(s_socket_fd, 1)==-1){
        printf("Listen Failed!!!\n");
        exit(1);
    }
    printf("Wait Client...\n");
    /*클라이언트 주소 크기 저장*/
    client_address_size = sizeof(client_address);
    /*클라이언트가 서버에 접속하면 접속을 수락함*/
    if((c_socket_fd = accept( s_socket_fd, (struct sockaddr*)&client_address, &client_address_size))==-1){
        printf("Accept Failed!!!\n");
        exit(1);
    }
    /*클라이언트 연결 성공*/
    printf("Client Connect!!!\n");
    /*클라이언트 포트번호 확인용*/
    printf("Wait for Client Message...\n");
    printf("Client Port Number: %d\n",client_address.sin_port);
    /*클라이언트로부터 "Bye" 입력받기 전까지 반복*/
    while(1){
    /*클라이언트가 전달한 메시지를 읽어 들여서 Msg2Server에 대입*/
    read(c_socket_fd, Msg2Server ,sizeof(Msg2Server));
    /*클라이언트로부터 Bye 문자열 받은 경우 종료*/
        if(strcmp(Msg2Server, "Bye\n")==0){
            break;
        }
    printf("\nFrom Client Message: %s\n",Msg2Server);
    /*버퍼 초기화*/
    memset(Msg2Server, 0, sizeof(Msg2Server));
    printf("Message To Client:");
    /*클라이언트에게 보낼 메세지 입력받고 Msg2Client에 저장*/
    fgets(Msg2Client, BUFSIZE, stdin);
    /*Msg2Client 에 저장된 메시지를 서버로 전송*/
    write(c_socket_fd, Msg2Client, sizeof(Msg2Client));
    /*버퍼 초기화*/
    memset(Msg2Client, 0, sizeof(Msg2Client));
    }
    /*클라이언트와의 접속을 종료함*/
    close(c_socket_fd);
    return 0;
}
