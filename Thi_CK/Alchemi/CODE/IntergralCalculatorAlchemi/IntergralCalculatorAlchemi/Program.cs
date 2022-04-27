using System;
using System.Collections.Generic;
using System.Text;

using Alchemi.Core.Owner;
using Alchemi.Core.Utility;

namespace IntergralCalculatorAlchemi
{
    class Program
    {

        static GApplication App;

        static double a = 0, b = 3;

        static int numOfThreads = 10;

        static double rangePerThreads = (b-a)/numOfThreads;

        [STAThread]
        static void Main(string[] args)
        {

            try
            {

                GConnection gConnection = GConnection.FromConsole("localhost", "9000", "user", "user");

                App = new GApplication(gConnection);

                App.ApplicationName = "Integral Calculator Application";
                App.Manifest.Add(new ModuleDependency(typeof(IntegralGridThread).Module));

                for(int i =0; i < numOfThreads; i++)
                {
                    double startA = a + i * rangePerThreads;
                    double startB = startA + rangePerThreads;

                    IntegralGridThread thread = new IntegralGridThread(startA, startB);

                    App.Threads.Add(thread);
                }

                App.ThreadFinish += new GThreadFinish(onThreadFinish);
                App.ApplicationFinish += new GApplicationFinish(onApplicationFinish);

                App.Start();

                Console.ReadLine();

            }
            catch(Exception e)
            {
                Console.WriteLine(e.ToString());
            }


        }

        static void onThreadFinish(GThread th)
        {
            Console.WriteLine("Thread {0} is finished", th.Id);
            IntegralGridThread thread = (IntegralGridThread)th;
            Console.WriteLine(thread.Result);
        }

        static void onApplicationFinish()
        {
            double result = 0;
            for(int i =0; i< App.Threads.Count; i++)
            {
                IntegralGridThread thread = (IntegralGridThread)App.Threads[i];
                result += thread.Result;
            }
            Console.WriteLine(result);
            Console.WriteLine("Appcation finished!!!");
        }
    }
}
