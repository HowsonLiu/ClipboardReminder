# ClipboardReminder
剪贴板提示器，用来提示你剪贴板东西的小工具<br>
那么，请问怎么才能用到呢？<br>
* 首先呢，我们下载并解压release中的rar<br>
![下载](ReadMeImage/1.png)<br>
* 接着运行ClipboardReminder.exe<br>
![运行](ReadMeImage/2.png)<br>
* 运行成功的话会有消息提示，注意只能运行一个哦（其实错了也没提示）<br>
![成功](ReadMeImage/3.png)<br>
* 接着我们随便复制一段文字，就会有提醒<br>
![复制](ReadMeImage/4.png)<br>
* 截图也是哦<br>
![截图](ReadMeImage/5.png)<br>
* 位置不合适可以直接用鼠标拉<br>
![拉](ReadMeImage/6.png)<br>
* 默认一秒后自动关闭，可以通过右键托盘图标设置<br>
![自动关闭](ReadMeImage/7.png)<br>
* 如果你想要自定义时间或是大小的话，可以下载ini文件放到exe旁边自定义哦<br>
![自定义](ReadMeImage/8.png)<br>
* ini文件内容是这样<br>
![ini](ReadMeImage/9.png)<br>

# ClipboardReminder 1.1
改动  
* 在文件头添加了我的签名
* 添加了令人高兴的开机启动
# ClipboardReminder 1.2
改动
有儿子说每次都要从中间移到右上角有点烦，那我就勉为其难改一下吧
# ClipboardReminder 1.3   
**Optimize:**<br>
Delete the useless .ui suffix file and update the repo directory structure<br>
**Update:**<br>
Before version 1.3, the tips existed as a window, so the following would occur:<br>
![1.2bug](ReadMeImage/Version1.2bug.PNG)<br>
When we press Alt + TAB, the prompt window appears in all the Windows that allow toggling, which is incorrect.
This bug was fixed in this version.
![1.3fixed](ReadMeImage/Version1.3fixed.PNG)
## 关于开机启动
* 好消息是: 需要以管理员权限运行才能添加到开机启动
* 坏消息是: 你添加一次之后本程序不提供取消开机启动的功能
当然你可以用在 \HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run中删除ClipboardReminder键就可以了
