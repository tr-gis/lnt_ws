
/* Author: Dave Coleman
   Desc:   Example control loop for reading, updating, and writing commands to a hardware interface
   using MONOTOIC system time
*/

#include <time.h>
#include "manipulator_hw_interface.h"

namespace manipulator_control
{
// Used to convert seconds elapsed to nanoseconds
static const double BILLION = 1000000000.0;

/**
 * \brief The control loop - repeatidly calls read() and write() to the hardware interface at a
 * specified frequency
 *        We use MONOTONIC time to ensure robustness in the event of system time updates/change.
 *        See
 * http://stackoverflow.com/questions/3523442/difference-between-clock-realtime-and-clock-monotonic
 */
class HWControlLoop
{
public:
  /**
   * \brief Constructor
   * \param NodeHandle
   * \param hardware_interface - the robot-specific hardware interface to be use with your robot
   */
  HWControlLoop(
      ros::NodeHandle& nh,
      boost::shared_ptr<manipulator_control::ManipulatorHWInterface> hardware_interface);

  // Run the control loop (blocking)
  void run();

protected:

  // Update funcion called with loop_hz_ rate
  void update();

  // Startup and shutdown of the internal node inside a roscpp program
  ros::NodeHandle nh_;

  // Name of this class
  std::string name_;

  // Settings
  ros::Duration desired_update_period_;
  double cycle_time_error_threshold_;

  // Timing
  ros::Duration elapsed_time_;
  double loop_hz_;
  struct timespec last_time_;
  struct timespec current_time_;

  /** \brief ROS Controller Manager and Runner
   *
   * This class advertises a ROS interface for loading, unloading, starting, and
   * stopping ros_control-based controllers. It also serializes execution of all
   * running controllers in \ref update.
   */
  boost::shared_ptr<controller_manager::ControllerManager> controller_manager_;

  /** \brief Abstract Hardware Interface for your robot */
  boost::shared_ptr<manipulator_control::ManipulatorHWInterface> hardware_interface_;

};  // end class

} // namespace
