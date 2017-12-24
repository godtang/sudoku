import os
from PIL import Image
import cv2


srcFile = 'F:/code/sudoku/Debug/image/nomarl_61.png'
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
    # 中值滤波  
    GrayImage= cv2.medianBlur(GrayImage,5)  
    ret,th1 = cv2.threshold(GrayImage,127,255,cv2.THRESH_BINARY)  
    #3 为Block size, 5为param1值  
    th2 = cv2.adaptiveThreshold(GrayImage,255,cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY,3,5)  
    th3 = cv2.adaptiveThreshold(GrayImage,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY,3,5)  
    titles = ['Gray Image', 'Global Thresholding (v = 127)', 'Adaptive Mean Thresholding', 'Adaptive Gaussian Thresholding']  
    images = [GrayImage, th1, th2, th3]  
    for i in xrange(4):  
       plt.subplot(2,2,i+1),plt.imshow(images[i],'gray')  
       plt.title(titles[i])  
       plt.xticks([]),plt.yticks([])  
    plt.show()  
    cv2.waitKey(0)
    #释放窗口
    cv2.destroyAllWindows() 
    I = Image.open(imagePath)
    L = I.convert('L')   #转化为灰度图
    L = I.convert('1')   #转化为二值化图
    L.save(imagePath)

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