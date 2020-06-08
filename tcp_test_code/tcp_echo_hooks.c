//#include "tcp_library.h"
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* NDK Header files */
#include <netmain.h>
#include <stkmain.h>
#include <stdio.h>

#define TCPPORT 1000
#define TCPHANDLERSTACK 1024

Void tcpHandler(UArg arg0, UArg arg1);
//Void ti_ndk_config_Global_serviceReport(void);
HANDLE hCfg, *phCfgEntry;
UINT8 *pData;

void netOpenHook()
{
    Task_Handle taskHandle;
    Task_Params taskParams;
    Error_Block eb;
    Error_init(&eb);

    //CfgSetDefault(hCfg);

    Task_Params_init(&taskParams);
    taskParams.stackSize = TCPHANDLERSTACK;
    taskParams.priority = 1;
    taskParams.arg0 = TCPPORT;
    taskHandle = Task_create((Task_FuncPtr)tcpHandler, &taskParams, &eb);

    if (taskHandle == NULL) {
        System_printf("netOpenHook: Failed to create tcpHandler Task\n");
    }
    System_flush();

    //CfgAddEntry(hCfg, CFGTAG_SERVICE, CFGITEM_SERVICE_DHCPSERVER, CIS_FLG_IFIDXVALID, 2048,pData,NULL);
    //CfgAddEntry(hCfg, CFGTAG_SERVICE, CFGITEM_SERVICE_DHCPSERVER,  CIS_FLG_IFIDXVALID, int Size, pData, *phCfgEntry );
}

CI_SERVICE_DHCPC dhcpc;
/*void netReportHook(CFGITEM_SERVICE_DHCPCLIENT, dhcpc.cisargs.Status, dhcpc.cisargs.ReportCode, hCfg)
{
    CI_SERVICE_DHCPC dhcpc;
    bzero( &dhcpc, sizeof(dhcpc));
}*/
void netIPAddrHook(unsigned int IPAddr, unsigned int IfIdx, unsigned int fAdd)
{
    /*static Task_Handle taskHandle;
    Task_Params taskParams;
    Error_Block eb;*/

    /* Create a HTTP task when the IP address is added */
    if (fAdd) {
        puts("cable bağlı");

        /*Task_Params_init(&taskParams);
        taskParams.stackSize = HTTPTASKSTACKSIZE;
        taskParams.priority = 1;
        taskHandle = Task_create((Task_FuncPtr)httpTask, &taskParams, &eb);
        if (taskHandle == NULL) {
            printError("netIPAddrHook: Failed to create HTTP Task\n", -1);
        }*/
    }
    else
    {

        //puts("cable bağsız");
    }
}





