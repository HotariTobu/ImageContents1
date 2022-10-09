namespace DATConverter
{
    internal static partial class Converter
    {
        public static Action<Context> ConvertToBarOfOBJ => context =>
        {
            for (var i = 0; true; i++)
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

                var x = .0;
                var y = .0;
                var z = .0;
                try
                {
                    x = double.Parse(tokens[0]);
                    y = double.Parse(tokens[1]);
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

                var v0 = 1 + i * 8;

                for (var dx = 0; dx < 2; dx++)
                {
                    for (var dy = 0; dy < 2; dy++)
                    {
                        context.Output.WriteLine($"v {x + dx} {y + dy} {z}");
                        context.Output.WriteLine($"v {x + dx} {y + dy} 0");

                        var v1 = v0 + dx * 2 + dy * 4;
                        var v2 = v1 + (((dx + dy) % 2 + 1) * 2) * (dy % 2 == 0 ? 1 : -1);
                        context.Output.WriteLine($"f {v1} {v1 + 1} {v2 + 1} {v2}");
                    }
                }

                context.Output.WriteLine($"f {v0} {v0 + 2} {v0 + 6} {v0 + 4}");
            }
        };
    }
}
