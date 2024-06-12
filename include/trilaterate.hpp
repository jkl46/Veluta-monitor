#ifndef TRILATERATE_HPP
#define TRILATERATE_HPP

# define M_PI 3.14159265358979323846
#define PYTHAG(x1, x2) sqrt(pow(x1, 2.0) + pow(x2, 2.0))

typedef struct {
	double x;
	double y;
} point_t;

typedef struct {
	point_t pos;
	double r;
} circle_t;

typedef struct {
	point_t pos;
	double slope;
} line_t;

typedef struct {
  double lat;
  double lon;
} coord_t;

typedef struct {
  coord_t *pos;
  double r;
} record_t;


// Function prototypes

int circle_circle_intersection(circle_t circle0, circle_t circle1, point_t *point1, point_t *point2);

int line_line_intersect(line_t line1, line_t line2, point_t *result);

double lon_degree_distance(double lon);

double lat_degree_distance(double lat);

double get_distance(coord_t point1, coord_t point2);

int trilaterate(record_t record1, record_t record2, record_t record3, coord_t *trilaterationCoord, coord_t *intersectionCoord);

int point_to_coord(coord_t base, point_t point, coord_t *result);

int estimate(int argc, char **argv);

double get_difference(double a, double b);
#endif // TRILATERATE_HPP
