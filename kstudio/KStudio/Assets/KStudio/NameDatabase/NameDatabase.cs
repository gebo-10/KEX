using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.IO;

public class NameDatabase
{
    private static NameDatabase instance = null;
    private NameDatabase() {
        Clear();
    }
    public static NameDatabase Instance
    {
        get
        {
            if (instance == null)
            {
                instance = new NameDatabase();
            }
            return instance;
        }
    }


    public uint index=1;
    public Dictionary< string,uint> names=new Dictionary<string, uint>();
    // Start is called before the first frame update

    //[EditorButton]
    public void Clear()
    {
        index = 1;
        names.Clear();
    }

    public uint add(string name)
    {
        uint id = 0;
        if (!names.TryGetValue(name,out id))
        {
            id = index;
            names.Add(name, id);
            index = index + 1;
            
        }
        return id;
    }

    public byte[] Serialize()
    {
        kserialize.NameDatabaseT database = new kserialize.NameDatabaseT();
        database.Names = new List<kserialize.NameT>();
        foreach(var name in names)
        {
            kserialize.NameT n = new kserialize.NameT();
            n.Str = name.Key;
            n.Id = name.Value;
            database.Names.Add(n);
        }
        return database.SerializeToBinary();
    }

    //[EditorButton]
    public void SaveFile(string filename)
    {
        var data = Serialize();
        File.WriteAllBytes(filename, data);
    }
}
