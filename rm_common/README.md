# rm_common模块

## 1.简介

rm_common是rmoss_core 中的一个公共基础包，提供一些公共基础工具及功能。主要实现了以下几个功能：

* 提供一些调试工具（如在图像上绘制四边形，显示图片，调试开关等）
* 提供一些简单图像处理工具（如基于单目视觉的3D位置解算工具，数学公式函数实现等等）

## 2.文件说明

主要文件：

|          文件           |                         功能描述                          |
| :---------------------: | :-------------------------------------------------------: |
|     definition.hpp     |          公共定义（暂未使用）          |
| debug.hpp/cpp | 调试工具，相关调试工具 |
|       math.hpp/cpp        |          数学工具，提供一些图像处理或计算相关工具           |
| mono_measure_tool.hpp/cpp | 单目测量工具类，单目算法封装（PNP解算，相似三角形反投影等） |

## 3.快速使用

#### debug模块

静态调试开关：控制是否显示调试信息

```c++
//获取调试开关状态，默认为false，
rm_common::isDebug();
//设置静态调试开关
rm_common::setDebug(true);
```

通用调试宏定义

```c++
//DEBUG_TOOL(text);text为一条语句 ，如果静态调试开关为false，括号里面的语句不会被执行。
DEBUG_TOOL(imshow("dst", dst));
DEBUG_TOOL(cout<<"data"<<endl);
```

图像调试宏定义

```c++
//在图像上绘制多边形，受静态调试开关控制
void drawRotatedRect(cv::Mat &img,cv::RotatedRect r,cv::Scalar color=green);
void draw4Point4f(cv::Mat &img, cv::Point2f *point2fs,cv::Scalar color=green);
void drawConvexHull(cv::Mat &img,std::vector<cv::Point2f> points,cv::Scalar color=green);
```

#### math模块

提供相关图像计算工具

```c++
//两点构成直线的倾角，结果为度，相对常规坐标系，（不同于图像坐标系）常规坐标系y轴方向为向上。
float calcInclineAngle(cv::Point2f point1, cv::Point2f point2);
//三角形的角度，第一个参数为顶点坐标,结果为度
float calcInnerAngle(cv::Point2f vertexPoint, cv::Point2f point1, cv::Point2f point2);
```

#### mono_measure_tool模块

工具类，主要包括基于PNP，和相似三角形投影算法的单目3d点位置解算。

* 详见文档[mono_measure_tool.md](doc/mono_measure_tool.md)

## 4.维护者及开源许可证

* wyx 1418555317@qq.com
* Zhenpeng Ge,  zhenpeng.ge@qq.com

* rm_common is provided under MIT