#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<boost/algorithm/string.hpp>
#include"jieba/Jieba.hpp"
namespace Lp700
{
  class fileTool
  {
  public:
    static bool readFile(const std::string& file,std::string* output)
    {
      //打开文件
      //std::ios::in只读的方式打开文件
      std::ifstream input(file,std::ios::in);
      if(!input.is_open())
      {
        std::cout<<"file open fail!"<<std::endl;
        return false;
      }

      //读取html里面每行的代码
      std::string line;
      while(std::getline(input,line))
      {
        //std::cout<<"getline"<<std::endl;
        *output+=line;
        //std::cout<<*output<<std::endl;
      }

      //文件读取完毕，关闭文件
      input.close();
      return true;
    }
  };

  //对每一个html文档标题 内容 url进行分离
  class stringTool
  {
  public:
    static bool Split(const std::string &target,std::vector<std::string> *out,const std::string& gep)
    {
      //使用boost自带的分割工具
      boost::split(*out,target,boost::is_any_of(gep),boost::token_compress_on);
    }
  };

  const char* const DICT_PATH = "./dict/jieba.dict.utf8";
  const char* const HMM_PATH = "./dict/hmm_model.utf8";
  const char* const USER_DICT_PATH = "./dict/user.dict.utf8";
  const char* const IDF_PATH = "./dict/idf.utf8";
  const char* const STOP_WORD_PATH = "./dict/stop_words.utf8";
   

  class jiebaUtil
  {
  private:
    static cppjieba::Jieba jieba;
  public:
    static void CutString(const std::string& src,std::vector<std::string>* out)
    {
      jieba.CutForSearch(src,*out);
    }
  };
  cppjieba::Jieba jiebaUtil::jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH);
}
