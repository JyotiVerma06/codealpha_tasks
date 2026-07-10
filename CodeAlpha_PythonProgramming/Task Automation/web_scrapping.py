import requests
from bs4 import BeautifulSoup


url = "https://www.python.org"   
response = requests.get(url)

if response.status_code == 200:
    soup = BeautifulSoup(response.text, 'html.parser')
    title = soup.title.string.strip()

    with open("title.txt", "w", encoding="utf-8") as f:
        f.write(title)

    print("Webpage title saved to title.txt")
else:
    print("Failed to retrieve webpage. Status code:", response.status_code)
