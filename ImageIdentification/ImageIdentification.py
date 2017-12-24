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
list = os.listdir(rootdir) #�г��ļ��������е�Ŀ¼���ļ�
for i in range(0,len(list)):
    imagePath = os.path.join(rootdir,list[i])
    img = cv2.imread(imagePath)
    GrayImage=cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)  
    # ��ֵ�˲�  
    GrayImage= cv2.medianBlur(GrayImage,5)  
    ret,th1 = cv2.threshold(GrayImage,127,255,cv2.THRESH_BINARY)  
    #3 ΪBlock size, 5Ϊparam1ֵ  
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
    #�ͷŴ���
    cv2.destroyAllWindows() 
    I = Image.open(imagePath)
    L = I.convert('L')   #ת��Ϊ�Ҷ�ͼ
    L = I.convert('1')   #ת��Ϊ��ֵ��ͼ
    L.save(imagePath)

def splitimage(src, rownum, colnum, dstpath):
    img = Image.open(src)
    w, h = img.size
    if rownum <= h and colnum <= w:
        print('Original image info: %sx%s, %s, %s' % (w, h, img.format, img.mode))
        print('��ʼ����ͼƬ�и�, ���Ժ�...')

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

        print('ͼƬ�и���ϣ������� %s ��СͼƬ��' % num)
    else:
        print('���Ϸ��������и������')

src = input('������ͼƬ�ļ�·����')
if os.path.isfile(src):
    dstpath = input('������ͼƬ���Ŀ¼��������·�����ʾʹ��ԴͼƬ����Ŀ¼����')
    if (dstpath == '') or os.path.exists(dstpath):
        row = int(input('�������и�������'))
        col = int(input('�������и�������'))
        if row > 0 and col > 0:
            splitimage(src, row, col, dstpath)
        else:
            print('��Ч�������и������')
    else:
        print('ͼƬ���Ŀ¼ %s �����ڣ�' % dstpath)
else:
    print('ͼƬ�ļ� %s �����ڣ�' % src)