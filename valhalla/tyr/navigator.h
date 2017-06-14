#ifndef VALHALLA_TYR_NAVIGATOR_H_
#define VALHALLA_TYR_NAVIGATOR_H_

#include <vector>
#include <string>
#include <tuple>

#include <valhalla/baldr/json.h>
#include <valhalla/baldr/location.h>
#include <valhalla/midgard/encoded.h>
#include <valhalla/midgard/pointll.h>
#include <valhalla/proto/route.pb.h>
#include <valhalla/proto/navigator.pb.h>

namespace valhalla {
namespace tyr {

// Off route threshold in meters
constexpr uint32_t kOffRouteThreshold = 50;

// Close to origin threshold in meters
constexpr uint32_t kOnRouteCloseToOriginThreshold = 20;

// Pre-transition base threshold in seconds
constexpr uint32_t kPreTransitionBaseThreshold = 4;

// Number of words per second - used to calculate pre-transition threshold
constexpr float kWordsPerSecond = 2.5f;

// Minimum speed threshold in meters per second (~1 KPH)
constexpr float kMinSpeedThreshold = 0.277f;

// Transition alert upper and lower deltas
constexpr float kTransitionAlertUpperDelta = 0.03f;
constexpr float kTransitionAlertLowerDelta = 0.03f;

// Minimum speed for certain transition alert types
constexpr uint32_t kInitialLongTransitionAlertMinSpeed = 28; // meters per second (~62.6 MPH)
constexpr uint32_t kInitialShortTransitionAlertMinSpeed = 18; // meters per second (~40.3 MPH)

// TODO metric

// Initial long transition alert length, length bounds, and
// minimum maneuver length threshold
constexpr float kInitialLongTransitionAlertLength = 2.0f;
constexpr float kInitialLongTransitionAlertLowerLength = kInitialLongTransitionAlertLength - kTransitionAlertLowerDelta;
constexpr float kInitialLongTransitionAlertUpperLength = kInitialLongTransitionAlertLength + kTransitionAlertUpperDelta;
constexpr float kInitialLongTransitionAlertMinManeuverLength = kInitialLongTransitionAlertLength * 2.0f;

// Initial short transition alert length, length bounds, and
// minimum maneuver length threshold
constexpr float kInitialShortTransitionAlertLength = 1.0f;
constexpr float kInitialShortTransitionAlertUpperLength = kInitialShortTransitionAlertLength + kTransitionAlertUpperDelta;
constexpr float kInitialShortTransitionAlertLowerLength = kInitialShortTransitionAlertLength - kTransitionAlertLowerDelta;
constexpr float kInitialShortTransitionAlertMinManeuverLength = kInitialShortTransitionAlertLength * 2.0f;

// Post-transition lower and upper bounds in seconds
constexpr uint32_t kPostTransitionLowerBound = 2;
constexpr uint32_t kPostTransitionUpperBound = 6;

// Closest point tuple indexes
constexpr size_t kClosestPoint = 0;
constexpr size_t kClosestPointDistance = 1;
constexpr size_t kClosestPointSegmentIndex = 2;

// Used instruction tuple indexes
constexpr size_t kInitialTransitionAlert = 0; // 2 or 1 miles depending on speed
constexpr size_t kFinalTransitionAlert = 1;   // half or quarter mile depending on speed
constexpr size_t kPreTransition = 2;
constexpr size_t kPostTransition = 3;

class Navigator {
  public:

    Navigator();

    virtual ~Navigator() = default;

    Navigator(Navigator&&) = default;
    Navigator& operator=(Navigator&&) = default;

    Navigator(const Navigator&) = default;
    Navigator& operator=(const Navigator&) = default;

    NavigationStatus SetRoute(const std::string& route_json_str);

    NavigationStatus OnLocationChanged(const FixLocation& fix_location);


  protected:

    void SetUnits();
    bool HasKilometerUnits() const;

    void SetShapeLengthTime();

    void SetUsedInstructions();

    bool IsDestinationShapeIndex(size_t idx) const;

    bool IsStartManeuverIndex(size_t idx) const;
    bool IsDestinationManeuverIndex(size_t idx) const;

    size_t FindManeuverIndex(size_t begin_search_index, size_t shape_index) const;
    size_t RfindManeuverIndex(size_t rbegin_search_index, size_t shape_index) const;

    NavigationStatus SnapToRoute(const FixLocation& fix_location);

    bool StartingNavigation(const NavigationStatus_RouteState& prev_route_state,
        const NavigationStatus_RouteState& curr_route_state) const;

    bool OnRouteLocationCloseToOrigin(const NavigationStatus& nav_status) const;

    float UnitsToMeters(float units) const;

    size_t GetWordCount(const std::string& instruction) const;

    uint32_t GetSpentManeuverTime(const FixLocation& fix_location,
        const NavigationStatus& nav_status) const;

    uint32_t GetRemainingManeuverTime(const FixLocation& fix_location,
        const NavigationStatus& nav_status) const;

    uint32_t GetPreTransitionThreshold(size_t instruction_index) const;

    bool IsTimeWithinBounds(uint32_t time, uint32_t lower_bound,
        uint32_t upper_bound) const;

    bool IsLengthWithinBounds(float length, float lower_bound,
        float upper_bound) const;

    bool IsInitialTransitionAlert(const FixLocation& fix_location,
        const NavigationStatus& nav_status, float& alert_length) const;

    /////////////////////////////////////////////////////////////////////////////

    // Specified route to navigate
    Route route_;

    // Current route state of navigator
    NavigationStatus_RouteState route_state_;

    // Current leg index
    size_t leg_index_;

    // Current maneuver index
    size_t maneuver_index_;

    // Boolean kilometer unit flag
    bool kilometer_units_;

    // Current leg shape
    std::vector<midgard::PointLL> shape_;

    // Current shape index
    size_t current_shape_index_;

    // Maneuver speeds in units per second
    std::vector<float> maneuver_speeds_;

    // Remaining leg length and time indexed by shape
    std::vector<std::pair<float, uint32_t>> remaining_leg_values_;

    // List of tuples by maneuver index that keeps track of the used instructions
    //     kInitialTransitionAlert
    //     kCloseTransitionAlert
    //     kPreTransition
    //     kPostTransition
    std::vector<std::tuple<bool, bool, bool, bool>> used_instructions_;

};


}
}

#endif  // VALHALLA_TYR_NAVIGATOR_H_
