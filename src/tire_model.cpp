#include "tire_model/tire_model.hpp"
#include "tire_model/internal/tire_file_parser.hpp"
#include <stdexcept>
#include <map>

using namespace tire_model;
using namespace tire_model::internal;

namespace {
    std::variant<TireMF612> makeModel(const std::string& filename) {
        std::map<std::string, std::string> params = parseTirFile(filename);
        TireModelType type = detectModelType(params);
        switch (type) {
            case TireModelType::MF612:
                return TireMF612(params);
            default:
                throw std::runtime_error("Unsupported tire model type");
        }
    }
}

TireModel::TireModel(const std::string& filename)
    : model_(makeModel(filename))
{
}

TireForces TireModel::evaluate(const TireInput& input) const {
    return std::visit([&input](const auto& m) { return m.evaluate(input); }, model_);
}
