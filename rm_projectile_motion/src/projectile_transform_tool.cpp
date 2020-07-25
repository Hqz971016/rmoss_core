/*******************************************************************************
 *  Copyright (c) 2020 robomaster-oss, All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify it 
 *  under the terms of the MIT License, See the MIT License for more details.
 *
 *  You should have received a copy of the MIT License along with this program.
 *  If not, see <https://opensource.org/licenses/MIT/>.
 *
 ******************************************************************************/
#include <opencv2/opencv.hpp>
#include "rm_projectile_motion/projectile_transform_tool.h"

using namespace rm_projectile_motion;
using namespace std;


void ProjectileTransformTool::setModel(ProjectileModelInterface *model){
    model_ = model;
}

int ProjectileTransformTool::transform(cv::Point3f position, float &pitch, float &yaw){
    if(model_==NULL){
        pitch = -(float)(atan2(position.z, position.x));
    }else{
        float angle;
        if(model_->inverse_solve( position.z,position.x,angle)!=0){
            return -1;   
        }
        pitch = -angle;
    }
    yaw = (float)(atan2(position.y, position.x));
    return 0;
}