#include<iostream>
#include<vector>
#include<string>
#include<boost/filesystem.hpp>
#include"Tool.hpp"
typedef struct DocInfo
{
  std::string title;
  std::string content;
  std::string url;
}doc_t;

const std::string srcFilePath="htmlData";
const std::string destFilePath="destData/destFile.txt";


bool saveFile(const std::string& srcdata,std::vector<std::string>* destdata);
bool parseHtml(const std::vector<std::string>& _fileList,std::vector<doc_t>* _results);
bool saveHtml(const std::vector<doc_t>& doc,const std::string& output);

bool saveFile(const std::string& srcdata,std::vector<std::string>* destdata)
{
  namespace bfpath=boost::filesystem;
  bfpath::path srcpath(srcdata);
  
  //判断输入进来的原始html路径是否存在
  if(!bfpath::exists(srcpath))
  {
    std::cout<<"filepath no exist!"<<std::endl;
    return false;
  }

  //逐个遍历路径下的每一个html文件
  bfpath::recursive_directory_iterator end;
  for(bfpath::recursive_directory_iterator curfile(srcpath);curfile!=end;curfile++)
  {
    if(!bfpath::is_regular_file(*curfile))
    {
      continue;
    }
    if(curfile->path().extension()!=".html")
    {
      continue;
    }
    destdata->push_back(curfile->path().string());
    //std::cout<<curfile->path().string()<<std::endl;
  }
  return true;
}
static bool parseTitle(const std::string& result,std::string* title)
{
  std::size_t begin=result.find("<title>");
  if(begin==std::string::npos)
  {
    std::cout<<"Not Find!"<<std::endl;
    return false;
  }
  std::size_t end=result.find("</title>");
  if(end==std::string::npos)
  {
    std::cout<<"Not Find!"<<std::endl;
    return false;
  }
  begin+=std::string("<title>").size();
  if(begin>end)
  {
    return false;
  }
  *title=result.substr(begin,end-begin);
  //std::cout<<*title<<std::endl;
  return true;
}
static bool parseContent(const std::string& result,std::string* content)
{
  enum status
  {
    LABEL,
    CONTENT 
  };
  enum status s=LABEL;
  for(char c:result)
  {
    switch(s)
    {
      case LABEL:
        if(c=='>')
        {
          s=CONTENT;
        }
        break;
      case CONTENT:
        if(c=='<')
        {
          s=LABEL;
        }
        else
        {
          if(c=='\n')
          {
            c=' ';
          }
          content->push_back(c);
        }
        break;
      default:
        break;
    }
  }
  //std::cout<<*content<<std::endl;
  return true;
}
static bool parseUrl(const std::string& file,std::string* url)
{
  std::string urlHead="https://www.boost.org/doc/libs/1_78_0/doc/html";
  std::string urlTail=file.substr(srcFilePath.size());
  
  *url=urlHead+urlTail;
  
  //std::cout<<*url<<std::endl;
  return true;
}
static void show(const doc_t& doc)
{
  std::cout<<"title: "<<doc.title<<std::endl;
  std::cout<<"content: "<<doc.content<<std::endl;
  std::cout<<"url: "<<doc.url<<std::endl;
}
bool parseHtml(const std::vector<std::string>& fileList,std::vector<doc_t>* results)
{
  for(const std::string& file:fileList)
  {
    //读取文件
    std::string result;
    if(!Lp700::fileTool::readFile(file,&result))
    {
      std::cout<<"readfile"<<std::endl;
      continue;
    }

    //解析标题
    doc_t doc;
    if(!parseTitle(result,&doc.title))
    {
      std::cout<<"parseTitle"<<std::endl;
      continue;
    }
    //解析内容
    if(!parseContent(result,&doc.content))
    {
      std::cout<<"parseContent"<<std::endl;
      continue;
    }
    //解析url
    if(!parseUrl(file,&doc.url))
    {
      std::cout<<"parseUrl"<<std::endl;
      continue;
    }
    results->push_back(std::move(doc));
    //show(doc);
  }
  return true;
}
bool saveHtml(const std::vector<doc_t>& doc,const std::string& output)
{
  //open file with output
  std::ofstream out(output,std::ios::out|std::ios::binary);
  if(!out.is_open())
  {
    return false;
  }

#define SEP '\3'
  for(auto& file:doc)
  {
    std::string outStr;
    outStr=file.title;
    outStr+=SEP;
    outStr+=file.content;
    outStr+=SEP;
    outStr+=file.url;
    outStr+='\n';
    //std::cout<<outStr<<std::endl;
    out.write(outStr.c_str(),outStr.size());
  }
  out.close();
  return true;
}
int main()
{
  //第一步：将所有的html文件都选出来，放在单独的数组当中备用
  std::vector<std::string> fileList;
  if(!saveFile(srcFilePath,&fileList))
  {
    std::cerr<<"saveFile error!"<<std::endl;
    return 1;
  }

  //第二步：将数组中所有的html文件进行数据清洗，解析出标题内容网址
  std::vector<doc_t> result;
  if(!parseHtml(fileList,&result))
  {
    std::cerr<<"parseFile fail!"<<std::endl;
    return 2;
  }
  //第三步：将清洗后的数据标题内容网址进行保存
  if(!saveHtml(result,destFilePath))
  {
    std::cout<<"saveHtml fail!"<<std::endl;
    return 3;
  }
 return 0;
}
