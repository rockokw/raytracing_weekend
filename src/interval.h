#ifndef INTERVAL_H
#define INTERVAL_H

#include "rtweekend.h"

struct Interval {
  double min;

  double max;

  Interval() : min(+infinity), max(-infinity) {}  // Default empty interval

  Interval(double min, double max) : min(min), max(max) {}

  double Size() const { return max - min; }

  bool Contains(double x) const { return min <= x and x <= max; }

  bool Surrounds(double x) const { return min < x and x < max; }

  static const Interval kEmpty;

  static const Interval kUniverse;
};

const Interval Interval::kEmpty = Interval(+infinity, -infinity);

const Interval Interval::kUniverse = Interval(-infinity, +infinity);

#endif
