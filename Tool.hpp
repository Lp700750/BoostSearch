#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<boost/algorithm/string.hpp>
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
}
