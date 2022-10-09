namespace DATConverter
{
    internal static partial class Converter
    {
        public static Action<Context> ConvertToMapOfCSV => context =>
        {
            var data = new Dictionary<(int, int), double>();

            var xMin = int.MaxValue;
            var xMax = int.MinValue;

            var yMin = int.MaxValue;
            var yMax = int.MinValue;

            while (true)
            {
                var line = context.Input.ReadLine();
                if (line == null)
                {
                    break;
                }

                var tokens = line.Split(' ', StringSplitOptions.RemoveEmptyEntries);
                if (tokens.Length < 3)
                {
                    continue;
                }

                var x = 0;
                var y = 0;
                var z = .0;
                try
                {
                    x = (int)double.Parse(tokens[0]);
                    y = (int)double.Parse(tokens[1]);
                    z = double.Parse(tokens[2]);
                }
                catch
                {
                    continue;
                }

                if (z < -9999)
                {
                    continue;
                }

                data.Add((x, y), z);

                if (xMin > x)
                {
                    xMin = x;
                }
                else if (xMax < x)
                {
                    xMax = x;
                }

                if (yMin > y)
                {
                    yMin = y;
                }
                else if (yMax < y)
                {
                    yMax = y;
                }
            }

            context.Output.WriteLine(string.Join(',', xMin, xMax, yMin, yMax));

            for (var y = yMin; y <= yMax; y++)
            {
                var yRange = Enumerable.Range(xMin, xMax - xMin + 1);
                var values = yRange.Select(x =>
                {
                    var key = (x, y);
                    if (data.ContainsKey(key))
                    {
                        return data[key].ToString();
                    }
                    return "NaN";
                });
                context.Output.WriteLine(string.Join(',', values));
            }
        };
    }
}
