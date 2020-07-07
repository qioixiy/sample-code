#include "FL/Fl.H"  // 这个是通用的，必须包含
// 以下的包含视使用情况而定，一般用什么类就添加什么头文件
// 注意：以FL/开头，Fl_前缀的l是小写，最后的.H是大写
#include "FL/Fl_Window.H"
#include "FL/Fl_Double_Window.H"

#include "FL/Fl_Button.H"
#include "FL/Fl_Input.H"

// 标准的C++ main函数
// 在g++编译器连接选项中指定-mwindows编译不带控制台的纯窗口程序
// 我没用过VC编译这个程序，但应该是，除了需要指定是Windows程序外，还要修改入口点
int main(int argc, char **argv)
{
    // 创建主窗口，因为Fl_Window会造成闪烁，感觉很慢，可以试一下
    // 所以一般用Fl_Double_Window，这个Window使用了双缓冲，所以不会有闪烁
   
    // 可以看到，创建任何Widget，构造函数为Fl_Widget(x, y, width, height, label)
    // 对于Window，label就是窗口的标题
    Fl_Double_Window *w = new Fl_Double_Window(100, 200, 460, 320, "第一个Fltk程序");
    // 对于文本输入框，label就是输入框前面的标签
    Fl_Input *input = new Fl_Input(50, 10, 100, 30, "姓名:");
    // 对于按钮，就是按钮显示的文字
    Fl_Button *b = new Fl_Button(100, 50, 50, 30, "好的");

    // 这里要结束，对于所有的Fl_Group（通用容器），有两个方法，叫begin()和end()
    // 在这两个方法之间创建的所有的控件，都是他的子控件
    // 为什么没有调用begin()呢？因为Fl_Group的子类在创建时（这里即Fl_Double_Window），就自动调用了begin()
    // 也可以显式调用begin()和end()来添加控件
    w->end();
   
    // 如果没有这个调用，主窗口将不可改变大小。
    // 关于resize下面有详细介绍
    w->resizable(w);

    // 显示窗口
    w->show();
   
    // 默认的消息循环
    return Fl::run();
}
