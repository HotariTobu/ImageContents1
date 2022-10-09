namespace DATConverter
{
    internal static partial class Converter
    {
        public static Action<Context> ConvertToPointSetOfWRL => context =>
        {
            context.Output.WriteLine(@"#VRML V2.0 utf8

Shape {
    appearance Appearance
        {
            material Material
            {
                diffuseColor 1.0 0.0 0.0
                emissiveColor 1.0 0.0 0.0
            }
        }
        geometry PointSet
        {
            coord Coordinate
            {
                point[
            ");

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

                var z = .0;
                if (!double.TryParse(tokens[2], out z) || z < -9999)
                {
                    continue;
                }

                context.Output.WriteLine(line + ',');
            }

            context.Output.WriteLine(@"
                ]
            }
        }
    }
            ");
        };
    }
}
