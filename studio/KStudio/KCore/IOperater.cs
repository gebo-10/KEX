using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace KStudio.Core
{
    public interface  IOperater : ICommand
    {
        void Undo();
        void Redo();
    }
}
