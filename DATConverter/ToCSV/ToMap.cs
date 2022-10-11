namespace DATConverter
{
    internal static partial class Converter
    {
        public static Action<Context> ConvertToMapOfCSV => context =>
        {
            var data = new Dictionary<(int, int), double>();

            var minX = int.MaxValue;
            var maxX = int.MinValue;

            var minY = int.MaxValue;
            var maxY = int.MinValue;

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

                if (minX > x)
                {
                    minX = x;
                }
                else if (maxX < x)
                {
                    maxX = x;
                }

                if (minY > y)
                {
                    minY = y;
                }
                else if (maxY < y)
                {
                    maxY = y;
                }
            }

            context.Output.WriteLine(string.Join(',', minX, maxX, minY, maxY));

            for (var y = minY; y <= maxY; y++)
            {
                var yRange = Enumerable.Range(minX, maxX - minX + 1);
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
