#include"cpp-httplib/httplib.h"
#include"Search.hpp"
const std::string input="destData/destFile.txt";
const std::string root_path="./website";

int main()
{
  Lp700_search::search find;
  find.initSearch(input);

  httplib::Server svr;
  svr.set_base_dir(root_path.c_str());
  svr.Get("/s",[&find](const httplib::Request &req,httplib::Response &rsp)
      {
        if(!req.has_param("word"))
        {
          rsp.set_content("Not KeyWord!","text/plain;charset=utf-8");

          return;
        }
        std::string word=req.get_param_value("word");
        std::string json_string;
        find.Search(word,&json_string);
        rsp.set_content(json_string,"application/json");
      });
  svr.listen("0.0.0.0",8081);
  return 0;
}

