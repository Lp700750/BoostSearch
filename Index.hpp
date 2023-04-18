#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<fstream>
namespace index
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
  

  class Index
  {
  public:
    Docfo* farwardSearch(uint64_t doc_id)
    {
      if(doc_id>=farwardIndex.size())
      {
        return nullptr;
      }
      return &farwardIndex[doc_id];
    }
    std::vector<Node>* invertSearch(const std::string& word)
    {
      auto iter=invertIndex.find(word);
      if(iter==invertIndex.end())
      {
        std::cout<<"Not Find!"<<std::endl;
        return nullptr;
      }
      return &(iter->second);
    }
  private:
    std::vector<Docfo> farwardIndex;
    std::unordered_map<std::string,std::vector<Node>> invertIndex;
  };
}
