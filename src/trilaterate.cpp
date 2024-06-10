// trilaterate.cpp is used for trilaterating using decimal degrees
// usage
// create 3 circles defined by their middle point and radius with record_t
// create 2 coord_t variables that hold the trilateration and triangulation point
// use int trilaterate(record_t, record_t, record_t, coord_t*, coord_t*) with parameters

#include <math.h>
#include "trilaterate.hpp"

// Calculate radian from degree
#define DEGREE_TO_RAD(degree) (degree * M_PI / 180.0)

// Formula for length of degree longitude at latitude 'lat'. Reference: https://en.wikipedia.org/wiki/Geographic_coordinate_system
#define lon_degree_distance(lat) (111412.84 * cos(DEGREE_TO_RAD(lat))) - (93.5 * cos(3 * DEGREE_TO_RAD(lat))) + (0.118 * cos(5 * DEGREE_TO_RAD(lat)))
// Formula for length of degree latitude at latitude 'lat'. Reference: https://en.wikipedia.org/wiki/Geographic_coordinate_system
#define lat_degree_distance(lat) (111132.92 - 559.82 * cos(2 * DEGREE_TO_RAD(lat))) + (1.175 * cos(4 * DEGREE_TO_RAD(lat))) + (0.0023 * cos(6 * DEGREE_TO_RAD(lat)))

// Reference: https://paulbourke.net/geometry/circlesphere/
int circle_circle_intersection(circle_t circle1, circle_t circle2, point_t *intersection1, point_t *intersection2)
{
    double a, dx, dy, d, h, rx, ry;
    double x0, x1, x2, y0, y1, y2, r0, r1;
    
    x0 = circle1.pos.x;
    x1 = circle2.pos.x;
    y0 = circle1.pos.y;
    y1 = circle2.pos.y;

    r0 = circle1.r;
    r1 = circle2.r;
    
    /* dx and dy are the vertical and horizontal distances between
    * the circle centers.
    */
    dx = x1 - x0;
    dy = y1 - y0;

    /* Determine the straight-line distance between the centers. */
    //d = sqrt((dy*dy) + (dx*dx));
    d = hypot(dx, dy); // Suggested by Keith Briggs

    /* Check for solvability. */
    if (d > (r0 + r1))
    {
      /* no solution. circles do not intersect. */
      return 0;
    }
    if (d < fabs(r0 - r1))
    {
      /* no solution. one circle is contained in the other */
      return 0;
    }

    /* 'point 2' is the point where the line through the circle
    * intersection points crosses the line between the circle
    * centers.  
    */

    /* Determine the distance from point 0 to point 2. */
    a = ((r0 * r0) - (r1 * r1) + (d * d)) / (2.0 * d) ;

    /* Determine the coordinates of point 2. */
    x2 = x0 + (dx * a/d);
    y2 = y0 + (dy * a/d);

    /* Determine the distance from point 2 to either of the
    * intersection points.
    */
    h = sqrt((r0 * r0) - (a * a));

    /* Now determine the offsets of the intersection points from
    * point 2.
    */
    rx = -dy * (h / d);
    ry = dx * (h / d);

    /* Determine the absolute intersection points. */
    intersection1->x = x2 + rx;
    intersection1->y = y2 + ry;

    intersection2->x = x2 - rx;
    intersection2->y = y2 - ry;
    
    return 1;
}

// Calculate intersection between 2 lines. Store result in point_t p
int line_line_intersect(line_t line1, line_t line2, point_t *result)
{
    if (line1.slope == line2.slope) // No cross section
      return 0;
    
    double a1, c1, a2, c2, b1, b2;
    double xi, yi;

    a1 = line1.slope;
    c1 = line1.pos.x * line1.slope + line1.pos.y;

    a2 = line2.slope;
    c2 = line2.pos.x * line2.slope + line2.pos.y;

    xi = (c2 - c1) / (a1 - a2);
    yi = (a2 * c1 - a1 * c2) / ((a1) - (a2)) * -1;

    result->x = xi;
    result->y = yi;

    return 1;
}

// Calculate length of degree of longitude at latitude x in meters
// Reference: https://en.wikipedia.org/wiki/Geographic_coordinate_system
/* Function has been change to define*/
// double lon_degree_distance(double lon)
// {
//   // Degrees to radians
//   lon = lon * M_PI / 180.0;
//   return (111412.84 * cos(lon)) - (93.5 * cos(3 * lon)) + (0.118 * cos(5 * lon));
// }

// Calculate length of degree of latitude at latitude x in meters
// Reference: https://en.wikipedia.org/wiki/Geographic_coordinate_system
/* Function has been change to define*/
// double lat_degree_distance(double lat)
// {
// 	// Degrees to radians
// 	lat = lat * M_PI / 180.0;
// 	return (111132.92 - 559.82 * cos(2 * lat)) + (1.175 * cos(4 * lat)) + (0.0023 * cos(6 * lat));
// }

