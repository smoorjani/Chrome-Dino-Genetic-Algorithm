#pragma once

#include "ofMain.h"

constexpr float OBSTACLE_VELOCITY = 5;
constexpr float SPEED_FACTOR = 0.00025;
constexpr int MAX_NUMBER_OF_OBSTACLES = 5;

class obstacle {
   private:
	   float obstacle_x;
	   float obstacle_y;
	   float obstacle_x_velocity;
	   float obstacle_width;
	   float obstacle_height;

	   ofVec2f window_dims;
	   static const float obstacle_proportion_scalar;

	   ofImage obstacle_image;
	   ofRectangle obstacle_hitbox;
	   ofColor obstacle_color;

   public:
       obstacle(float x, float y);
	   obstacle(float x, float y, float width, float height);

	   float get_obstacle_x() const;
	   float get_obstacle_y() const;
	   float get_obstacle_width() const;
	   float get_obstacle_height() const;

	   float get_velocity_x() const;
	   void set_velocity_x(float x_velocity);

	   ofRectangle get_obstacle_hitbox();
	   ofColor get_obstacle_color();

	   ofImage get_obstacle_image();
	   void set_obstacle_image(ofImage& img);
	   void setup_image(std::string& filepath);

	   void update_obstacle_position(float new_x, float new_y);
	   void update(float previous_obstacle_x);
};
