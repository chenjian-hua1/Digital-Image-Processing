import statistics
import numpy as np

datas = [1, 0, 3, 4, 5, 5, 2, 190, 200, 200, 255, 242, 233, 233]
pop_variance_w = []
for th in range(1, 256):
    bg_px = [data for data in datas if data<th]
    forward_px = [data for data in datas if data>=th]

    pop_variance1 = statistics.pvariance(bg_px)
    pop_variance2 = statistics.pvariance(forward_px)

    w1 = len(bg_px)/len(datas)
    w2 = len(forward_px)/len(datas)
    pop_variance_w.append(w1*pop_variance1 + w2*pop_variance2)
    # print(w1*pop_variance1 + w2*pop_variance2)
    # print(pop_variance1, pop_variance2)
    # print(len(bg_px), len(forward_px))
    # print(w1, w2)
    # print(pop_variance1, pop_variance2)
    # print(f"pop_variance_w[{th}]={pop_variance_w}")

print(f"閾值為 {np.argmin(pop_variance_w)+1} 出現最小變異數總和")
# print(pop_variance_w[6])