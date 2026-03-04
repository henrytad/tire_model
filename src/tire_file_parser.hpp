#pragma once

#include "tire_model_base.hpp"
#include <string>
#include <optional>
#include <utility>
#include <map>

namespace tire_model {

/**
 * @brief Trim whitespace from the beginning and end of a string
 */
std::string trim(const std::string& str);

/**
 * @brief Parse a line and extract parameter name and string value
 * 
 * Handles comments (everything after $) and removes quotes.
 * 
 * @param line Input line from .tir file
 * @return Pair of (parameter name, value) if parsing succeeded, empty optional otherwise
 */
std::optional<std::pair<std::string, std::string>> parseParameterLineString(const std::string& line);

/**
 * @brief Safely convert a string to a double
 * 
 * @param str String to convert
 * @return Optional double value, empty if conversion fails
 */
std::optional<double> safeStod(const std::string& str);

/**
 * @brief Safely get a double value from a parameter map
 * 
 * @param params Parameter map
 * @param key Parameter key to look up
 * @param defaultValue Default value if key not found or conversion fails
 * @return Double value from map or default value
 */
double getDoubleFromMap(const std::map<std::string, std::string>& params, const std::string& key, double defaultValue = 0.0);

/**
 * @brief Safely get a string value from a parameter map
 * 
 * @param params Parameter map
 * @param key Parameter key to look up
 * @param defaultValue Default value if key not found
 * @return String value from map or default value
 */
std::string getStringFromMap(const std::map<std::string, std::string>& params, const std::string& key, const std::string& defaultValue = "");

/**
 * @brief Parse a .tir file into a parameter map (internal use only)
 * 
 * @param filename Path to the .tir parameter file
 * @return Map of parameter names to string values
 */
std::map<std::string, std::string> parseTirFile(const std::string& filename);

/**
 * @brief Detect tire model type from parameter map (internal use only)
 * 
 * @param params Parameter map from parsed .tir file
 * @return Detected tire model type
 * @throws std::runtime_error if the model type cannot be determined or is not supported
 */
TireModelType detectModelType(const std::map<std::string, std::string>& params);

} // namespace tire_model
