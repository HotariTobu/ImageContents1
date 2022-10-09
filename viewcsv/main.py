# %matplotlib widget

# importing required libraries
import pandas as pd
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

def draw(path: str):
  # CSVからデータを読み込む
  data = pd.read_csv(path, header=None, skiprows=1)

  # 3Dグラフの初期化
  fig = plt.figure()
  ax = fig.add_subplot(111, projection='3d')

  # データの準備
  Xgrid = data.columns.values.astype(np.float32)
  Ygrid = data.index.values.astype(np.float32)
  X, Y = np.meshgrid(Xgrid, Ygrid)
  Z = data.values

  # Plot a basic wireframe.
  ax.plot_surface(X, Y, Z, rstride=10, cstride=10)

  # 必要な場合はここでその他の設定をします。
  plt.xlim(0, 1000)
  plt.ylim(0, 1000)
  ax.set_zlim(-500, 500)

  # 表示
  plt.show()

draw('../destination_data/53394610_dsm_1m.csv')
# draw('../destination_data/sample.csv')

input()