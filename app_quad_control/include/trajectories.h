#pragma once
#include <Eigen/Dense>
#include <iostream>
#include <cmath>
/* BENCHMARK TRAJECTORIES */
// vertical step response from 1.20 m to 0.20 m with forward speed
void circleStepResponse(float t, Eigen::Vector3f &pos,
                        Eigen::Vector3f &pos_ref, float &yaw_ref);

// test the vertical speed controller
void verticalSpeedController(float t, Eigen::Vector3f &pos,
                             Eigen::Vector3f &pos_ref, float &yaw_ref);

// oscillations
void oscillations(float t, Eigen::Vector3f &pos,
                  Eigen::Vector3f &pos_ref, float &yaw_ref);

// velocity control
void velocityControl(float t, Eigen::Vector3f &pos, Eigen::Vector3f &pos_ref, float &yaw_ref, Eigen::Vector3f &vel_ref);
void velocityStepResponse(float t, Eigen::Vector3f &pos, Eigen::Vector3f &pos_ref, float &yaw_ref, Eigen::Vector3f &vel_ref, float v);

/* DATA COLLECTION TRAJECTORIES */
// quasi static flying for simple GE Model
void staticDataCollection(float t, Eigen::Vector3f &pos,
                          Eigen::Vector3f &pos_ref, float &yaw_ref);

// vertical speed flying for more advanced GE Model
void verticalSpeedDataCollection(float t, Eigen::Vector3f &pos,
                                 Eigen::Vector3f &pos_ref, float &yaw_ref);

// omnidirectional flying for most advanced GE Model
void velocityDataCollection(float t, Eigen::Vector3f &pos, Eigen::Vector3f &pos_ref, float &yaw_ref, Eigen::Vector3f &vel_ref);

// helper functions for velocityDataCollection()
void flyfwd(float x_max, float height, float y, float speed, Eigen::Vector3f &pos, Eigen::Vector3f &pos_ref, float &yaw_ref, Eigen::Vector3f &vel_ref);
void flybwd(float x_min, float height, float y, float speed, Eigen::Vector3f &pos, Eigen::Vector3f &pos_ref, float &yaw_ref, Eigen::Vector3f &vel_ref);

// swoop test
void swoop(float t, Eigen::Vector3f &pos, Eigen::Vector3f &pos_ref, float &yaw_ref, Eigen::Vector3f &vel_ref, float v);