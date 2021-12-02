using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using FlatBuffers;
using kserialize;
using System.Net;
using System;
using System.IO;
using KStudio;

public class Main : MonoBehaviour
{
    public string namedatabase;
    public string dir;
    public string bundleName;
    // Start is called before the first frame update

    Material mat;
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    [EditorButton]
    void Build()
    {
        NameDatabase.Instance.Clear();
        AssetBundleBuilder.BuildPath(dir, bundleName);
        NameDatabase.Instance.SaveFile(namedatabase);
    }
}
