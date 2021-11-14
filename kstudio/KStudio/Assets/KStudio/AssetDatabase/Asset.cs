using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KStudio
{
    abstract class Asset
    {
        public abstract void InitCommon(kserialize.AssetType type, uint id);
    }
}
