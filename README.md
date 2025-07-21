# **中正高中機器學習**

## 矩陣乘法例題

![image](https://hackmd.io/_uploads/H10vFoD8gg.png)


## L1, L2-Norm

:::info
:bulb: Norm 稱為範數，用於量化向量大小(距離)
:::


### &rarr; L1-Norm

![image](https://hackmd.io/_uploads/SkgCqivIlg.png)

### &rarr; L2-Norm

![image](https://hackmd.io/_uploads/ry-J2jP8le.png)

### &rarr; 正則化概念

:::info
:bulb: 正則化透過處罰項，讓 argmin(L(w)+R(w)) 去除掉 R(w) 過大(w 權重大)的情況出現
:::

![image](https://hackmd.io/_uploads/B1qXkHcUll.jpg)
![image](https://hackmd.io/_uploads/ByqwJHqUll.jpg)


### &rarr; 基於 L1,L2-Norm 正則化的梯度下降法
:::info
:bulb: 梯度下降法會根據後面偏微分結果，改變中間是要做+或-，因為梯度下降法的目標在於最小化目標(Loss)
  當偏微分為正 -> 當前 Wj 方向會導致 Loss 變大(遞增) -> 往相反(遞減)方向走所以是 - 號
  當偏微分為負 -> 當前 Wj 方向會導致 Loss 變小(遞減) -> 往相同(遞減)方向走所以是 + 號
:::
![image](https://hackmd.io/_uploads/HJUOfhvLex.png)

### &rarr; L1-Norm 梯度下降法

:::info
:bulb: L1-Norm 正則化 -> 將不重要特徵的權重設成0 (砍掉特徵) 
:::
![image](https://hackmd.io/_uploads/B1agm3v8xe.png)

### &rarr; L2-Norm 梯度下降法

:::info
:bulb: L2-Norm 正則化 -> 將不重要特徵的權重設為非常小但≠0
:::
![image](https://hackmd.io/_uploads/BJgrm3v8xl.png)


## Rank

### &rarr; 概念
![image](https://hackmd.io/_uploads/rJ5SlawIgl.jpg)

### &rarr; 例題
![image](https://hackmd.io/_uploads/rJY2gpwIlx.jpg)

:::spoiler 解答
![image](https://hackmd.io/_uploads/r19JZTD8xe.jpg)

剩下 2 row 無法消除 -> Rank(A)=2
:::



## PCA(Principal components analysis)

### &rarr; 概念

PCA(主成分分析)：將原始資料投影到抽象的低維空間

原因：
1. 將原始資料投影到抽象的低維空間
2. 某些變數資訊量較少(對於辨識任務幾乎沒幫助)
3. 變數間存在高度關聯性

目標：降維後資料能代表原本高維資料

![image](https://hackmd.io/_uploads/BJN0lHcLeg.png)
> Source: https://medium.com/ai%E5%8F%8D%E6%96%97%E5%9F%8E/preprocessing-data-%E4%B8%BB%E6%88%90%E5%88%86%E5%88%86%E6%9E%90-pca-%E5%8E%9F%E7%90%86%E8%A9%B3%E8%A7%A3-afe1fd044d4f

### &rarr; 方法

Step 1 -> 求出斜方差矩陣 (找變數間關聯)
Step 2 -> 特徵分解 (找特徵向量v-方向, 特徵值μ-重要性)
Step 3 -> 選擇特徵值(主成分)前幾高的特徵向量
Step 4 -> 藉由特徵向量進行低維空間投影

:::info
:bulb: 補充：
1. 特徵向量類似於線性獨立的基底
2. 特徵值即變異量
   (變異量小->近似常數->辨識任務沒幫助)
:::

:::spoiler 詳細過程

![image](https://hackmd.io/_uploads/rkME53vLeg.jpg)

![image](https://hackmd.io/_uploads/BkaS52vLge.jpg)

![image](https://hackmd.io/_uploads/rkiUc2vUxg.jpg)

![image](https://hackmd.io/_uploads/H16D52DLxx.jpg)

![image](https://hackmd.io/_uploads/SJ8K5hP8el.jpg)

![image](https://hackmd.io/_uploads/H1H5q3v8lg.jpg)

![image](https://hackmd.io/_uploads/HJri5hw8lx.jpg)

![image](https://hackmd.io/_uploads/HyLA5hD8xx.jpg)

![image](https://hackmd.io/_uploads/BkIko3DUex.jpg)

![image](https://hackmd.io/_uploads/H1Qlo2PIel.jpg)

:::

### &rarr; 例題

![image](https://hackmd.io/_uploads/Bk3TsnD8ge.png)

:::spoiler 解答
Step 1 -> 求斜方差矩陣 C
![image](https://hackmd.io/_uploads/H12zhnDIxx.png)

Step 2 -> 特徵分解
![image](https://hackmd.io/_uploads/B1w9anPLll.png)
![image](https://hackmd.io/_uploads/rk4pphPLex.png)
![image](https://hackmd.io/_uploads/SJpg02wIxe.png)
![image](https://hackmd.io/_uploads/HJvM0hv8ex.png)

Step 3 -> 選擇特徵向量
![image](https://hackmd.io/_uploads/BJVYC2DUel.png)

Step 4 -> 投影至低維空間
![image](https://hackmd.io/_uploads/B1Ux1TwUgx.png)


:::

