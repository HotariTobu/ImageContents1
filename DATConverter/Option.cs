namespace DATConverter
{
    internal class Option : IDisposable
    {
        public string SourcePath { get; init; }
        public string DestinationPath { get; init; }
        public Action<Context> Convert { get; init; }
        public string Extension { get; init; }

        private string _optionPath;

        private static readonly string s_lineSeparator = ": ";
        private static readonly string s_extensionSeparator = "Of";

        public Option(string optionPath)
        {
            SourcePath = "../../../../source_data";
            DestinationPath = "../../../../destination_data";
            Convert = Converter.ConvertToMapOfCSV;
            Extension = ".csv";

            _optionPath = optionPath;

            string[]? lines = null;
            try
            {
                lines = File.ReadAllLines(optionPath);
            }
            catch (Exception e)
            {
                Console.WriteLine($"{e.Message}\n{e.StackTrace}");
            }

            if (lines == null)
            {
                return;
            }

            foreach (var line in lines)
            {
                if (line.StartsWith('#'))
                {
                    continue;
                }

                var lineSeparatorIndex = line.IndexOf(s_lineSeparator);

                var key = line.Substring(0, lineSeparatorIndex);
                var value = line.Substring(lineSeparatorIndex + s_lineSeparator.Length);

                switch (key)
                {
                    case "SourcePath":
                        SourcePath = value;
                        break;

                    case "DestinationPath":
                        DestinationPath = value;
                        break;

                    case "Function":
                        {
                            var convert = typeof(Converter).GetProperty(value)?.GetValue(null) as Action<Context>;
                            if (convert == null)
                            {
                                break;
                            }

                            Convert = convert;

                            string methodName = convert.Method.GetName();
                            var extensionIndex = methodName.LastIndexOf(s_extensionSeparator);
                            string extension = methodName.Substring(extensionIndex + s_extensionSeparator.Length);
                            Extension = $".{extension.ToLower()}";
                        }
                        break;
                }
            }
        }

        public void Dispose()
        {
            var lines = from pair in new Dictionary<string, string>
                        {
                            { "SourcePath", SourcePath },
                            { "DestinationPath", DestinationPath },
                            { "Function", Convert.Method.GetName() },
                        }
                        select $"{pair.Key}{s_lineSeparator}{pair.Value}";

            try
            {
                File.WriteAllLines(_optionPath, lines);
            }
            catch (Exception e)
            {
                Console.WriteLine($"{e.Message}\n{e.StackTrace}");
            }
        }
    }
}
