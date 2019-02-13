/*
 * Copyright (C) 2019 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "TouchscreenGestureService"

#include <android-base/file.h>
#include <android-base/logging.h>

#include "TouchscreenGesture.h"

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace implementation {

const std::map<int32_t, TouchscreenGesture::GestureInfo> TouchscreenGesture::kGestureInfoMap = {
    {0, {254, "One finger up swipe", "/sys/devices/soc.0/78b9000.i2c/i2c-5/5-0040/up_swipe_enable"}},
    {1, {249, "One finger down swipe", "/sys/devices/soc.0/78b9000.i2c/i2c-5/5-0040/down_swipe_enable"}},
    {2, {250, "One finger left swipe", "/sys/devices/soc.0/78b9000.i2c/i2c-5/5-0040/left_swipe_enable"}},
    {3, {251, "One finger right swipe", "/sys/devices/soc.0/78b9000.i2c/i2c-5/5-0040/right_swipe_enable"}},
    {4, {252, "Letter C", "/sys/devices/soc.0/78b9000.i2c/i2c-5/5-0040/letter_c_enable"}},
    {5, {255, "Letter E", "/sys/devices/soc.0/78b9000.i2c/i2c-5/5-0040/letter_e_enable"}},
    {6, {256, "Letter M", "/sys/devices/soc.0/78b9000.i2c/i2c-5/5-0040/letter_m_enable"}},
    {7, {253, "Letter O", "/sys/devices/soc.0/78b9000.i2c/i2c-5/5-0040/letter_o_enable"}},
    {8, {260, "Letter S", "/sys/devices/soc.0/78b9000.i2c/i2c-5/5-0040/letter_s_enable"}},
    {9, {259, "Letter V", "/sys/devices/soc.0/78b9000.i2c/i2c-5/5-0040/letter_v_enable"}},
    {10, {257, "Letter W", "/sys/devices/soc.0/78b9000.i2c/i2c-5/5-0040/letter_w_enable"}},
    {11, {258, "Letter Z", "/sys/devices/soc.0/78b9000.i2c/i2c-5/5-0040/letter_z_enable"}},
};

// Methods from ::vendor::lineage::touch::V1_0::ITouchscreenGesture follow.
Return<void> TouchscreenGesture::getSupportedGestures(getSupportedGestures_cb resultCb) {
    std::vector<Gesture> gestures;

    for (const auto& entry : kGestureInfoMap) {
        gestures.push_back({entry.first, entry.second.name, entry.second.keycode});
    }
    resultCb(gestures);

    return Void();
}

Return<bool> TouchscreenGesture::setGestureEnabled(const Gesture& gesture, bool enabled) {
    const auto entry = kGestureInfoMap.find(gesture.id);
    if (entry == kGestureInfoMap.end()) {
        return false;
    }

    if (!android::base::WriteStringToFile((enabled ? "1" : "0"), entry->second.path)) {
        LOG(ERROR) << "Failed to write " << entry->second.path;
        return false;
    }

    return true;
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
