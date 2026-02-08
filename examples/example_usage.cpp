#include "tire_model/tire_model.hpp"
#include <iostream>

int main() {
    try {
        // Create a tire model - automatically detects model type from file
        // Note: The sample.tir file is copied to the build directory by CMake
        tire_model::TireModel tire("sample.tir");
        
        // Evaluate tire forces and moments
        tire_model::TireInput input{
            .Fz = 5000.0,
            .alpha = 0.1,
            .kappa = 0.05,
            .gamma = 0.0,
            .Vcx = 10.0
        };
        
        tire_model::TireForces forces = tire.evaluate(input);
        
        std::cout << "Tire Forces:" << std::endl;
        std::cout << "  Fx (Longitudinal): " << forces.Fx << " N" << std::endl;
        std::cout << "  Fy (Lateral): " << forces.Fy << " N" << std::endl;
        std::cout << "  Mz (Aligning Moment): " << forces.Mz << " Nm" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

