#include <gtest/gtest.h>
#include "tire_model/tire_model.hpp"
#include <variant>

using namespace tire_model;

class GetParamTest : public ::testing::Test {
protected:
    TireModel model{"sample.tir"};
};

TEST_F(GetParamTest, NumericParamReturnsDouble) {
    std::optional<TireParam> result = model.getParam("VERTICAL_STIFFNESS");
    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(std::holds_alternative<double>(*result));
    EXPECT_DOUBLE_EQ(std::get<double>(*result), 209651.0);
}

TEST_F(GetParamTest, StringParamReturnsString) {
    std::optional<TireParam> result = model.getParam("LENGTH");
    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(std::holds_alternative<std::string>(*result));
    EXPECT_EQ(std::get<std::string>(*result), "meter");
}

TEST_F(GetParamTest, MissingParamReturnsNullopt) {
    EXPECT_FALSE(model.getParam("DOES_NOT_EXIST").has_value());
}
