using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;

namespace UI.Plugins.Hierarchy
{
    #region
    public class TreeItem : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// 节点显示的图片
        /// </summary>
        public BitmapImage BI { get; set; }

        /// <summary>
        /// 节点显示的文本
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// 节点类型
        /// </summary>
        public string Type { get; set; }

        /// <summary>
        /// 父节点
        /// </summary>
        public TreeItem Parent { get; set; }

        /// <summary>
        /// 子节点集合
        /// </summary>
        public ObservableCollection<TreeItem> Childern { get; set; }

        private bool m_isAdd = false;
        /// <summary>
        /// 拖动到目标节点时增加到同级目录标志
        /// </summary>
        public bool IsAdd
        {
            get { return m_isAdd; }
            set
            {
                if (m_isAdd != value)
                {
                    m_isAdd = value;
                    if (m_isAdd)
                    {
                        IsAddIn = false;
                    }
                    if (PropertyChanged != null)
                    {
                        PropertyChanged.Invoke(this, new PropertyChangedEventArgs("IsAdd"));
                    }
                }
            }
        }

        private bool m_isAddin = false;
        /// <summary>
        /// 拖动到目标节点时增加到子目录标志
        /// </summary>
        public bool IsAddIn
        {
            get { return m_isAddin; }
            set
            {
                if (m_isAddin != value)
                {
                    m_isAddin = value;
                    if (m_isAddin)
                    {
                        m_isAdd = false;
                    }
                    //触发事件
                    if (PropertyChanged != null)
                    {
                        PropertyChanged.Invoke(this, new PropertyChangedEventArgs("IsAddIn"));
                    }
                }
            }
        }
    }
    #endregion
}

