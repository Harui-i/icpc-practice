import os
import requests

# Fetch environment variables
DROPBOX_REFRESH_TOKEN = os.getenv('DROPBOX_REFRESH_TOKEN')
DROPBOX_APP_KEY = os.getenv('DROPBOX_APP_KEY')
DROPBOX_APP_SECRET = os.getenv('DROPBOX_APP_SECRET')

# Dropbox API URL for token refresh
url = "https://api.dropbox.com/oauth2/token"

# Prepare the data for the POST request
data = {
    'refresh_token': DROPBOX_REFRESH_TOKEN,
    'grant_type': 'refresh_token',
    'client_id': DROPBOX_APP_KEY,
    'client_secret': DROPBOX_APP_SECRET
}

# Make the POST request
response = requests.post(url, data=data)

# Check for success and print the result
if response.status_code == 200:
    DROPBOX_ACCESS_TOKEN = response.json().get('access_token')
    print(f"new dropbox access token : {DROPBOX_ACCESS_TOKEN}")


else:
    print("Error:", response.status_code, response.text)
