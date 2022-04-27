using System;
using System.Collections.Generic;
using Alchemi.Core.Owner;

namespace Parallel_Search_String
{
    class Program
    {
        static GApplication App;

        // Read the file as one string.
        static string text = System.IO.File.ReadAllText(@"..\..\document.txt");
        static List<string> sentences = new List<string>(text.Split('.'));
        static int NumberOfSentences = sentences.Count;
        static int SentencessPerThread = 5;
        static int NumThreads = 0;
            
        [STAThread]
        static void Main(string[] args)
        {
            // Kết nối đến Manager
            GConnection connection = GConnection.FromConsole("localhost", "9000", "user", "user");

            // Tạo đối tượng application tượng trưng cho ứng dụng mình đang chạy
            App = new GApplication(connection); // Khởi tạo
            App.ApplicationName = "The search for SAMI...";  // Gán tên của ứng dụng, tên này sẽ hiển thị trong cửa sổ Alchemi Console
            App.Manifest.Add(new ModuleDependency(typeof(StringSearchGridThread).Module));   // Thêm grid thread?

            // Tính số luông cần dùng
            NumThreads = (Int32)Math.Floor((double)NumberOfSentences / SentencessPerThread);
            if (SentencessPerThread * NumThreads < NumberOfSentences)
            {
                NumThreads++;
            }

            // Tạo và thêm các luồng
            for (int i = 0; i < NumThreads; i++)
            {
                int StartIndex = i * SentencessPerThread;
                int SentencesForThisThread = Math.Min(SentencessPerThread, NumberOfSentences - i * SentencessPerThread);

                StringSearchGridThread thread = new StringSearchGridThread(sentences.GetRange(StartIndex, SentencesForThisThread)); // Khởi tạo thread mới
                App.Threads.Add(thread);    // Thêm thread vào ứng dụng
            }

            // Các sự kiện
            App.ThreadFinish += new GThreadFinish(OnThreadFinish);

            // App bắt đầu chạy
            App.Start();

            Console.ReadLine();
        }

        // Sự kiện kết thúc một thread
        static public void OnThreadFinish(GThread th)
        {
            Console.WriteLine("Thread {0} finished the job", th.Id);
            StringSearchGridThread thread = (StringSearchGridThread)th;
            foreach (int i in thread.Result)
            {
                if (i == -1)
                {
                    Console.WriteLine("NULL");
                }
                else
                {
                    Console.WriteLine(i);
                }

            }


        }
    }
}
