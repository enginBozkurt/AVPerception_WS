#ifndef DETECTION_RADAR_TRACKER_H
#define DETECTION_RADAR_TRACKER_H

#include <ros/ros.h>
#include <raw_data/RadarRawArray.h>
#include <detection/Target.h>
#include <detection/TargetArray.h>
#include "detection/object.h"
#include "detection/dbscan.h"
#include "detection/GNN.h"

class RadarTracker
{
public:
    RadarTracker(void);
    ~RadarTracker();

    void EKF(const raw_data::RadarRawArray& input);
    void InitTrack(const RadarObject &obj);
    void Predict(void);
    void MatchGNN(const std::vector<RadarObject>& src);
    void Update(const std::vector<RadarObject>& src);
    void RemoveTrack(int index);
    bool IsConverged(int track_index);
    void PubRadarTracks(void);
    void GetTimeStamp(ros::Time& stamp);
    void GetRadarTrack(std::vector<LocalTrack>& tracks);

private:
    std::vector<vector6d> X, X_;  // rx ry vx vy ax ay
    std::vector<matrix6d> P, P_;
    std::vector<ObjectInfo> track_info;
    matrix6d init_P;
    matrix6d F;
    matrix6d Q;
    matrix3d R;

    std::vector<std::pair<int, int> > matched_pair;
    std::vector<bool> prev_matched;
    std::vector<bool> src_matched;

    double ts;
    ros::Time time_stamp;
};

#endif // DETECTION_RADAR_TRACKER_H