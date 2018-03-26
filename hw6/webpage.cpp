#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include "webpage.h"
using namespace std;

WebPage::WebPage(string weblink) {
	setWebLink(weblink);
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
	incominglinks_vec.push_back(incominglink);
}

void WebPage::addOutgoingLink(string outgoinglink) {
	outgoinglinks_vec.push_back(outgoinglink);
}

const vector<string>& WebPage::getIncomingLinkVec() {
	return incominglinks_vec;
}

const vector<string>& WebPage::getOutgoingLinkVec() {
	return outgoinglinks_vec;
}