using kserialize;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace KStudio
{
    class AssetBundleBuilder
    {
        FileStream file;
        kserialize.AssetBundleT bundle;
        uint offset = 4;
        uint assetCount = 0;
        public AssetBundleBuilder(string path)
        {
            bundle = new AssetBundleT();
            bundle.AssetInfos = new List<AssetInfoT>();
            file = System.IO.File.OpenWrite(path);
            file.Seek(offset, SeekOrigin.Begin);
        }
        public void Push(kserialize.AssetType type,string path)
        {
            Debug.Log("Building------ " + path);
            var info = new AssetInfoT();
            info.Type = type;
            byte[] buffer=new byte[1];
            switch (type)
            {
                case AssetType.Shader:
                    var shader=new ShaderAsset(path);
                    var id = NameDatabase.Instance.add(path);
                    shader.InitCommon(type, id);
                    buffer = shader.Serialize();
                    info.Id = id;
                    info.Size = (uint)buffer.Length;
                    info.Offset = (uint)offset;
                    offset = offset + info.Size;
                    //Debug.Log(shader.shader.ToString());
                    break;
            }
            bundle.AssetInfos.Add(info);
            assetCount = assetCount + 1;
            file.Write(buffer, 0, buffer.Length);
        }
        public void End()
        {
            var bundle_data = bundle.SerializeToBinary();
            file.Write(bundle_data, 0, bundle_data.Length);

            int netOffset = IPAddress.HostToNetworkOrder((int)offset);
            var array = BitConverter.GetBytes(netOffset);
            file.Seek(0, SeekOrigin.Begin);
            file.Write(array, 0, array.Length);
            
            file.Flush();
            file.Close();
        }


        public static void BuildPath( string dir , string bundleName)
        {
            Debug.Log("BuildPath dir=" + dir + "   bundle=" + bundleName);
            AssetBundleBuilder builder = new AssetBundleBuilder(bundleName);

            var files = Directory.GetFiles(dir, "*", SearchOption.AllDirectories);
            foreach (var file in files)
            {
                FileInfo info = new FileInfo(file);
                if (info.Extension == ".glsl")
                {
                    builder.Push(AssetType.Shader, file);
                }
            }

            builder.End();
        }
    }
}
