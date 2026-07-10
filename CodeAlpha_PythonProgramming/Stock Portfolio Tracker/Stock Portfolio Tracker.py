import csv


stock_prices = {"AAPL": 180, "TSLA": 250, "MSFT": 320, "GOOG": 140, "AMZN": 130}

portfolio = {}
total_investment = 0

print("Welcome to the Stock Portfolio Tracker!")
print("Available stocks:", ", ".join(stock_prices.keys()))

while True:
    stock = input("Enter stock symbol (or 'done' to finish): ").upper()
    if stock == "DONE":
        break
    if stock not in stock_prices:
        print("Stock not found. Try again.")
        continue
    
    quantity = int(input(f"Enter quantity of {stock}: "))
    portfolio[stock] = portfolio.get(stock, 0) + quantity
    total_investment += quantity * stock_prices[stock]

print("\nYour Portfolio Summary:")
for stock, qty in portfolio.items():
    print(f"{stock}: {qty} shares → ${qty * stock_prices[stock]}")

print(f"\nTotal Investment Value: ${total_investment}")


save = input("Do you want to save results to a CSV file? (yes/no): ").lower()
if save == "yes":
    with open("portfolio_summary.csv", "w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(["Stock", "Quantity", "Value"])
        for stock, qty in portfolio.items():
            writer.writerow([stock, qty, qty * stock_prices[stock]])
        writer.writerow(["Total", "", total_investment])
    print("Portfolio saved to portfolio_summary.csv")