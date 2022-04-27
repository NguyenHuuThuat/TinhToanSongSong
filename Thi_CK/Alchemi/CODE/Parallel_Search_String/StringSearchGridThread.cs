using System;
using System.Collections.Generic;
using Alchemi.Core.Owner;

namespace Parallel_Search_String
{
    [Serializable]
    class StringSearchGridThread : GThread
    {
        // Biến riêng
        private List<int> _Result = new List<int>();
        private int _StartIndex;
        private int _NumSentences;
        private List<string> _Sentences = new List<string>();

        // Decorator
        public List<int> Result
        {
            get
            {
                return _Result;
            }
        }

        public List<string> Sentences
        {
            get
            {
                return _Sentences;
            }
        }
        public int StartIndex
        {
            get
            {
                return _StartIndex;
            }
        }

        public int NumSentences
        {
            get
            {
                return _NumSentences;
            }
        }

        // Constructor
        public StringSearchGridThread(List<string> Sentences)
        {
            _Sentences = Sentences;
        }

        public override void Start()
        {
            for (int i = 0; i < _Sentences.Count; i++)
            {
                _Result.Add(_Sentences[i].IndexOf("SAMI", 0));
            }
        }
    }
}
