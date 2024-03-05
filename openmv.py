# Blob Detection and uart transport
import sensor, image, time,math
from pyb import UART
import json

sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.RGB565) # use RGB565.
sensor.set_framesize(sensor.QVGA) # use QQVGA for speed.
sensor.skip_frames(10) # Let new settings take affect.
sensor.set_auto_whitebal(False) # turn this off.
clock = time.clock() # Tracks FPS.
threshold = (62, 99, -68, -4, 8, 83)
uart = UART(3, 115200)
def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob[2]*blob[3] > max_size:
            max_blob=blob
            max_size = blob[2]*blob[3]
    return max_blob

while(True):
    img = sensor.snapshot() # Take a picture and return the image.
    blobs = img.find_blobs([threshold])
    if blobs:
            largest_blob = find_max(blobs)
            # 将质心坐标转换为 uint16 类型
            x_coord = int(largest_blob.cx())
            y_coord = int(largest_blob.cy())
            # 打印坐标
            print("Center at:", x_coord, y_coord)
            # 在图像上绘制轮廓和质心
            img.draw_rectangle(largest_blob.rect(), color=(255, 0, 0), thickness=2)
            img.draw_cross(x_coord,y_coord, color=(0, 255, 0), thickness=2)
            img_data=bytearray([0x2C,7,x_coord,y_coord,3,4,0X5B])
            uart.write(img_data)
        # 显示处理后的图像
        #img.show()
    else:
        img_data=bytearray([0x2C,7,0,0,3,4,0X5B])
        uart.write(img_data)

