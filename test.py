import numpy as np
from scipy.signal import find_peaks

def random_walk(start, length):
    steps = np.random.choice([-1.0, 1.0], size=length)
    return np.cumsum(np.insert(steps, 0, start))

start_number = 100.0
wallet_baseCoin = 100.0
wallet_tradeCoin = 0
array_length = 30000
random_array = random_walk(start_number, array_length)
random_array[random_array < 1] = 1

import matplotlib.pyplot as plt

window_size = 1000
averaged_array = np.convolve(random_array, np.ones(window_size)/window_size, mode='valid')
plt.plot(averaged_array, label='Averaged Array')
peaks, _ = find_peaks(averaged_array)

valleys, _ = find_peaks(-averaged_array)
plt.plot(valleys, averaged_array[valleys], "o", label='Valleys')

plt.plot(peaks, averaged_array[peaks], "x")

blank_array = np.zeros_like(random_array)

filtered_peaks = []
filtered_valleys = []

for peak in peaks:
    for valley in valleys:
        if abs(averaged_array[peak] - averaged_array[valley]) >= 4:
            filtered_peaks.append(peak)
            filtered_valleys.append(valley)

peaks = np.array(filtered_peaks)
valleys = np.array(filtered_valleys)

for i in range(len(random_array)):
    if(i in peaks):
        if(wallet_baseCoin == 0):
            wallet_baseCoin = (wallet_tradeCoin * random_array[i]/100.0) * .95
            wallet_tradeCoin = 0
    elif(i in valleys):
        wallet_tradeCoin = wallet_baseCoin * 100.0 / random_array[i]
        wallet_baseCoin = 0
    
    blank_array[i] = wallet_baseCoin + (wallet_tradeCoin * random_array[i]/100.0) * .95
plt.plot(random_array, label='Random Array')

plt.plot(blank_array, label='Wallet Value')
time = array_length * 15 / 60 / 24
print("Time: ", time)
plt.legend()
plt.show()


