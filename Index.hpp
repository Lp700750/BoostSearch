#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<fstream>
#include<mutex>
#include"Tool.hpp"
namespace Lp700_index
{
  struct Docfo
  {
    std::string title;
    std::string content;
    std::string url;
    uint64_t docId;
  };

  struct Node
  {
    std::string keyword;
    int weight;
    uint64_t docid;
  };
  
  typedef std::vector<Node> invertList;
  class Index
  {
  private:
    std::vector<Docfo> farwardIndex;
    std::unordered_map<std::string,std::vector<Node>> invertIndex;
  private:
    //设计成单例模式
    Index(){}
    Index(const Index& index)=delete;
    Index& operator=(const Index& index)=delete;
    static Index* instance;
    static std::mutex mtx;

  public:
    //外部给出公众的实例出类对象的方法
    static Index* getInstance()
    {
      if(instance==nullptr)
      {
        mtx.lock();
        if(instance==nullptr)
        {
          instance=new Index();
        }
        mtx.unlock();
      }
      return instance;
    }

    //建立正排索引
    Docfo* farwardSearch(uint64_t doc_id)
    {
      if(doc_id>=farwardIndex.size())
      {
        return nullptr;
      }
      return &farwardIndex[doc_id];
    }

    //建立倒排索引
    invertList* invertSearch(const std::string& word)
    {
      auto iter=invertIndex.find(word);
      if(iter==invertIndex.end())
      {
        std::cout<<"Not Find!"<<std::endl;
        return nullptr;
      }
      return &(iter->second);
    }

    //根据解析得到的文件，构建由倒排索引到正排索引的过程
    bool builtIndex(const std::string& input)
    {
      std::ifstream in(input,std::ios::in|std::ios::binary);
      if(!in.is_open())
      {
        std::cout<<"input open fail!"<<std::endl;
        return false;
      }
      std::string line;
      while(std::getline(in,line))
      {
        //进行正排索引
        Docfo* doc=builtFarwardIndex(line);
        if(doc==nullptr)
        {
          std::cout<<"builtFarwardIndex"<<std::endl;
          continue;
        }

        //进行倒排索引
        builtInvertIndex(*doc);

      }
      return true;
    }
  private:
    Docfo* builtFarwardIndex(const std::string& line)
    {
      //存放每一个html文档的标题，内容，url的数组
      std::vector<std::string> result;
      
      //设置3部分的分隔符
      const std::string sep="\3";

      Lp700::stringTool::Split(line,&result,sep);

      //如果分离出来的结果不是三部分，就说明有问题
      if(3!=result.size())
      {
        std::cout<<"split fail"<<std::endl;
        return  nullptr;
      }

      //将分离好的html三部分装入数组当中
      Docfo doc;
      doc.title=result[0];
      doc.content=result[1];
      doc.url=result[2];

      //紧跟着数组的下标作为其文档的id
      doc.docId=farwardIndex.size();

      //push_back()会进行拷贝，导致效率会降低
      farwardIndex.push_back(std::move(doc));
      
      return &farwardIndex.back();
    }
    
    //
    bool builtInvertIndex(const Docfo& doc)
    {
      //统计某一个词的标题和内容的大小
      struct word_cnt
      {
        int title_cnt;
        int content_cnt;
        word_cnt()
          :title_cnt(0)
          ,content_cnt(0)
        {}
      };
      
      //建立一个某一个词与其词频统计的映射表
      std::unordered_map<std::string,word_cnt> wordMap;

      //用来装标题当中分词的数组
      std::vector<std::string> titleVec;

      //对标题进行jieba分词
      Lp700::jiebaUtil::CutString(doc.title,&titleVec);

      //对标题当中的分词进行词频统计
      for(std::string s:titleVec)
      {
        //将所有的单词全都转换成小写
        boost::to_lower(s);
        
        //如果wordMap[s]存在的话就查找，如果没有的话就会新建
        wordMap[s].title_cnt++;
      }

      //用来转内容当中分词的数组
      std::vector<std::string> contentVec;

      //用来对内进行分词处理
      Lp700::jiebaUtil::CutString(doc.content,&contentVec);

      //对内容当中的分词进行词频统计
      for(std::string s:contentVec)
      {
        boost::to_lower(s);
        wordMap[s].content_cnt++;
      }
      
      //进行相关度分析
      for(auto &word_pair:wordMap)
      {
        Node node;
        node.docid=doc.docId;
        node.keyword=word_pair.first;
        node.weight=10*word_pair.second.title_cnt+word_pair.second.content_cnt;
        std::vector<Node>& invertList=invertIndex[word_pair.first];

        invertList.push_back(std::move(node));
      }
      return true;
    }
  };
  Index* Index::instance=nullptr;
  std::mutex Index::mtx;
}
