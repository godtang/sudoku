import os
import sys
from PIL import Image
import cv2 
import time

def splitimage(src, rownum, colnum, dstpath):
    img = Image.open(src)
    w, h = img.size
    if rownum <= h and colnum <= w:
        print('Original image info: %sx%s, %s, %s' % (w, h, img.format, img.mode))
        print('开始处理图片切割, 请稍候...')

        s = os.path.split(src)
        if dstpath == '':
            dstpath = s[0]
        fn = s[1].split('.')
        basename = fn[0]
        ext = fn[-1]

        num = 0
        rowheight = h // rownum
        colwidth = w // colnum
        for r in range(rownum):
            for c in range(colnum):
                box = (c * colwidth, r * rowheight, (c + 1) * colwidth, (r + 1) * rowheight)
                img.crop(box).save(os.path.join(dstpath, basename + '_' + str(num) + '.' + ext), ext)
                num = num + 1

        print('图片切割完毕，共生成 %s 张小图片。' % num)
    else:
        print('不合法的行列切割参数！')


'''
src = input('请输入图片文件路径：')
if os.path.isfile(src):
    dstpath = input('请输入图片输出目录（不输入路径则表示使用源图片所在目录）：')
    if (dstpath == '') or os.path.exists(dstpath):
        row = int(input('请输入切割行数：'))
        col = int(input('请输入切割列数：'))
        if row > 0 and col > 0:
            splitimage(src, row, col, dstpath)
        else:
            print('无效的行列切割参数！')
    else:
        print('图片输出目录 %s 不存在！' % dstpath)
else:
    print('图片文件 %s 不存在！' % src)
'''

def InverseWhite(img):  
    w,h=img.size  
    data=img.getdata()
    for x in range(w):  
        for y in range(h):  
            #img.putpixel((x,y),255-data[y*w+x])  
            if data[y*w+x]!=255:#255是白色 0是黑色  
                img.putpixel((x,y),0)  
            else:  
                img.putpixel((x,y),255)  
    return img 

def Identification(imagePath):
    img = Image.open(imagePath)
    data=img.getdata()
    number = -1
    if IsZero(data):
        number = 0
    else:
        number = SimilarityRatio(data)
    return number

def IsZero(data):
    img = Image.open('F:/code/sudoku/Debug/image/mold/0/0_1.png')
    moldData=img.getdata()
    w,h=moldData.size
    indexEqui = 0
    indexTotal = 0
    for x in range(w):  
        for y in range(h):
            if data[y*w+x] == moldData[y*w+x]:
                indexEqui = indexEqui + 1
            indexTotal = indexTotal + 1
    ratio = (indexEqui+0.0) / (indexTotal)
    if ratio > 0.99 :
        return True
    else:
        return False

def SimilarityRatio(data):
    moldPath = 'F:/code/sudoku/Debug/image/mold/'
    maxPossibleNumber = 0
    for iMold in range(1,10):
        moldNumberPath = moldPath + str(iMold)
        list = os.listdir(moldNumberPath) #列出文件夹下所有的目录与文件
        for i in range(0,len(list)):            
            imagePath = os.path.join(moldNumberPath,list[i])
            img = Image.open(imagePath)
            moldData=img.getdata()
            w,h=img.size
            indexEqui = 0
            indexTotal = 0
            for x in range(w):  
                for y in range(h):
                    if data[y*w+x] == moldData[y*w+x] and 0 == data[y*w+x]:
                        indexEqui = indexEqui + 1
                    if 0 == data[y*w+x]:
                        indexTotal = indexTotal + 1
            if 0 == indexTotal :
                continue
            ratio = (indexEqui+0.0) / (indexTotal)
            #print str(i) + "|" + str(ratio) + "|" + str(indexEqui) + "|" + str(indexTotal)
            if ratio > 0.90:
                return iMold
    return maxPossibleNumber


if __name__ == '__main__':
    srcFile = 'F:/code/sudoku/Debug/image/nomarl_62.png'
    s = os.path.split(srcFile)
    dstpath = s[0]
    fn = s[1].split('.')
    basename = fn[0]
    ext = fn[-1]
    y=540
    width=105
    height=105
    img = Image.open(srcFile)

    numberThinList = [0,1,3,4,6,7]
    numberThickList = [2,5]
    countTick = 1
    for i in range(0,9):
        x=28
        for j in range(0,9):
            #print "x="+str(x)
            box = (x+2, y+2, x+width, y+height)
            img.crop(box).save(os.path.join(dstpath+'/splite', basename + '_'+str(countTick)+'.' + ext), ext)
            if j in numberThinList:
                x = x + 6 + width+2
            elif j in numberThickList:
                x = x + 12 + width+2
            countTick = countTick + 1
        if i in numberThinList:
            y = y + 6 + height+2
        elif i in numberThickList:
            y = y + 12 + height+2

    rootdir = 'F:/code/sudoku/Debug/image/splite/'
    list = os.listdir(rootdir) #列出文件夹下所有的目录与文件
    for i in range(0,len(list)):
        imagePath = os.path.join(rootdir,list[i])
        img = cv2.imread(imagePath)    
        GrayImage=cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
        ret, thresh = cv2.threshold(GrayImage, 12, 255,cv2.THRESH_BINARY)
        cv2.imwrite(imagePath, thresh)

    strNumberString = "{\n"
    for i in range(1,82):
        imagePath = rootdir + "nomarl_62_" + str(i) + ".png"
        #img = Image.open(imagePath)
        #img.resize((32,32),Image.ANTIALIAS)
        #img.save(imagePath, quality=100)
        number = Identification(imagePath)
        if i%9 == 1:
            strNumberString = strNumberString + '{'
        strNumberString = strNumberString + str(number)
        if i%9 != 0:
            strNumberString = strNumberString + ','
        if i%81 == 0:
            strNumberString = strNumberString + '}\n'
            break
        if i%9 == 0:
            strNumberString = strNumberString + '},\n'
    strNumberString = strNumberString + '}'
    print strNumberString

