//==========================================================================
// 科泰世纪科技有限公司 版权所有 2000年--2004年
// Copyright (c) 2000-2004,  KoreTide Corp.  All Rights Reserved.
//==========================================================================
#include <elastos.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

IDriver *pDevice = NULL;

void help(char* cmd)
{
    printf("\rCommand <%s> Help Message:\n \
            \r  /f0 Get LCD FrameBuffer!\n \
            \r  /f1 Turn On BackLight!\n \
            \r  /f2 Turn Off BackLight!\n \
            \r  /f3 LCD Suspend Graceful!\n \
            \r  /f4 LCD Suspend Immediate!\n \
            \r  /f5 LCD Resume!\n \
            \r  /f6 LCD Resume & Init ToshibaVGA!\n \
            \r  /f7 Get PWM_OUT<x> Registers Value!\n \
            \r      eg: Cmd /f6 <x>\n \
            \r  /f8 Set PWM_OUT<x> Registers Value!\n \
            \r      eg: Cmd /f7 <x> v1 v2 v3\n \
            \r  /f9 Edit Customer Registers Value!\n \
            \r      eg: Cmd /f8 Reg Value \n \
            \r  /fa Read Customer Registers Value!\n \
            \r      eg: Cmd /f9 Reg\n \
            \r  /fb Dump GPIO Registers Value!\n \
            \r  /fc Turn Off KeyPad LED!\n \
            \r  /fd Turn On  KeyPad LED!\n",
            cmd);
}

void DumpGpio(long* value)
{
    printf("GPLR0 : %08x\n", value[0]);
    printf("GPLR1 : %08x\n", value[1]);
    printf("GPLR2 : %08x\n", value[2]);
    printf("GPLR3 : %08x\n", value[3]);

    printf("GPDR0 : %08x\n", value[4]);
    printf("GPDR1 : %08x\n", value[5]);
    printf("GPDR2 : %08x\n", value[6]);
    printf("GPDR3 : %08x\n", value[7]);

    printf("GRER0 : %08x\n", value[8]);
    printf("GRER1 : %08x\n", value[9]);
    printf("GRER2 : %08x\n", value[10]);
    printf("GRER3 : %08x\n", value[11]);

    printf("GFER0 : %08x\n", value[12]);
    printf("GFER1 : %08x\n", value[13]);
    printf("GFER2 : %08x\n", value[14]);
    printf("GFER3 : %08x\n", value[15]);

    printf("GEDR0 : %08x\n", value[16]);
    printf("GEDR1 : %08x\n", value[17]);
    printf("GEDR2 : %08x\n", value[18]);
    printf("GEDR3 : %08x\n", value[19]);
}

long strtohex(char *str)
{
    long tmp = 0, s1;
    char *p = str;
    bool sig = false;

    while (*p != '\0') {
        s1 = *p;
        if (sig) {
            if ( (s1 >= '0') && (s1 <= '9') ) {
                s1 = s1 - '0';
            }
            else if ( (s1 >= 'a') && (s1 <= 'f') ) {
                s1 = s1 - 'a' + 10;
            }
            else if ( (s1 >= 'A') && (s1 <= 'F') ) {
                s1 = s1 - 'A' + 10;
            }
            else {
                return 0;
            }
            tmp = (tmp << 4) + s1;
        }
        else if ( (s1 == 'x') || (s1 == 'X') ) {
            sig = true;
        }
        p++;
    }

    return tmp;
}

