#pragma once

#include "ofMain.h"

class obstacle {
   private:
	   int obstacle_x;
	   int obstacle_y;
	   int obstacle_width;
	   int obstacle_height;

	   ofVec2f window_dims;
	   static const float obstacle_proportion_scalar;

	   ofRectangle obstacle_hitbox;
	   ofColor obstacle_color;

   public:
       obstacle(int x, int y);
	   obstacle(int x, int y, int width, int height);

	   int get_obstacle_x() const;
       int get_obstacle_y() const;
       int get_obstacle_width() const;
       int get_obstacle_height() const;
};
