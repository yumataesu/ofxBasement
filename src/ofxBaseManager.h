#pragma once

#ifndef ofxBaseManager_h
#define ofxBaseManager_h

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <type_traits>
#include <algorithm>
#include <functional>

#include "ofxBaseBehavior.h"

namespace ofx {
namespace Base {
template<typename manage_type>
class BaseManager {
    using ref = std::shared_ptr<manage_type>;
    
public:
    virtual ~BaseManager(){}
    
    template<typename type, typename ... arguments>
    static void register_(const std::string& name, arguments&& ... args) {
		registered_names().push_back(name);
        ctor_map<arguments ...>()[name] = [](arguments&& ... args) {
            return std::make_shared<type>(std::forward<arguments>(args)...);
        };
    }
    
    template <typename ... arguments>
    ref add(const std::string& name, arguments && ... args) {
        auto ctor = make_ctor(name, std::forward<arguments>(args) ...);
        process_map[name] = ctor;
        
        return ctor;
    }
    
    void remove(const std::string& name) {
		process_map.erase(name);
    }

    virtual void update(ofEventArgs& args) {
		delta_time_ = ofGetLastFrameTime();
        for(const auto& c : process_map) {
            c.second->update(delta_time_);
        }
    }
    
    void drawGui(ofxImGui::Settings& settings) {
        for(const auto& c : process_map) {
            c.second->drawGui(settings);
        }
    }
    
    static std::vector<std::string>& registered_names() {
        static std::vector<std::string> _;
        return _;
    }

	ref getByName(const std::string& name) {
		auto it = process_map.find(name);
		if (it != process_map.end()) {
			return it->second;
		}
		else {
			return nullptr;
		}
	}
    
protected:
    template <typename ... arguments>
    static ref make_ctor(const std::string &name, arguments && ... args) {
        return ctor_map<arguments ...>().at(name)(std::forward<arguments>(args) ...);
    }
    
    template <typename ... arguments>
    static std::map<std::string, std::function<ref(arguments&& ... args)>>& ctor_map() {
        static std::map<std::string, std::function<ref(arguments&& ... args)>> _;
        return _;
    }

    std::map<std::string, ref> process_map;
	double delta_time_;
};
}
}
#endif
