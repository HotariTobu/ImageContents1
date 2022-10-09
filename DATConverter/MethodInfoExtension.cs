using System.Reflection;
using System.Text.RegularExpressions;

namespace DATConverter
{
    internal static class MethodInfoExtension
    {
        public static string GetName(this MethodInfo methodInfo)
        {
            var debugName = methodInfo.Name;

            var match = Regex.Match(debugName, @"<\w+_(\w+)>");
            if (match.Success)
            {
                return match.Groups[1].Value;
            }


            return debugName;
        }
    }
}
