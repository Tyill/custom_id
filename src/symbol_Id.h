//
// CustomId Project
// Copyright (C) 2022 by Contributors <https://github.com/Tyill/custom_id>

#include <string>

class SymbolId{
public:
    SymbolId(const std::string& alfabet = "") :
        m_alfabet(alfabet){
        reset();
    }

    void reset() {
        m_value = "A1";
    }

    void setValue(const std::string& val) {
        m_value = val;
    }

    std::string value() {
        return m_value;
    }

    /// return - has next?
    bool increment() {
        int cnum = m_value.back() - 48;
        if (cnum < 9) {
            ++cnum;
            m_value.back() = cnum + 48;
            return true;
        }
       
        char csymb = *(m_value.end() - 2);
        char nextSymb = ' ';
        for (size_t i = 0; i < m_alfabet.size() - 1; ++i) {
            if (csymb == m_alfabet[i]) {
                nextSymb = m_alfabet[i + 1];
                break;
            }
        }
        bool hasNext = nextSymb != ' ';

        if (hasNext) {
            *(m_value.end() - 2) = nextSymb;
            *(m_value.end() - 1) = 1 + 48;
        }        
        return hasNext;
    }

private:
    std::string m_value;
    std::string m_alfabet;
};