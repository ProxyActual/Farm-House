import numpy as np
from scipy.signal import find_peaks

def random_walk(start, length):
    steps = np.random.choice([-1.0, 1.0], size=length)
    return np.cumsum(np.insert(steps, 0, start))

start_number = 100.0
wallet_baseCoin = 100.0
wallet_tradeCoin = 0
array_length = 30000 * 2
random_array = random_walk(start_number, array_length)
random_array[random_array < 1] = 1

import matplotlib.pyplot as plt

window_size = 500
averaged_array = np.convolve(random_array, np.ones(window_size)/window_size, mode='valid')
plt.plot(averaged_array, label='Averaged Array')
peaks, _ = find_peaks(averaged_array)

valleys, _ = find_peaks(-averaged_array)

blank_array = np.zeros_like(random_array)

filtered_peaks = []
filtered_valleys = []

for i in range(len(peaks)):
    if((averaged_array[peaks[i]] - averaged_array[valleys[i]]) > 10):
        filtered_peaks.append(peaks[i])
        filtered_valleys.append(valleys[i])
        print("Peak: ", peaks[i], "Valley: ", valleys[i])

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

plt.plot(valleys, averaged_array[valleys], "o", label='Valleys')

plt.plot(peaks, averaged_array[peaks], "x")

time = array_length * 15 / 60 / 24 / 365
print("Time: ", time)
print("Wallet Value: ", wallet_baseCoin + wallet_tradeCoin * random_array[-1]/100.0, " Increase of ", (wallet_baseCoin + wallet_tradeCoin * random_array[-1]/100.0) - start_number)
plt.legend()
plt.show()



