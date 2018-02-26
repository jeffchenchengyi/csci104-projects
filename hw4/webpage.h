#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <vector>
#include <string>

class WebPage {
  public:
    WebPage(std::string);
    ~WebPage();
    void setWebLink(std::string);
    std::string getWebLink();
    void addIncomingLink(std::string);
    void addOutgoingLink(std::string);
    const std::vector<std::string>& getIncomingLinkVec();
    const std::vector<std::string>& getOutgoingLinkVec(); 

 private:
    std::string weblink;
    std::vector<std::string> incominglinks_vec;
    std::vector<std::string> outgoinglinks_vec;
};

#endif