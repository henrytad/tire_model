#include "tire_model/tire_model.hpp"
#include "tire_model/internal/tire_model_base.hpp"
#include "tire_model/internal/tire_mf612.hpp"
#include "tire_model/internal/tire_file_parser.hpp"
#include <stdexcept>
#include <memory>
#include <map>

using namespace tire_model;
using namespace tire_model::internal;

namespace {
    std::unique_ptr<TireModelBase> createModel(const std::string& filename) {
        // Parse the entire file into a map
        std::map<std::string, std::string> params = parseTirFile(filename);
        
        // Detect model type from parameters
        TireModelType type = detectModelType(params);
        
        switch (type) {
            case TireModelType::MF612: return std::make_unique<TireMF612>(params);
            default: throw std::runtime_error("Unsupported tire model type");
        }
    }
}

TireModel::TireModel(const std::string& filename)
    : model_(createModel(filename))
{
}

TireModel::~TireModel() = default;

TireForces TireModel::evaluate(const TireInput& input) const {
    return model_->evaluate(input);
}
