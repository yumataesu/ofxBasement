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
    virtual void update(const double& delta_time) = 0;
    virtual void draw() {};
    
	void setName(const std::string& name) { name_ = name; }
	const std::string& getName() { return name_; }
    
    virtual void bang() {}
    
protected:
    std::string name_;
	ofParameterGroup parameter_group_;
};
}
}
#endif