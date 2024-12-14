import yfinance as yf
import datetime

def get_bitcoin_price_at_datetime(date_time):
    btc = yf.Ticker("ETH-USD")
    hist = btc.history(start=date_time.strftime('%Y-%m-%d'), end=(date_time + datetime.timedelta(days=1)).strftime('%Y-%m-%d'))
    
    if not hist.empty:
        return hist.iloc[0]['Close']
    else:
        return None

priceHistory = []

# Example usage
date_time_str = '2022-01-01 12:00:00'
date_time = datetime.datetime.strptime(date_time_str, '%Y-%m-%d %H:%M:%S')
end_time = datetime.datetime.now()

while date_time < end_time:
    price = get_bitcoin_price_at_datetime(date_time)
    if price:
        priceHistory.append(price)
        print(f'The price of Bitcoin on {date_time.strftime("%Y-%m-%d %H:%M:%S")} was ${price}')
    else:
        print(f'Could not fetch the Bitcoin price for {date_time.strftime("%Y-%m-%d %H:%M:%S")}')
    date_time += datetime.timedelta(hours=12)
date_time = datetime.datetime.strptime(date_time_str, '%Y-%m-%d %H:%M:%S')
price = get_bitcoin_price_at_datetime(date_time)

if price:
    print(f'The price of Bitcoin on {date_time_str} was ${price}')
else:
    print('Could not fetch the Bitcoin price for the given date and time.')

import matplotlib.pyplot as plt

# Plotting the price history
dates = [date_time + datetime.timedelta(hours=12 * i) for i in range(len(priceHistory))]
plt.figure(figsize=(10, 5))
plt.plot(dates, priceHistory, linestyle='-', color='b')
plt.xlabel('Date and Time')
plt.ylabel('Bitcoin Price (USD)')
plt.title('Bitcoin Price History')
plt.grid(True)
plt.xticks(rotation=45)
plt.tight_layout()
plt.show()