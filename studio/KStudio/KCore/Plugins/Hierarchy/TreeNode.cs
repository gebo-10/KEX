using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KStudio.Core.Plugins.Hierarchy
{
    class TreeNode : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler? PropertyChanged =null;
        public ObservableCollection<TreeNode> Children { get; set; } = new ObservableCollection<TreeNode>();
        public int id { get; set; } = 0;

        public string name;
        public string Name
        {
            get { return name; }
            set
            {
                name = value;
                if (this.PropertyChanged != null)
                {
                    this.PropertyChanged.Invoke(this, new PropertyChangedEventArgs("Name"));//当Name的属性值发生改变时，PropertyChanged事件触发
                }
            }
        }

        private bool isExpanded = false;
        public bool IsExpanded
        {
            get { return isExpanded; }
            set
            {
                isExpanded = value;
                if (this.PropertyChanged != null)
                {
                    this.PropertyChanged.Invoke(this, new PropertyChangedEventArgs("IsExpanded"));//当Name的属性值发生改变时，PropertyChanged事件触发
                }
            }
        }

        private bool type = false;
        public bool Type
        {
            get { return isExpanded; }
            set
            {
                isExpanded = value;
                if (this.PropertyChanged != null)
                {
                    this.PropertyChanged.Invoke(this, new PropertyChangedEventArgs("IsExpanded"));//当Name的属性值发生改变时，PropertyChanged事件触发
                }
            }
        }


    }
}
