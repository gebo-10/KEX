using kserialize;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KStudio
{
    abstract class Asset
    {
        public virtual void InitCommon(kserialize.AssetType type, uint id) { }
        public virtual byte[] Serialize() { return null; }
        public static Asset CreateAsset(AssetType type, string path)
        {
            switch (type)
            {
                case AssetType.Shader:
                    return new ShaderAsset(path);
                case AssetType.Mesh:
                    return new MeshAsset(path);
            }
            return null;
        }
    }
}
