#!/usr/bin/env python
# license removed for brevity
import numpy as np
import rospy
import cv2
import cv2.aruco as aruco

from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge


THRESHOLD = 50
bridge = CvBridge()


def get_quaternion_from_euler(roll, pitch, yaw):
    """
    Convert an Euler angle to a quaternion.

    Input
      :param roll: The roll (rotation around x-axis) angle in radians.
      :param pitch: The pitch (rotation around y-axis) angle in radians.
      :param yaw: The yaw (rotation around z-axis) angle in radians.

    Output
      :return qx, qy, qz, qw: The orientation in quaternion [x,y,z,w] format
    """
    qx = np.sin(roll / 2) * np.cos(pitch / 2) * np.cos(yaw / 2) - np.cos(roll / 2) * np.sin(pitch / 2) * np.sin(yaw / 2)
    qy = np.cos(roll / 2) * np.sin(pitch / 2) * np.cos(yaw / 2) + np.sin(roll / 2) * np.cos(pitch / 2) * np.sin(yaw / 2)
    qz = np.cos(roll / 2) * np.cos(pitch / 2) * np.sin(yaw / 2) - np.sin(roll / 2) * np.sin(pitch / 2) * np.cos(yaw / 2)
    qw = np.cos(roll / 2) * np.cos(pitch / 2) * np.cos(yaw / 2) + np.sin(roll / 2) * np.sin(pitch / 2) * np.sin(yaw / 2)

    return [qx, qy, qz, qw]

def findAruco(img, marker_size=6, total_markers=250, draw=True):

    ''' preprocessing '''
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    key = getattr(aruco, f'DICT_{marker_size}X{marker_size}_{total_markers}')
    arucoDict = aruco.Dictionary_get(key)
    arucoParam = aruco.DetectorParameters_create()
    corners, ids, _ = aruco.detectMarkers(gray, arucoDict, parameters=arucoParam)
    if ids is not None:
        x_sum = corners[0][0][0][0] + corners[0][0][1][0] + corners[0][0][2][0] + corners[0][0][3][0]
        y_sum = corners[0][0][0][1] + corners[0][0][1][1] + corners[0][0][2][1] + corners[0][0][3][1]

        x_centerPixel = int(x_sum / 4)
        y_centerPixel = int(y_sum / 4)
        cv2.circle(img, (x_centerPixel, y_centerPixel), radius=3, color=(0, 0, 255))
        if draw:
            aruco.drawDetectedMarkers(img, corners)

        return corners, ids, (x_centerPixel, y_centerPixel)
    return None, None, None


def center_aruco(img, center_aruco):
    height, width = img.shape[:2]
    center_screen = (int(width / 2), height / 2)
    # if center_aruco[0] < center_screen[0]-THRESHOLD:
    #     print("right")
    # if center_aruco[0] > center_screen[0]+THRESHOLD:
    #     print("left")
    # if center_aruco[1] < center_screen[1]-THRESHOLD:
    #     print("bottom")
    # if center_aruco[1] > center_screen[1]+THRESHOLD:
    #     print("top")


def rotate_aruco(img, corners, center):
    height, width = img.shape[:2]
    center_screen = (int(width / 2), int(height / 2))
    top_left_square_screen = (int((width-height)/2), 0)

    top_left = (int(corners[0][0][0][0]), int(corners[0][0][0][1]))
    # print(top_left, center_screen, top_left_square_screen)
    cv2.line(img, top_left, center, (0,255,0), 2)
    cv2.line(img, top_left_square_screen, center_screen, (0,255,0), 2)


    vector_1 = [top_left[0] - center[0], top_left[1] - center[1]]
    vector_2 = [top_left_square_screen[0] - center_screen[0], top_left_square_screen[1] - center_screen[1]]

    unit_vector_1 = vector_1 / np.linalg.norm(vector_1)
    unit_vector_2 = vector_2 / np.linalg.norm(vector_2)
    dot_product = np.dot(unit_vector_1, unit_vector_2)
    angle = np.arccos(dot_product)

    quaternion = get_quaternion_from_euler(0, 0, angle)

    print(quaternion)

    return quaternion

    # if angle > 0:
    #     print("rotate clockwise")
    # if angle < 0:
    #     print("rotate counter_clockwise")

def image_callback(data):
    img = bridge.imgmsg_to_cv2(data, 'bgr8')
    
    # find the arucos
    corners, ids, center = findAruco(img)
    
    if ids is not None:
        
        # bring aruco to middle
        center_aruco(img, center)
        
        # rotate aruco
        rotate_aruco(img, corners, center)
    
    
    cv2.imshow("img", img)
    cv2.waitKey(3)

def vision():
	# subscriber
	rospy.init_node('listener', anonymous=True)
	rospy.Subscriber("/raspicam_node/image", Image, image_callback)
	rospy.spin()

if __name__ == '__main__':
	vision()
