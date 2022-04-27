using System;
using System.Collections.Generic;
using System.Text;

using Alchemi.Core.Owner;

namespace IntergralCalculatorAlchemi
{
    [Serializable]
    class IntegralGridThread : GThread
    {

        private double a, b;

        private double deltaX = 0.001;

        private double result;

        public IntegralGridThread(double a, double b)
        {
            this.a = a;
            this.b = b;

            if (a > b)
            {
                deltaX = -0.001;
            }
            else
            {
                deltaX = 0.001;
            }
            result = 0;
        }

        public double Result
        {
            get
            {
                return this.result;
            }
        }

        private double areaOfTrapezium(double a, double b, double h)
        {
            return (a + b) * h / 2;
        }

        private double f(double x)
        {
            return x * x + Math.Sqrt(x);
        }

        public override void Start()
        {
            double temp = a;

            if (a < b)
            {
                while(temp < b)
                {
                    result += areaOfTrapezium(f(temp), f(Math.Min(temp+deltaX,b)), deltaX);
                    temp += deltaX;
                }
            }
            else
            {
                while (temp > b)
                {
                    result += areaOfTrapezium(f(temp), f(Math.Max(temp + deltaX, b)), deltaX);
                    temp += deltaX;
                }
            }
        }
    }
}
