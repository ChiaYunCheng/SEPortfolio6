/*
 * Created  by rbh, 30/01/11
 * Modified by nas, 21/12/16
 */

#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <cmath>

#include "utilities.h"
#include "xmlparser.h"
#include "track.h"

namespace GPXP
{
  Track::Track(string source, bool isFileName)
  {
      using namespace XML_Parser;
      using std::endl;

	  if (isFileName)
	  {
		  if (!(canOpenFile(source)))
		  {
			  return;
		  }
	  }

	  if (checkFor(source, "gpx") && checkFor(source, "trk"))
	  {
		  source = extractContentFromElement(source, "trk");
		  
		  getTrackName(source);

		  mergeTrackSegs(source);

		  if (checkFor(source, "trkpt"))
		  {
			  while (elementExists(source, "trkpt"))
			  {
				  processNextPoint(source, "trkpt");
			  }

			  oss << endl << positions.size() << " positions added";

			  calcRouteLength();

			  constructorSucceeded = true;
		  }
	  }
      
	  constructorReport = oss.str();
  }

  void Track::getTrackName(string & source)
  {
	  using namespace XML_Parser;

	  if (elementExists(source, "name"))
	  {
		  routeName = extractContentAndErase(source, "name");
		  oss << std::endl << "track name is " << routeName;
	  }
  }

  void Track::mergeTrackSegs(string & source)
  {
	  using namespace XML_Parser;

	  string mergedTrkSegs;
	  while (elementExists(source, "trkseg"))
	  {
		  string trkseg = extractContentAndErase(source, "trkseg");
		  string segname = getAndEraseElement(trkseg, "name");
		  mergedTrkSegs += trkseg;
	  }

	  if (!mergedTrkSegs.empty())
	  {
		  source = mergedTrkSegs;
	  }
  }

  string Track::getPointTime(string rawPoint) const
  {
	  return XML_Parser::extractContentFromElement(rawPoint, "time");
  }

  void Track::processNextPoint(string & source, string element)
  {
	  string point = XML_Parser::getAndEraseElement(source, element);

	  Position currentPos = getPointPosition(point);
	  string time = getPointTime(point);
	  seconds timeElapsed = 0;

	  if (!positions.empty())	//if not the first point
	  {
		  Position lastPos = positions.back();
		  if (areSameLocation(lastPos, currentPos))
		  {
			  // If we're still at the same location, then we haven't departed yet.
			  departed.back() = timeFromString(time) - startTime;
			  oss << std::endl << "position ignored: " << currentPos.toString();
			  return;
		  }
		  else
		  {
			  timeElapsed = timeFromString(time) - startTime;
			  oss << std::endl << "position added: " << currentPos.toString();
			  oss << " at time " << timeAsString(departed.back());
		  }
	  }
	  else
	  {
		  startTime = timeFromString(time);
		  oss << std::endl << "start position added: " << currentPos.toString();
	  }

	  arrived.push_back(timeElapsed);
	  departed.push_back(timeElapsed);
	  positions.push_back(currentPos);
	  positionNames.push_back(getPointName(point));
  }

  seconds Track::totalTime() const
  {
      /* Computes total elapsed time between start and finish of the Track.
       * One of the 3 functions should exploit:
       * totalTime() == restingTime() + travellingTime()
       */
      bool implemented = false;
      assert(implemented);
      return (0);
  }

  seconds Track::restingTime() const
  {
      /* Computes total elapsed time between start and finish of the Track
       * that is spent not moving.
       * One of the 3 functions should exploit:
       * totalTime() == restingTime() + travellingTime()
       */
      bool implemented = false;
      assert(implemented);
      return (0);
  }

  seconds Track::travellingTime() const
  {
      /* Total elapsed time between start and finish of the Track that is
       * spent moving.
       * One of the 3 functions should exploit:
       * totalTime() == restingTime() + travellingTime()
       */
      bool implemented = false;
      assert(implemented);
      return (0);
  }

  speed Track::maxSpeed() const
  {
      /* Computes the greatest speed between any 2 Positions in the Track.
       */
      bool implemented = false;
      assert(implemented);
      return (0.0);
  }

  speed Track::averageSpeed(bool includeRests) const
  {
      /* Computes the average speed over the track.
       * The parameter determines whether the divisor is the totalTime()
       * or the travellingTime().
       */
      bool implemented = false;
      assert(implemented);
      return (0.0);
  }

  speed Track::maxRateOfClimb() const
  {
      /* Computes the greatest rate of climb between any 2 Positions.
       */
      bool implemented = false;
      assert(implemented);
      return (0.0);
  }

  speed Track::maxRateOfDescent() const
  {
      /* Computes the greatest rate of descent between any 2 Positions.
       */
      bool implemented = false;
      assert(implemented);
      return (0.0);
  }
}
