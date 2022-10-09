using DATConverter;

using var option = new Option("option.txt");

if (!Directory.Exists(option.SourcePath))
{
    return;
}
var sourcePaths = Directory.GetFiles(option.SourcePath, "*.dat");

Directory.CreateDirectory(option.DestinationPath);

foreach (var sourcePath in sourcePaths)
{
    var filename = Path.GetFileNameWithoutExtension(sourcePath);
    var destinationPath = Path.Combine(option.DestinationPath, filename + option.Extension);

    Console.WriteLine($"Converting: {sourcePath} > {destinationPath}");

    try
    {
        using var input = new StreamReader(sourcePath);
        using var output = new StreamWriter(destinationPath);
        var context = new Context(input, output);

        option.Convert(context);
    }
    catch (Exception e)
    {
        Console.WriteLine($"{e.Message}\n{e.StackTrace}");
    }
}
