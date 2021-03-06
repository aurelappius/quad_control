#include "compensators.h"

// load parameters from yaml file
YAML::Node yaml = YAML::LoadFile("app_quad_control/parameters/params.yaml");
// read values from yaml file
const float quad_rotor_radius = yaml["quad_rotor_radius"].as<float>();
const float quad_rotor_distance = yaml["quad_rotor_distance"].as<float>();
const float sanchez_constant = yaml["sanchez_constant"].as<float>();
const float rho_air = yaml["rho_air"].as<float>();
const float quadcopter_mass = yaml["quadcopter_mass"].as<float>();
const float g = yaml["g"].as<float>();

const float T_h = quadcopter_mass * g / 4; // hover thrust of one rotor[N]

float CheesemanCompensator(float thrust_ref, float z)
{
    return thrust_ref * (1.0 - std::pow((quad_rotor_radius / (4 * z)), 2));
}
// Nobahari compensator (R_eq = 2.5*R)
float NobahariCompensator(float thrust_ref, float z)
{
    return thrust_ref *
           (1.0 - std::pow((2.5 * quad_rotor_radius / (4 * z)), 2));
}

// Hayden compensator
float HaydenCompensator(float thrust_ref, float z)
{
    return thrust_ref * std::pow(0.9926 + 0.03794 * 4 * quad_rotor_radius *
                                              quad_rotor_radius / (z * z),
                                 (-2.0 / 3.0));
}

// Sanchez compensator
float SanchezCompensator(float thrust_ref, float z)
{
    float d = quad_rotor_distance;
    float R = quad_rotor_radius;
    return thrust_ref *
           (1 - std::pow(R / (4 * z), 2) -
            R * R * (z / std::pow(std::pow(d * d + 4 * z * z, 3), 0.5)) -
            0.5 * R * R *
                (z / std::pow(std::pow(2 * d * d + 4 * z * z, 3), 0.5) *
                 sanchez_constant));
}

// Appius Static Compensator
float AppiusCompensator(float thrust_ref, float z)
{
    return thrust_ref / (0.11413538 * std::exp(-5.38792044 * z) + 1.0275278);
}

float CheesemanDynamicCompensator(float thrust_ref, float z, float v)
{
    const float v_h = std::sqrt(T_h / (2 * rho_air * M_PI * quad_rotor_radius));
    return thrust_ref * (1.0 - (std::pow((quad_rotor_radius / (4 * z)), 2) / (1 + (std::pow((v / v_h), 2)))));
}

// Kan compensator with forward_speed
float KanDynamicCompensator(float thrust_ref, float z, float v)
{
    const float v_h = std::sqrt(T_h / (2 * rho_air * M_PI * quad_rotor_radius));
    return thrust_ref * ((1 + (50 / 3) * std::pow((v / v_h), 3)) / (1 - ((3 * quad_rotor_radius) / (25 * z))));
}