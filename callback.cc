#include "callback.h"
#include <iostream>

Callback::Callback(const seeso::DisplayInfo &display): pc(display), wdu() {}

void Callback::OnGaze(uint64_t timestamp, float x, float y,
                      seeso::TrackingState tracking_state, seeso::EyeMovementState eye_movement_state) {
  if (tracking_state == seeso::TrackingState::SUCCESS) {
    if (view != nullptr) {
      // Get the left top position of the 'seesosample' window
      auto winPos = wdu.getWindowPosition(view->getWindowName());
      // Convert the gaze xy point to a position on the screen.
      auto gazeOnScreenPos = pc.cameraToScreen(x, y);
      // Convert the gazeOnScreenPos to the value in the 'seesosample' window.
      auto gazePoint = pc.screenToWindow(gazeOnScreenPos, winPos);
      std::cout << "gazePoint: " << gazePoint.first << ", " << gazePoint.second << std::endl;
      // Pass to view to display in the seesosample window.
      view->setPoint(gazePoint.first, gazePoint.second);
    }
  } else {
    std::cout << "OnGaze not found: " << std::endl;
  }
}

void Callback::OnCalibrationProgress(float progress) {
  // Not yet implemented.
}

void Callback::OnCalibrationNextPoint(float next_point_x, float next_point_y) {
  // Not yet implemented.
}

void Callback::OnCalibrationFinished(std::vector<float> calib_data) {
  // Not yet implemented.
}

void Callback::registerView(const std::shared_ptr<seeso::View> &view) {
  this->view = view;
}