# start simple
import csv

# not great version
with open('Favorite TV Shows - Form Responses 1.csv', "r") as file:
    reader = csv.reader(file)
    next(reader)  # skip the header row
    for row in reader:
        print(row[1])
        
# Better: use a dict:
with open('Favorite TV Shows - Form Responses 1.csv', "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        print(row['title'])


# find unique titles:
titles = {}
with open('Favorite TV Shows - Form Responses 1.csv', "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        title = row['title'].upper().strip()
        if title in titles:
            titles[title] += 1
        else:
            titles[title] = 1

def f(title):
    return titles[title]
    

print("-"*500)
for title in sorted(titles, key=f, reverse=True):
    print(title, titles[title])
    
    
# find the most popular show
print("-"*500)
for title in sorted(titles, key=lambda title: titles[title], reverse=True):
    print(title, titles[title])
