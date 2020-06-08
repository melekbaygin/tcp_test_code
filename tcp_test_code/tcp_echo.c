#include <string.h>
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/GPIO.h>
#include <ti/sysbios/knl/Semaphore.h>

#include <netmain.h>
#include <stkmain.h>
#include <stdio.h>
#include "Board.h"
#include "tcp_test.h"
#include <stdint.h>
#include "ti/drivers/emac/EMACSnow.c"
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>



#define tcp_paket_boyutu 256
#define tcp_kuyruk_sayisi 3

/*STKEVENT_Handle hEvent;
STKEVENT  stkEvent;
Semaphore_Handle hSem;*/

Void tcpHandler(UArg arg0, UArg arg1)
{
    tcp_server_kurulum(arg0, arg1);
}


/*static char *TaskName[] = { "Telnet","HTTP","NAT","DHCPS","DHCPC","DNS" };
static char *ReportStr[] = { "","Running","Updated","Complete","Fault" };
static char *StatusStr[] = { "Disabled", "Waiting", "IPTerm", "Failed", "Enabled" };
static void ServiceReport( uint Item, uint Status, uint Report, HANDLE h )
{
printf( "Service Status: %-9s: %-9s: %-9s: %03d\n",
TaskName[Item-1], StatusStr[Status], ReportStr[Report/256], Report&0xFF );
}*/


Void cihaziciTest(UArg arg0)
{
    /*CI_IPNET cip;
    unsigned char test1=cip.IPAddr;
    CISARGS cis;
    unsigned char test=cis.Status;*/

    /*STKEVENT_init(hEvent,hSem);
    STKEVENT_signal(hEvent,STKEVENT_LINKDOWN,0);*/

    /*CI_SERVICE_TELNET telnet;
    bzero( &telnet, sizeof(telnet));
    telnet.cisargs.Mode=CIS_FLG_IFIDXVALID;
    telnet.cisargs.pCbSrv = &ServiceReport;*/

    /*CI_SERVICE_DHCPC dhcpc;
    bzero( &dhcpc, sizeof(dhcpc) );
    dhcpc.cisargs.Mode = CIS_FLG_IFIDXVALID;
    //dhcpc.cisargs.IfIdx = dhcpIdx;
    dhcpc.cisargs.pCbSrv = &ServiceReport;*/
    /*CfgAddEntry( hCfg, CFGTAG_SERVICE, CFGITEM_SERVICE_TELNET, 0,
    sizeof(telnet), (unsigned char *)&telnet, 0 );*/
    //cis.Item=CFGITEM_SERVICE_DHCPCLIENT;
    //EMACSnow_NIMUInit(hEvent);
    EMACSnow_init(NULL);
    EMACSnow_isLinkUp(NULL);
    /*if(NC_OPMODE_INTERRUPT && !(hSem = SemCreate(0)) )

      // Initialize our Event object
      STKEVENT_init( &stkEvent, hSem );
      //STKEVENT_signal(&stkEvent,STKEVENT_LINKUP,0);
      STKEVENT_signal(&stkEvent,STKEVENT_LINKDOWN,0);
      if (stkEvent.hSemEvent==STKEVENT_LINKUP) {

          puts("cablebağlı");
      }
      else {

          puts("cablebağsız");
      }*/
}

int main(void)
{
    Board_initGeneral();
    Board_initGPIO();
    Board_initEMAC();

    /*Task_Handle taskHandle;
    Task_Params taskParams;
    Error_Block eb;
    Error_init(&eb);*/

    /*Task_Params_init(&taskParams);
    taskParams.stackSize = 1024;
    taskParams.priority = 2;
    taskHandle = Task_create((Task_FuncPtr)cihaziciTest, &taskParams, &eb);
    if (taskHandle == NULL) {
        System_printf("cihaziciTest: Cihaz içi test taskı oluşturulamadı\n");
    }*/


    System_flush();
    BIOS_start();
    return (0);
}


