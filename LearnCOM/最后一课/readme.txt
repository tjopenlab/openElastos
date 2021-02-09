Here are the steps to program your first ezCOM component:

(1) write your own hello.cdl
(2) type "zmake hello.cdl" to generate following files:
    CHello.cpp -- C++ implementation framework
    CHello.h   -- C++ header framework
    hello.xml  -- documentation framework
    sources    -- file needed to build hello.dll component
(3) in CHello.cpp, fill in following 3 lines in CHello::Hello()
    {
        outStrBuf.Copy(inStr);
        outStrBuf.Append(L" world!");
        return NOERROR;
    }
(4) type "zmake" to build hello.dll
(5) write your test code to try out the first ezCOM component you just wrote

Congratulations!
