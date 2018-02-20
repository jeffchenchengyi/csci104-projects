#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <set>
#include <string>

class WebPage {
  public:
    WebPage(std::string);
    ~WebPage();
    void setWebLink(std::string);
    std::string getWebLink();
    void addIncomingLink(std::string);
    void addOutgoingLink(std::string);
    const std::set<std::string>& getIncomingLinkSet();
    const std::set<std::string>& getOutgoingLinkSet(); 

 private:
    std::string weblink;
    std::set<std::string> incominglinks_set;
    std::set<std::string> outgoinglinks_set;
};

#endif