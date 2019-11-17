#pragma once

constexpr int DEFAULT_OBSTACLE_WIDTH = 40;
constexpr int DEFAULT_OBSTACLE_HEIGHT = 40;

class obstacle {
   private:
	   int obstacle_x;
	   int obstacle_y;
	   int obstacle_width;
	   int obstacle_height;

   public:
       obstacle(int x, int y);
	   obstacle(int x, int y, int width, int height);

	   int get_obstacle_x() const;
       int get_obstacle_y() const;
       int get_obstacle_width() const;
       int get_obstacle_height() const;
};
