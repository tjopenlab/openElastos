//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates how to copy datas from
//               source CarArray object to current CarArray object,and point
//               out the copy size.
//
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    Int32 i;
    BufferOf_<Int32, 10> myArray1;
    CConsole::Write("Before copy myArray1 is:");
    for (i = 0; i < 10; i++) {
        myArray1[i] = i + 10;
        CConsole::Write(myArray1[i]);
        CConsole::Write(" ");
    }
    CConsole::WriteLine("");

    BufferOf_<Int32, 5> myArray2;
    CConsole::Write("Before copy myArray2 is:");
    for (i = 0; i < 5; i++) {
        myArray2[i] = i + 20;
        CConsole::Write(myArray2[i]);
        CConsole::Write(" ");
    }
    CConsole::WriteLine("");

    myArray1.Copy(&myArray2);
    CConsole::Write("After copy 5 members myArray1 is:");
    for (i = 0; i < myArray1.GetUsed(); i++) {
   		CConsole::Write(myArray1[i]);
        CConsole::Write(" ");
    }
    CConsole::WriteLine("");
    CConsole::Write("myArray1 used = ");
    CConsole::WriteLine(myArray1.GetUsed());

    CConsole::WriteLine("");
    Int32 pn[4] = {1, 2 ,3, 4};
    CConsole::Write("Before copy pn is:");
    for (i = 0; i < 4; i++) {
        CConsole::Write(pn[i]);
        CConsole::Write(" ");
    }
    CConsole::WriteLine("");

    myArray1.Copy(pn, 4);
    CConsole::Write("After copy 4 members myArray1 is:");
    for (i = 0; i < myArray1.GetUsed(); i++) {
    	CConsole::Write(myArray1[i]);
        CConsole::Write(" ");
    }
    CConsole::WriteLine("");
    CConsole::Write("myArray1 used = ");
    CConsole::WriteLine(myArray1.GetUsed());

    return 0;
}

//==========================================================================
//Output
//
//    Before copy myArray1 is:10 11 12 13 14 15 16 17 18 19
//    Before copy myArray2 is:20 21 22 23 24
//    After copy 5 members myArray1 is:20 21 22 23 24
//    myArray1 used = 5

//    Before copy pn is:1 2 3 4
//    After copy 4 members myArray1 is:1 2 3 4
//    myArray1 used = 4
//==========================================================================
