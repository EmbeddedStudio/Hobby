#include<windows.h>
#include<stdio.h>


void main()
{
	MessageBox(0,"你好","天朝",0);
	//第一个参数设置为0，第一个参数是依赖的窗口的编号，相当于谁弹出的窗口，
	//0为系统弹出，第二个参数是对话框的内容，第三个参数是对话框的标题，
	//第四个参数是对话框类型，设置成0即可
	ShellExecute(0,"open" ,"calc",0,0,1);
	//getchar();
}