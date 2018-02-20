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

void WebPage::addIncomingLink(string incominglink) {
	incominglinks_set.insert(incominglink);
}

void WebPage::addOutgoingLink(string outgoinglink) {
	outgoinglinks_set.insert(outgoinglink);
}

const set<string>& WebPage::getIncomingLinkSet() {
	return incominglinks_set;
}

const set<string>& WebPage::getOutgoingLinkSet() {
	return outgoinglinks_set;
}