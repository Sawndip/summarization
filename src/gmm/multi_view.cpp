#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include "util.h"
#include "Server.h"
#include "VideoSensor.h"
#include "database/Dataset.h"

using namespace cv;
using std::vector;

int main(int argc, char** argv)
{
    srand(time(NULL));
    if (argc != 2)
    {
        printf("usage: %s <dataset>\n", argv[0]);
        return -1;
    }

    vector<VideoSensor> sensors;
    Dataset set(argv[1]);
    for (int i=0, n=set.getVideoInfo().size(); i<n; ++i) {
        VideoInfo info = set.getVideoInfo()[i];
        VideoCapture cap(info.path);
        sensors.push_back(VideoSensor(cap, info.offset));
    }

    if (sensors.size() == 0)
    {
        printf("There is no video files found.\n");
        return -1;
    }

    int w = sensors[0].getWidth();
    int h = sensors[0].getHeight();
    VideoWriter writer("output.avi", CV_FOURCC('M', 'P', 'E', 'G'), 30, Size(w, h));

    Server server(sensors, writer);
    server.run();

    return 0;
}

