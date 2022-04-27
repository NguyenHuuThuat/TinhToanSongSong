using System;
using System.Collections.Generic;

namespace Serial_Search_String
{
    class Program
    {
        static void Main(string[] args)
        {
            int i, j;

            // Read the file as one string.
            string text = System.IO.File.ReadAllText(@"..\..\..\document2.txt");
            List<string> sentences = new List<string>(text.Split('.'));

            for (i = 0; i < sentences.Count; i++)
            {
                Console.WriteLine(sentences[i]);
                j = sentences[i].IndexOf("SAMI", 0);
                if (j != -1)
                {
                    Console.WriteLine("SAMI position: " + j);
                }else
                {
                    Console.WriteLine("No SAMI was found in this sentence.");
                }
            }

            // Keep the console window open in debug mode.
            Console.WriteLine("Press any key to exit.");
            System.Console.ReadKey();
        }
    }
}
