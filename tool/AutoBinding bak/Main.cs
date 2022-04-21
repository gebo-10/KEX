using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using ClangSharp;
using System;
using AutoMetaData;
public class Main : MonoBehaviour
{
    void Start()
    {
        Parser.DumpAST(Application.streamingAssetsPath + "/component.h");
        Generator.BeginGenerator();

        var data = Parser.ParserFile(Application.streamingAssetsPath + "/component.h");
        Generator.GeneratorSol(data, Application.streamingAssetsPath + "/reg_component.cc");

        Generator.EndGenerator();
    }
}
