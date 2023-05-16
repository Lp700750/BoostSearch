# boostSearch
---------------------------------------------目前解释说明部分还在更新:snowman:--------------------------------------------
### 0 前言
> 在使用C++这门语言进行编程的过程当中，必然少不了对于各种库的使用，其中最出名用的最多的当中就属于STL了，他给C++编程人员减少了不少的麻烦，但是随着时间的推移，人们对于需求的增多，对于库的需求也慢慢的增加，但是由于STL库更新速度较慢，某些其他的语言库逐渐被使用，这里面体谅感比较好的就是boost库，但是当我们真正的进入[boost库官网](https://www.boost.org/)，会发现这个库里面的文件会很多，但是对于它们的搜索却没有，这无疑对C++的开发人员来说很苦恼，据此做一个搜索框来提高对于里面库的查找体验。
### 1 内容介绍
#### 1.1 大纲介绍
>1. `Parse.cpp`  主要是对原始的Boost当中各种库进行解析，将所有的库Html里面的内容输出为字符串的形式   
>2. Index.hpp  主要是解析出来的每一个Html进行构建正排和倒排索引   
>3. Search.hpp 主要是通过关键句来进行查找对应的关键词在那个Html当中出现   
>4. Tool.hpp   主要是各种通用“工具”类函数  
>5. Debug.cpp  主要是用来进行调试，便于发现问题  
#### 1.2 Parse解析


