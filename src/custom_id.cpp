//
// CustomId Project
// Copyright (C) 2022 by Contributors <https://github.com/Tyill/custom_id>

#include "../include/custom_id.h"
#include "symbol_Id.h"

#include <mutex>
#include <regex>

using namespace std;
    
class CustomId::Impl {
public:
    Impl();

    bool setCurrentId(const string& id);

    string nextId();

private:
    std::vector<SymbolId> m_currentId;
    std::mutex m_mtx;
    const std::string m_alfabet = "ABCEHIKLNOPRSTUWXYZ";
    std::regex m_templ;
};

CustomId::Impl::Impl() {
    m_templ = std::regex("[" + m_alfabet + "][1-9](-[" + m_alfabet + "][1-9]){0,9}");
}

bool CustomId::Impl::setCurrentId(const string& id) {
   std::lock_guard<std::mutex> lck(m_mtx);

//1. ������ ������������� ������������������ ����� ��� �A1�, ������ � �A2�, ������ - �A3� � ��� �����.�� �A9� ������� �B1�.��������� ����� �Z9� ����� ��� �A1 - A1�, ����� �A1 - A2� � ��� �����.����� �A1 - Z9� ������� �A2 - A1�.
//2. ������������ ����� �������������� - ������ ����� �� ��� �������.
//3. � ��������������� ������� �� ������ �������������� ����� �D�, �F�, �G�, �J�, �M�, �Q�, �V� � ����� �0�.
    
  if (std::regex_match(id, m_templ)) {
      
      m_currentId.clear();
      for (size_t i = 0; i < id.size(); i += 3) {
          m_currentId.emplace_back(m_alfabet);
          m_currentId.back().setValue(id.substr(i, 2));
      }
      return true;
  }
  return false;
}

string CustomId::Impl::nextId() {
    std::lock_guard<std::mutex> lck(m_mtx);

    if (m_currentId.empty()) {
        m_currentId.emplace_back(m_alfabet);
        return m_currentId[0].value();
    }

    for (size_t i = m_currentId.size() - 1; i >= 0; --i) {
        if (!m_currentId[i].increment()) {
            for (size_t j = i; j < m_currentId.size(); ++j) {
                m_currentId[j].reset();
            }
            if (i == 0) {
                m_currentId.emplace_back("A1");

                if (m_currentId.size() > 10) {
                    m_currentId.resize(1);
                }
                break;
            }
        }
        else break;
    }

    string idStr = m_currentId[0].value();
    for (size_t i = 1; i < m_currentId.size(); ++i) {
        idStr += "-" + m_currentId[i].value();
    }

    return idStr;
}


bool CustomId::setCurrentId(const string& id) {
    return m_d ? m_d->setCurrentId(id) : false;
}
string CustomId::nextId() {
    return m_d ? m_d->nextId() : "";
}

CustomId::CustomId() {
    m_d = new Impl();
}
CustomId::~CustomId() {
    if (m_d) delete m_d;
}
CustomId::CustomId(CustomId&& other) {
    m_d = other.m_d;
    other.m_d = nullptr;
}
CustomId& CustomId::operator=(CustomId&& other) {
    if (this != &other) {
        if (m_d) delete m_d;

        m_d = other.m_d;
        other.m_d = nullptr;
    }
    return *this;
}