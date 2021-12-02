﻿using KLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace tab
{
    /// <summary>
    /// Page2.xaml 的交互逻辑
    /// </summary>
    public partial class Page2 : Page
    {
        public Page2()
        {
            InitializeComponent();
        }

        private void grid_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            ConsoleLogHelper.WriteLine(e.NewSize.ToString());
            Grid g=(Grid)sender;
            var p=g.PointToScreen(new Point(0, 0));
            ConsoleLogHelper.WriteLine(p.ToString());
            ConsoleLogHelper.WriteLine(g.RenderSize.ToString());
            
        }
    }
}
