/*
 * Created  by rbh, 27/02/15
 * Modified by nas, 21/12/16
 */

#ifndef TRACK_H_RBH270215
#define TRACK_H_RBH270215

#include <vector>

#include "gpxp.h"
#include "position.h"
#include "route.h"

namespace GPXP
{
  using std::string;
  using std::vector;

  class Track : public Route
  {
    public:
      Track(string source, bool isFileName = false);

      seconds totalTime() const;
      seconds restingTime() const;
      seconds travellingTime() const;
      speed maxSpeed() const;
      speed averageSpeed(bool includeRests = false) const;
      speed maxRateOfClimb() const;
      speed maxRateOfDescent() const;

    protected:
	  void getTrackName(string & source);
	  void mergeTrackSegs(string & source);
	  string getPointTime(string rawPoint) const;
	  void processNextPoint(string & source, string element);

    private:
      /* These vectors store the arrival time and departure time at each
       * Position in the Track.  These times are relative to the start of
       * the Track; thus arrived[0] is always 0.
       */
	  seconds startTime;
      vector<seconds> arrived;
      vector<seconds> departed;
  };
}

#endif
