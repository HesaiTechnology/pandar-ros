/* -*- mode: C++ -*- */
/*
 *  Copyright (C) 2009, 2010 Austin Robot Technology, Jack O'Quin
 *  Copyright (C) 2011 Jesse Vera
 *  Copyright (C) 2012 Austin Robot Technology, Jack O'Quin
 *  Copyright (c) 2017 Hesai Photonics Technology, Yang Sheng
 *  License: Modified BSD Software License Agreement
 *
 *  $Id$
 */

/** @file

    This class converts raw Pandar40 3D LIDAR packets to PointCloud2.

*/

#ifndef _PANDAR_POINTCLOUD_CONVERT_H_
#define _PANDAR_POINTCLOUD_CONVERT_H_ 1

#include <ros/ros.h>

#include <sensor_msgs/PointCloud2.h>
#include <pandar_pointcloud/rawdata.h>

#include <dynamic_reconfigure/server.h>
#include <pandar_pointcloud/CloudNodeConfig.h>

namespace pandar_pointcloud
{
class Convert
{
public:

    Convert(ros::NodeHandle node, ros::NodeHandle private_nh);
    ~Convert() {}

private:

    void callback(pandar_pointcloud::CloudNodeConfig &config,
                  uint32_t level);
    void processScan(const pandar_msgs::PandarScan::ConstPtr &scanMsg);

    ///Pointer to dynamic reconfigure service srv_
    boost::shared_ptr<dynamic_reconfigure::Server<pandar_pointcloud::
    CloudNodeConfig> > srv_;

    boost::shared_ptr<pandar_rawdata::RawData> data_;
    ros::Subscriber pandar_scan_;
    ros::Publisher output_;

    /// configuration parameters
    typedef struct {
        int npackets;                    ///< number of packets to combine
    } Config;
    Config config_;
};

} // namespace pandar_pointcloud

#endif // _PANDAR_POINTCLOUD_CONVERT_H_