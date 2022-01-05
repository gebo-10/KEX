using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using ClangSharp;
using System;
using AutoMetaData;
using System.IO;

public class Main : MonoBehaviour
{
    public FileListConfig file_config;
    public string out_dir;
    void Start()
    {
        //Parser.DumpAST(Application.streamingAssetsPath + "/component.h");
        
        Generator.BeginGenerator(out_dir);
        foreach(var file in file_config.files)
        {
            Parser.DumpAST(file);
            FileInfo info = new FileInfo(file);
            string reg_file = info.Name;
            reg_file= reg_file.Replace(".h", ".cc");
            reg_file = "reg_" + reg_file;
            var data = Parser.ParserFile(file);
            Generator.GeneratorSol(data, out_dir + reg_file);
        }
        //var data = Parser.ParserFile(Application.streamingAssetsPath + "/component.h");
        //Generator.GeneratorSol(data, Application.streamingAssetsPath + "/reg_component.cc");

        Generator.EndGenerator();
    }
}
