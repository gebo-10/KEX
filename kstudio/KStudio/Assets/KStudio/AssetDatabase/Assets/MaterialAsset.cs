using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using kserialize;
using FlexBuffers;
using UnityEngine;
using XLua;
namespace KStudio
{
    class Mat
    {
        public string shader;
        public string name;
    }
    class MaterialAsset : Asset
    {
        //FlexBuffers.FlexBufferBuilder builder;
        LuaEnv luaenv = null;
        string content;
        public MaterialAsset(string path)
        {
            content = File.ReadAllText(path);
            
        }

        public override List<uint> GetDepends() {
            luaenv = new LuaEnv();
            var objs=luaenv.DoString(content);
            LuaTable t = (LuaTable)objs[0];
            var shader=t.Get<string>("shader");
            List<uint> depends = new List<uint>();
            depends.Add(NameDatabase.Instance.get_id(shader));
            return depends;
        }

        public override byte[] Serialize()
        {
            //return content.ToArray<byte>();
            return  Encoding.UTF8.GetBytes(content);
        }
    }
}
