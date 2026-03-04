#include "tire_model_base.hpp"
#include "tire_file_parser.hpp"
#include <utility>

namespace tire_model {

TireModelBase::TireModelBase(std::map<std::string, std::string> rawParams)
    : rawParams_(std::move(rawParams))
{
}

std::optional<TireParam> TireModelBase::getParam(const std::string& key) const {
    std::map<std::string, std::string>::const_iterator it = rawParams_.find(key);
    if (it == rawParams_.end()) return std::nullopt;
    std::optional<double> d = safeStod(it->second);
    if (d.has_value()) return *d;
    return it->second;
}

} // namespace tire_model
