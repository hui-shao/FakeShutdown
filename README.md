# FakeShutdown

通过替换 shutdown.exe 实现某种另类的关机（整蛊向）

### 说明

本来是像上述的那样想的，结果发现，开始菜单里的关机按键并不是调用 "C:\Windows\system32"下面的 `shutdown.exe`，而是通过 Win32 API 实现。

突然就少了一点点乐趣……

不过，自己写了好一会儿的程序删了也觉得可惜。

况且，源码里面的一些东西（~~踩到的坑~~）还是值得记忆和分享的。

比如：

- CMake下，为 Console App 添加管理员UAC

- 通过 Win32 API 实现控制台窗口的隐藏

- 通过 Win32 API 实现获取 Token、LUID 进行提权（比如本次关机需要获取 `SE_SHUTDOWN_NAME` 权限）并关机

- MessageBox 的各种使用（按钮、图标、返回值）

  