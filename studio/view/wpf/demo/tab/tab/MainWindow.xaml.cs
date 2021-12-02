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
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using KLib;
namespace tab
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            ObservableCollection<int> list = new ObservableCollection<int>();
            //list.CollectionChanged += (object? sender, NotifyCollectionChangedEventArgs e) => { };
            Page2 page =new Page2();
            this.f2.Content = page;
           
            page.grid.RowDefinitions.Add(new RowDefinition());

            ConsoleLogHelper.OpenConsole();


        }

        private void TabControl_SelectionChanged_1(object sender, SelectionChangedEventArgs e)
        {

        }
        private int a;
        private void MenuItem_Click_1(object sender, RoutedEventArgs e)
        {
            TabItem b = new TabItem();//先造一个新的选项
            b.Header = "窗口" + a;//新建一个名字，如窗口2
            aaa.Items.Add(b);//把建好的放到里面去
            aaa.SelectedIndex = a + 1;//造新窗口
            a++;//递增

        }

        private void MenuItem_Click_2(object sender, RoutedEventArgs e)
        {
            this.Close();//把按钮关闭
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            Window1 w=new Window1();
            w.Show();
        }
    }
}
