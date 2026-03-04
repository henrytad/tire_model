#include "tire_file_parser.hpp"
#include <fstream>
#include <stdexcept>
#include <map>
#include <cctype>
#include <algorithm>

namespace tire_model {

std::string trim(const std::string& str) {
    // Find first non-whitespace character (handles space, tab, \r, \n, etc.)
    auto first = std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    });
    if (first == str.end()) return "";

    // Find last non-whitespace character
    auto last = std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base();
    
    return std::string(first, last);
}

std::optional<std::pair<std::string, std::string>> parseParameterLineString(const std::string& line) {
    // Remove comments (everything after $)
    size_t commentPos = line.find('$');
    std::string cleanLine = (commentPos != std::string::npos) ? line.substr(0, commentPos) : line;
    
    // Find equals sign
    size_t eqPos = cleanLine.find('=');
    if (eqPos == std::string::npos) return std::nullopt;
    
    // Extract parameter name (before =)
    std::string paramName = trim(cleanLine.substr(0, eqPos));
    
    // Extract value (after =)
    std::string value = trim(cleanLine.substr(eqPos + 1));
    
    // Remove quotes if present
    if (value.length() >= 2 && value.front() == '\'' && value.back() == '\'') {
        value = value.substr(1, value.length() - 2);
    }
    
    return std::make_pair(paramName, value);
}

std::optional<double> safeStod(const std::string& str) {
    try {
        return std::stod(str);
    } catch (...) {
        return std::nullopt;
    }
}

double getDoubleFromMap(const std::map<std::string, std::string>& params, const std::string& key, double defaultValue) {
    auto it = params.find(key);
    if (it != params.end()) {
        std::optional<double> val = safeStod(it->second);
        if (val.has_value()) {
            return *val;
        }
    }
    return defaultValue;
}

std::string getStringFromMap(const std::map<std::string, std::string>& params, const std::string& key, const std::string& defaultValue) {
    auto it = params.find(key);
    if (it != params.end()) {
        return it->second;
    }
    return defaultValue;
}

std::map<std::string, std::string> parseTirFile(const std::string& filename) {
    std::map<std::string, std::string> params;
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open tire parameter file: " + filename);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::string trimmed = trim(line);
        // Skip empty lines and comments and section headers
        if (trimmed.empty() || trimmed[0] == '!' || trimmed[0] == '$' || trimmed[0] == '[') {
            continue;
        }
        
        // Parse parameter line (both string and numeric are stored as strings)
        std::optional<std::pair<std::string, std::string>> result = parseParameterLineString(line);
        if (result) {
            const auto& [name, val] = *result;
            params[name] = val;
        }
    }
    
    return params;
}

TireModelType detectModelType(const std::map<std::string, std::string>& params) {
    auto fitTypIt = params.find("FITTYP");
    if (fitTypIt != params.end()) {
        const std::string& fitTypStr = fitTypIt->second;
        if (fitTypStr == "61") {
            return TireModelType::MF612;
        }
        // Found FITTYP but it's not 61
        throw std::runtime_error("Unsupported tire model type detected: FITTYP = " + fitTypStr + ". Only FITTYP = 61 (MF6.1) is currently supported.");
    }
    
    // No model type found in file
    throw std::runtime_error("Could not determine tire model type from parameter file. Expected FITTYP = 61 (MF6.1). Only MF6.1 is currently supported.");
}

} // namespace tire_model
