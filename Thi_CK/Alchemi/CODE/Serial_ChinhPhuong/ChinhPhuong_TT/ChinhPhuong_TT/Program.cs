using System;
using System.Collections.Generic;
using System.Text;

namespace ChinhPhuong_TT
{
    class Program
    {
        static void lietKeChinhPhuong(int n)
        {
            for (int i = 1; i <= n; i++)
            {
                if (Math.Sqrt(i) == (int)Math.Sqrt(i))
                    Console.Write(i + " ");
            }
        }
        static void Main(string[] args)
        {
            int n = 24;
            lietKeChinhPhuong(n);
            Console.ReadLine();
        }
    }
}
