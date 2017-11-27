# 文明5定时退出

这个小程序用来在windows上定时杀死进程（默认为文明5），从而让自己无法继续“下一回合”，达到养生保健的效果。

在强制退出前10分钟和前3分钟，会分别自动播放两次提示音，提醒你该存档了。

## 使用

### 直接使用

可以直接使用已经编译好的exe文件，虽然我在不同的机器和windows版本上都测试通过了，但理论上它不一定能在你的机器上正常运行。如果不能，请参考下面的“编译”，在你的机器上重新编译。

#### 双击使用

此方法简单方便，使用默认的退出时间。

下载解压全部文件，并双击kill_civ.exe运行，然后开始玩文明5即可。文明5将会在今晚12点（默认的时间）被强制退出。

请注意在文明5退出前不可退出kill_civ.exe。

#### 命令行

此方法可以自定义退出时间和想要退出的游戏。

在下载解压后的文件夹中，按住shift键并鼠标右键点击空白处，选择“在此处打开命令行窗口”，在打开的窗口中输入`cmd`并回车。

输入

`kill_civ HH:MM PRONAME`

其中`HH:MM`是你希望退出文明5的时间，比如22:30即为今晚10点30分退出。如不填写则使用默认值00:00，即今晚0点整。

`PRONAME`是文明5的进程名，如不填写则使用默认值CivilizationV。你可以在任务管理器中查看你电脑上的文明5对应的进程名（此时文明5需已启动），如果它不包含“CivilizationV”，则你可以将`PRONAME`指定为你的文明5进程名。同样，你也可以通过指定`PRONAME`强制退出其他程序如文明6。注意，如果要填写`PRONAME`，必须也填写HH:MM项。

例如，输入

`kill_civ 23:00 civilization`

回车后显示

> The process "civilization" will be killed in  2 hours and 59 minutes.

则“文明”游戏将在2小时59分后的23:00退出。

### 编译

在命令行中输入

`gcc -o kill_civ.exe main.c -lwinmm`

即可完成编译（需在windows系统中编译），这需要你的电脑上安装了gcc。编译完成后即可按上述方法使用kill_civ.exe。

另外，你可以修改main.c中的
```
int notice_before_1 = 10*60;	//seconds before killing when first notice
int notice_before_2 = 3*60;   //seconds before killing when second notice
```
来修改退出前的提醒时间。也可以使用其他的wav音乐文件替换alert_sound.wav，来使用你喜欢的提示音。
