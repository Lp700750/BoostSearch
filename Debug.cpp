#include<iostream>
#include<string>
#include"Search.hpp"

const std::string srctPath="./destData/destFile.txt";

int main()
{
  Lp700_search::search* querySearch=new Lp700_search::search();
  querySearch->initSearch(srctPath);
  
  std::string query;
  std::string json_string;
  char buffer[1024];
  while(true)
  {
    std::cout<<"please enter query of you wanna search #:";
    fgets(buffer,sizeof(buffer)-1,stdin);
    buffer[strlen(buffer)-1]=0;
    query=buffer;
    querySearch->Search(query,&json_string);
    std::cout<<json_string<<std::endl;
  }

  return 0;
}
