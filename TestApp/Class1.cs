using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace TestApp
{
    public static class Native
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static void PrintMethod(string msg);
    }

    public static class Lib
    {
       
        public static void test()
        {
            Native.PrintMethod("Hello from C# \n");
        }
    }
}
