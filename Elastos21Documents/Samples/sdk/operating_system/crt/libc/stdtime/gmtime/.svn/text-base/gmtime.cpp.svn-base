//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================



#include <stdio.h>
#include <time.h>
  

int main(void)
{
struct tm *local;
time_t t;
t=time(NULL);
local=localtime(&t);
printf("Local hour is: %d\n",local->tm_hour);
local=gmtime(&t);
printf("UTC hour is: %d\n",local->tm_hour);
return 0;
}


//==========================================================================
//Output
//local hour is:11
//UTC hour is:3   
//==========================================================================
