import csv
from cs50 import SQL


open("shows.db", "w").close()  # create an empty file
db = SQL("sqlite:///shows.db")  # kinda looks like a URL
# Opens our empty DB with nothing in it yet

db.execute("CREATE TABLE shows (id INTEGER, title TEXT, PRIMARY KEY(id))")
db.execute("CREATE TABLE genres (show_id INTEGER, genre TEXT, FOREIGN KEY(show_id) REFERENCES shows(id))")



with open("Favorite TV Shows - Form Responses 1.csv") as file:
    reader = csv.DictReader(file)
    for row in reader:
        title = row['title'].strip().upper()
        
        id = db.execute("INSERT INTO shows (title) VALUES(?)", title)  # ? is a placeholder. Like a %s in c
        # db execute returns the int that was just used for this show
        
        for genre in row["genres"].split(", "):
            db.execute("INSERT INTO genres (show_id, genre) VALUES(?, ?)", id, genre)
