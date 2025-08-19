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

### &rarr; 平均濾波器
:bulb: 局部平均化可將原本高亮度值壓低，達到模糊效果即低通濾波器
![image](https://hackmd.io/_uploads/rk1cUoxtee.jpg)


### &rarr; 高斯濾波器
:bulb: 雖然跟平均濾波器都是低通濾波器，都可以達到模糊效果，但差在高斯比較能保留原始圖片特性，越靠近處理點的位置權重越重，盡可能凸顯原始的亮度，不是像平均給同樣的係數  
![1Hews6M](https://hackmd.io/_uploads/rJD5Fogtxx.png)

### &rarr; Sobel 邊緣偵測
:bulb: 更重視中間區域的變化 濾波器係數為 (2,-2)，如果中間變化值較大時像 255,0 時->$255*2-0*(-2)=510$，相較濾波器係數為 (1,-1) 時強度多兩倍 

![sobmasks](https://hackmd.io/_uploads/SkFlXiltlx.gif)

標準版本->  
$Out=\sqrt{G_x^2+G_y^2}$

簡易版本->  
$Out=|G_x|+|G_y|$

### &rarr; Prewitt 邊緣偵測
:bulb: 相較 Sobel 運算子Prewitt會平均抓三區塊的變化值去算邊緣的強度值，三區塊的濾波器係數都為 (1,-1)。  
:pushpin: 邊緣偵測是抓出兩側的變化值大認定爲邊緣，因此邊緣偵測是高通濾波器！
![image](https://hackmd.io/_uploads/rk9FzilFxg.png)

標準版本->  
$Out=\sqrt{G_x^2+G_y^2}$

簡易版本->  
$Out=|G_x|+|G_y|$

### &rarr; 中值濾波器
:bulb: 用於消除胡椒鹽雜訊(局部只有一兩個點異常變化)，採用取局部中值方式可避開這些極少數點  
![1484949784-577764374](https://hackmd.io/_uploads/ByVEqoxFxe.png)
> Souce： https://honglung.pixnet.net/blog/post/85115497

### &rarr; 例題
![image](https://hackmd.io/_uploads/r1xnojeKxl.png)

(1) High Pass：  
(2) Low Pass：  
(3) Unsharp：  
(4) Average：  
(5) Gaussian：  
(6) Second Derivative：  
(7) Denoise：  
(8) Smooth：

:::spoiler 解釋
:bulb: 簡單分辨法 ->  
&nbsp; &nbsp; &nbsp;高通：係數總和為 0  
&nbsp; &nbsp; &nbsp;低通：係數總和為 1  
&nbsp; &nbsp; &nbsp;但有特殊情況不符合，像是係數正負值都有時基本上都不是低通

a -> $45^\circ$ 邊緣, High Pass  
b -> 中心亮度突出偵測(類似邊緣偵測)，總合也為0所以是 High Pass  
c -> 總和為1但不是 Low Pass，而是更強調中心是高亮度值的區塊，否則如果區塊中心與周遭部分差不多或更小時，該點會被其他周圍點減到消失(係數中心是正 周圍負)，這個就是「銳化」  
d -> 平均濾波器, Low Pass  
e -> $135^\circ$ 邊緣, High Pass  
f -> 垂直邊緣, High Pass  
g -> 與 b 相同，High Pass  
h -> 中心係數高周遭係數大小下降，高斯濾波器, Low Pass  
i -> 見 c ，如果局部數值都差不多甚至是中心較小時，經過該處理會消失留下中心較亮的部分，可以做銳化  
j -> 保留中心亮度值，所以處理完還是原本圖片，不是 High 也不是 Low Pass  
k -> 垂直邊緣(Sobel), High Pass  
l -> $45^\circ$ 邊緣, High Pass  
m -> 見 h 說明，高斯濾波器, Low Pass
:::


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
---
:bulb: 使用線性方程式 $\frac{y-1}{x-1}$ = $\frac{w_y-1}{w_x-1}$ -> (移項後)${x}=\frac{w_y-1}{w_x-1}(y-1)+1$ 帶入縮放圖片位置($y$)求出原始圖片位置($x$)

&nbsp; &nbsp; &nbsp;${y}$->縮放後影像位置 ${x}$->縮放前影像位置 ${w_y}$->縮放後長度 ${w_x}$->縮放前長度

### &rarr; 進階1 - 鄰近補值
---
:information_source: 因為縮放後圖片位置 逆求 原始影像位置不一定整數

:bulb: 鄰近補值->取最近的點作為結果(四捨五入)

:pushpin: 假設算出 3.2 -> $ans=round(3.2)=3$


### &rarr; 進階2 - 線性插值
---
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


:pencil2: Pre Step ->  
$α=x_c-floor(x_c)$  
$β=y_c-floor(y_c)$

:pencil2: Step 1 ->  

$UP=LeftUp*(1-α)+RightUp*α$  
$DOWN=LeftDown*(1-α)+RightDown*α$

:pencil2: Step 2 ->  

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

:pencil2: Step 1 -> 反旋轉(要考慮中心點旋轉)  
:bulb: 反旋轉方程只是將原本旋轉方程的 θ -> -θ
![image](https://hackmd.io/_uploads/rkBe3Fh_le.png)

:pencil2: Step 2  
使用線性內插法或鄰近補值法(反旋轉後非整數)


## 連通標記

:bulb: 四連通的結構元素是看左跟上，所以該點的左,上有 label 值時，代表該點label與周圍的label為同一連通區塊可合併，連通區塊總數為獨立 label 值數量
![diagram](https://hackmd.io/_uploads/S1cUw3Ztxe.jpg)
> Source：https://zhajiman.github.io/post/connected_component_labelling/

:pushpin: 八連通差在結構元素而已，方法與四連通都一樣。  
結構元素在程式碼時只要看 x->掃描點和左,上區域就好(已掃描區塊)，因為掃描由左到右上到下，當前掃描點右邊下面是還沒看過的區塊！
![image](https://hackmd.io/_uploads/BJr-93ZYll.jpg)

a->四連通 b->八連通


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