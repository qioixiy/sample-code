#!/usr/bin/env python3

import os
import cv2 as cv
import cv2
import numpy as np

# https://github.com/guoya1003/data_process/blob/master/clip_merge_picture.py

"""
输入：图片路径(path+filename)，裁剪获得小图片的列数、行数（也即宽、高）
输出：无
"""
def crop_one_picture(path, filename, cols, rows):
    img=cv2.imread(path+filename,-1)##读取彩色图像，图像的透明度(alpha通道)被忽略，默认参数;灰度图像;读取原始图像，包括alpha通道;可以用1，0，-1来表示
    sum_rows=img.shape[0]   #高度
    sum_cols=img.shape[1]   #宽度
    save_path=path+"/crop{0}_{1}/".format(cols,rows)  #保存的路径
    if not os.path.exists(save_path):
        os.makedirs(save_path)
    print("裁剪所得{0}列图片，{1}行图片.".format(int(sum_cols/cols),int(sum_rows/rows))) 
    
    for i in range(int(sum_cols/cols)):
        for j in range(int(sum_rows/rows)):
            cv2.imwrite(save_path+os.path.splitext(filename)[0]+'_'+str(j)+'_'+str(i)+os.path.splitext(filename)[1],img[j*rows:(j+1)*rows,i*cols:(i+1)*cols,:])
            print(path+"/crop/"+os.path.splitext(filename)[0]+'_'+str(j)+'_'+str(i)+os.path.splitext(filename)[1])
    print("裁剪完成，得到{0}张图片.".format(int(sum_cols/cols)*int(sum_rows/rows)))
    print("文件保存在{0}".format(save_path))

"""遍历文件夹下某格式图片"""
def file_name(root_path,picturetype):
    filename=[]
    for root,dirs,files in os.walk(root_path):
        for file in files:
            if os.path.splitext(file)[1]==picturetype:
                filename.append(os.path.join(root,file))
    return filename

"""
输入：图片路径(path+filename)，裁剪所的图片的列的数量、行的数量
输出：无
"""
def merge_picture(merge_path,num_of_cols,num_of_rows):
    filename=file_name(merge_path,".tif")
    shape=cv2.imread(filename[0],-1).shape    #三通道的影像需把-1改成1
    cols=shape[1]
    rows=shape[0]
    channels=shape[2]
    dst=np.zeros((rows*num_of_rows,cols*num_of_cols,channels),np.uint8)
    for i in range(len(filename)):
        img=cv2.imread(filename[i],-1)
        cols_th=int(filename[i].split("_")[-1].split('.')[0])
        rows_th=int(filename[i].split("_")[-2])
        roi=img[0:rows,0:cols,:]
        dst[rows_th*rows:(rows_th+1)*rows,cols_th*cols:(cols_th+1)*cols,:]=roi
    cv2.imwrite(merge_path+"merge.tif",dst)

def tranlate_image_format(in_file, out_file):
    cv2.imwrite(out_file, cv2.imread(in_file))

path='./'
filename="pattern.jpg"
tranlate_image_format('1280x360_4x2_image.png', filename)
cols=320
rows=180
crop_one_picture(path, filename, cols, rows)
