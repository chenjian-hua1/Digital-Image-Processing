數位影像處理
===

## 灰階轉換
:bulb: Gray = R * 0.299 + G * 0.587 + B * 0.114
## 亮度對比調整
:bulb: a*(g-128)+128+b

&nbsp; &nbsp; &nbsp;a->對比度[0, 1.0]  b->亮度  g->灰階值

## 馬賽克
:bulb: 局部區塊都用中間的值去替代 (沒有細節)
![image](https://hackmd.io/_uploads/S1nvcWsugl.png)

## 位元切片(BitPlane)
:bulb: 假設圖片顏色深度 3Bits -> 0~7，3個位元都會有各自的切面圖
![image](https://hackmd.io/_uploads/H1XBobougg.png)

## 直方等化

### &rarr; 名詞介紹
1. 亮度->直方圖靠左(暗)、直方圖靠右(亮)
2. 對比->直方平均分布範圍(亮度分布)

![image](https://hackmd.io/_uploads/Sy80vYsuge.png)

### &rarr; 等化方法
:bulb: 通過 cmf(累計機率函數) 讓原本出現機率低的亮度值出現較多次(之前亮度值數量會累計)->達到色彩平均分布效果

![image](https://hackmd.io/_uploads/B1J0FYjOgl.png)

## 影像濾波器(Filter)



## OTSU 門檻值分割
### &rarr; 概念
:bulb: 找出一個門檻值能夠劃分前景、背景
![image](https://hackmd.io/_uploads/HJBe3Yi_gg.png)

### &rarr; 方法
:bulb: 因為要劃分前背景，所以標準差σ(集中程度)要小，否則大的話會黏在一起不好分 -> th = argmin(σ1+σ2)
![image](https://hackmd.io/_uploads/Bk5_TFodxe.png)

:::spoiler 詳細方法
![image](https://hackmd.io/_uploads/HkZjCtjdxg.png)
:::


## 影像倍率縮放
### &rarr; 基本方法
:bulb: 使用線性方程式 $\frac{y-1}{x-1}$ = $\frac{w_y-1}{w_x-1}$ -> (移項後)${x}=\frac{w_y-1}{w_x-1}(y-1)+1$ 帶入縮放圖片位置($y$)求出原始圖片位置($x$)

&nbsp; &nbsp; &nbsp;${y}$->縮放後影像位置 ${x}$->縮放前影像位置 ${w_y}$->縮放後長度 ${w_x}$->縮放前長度

### &rarr; 進階1 - 鄰近補值
:information_source: 因為縮放後圖片位置 逆求 原始影像位置不一定整數

:bulb: 鄰近補值->取最近的點作為結果(四捨五入)

:pushpin: 假設算出 3.2 -> $ans=round(3.2)=3$


### &rarr; 進階2 - 線性插值
:bulb: 線性插值->做鄰近點的加權平均(離越近的點加權越重)

:information_source: $ans=p_l*(1-α)+p_r*α$

&nbsp; &nbsp; &nbsp;$α=p_c-p_l$

&nbsp; &nbsp; &nbsp;$p_c$->當前點 $p_l$->左測鄰近點 $p_r$->右側鄰近點 $α$->右側點權重

:pushpin: 假設位置 $p_c=3.2$

$p_l=pixel[floor(p_c)]=pixel[3]$

$p_r=pixel[ceil(p_c)]=pixel[4]$

$α=p_c-p_l=3.2-3=0.2$

$ans=p_l*(1-α)+p_r*α$

&nbsp; &nbsp; &nbsp;&nbsp; $=pixel[3]*0.8+pixel[4]*0.2$


### &rarr; 進階2.1 - 二維影像線性插值

:bulb: 上下邊先各自求左右兩側的線性插值 -> $OUT=DOWN*(1-β)+UP*β$

![image](https://hackmd.io/_uploads/Sklvluhdxg.png)

Pre Step ->

$α=x_c-floor(x_c)$ 

$β=y_c-floor(y_c)$

Step 1 ->

$UP=LeftUp*(1-α)+RightUp*α$

$DOWN=LeftDown*(1-α)+RightDown*α$

Step 2 ->

$OUT=DOWN*(1-β)+UP*β$


## 影像旋轉

### &rarr; 旋轉後影像長寬

:bulb: 將原本圖片的長寬作為斜邊($r$)，透過三角函數 $sinθ, cosθ$ 投影到新圖片的長寬

![image](https://hackmd.io/_uploads/SyCAIKndel.png)  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; $w,h$->旋轉前長寬  $nw,nh$->旋轉後長寬

&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
$nw=h*sinθ+w*cosθ$  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
$nh=w*sinθ+h*cosθ$

### &rarr; 旋轉方程

![image](https://hackmd.io/_uploads/ryAeoKhulx.png)

:::spoiler 證明
![image](https://hackmd.io/_uploads/BkQSjF3ugg.png)
![image](https://hackmd.io/_uploads/rJLUiKhuxg.png)
![image](https://hackmd.io/_uploads/By4diKh_xe.png)

:::

:pushpin: 按照中心點旋轉
![image](https://hackmd.io/_uploads/HkUu6Fhdee.png)

### &rarr; 旋轉後亮度值

Step 1 -> 反旋轉(要考慮中心點旋轉)  
:bulb: 反旋轉方程只是將原本旋轉方程的 θ -> -θ
![image](https://hackmd.io/_uploads/rkBe3Fh_le.png)

Step 2 -> 使用線性內插法或鄰近補值法(反旋轉後非整數)


## 連通標記


## 自動對焦

:bulb: 自動對焦是要找出最清楚的圖片，所以邊緣應該最清楚(邊緣偵測強度值總和最大)

:pushpin: $ans=argmax[sum(edgeDetect(image))]$

## 線偵測

:bulb: 透過圖中有的白點座標，假設各種 θ 值(預想線)求 r 值，如果多點都求出相同 r 值，代表該 θ 值的線通過多個點(線段存在)
![image](https://hackmd.io/_uploads/BJRWDchOgg.png)

:pushpin: 舉例
![image](https://hackmd.io/_uploads/SkoP_q3dge.png)

## 圓偵測

### &rarr; 基本觀念

![image](https://hackmd.io/_uploads/B1vt5q3Oel.png)

圓心->$(a,b)$  半徑->$r$  
圓公式->$(x-a)^2+(y-b)^2=r^2$

![image](https://hackmd.io/_uploads/rk8kjq2Oge.png)

### &rarr; 方法

![image](https://hackmd.io/_uploads/B1jBj5ndll.png)

Step 1 -> (因為圓上任一點到圓心的距離皆為半徑$r$)，因此可以將圖中任一白點作為圓心以不同半徑 $r$ 畫圓  
Step 2 -> 如果同一半徑 $r$下畫圓，有多個圓交於一點，代表這些點都是 交點作為圓心 半徑 $r$ 的圓上的其中一點 (代表圖上有圓)