#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <set>
#include <map>
#include "webpage.h"
using namespace std;

WebPage::WebPage(string weblink) {
	WebPage::setWebLink(weblink);
}

WebPage::~WebPage() {
}

void WebPage::setWebLink(string newWebLink) {
	weblink = newWebLink;
}

string WebPage::getWebLink() {
	return weblink;
}

void WebPage::addIncomingLink(WebPage* incominglink_ptr) {
	incominglinks_set.insert(incominglink_ptr);
}

void WebPage::addOutgoingLink(WebPage* outgoinglink_ptr) {
	outgoinglinks_set.insert(outgoinglink_ptr);
}

const set<WebPage*>& WebPage::getIncomingLinkSet() {
	return incominglinks_set;
}

const set<WebPage*>& WebPage::getOutgoingLinkSet() {
	return outgoinglinks_set;
}