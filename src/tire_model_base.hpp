#pragma once

#include "tire_model/tire_types.hpp"
#include <map>
#include <optional>
#include <string>

namespace tire_model {

/**
 * @brief Enumeration of supported tire model types
 */
enum class TireModelType {
    MF612,  // Magic Formula 6.1.2
    // Future models can be added here
};

/**
 * @brief Base class for all tire model implementations
 */
class TireModelBase {
public:
    virtual ~TireModelBase() = default;

    virtual TireForces evaluate(const TireInput& input) const = 0;

    /// Looks up any raw parameter from the .tir file by key.
    /// Returns nullopt if the key is absent; double if numeric, string otherwise.
    std::optional<TireParam> getParam(const std::string& key) const;

protected:
    TireModelBase() = default;
    explicit TireModelBase(std::map<std::string, std::string> rawParams);

    /// Read-only access to the raw .tir file parameters for use in subclass constructors.
    const std::map<std::string, std::string>& rawParams() const { return rawParams_; }

private:
    std::map<std::string, std::string> rawParams_;
};

} // namespace tire_model

