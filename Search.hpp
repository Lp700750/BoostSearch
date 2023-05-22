#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"Index.hpp"
#include"Tool.hpp"
#include<unordered_map>
#include<algorithm>
#include<jsoncpp/json/json.h>
namespace Lp700_search
{
  struct InvertNode
  {
    uint64_t docId;
    int weight;
    std::vector<std::string> words;
    InvertNode():docId(0),weight(0){}
  };

  class search
  {
  private:
    Lp700_index::Index* index;
  public:
    search(){};
    ~search(){};
  public:
    //初始化搜索
    void initSearch(const std::string& input)
    {
      //获取单例对象
      index=Lp700_index::Index::getInstance();

      //根据index来建立索引
      index->builtIndex(input);
    }

    //根据输入的关键句来进行搜索
    void Search(const std::string& query,std::string* json_string)
    {
      //1.对输入的搜索关键句进行分词处理
      std::vector<std::string> words;
      Lp700::jiebaUtil::CutString(query,&words);

      //2.对分的词进行index查找
      std::vector<InvertNode> allList;
      std::unordered_map<uint64_t,InvertNode> tokens_map;
      
      //2.1对输入搜索而分的词进行遍历
      for(std::string word:words)
      {
        //将所有的词同意进行小写
        boost::to_lower(word);

        //对搜到的词进行搜索index
        Lp700_index::invertList* invertlist=index->invertSearch(word);

        if(invertlist==nullptr)
        {
          std::cout<<"invertlist"<<std::endl;
          continue;
        }

        for(const auto& elem : *invertlist)
        {
          auto& iter=tokens_map[elem.docid];
          
          iter.docId=elem.docid;
          iter.weight+=elem.weight;
          iter.words.push_back(elem.keyword);
        }
      }

      for(const auto& iter:tokens_map)
      {
        allList.push_back(std::move(iter.second));
      }

      //3.对查找出来的结果进行权值排序
      std::sort(allList.begin(),allList.end(),\
          [](const InvertNode& e1,const InvertNode& e2)
          {
            return e1.weight>e2.weight;
          });

      //4.对排序出来的结果进行jsoncpp处理 传送给前端
      Json::Value root;

      for(auto& iter : allList)
      {
        Lp700_index::Docfo* doc=index->farwardSearch(iter.docId);
        if(doc==nullptr)
        {
          std::cout<<"JsonValue fail"<<std::endl;
          continue;
        }
        Json::Value elemNode;

        elemNode["title"]=doc->title;
        elemNode["desc"]=getDesc(doc->content,iter.words[0]);
        elemNode["url"]=doc->url;
        elemNode["id"]=(int)iter.docId;
        elemNode["weight"]=iter.weight;

        root.append(elemNode);
      }
        
      //Json::FastWriter writer;
      Json::StyledWriter writer;
      *json_string=writer.write(root);
    
    }

      //对每一个html的内容部分进行截取  展示在搜索的界面当中
    std::string getDesc(const std::string& html_content,const std::string& word)
    {
      const int prevStop=50;
      const int nextStop=100;
      auto iter=std::search(html_content.begin(),html_content.end(),
          word.begin(),word.end(),[](int x,int y)
          {
            return (std::tolower(x)==std::tolower(y));
          });
      if(iter==html_content.end())
      {
        return "error1";
      }

      int pos=std::distance(html_content.begin(),iter);
      int start=0;
      int end=html_content.size()-1;
      if(pos>start+prevStop)
      {
        start=pos-prevStop;
      }
      if(pos<end-nextStop)
      {
        end=pos+nextStop;
      }
      if(start>=end)
      {
        return "error2";
      }
      std::string desc=html_content.substr(start,end-start);
      desc+="...";

      return desc;
    }
  };
}

