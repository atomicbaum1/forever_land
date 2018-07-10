
//
// Created by Matthew Baum on 12/15/17.
// Copyright (c) 2017 Arctic Fox Studio, LTD. All rights reserved.
//

#pragma once
#include <string>

class System {
private:
    static std::string _sdlVersionString;
public:
    static const std::string &getSdlVersions();

public:
    System() = default;
    virtual ~System() = default;

};



