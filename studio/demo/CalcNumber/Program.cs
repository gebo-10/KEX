using System;
using System.Text.RegularExpressions;

Console.WriteLine("\n计算dxf文件尺寸大小总和---------------------\n");
string path = Directory.GetCurrentDirectory();
Console.WriteLine("当前目录路径为: \n"+path+"\n");

string[] files = Directory.GetFiles(path, "*.dxf");
Console.WriteLine("获取当前目录所有dxf文件: ");
foreach (string file in files)
{
    Console.WriteLine(file);
}
string RegexStr = @"-([0-9|.]+)?.dxf";
decimal sum = 0;
Console.WriteLine("\n\n");
foreach (string file in files)
{
    Match mt = Regex.Match(file, RegexStr);
    string num=mt.Groups[1].Value;
    if (num.Length <= 0)
    {
        Console.WriteLine(file + " 文件名不符合标准 xxx-数值.dxf, 此文件不计算");
        continue;
    }
    Console.WriteLine("获得尺寸: "+num);
    decimal n = 0;
    if (decimal.TryParse(num, out n))
    {
        sum += n;
    }
}
Console.WriteLine("\n总和为: "+ sum);

Console.ReadLine();