#include "tire_model/tire_model.hpp"
#include "tire_file_parser.hpp"
#include "mf612/tire_mf612.hpp"
#include <stdexcept>
#include <map>
#include <optional>
#include <variant>

using namespace tire_model;

struct TireModel::ModelVariant {
    std::variant<TireMF612> model;
};

namespace {
    std::variant<TireMF612> makeModel(const std::string& filename) {
        std::map<std::string, std::string> params = parseTirFile(filename);
        TireModelType type = detectModelType(params);
        switch (type) {
            case TireModelType::MF612:
                return TireMF612(std::move(params));
            default:
                throw std::runtime_error("Unsupported tire model type");
        }
    }
}

TireModel::TireModel(const std::string& filename)
    : modelVariant_(std::make_unique<ModelVariant>(makeModel(filename)))
{
}

TireModel::~TireModel() = default;

TireModel::TireModel(const TireModel& other)
    : modelVariant_(std::make_unique<ModelVariant>(*other.modelVariant_))
{
}

TireModel& TireModel::operator=(const TireModel& other) {
    if (this != &other) {
        modelVariant_ = std::make_unique<ModelVariant>(*other.modelVariant_);
    }
    return *this;
}

TireModel::TireModel(TireModel&&) noexcept = default;
TireModel& TireModel::operator=(TireModel&&) noexcept = default;

TireForces TireModel::evaluate(const TireInput& input) const {
    return std::visit([&input](const auto& m) { return m.evaluate(input); }, modelVariant_->model);
}

std::optional<TireParam> TireModel::getParam(const std::string& key) const {
    return std::visit([&key](const auto& m) { return m.getParam(key); }, modelVariant_->model);
}
