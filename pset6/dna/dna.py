# Moshe Rubin
# 2/3/2021
# DNA problem set 6
# https://cs50.harvard.edu/x/2021/psets/6/dna/

import sys
import csv


def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)
    print(match_dna())

# make a people dict, where names are keys and values are dicts of STR counts


def make_people_dict():
    people = {}
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for line in reader:
            name = line.pop('name')
            people[name] = line
                
    # print(people, sep='\n')
    return people


def load_dna_seq():
    with open(sys.argv[2]) as dna_file:
        dna = dna_file.read()
    dna = dna.replace("\n", "")
    return dna


def load_STR_seq():
    with open(sys.argv[1]) as file:
        reader = csv.reader(file)
        STRs = list(reader)[0]
        STRs.pop(0)
    return STRs
        

def search_for_str():
    str_list = load_STR_seq()
    dna_seq = load_dna_seq()
    
    # make a dict of STR counts
    counts = {}
    for STR in str_list:
        counts[STR] = 0
    
    dna_seq_len = len(dna_seq)
    # print(dna_seq)
    for STR in str_list:
        repeat = 1
        while (STR * repeat) in dna_seq:
            counts[STR] = repeat
            repeat += 1
    return counts
    

def match_dna():
    people = make_people_dict()
    str_counts = search_for_str()
    # print(str_counts)
    
    for person in people:
        person_str_count = people[person]
        match = True
        for seq in person_str_count:
            match = match and (int(person_str_count[seq]) == str_counts[seq])
        if match:
            return person
    return "No match"
    
            
if __name__ == "__main__":
    main()
                