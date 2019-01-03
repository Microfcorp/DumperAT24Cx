using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.IO.Ports;
using IniFiles;

namespace Dumper
{
    class Program
    {
        
        static void Main(string[] args)
        {
            IniFile INI = new IniFile("config.ini");
            SerialPort sp = new System.IO.Ports.SerialPort();
            String path = "";

            if (args.Length > 0)
                path = args[0];
                
            if (INI.KeyExists("Port", "Main"))
                sp.PortName = INI.ReadINI("Main", "Port");
            else sp.PortName = "COM1";

            if (INI.KeyExists("File", "Main"))
                path = INI.ReadINI("Main", "File");

            if (INI.KeyExists("BaudRate", "Main"))
                sp.BaudRate = int.Parse(INI.ReadINI("Main", "BaudRate"));
            else sp.BaudRate = 9600;

            if (INI.KeyExists("ReadTimeout", "Main"))
                sp.ReadTimeout = int.Parse(INI.ReadINI("Main", "ReadTimeout"));

            byte[] bytes = File.ReadAllBytes(path);
            Console.WriteLine("Начать?");
            Console.ReadLine();
            
            sp.NewLine = "\r\n";
            try
            {
                sp.Open();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Возникла ошибка "+ex.Message);
            }

            for (int i = 0; i < bytes.Length; i++)
            {
                sp.Write(bytes, i, 1);
                try
                {
                    Console.WriteLine(sp.ReadLine());
                }
                catch
                {
                    Console.WriteLine("Ошибка! Программатор не отвечает");
                }             
            }
            Console.WriteLine("Запись окончена");
            Console.WriteLine("Нажмите для выхода");
            Console.ReadLine();
        }
    }
}
