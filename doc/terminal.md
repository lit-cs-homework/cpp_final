
# terminal

## 基本介绍

实现了基本的终端属性样式控制库，
依靠条件编译实现了跨平台：

- Windows 下使用 Windows API 实现
- Linux, MacOS 等 POSIX 系统 下使用ANSI转移序列

## 作用

此次项目主要用到了 terminal 中的以下函数：

### 光标控制

- showCursor/hideCursor: 显示/隐藏光标， 用于scenario模块输出逐字一句话时不显示尾部的光标， 避免了光标不停移动晃眼的问题
- setCursorPos: 设置光标位置， 用于在输出地图前重置光标位置到屏幕首部， 避免新一帧地图被打印时将上一帧地图向上一行一行挤导致的画面抖动不连续的问题


### 样式设置

- setBack/ForegroundColor: 用于为剧情/对话字体添加颜色， 首先是增加了辨识度， 其次是使游戏画面更有吸引力
- setStyle: 设置字体样式， 如粗体，闪烁等
- resetAttribute: 重置之前因为 `set*` 调用而改变的终端样式
- styledWrite: 对样式化输出的高层次包装， 避免了每次设置终端样式输出后需要手动调用 `resetAttributes` 复原默认样式的繁杂操作

