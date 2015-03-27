/*
This file is part of BGSLibrary.

BGSLibrary is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

BGSLibrary is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with BGSLibrary.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef BGS_AdaptiveSelective_define_hpp
#define BGS_AdaptiveSelective_define_hpp



#include <iostream>
#include <opencv2/opencv.hpp>


#include "../bgs.hpp"

class AdaptiveSelectiveBackgroundLearning : public IBGS
{
private:
  bool firstTime;
  cv::Mat img_background;
  double alphaLearn;
  double alphaDetection;

  long counter;
  long learningFrames;
  double minVal;
  double maxVal;
  int threshold;
  bool showOutput;

public:

  AdaptiveSelectiveBackgroundLearning();
  ~AdaptiveSelectiveBackgroundLearning();

  void process(const cv::Mat &img_input, cv::Mat &img_output, cv::Mat &img_bgmodel);

private:
  void saveConfig();
  void loadConfig();
};

#endif
