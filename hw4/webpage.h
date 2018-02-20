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
    void addIncomingLink(WebPage*);
    void addOutgoingLink(WebPage*);
    const std::set<WebPage*>& getIncomingLinkSet();
    const std::set<WebPage*>& getOutgoingLinkSet(); 

 private:
    std::string weblink;
    std::set<WebPage*> incominglinks_set;
    std::set<WebPage*> outgoinglinks_set;
};

#endif