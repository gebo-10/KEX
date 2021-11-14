using kserialize;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using UnityEditor;
using UnityEngine;
namespace KStudio
{
    class MeshAsset: Asset
    {
        public MeshT mesh=new MeshT();
        public MeshAsset(string path)
        {
            GameObject  go = AssetDatabase.LoadAssetAtPath<GameObject>(path);
            var filter=go.GetComponent<MeshFilter>();
            var m = filter.sharedMesh;

            mesh.Indices = new List<ushort>();
            m.GetIndices(mesh.Indices,0);

            mesh.Position = new List<Vec3T>();
            foreach (var pos in m.vertices)
            {
                var vec3 = new Vec3T();
                vec3.X = pos.x*100f;
                vec3.Y = pos.y * 100f;
                vec3.Z = pos.z * 100f;
                mesh.Position.Add(vec3);
            }
        }

        public override void InitCommon(AssetType type, uint id)
        {
            mesh.AssetCommon = new kserialize.AssetCommonT();
            mesh.AssetCommon.AssetType = type;
            mesh.AssetCommon.Id = id;
        }

        public override byte[] Serialize()
        {
            return mesh.SerializeToBinary();
        }
    }
}
