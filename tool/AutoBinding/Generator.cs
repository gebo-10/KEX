using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using ClangSharp;
using System.IO;
namespace AutoMetaData
{
	public class Generator
	{
		public static StreamWriter header_file_write;
		public static StreamWriter cc_file_write;
		public static void BeginGenerator()
        {
			string filename = Application.streamingAssetsPath + "/auto_registe.h";
			File.Delete(filename);
			File.Create(filename).Dispose();
			header_file_write = new StreamWriter(filename);
			header_file_write.WriteLine("#pragma once");
			header_file_write.WriteLine("#include<sol.hpp>");
			header_file_write.WriteLine("extern void reg_all(sol::table& lua);");

			filename = Application.streamingAssetsPath + "/auto_registe.cc";
			File.Delete(filename);
			File.Create(filename).Dispose();
			cc_file_write = new StreamWriter(filename);
			cc_file_write.WriteLine("#include \"auto_registe.h\"");
			cc_file_write.WriteLine("void reg_all(sol::table& lua){");
		}

		public static void EndGenerator()
		{
			header_file_write.Flush();
			header_file_write.Close();

			cc_file_write.WriteLine("}");
			cc_file_write.Flush();
			cc_file_write.Close();
		}
		public static void GeneratorSol(MetaDatabase meta_database,string filename)
		{
			FileInfo file_info = new FileInfo(filename);
			string tag = file_info.Name.Replace(".cc", "");
			File.Delete(filename);
			File.Create(filename).Dispose();
			StreamWriter sr = new StreamWriter(filename);
			sr.WriteLine("#include \"auto_registe.h\"");
			sr.WriteLine("#include <{0}>" ,meta_database.filename);
			sr.WriteLine("void {0}(sol::table& lua) {{", tag);

			header_file_write.WriteLine("extern void {0}(sol::table& lua);", tag);
			cc_file_write.WriteLine("	void {0}(lua);", tag);

			foreach (var item in meta_database.class_list)
			{
				var class_data = item.Value;
				if (class_data.values.Count == 0 && class_data.methods.Count == 0) continue;
				sr.WriteLine("	{");
				GeneratorClass(sr, class_data);
				sr.WriteLine("	}");
			}
			
			sr.WriteLine("}");
			sr.Flush();
			sr.Close();
		}

		public static void GeneratorClass(StreamWriter sr, ClassMateData data)
		{
			sr.WriteLine(string.Format("		sol::usertype<{0}> type = lua.new_usertype<{0}>(\"{0}\",",data.name));
			if(data.parent != null)
			{
				sr.WriteLine(string.Format("			sol::base_classes, sol::bases<{0}>()", data.parent)); 
			}
			if(data.constructor.Count > 0)
			{
				sr.WriteLine("			sol::constructors <");
				for(int i = 0; i < data.constructor.Count; i++)
				{
					var constructor = data.constructor[i];
					string decl = constructor.decl;
					//decl.Replace("void", data.name);
					decl=decl.Substring(4);
					decl = data.name + decl;
					if (i!= (data.constructor.Count-1))
					{
						decl += ",";
					}
					decl = "			" + decl; 
					sr.WriteLine(decl);
				}

				sr.WriteLine("			> ()");
			}
			sr.WriteLine("		);");

			foreach(var field in data.values)
			{
				sr.WriteLine(string.Format("        type[\"{0}\"] = &{1}::{0};",field.name,data.name));
			}

			foreach (var field in data.methods)
			{
				sr.WriteLine(string.Format("        type[\"{0}\"] = &{1}::{0};", field.name, data.name));
			}

		}


		public static void GeneratorEnum(StreamWriter sr,EnumMateData data)
		{
		}
		//public static void GeneratorFunction(StreamWriter sr,)
		//{
		//}
	}
}
