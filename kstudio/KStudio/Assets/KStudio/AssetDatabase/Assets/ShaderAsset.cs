using kserialize;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KStudio
{
    class ShaderAsset: Asset
    {
        public kserialize.ShaderT shader=new kserialize.ShaderT();
        public enum State
        {
            Nil,
            Decl,
            Vert,
            Frag,
            Compute,
        }
        State state;
        public ShaderAsset(string path)
        {
            state = State.Nil;
            var lines= File.ReadAllLines(path);
            foreach(var line in lines)
            {
                if (line.Contains("#decl"))
                {
                    state = State.Decl;
                    continue;
                }else if(line.Contains("#frag"))
                {
                    state = State.Frag;
                    continue;
                }
                else if (line.Contains("#vert"))
                {
                    state = State.Vert;
                    continue;
                }
                else if (line.Contains("#compute"))
                {
                    state = State.Compute;
                    continue;
                }

                switch (state)
                {
                    case State.Nil:

                        break;
                    case State.Decl:

                        break;
                    case State.Vert:
                        shader.Vert += line;
                        shader.Vert += "\n";
                        break;
                    case State.Frag:
                        shader.Frag += line;
                        shader.Frag += "\n";
                        break;
                    case State.Compute:
                        shader.Compute += line;
                        shader.Compute += "\n";
                        break;
                }
            }
        }

        //public override void InitCommon(AssetType type, uint id)
        //{
        //    shader.AssetCommon = new kserialize.AssetCommonT();
        //    shader.AssetCommon.AssetType = type;
        //    shader.AssetCommon.Id = id;
        //}

        public override byte[] Serialize()
        {
            return shader.SerializeToBinary();
        }
    }
}
