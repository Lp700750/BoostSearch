# boostSearch
---------------------------------------------目前解释说明部分还在更新:snowman:--------------------------------------------
## 0 前言
> 在使用C++这门语言进行编程的过程当中，必然少不了对于各种库的使用，其中最出名用的最多的当中就属于STL了，他给C++编程人员减少了不少的麻烦，但是随着时间的推移，人们对于需求的增多，对于库的需求也慢慢的增加，但是由于STL库更新速度较慢，某些其他的语言库逐渐被使用，这里面体谅感比较好的就是boost库，但是当我们真正的进入[boost库官网](https://www.boost.org/)，会发现这个库里面的文件会很多，但是对于它们的搜索却没有，这无疑对C++的开发人员来说很苦恼，据此做一个搜索框来提高对于里面库的查找体验。
## 1 内容介绍
![Boost结构图 drawio](https://github.com/Lp700750/BoostSearch/assets/104414865/d9a89950-e1ab-462d-8ce0-7d8f64fc068c)

### 1.1 大纲介绍
>1. _Parse.cpp_  主要是对原始的Boost当中各种库进行解析，将所有的库Html里面的内容输出为字符串的形式   
>2. _Index.hpp_  主要是解析出来的每一个Html进行构建正排和倒排索引   
>3. _Search.hpp_ 主要是通过关键句来进行查找对应的关键词在那个Html当中出现   
>4. _Tool.hpp_   主要是各种通用“工具”类函数  
>5. _Debug.cpp_  主要是用来进行调试，便于发现问题  
### 1.2 _Parse_
这部分的主要功能主要有三个，第一步先将boost库里面的所有的库文件(.html)全部找出来；第二步就是将读取相应的.html文件，将文件里面的文件标题，文件的内容，文件的网址全部都提取出来；第三步将提取出来的文件保存在相应的文件里面，为下一步使用做准备。    
#### 1.2.1 _saveFile_
这里首先需要定义一个结构体，便于后面解析出来的内容进行存储
```
typedef struct DocInfo
{
  std::string title;
  std::string content;
  std::string url;
}doc_t;
```   
下面这个就是该解析函数，它的主要功能就是对传入的文件srcdata文件夹进行检查，看他是否符合要求的文件，如果是的话就把该文件(带有路径)存放到destdata文件里面，便于后面进行解析文件里面的内容。
```   
bool saveFile(const std::string& srcdata,std::vector<std::string>* destdata);
```     
需要注意的是，它里面的对于文件是否存在，文件的迭代查询采用的都是boost内部自带的库函数
#### 1.2.2 _parseHtml_
```
bool parseHtml(const std::vector<std::string>& _fileList,std::vector<doc_t>* _results);
static bool parseTitle(const std::string& result,std::string* title);
static bool parseContent(const std::string& result,std::string* content);
static bool parseUrl(const std::string& file,std::string* url);
```   
这部分的功能就是将上面解析出来的文件进行读取，然后分别将每一个文件内部的title,content,url进行解析获取然后保存于上面提到的DocInfo，然后以DocInfo为单位将每一份解析完文件保存于_results当中，便于后面的第三步操作。
#### 1.2.3 _saveHtml_
```
bool saveHtml(const std::vector<doc_t>& doc,const std::string& output);
```
这部分的内容相较于来说比较简单，它的主要功能就是对上面解析好的文件进行文件输出。
###  1.3 _Index.hpp_