int trilaterate(record_t record1, record_t record2, record_t record3, coord_t *trilaterationCoord, coord_t *intersectionCoord)
{
    // Convert GPS into relative positions in meters
    // record1 is base
    double lonLength = lon_degree_distance(record1.pos->lat); // Length of degree longitude in meters
    double latLength = lat_degree_distance(record1.pos->lat); // length of degree latitude in meters

    circle_t circle1, circle2, circle3;
    circle1 = {{0.0, 0.0}, record1.r};
    circle2 = {{
        (record2.pos->lon - record1.pos->lon) * lonLength, 
        (record2.pos->lat - record1.pos->lat) * latLength},
        record2.r };
    circle3 = {{
        (record3.pos->lon - record1.pos->lon) * lonLength,
        (record3.pos->lat - record1.pos->lat) * latLength}, 
        record3.r};



    // Store points in this array
    point_t intersectionPoints[3][2];
    
    if (!circle_circle_intersection(circle1, circle2, &intersectionPoints[0][0], &intersectionPoints[0][1]))
    {
      // TODO: handle error
    }
    if (!circle_circle_intersection(circle2, circle3, &intersectionPoints[1][0], &intersectionPoints[1][1]))
    {
      // TODO: Handle error
    }
    if (!circle_circle_intersection(circle1, circle3, &intersectionPoints[2][0], &intersectionPoints[2][1]))
    {
      // TODO: Handle error
    }

    point_t *closestPoints[3];
    double shortestDistance = 0xFFFFFFFFFFFFFFFF;

    //table connected 1d index to 2d. For easy of use. inefficient.
    point_t *pointMap[6] = {&intersectionPoints[0][0], &intersectionPoints[0][1], &intersectionPoints[1][0], &intersectionPoints[1][1], &intersectionPoints[2][0], &intersectionPoints[2][1]};

    // Find the lowest distance between a group of 3 points
    for (int a = 0; a < 6; a++)
    {
        for (int b = 0; b < 6; b++)
        {
            for (int c = 0; c < 6; c++)
            {
                if(a != b && b != c && a != c)
                {
                    double distance = 
                        PYTHAG(get_difference(pointMap[a]->x, pointMap[b]->x), get_difference(pointMap[a]->y, pointMap[b]->y)) +  // a-b
                        PYTHAG(get_difference(pointMap[b]->x, pointMap[c]->x), get_difference(pointMap[b]->y, pointMap[c]->y)) +  // b-c
                        PYTHAG(get_difference(pointMap[a]->x, pointMap[c]->x), get_difference(pointMap[a]->y, pointMap[c]->y));   // a-c

                    if (distance < shortestDistance)
                    {
                        closestPoints[0] = pointMap[a];
                        closestPoints[1] = pointMap[b];
                        closestPoints[2] = pointMap[c];
                        shortestDistance = distance;
                    }
                }
            }
        }
    }

    // calculate average of intersection
    // TODO: Handle average if no 3 points
    double xAvg, yAvg;
    for (size_t i = 0; i < 3; i++)
    {
        xAvg += closestPoints[i]->x;
        yAvg += closestPoints[i]->y;
    }
    
    // Calculate average and confirm estimated trilateration coordinate
    point_t trilaterationResult = {xAvg / 3, yAvg / 3};
    point_to_coord(*(record1.pos), trilaterationResult, trilaterationCoord);

    // Calculate lines for circle intersections
    // line1 = intersection circle1-circle2
    // line2 = intersection circle2-circle3
    // line3 = intersection circle1-circle3
    line_t line1, line2, line3;

    // Now for the triangulation
    // Construct lines 
    line1 = {intersectionPoints[0][0], (intersectionPoints[0][1].y - intersectionPoints[0][0].y) / (intersectionPoints[0][1].x - intersectionPoints[0][0].x) * -1};  // Line 1-2
    line2 = {intersectionPoints[1][0], (intersectionPoints[1][1].y - intersectionPoints[1][0].y) / (intersectionPoints[1][1].x - intersectionPoints[1][0].x) * -1}; // line 2-3
    line3 = {intersectionPoints[2][0], (intersectionPoints[2][1].y - intersectionPoints[2][0].y) / (intersectionPoints[2][1].x - intersectionPoints[2][0].x) * -1}; // line 1-3
    // At this point lines between intersections have been constructed

    // Calculate crossing point of lines between circle intersections
    point_t lineIntersection[3];
    line_line_intersect(line1, line2, &lineIntersection[0]);
    line_line_intersect(line2, line3, &lineIntersection[1]);
    line_line_intersect(line1, line3, &lineIntersection[2]);

    point_t intersectionResult = {(lineIntersection[0].x + lineIntersection[1].x + lineIntersection[2].x) / 3 * -1, (lineIntersection[0].y + lineIntersection[1].y + lineIntersection[2].y) / 3};
    point_to_coord(*(record1.pos), intersectionResult, intersectionCoord);
    // DONE

    return 1;
}

// Return length in meters between 2 coordinates

double get_distance(coord_t point1, coord_t point2)
{
    double xi, yi;

    double latLength = (lat_degree_distance(point1.lat) + lat_degree_distance(point2.lat)) / 2;
    double lonLength = (lon_degree_distance(point1.lat) + lon_degree_distance(point2.lat)) / 2;

    xi = (point1.lon - point2.lon) * lonLength;
    yi = (point1.lat - point2.lat) * latLength;
    
    return abs(PYTHAG(xi, yi));
}

// Set point as coordinate from base coordinate

int point_to_coord(coord_t base, point_t point, coord_t *result)
{
    double latLength = lat_degree_distance(base.lat);
    double lonLength = lon_degree_distance(base.lat);

    result->lat = point.y / latLength + base.lat; 
    result->lon = point.x / lonLength + base.lon; 

    return 1;
}

// Return length of a to b

double get_difference(double a, double b)
{
    if (a < b)
      return abs(a - b);
    else
      return abs(b - a);
}
