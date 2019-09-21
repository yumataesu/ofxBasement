#pragma once

#ifndef ofxBaseBehavior_h
#define ofxBaseBehavior_h

#include "ofParameter.h"
#include "ofxImGui.h"

namespace ofx {
namespace Base {
class Behavior {
public:
    virtual ~Behavior() {};
    
	void setName(const std::string& name) { parameter_group_.setName(name); }
	const std::string& getName() { return parameter_group_.getName(); }
    
protected:
	ofParameterGroup parameter_group_;
};
}
}
#endif