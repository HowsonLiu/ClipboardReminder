# ClipboardReminder
剪贴板提示器，用来提示你剪贴板东西的小工具<br>
那么，请问怎么才能用到呢？<br>
* 首先呢，我们下载并解压release中的rar<br>
![下载](https://raw.githubusercontent.com/HowsonLiu/ReadmeImage/master/ClipboardReminder/1.png)<br>
* 接着运行ClipboardReminder.exe<br>
![运行](https://raw.githubusercontent.com/HowsonLiu/ReadmeImage/master/ClipboardReminder/2.png)<br>
* 运行成功的话会有消息提示，注意只能运行一个哦（其实错了也没提示）_(:з」∠)_<br>
![成功](https://raw.githubusercontent.com/HowsonLiu/ReadmeImage/master/ClipboardReminder/3.png)<br>
* 接着我们随便复制一段文字，就会有提醒<br>
![复制](https://raw.githubusercontent.com/HowsonLiu/ReadmeImage/master/ClipboardReminder/4.png)<br>
* 截图也是哦<br>
![截图](https://raw.githubusercontent.com/HowsonLiu/ReadmeImage/master/ClipboardReminder/5.png)<br>
* 位置不合适可以直接用鼠标拉<br>
![拉](https://raw.githubusercontent.com/HowsonLiu/ReadmeImage/master/ClipboardReminder/6.png)<br>
* 默认一秒后自动关闭，可以通过右键托盘图标设置<br>
![自动关闭](https://raw.githubusercontent.com/HowsonLiu/ReadmeImage/master/ClipboardReminder/7.png)<br>
* 如果你想要自定义时间或是大小的话，可以下载ini文件放到exe旁边自定义哦<br>
![自定义](https://raw.githubusercontent.com/HowsonLiu/ReadmeImage/master/ClipboardReminder/8.png)<br>
* ini文件内容是这样<br>
![ini](https://raw.githubusercontent.com/HowsonLiu/ReadmeImage/master/ClipboardReminder/9.png)<br>

## 已知的漏洞
1. 有时复制文本会显示HTML.但这绝对不是我的错,绝对不是ヽ(`Д´)ﾉ.都是Qt的错<br>
2. 满足以下的条件会出现界面样式问题<br>
    a) 我是绝对不会说的( ´_ゝ｀)<br>
    b) 你发现了我也不会改的(｀・ω・´)<br>
# ClipboardReminder 1.1
改动  
* 在文件头添加了我的签名(๑•̀ㅂ•́)و✧
* 添加了令人高兴的开机启动(*/ω＼*)
## 关于开机启动
* 好消息是: 需要以管理员权限运行才能添加到开机启动(ノへ￣、)
* 坏消息是: 你添加一次之后本程序不提供取消开机启动的功能(*￣3￣)╭  
我是不会告诉你, 在注册表\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run中删除ClipboardReminder键就可以了┌( ´_ゝ` )┐
