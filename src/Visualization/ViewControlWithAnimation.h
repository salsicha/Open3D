// ----------------------------------------------------------------------------
// -                       Open3DV: www.open3dv.org                           -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015 Qianyi Zhou <Qianyi.Zhou@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#pragma once

#include "ViewControl.h"
#include "ViewTrajectory.h"

namespace three {

class ViewControlWithAnimation : public ViewControl {
public:
	enum AnimationMode {
		ANIMATION_FREEMODE = 0,
		ANIMATION_REVIEWMODE = 1,
		ANIMATION_PLAYMODE = 2,
	};

public:
	virtual void Reset();
	virtual void ChangeFieldOfView(double step);
	virtual void Scale(double scale);
	virtual void Rotate(double x, double y);
	virtual void Translate(double x, double y);

	void AddLastKeyFrame() {
		view_trajectory_.view_status_.push_back(ConvertToViewStatus());
	}
	void DeleteLastKeyFrame() {
		if (!view_trajectory_.view_status_.empty()) {
			view_trajectory_.view_status_.pop_back();
		}
	}
	void ClearAllKeyFrames() {
		view_trajectory_.view_status_.clear();
	}
	void AddSpinKeyFrames(int num_of_key_frames = 20);
	size_t NumOfKeyFrames() const {
		return view_trajectory_.view_status_.size();
	}

	void ToggleTrajectoryLoop();
	void ChangeTrajectoryInterval(int change);
	int GetTrajectoryInterval() const {
		return view_trajectory_.interval_;
	}

protected:
	ViewTrajectory::ViewStatus ConvertToViewStatus();
	void ConvertFromViewStatus(const ViewTrajectory::ViewStatus status);

protected:
	AnimationMode animation_mode_ = ANIMATION_FREEMODE;
	ViewTrajectory view_trajectory_;
};

}	// namespace three
