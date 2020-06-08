/*
 * tcp_test.c
 *
 *  Created on: Mar 4, 2020
 *      Author: mustafa
 */

#include "tcp_library.h"
#include <stdio.h>

int                status;
int                clientfd;
int                server;
struct sockaddr_in localAddr;
struct sockaddr_in clientAddr;
int                optval;
int                optlen = sizeof(optval);
socklen_t          addrlen = sizeof(clientAddr);
Task_Handle        taskHandle;
Task_Params        taskParams;
Task_Handle        taskHandle1;
Task_Params        taskParams1;
Error_Block        eb;

enum HataEnum
{
    TCP_Connect_Error=001,
    TCP_Sent_Error=002,
    TCP_Receive_Error=003,
};
struct HataStruct
{
    unsigned char toplamHata;
    unsigned char hataKodu;
    unsigned char hataAdeti;
    unsigned char histerisis;
    unsigned char hataZamani;
};

tRingBufObject RingBuf;
struct HataStruct HataStruct;
#define tcp_paket_boyutu 256
#define tcp_kuyruk_sayisi 3

Void cihaziciTest(UArg arg0);

Void tcpWorker(UArg arg0, UArg arg1)
        {
            int  clientfd = (int)arg0;
            int  bytesRcvd;
            int  bytesSent;
            unsigned char buffer[tcp_paket_boyutu];
            RingBufInit(&RingBuf,buffer, sizeof(buffer));

            System_printf("tcpWorker: başlatıldı clientfd = 0x%x\n", clientfd);

            while ((bytesRcvd = recv(clientfd, buffer, tcp_paket_boyutu, 0)) > 0)
            {
                bytesSent = send(clientfd, buffer, bytesRcvd, 0);
                if (bytesSent < 0 || bytesSent != bytesRcvd)
                {
                    System_printf("Hata: Send edilemedi.\n");
                    break;
                }
            }
            System_printf("tcpWorker: durduruldu clientfd = 0x%x\n", clientfd);
            close(clientfd);
        }

void tcp_server_kurulum(UArg arg0, UArg arg1)
{
        server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (server == -1) {
            System_printf("Hata: Soket oluşturulamadı.\n");
            goto shutdown;
        }

        memset(&localAddr, 0, sizeof(localAddr));
        localAddr.sin_family = AF_INET;
        localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        localAddr.sin_port = htons(arg0);

        status = bind(server, (struct sockaddr *)&localAddr, sizeof(localAddr));
        if (status == -1) {
            System_printf("Hata: Server/Client kurulumu yapılamadı.\n");
            goto shutdown;
        }

        status = listen(server, tcp_kuyruk_sayisi);
        if (status == -1) {
            System_printf("Hata: Dinleme yapılamıyor.\n");
            goto shutdown;
        }

        optval = 1;
        if (setsockopt(server, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
            System_printf("Hata: Socket kurulumu yapılamadı.\n");
            goto shutdown;
        }
        while ((clientfd = accept(server, (struct sockaddr *)&clientAddr, &addrlen)) != -1)
        {
                Error_init(&eb);
                Task_Params_init(&taskParams);
                taskParams.arg0 = (UArg)clientfd;
                taskParams.stackSize = 1280;

                Error_init(&eb);
                Task_Params_init(&taskParams1);
                taskParams.arg0 = (UArg)clientfd;
                taskParams.stackSize = 1280;
                taskHandle1 = Task_create((Task_FuncPtr)cihaziciTest, &taskParams, &eb);


                taskHandle = Task_create((Task_FuncPtr)tcpWorker, &taskParams, &eb);
                if (taskHandle == NULL)
                {
                    System_printf("Hata: Yeni task oluşturulamadı\n");
                    close(clientfd);
                }

        }

        addrlen = sizeof(clientAddr);
        shutdown:
        if (server > 0)
        {
            close(server);
        }
}






