//
// CustomId Project
// Copyright (C) 2022 by Contributors <https://github.com/Tyill/custom_id>


#pragma once

#include <string>

class CustomId {

public:
    explicit CustomId();
    ~CustomId();

    CustomId(const CustomId&) = delete;
    CustomId(CustomId&&);
    CustomId& operator=(const CustomId&) = delete;
    CustomId& operator=(CustomId&&);
    
    /// Set current id
    /// @param id 
    /// return true - ok
    bool setCurrentId(const std::string& id);
  
    /// Get next id
    /// return id
    std::string nextId();

private:
    class Impl;
    Impl* m_d = nullptr;  
};