import pyrebase

config = {
    "apiKey": "AIzaSyBYuBr7IfqHo3i4aDZmIk5bGQLlyYkN51c",
    "authDomain": "fota-d0e0a.firebaseapp.com",
    "storageBucket": "fota-d0e0a.appspot.com",
    "databaseURL": "https://console.firebase.google.com/u/0/project/fota-d0e0a/database/fota-d0e0a-default-rtdb/data/~2F"
}

firebase = pyrebase.initialize_app(config)
db = firebase.database()

# Specify the path to the data you want to retrieve within the Firebase Realtime Database
data_path = "gs://fota-d0e0a.appspot.com/Newupdate"

# Retrieve the data
try:
    data = db.child(data_path).get().val()
    if data:
        # Process the data
        print(data)
    else:
        print("Data not found at the specified path.")
except Exception as e:
    print(f"An error occurred: {str(e)}")
