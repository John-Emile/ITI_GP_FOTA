import requests

# Replace with the actual URL you want to access
url = "https://console.firebase.google.com/u/0/project/fota-d0e0a/database/fota-d0e0a-default-rtdb/data/~2F"

try:
    response = requests.get(url)
    if response.status_code == 200:
        data = response.json()  # Assuming the response is JSON data
        print(data)
    else:
        print(f"Failed to retrieve data. Status code: {response.status_code}")
except Exception as e:
    print(f"An error occurred: {str(e)}")
