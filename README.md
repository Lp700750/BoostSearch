# BoostSearch
-----------------------------------目前解释说明部分还在更新-----------------------------
### 这里面主要有以下几部分组成
1.Parse.cpp  主要是对原始的Boost当中各种库进行解析，将所有的库Html里面的内容输出为字符串的形式

2.Index.hpp  主要是解析出来的每一个Html进行构建正排和倒排索引

3.Search.hpp 主要是通过关键句来进行查找对应的关键词在那个Html当中出现

4.Tool.hpp   主要是各种通用“工具”类函数

5.Debug.cpp  主要是用来进行调试，便于发现问题