int main(int argc, char *argv[])
{
    ECode ec;

    if (argc < 2) {
        help(argv[0]);
        return 1;
    }

    ec = CSystem::FindRunningObject(
            L"device:display0", (IInterface **)&pDevice);
    if (FAILED(ec)) {
        printf("ERROR: Can't find Service: display, ec = 0x%08x\n", ec);
        return 1;
    }
    printf("CSystem::FindRunningObject display OK!\n");

    BufferOf<Byte> ebbInData = BufferOf<Byte>::AllocByteBuf(32);
    BufferOf<Byte> ebbOutData = BufferOf<Byte>::AllocByteBuf(256);
    char *fID;
    long *value = (long*)(char*)ebbInData;
    int  pwmID;
    fID = argv[1];

    if ( ( fID[1] != '\0' ) && ( fID[2] != '\0' ) && ( fID[3] == '\0' )) {
        if ( ( fID[1] == 'f' ) || ( fID[1] == 'F' ) ) {
            switch( fID[2] ) {
                case '0':
                    printf("Function #0 Get LCD FrameBuffer Address ...!\n");
                    pDevice->Control( 3, EZBYTEBUF_NULL, ebbOutData, NULL );
                    value = (long*)(char*)ebbOutData;
                    printf( "Got LCD FrameBuffer Address : %08x\n",
                                value[0] );
                    break;

                case '1':
                    printf("Function #1 Turn On BackLight ...!\n");
                    pDevice->Control( 11, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL );
                    printf( "Turn On BackLight!\n");
                    break;

                case '2':
                    printf("Function #2 Turn Off BackLight ...!\n");
                    pDevice->Control( 12, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL );
                    printf( "Turn Off BackLight!\n");
                    break;

                case '3':
                    printf("Function #3 LCD Suspend Graceful ...!\n");
                    value[0] = 0x00;
                    ebbInData.SetUsed(4);
                    pDevice->Control( 1000, ebbInData, EZBYTEBUF_NULL, NULL );
                    printf( "LCD Suspend Graceful!\n");
                    break;

                case '4':
                    printf("Function #4 LCD Suspend Immediate ...!\n");
                    value[0] = 0x01;
                    ebbInData.SetUsed(4);
                    pDevice->Control( 1000, ebbInData, EZBYTEBUF_NULL, NULL );
                    printf( "LCD Suspend Immediate!\n");
                    break;

                case '5':
                    printf("Function #5 LCD Resume ...!\n");
                    pDevice->Control( 1001, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL );
                    printf( "LCD Resume!\n");
                    break;

                case '6':
                    printf("Function #6 LCD Resume & Init ToshibaVGA ...!\n");
                    pDevice->Control( 1002, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL );
                    printf( "LCD Resume & Init ToshibaVGA!\n");
                    break;

                case '7':
                    if ( (argc > 2) && ( argv[2][0]>= '0') && ( argv[2][0] <= '3') ) {
                        pwmID = (int)(argv[2][0] - '0');
                    }
                    else {
                        pwmID = 0;
                    }
                    value[0] = pwmID;
                    ebbInData.SetUsed(4);
                    printf("Function #7 Get PWM_OUT<%d> Registers Value ...!\n", pwmID);
                    pDevice->Control( 2002, ebbInData, ebbOutData, NULL );
                    value = (long*)(char*)ebbOutData;
                    printf( "\rPWM_OUT<%d> Address [%08x]:\n \
                            \rPWMCR %08x PWMDCR %08x PWMPCR %08x\n",
                            pwmID, value[0], value[1], value[2], value[3]);
                    break;

                case '8':
                    if ( (argc > 5) && ( argv[2][0]>= '0') && ( argv[2][0] <= '3') ) {
                        pwmID = (int)(argv[2][0] - '0');
                        value[0] = pwmID;
                        value[1] = strtohex(argv[3]);
                        value[2] = strtohex(argv[4]);
                        value[3] = strtohex(argv[5]);
                        ebbInData.SetUsed(16);
                    }
                    else {
                        printf("invaild function!\n");
                        break;
                    }
                    printf("Function #8 Set PWM_OUT<%d> Registers Value ...!\n", pwmID);
                    pDevice->Control( 2003, ebbInData, EZBYTEBUF_NULL, NULL );
                    pDevice->Control( 2002, ebbInData, ebbOutData, NULL );
                    value = (long*)(char*)ebbOutData;
                    printf( "\rPWM_OUT<%d> Address [%08x]:\n \
                            \rPWMCR %08x PWMDCR %08x PWMPCR %08x\n",
                            pwmID, value[0], value[1], value[2], value[3]);
                    break;

                case '9':
                    printf("Function #9 Edit Customer Registers Value ...!\n");
                    if ( argc > 3) {
                        value[0] = strtohex(argv[2]);
                        value[1] = strtohex(argv[3]);
                        ebbInData.SetUsed(8);
                    }
                    else {
                        break;
                    }
                    pDevice->Control( 2004, ebbInData, ebbOutData, NULL );
                    value = (long*)(char*)ebbOutData;
                    printf("Customer Change Register %08x Value To : %08x\n",
                        value[0], value[1]);
                    break;

                case 'a':
                case 'A':
                    printf("Function #a Read Customer Registers Value ...!\n");
                    if ( argc > 2) {
                        value[0] = strtohex(argv[2]);
                        ebbInData.SetUsed(4);
                    }
                    else {
                        break;
                    }
                    pDevice->Control( 2005, ebbInData, ebbOutData, NULL );
                    value = (long*)(char*)ebbOutData;
                    printf("Read Specify Register [%08x] Value : %08x\n",
                        value[0], value[1]);
                    break;

                case 'b':
                case 'B':
                    printf("Function #b Dumping GPIO Registers Value ...!\n");
                    pDevice->Control( 2006, EZBYTEBUF_NULL, ebbOutData, NULL );
                    value = (long*)(char*)ebbOutData;
                    DumpGpio(value);
                    break;

                case 'c':
                case 'C':
                    printf("Function #c Turn Off The KeyPad LED ...!\n");
                    pDevice->Control( 1003, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL );
                    break;

                case 'd':
                case 'D':
                    printf("Function #d Turn On The KeyPad LED ...!\n");
                    pDevice->Control( 1004, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL );
                    break;

                default:
                    help(argv[0]);
            }

            value = (long*)(char*)ebbInData;
            ebbOutData.SetUsed(0);
            ebbInData.SetUsed(0);
        }
        else {
            help(argv[0]);
        }
    }


    BufferOf<Byte>::FreeByteBuf(ebbInData);
    BufferOf<Byte>::FreeByteBuf(ebbOutData);
    pDevice->Release();
    return 0;
}
